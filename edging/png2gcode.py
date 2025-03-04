import sys
from PIL import Image
from potrace import Bitmap, POTRACE_TURNPOLICY_MINORITY
import subprocess
import shutil

def file_to_svg(filename: str):
    try:
        image = Image.open(filename).convert('L')  # Convert to grayscale
    except IOError:
        print("Image (%s) could not be loaded." % filename)
        return

    # Invert the image so that white lines become black
    image = Image.eval(image, lambda x: 255 - x)

    bm = Bitmap(image, blacklevel=0.5)
    plist = bm.trace(
        turdsize=2,
        turnpolicy=POTRACE_TURNPOLICY_MINORITY,
        alphamax=1,
        opticurve=True,
        opttolerance=0.2,
    )

    with open(f"{filename}.svg", "w") as fp:
        fp.write(
            f'''<svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="{image.width}" height="{image.height}" viewBox="0 0 {image.width} {image.height}">''')
        parts = []
        for curve in plist:
            fs = curve.start_point
            parts.append(f"M{fs.x},{fs.y}")
            for segment in curve.segments:
                if segment.is_corner:
                    a = segment.c
                    b = segment.end_point
                    parts.append(f"L{a.x},{a.y}L{b.x},{b.y}")
                else:
                    a = segment.c1
                    b = segment.c2
                    c = segment.end_point
                    parts.append(f"C{a.x},{a.y} {b.x},{b.y} {c.x},{c.y}")
            parts.append("z")
        fp.write(f'<path stroke="black" fill="none" d="{"".join(parts)}"/>')
        fp.write("</svg>")

def png2gcode():
    file_to_svg("edges_me.png")

    # Check if svg2gcode.exe is available
    svg2gcode_path = shutil.which("svg2gcode.exe")
    if svg2gcode_path is None:
        print("Error: svg2gcode.exe is not found in the system PATH.")
        sys.exit(1)

    command = [
        svg2gcode_path, "edges_me.png.svg",
        "--off", "M4", "--on", "M5", "-o", "out.gcode", "--dpi", "1",
        "--tolerance", "5"
    ]

    result = subprocess.run(command, capture_output=True, text=True)

    print("stdout:", result.stdout)
    print("stderr:", result.stderr)

if __name__ == "__main__":
    png2gcode()
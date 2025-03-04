import cv2
import tkinter as tk
from PIL import Image, ImageTk

def start_camera_feed():
    def update_frame():
        ret, frame = cap.read()
        if ret:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img = Image.fromarray(frame)
            imgtk = ImageTk.PhotoImage(image=img)
            lbl.imgtk = imgtk
            lbl.configure(image=imgtk)
        lbl.after(10, update_frame)

    def take_photo():
        ret, frame = cap.read()
        if ret:
            cv2.imwrite("me.png", frame)
            print("Photo taken and saved as me.png")
            root.destroy()

    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 960)

    root = tk.Tk()
    root.title("Camera Feed")
    root.geometry("800x600")

    lbl = tk.Label(root)
    lbl.pack()

    btn = tk.Button(root, text="Take Photo", command=take_photo)
    btn.pack()

    update_frame()

    root.mainloop()

    cap.release()
    cv2.destroyAllWindows()
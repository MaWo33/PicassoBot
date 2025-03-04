# main.py
from time import sleep
from edge import create_gui, update_loop
from take_photo import start_camera_feed
from png2gcode import png2gcode
from send_to_serial  import start_sending
import threading
import queue

# Create a queue for tkinter operations
tk_queue = queue.Queue()

if __name__ == "__main__":
    # Start the camera feed and take a photo
    # start_camera_feed()

    # Start the update loop in a separate thread
    update_thread = threading.Thread(target=update_loop, args=(tk_queue,))
    update_thread.start()
    # Start the GUI in the main thread
    create_gui(tk_queue)

    png2gcode()
    start_sending()
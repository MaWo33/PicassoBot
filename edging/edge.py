import tkinter as tk
from time import sleep
from tkinter import ttk
from PIL import Image, ImageTk
import cv2
import numpy as np
import json
import threading
import queue

scale_factor = 1
edge_window = None
panel = None
lock = threading.Lock()

# Load slider values from file
def load_slider_values():
    with lock:
        try:
            with open('slider_values.json', 'r') as file:
                return json.load(file)
        except FileNotFoundError:
            return {'canny_low': 100, 'canny_high': 200}

# Save slider values to file
def save_slider_values(values):
    with lock:
        with open('slider_values.json', 'w') as file:
            json.dump(values, file)

# Image processing function
def make_image(canny_low, canny_high):
    # Open the image
    image = Image.open('me.png')
    # Scale down the image
    new_size = (int(image.width * scale_factor), int(image.height * scale_factor))
    image = image.resize(new_size)

    # Convert the image to grayscale
    gray_image = image.convert('L')
    gray_image.save('gray_me.png')

    blur_image = np.array(gray_image)

    blur_array = cv2.GaussianBlur(blur_image, (5, 5), 0)

    # Detect edges using Canny edge detection
    edges = cv2.Canny(blur_array, canny_low, canny_high)

    # Convert the edges array back to an image
    edges_image = Image.fromarray(edges)

    # Save the edges image as a PNG file
    edges_image.save('edges_me.png')
    print("Image saved")

    # Update the image in the Tkinter window
    img = ImageTk.PhotoImage(edges_image)
    panel.config(image=img)
    panel.image = img

def create_gui(tk_queue):
    global panel
    global edge_window
    values = load_slider_values()

    def update_values(event=None):
        values['canny_low'] = int(canny_low_slider.get())
        values['canny_high'] = int(canny_high_slider.get())
        save_slider_values(values)
        canny_low_value_label.config(text=f"Canny Low: {values['canny_low']}")
        canny_high_value_label.config(text=f"Canny High: {values['canny_high']}")

    edge_window = tk.Tk()
    edge_window.title("Canny Edge Detection")
    edge_window.geometry("800x600")

    ttk.Label(edge_window, text="Canny Low").pack()
    canny_low_slider = ttk.Scale(edge_window, from_=0, to=500, orient='horizontal', length=200)
    canny_low_slider.set(values['canny_low'])
    canny_low_slider.pack()
    canny_low_slider.bind("<Motion>", update_values)
    canny_low_value_label = ttk.Label(edge_window, text=f"Canny Low: {values['canny_low']}")
    canny_low_value_label.pack()

    ttk.Label(edge_window, text="Canny High").pack()
    canny_high_slider = ttk.Scale(edge_window, from_=0, to=500, orient='horizontal', length=200)
    canny_high_slider.set(values['canny_high'])
    canny_high_slider.pack()
    canny_high_slider.bind("<Motion>", update_values)
    canny_high_value_label = ttk.Label(edge_window, text=f"Canny High: {values['canny_high']}")
    canny_high_value_label.pack()

    img = ImageTk.PhotoImage(Image.open("edges_me.png"))
    panel = tk.Label(edge_window, image=img)
    panel.pack(side="bottom", fill="both", expand="yes")

    def process_queue():
        try:
            while True:
                task, kwargs = tk_queue.get_nowait()
                if task == 'make_image':
                    make_image(**kwargs)
        except queue.Empty:
            pass
        edge_window.after(100, process_queue)

    process_queue()
    edge_window.mainloop()

def update_loop(tk_queue):
    while True:
        values = load_slider_values()
        tk_queue.put(('make_image', {'canny_low': values['canny_low'], 'canny_high': values['canny_high']}))
        sleep(3)

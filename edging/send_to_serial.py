from idlelib.outwin import file_line_pats

import serial
import time
import os

def start_sending():
    ser = serial.Serial('COM7', 230400)  # Replace 'COM7' with your Arduino's port

    time.sleep(5)  # Wait for the serial connection to initialize

    while ser.in_waiting:  # Check if there is data waiting in the buffer
        response = ser.readline().decode('utf-8').strip()
        print(response)

    ser.write(b"receiveg")  # Send the command
    time.sleep(3)  # Give some time for Arduino to process and respond

    file_path = "out.gcode"
    arduino_ack = "OK"
    # Get file size
    file_size = os.path.getsize(file_path)

    while ser.in_waiting:  # Check if there is data waiting in the buffer
        response = ser.readline().decode('utf-8').strip()
        print(response)

    # Open and send the file
    with open(file_path, 'rb') as file:
        # Send file size first (as a string followed by newline)
        ser.write(f"{file_size}\n".encode())
        time.sleep(1)

        # Wait for Arduino to acknowledge
        while ser.in_waiting == 0:
            pass
        ack = ser.readline().decode().strip()
        if ack != arduino_ack:
            print("Failed to get acknowledgment from Arduino for the length")
            ser.close()
            exit()

        # Send file contents in chunks
        chunk_size = 511  # Adjust this based on Arduino's buffer size and processing speed
        bytes_sent = 0
        time.sleep(0.2)
        while True:
            chunk = file.read(chunk_size)
            if not chunk:
                break
            ser.write(chunk)
            bytes_sent += len(chunk)
            print(f"Progress: {bytes_sent}/{file_size} bytes sent")

            # Wait for Arduino to process the chunk
            while ser.in_waiting == 0:
                pass
            ack = ser.readline().decode().strip()
            if ack != arduino_ack:
                print("Failed to get acknowledgment from Arduino")
                ser.close()
                exit()

    print("File transfer complete")
    ser.close()


if __name__ == "__main__":
    start_sending()
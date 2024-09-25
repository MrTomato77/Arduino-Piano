import serial

# Configure the UART port
uart_port = '/dev/ttyS1'  # Replace with the correct UART port for your system
uart_baudrate = 115200
uart = serial.Serial(uart_port, uart_baudrate, timeout=1)


def read_bpm_from_uart():
    if uart.in_waiting > 0:  # Check if there is data available
        try:
            data = uart.readline().decode('utf-8', errors='ignore').strip()  # Read a line from UART
            print(data)
            return int(data)  # Convert the received data to an integer
        except ValueError:
            print("Invalid BPM received.")
    return None  # Return None if no valid data

read_bpm_from_uart()


# Main loop to read data from Arduino
while True:
    read_bpm_from_uart()

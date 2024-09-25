# uart.py
import serial

def setup_uart(port='/dev/ttyS1', baudrate=115200):
    """
    Setup the UART connection.
    :param port: UART port
    :param baudrate: Baudrate for UART communication
    :return: UART serial object
    """
    uart = serial.Serial(port, baudrate, timeout=1)
    return uart

def read_bpm(uart):
    """
    Read BPM value from UART.
    :param uart: UART serial object
    :return: Integer value of BPM, or None if invalid
    """
    if uart.in_waiting > 0:
        try:
            bpm = int(uart.readline().decode('utf-8', errors='ignore').strip())
            return bpm
        except ValueError:
            print("Invalid BPM received.")
            return None
    return None

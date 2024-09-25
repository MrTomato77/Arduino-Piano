import serial
import odroid_wiringpi as wiringpi
import time

# Configure the UART port
uart_port = '/dev/ttyS1'  # Replace with the correct UART port for your system
uart_baudrate = 115200
uart = serial.Serial(uart_port, uart_baudrate, timeout=1)

# Set up WiringPi
wiringpi.wiringPiSetup()

# Set the pin for the passive buzzer
buzzer_pin = 0  # WiringPi pin 0 (physical pin 11, GPIOX_3)

# Set the buzzer pin to output mode
wiringpi.pinMode(buzzer_pin, 1)  # OUTPUT mode for buzzer

# Create a soft tone on the buzzer pin (for passive buzzers)
wiringpi.softToneCreate(buzzer_pin)

# Minimum and Maximum BPM limits
min_bpm = 30
max_bpm = 300
bpm = 120  # Initialize BPM to a default value

def read_bpm_from_uart():
    if uart.in_waiting > 0:  # Check if there is data available
        try:
            data = uart.readline().decode('utf-8', errors='ignore').strip()  # Read a line from UART
            return int(data)  # Convert the received data to an integer
        except ValueError:
            print("Invalid BPM received.")
    return None  # Return None if no valid data

# Metronome function
def metronome():
    global bpm
    while True:
        # Check for incoming BPM from UART
        new_bpm = read_bpm_from_uart()
        if new_bpm is not None and min_bpm <= new_bpm <= max_bpm:
            bpm = new_bpm  # Update BPM if valid
            print(f"BPM updated from UART: {bpm}")

        interval = 60.0 / bpm  # Calculate the interval between beats

        # Turn the buzzer ON with the tone frequency
        wiringpi.softToneWrite(buzzer_pin, 1000)  # 1000 Hz tone
        print(f"Buzzer ON with {bpm} BPM")

        # Keep the buzzer ON for a fraction of the interval
        time.sleep(0.3)  # Duration for the beep sound

        # Turn the buzzer OFF
        wiringpi.softToneWrite(buzzer_pin, 0)
        print("Buzzer OFF")

        # Calculate remaining time for the sleep, ensuring it is non-negative
        remaining_sleep = interval - 0.3
        if remaining_sleep > 0:
            time.sleep(remaining_sleep)  # Sleep only if remaining time is positive

# Start the metronome
metronome()

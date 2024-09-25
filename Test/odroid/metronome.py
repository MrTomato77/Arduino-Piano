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

# Variables to track metronome state
last_buzz_time = 0
bpm = 60  # Default BPM
buzzer_on_duration = 0.1  # Buzzer ON duration in seconds
interval = 60.0 / bpm  # Calculate the interval between beats
buzzer_state = False  # Buzzer initially OFF

def metronome():
    global last_buzz_time, bpm, interval, buzzer_state

    if uart.in_waiting > 0:  # Check if there is data available
        try:
            # Read a line from UART and convert to integer
            bpm = int(uart.readline().decode('utf-8', errors='ignore').strip())
            print(f"New BPM received: {bpm}")
            interval = 60.0 / bpm  # Recalculate interval based on BPM
        except ValueError:
            print("Invalid BPM received.")

    current_time = time.monotonic()  # Get the current time

    if buzzer_state:  # If the buzzer is ON
        if current_time - last_buzz_time >= buzzer_on_duration:
            wiringpi.softToneWrite(buzzer_pin, 0)  # Turn the buzzer OFF
            buzzer_state = False  # Update the state to OFF
            last_buzz_time = current_time  # Record the time the buzzer was turned off
    else:  # If the buzzer is OFF
        if current_time - last_buzz_time >= interval:
            wiringpi.softToneWrite(buzzer_pin, 1000)  # Turn the buzzer ON with 1000 Hz tone
            buzzer_state = True  # Update the state to ON
            last_buzz_time = current_time  # Record the time the buzzer was turned on

while True:
    metronome()

#pip install odroid-wiringpi

import odroid_wiringpi as wpi
import time

# Define the GPIO pin connected to the buzzer
BUZZER_PIN = 18  # Replace with your specific pin number

# Initialize WiringPi with GPIO numbering
wpi.wiringPiSetupGpio()

# Set the buzzer pin as an output
wpi.pinMode(BUZZER_PIN, 1)  # 1 denotes output mode

# Function to make the buzzer sound
def buzz(frequency, duration):
    if frequency == 0:
        wpi.digitalWrite(BUZZER_PIN, 0)
        time.sleep(duration)
        return

    period = 1.0 / frequency
    delay = period / 2
    cycles = int(duration * frequency)

    for _ in range(cycles):
        wpi.digitalWrite(BUZZER_PIN, 1)  # Turn buzzer on
        time.sleep(delay)
        wpi.digitalWrite(BUZZER_PIN, 0)  # Turn buzzer off
        time.sleep(delay)

try:
    # Test the buzzer at 1000 Hz for 2 seconds
    buzz(1000, 2)

finally:
    # Clean up by setting the buzzer pin to low
    wpi.digitalWrite(BUZZER_PIN, 0)

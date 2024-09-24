import time
import odroid_wiringpi as wiringpi

# Set up WiringPi
wiringpi.wiringPiSetup()

# Set the pin for the passive buzzer
buzzer_pin = 0  # WiringPi pin 0 (physical pin 11, GPIOX_3)

# Create a soft tone on the buzzer pin (for passive buzzers)
wiringpi.softToneCreate(buzzer_pin)

# Set the frequency for the buzzer tone (example frequency 1000 Hz)
frequency = 1000  # Adjust to the desired tone frequency

# Start a loop to turn the buzzer on and off
while True:
    # Turn the buzzer ON with a tone frequency
    wiringpi.softToneWrite(buzzer_pin, frequency)
    print("Buzzer ON with tone")
    
    # Keep the buzzer ON for 1 second
    time.sleep(1)

    # Turn the buzzer OFF by setting frequency to 0
    wiringpi.softToneWrite(buzzer_pin, 0)
    print("Buzzer OFF")

    # Keep the buzzer OFF for 1 second
    time.sleep(1)

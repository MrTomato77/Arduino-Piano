import time
import odroid_wiringpi as wiringpi

# Set up WiringPi
wiringpi.wiringPiSetup()

# Set the pin for the passive buzzer
buzzer_pin = 0  # WiringPi pin 0 (physical pin 11, GPIOX_3)

# Set the pins for the buttons
increase_button_pin = 2  # WiringPi pin 2 (physical pin 13, IO.480)
decrease_button_pin = 3  # WiringPi pin 3 (physical pin 15, IO.483)

# Set the buzzer pin to output mode
wiringpi.pinMode(buzzer_pin, 1)  # OUTPUT mode for buzzer

# Set the button pins to input mode
wiringpi.pinMode(increase_button_pin, 0)  # INPUT mode for increase button
wiringpi.pinMode(decrease_button_pin, 0)  # INPUT mode for decrease button

# Enable pull-down resistors for the buttons (if needed)
wiringpi.pullUpDnControl(increase_button_pin, wiringpi.PUD_DOWN)
wiringpi.pullUpDnControl(decrease_button_pin, wiringpi.PUD_DOWN)

# Create a soft tone on the buzzer pin (for passive buzzers)
wiringpi.softToneCreate(buzzer_pin)

# Initial BPM for the metronome
bpm = 120  # Starting at 120 BPM
interval = 60.0 / bpm  # Calculate time between beats

# Frequency of the buzzer tone
frequency = 1000  # Tone frequency (1000 Hz)

# Minimum and Maximum BPM limits
min_bpm = 30
max_bpm = 300

# Start the loop for metronome and button control
while True:
    # Check if the increase button is pressed
    if wiringpi.digitalRead(increase_button_pin) == 0:
        if bpm < max_bpm:
            bpm += 10  # Increase BPM by 10
            interval = 60.0 / bpm  # Recalculate interval based on new BPM
            print(f"BPM increased to: {bpm}")
        time.sleep(0.2)  # Debounce delay for button press

    # Check if the decrease button is pressed
    if wiringpi.digitalRead(decrease_button_pin) == 0:
        if bpm > min_bpm:
            bpm -= 10  # Decrease BPM by 10
            interval = 60.0 / bpm  # Recalculate interval based on new BPM
            print(f"BPM decreased to: {bpm}")
        time.sleep(0.2)  # Debounce delay for button press

    # Turn the buzzer ON with the tone frequency
    wiringpi.softToneWrite(buzzer_pin, frequency)
    print(f"Buzzer ON with {bpm} BPM")

    # Keep the buzzer ON for a fraction of the interval
    time.sleep(0.3)  # Duration for the beep sound

    # Turn the buzzer OFF
    wiringpi.softToneWrite(buzzer_pin, 0)
    print("Buzzer OFF")

    # Wait for the remaining interval time
    time.sleep(interval - 0.3)

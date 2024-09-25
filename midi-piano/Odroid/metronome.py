# metronome.py
import odroid_wiringpi as wiringpi
import time

def setup_buzzer(pin=0):
    wiringpi.wiringPiSetup()
    wiringpi.pinMode(pin, 1)  # Set pin to OUTPUT mode
    wiringpi.softToneCreate(pin)

def run_metronome(bpm, buzzer_pin=0):

    if bpm is None:
        return 
    elif bpm <= 0:
        bpm = 1
    
    print(f"Buzzer ON with {bpm} BPM")
    interval = 60.0 / bpm  # Calculate the interval time in seconds

    # Sound the buzzer
    wiringpi.softToneWrite(buzzer_pin, 1000)  # Buzzer ON with 1000 Hz tone
    time.sleep(0.1)  # Buzzer ON for 100 milliseconds
    wiringpi.softToneWrite(buzzer_pin, 0)  # Buzzer OFF
    time.sleep(interval - 0.1)  # Wait for the rest of the interval

    print(f"interval: {interval:.2f} sec")

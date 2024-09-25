# metronome.py
import odroid_wiringpi as wiringpi
import time

def setup_buzzer(pin=0):
    """
    Setup the buzzer pin.
    :param pin: WiringPi pin number
    """
    wiringpi.wiringPiSetup()
    wiringpi.pinMode(pin, 1)  # Set pin to OUTPUT mode
    wiringpi.softToneCreate(pin)  # Create a soft tone on the pin

def run_metronome(bpm, buzzer_pin=0):
    """
    Run the metronome based on BPM value.
    :param bpm: Beats per minute
    :param buzzer_pin: Pin number for the buzzer
    """
    if bpm is None:
        return
    
    print(f"Buzzer ON with {bpm} BPM")
    interval = 60.0 / bpm  # Calculate the interval time in seconds

    # Sound the buzzer
    wiringpi.softToneWrite(buzzer_pin, 1000)  # Buzzer ON with 1000 Hz tone
    time.sleep(0.1)  # Buzzer ON for 100 milliseconds
    wiringpi.softToneWrite(buzzer_pin, 0)  # Buzzer OFF
    time.sleep(interval - 0.1)  # Wait for the rest of the interval

    print(f"interval: {interval:.2f} sec")

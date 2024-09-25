# main.py
from uart import setup_uart, read_bpm
from metronome import setup_buzzer, run_metronome

def main():
    uart = setup_uart()  # Setup UART
    buzzer_pin = 0       # Define the pin for the buzzer

    setup_buzzer(buzzer_pin)  # Setup the buzzer

    while True:
        bpm = read_bpm(uart)  # Read BPM from UART
        run_metronome(bpm, buzzer_pin)  # Run the metronome with the given BPM

if __name__ == "__main__":
    main()

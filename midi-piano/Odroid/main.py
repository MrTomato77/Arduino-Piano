# main.py
from uart import setup_uart, read_bpm
from metronome import setup_buzzer, run_metronome

def main():
    uart = setup_uart()
    buzzer_pin = 0

    setup_buzzer(buzzer_pin)

    while True:
        bpm = read_bpm(uart)
        run_metronome(bpm, buzzer_pin)

if __name__ == "__main__":
    main()

from uart import setup_uart, read_bpm
from metronome import setup_buzzer, run_metronome

def main():
    setup_buzzer(buzzer_pin)
    uart = setup_uart()
    buzzer_pin = 0
    prev_bpm = None

    while True:
        bpm = read_bpm(uart)
        if bpm != prev_bpm:
            print(f"BPM changed from {prev_bpm} to {bpm}. Restarting metronome.")
            prev_bpm = bpm
            run_metronome(bpm, buzzer_pin)
        else:
            run_metronome(bpm, buzzer_pin)

if __name__ == "__main__":
    main()

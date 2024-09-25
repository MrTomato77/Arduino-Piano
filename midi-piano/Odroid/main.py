import threading
import time
from uart import setup_uart, read_bpm
from metronome import setup_buzzer, run_metronome

def bpm_listener(uart, bpm_change_event, bpm_holder):
    while True:
        bpm = read_bpm(uart)
        if bpm is not None and bpm != bpm_holder['bpm']:
            bpm_holder['bpm'] = bpm 
            bpm_change_event.set()  #interrupt (set event)
        time.sleep(0.1)

def main():
    uart = setup_uart()
    buzzer_pin = 0
    setup_buzzer(buzzer_pin)

    bpm_holder = {'bpm': None}  # เก็บค่า bpm ปัจจุบันในรูปแบบ dictionary
    bpm_change_event = threading.Event()  # สร้าง event สำหรับแจ้งการเปลี่ยนแปลง bpm

    # เริ่ม thread สำหรับการฟังค่า bpm
    listener_thread = threading.Thread(target=bpm_listener, args=(uart, bpm_change_event, bpm_holder))
    listener_thread.daemon = True  # ตั้ง thread นี้ให้ทำงานแบบ background
    listener_thread.start()

    prev_bpm = None

    while True:
        # รอให้มีการเปลี่ยนแปลง bpm
        bpm_change_event.wait()  # หยุดรอจนกว่าจะมีการ set event
        bpm = bpm_holder['bpm']

        if bpm != prev_bpm:
            print(f"BPM changed to {bpm}. Restarting metronome.")
            prev_bpm = bpm
            run_metronome(bpm, buzzer_pin)

        bpm_change_event.clear()  # รีเซ็ต event เพื่อรอการเปลี่ยนแปลงครั้งต่อไป

if __name__ == "__main__":
    main()

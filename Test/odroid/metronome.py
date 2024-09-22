#sudo apt-get install python3-rpi.gpio
#python3 metronome.py

import RPi.GPIO as GPIO
import time

# ตั้งค่า GPIO
buzzer_pin = 18
GPIO.setmode(GPIO.BCM)
GPIO.setup(buzzer_pin, GPIO.OUT)

# ฟังก์ชัน metronome
def metronome(bpm):
    interval = 60 / bpm  # คำนวณเวลาสำหรับแต่ละบีต
    while True:
        GPIO.output(buzzer_pin, GPIO.HIGH)  # เปิด buzzer
        time.sleep(0.1)  # เสียง buzzer ดัง
        GPIO.output(buzzer_pin, GPIO.LOW)   # ปิด buzzer
        time.sleep(interval - 0.1)  # รอเวลาที่เหลือ

try:
    bpm = 120  # กำหนด BPM (beats per minute)
    metronome(bpm)
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()

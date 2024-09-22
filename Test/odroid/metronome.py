#pip install RPi.GPIO


import RPi.GPIO as GPIO
import time

# กำหนดหมายเลข pin ที่เชื่อมต่อกับ buzzer
BUZZER_PIN = 18

# ตั้งค่า pin เป็นโหมด output
GPIO.setmode(GPIO.BOARD)  # หรือใช้ GPIO.BCM ตามการเรียกหมายเลข pin
GPIO.setup(BUZZER_PIN, GPIO.OUT)

# Function สำหรับทำให้ buzzer ส่งเสียง
def buzz(frequency, duration):
    if frequency == 0:  # หยุดเสียง
        GPIO.output(BUZZER_PIN, GPIO.LOW)
        time.sleep(duration)
        return
    
    period = 1.0 / frequency
    delay = period / 2  # สลับ high และ low ครึ่งหนึ่งของ period

    cycles = int(duration * frequency)  # จำนวนรอบของคลื่นเสียง
    for _ in range(cycles):
        GPIO.output(BUZZER_PIN, GPIO.HIGH)  # ส่งสัญญาณ high ไปที่ buzzer
        time.sleep(delay)
        GPIO.output(BUZZER_PIN, GPIO.LOW)   # ส่งสัญญาณ low ไปที่ buzzer
        time.sleep(delay)

try:
    # ทดสอบส่งเสียงที่ 1000 Hz นาน 2 วินาที
    buzz(1000, 2)

finally:
    # ทำความสะอาด GPIO
    GPIO.cleanup()

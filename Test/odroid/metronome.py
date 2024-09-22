import sys
from time import sleep
import odroid_wiringpi as wpi

# กำหนดหมายเลขขา GPIO สำหรับควบคุม buzzer
BUZZER_PIN = 18  # เปลี่ยนเป็นหมายเลข GPIO ที่ต่อกับ buzzer ของคุณ

# ตั้งค่า WiringPi
wpi.wiringPiSetupGpio()  # ใช้หมายเลข GPIO แบบ BCM
wpi.pinMode(BUZZER_PIN, wpi.OUTPUT)  # ตั้งขาเป็นโหมด output

# ลูปเปิดและปิด buzzer เป็นเวลา 10 ครั้ง
for _ in range(10):
    # เปิดเสียง buzzer
    wpi.digitalWrite(BUZZER_PIN, wpi.HIGH)
    print("Buzzer ON")
    
    # รอ 1 วินาที
    sleep(1)
    
    # ปิดเสียง buzzer
    wpi.digitalWrite(BUZZER_PIN, wpi.LOW)
    print("Buzzer OFF")
    
    # รอ 1 วินาที
    sleep(1)

print("Program has ended")

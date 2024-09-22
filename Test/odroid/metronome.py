import odroid_wiringpi as wpi
import time

# ตั้งค่า
PIN = 18  # เปลี่ยนหมายเลข GPIO ให้ถูกต้อง

# เริ่มต้น wiringPi โดยใช้หมายเลขขาแบบ BCM
wpi.wiringPiSetupGpio()

# ตั้งขาเป็นโหมด output
wpi.pinMode(PIN, wpi.OUTPUT)

# เปิดและปิดขา GPIO 5 ครั้ง
for i in range(5):
    wpi.digitalWrite(PIN, wpi.HIGH)  # ตั้งขา HIGH
    time.sleep(1)
    wpi.digitalWrite(PIN, wpi.LOW)   # ตั้งขา LOW
    time.sleep(1)

print("การทดสอบเสร็จสิ้น")

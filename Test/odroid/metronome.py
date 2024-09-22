import odroid_wiringpi as wpi
import time

# กำหนดหมายเลขขา GPIO สำหรับลำโพง
SPEAKER_PIN = 18  # เปลี่ยนเป็นหมายเลข GPIO ที่ต่อกับลำโพงของคุณ

# ตั้งค่า WiringPi
wpi.wiringPiSetupGpio()  # ใช้หมายเลข GPIO แบบ BCM

# สร้าง softTone
wpi.softToneCreate(SPEAKER_PIN)

# ตัวอย่างความถี่ (ใน Hz)
frequencies = [440, 523, 587, 659, 698, 784, 880]  # A4, C5, D5, E5, F5, G5, A5

# เล่นเสียงแต่ละความถี่
try:
    for freq in frequencies:
        print(f"Playing frequency: {freq} Hz")
        wpi.softToneWrite(SPEAKER_PIN, freq)  # เล่นความถี่
        time.sleep(1)  # รอ 1 วินาทีก่อนเปลี่ยนไปยังความถี่ถัดไป

    # หยุดเสียง
    wpi.softToneWrite(SPEAKER_PIN, 0)  # หยุดเล่นเสียง
    print("Sound stopped.")
except Exception as e:
    print(f"Error: {e}")

print("Program has ended.")

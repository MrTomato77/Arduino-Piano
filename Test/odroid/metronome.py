import time
import odroid_wiringpi as wiringpi

# ตั้งค่า WiringPi
wiringpi.wiringPiSetup()

# ตั้งค่า buzzer pin (ใช้ softTone)
buzzer_pin = 0  # GPIO 0

# สร้าง softTone บน pin ที่กำหนด
wiringpi.softToneCreate(buzzer_pin)

# ตั้งค่า BPM สำหรับ metronome
bpm = 120  # จังหวะ 120 BPM
interval = 60.0 / bpm  # คำนวณเวลาระหว่างจังหวะ (วินาทีต่อจังหวะ)

# ความถี่ของเสียง metronome (ปรับตามความต้องการ)
frequency = 1000  # ความถี่เสียง (1000 Hz)

# เริ่มการทำงาน metronome
while True:
    # เปิด buzzer ด้วยความถี่ที่กำหนด
    wiringpi.softToneWrite(buzzer_pin, frequency)
    print("Beep!")
    
    # รอ 0.1 วินาทีเพื่อให้ buzzer ส่งเสียง
    time.sleep(0.1)

    # ปิดเสียง (softToneWrite(0) จะหยุดเสียง)
    wiringpi.softToneWrite(buzzer_pin, 0)

    # รอระยะเวลาระหว่างจังหวะตาม BPM ที่กำหนด
    time.sleep(interval - 0.1)

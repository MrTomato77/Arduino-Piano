import odroid_wiringpi as wpi

# ตั้งค่า GPIO pin ตาม WiringPi
wpi.wiringPiSetup()

# ตั้งค่า pin 1 (Physical Pin 12 / GPIO 492) เป็น input สำหรับปุ่มกด
wpi.pinMode(1, 0)  # 0 หมายถึง input

while True:
    button_state = wpi.digitalRead(1)  # อ่านค่าจากปุ่ม
    if button_state == 0:  # ถ้าปุ่มถูกกด (ปุ่มกดมีการเชื่อมต่อแบบ pull-down)
        print("button_ok")

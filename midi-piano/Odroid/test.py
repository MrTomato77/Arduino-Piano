from luma.core.interface.serial import i2c
from luma.lcd import CharLCD
import time

serial = i2c(port=1, address=0x27)
lcd = CharLCD(serial, width=16, height=2)

lcd.clear()
lcd.text('hola', 0, 0)

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass
finally:
    lcd.clear()

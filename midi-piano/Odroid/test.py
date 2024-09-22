import time

from luma.core.interface.serial import pcf8574
from luma.lcd.device import hd44780

interface = pcf8574(address=0x27, backlight_enabled=True)
device = hd44780(interface, width=16, height=2)
device.text = "Hello world"

time.sleep(20000)
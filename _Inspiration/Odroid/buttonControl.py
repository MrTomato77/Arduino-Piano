import odroid_wiringpi as wpi
import time

wpi.wiringPiSetup()

class DebouncedButton():
    def __init__(self, pin):
        self.pin = pin
        self.last_press = 0
        wpi.pinMode(pin, 0)
    
    def is_pressed(self):
        if not wpi.digitalRead(self.pin) and time.time() - self.last_press > 0.7:
            self.last_press = time.time()
            return True
        else:
            return False

class LED():
    def __init__(self, pin):
        self.pin = pin
        wpi.pinMode(self.pin, 1)
    
    def on(self):
        wpi.digitalWrite(self.pin, 1)
    
    def off(self):
        wpi.digitalWrite(self.pin, 0)

from lcd_i2c import CharLCD
import time

# Create an instance of the CharLCD class
lcd = CharLCD(i2c_addr=0x27, cols=16, rows=2)  # Adjust I2C address if needed

# Clear the display
lcd.clear()

# Display "hola"
lcd.message('hola')

# Keep the program running
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass
finally:
    lcd.clear()

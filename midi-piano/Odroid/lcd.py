import smbus2
import time
from RPLCD.i2c import CharLCD

# Define I2C addresses
I2C_ARDUINO_ADDRESS = 0x08  # Arduino I2C address

# Initialize I2C (smbus) - Bus 1 is for ODROID C4
bus = smbus2.SMBus(1)

# Initialize the I2C LCD
lcd = CharLCD('PCF8574', 0x23, bus=1, cols=16, rows=2)

def read_arduino():
    """Read data from the Arduino over I2C"""
    try:
        # Arduino sends 3 bytes: BPM, Octave, Note
        data = bus.read_i2c_block_data(I2C_ARDUINO_ADDRESS, 0, 3)
        bpm = data[0]      # First byte: BPM
        octave = data[1]   # Second byte: Octave
        note = data[2]     # Third byte: Note
        return bpm, octave, note
    except Exception as e:
        print(f"Error reading from Arduino: {e}")
        return None, None, None

def update_lcd(bpm, octave, note):
    """Update the LCD display with BPM, Octave, and Note"""
    lcd.clear()  # Clear the display before writing
    lcd.write_string(f"BPM: {bpm}\nOctave: {octave} Note: {note}")

def main():
    # Initialize the LCD
    lcd.clear()
    
    while True:
        # Read values from Arduino
        bpm, octave, note = read_arduino()
        if bpm is not None and octave is not None and note is not None:
            print(f"Received - BPM: {bpm}, Octave: {octave}, Note: {note}")
            # Update the LCD
            update_lcd(bpm, octave, note)
        else:
            print("No valid data received.")
        
        time.sleep(1)  # Check for updates every second

if __name__ == "__main__":
    main()

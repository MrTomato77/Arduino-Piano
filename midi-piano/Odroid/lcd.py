import time
import smbus2
import serial

# Set up I2C communication with the LCD
I2C_LCD_ADDR = 0x23  # Address of the I2C LCD
LCD_WIDTH = 16    # Maximum characters per line

# LCD commands
LCD_CHR = 1  # Mode - Sending data
LCD_CMD = 0  # Mode - Sending command

LCD_LINE_1 = 0x80  # LCD RAM address for the 1st line
LCD_LINE_2 = 0xC0  # LCD RAM address for the 2nd line

LCD_BACKLIGHT = 0x08  # On
ENABLE = 0b00000100  # Enable bit

# Timing constants
E_PULSE = 0.0005
E_DELAY = 0.0005

# Initialize Serial communication with Arduino
bus = smbus2.SMBus(1)  # Initialize I2C bus (1 indicates the correct bus for ODROID)
port = '/dev/ttyS1'  # Replace with the correct port
baudrate = 115200
uno = serial.Serial(port, baudrate, timeout=1)

def lcd_init():
    """Initialize LCD display."""
    lcd_byte(0x33, LCD_CMD)  # 110011 Initialize
    lcd_byte(0x32, LCD_CMD)  # 110010 Initialize
    lcd_byte(0x06, LCD_CMD)  # Cursor move direction
    lcd_byte(0x0C, LCD_CMD)  # Turn cursor off
    lcd_byte(0x28, LCD_CMD)  # 2 line display
    lcd_byte(0x01, LCD_CMD)  # Clear display
    time.sleep(E_DELAY)

def lcd_byte(bits, mode):
    """Send byte to data pins."""
    bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT

    bus.write_byte(I2C_LCD_ADDR, bits_high)
    lcd_toggle_enable(bits_high)

    bus.write_byte(I2C_LCD_ADDR, bits_low)
    lcd_toggle_enable(bits_low)

def lcd_toggle_enable(bits):
    """Toggle enable pin."""
    time.sleep(E_DELAY)
    bus.write_byte(I2C_LCD_ADDR, (bits | ENABLE))
    time.sleep(E_PULSE)
    bus.write_byte(I2C_LCD_ADDR, (bits & ~ENABLE))
    time.sleep(E_DELAY)

def lcd_string(message, line):
    """Send string to display."""
    message = message.ljust(16, " ")  # Pad string with spaces if shorter than 16 characters
    lcd_byte(line, LCD_CMD)

    for i in range(16):
        lcd_byte(ord(message[i]), LCD_CHR)

def receive_data_from_arduino():
    """Read BPM, Octave, and Note from Arduino."""
    try:
        # Wait for serial data from Arduino
        data = uno.readline().decode('utf-8').strip()
        if data:
            # Split data assuming it comes in "BPM,Octave,Note" format
            bpm, octave, note = data.split(',')
            return int(bpm), int(octave), note
    except Exception as e:
        print(f"Error reading data: {e}")
    return None, None, None

def display_data_on_lcd(bpm, octave, note):
    """Display BPM, Octave, and Note on the LCD."""
    lcd_string(f"BPM: {bpm}", LCD_LINE_1)
    lcd_string(f"Oct: {octave} Note: {note}", LCD_LINE_2)

def main():
    """Main loop to handle data reading and LCD output."""
    lcd_init()  # Initialize the LCD

    while True:
        # Receive data from Arduino
        bpm, octave, note = receive_data_from_arduino()

        if bpm is not None and octave is not None and note:
            print(f"Received -> BPM: {bpm}, Octave: {octave}, Note: {note}")
            display_data_on_lcd(bpm, octave, note)
        else:
            print("Waiting for data...")
        
        time.sleep(1)  # Polling delay

if __name__ == "__main__":
    main()

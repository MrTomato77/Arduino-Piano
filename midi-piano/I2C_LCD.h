#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the I2C LCD address and the size of the LCD (16x2 or 20x4 etc.)
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Create an instance of the LCD class
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Function to initialize the LCD
void setupLCD() {
  lcd.begin();
  lcd.backlight();  // Turn on the backlight
}

// Function to update the octave display on the LCD
void displayOctave(int octave) {
  lcd.setCursor(0, 0); // Set the cursor to the second row
  lcd.print("Octave: ");
  lcd.print(octave-1);
  lcd.print(",");    // Clear any trailing characters from previous updates
  lcd.print(octave);
}

void displayBPM(int bpm) {
  lcd.setCursor(0, 1); // Set the cursor to the second row
  lcd.print("BPM: ");
  lcd.print(bpm);
  lcd.print("   ");    // Clear any trailing characters from previous updates
}

#endif // I2C_LCD_H
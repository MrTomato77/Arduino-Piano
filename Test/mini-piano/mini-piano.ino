#include <Wire.h>
#include "pitches.h"

#define SPEAKER_PIN 8
#define PCF8574_ADDRESS 0x20

const int buttonTones[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};
const int numTones = sizeof(buttonTones) / sizeof(buttonTones[0]);

void setup() {
  Wire.begin();  // Initialize I2C
  pinMode(SPEAKER_PIN, OUTPUT);
  
  // Set all PCF8574 pins as inputs with pull-up (PCF8574 pins default to HIGH)
  Wire.beginTransmission(PCF8574_ADDRESS);
  Wire.write(0xFF); // Set all pins HIGH to enable internal pull-ups
  Wire.endTransmission();
}

void loop() {
  int pitch = 0;

  // Read the button states from PCF8574
  Wire.requestFrom(PCF8574_ADDRESS, 1);
  if (Wire.available()) {
    uint8_t buttonStates = Wire.read(); // Read the byte from PCF8574

    for (uint8_t i = 0; i < numTones; i++) {
      // Check if the button is pressed (LOW state)
      if (!(buttonStates & (1 << i))) {
        pitch = buttonTones[i];
        break;  // Play the first detected tone
      }
    }
  }

  if (pitch) {
    tone(SPEAKER_PIN, pitch);
  } else {
    noTone(SPEAKER_PIN);
  }
}

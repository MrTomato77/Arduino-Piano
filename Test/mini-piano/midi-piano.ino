#include <Wire.h>
#include "pitches.h"

#define SPEAKER_PIN 8
#define PCF8574_ADDRESS 0x20
#define DEBOUNCE_DELAY 10  // Debounce delay in milliseconds

const int buttonTones[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};

const char* buttonNames[] = {
  "C4", "D4", "E4", "F4", 
  "G4", "A4", "B4", "C5"
};

const int numTones = sizeof(buttonTones) / sizeof(buttonTones[0]);
uint8_t lastButtonStates = 0xFF;  // Keep track of previous button states
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(38400);
  Wire.begin();  // Initialize I2C
  pinMode(SPEAKER_PIN, OUTPUT);

  // Set all PCF8574 pins as inputs with pull-up
  Wire.beginTransmission(PCF8574_ADDRESS);
  Wire.write(0xFF); // Set all pins HIGH to enable internal pull-ups
  Wire.endTransmission();
}

void loop() {
  playPiano();
}

void playPiano() {
  int pitch = readButtonStates();
  
  if (pitch) {
    tone(SPEAKER_PIN, pitch);
  } else {
    noTone(SPEAKER_PIN);
  }
}

int readButtonStates() {
  unsigned long currentTime = millis();
  int pitch = 0;

  // Read the button states from PCF8574
  Wire.requestFrom(PCF8574_ADDRESS, 1);
  if (Wire.available()) {
    uint8_t currentButtonStates = Wire.read(); // Read the byte from PCF8574
    if (debounce(currentButtonStates, currentTime)) {
      pitch = getPressedTone(lastButtonStates); // Get the tone for the pressed button
    }
  }
  return pitch;
}

int getPressedTone(uint8_t buttonStates) {
  for (uint8_t i = 0; i < numTones; i++) {
    // Check if the button is pressed (LOW state)
    if (!(buttonStates & (1 << i))) {
      Serial.println(buttonNames[i]);  // Print the corresponding key name
      return buttonTones[i];  // Return the tone for the first detected button press
    }
  }
  return 0; // No button pressed
}

bool debounce(uint8_t currentButtonStates, unsigned long currentTime) {
  if (currentButtonStates != lastButtonStates) {
    lastDebounceTime = currentTime;
    lastButtonStates = currentButtonStates;
  }
  return (currentTime - lastDebounceTime) > DEBOUNCE_DELAY;
}

#include <Wire.h>
#include "pitches.h"
#include "metronome.h"

#define SPEAKER_PIN 8
#define PCF8574_ADDRESS 0x20
#define PCF8574_ADDRESS2 0x21
#define DEBOUNCE_DELAY 10  // Debounce delay in milliseconds

const int buttonTones[] = {
  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4,
  NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4,
  NOTE_AS4, NOTE_B4
};

const char* buttonNames[] = {
  "C4", "Db4", "D4", "Eb4", "E4",
  "F4", "F#4", "G4", "Ab4", "A4",
  "Bb4", "B4"
};

const int numTones = sizeof(buttonTones) / sizeof(buttonTones[0]);
uint8_t lastButtonStates1 = 0xFF;  // Keep track of previous button states for PCF8574_1
uint8_t lastButtonStates2 = 0xFF;  // Keep track of previous button states for PCF8574_2

void setup() {
  Serial.begin(38400);
  Wire.begin();  // Initialize I2C
  pinMode(SPEAKER_PIN, OUTPUT);

  // Set all PCF8574 pins as inputs with pull-up
  Wire.beginTransmission(PCF8574_ADDRESS);
  Wire.write(0xFF); // Set all pins HIGH to enable internal pull-ups
  Wire.endTransmission();

  Wire.beginTransmission(PCF8574_ADDRESS2);
  Wire.write(0xFF); // Set all pins HIGH to enable internal pull-ups
  Wire.endTransmission();

  // Initialize metronome
  setupMetronome();
}

void loop() {
  playPiano();
  playMetronome();  // Add metronome functionality
  adjustBPM();      // Adjust BPM based on button presses
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

  // Read the button states from PCF8574_1
  Wire.requestFrom(PCF8574_ADDRESS, 1);
  if (Wire.available()) {
    uint8_t currentButtonStates1 = Wire.read(); // Read the byte from PCF8574_1
    if (debounce(currentButtonStates1, lastButtonStates1, currentTime)) {
      pitch = getPressedTone(currentButtonStates1, 0); // Get the tone for the pressed button from PCF8574_1
    }
  }

  // Read the button states from PCF8574_2
  Wire.requestFrom(PCF8574_ADDRESS2, 1);
  if (Wire.available()) {
    uint8_t currentButtonStates2 = Wire.read(); // Read the byte from PCF8574_2
    if (debounce(currentButtonStates2, lastButtonStates2, currentTime)) {
      pitch = getPressedTone(currentButtonStates2, 8); // Get the tone for the pressed button from PCF8574_2
    }
  }
  return pitch;
}

int getPressedTone(uint8_t buttonStates, int offset) {
  for (uint8_t i = 0; i < 8; i++) {
    // Check if the button is pressed (LOW state)
    if (!(buttonStates & (1 << i))) {
      Serial.print("Button States: ");
      Serial.println(buttonStates, BIN); // Print the binary value of buttonStates
      Serial.print("Pressed: ");
      Serial.println(buttonNames[i + offset]);  // Print the corresponding key name
      return buttonTones[i + offset];  // Return the tone for the detected button press
    }
  }
  return 0; // No button pressed
}

bool debounce(uint8_t currentButtonStates, uint8_t &lastButtonStates, unsigned long currentTime) {
  if (currentButtonStates != lastButtonStates) {
    lastDebounceTime = currentTime;
    lastButtonStates = currentButtonStates;
  }
  return (currentTime - lastDebounceTime) > DEBOUNCE_DELAY;
}

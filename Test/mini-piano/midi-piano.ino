#include <Wire.h>
#include "pitches.h"

#define SPEAKER_PIN 8
#define PCF8574_ADDRESS 0x20
#define DEBOUNCE_DELAY 10  // Debounce delay in milliseconds

#define METRONOME_PIN 7  // New pin for metronome sound
#define BPM_INCREMENT 10
#define INITIAL_BPM 120
#define METRONOME_TICK_DURATION 100  // Duration of the tick sound in milliseconds
#define METRONOME_PITCH 300

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

unsigned long metronomeInterval;  // Interval between beats
unsigned long lastMetronomeTime = 0;
int currentBPM = INITIAL_BPM;  // Current BPM

// Button pins for BPM adjustment
const int BPM_UP_PIN = 6;
const int BPM_DOWN_PIN = 5;

// Store previous button states for edge detection
bool lastBPMUpState = HIGH;
bool lastBPMDownState = HIGH;

void setup() {
  Serial.begin(38400);
  Wire.begin();  // Initialize I2C
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(METRONOME_PIN, OUTPUT);  // Set the metronome pin as output

  // Set BPM adjustment pins as inputs with pull-up resistors
  pinMode(BPM_UP_PIN, INPUT_PULLUP);
  pinMode(BPM_DOWN_PIN, INPUT_PULLUP);

  // Set all PCF8574 pins as inputs with pull-up
  Wire.beginTransmission(PCF8574_ADDRESS);
  Wire.write(0xFF); // Set all pins HIGH to enable internal pull-ups
  Wire.endTransmission();

  // Calculate the metronome interval
  metronomeInterval = 60000 / currentBPM;
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

void playMetronome() {
  unsigned long currentTime = millis();
  
  // Check if it's time for a new beat
  if (currentTime - lastMetronomeTime >= metronomeInterval) {
    // Play the metronome tick with a lower frequency
    tone(METRONOME_PIN, 300, METRONOME_TICK_DURATION);  // Example lower frequency (300 Hz) and duration
    lastMetronomeTime = currentTime;
  }
}

void adjustBPM() {
  // Read the current button states
  bool currentBPMUpState = digitalRead(BPM_UP_PIN);
  bool currentBPMDownState = digitalRead(BPM_DOWN_PIN);
  unsigned long currentTime = millis();
  
  // Check for BPM up button falling edge
  if (lastBPMUpState == HIGH && currentBPMUpState == LOW) {
    if (currentTime - lastDebounceTime > DEBOUNCE_DELAY) {
      currentBPM += BPM_INCREMENT;
      if (currentBPM > 500) currentBPM = 500;  // Set maximum BPM limit
      lastDebounceTime = currentTime;
      updateMetronomeInterval();
    }
  }

  // Check for BPM down button falling edge
  if (lastBPMDownState == HIGH && currentBPMDownState == LOW) {
    if (currentTime - lastDebounceTime > DEBOUNCE_DELAY) {
      currentBPM -= BPM_INCREMENT;
      if (currentBPM < 10) currentBPM = 10;  // Set minimum BPM limit
      lastDebounceTime = currentTime;
      updateMetronomeInterval();
    }
  }

  // Update the previous button states
  lastBPMUpState = currentBPMUpState;
  lastBPMDownState = currentBPMDownState;
}

void updateMetronomeInterval() {
  metronomeInterval = 60000 / currentBPM;
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
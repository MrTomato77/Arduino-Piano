#include <Arduino.h>

const int METRONOME_PIN = 7;
const int BPM_UP_PIN = 6;
const int BPM_DOWN_PIN = 5;
const int INITIAL_BPM = 120;
const int BPM_INCREMENT = 1;
const int METRONOME_TICK_DURATION = 100;
const int METRONOME_FREQUENCY = 100;

static unsigned long metronomeInterval;  // Interval between beats
static unsigned long lastMetronomeTime = 0;
static int currentBPM = INITIAL_BPM;  // Current BPM

static bool lastBPMUpState = HIGH;
static bool lastBPMDownState = HIGH;
static unsigned long lastDebounceTime = 0;
static const unsigned long DEBOUNCE_DELAY = 50; // Adjust as needed

void updateMetronomeInterval() {
  metronomeInterval = 60000 / currentBPM;
}

void setupMetronome() {
  pinMode(METRONOME_PIN, OUTPUT);
  pinMode(BPM_UP_PIN, INPUT_PULLUP);
  pinMode(BPM_DOWN_PIN, INPUT_PULLUP);
  updateMetronomeInterval();
}

void playMetronome() {
  unsigned long currentTime = millis();
  
  // Check if it's time for a new beat
  if (currentTime - lastMetronomeTime >= metronomeInterval) {
    // Play the metronome tick with a lower frequency
    tone(METRONOME_PIN, METRONOME_FREQUENCY, METRONOME_TICK_DURATION);  // Example lower frequency (300 Hz) and duration
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
      if (currentBPM > 240) currentBPM = 240;  // Set maximum BPM limit
      lastDebounceTime = currentTime;
      updateMetronomeInterval();
    }
  }

  // Check for BPM down button falling edge
  if (lastBPMDownState == HIGH && currentBPMDownState == LOW) {
    if (currentTime - lastDebounceTime > DEBOUNCE_DELAY) {
      currentBPM -= BPM_INCREMENT;
      if (currentBPM < 30) currentBPM = 30;  // Set minimum BPM limit
      lastDebounceTime = currentTime;
      updateMetronomeInterval();
    }
  }

  // Update the previous button states
  lastBPMUpState = currentBPMUpState;
  lastBPMDownState = currentBPMDownState;
}

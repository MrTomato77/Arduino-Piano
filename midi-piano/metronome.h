#ifndef METRONOME_H
#define METRONOME_H

#include <Arduino.h> // Include Arduino library for Serial functions

const int INITIAL_BPM = 120;
const int BPM_UP_PIN = 6;
const int BPM_DOWN_PIN = 5;
const int BPM_INCREMENT = 5;  // Amount to increase/decrease BPM
const unsigned long DEBOUNCE_DELAY = 50;  // Debounce delay in milliseconds

int currentBPM = INITIAL_BPM; // Current BPM value
int lastBPMUpState = HIGH; // Previous state of BPM up button
int lastBPMDownState = HIGH; // Previous state of BPM down button
unsigned long lastDebounceTime = 0; // Last time the button was pressed
unsigned long metronomeInterval; // Interval between beats

void updateMetronomeInterval() {
  metronomeInterval = 60000 / currentBPM; // Calculate interval in milliseconds
}

void setupMetronome() {
  pinMode(BPM_UP_PIN, INPUT_PULLUP); // Set BPM up button as input with pull-up resistor
  pinMode(BPM_DOWN_PIN, INPUT_PULLUP); // Set BPM down button as input with pull-up resistor
  updateMetronomeInterval(); // Initialize metronome interval
}

void printCurrentBPM() {
  Serial.print("Current BPM: "); // Print label
  Serial.println(currentBPM);   // Print current BPM value
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
      printCurrentBPM(); // Print the current BPM when adjusted
    }
  }

  // Check for BPM down button falling edge
  if (lastBPMDownState == HIGH && currentBPMDownState == LOW) {
    if (currentTime - lastDebounceTime > DEBOUNCE_DELAY) {
      currentBPM -= BPM_INCREMENT;
      if (currentBPM < 10) currentBPM = 10;  // Set minimum BPM limit
      lastDebounceTime = currentTime;
      updateMetronomeInterval();
      printCurrentBPM(); // Print the current BPM when adjusted
    }
  }

  // Update the previous button states
  lastBPMUpState = currentBPMUpState;
  lastBPMDownState = currentBPMDownState;
}



#endif // METRONOME_H

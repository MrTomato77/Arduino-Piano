#ifndef OCTAVE_H
#define OCTAVE_H

#include <Arduino.h>
#include "I2C_LCD.h"

// Define pins for buttons
const int buttonIncreasePin = 16;  // Pin for increase button
const int buttonDecreasePin = 17;  // Pin for decrease button

// Define octave
const int minOctave = 0;
const int maxOctave = 5;
int currentOctave = 3;
unsigned long lastIncreaseTime = 0;
unsigned long lastDecreaseTime = 0;
const unsigned long debounceOctave = 10;

void setupOctaveButtons() {
    pinMode(buttonIncreasePin, INPUT_PULLUP);
    pinMode(buttonDecreasePin, INPUT_PULLUP);
}

int getCurrentOctave() {
    return currentOctave;
}

void increaseOctave() {
    if (currentOctave < maxOctave) {
        currentOctave++;
        displayOctave(getCurrentOctave());
    }
}

void decreaseOctave() {
    if (currentOctave > minOctave) {
        currentOctave--;
    } else {
        currentOctave = minOctave;
    }
    displayOctave(getCurrentOctave());
}

void checkOctaveButtons() {
    unsigned long currentMillis = millis();
    if (digitalRead(buttonIncreasePin) == LOW) {
        if (currentMillis - lastIncreaseTime > debounceOctave) {
            increaseOctave();
            lastIncreaseTime = currentMillis;
        }
    }
    if (digitalRead(buttonDecreasePin) == LOW) {
        if (currentMillis - lastDecreaseTime > debounceOctave) {
            decreaseOctave();
            lastDecreaseTime = currentMillis;
        }
    }
}

#endif

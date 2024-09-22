#ifndef OCTAVE_H
#define OCTAVE_H

#include <Arduino.h>

// Define pins for buttons
const int buttonIncreasePin = 3;  // Pin for increase button
const int buttonDecreasePin = 4;  // Pin for decrease button

// Define octave range limits
const int minOctave = 1;
const int maxOctave = 8;

// Variable to store the current octave
int currentOctave = 0;

// Function to initialize the buttons
void setupOctaveButtons() {
    pinMode(buttonIncreasePin, INPUT_PULLUP);
    pinMode(buttonDecreasePin, INPUT_PULLUP);
}

// Function to increase the octave
void increaseOctave() {
    if (currentOctave < maxOctave) {
        currentOctave++;
    }
}

// Function to decrease the octave
void decreaseOctave() {
    if (currentOctave > minOctave) {
        currentOctave--;
    }
}

// Function to check for button presses
void checkOctaveButtons() {
    // Check if the increase button is pressed
    if (digitalRead(buttonIncreasePin) == LOW) {
        increaseOctave();
        delay(200);  // Debounce delay
    }

    // Check if the decrease button is pressed
    if (digitalRead(buttonDecreasePin) == LOW) {
        decreaseOctave();
        delay(200);  // Debounce delay
    }
}

// Function to get the current octave value
int getCurrentOctave() {
    return currentOctave;
}

#endif

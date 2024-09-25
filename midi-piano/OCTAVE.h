#ifndef OCTAVE_H
#define OCTAVE_H

#include <Arduino.h>
#include "I2C_LCD.h"

// Define pins for buttons
const int buttonIncreasePin = 16;  // Pin for increase button
const int buttonDecreasePin = 17;  // Pin for decrease button

// Define octave range limits
const int minOctave = 1;
const int maxOctave = 5;

// Variable to store the current octave
int currentOctave = 2;

// Function to initialize the buttons
void setupOctaveButtons() {
    pinMode(buttonIncreasePin, INPUT_PULLUP);
    pinMode(buttonDecreasePin, INPUT_PULLUP);
}

// Function to get the current octave value
int getCurrentOctave() {
    return currentOctave;
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

// Function to check for button presses to increase or decrease octave
void checkOctaveButtons() {
    // Check if the increase button is pressed
    if (digitalRead(buttonIncreasePin) == LOW) {
        increaseOctave();            // Increase the octave
        displayOctave(getCurrentOctave());  // Update the LCD display with the new octave
    }

    // Check if the decrease button is pressed
    if (digitalRead(buttonDecreasePin) == LOW) {
        decreaseOctave();            // Decrease the octave
        displayOctave(getCurrentOctave());  // Update the LCD display with the new octave
    }
}

#endif

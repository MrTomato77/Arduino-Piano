#ifndef BPM_H
#define BPM_H

#include <Arduino.h>
#include "I2C_LCD.h"

// Define pins for buttons
const int buttonIncreasePin = 14;  // Pin for increase button
const int buttonDecreasePin = 15;  // Pin for decrease button

// Define BPM range limits
const int minBPM = 1;
const int maxBPM = 5;

// Variable to store the current BPM
int currentBPM = 2;

// Function to initialize the buttons
void setupBPMButtons() {
    pinMode(buttonIncreasePin, INPUT_PULLUP);
    pinMode(buttonDecreasePin, INPUT_PULLUP);
}

// Function to get the current BPM value
int getCurrentBPM() {
    return currentBPM;
}

// Function to increase the BPM
void increaseBPM() {
    if (currentBPM < maxBPM) {
        currentBPM++;
    }
}

// Function to decrease the BPM
void decreaseBPM() {
    if (currentBPM > minBPM) {
        currentBPM--;
    }
}

// Function to check for button presses to increase or decrease BPM
void checkBPMButtons() {
    // Check if the increase button is pressed
    if (digitalRead(buttonIncreasePin) == LOW) {
        increaseBPM();            // Increase the BPM
        displayBPM(getCurrentBPM());  // Update the LCD display with the new BPM
    }

    // Check if the decrease button is pressed
    if (digitalRead(buttonDecreasePin) == LOW) {
        decreaseBPM();            // Decrease the BPM
        displayBPM(getCurrentBPM());  // Update the LCD display with the new BPM
    }
}

#endif

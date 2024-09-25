#ifndef BPM_H
#define BPM_H

#include <Arduino.h>
#include "I2C_LCD.h"

// Define pins for buttons
const int bpmIncPin = 14;  // Pin for increase button
const int bpmDecPin = 15;  // Pin for decrease button

// Define BPM range limits
const int minBPM = 10;
const int maxBPM = 500;

// Variable to store the current BPM
int currentBPM = 120;

// Function to initialize the buttons
void setupBPMButtons() {
    pinMode(bpmIncPin, INPUT_PULLUP);
    pinMode(bpmDecPin, INPUT_PULLUP);
}

// Function to get the current BPM value
int getCurrentBPM() {
    return currentBPM;
}

// Function to increase the BPM
void increaseBPM() {
    if (currentBPM < maxBPM) {
        currentBPM+=5;
        delay(100);
    }
}

// Function to decrease the BPM
void decreaseBPM() {
    if (currentBPM > minBPM) {
        currentBPM-=5;
        delay(100);
    }
}

// Function to check for button presses to increase or decrease BPM
void checkBPMButtons() {
    // Check if the increase button is pressed
    if (digitalRead(bpmIncPin) == LOW) {
        increaseBPM();            // Increase the BPM
        displayBPM(getCurrentBPM());  // Update the LCD display with the new BPM
    }

    // Check if the decrease button is pressed
    if (digitalRead(bpmDecPin) == LOW) {
        decreaseBPM();            // Decrease the BPM
        displayBPM(getCurrentBPM());  // Update the LCD display with the new BPM
    }
}

#endif

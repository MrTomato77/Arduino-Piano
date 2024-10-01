#ifndef BPM_H
#define BPM_H

#include <Arduino.h>
#include "I2C_LCD.h"

// Define pins for buttons
const int bpmIncPin = 14;  // Pin for increase button
const int bpmDecPin = 15;  // Pin for decrease button

// Define BPM
const int minBPM = 10;
const int maxBPM = 300;
int currentBPM = 120;
unsigned long lastBpmIncTime = 0;
unsigned long lastBpmDecTime = 0;
const unsigned long debounceBPM = 100;

void setupBPMButtons() {
    pinMode(bpmIncPin, INPUT_PULLUP);
    pinMode(bpmDecPin, INPUT_PULLUP);
}

int getCurrentBPM() {
    return currentBPM;
}

void increaseBPM() {
    if (currentBPM < maxBPM) {
        currentBPM += 5;
    } else {
        currentBPM = minBPM;
    }
    displayBPM(getCurrentBPM());
}

void decreaseBPM() {
    if (currentBPM > minBPM) {
        currentBPM -= 5;
    } else {
        currentBPM = maxBPM;
    }
    displayBPM(getCurrentBPM());
}

void checkBPMButtons() {
    unsigned long currentMillis = millis();
    if (digitalRead(bpmIncPin) == LOW) {
        if (currentMillis - lastBpmIncTime > debounceBPM) {
            increaseBPM();
            lastBpmIncTime = currentMillis;
        }
    }
    if (digitalRead(bpmDecPin) == LOW) {
        if (currentMillis - lastBpmDecTime > debounceBPM) {
            decreaseBPM();
            lastBpmDecTime = currentMillis;
        }
    }
}

#endif

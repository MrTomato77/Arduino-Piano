#ifndef UART_H
#define UART_H

#include <Wire.h>
#include <SoftwareSerial.h> // Include the SoftwareSerial library
#include "BPM.h"      // Include BPM.h to access currentBPM

// Define RX and TX pins for SoftwareSerial
const int rxPin = 2; // Choose a pin for receiving data
const int txPin = 11; // Choose a pin for transmitting data
SoftwareSerial mySerial(rxPin, txPin); // Create a SoftwareSerial object

void setupUART() {
  mySerial.begin(115200); // Start UART communication at 115200 baud
}

void sendCurrentBPM() {
  mySerial.println(currentBPM); // Send current BPM
  // Serial.print(currentBPM);
}

#endif // UART_H

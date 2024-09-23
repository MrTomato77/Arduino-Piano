#include <Wire.h>

void setup() {
  Wire.begin(); // Start the I2C bus
  Serial.begin(9600); // Start the Serial communication at 9600 baud rate
  while (!Serial); // Wait for Serial to initialize
  Serial.println("I2C Scanner Ready. Scanning...");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++ ) {
    // Start the I2C transmission
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    // Check for device presence
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found.\n");
  } else {
    Serial.print(nDevices);
    Serial.println(" device(s) found.\n");
  }

  delay(5000); // Wait 5 seconds before the next scan
}

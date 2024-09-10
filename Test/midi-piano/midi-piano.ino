#include <PCF8574.h>
#include "pitches.h"

// Pin definitions
#define BUZZER_PIN 8

boolean ButtonWasPressed1[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed2[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed3[] = { false, false, false, false, false, false, false, false };

int octave = 4;

PCF8574 PCF1(0x20);
PCF8574 PCF2(0x21);
PCF8574 PCF3(0x22);

void setupPinMode() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void setup() {
  setupPinMode();
  Serial.begin(115200);
  PCF1.begin();
  PCF2.begin();
  PCF3.begin();
}

void playNoteOnBuzzer(int note) {
  tone(BUZZER_PIN, note);
}

void stopNoteOnBuzzer() {
  noTone(BUZZER_PIN);
}

const char* noteNames[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
void printNoteName(int note) {
  int baseNote = 21;
  int noteIndex = note - baseNote;
  int noteInOctave = noteIndex % 12;
  int noteOctave = (noteIndex / 12);
  if (noteInOctave >= 0 && noteInOctave < 12) {
    Serial.print(noteNames[noteInOctave]);
    Serial.print(noteOctave);
    Serial.println();
  } else {
    Serial.println("Invalid note");
  }
}

void checkKey1(int key) {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  static unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF1.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed1[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed1[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int note = 21 + (12 * octave) + key;  // Adjust for octave and key
    if (ButtonWasPressed1[key]) {
      Serial.print("Playing note: ");
      Serial.print(note);
      Serial.print(" - ");
      printNoteName(note);
      playNoteOnBuzzer(note);
    } else {
      stopNoteOnBuzzer();
    }
  }
}

void checkKey2(int key) {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  static unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF2.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed2[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed2[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int note = 33 + (12 * octave) + key;  // Adjust for octave and key
    if (ButtonWasPressed2[key]) {
      Serial.print("Playing note: ");
      Serial.print(note);
      Serial.print(" - ");
      printNoteName(note);
      playNoteOnBuzzer(note);
    } else {
      stopNoteOnBuzzer();
    }
  }
}

void checkKey3(int key) {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  static unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF3.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed3[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed3[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int note = 45 + (12 * octave) + key;  // Adjust for octave and key
    if (ButtonWasPressed3[key]) {
      Serial.print("Playing note: ");
      Serial.print(note);
      Serial.print(" - ");
      printNoteName(note);
      playNoteOnBuzzer(note);
    } else {
      stopNoteOnBuzzer();
    }
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {
    checkKey1(i);
    checkKey2(i);
    checkKey3(i);
  }
}

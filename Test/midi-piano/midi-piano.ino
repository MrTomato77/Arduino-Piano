#include <PCF8574.h>
#include "pitches.h"
#include "octate.h"

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
  setupOctaveButtons();
  setupPinMode();
  Serial.begin(115200);
  PCF1.begin();
  PCF2.begin();
  PCF3.begin();
}

void playNoteOnBuzzer(int midiNote) {
  Note noteInfo = getNoteInfo(midiNote);
  if (noteInfo.frequency > 0) {
    tone(BUZZER_PIN, noteInfo.frequency);
  } else {
    noTone(BUZZER_PIN);
  }
}
void stopNoteOnBuzzer() {
  noTone(BUZZER_PIN);
}

// Function to print note names based on MIDI note number
void printNoteName(int midiNote) {
  Note noteInfo = getNoteInfo(midiNote);
  if (noteInfo.frequency > 0) {
    Serial.print("Note: ");
    Serial.print(noteInfo.name);
    Serial.print(", Frequency: ");
    Serial.println(noteInfo.frequency);
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
    int midiNote = 1 + (12 * getCurrentOctave()) + key;  // Adjust for octave and key
    if (ButtonWasPressed1[key]) {
      printNoteName(midiNote);
      playNoteOnBuzzer(midiNote);
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
    int midiNote = 9 + (12 * getCurrentOctave()) + key;  // Adjust for octave and key
    if (ButtonWasPressed2[key]) {
      playNoteOnBuzzer(midiNote);
      printNoteName(midiNote);
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
    int midiNote = 17 + (12 * getCurrentOctave()) + key;  // Adjust for octave and key
    if (ButtonWasPressed3[key]) {
      playNoteOnBuzzer(midiNote);
      printNoteName(midiNote);
    } else {
      stopNoteOnBuzzer();
    }
  }
}

void loop() {
  checkOctaveButtons();
  for (int i = 0; i < 8; ++i) {
    checkKey1(i);
    checkKey2(i);
    checkKey3(i);
  }
}

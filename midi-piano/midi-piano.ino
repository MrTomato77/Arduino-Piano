#include <PCF8574.h>
#include <MIDI.h>
#include "buzzerKeys.h"
#include "OCTAVE.h"
#include "BPM.h"
#include "UART.h"

boolean ButtonWasPressed1[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed2[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed3[] = { false, false, false, false, false, false, false, false };

PCF8574 PCF1(0x20);
PCF8574 PCF2(0x21);
PCF8574 PCF3(0x22);

MIDI_CREATE_DEFAULT_INSTANCE();

unsigned long buttonPressTime = 0;  // Time when the button is pressed
unsigned long soundStartTime = 0;   // Time when the sound starts playing

void setup() {
  PCF1.begin();
  PCF2.begin();
  PCF3.begin();

  setupBuzzer();
  setupBPMButtons();
  setupOctaveButtons();
  setupUART();

  setupLCD();
  displayOctave(getCurrentOctave());
  displayBPM(getCurrentBPM());

  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
}

void checkKey1(int key) {
  unsigned long currentTime = micros();
  const unsigned long DebounceTime = 5;
  static unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF1.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed1[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed1[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int buzzerNote = 1 + (12 * getCurrentOctave()) + key;
    int midiNote = 24 + (12 * getCurrentOctave()) + key;;
    if (ButtonWasPressed1[key]) {
      // Capture the time when the button is pressed
      buttonPressTime = micros();
      playNoteOnBuzzer(buzzerNote);
      // printBuzzerNote(buzzerNote);
      soundStartTime = micros();
      // Print the time it took from button press to sound starting
      Serial.print("Time from button press to sound (ms): ");
      Serial.println(soundStartTime - buttonPressTime);
      MIDI.sendNoteOn(midiNote, 127, 1);
    } else {
      stopNoteOnBuzzer();
      MIDI.sendNoteOff(midiNote, 0, 1);
    }
  }
}

void checkKey2(int key) {
  unsigned long currentTime = micros();
  const unsigned long DebounceTime = 5;
  static unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF2.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed2[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed2[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int buzzerNote = 9 + (12 * getCurrentOctave()) + key;
    int midiNote = 32 + (12 * getCurrentOctave()) + key;;
    if (ButtonWasPressed2[key]) {
      // Capture the time when the button is pressed
      buttonPressTime = micros();
      playNoteOnBuzzer(buzzerNote);
      // printBuzzerNote(buzzerNote);
      soundStartTime = micros();
      // Print the time it took from button press to sound starting
      Serial.print("Time from button press to sound (ms): ");
      Serial.println(soundStartTime - buttonPressTime);
      MIDI.sendNoteOn(midiNote, 127, 1);
    } else {
      stopNoteOnBuzzer();
      MIDI.sendNoteOff(midiNote, 0, 1);
    }
  }
}

void checkKey3(int key) {
  unsigned long currentTime = micros();
  const unsigned long DebounceTime = 5;
  static unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF3.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed3[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed3[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int buzzerNote = 17 + (12 * getCurrentOctave()) + key;
    int midiNote = 40 + (12 * getCurrentOctave()) + key;;
    if (ButtonWasPressed3[key]) {
      // Capture the time when the button is pressed
      buttonPressTime = micros();
      playNoteOnBuzzer(buzzerNote);
      // printBuzzerNote(buzzerNote);
      soundStartTime = micros();
      // Print the time it took from button press to sound starting
      Serial.print("Time from button press to sound (ms): ");
      Serial.println(soundStartTime - buttonPressTime);
      MIDI.sendNoteOn(midiNote, 127, 1);
    } else {
      stopNoteOnBuzzer();
      MIDI.sendNoteOff(midiNote, 0, 1);
    }
  }
}

void loop() {
  checkOctaveButtons();
  checkBPMButtons();
  sendCurrentBPM();
  for (int i = 0; i < 8; ++i) {
    checkKey1(i);
    checkKey2(i);
    checkKey3(i);
  }
}
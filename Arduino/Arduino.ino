#include <PCF8574.h>
#include <MIDI.h>

//pin
#define OCTAVE_UP 4
#define OCTAVE_DOWN 5
#define START_BTN 7
#define REC_BTN 6
#define STOP_BTN 7
#define PATTERN_UP 10
#define PATTERN_DOWN 11

//status
#define PLAY_STATUS 8
#define REC_STATUS 9
MIDI_CREATE_DEFAULT_INSTANCE();

boolean ButtonWasPressed1[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed2[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed3[] = { false, false, false, false, false, false, false, false };

boolean ButtonOctaveUpWasPressed = false;
boolean ButtonOctaveDownWasPressed = false;
boolean ButtonStartWasPressed = false;
boolean ButtonStopWasPressed = false;
boolean ButtonRecWasPressed = false;
boolean ButtonPatternUpWasPressed = false;
boolean ButtonPatternDownWasPressed = false;

int potPins[] = { A0, A1, A2, A3 };
int lastPotValues[] = { 0, 0, 0, 0 };
int midiNotePoten[] = { 4, 5, 6, 7 };

const int threshold = 2;
int octave = 0;
PCF8574 PCF1(0x20);
PCF8574 PCF2(0x21);
PCF8574 PCF3(0x22);

void setupPinMode() {
  pinMode(OCTAVE_UP, INPUT);
  pinMode(OCTAVE_DOWN, INPUT);
  pinMode(START_BTN, INPUT);
  pinMode(STOP_BTN, INPUT);
  pinMode(REC_BTN, INPUT);
  pinMode(PLAY_STATUS, OUTPUT);
  pinMode(REC_STATUS, OUTPUT);
  pinMode(PATTERN_UP, INPUT);
  pinMode(PATTERN_DOWN, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(potPins[i], INPUT);
  }
}

void setup() {
  setupPinMode();
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
  PCF1.begin();
  PCF2.begin();
  PCF3.begin();
}

void checkKey1(int key) {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF1.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed1[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed1[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int note = 24 + (12 * octave);
    if (ButtonWasPressed1[key]) {
      MIDI.sendNoteOn(key == 0 ? note : note + key, 127, 1);
    } else {
      MIDI.sendNoteOn(key == 0 ? note : note + key, 0, 1);
    }
  }
}

void checkKey2(int key) {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF2.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed2[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed2[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int note = 32 + (12 * octave);
    if (ButtonWasPressed2[key]) {
      MIDI.sendNoteOn(key == 0 ? note : note + key, 127, 1);
    } else {
      MIDI.sendNoteOn(key == 0 ? note : note + key, 0, 1);
    }
  }
}

void checkKey3(int key) {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = PCF3.readButton(key) == LOW;
  if (buttonIsPressed != ButtonWasPressed3[key] && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonWasPressed3[key] = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    int note = 40 + (12 * octave);
    if (ButtonWasPressed3[key]) {
      MIDI.sendNoteOn(key == 0 ? note : note + key, 127, 1);
    } else {
      MIDI.sendNoteOn(key == 0 ? note : note + key, 0, 1);
    }
  }
}

void checkButtonOctaveUp() {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = digitalRead(OCTAVE_UP) == LOW;
  if (buttonIsPressed != ButtonOctaveUpWasPressed && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonOctaveUpWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    if (ButtonOctaveUpWasPressed) {
      if (octave < 8) {
        octave++;
        //lcdDisplayOctave(octave);
      }
    }
  }
}

void checkButtonOctaveDown() {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = digitalRead(OCTAVE_DOWN) == LOW;
  if (buttonIsPressed != ButtonOctaveDownWasPressed && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonOctaveDownWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    if (ButtonOctaveDownWasPressed) {
      if (octave > 0) {
        octave--;
        //lcdDisplayOctave(octave);
      }
    }
  }
}

bool isPLaying = false;
bool isRecording = false;
unsigned long currentTime;
byte pattern;

void midiReadStatus() {
  if (MIDI.read()) {
    // A MIDI message was received
    byte channel = MIDI.getChannel();
    byte status = MIDI.getType();
    byte data1 = MIDI.getData1();
    byte data2 = MIDI.getData2();
    //play status
    if (data2 == 0x00) {
      digitalWrite(PLAY_STATUS, data1);
      isPLaying = data1;
    }
    //Rec status
    if (data2 == 0x01) {
      isRecording = data1;
    }
    //Stop status
    if (data2 == 0x02) {
      isPLaying = false;
    }
    //Pattern status
    if (data2 == 0x03) {
      pattern = data1;
    }
  }
  if (isPLaying && isRecording) {
    if (millis() - currentTime > 300) {
      if (millis() - currentTime > 600) {
        currentTime = millis();
      }
      digitalWrite(REC_STATUS, 1);
    } else {
      digitalWrite(REC_STATUS, 0);
    }
  } else {
    digitalWrite(REC_STATUS, isRecording);
  }
}

void checkButtonStartDown() {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = digitalRead(START_BTN) == LOW;
  if (buttonIsPressed != ButtonStartWasPressed && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonStartWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    if (ButtonStartWasPressed) {
      MIDI.sendNoteOn(0, 127, 1);
    } else {
      MIDI.sendNoteOn(0, 0, 1);
    }
  }
}

void checkButtonRecDown() {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = digitalRead(REC_BTN) == LOW;
  if (buttonIsPressed != ButtonRecWasPressed && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonRecWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    if (ButtonRecWasPressed) {
      MIDI.sendNoteOn(12, 127, 1);
    } else {
      MIDI.sendNoteOn(12, 0, 1);
    }
  }
}

void checkButtonStopDown() {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = digitalRead(STOP_BTN) == LOW;
  if (buttonIsPressed != ButtonStopWasPressed && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonStopWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    if (ButtonStopWasPressed) {
      MIDI.sendNoteOn(1, 127, 1);
    } else {
      MIDI.sendNoteOn(1, 0, 1);
    }
  }
}

void checkButtonPatternUpDown() {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = digitalRead(PATTERN_UP) == LOW;
  if (buttonIsPressed != ButtonPatternUpWasPressed && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonPatternUpWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    if (ButtonPatternUpWasPressed) {
      MIDI.sendNoteOn(13, 127, 1);
      //lcdDisplayPattern(pattern);
    } else {
      MIDI.sendNoteOn(13, 0, 1);
    }
  }
}

void checkButtonPatternDown() {
  unsigned long currentTime = millis();
  const unsigned long DebounceTime = 10;
  unsigned long ButtonStateChangeTime = 0;
  boolean buttonIsPressed = digitalRead(PATTERN_DOWN) == LOW;
  if (buttonIsPressed != ButtonPatternDownWasPressed && currentTime - ButtonStateChangeTime > DebounceTime) {
    ButtonPatternDownWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;
    if (ButtonPatternDownWasPressed) {
      MIDI.sendNoteOn(2, 127, 1);
      //lcdDisplayPattern(pattern);
    } else {
      MIDI.sendNoteOn(2, 0, 1);
    }
  }
}

void checkPoten() {
  for (int i = 0; i < 4; i++) {
    float potValue = ((1023 - analogRead(potPins[i])) / 1023.0) * 127;
    if (abs(potValue - lastPotValues[i]) >= threshold) {
      MIDI.sendNoteOn(midiNotePoten[i], (int)potValue, 1);
      lastPotValues[i] = potValue;
    }
  }
}

void loop() {
  checkPoten();
  checkButtonOctaveUp();
  checkButtonOctaveDown();
  checkButtonStartDown();
  //checkButtonStopDown();
  checkButtonRecDown();
  //checkButtonPatternUpDown();
  //checkButtonPatternDown();
  midiReadStatus();
  for (int i = 0; i < 8; i++) {
    checkKey1(i);
    checkKey2(i);
    checkKey3(i);
  }
}

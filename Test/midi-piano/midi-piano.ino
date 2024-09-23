#include <PCF8574.h>
#include <MIDI.h>
#include "OCTAVE.h"
#include "buzzerKeys.h"

// Pin definitions
#define BUZZER_PIN 8  // Ensure this is a PWM-capable pin on your board

// Midi init
MIDI_CREATE_DEFAULT_INSTANCE();

boolean ButtonWasPressed1[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed2[] = { false, false, false, false, false, false, false, false };
boolean ButtonWasPressed3[] = { false, false, false, false, false, false, false, false };

PCF8574 PCF1(0x20);
PCF8574 PCF2(0x21);
PCF8574 PCF3(0x22);

// Potentiometer for volume control
int volumePotPin = A0;  // Potentiometer connected to A0
int lastVolumeValue = 0;  // To store the last volume value
const int volumeThreshold = 2;  // Only update volume if change is significant
int currentVolume = 0;  // Stores the current volume value from potentiometer

void setupPinMode() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(volumePotPin, INPUT);
}

void setup() {
  setupPinMode();
  setupOctaveButtons();
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
  PCF1.begin();
  PCF2.begin();
  PCF3.begin();
}

// Function to play note on buzzer with given frequency and volume
void playNoteOnBuzzer(int buzzerNote) {
  BuzzerNote noteInfo = getBuzzerNoteInfo(buzzerNote);
  if (noteInfo.frequency > 0) {
    // Modulate tone based on the volume (duty cycle)
    analogWrite(BUZZER_PIN, currentVolume);  // Adjust PWM output to control volume
    tone(BUZZER_PIN, noteInfo.frequency);  // Generate tone with the desired frequency
  } else {
    noTone(BUZZER_PIN);
  }
}

// Function to stop the buzzer
void stopNoteOnBuzzer() {
  noTone(BUZZER_PIN);
  analogWrite(BUZZER_PIN, 0);  // Turn off the PWM signal to ensure silence
}

// Function to read and adjust the buzzer volume using the potentiometer
void adjustBuzzerVolume() {
  // Read the potentiometer value (0-1023)
  int potValue = analogRead(volumePotPin);

  // Map the potentiometer value to a volume range (0-255 for PWM duty cycle)
  currentVolume = map(potValue, 0, 1023, 0, 255);

  // Only update if the volume change is significant
  if (abs(currentVolume - lastVolumeValue) > volumeThreshold) {
    lastVolumeValue = currentVolume;
    //Serial.print("Adjusted Volume: ");
    //Serial.println(currentVolume);
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
    int buzzerNote = 1 + (12 * getCurrentOctave()) + key;
    int midiNote = 24 + (12 * getCurrentOctave()) + key;
    if (ButtonWasPressed1[key]) {
      //printBuzzerNote(buzzerNote);
      playNoteOnBuzzer(buzzerNote);
      MIDI.sendNoteOn(midiNote, 127, 1);
      delay(200);
    } else {
      stopNoteOnBuzzer();
      MIDI.sendNoteOff(midiNote, 0, 1);
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
    int buzzerNote = 9 + (12 * getCurrentOctave()) + key;
    int midiNote = 32 + (12 * getCurrentOctave()) + key;
    if (ButtonWasPressed2[key]) {
      //printBuzzerNote(buzzerNote);
      playNoteOnBuzzer(buzzerNote);
      MIDI.sendNoteOn(midiNote, 127, 1);
      delay(200);
    } else {
      stopNoteOnBuzzer();
      MIDI.sendNoteOff(midiNote, 0, 1);
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
    int buzzerNote = 17 + (12 * getCurrentOctave()) + key;
    int midiNote = 40 + (12 * getCurrentOctave()) + key;
    if (ButtonWasPressed3[key]) {
      //printBuzzerNote(buzzerNote);
      playNoteOnBuzzer(buzzerNote);
      MIDI.sendNoteOn(midiNote, 127, 1);
      delay(200);
    } else {
      stopNoteOnBuzzer();
      MIDI.sendNoteOff(midiNote, 0, 1);
    }
  }
}

void loop() {
  adjustBuzzerVolume();
  checkOctaveButtons();
  for (int i = 0; i < 8; ++i) {
    checkKey1(i);
    checkKey2(i);
    checkKey3(i);
  }
}

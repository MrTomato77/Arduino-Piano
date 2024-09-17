#ifndef MIDIKEYS_H
#define MIDIKEYS_H

#include <Arduino.h>

// Struct to hold MIDI note information
struct MidiNote {
    int midiNumber;
    const char* name;
};

// Function to get the MIDI number and name of a given MIDI note
MidiNote getMidiNoteInfo(int midiNote) {
    MidiNote noteInfo;
    switch (midiNote) {
        case 24: noteInfo = {24, "C1"}; break;
        case 25: noteInfo = {25, "C#1"}; break;
        case 26: noteInfo = {26, "D1"}; break;
        case 27: noteInfo = {27, "D#1"}; break;
        case 28: noteInfo = {28, "E1"}; break;
        case 29: noteInfo = {29, "F1"}; break;
        case 30: noteInfo = {30, "F#1"}; break;
        case 31: noteInfo = {31, "G1"}; break;
        case 32: noteInfo = {32, "G#1"}; break;
        case 33: noteInfo = {33, "A1"}; break;
        case 34: noteInfo = {34, "A#1"}; break;
        case 35: noteInfo = {35, "B1"}; break;
        case 36: noteInfo = {36, "C2"}; break;
        case 37: noteInfo = {37, "C#2"}; break;
        case 38: noteInfo = {38, "D2"}; break;
        case 39: noteInfo = {39, "D#2"}; break;
        case 40: noteInfo = {40, "E2"}; break;
        case 41: noteInfo = {41, "F2"}; break;
        case 42: noteInfo = {42, "F#2"}; break;
        case 43: noteInfo = {43, "G2"}; break;
        case 44: noteInfo = {44, "G#2"}; break;
        case 45: noteInfo = {45, "A2"}; break;
        case 46: noteInfo = {46, "A#2"}; break;
        case 47: noteInfo = {47, "B2"}; break;
        case 48: noteInfo = {48, "C3"}; break;
        case 49: noteInfo = {49, "C#3"}; break;
        case 50: noteInfo = {50, "D3"}; break;
        case 51: noteInfo = {51, "D#3"}; break;
        case 52: noteInfo = {52, "E3"}; break;
        case 53: noteInfo = {53, "F3"}; break;
        case 54: noteInfo = {54, "F#3"}; break;
        case 55: noteInfo = {55, "G3"}; break;
        case 56: noteInfo = {56, "G#3"}; break;
        case 57: noteInfo = {57, "A3"}; break;
        case 58: noteInfo = {58, "A#3"}; break;
        case 59: noteInfo = {59, "B3"}; break;
        case 60: noteInfo = {60, "C4"}; break;
        case 61: noteInfo = {61, "C#4"}; break;
        case 62: noteInfo = {62, "D4"}; break;
        case 63: noteInfo = {63, "D#4"}; break;
        case 64: noteInfo = {64, "E4"}; break;
        case 65: noteInfo = {65, "F4"}; break;
        case 66: noteInfo = {66, "F#4"}; break;
        case 67: noteInfo = {67, "G4"}; break;
        case 68: noteInfo = {68, "G#4"}; break;
        case 69: noteInfo = {69, "A4"}; break;
        case 70: noteInfo = {70, "A#4"}; break;
        case 71: noteInfo = {71, "B4"}; break;
        case 72: noteInfo = {72, "C5"}; break;
        case 73: noteInfo = {73, "C#5"}; break;
        case 74: noteInfo = {74, "D5"}; break;
        case 75: noteInfo = {75, "D#5"}; break;
        case 76: noteInfo = {76, "E5"}; break;
        case 77: noteInfo = {77, "F5"}; break;
        case 78: noteInfo = {78, "F#5"}; break;
        case 79: noteInfo = {79, "G5"}; break;
        case 80: noteInfo = {80, "G#5"}; break;
        case 81: noteInfo = {81, "A5"}; break;
        case 82: noteInfo = {82, "A#5"}; break;
        case 83: noteInfo = {83, "B5"}; break;
        case 84: noteInfo = {84, "C6"}; break;
        case 85: noteInfo = {85, "C#6"}; break;
        case 86: noteInfo = {86, "D6"}; break;
        case 87: noteInfo = {87, "D#6"}; break;
        case 88: noteInfo = {88, "E6"}; break;
        case 89: noteInfo = {89, "F6"}; break;
        case 90: noteInfo = {90, "F#6"}; break;
        case 91: noteInfo = {91, "G6"}; break;
        case 92: noteInfo = {92, "G#6"}; break;
        case 93: noteInfo = {93, "A6"}; break;
        case 94: noteInfo = {94, "A#6"}; break;
        case 95: noteInfo = {95, "B6"}; break;
        case 96: noteInfo = {96, "C7"}; break;
        case 97: noteInfo = {97, "C#7"}; break;
        case 98: noteInfo = {98, "D7"}; break;
        case 99: noteInfo = {99, "D#7"}; break;
        case 100: noteInfo = {100, "E7"}; break;
        case 101: noteInfo = {101, "F7"}; break;
        case 102: noteInfo = {102, "F#7"}; break;
        case 103: noteInfo = {103, "G7"}; break;
        case 104: noteInfo = {104, "G#7"}; break;
        case 105: noteInfo = {105, "A7"}; break;
        case 106: noteInfo = {106, "A#7"}; break;
        case 107: noteInfo = {107, "B7"}; break;
        default: noteInfo = {0, "Unknown"}; // Return 0 and "Unknown" if the note is out of range
    }
    return noteInfo;
}

#endif

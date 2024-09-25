#ifndef PITCHES_H
#define PITCHES_H

#include <Arduino.h>

// Struct to hold note information
struct Note {
    int frequency;
    const char* name;
};

// Function to get the frequency and name of a given MIDI note
Note getNoteInfo(int midiNote) {
    Note noteInfo;
    switch (midiNote) {
        case 1: noteInfo = {33, "C1"}; break;
        case 2: noteInfo = {35, "C#1"}; break;
        case 3: noteInfo = {37, "D1"}; break;
        case 4: noteInfo = {39, "D#1"}; break;
        case 5: noteInfo = {41, "E1"}; break;
        case 6: noteInfo = {44, "F1"}; break;
        case 7: noteInfo = {46, "F#1"}; break;
        case 8: noteInfo = {49, "G1"}; break;
        case 9: noteInfo = {52, "G#1"}; break;
        case 10: noteInfo = {55, "A1"}; break;
        case 11: noteInfo = {58, "A#1"}; break;
        case 12: noteInfo = {62, "B1"}; break;
        case 13: noteInfo = {65, "C2"}; break;
        case 14: noteInfo = {69, "C#2"}; break;
        case 15: noteInfo = {73, "D2"}; break;
        case 16: noteInfo = {78, "D#2"}; break;
        case 17: noteInfo = {82, "E2"}; break;
        case 18: noteInfo = {87, "F2"}; break;
        case 19: noteInfo = {93, "F#2"}; break;
        case 20: noteInfo = {98, "G2"}; break;
        case 21: noteInfo = {104, "G#2"}; break;
        case 22: noteInfo = {110, "A2"}; break;
        case 23: noteInfo = {117, "A#2"}; break;
        case 24: noteInfo = {123, "B2"}; break;
        case 25: noteInfo = {131, "C3"}; break;
        case 26: noteInfo = {139, "C#3"}; break;
        case 27: noteInfo = {147, "D3"}; break;
        case 28: noteInfo = {156, "D#3"}; break;
        case 29: noteInfo = {165, "E3"}; break;
        case 30: noteInfo = {175, "F3"}; break;
        case 31: noteInfo = {185, "F#3"}; break;
        case 32: noteInfo = {196, "G3"}; break;
        case 33: noteInfo = {208, "G#3"}; break;
        case 34: noteInfo = {220, "A3"}; break;
        case 35: noteInfo = {233, "A#3"}; break;
        case 36: noteInfo = {247, "B3"}; break;
        case 37: noteInfo = {262, "C4"}; break;
        case 38: noteInfo = {277, "C#4"}; break;
        case 39: noteInfo = {294, "D4"}; break;
        case 40: noteInfo = {311, "D#4"}; break;
        case 41: noteInfo = {330, "E4"}; break;
        case 42: noteInfo = {349, "F4"}; break;
        case 43: noteInfo = {370, "F#4"}; break;
        case 44: noteInfo = {392, "G4"}; break;
        case 45: noteInfo = {415, "G#4"}; break;
        case 46: noteInfo = {440, "A4"}; break;
        case 47: noteInfo = {466, "A#4"}; break;
        case 48: noteInfo = {494, "B4"}; break;
        case 49: noteInfo = {523, "C5"}; break;
        case 50: noteInfo = {554, "C#5"}; break;
        case 51: noteInfo = {587, "D5"}; break;
        case 52: noteInfo = {622, "D#5"}; break;
        case 53: noteInfo = {659, "E5"}; break;
        case 54: noteInfo = {698, "F5"}; break;
        case 55: noteInfo = {740, "F#5"}; break;
        case 56: noteInfo = {784, "G5"}; break;
        case 57: noteInfo = {831, "G#5"}; break;
        case 58: noteInfo = {880, "A5"}; break;
        case 59: noteInfo = {932, "A#5"}; break;
        case 60: noteInfo = {988, "B5"}; break;
        case 61: noteInfo = {1047, "C6"}; break;
        case 62: noteInfo = {1109, "C#6"}; break;
        case 63: noteInfo = {1175, "D6"}; break;
        case 64: noteInfo = {1245, "D#6"}; break;
        case 65: noteInfo = {1319, "E6"}; break;
        case 66: noteInfo = {1397, "F6"}; break;
        case 67: noteInfo = {1480, "F#6"}; break;
        case 68: noteInfo = {1568, "G6"}; break;
        case 69: noteInfo = {1661, "G#6"}; break;
        case 70: noteInfo = {1760, "A6"}; break;
        case 71: noteInfo = {1865, "A#6"}; break;
        case 72: noteInfo = {1976, "B6"}; break;
        case 73: noteInfo = {2093, "C7"}; break;
        case 74: noteInfo = {2217, "C#7"}; break;
        case 75: noteInfo = {2349, "D7"}; break;
        case 76: noteInfo = {2489, "D#7"}; break;
        case 77: noteInfo = {2637, "E7"}; break;
        case 78: noteInfo = {2794, "F7"}; break;
        case 79: noteInfo = {2960, "F#7"}; break;
        case 80: noteInfo = {3136, "G7"}; break;
        case 81: noteInfo = {3322, "G#7"}; break;
        case 82: noteInfo = {3520, "A7"}; break;
        case 83: noteInfo = {3729, "A#7"}; break;
        case 84: noteInfo = {3951, "B7"}; break;
        case 85: noteInfo = {4186, "C8"}; break;
        case 86: noteInfo = {4435, "C#8"}; break;
        case 87: noteInfo = {4699, "D8"}; break;
        case 88: noteInfo = {4978, "D#8"}; break;
        case 89: noteInfo = {5274, "E8"}; break;
        case 90: noteInfo = {5588, "F8"}; break;
        case 91: noteInfo = {5919, "F#8"}; break;
        case 92: noteInfo = {6271, "G8"}; break;
        case 93: noteInfo = {6644, "G#8"}; break;
        case 94: noteInfo = {7040, "A8"}; break;
        case 95: noteInfo = {7458, "A#8"}; break;
        case 96: noteInfo = {7902, "B8"}; break;
        default: noteInfo = {0, "Unknown"}; // Return 0 and "Unknown" if note is out of range
    }
    return noteInfo;
}

#endif

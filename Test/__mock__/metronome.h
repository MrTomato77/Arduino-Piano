#ifndef METRONOME_H
#define METRONOME_H

// Function declarations
void setupMetronome();
void playMetronome();
void adjustBPM();
void updateMetronomeInterval();

// Constants
extern const int METRONOME_PIN;
extern const int BPM_UP_PIN;
extern const int BPM_DOWN_PIN;
extern const int INITIAL_BPM;
extern const int BPM_INCREMENT;
extern const int METRONOME_TICK_DURATION;

#endif // METRONOME_H
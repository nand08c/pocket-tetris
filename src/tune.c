
#include "tune.h"

#include <stdbool.h>
#include <stdint.h>

#include "avr/io.h"

// NOTES array as 8bit frequency values for the timer to produce notes in the
// buzzer
const uint8_t NOTES[] = {0x01};
uint8_t note_counter = 0;
bool is_playing = false;

void tune_setup(void) {
    // Setup TIM0 to toggle OCRA0 on TIM0 reaching top and put into CTC Mode
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);
    return;
}

/**
 * Start the note reproduction and reset the counter of notes
 */
void tune_start(void) {
    note_counter = 0;
    is_playing = true;

    tune_next();
}

/**
 * Set the next note in the tuner
 */
void tune_next(void) { OCR0A = NOTES[note_counter++]; }

/**
 * Returns if the tuner is being played
 *
 * @return
 *  - true if playing
 *  - false if not playing
 */
bool is_tuning(void) { return is_playing; }

/**
 * Pause or Resume the playing of the tuner and leaves the counter of noted as
 * if
 */
void tune_pause(void) { is_playing = false; }
void tune_resume(void) { is_playing = true; }

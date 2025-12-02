#include "tune.h"

#include <stdbool.h>
#include <stdint.h>

#include "avr/io.h"

// Define a simple note structure
typedef struct {
    uint8_t pitch;    // OCR0A value (0 for silence)
    uint8_t duration; // Duration in ticks
} Note;

// Simple melody placeholder
// 0 pitch = silence
// {0, 0} = End of song
const Note MELODY[] = {
    {71, 100}, // A
    {63, 50},  // B
    {59, 50},  // C
    {53, 100}, // D
    {59, 50},  // C
    {63, 50},  // B
    {71, 100}, // A
    {0, 50},   // Rest
    {0, 0}     // End of song
};

static volatile uint16_t note_index = 0;
static volatile uint16_t duration_counter = 0;
static volatile bool is_playing = false;

void tune_setup(void) {
    // Setup TIM0 to toggle OC0A on Compare Match and put into CTC Mode
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);
    
    // Set Prescaler to 1024 (CS02 | CS00)
    // F_CPU = 16MHz. 16MHz / 1024 = 15.625kHz timer clock.
    TCCR0B |= (1 << CS02) | (1 << CS00);
}

static void tune_stop_hardware(void) {
    // Disconnect timer from output pin to stop sound
    TCCR0A &= ~(1 << COM0A0);
}

static void tune_start_hardware(void) {
    // Reconnect timer to output pin
    TCCR0A |= (1 << COM0A0);
}

/**
 * Start the note reproduction and reset the counter of notes
 */
void tune_start(void) {
    note_index = 0;
    duration_counter = 0;
    is_playing = true;
}

/**
 * Called periodically by the system timer to manage note duration
 */
void tune_tick(void) {
    if (!is_playing) return;

    if (duration_counter > 0) {
        duration_counter--;
    } else {
        // Load next note
        uint8_t pitch = MELODY[note_index].pitch;
        uint8_t len = MELODY[note_index].duration;

        if (len == 0 && pitch == 0) {
            // End of song - Restart
            note_index = 0;
        } else {
            if (pitch == 0) {
                tune_stop_hardware(); // Rest
            } else {
                OCR0A = pitch;
                tune_start_hardware(); // Play
            }
            duration_counter = len;
            note_index++;
        }
    }
}

/**
 * Returns if the tuner is being played
 *
 * @return
 *  - true if playing
 *  - false if not playing
 */
bool is_tuning(void) { return is_playing; }

/**
 * Pause or Resume the playing of the tuner
 */
void tune_pause(void) { 
    is_playing = false; 
    tune_stop_hardware();
}

void tune_resume(void) { 
    is_playing = true; 
}
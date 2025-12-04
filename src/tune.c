#include "tune.h"

#include <stdbool.h>
#include <stdint.h>

#include "avr/io.h"

// Define a simple note structure
typedef struct {
    uint8_t pitch;     // OCR0A value (0 for silence)
    uint8_t duration;  // Duration in ticks (1 tick = 2ms)
} Note;

// Tetris Theme (Korobeiniki) - Transposed to B Minor to fit 2kHz-4kHz range
// Frequencies: B7=3951Hz, F#7=2960Hz, G7=3135Hz, A7=3520Hz, E7=2637Hz
// Calculated for Prescaler 64
const Note MELODY[] = {
    {31, 150},  // B7 (Dotted Quarter)
    {31, 150},  // B7 (Dotted Quarter)
    {41, 50},   // F#7 (Eighth)
    {41, 50},   // F#7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {35, 100},  // A7 (Quarter)
    {35, 100},  // A7 (Quarter)
    {39, 50},   // G7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {41, 50},   // F#7 (Eighth)
    {41, 50},   // F#7 (Eighth)
    {46, 150},  // E7 (Dotted Quarter)
    {46, 150},  // E7 (Dotted Quarter)
    {46, 50},   // E7 (Eighth)
    {46, 50},   // E7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {31, 100},  // B7 (Quarter)
    {31, 100},  // B7 (Quarter)
    {35, 50},   // A7 (Eighth)
    {35, 50},   // A7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {41, 150},  // F#7 (Dotted Quarter)
    {41, 150},  // F#7 (Dotted Quarter)
    {39, 50},   // G7 (Eighth)
    {39, 50},   // G7 (Eighth)
    {35, 100},  // A7 (Quarter)
    {35, 100},  // A7 (Quarter)
    {31, 100},  // B7 (Quarter)
    {31, 100},  // B7 (Quarter)
    {39, 100},  // G7 (Quarter)
    {39, 100},  // G7 (Quarter)
    {46, 100},  // E7 (Quarter)
    {46, 100},  // E7 (Quarter)
    {46, 100},  // E7 (Quarter)
    {46, 100},  // E7 (Quarter)
    {0, 200},   // Rest
    {0, 200},   // Rest
    {0, 0}      // End of song
};

static volatile uint16_t note_index = 0;
static volatile uint16_t duration_counter = 0;
static volatile bool is_playing = false;

void tune_setup(void) {
    // Setup TIM0 to toggle OC0A on Compare Match and put into CTC Mode
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);

    // Setup pin output
    DDRB |= (1 << PB1);
    DDRD |= (1 << PD6);

    // Set Prescaler to 64 (CS01 | CS00)
    // F_CPU = 16MHz. 16MHz / 64 = 250kHz timer clock.
    // Formula: f = 250000 / (2 * (1 + OCR0A))
    // This enables reasonable 8-bit resolution for 2kHz-4kHz frequencies.
    TCCR0B = (1 << CS01) | (1 << CS00);
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
                tune_stop_hardware();  // Rest
            } else {
                OCR0A = pitch;
                tune_start_hardware();  // Play
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

void tune_resume(void) { is_playing = true; }

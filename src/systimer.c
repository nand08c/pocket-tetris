#include "systimer.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>

#include "tune.h"

static volatile tick_t systick_count = 0;

/**
 * @brief Timer 1 Compare A Match Interrupt Service Routine.
 *
 * This function is called when the TCNT1 counter reaches the value in OCR1A.
 * It increments the system tick counter every 2ms.
 */
ISR(TIMER1_COMPA_vect) {
    systick_count++;
    tune_tick();
}

void systimer_init(void) {
    // Configure Timer1 for CTC mode
    // WGM12 is in TCCR1B
    TCCR1B |= (1 << WGM12);

    // Set prescaler to 64
    // CS11 and CS10 are in TCCR1B
    TCCR1B |= (1 << CS11) | (1 << CS10);

    // Set the compare value for a 2ms tick
    // F_CPU = 16,000,000 Hz
    // Prescaler = 64
    // Timer clock = 16,000,000 / 64 = 250,000 Hz
    // Desired tick = 2ms = 1/500 Hz
    // OCR1A = (Timer clock / Desired frequency) - 1
    // OCR1A = (250,000 / 500) - 1 = 500 - 1 = 499
    OCR1A = 499;

    // Enable Timer1 Compare A match interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Enable global interrupts
    sei();
}

tick_t systimer_gettime(void) {
    tick_t ticks;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { ticks = systick_count; }
    return ticks;
}

tick_t time_since(tick_t time) { return systimer_gettime() - time; }

#include "buttons.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile enum BUTTON pressed_button = NONE;

void setup_buttons(void) {
    // Configure A0, A1, A2 (PC0, PC1, PC2) as inputs
    DDRC &= ~((1 << DDC0) | (1 << DDC1) | (1 << DDC2));
    // Enable pull-up resistors for A0, A1, A2
    PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2);

    // Enable Pin Change Interrupt for PCINT8-14 (which includes PC0, PC1, PC2)
    PCICR |= (1 << PCIE1);
    // Enable interrupts for PC0, PC1, PC2
    PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10);

    // Enable global interrupts
    sei();
}

void toggle_buttons_intr(void) {
    // Toggle the Pin Change Interrupt for PCINT8-14
    PCICR ^= (1 << PCIE1);
}

enum BUTTON poll(void) {
    if (!(PINC & (1 << PINC0))) {
        return LEFT;
    }
    if (!(PINC & (1 << PINC1))) {
        return RIGHT;
    }
    if (!(PINC & (1 << PINC2))) {
        return PUSHDOWN;
    }
    return NONE;
}

enum BUTTON get_pressed_button(void) {
    return pressed_button;
}

void clear_button_pressed(void) {
    pressed_button = NONE;
}

ISR(PCINT1_vect) {
    // A simple debouncing mechanism
    // This is not perfect, but it's better than nothing.
    // A better approach would be to use a timer.
    for (volatile int i = 0; i < 1000; i++);

    if (!(PINC & (1 << PINC0))) {
        pressed_button = LEFT;
    } else if (!(PINC & (1 << PINC1))) {
        pressed_button = RIGHT;
    } else if (!(PINC & (1 << PINC2))) {
        pressed_button = PUSHDOWN;
    }
}
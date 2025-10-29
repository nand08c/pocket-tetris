
#include "avr/io.h"
#include "stdlib.h"
#include "util/delay.h"

int main(void) {
    DDRB |= 0x20;

    while (1) {
        PORTB |= 0x20;
        _delay_ms(500);
        PORTB &= ~0x20;
        _delay_ms(500);
    }
    exit(EXIT_SUCCESS);
}

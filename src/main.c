
#include <util/delay.h>

#include "driver/i2c.h"
#include "driver/sh1106.h"
#include "graphics/GE_basic.h"

int main(void) {
    i2c_setup();
    sh1106_setup();

    point_t p = {10, 10};

    while (1) {
        sh1106_canvas_clear();
        sh1106_canvas_update();
        _delay_ms(500);

        GE_draw_rect(p, 20, 20);
        sh1106_canvas_update();
        _delay_ms(500);

        if (p.x > 128) {
            p.x = 10;
        } else {
            p.x += 10;
        }
        if (p.y > 64) {
            p.y = 10;
        } else {
            p.y += 5;
        }
    }
}

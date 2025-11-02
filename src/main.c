
#include "driver/i2c.h"
#include "driver/sh1106.h"
#include "graphics/GE.h"

int main(void) {
    i2c_setup();
    sh1106_setup();

    GE_draw_score(3000);
    GE_draw_tetris();
    sh1106_canvas_update();
}

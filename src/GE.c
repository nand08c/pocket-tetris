
#include "graphics/GE.h"

#include <stdint.h>

#include "graphics/GE_basic.h"
#include "stdio.h"

#define TETRIS_LENGTH CANVAS_LENGTH - 12 - 20
#define TETRIS_WIDTH CANVAS_WIDTH - 4

void GE_draw_score(uint16_t score) {
    const char* title = "score:";
    char score_text[6];
    sprintf(score_text, "%05i", score);
    point_t p = {.x = 3, .y = CANVAS_WIDTH - 4};

    for (int i = 0; title[i] != '\0'; i++) {
        GE_hputc(p, title[i], 1);
        p.y -= 6;
    }
    for (int i = 0; score_text[i] != '\0'; i++) {
        GE_hputc(p, score_text[i], 1);
        p.y -= 6;
    }
}

void GE_draw_tetris() {
    const point_t start = {.x = 12, .y = 2};
    uint8_t dx, dy;

    GE_draw_rect(start, TETRIS_LENGTH, TETRIS_WIDTH);

    dx = 0;
    for (int i = 0; i < 16; i++) {
        GE_draw_vline(P(start.x + dx, start.y), TETRIS_WIDTH);
        dx += 6;
    }
    dy = 0;
    for (int i = 0; i < 6; i++) {
        GE_draw_hline(P(start.x, start.y + dy), TETRIS_LENGTH);
        dy += 6;
    }
}

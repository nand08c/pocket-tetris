
#ifndef __GE_BASIC_H__
#define __GE_BASIC_H__

#include <stdint.h>

#include "original_types.h"

typedef uint64_t* canvas_t;

#define CANVAS_LENGTH 128
#define CANVAS_WIDTH 64

/**
 * Draws a pixel to the canvas
 */
void GE_draw_pixel(point_t p);

/**
 * Draws a vertical line starting from p with the lenght given
 */
void GE_draw_vline(point_t p, uint8_t length);

/**
 * Draws a horizontal line starting from p with the lenght given
 */
void GE_draw_hline(point_t p, uint8_t length);

/**
 * Draws a vertical line across the display in the given x position
 */
void GE_draw_fullvline(uint8_t posx);

/**
 * Draws a horizontal line across the display in the given y position */
void GE_draw_fullhline(uint8_t posy);

/**
 * Draws an empty rect starting in start using the width and height especified
 */
void GE_draw_rect(point_t start, uint8_t width, uint8_t height);

/**
 * Draws an full rect starting in start using the width and height especified
 * */
void GE_fill_rect(point_t start, uint8_t width, uint8_t height);

/**
 * Draws the character given with the point given as it's NW point
 * @ param scale is an integer that multiplys the amount of pixels used as a
 * size
 */
void GE_putc(point_t pos, char c, uint8_t scale);

/**
 * Draws the character given with the point given as it's NW point horizontally
 * @ param scale is an integer that multiplys the amount of pixels used as a
 * size
 */
void GE_hputc(point_t pos, char c, uint8_t scale);

#endif /* __GE_BASIC_H__ */

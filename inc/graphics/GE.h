
#ifndef __GE_H__
#define __GE_H__

#include "stdint.h"

/**
 * Draws the score up top of the screen fixxing the score to be 5 digits long
 */
void GE_draw_score(uint16_t score);
/**
 * Draws the main box containing all the boxes
 */
void GE_draw_tetris(void);  // TODO: Add some objet that holds all the
                            // information for all the boxes

/**
 * Draws the next piece to be printed on the bottom of the screen
 */
void GE_draw_nextpiece(void);  // TODO: Maybe this wiil be not implemented

#endif /* __GE_H__ */

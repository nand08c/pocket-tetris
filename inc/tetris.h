
#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdbool.h>

#include "types.h"

/**
 * This header contains some definitions to work with the tetris array and the
 * pieces in it
 */

/*
 * we'll use an array of pieces_t to hold all the used tiles in the tetris grid
 * colissions checks will be made in runtime using searching wich may be super
 * taxing but we'll see this same array can be passed to be drawed in the screen
 * at least
 */

/**
 * Takes a piece and checks if it collides with any other piece in the array in
 * the given position
 */
bool check_colission(piece_t* p);

/**
 * Take a piece from the array and rotate it
 */
bool piece_rotate(piece_t* p);

#endif /* __TETRIS_H__ */

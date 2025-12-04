#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdbool.h>
#include <stdint.h>

#include "types.h"

/**
 * This header contains definitions to work with the tetris board and pieces.
 * The board is represented as a bit-array where each row is a byte.
 */

/**
 * Initialize or reset the Tetris board.
 */
void tetris_init(void);

/**
 * Checks if a piece is within the valid bounds of the play area (walls and
 * floor).
 * @param p Pointer to the piece to check.
 * @return true if the piece is within bounds, false if it collides with
 * walls/floor or is out of range.
 */
bool tetris_check_bounds(const piece_t* p);

/**
 * Checks if a piece collides with existing tiles in the board.
 * @param p Pointer to the piece to check.
 * @return true if there is a collision, false otherwise.
 */
bool tetris_check_collision(const piece_t* p);

/**
 * Places a piece onto the board.
 * It first checks for collisions. If no collision, the piece's tiles are marked
 * on the board.
 * @param p Pointer to the piece to place.
 * @return true if placed successfully, false if collision prevented placement.
 */
bool tetris_place_piece(const piece_t* p);

/**
 * Checks if a specific row is full.
 * @param row The row index to check (0-15).
 * @return true if the row is full, false otherwise.
 */
bool tetris_check_row_full(uint8_t row);

/**
 * Eliminates a row from the board and shifts all rows above it down.
 * @param row The row index to eliminate.
 */
void tetris_eliminate_row(uint8_t row);

/**
 * Get the raw board array (mostly for rendering).
 * @return Pointer to the internal board array of size Ylimit.
 */
const uint8_t* tetris_get_board(void);

/**
 * Takes a piece from the array and rotate it
 */
piece_t piece_rotate_right(const piece_t* p);

/**
 * Initialize a piece defined by its type and anchor
 */
piece_t make_piece(tile_t anchor, enum PIECEFORM type);

#endif /* __TETRIS_H__ */

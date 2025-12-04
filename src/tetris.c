#include "tetris.h"

#include <string.h>

#include "types.h"

// The board is an array of 16 rows (Ylimit).
// Each row is a uint8_t where the lower 6 bits (Xlimit) represent columns.
// Bit 0 is column 0, Bit 5 is column 5.
static uint8_t board[Ylimit];

void tetris_init(void) { memset(board, 0, sizeof(board)); }

bool tetris_check_bounds(const piece_t* p) {
    for (int i = 0; i < 4; i++) {
        uint8_t x = TILEX(p->tiles[i]);
        uint8_t y = TILEY(p->tiles[i]);

        // Check X bounds (Walls)
        if (x >= Xlimit) {
            return false;
        }
        // Check Y bounds (Floor)
        // Note: Y is unsigned, so < 0 impossible.
        if (y >= Ylimit) {
            return false;
        }
    }
    return true;
}

bool tetris_check_collision(const piece_t* p) {
    for (int i = 0; i < 4; i++) {
        uint8_t x = TILEX(p->tiles[i]);
        uint8_t y = TILEY(p->tiles[i]);

        // Only check board collision if the coordinate is within bounds.
        // If it's out of bounds, it's the job of check_bounds, or we ignore it
        // here.
        if (y < Ylimit && x < Xlimit) {
            if (board[y] & (1 << x)) {
                return true;
            }
        }
    }
    return false;
}

bool tetris_place_piece(const piece_t* p) {
    // Ensure no collision before placing
    if (tetris_check_collision(p)) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        uint8_t x = TILEX(p->tiles[i]);
        uint8_t y = TILEY(p->tiles[i]);

        if (y < Ylimit && x < Xlimit) {
            board[y] |= (1 << x);
        }
    }
    return true;
}

bool tetris_check_row_full(uint8_t row) {
    if (row >= Ylimit) return false;

    // Create a mask for Xlimit bits (e.g., 6 bits -> 0x3F)
    uint8_t full_mask = (1 << Xlimit) - 1;

    return (board[row] & full_mask) == full_mask;
}

void tetris_eliminate_row(uint8_t row) {
    if (row >= Ylimit) return;

    // Shift all rows above 'row' down by one
    for (int y = row; y > 0; y--) {
        board[y] = board[y - 1];
    }
    // Clear the top row (index 0)
    board[0] = 0;
}

const uint8_t* tetris_get_board(void) { return board; }

piece_t piece_rotate_right(const piece_t* p) {
    piece_t rotated_p;
    rotated_p.type = p->type;

    // Get anchor position (first tile)
    uint8_t anchor_x = TILEX(p->tiles[0]);
    uint8_t anchor_y = TILEY(p->tiles[0]);

    for (int i = 0; i < 4; i++) {
        uint8_t current_x = TILEX(p->tiles[i]);
        uint8_t current_y = TILEY(p->tiles[i]);

        // Translate point so anchor is origin (0,0)
        int8_t rel_x = (int8_t)current_x - (int8_t)anchor_x;
        int8_t rel_y = (int8_t)current_y - (int8_t)anchor_y;

        // Rotate 90 degrees clockwise
        // In screen coords (Y down): (x, y) -> (-y, x)
        int8_t rotated_rel_x = -rel_y;
        int8_t rotated_rel_y = rel_x;

        // Translate back
        // We cast to int8_t to ensure signed arithmetic, then to uint8_t for
        // storage Note: This may wrap around if out of bounds (e.g. -1 becomes
        // 255 -> 15 masked) The caller must check bounds.
        uint8_t final_x = (uint8_t)(rotated_rel_x + (int8_t)anchor_x);
        uint8_t final_y = (uint8_t)(rotated_rel_y + (int8_t)anchor_y);

        rotated_p.tiles[i] = TILE(final_x, final_y);
    }

    return rotated_p;
}

piece_t make_piece(tile_t anchor, enum PIECEFORM type) {
    piece_t p;
    p.type = type;
    p.tiles[0] = anchor;  // Anchor is always the first tile

    uint8_t ax = TILEX(anchor);
    uint8_t ay = TILEY(anchor);

    // Relative offsets (x, y) for tiles 1, 2, 3
    // Y-axis is positive DOWN.
    int8_t offsets[3][2] = {{0, 0}, {0, 0}, {0, 0}};

    switch (type) {
        case OPIECE:
            // Square
            // [2][3]
            // [0][1] (0 is A)
            offsets[0][0] = 1;
            offsets[0][1] = 0;
            offsets[1][0] = 0;
            offsets[1][1] = -1;
            offsets[2][0] = 1;
            offsets[2][1] = -1;
            break;
        case IPIECE:
            // Line
            // [3]
            // [2]
            // [1]
            // [0] (A)
            offsets[0][0] = 0;
            offsets[0][1] = -1;
            offsets[1][0] = 0;
            offsets[1][1] = -2;
            offsets[2][0] = 0;
            offsets[2][1] = -3;
            break;
        case TPIECE:
            // T
            //    [2]
            // [1][0][3] (0 is A)
            offsets[0][0] = -1;
            offsets[0][1] = 0;
            offsets[1][0] = 0;
            offsets[1][1] = -1;
            offsets[2][0] = 1;
            offsets[2][1] = 0;
            break;
        case LPIECE:
            // L
            // [2]
            // [1]
            // [0][3] (0 is A)
            offsets[0][0] = 0;
            offsets[0][1] = -1;
            offsets[1][0] = 0;
            offsets[1][1] = -2;
            offsets[2][0] = 1;
            offsets[2][1] = 0;
            break;
        case JPIECE:
            // J
            //    [2]
            //    [1]
            // [3][0] (0 is A)
            offsets[0][0] = 0;
            offsets[0][1] = -1;
            offsets[1][0] = 0;
            offsets[1][1] = -2;
            offsets[2][0] = -1;
            offsets[2][1] = 0;
            break;
        case ZPIECE:
            // Z
            // [2][1]
            //    [0][3] (0 is A)
            offsets[0][0] = 0;
            offsets[0][1] = -1;
            offsets[1][0] = -1;
            offsets[1][1] = -1;
            offsets[2][0] = 1;
            offsets[2][1] = 0;
            break;
        case SPIECE:
            // S
            //    [1][2]
            // [3][0]    (0 is A)
            offsets[0][0] = 0;
            offsets[0][1] = -1;
            offsets[1][0] = 1;
            offsets[1][1] = -1;
            offsets[2][0] = -1;
            offsets[2][1] = 0;
            break;
        default:
            break;
    }

    for (int i = 0; i < 3; i++) {
        uint8_t tx = (uint8_t)((int8_t)ax + offsets[i][0]);
        uint8_t ty = (uint8_t)((int8_t)ay + offsets[i][1]);
        p.tiles[i + 1] = TILE(tx, ty);
    }

    return p;
}

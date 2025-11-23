
#ifndef __ORIGINAL_TYPES_H__
#define __ORIGINAL_TYPES_H__

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} point_t;

#define P(x, y) \
    (const point_t) { x, y }

enum PIECEFORM {
    NONE = -1,
    OPIECE,  // Square one
    IPIECE,  // long one
    TPIECE,  // T one
    LPIECE,  // L shaped one
    JPIECE,  // L inv shaped one
    ZPIECE,  // squaigly one by lef side
    SPIECE   // squaigly one by right side
};

#define Ylimit 16
#define Xlimit 6

#define POSYMSK 0xf0
#define POSXMSK 0x0f

typedef union {
    uint8_t posy;
    uint8_t posx;
} tile_t;

#define TILEX(tile) (tile & POSXMSK)
#define TILEY(tile) ((tile & POSYMSK) >> 4)

typedef struct {
    tile_t tiles[4];
    enum PIECEFORM type;
} piece_t;

#endif /* __ORIGINAL_TYPES_H__ */

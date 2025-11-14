
#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdint.h>

#define Ylimit 16
#define Xlimit 6

#define POSYMSK 0xf0
#define POSXMSK 0x0f

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

typedef union {
    uint8_t posy;
    uint8_t posx;
} tile_t;

typedef struct {
    tile_t tiles[4];
    tile_t origin;
    enum PIECEFORM type;
} piece_t;

#endif /* __TETRIS_H__ */

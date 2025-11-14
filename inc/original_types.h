
#ifndef __ORIGINAL_TYPES_H__
#define __ORIGINAL_TYPES_H__

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} point_t;

#define P(x, y) \
    (const point_t) { x, y }

#endif /* __ORIGINAL_TYPES_H__ */

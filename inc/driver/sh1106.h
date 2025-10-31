
#ifndef __SH1106_h__
#define __SH1106_h__

#include <stdint.h>

#define CANVAS_LEN 128

/**
 * Initialisates the sh1106 driver on the display via i2c
 */
void sh1106_setup(void);

/**
 * Clears the internal canvas buffer
 */
void sh1106_canvas_clear(void);

/**
 * Send the canvas buffer to the display via i2c
 */
void sh1106_canvas_update(void);

/**
 * Gives a handle to the internal canvas buffer
 */
uint64_t* sh1106_get_canvas();

#endif /* __SH1106_h__ */

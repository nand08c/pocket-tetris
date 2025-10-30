
#ifndef __SH1106_h__
#define __SH1106_h__

#include <stdint.h>

#define CANVAS_LEN 128

void sh1106_setup(void);
void sh1106_canvas_clear(void);
void sh1106_canvas_update(void);
uint64_t* sh1106_get_canvas();

#endif /* __SH1106_h__ */

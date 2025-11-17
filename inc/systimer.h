
#ifndef __SYSTIMER_H__
#define __SYSTIMER_H__

#include <stdint.h>

#define MS_TO_TICKS(ms) (ms >> 2)
#define TICKS_TO_MS(ticks) (ticks << 2)

typedef uint16_t tick_t;

/**
 * Setup the register for TIM1 to be used to generate ticks every 2 ms
 */
void systimer_init(void);

/**
 * Get the actual tick from the internal variable
 */
tick_t systimer_gettime(void);

/**
 * Get the ticks since a given time
 */
tick_t time_since(tick_t time);

#endif /* __SYSTIMER_H__ */

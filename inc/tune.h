
#ifndef __TUNE_H__
#define __TUNE_H__

#include <stdbool.h>

/**
 * Setup the TIM0 to produce PWM signals in the Pin PB1|D9 and the tracking of
 * notes outputed
 */
void tune_setup(void);

/**
 * Start the note reproduction and reset the counter of notes
 */
void tune_start(void);

/**
 * Set the next note in the tuner
 */
void tune_next(void);

/**
 * Returns if the tuner is being played
 *
 * @return
 *  - true if playing
 *  - false if not playing
 */
bool is_tuning(void);

/**
 * Pause or Resume the playing of the tuner and leaves the counter of noted as
 * if
 */
void tune_pause(void);
void tune_resume(void);

#endif /* __TUNE_H__ */

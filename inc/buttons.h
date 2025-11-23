
#ifndef __BUTTONS_H__
#define __BUTTONS_H__

enum BUTTON { NONE = 0, LEFT, RIGHT, PUSHDOWN, ROTATE };

/**
 * Set the hardware for the buttons using level change interrupts in the pins:
 * A0 ~ A2
 */
void setup_buttons(void);

/**
 * Toggles the interrupt reception for the buttons
 */
void toggle_buttons_intr(void);

/**
 * Do a manual polling of the state of the pines and get the active button
 */
enum BUTTON poll(void);

/**
 * Retrieve the botton pressed stored in the local variable used in the
 * interrupts
 */
enum BUTTON get_pressed_button(void);

/**
 * Clears the local variable that stores the button pressed so it can avoid
 * repeating false inputs when no interrupt is triggered
 */
void clear_button_pressed(void);

#endif /* __BUTTONS_H__ */


#ifndef __TASKS_H__
#define __TASKS_H__

#include "systimer.h"

typedef void (*task_cb)(void);

typedef struct {
    task_cb task_func;
    tick_t last_executed;
    const tick_t interval;
} task_t;

void task_execute(const task_t* task);
void task_check_interval_done(const task_t* task);

#endif /* __TASKS_H__ */

#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "main.h"
#include "tim.h"
#include "analog.h"

void encoder_init(void);
void encoder_stop(void);

uint32_t timer_get_current_tick(void);
void timer_update_callback(void);

#endif /* __HARDWARE_H */
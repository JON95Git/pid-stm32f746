#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "main.h"
#include "tim.h"
#include "analog.h"

void init_fatfs(void);
void hardware_init(void);
void encoder_init(void);
void encoder_stop(void);
void pwm_timer_init();
uint32_t timer_get_current_tick(void);
void timer_update_callback(void);

#endif /* __HARDWARE_H */
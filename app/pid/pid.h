#ifndef __PID_H
#define __PID_H

#include "hardware.h"
#include "arm_math.h"
#include "stdbool.h"
#include <math.h>
#include "tim.h"
#include "analog.h"

// #define PID_PARAM_KP 0.25
// #define PID_PARAM_KI 0.0001
// #define PID_PARAM_KD 0

#define PID_PARAM_KP 0.1
#define PID_PARAM_KI 0
#define PID_PARAM_KD 0

#define PULSES_PER_REVOLUTION 20
#define DEBOUNCE_TIME 1000

void pid_try_pid(void);
void pid_config(void);
void pid_process(void);
void pid_set_parameters(uint32_t kp, uint32_t ki, uint32_t kd, uint32_t sp);
void pid_get_parameters(uint32_t *kp, uint32_t *ki, uint32_t *kd, uint32_t *sp);

void encoder_callback(TIM_HandleTypeDef *htim);
void rpm_calculate(void);
void get_rpm(uint16_t *raw_rpm);

#endif /* __PID_H */
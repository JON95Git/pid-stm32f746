#ifndef __PID_H
#define __PID_H

#include "hardware.h"
#include "arm_math.h"
#include "stdbool.h"
#include <math.h>
#include "tim.h"
#include "analog.h"

//#define PID_DEBUG

#define PID_PARAM_KP 0.45
#define PID_PARAM_KI 0.45
#define PID_PARAM_KD 0

#define PULSES_PER_REVOLUTION 340
#define BASET_TIME 1000
#define MAX_PWM_OUTPUT 1000
#define SET_POINT_INIT 120

void pid_config(void);
void pid_process(void);
void pid_set_parameters(uint32_t kp, uint32_t ki, uint32_t kd, uint32_t sp);
void pid_get_parameters(int32_t *kp, int32_t *ki, int32_t *kd, int32_t *sp);
void pid_get_data(int16_t *pv, int16_t *sp);

void encoder_callback(TIM_HandleTypeDef *htim);
void get_rpm(uint16_t *raw_rpm);
void get_pwm_duty(uint16_t *pwm_duty);

#endif /* __PID_H */

#ifndef __ANALOG_H
#define __ANALOG_H

#include <stdio.h>
#include <string.h>
#include "cmsis_os.h"
#include "system.h"
#include "adc.h"

#define	ANALOG_ADC_INSTANCE ADC3
#define	ANALOG_ADC hadc3
#define	ANALOG_ADC_IRQn ADC_IRQn
#define ANALOG_DMA_IRQn DMA2_Stream1_IRQn
#define	ANALOG_TASK_SIGNAL 0x0003

extern osThreadId analogTaskHandle;

void analog_init(void);
void analog_start(void);
void analog_process(void);
void get_analog_value(uint32_t *analog_value);
void analog_callback(ADC_HandleTypeDef *hadc);
void analog_callback_error(ADC_HandleTypeDef *hadc);

#endif /* __ANALOG_H */
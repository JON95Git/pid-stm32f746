#include "hardware.h"

static volatile uint32_t timer_counter = 0;


void hardware_init(void)
{
    encoder_init();
}

uint32_t timer_get_current_tick(void)
{
	return (timer_counter);
}

void timer_update_callback(void)
{
	++timer_counter;
}

void encoder_init(void)
{
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
}

void encoder_stop(void)
{
    HAL_TIM_Encoder_Stop_IT(&htim3, TIM_CHANNEL_ALL);
}
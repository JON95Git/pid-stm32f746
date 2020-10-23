#include "hal_callbacks.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    analog_callback(hadc);
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
    analog_callback_error(hadc);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // update_pulse_by_interrupt();
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    encoder_callback(htim);
}
#include "analog.h"

static volatile uint32_t adc;

static void analog_enable_irq(void);
static void analog_stop(void);

static osMutexDef (mutex);
static osMutexId  (mutex_id);

void analog_init(void)
{
    mutex_id = osMutexCreate(osMutex(mutex));
}

void analog_start(void)
{
    HAL_StatusTypeDef ret = HAL_OK;
    ret = HAL_ADC_Start_DMA(&ANALOG_ADC, (uint32_t *)&adc, 1);
    if (ret != HAL_OK) {
        error_handler();
    }
}

void analog_process(void)
{
    analog_enable_irq();
    analog_start();
}

void get_analog_value(uint32_t *analog_value)
{
    osMutexWait(mutex_id, osWaitForever);
    *analog_value = adc;
    // printf("adc: %d \n\r", adc);
    osMutexRelease(mutex_id);
}

static void analog_stop(void)
{
    HAL_NVIC_DisableIRQ(ANALOG_DMA_IRQn);
    HAL_NVIC_DisableIRQ(ANALOG_ADC_IRQn);
}

static void analog_enable_irq(void)
{
    HAL_NVIC_EnableIRQ(ANALOG_DMA_IRQn);
    HAL_NVIC_EnableIRQ(ANALOG_ADC_IRQn);
}

void analog_callback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ANALOG_ADC_INSTANCE) {
        analog_stop();
        osSignalSet(analogTaskHandle, ANALOG_TASK_SIGNAL);
    }   
}

void analog_callback_error(ADC_HandleTypeDef *hadc)
{
    printf("HAL_ADC_ErrorCallback->ErrorCode %ld \n\r", hadc->ErrorCode);
}
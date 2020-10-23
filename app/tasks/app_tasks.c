#include "app_tasks.h"
#include "tim.h"
#include "pid.h"

/* Mutexes */
osMutexDef (lvgl_mutex);
osMutexId  (lvgl_mutex_id);

/* Tasks handlers */
osThreadId lvglTaskHandle;
osThreadId analogTaskHandle;
osThreadId pidTaskHandle;

void app_create_tasks(void)
{
    osThreadDef(lvglTask, lvgl_task, osPriorityHigh, 0, 2048);
    lvglTaskHandle = osThreadCreate(osThread(lvglTask), NULL);
    
    osThreadDef(analogTask, analog_task, osPriorityNormal, 0, 512);
    analogTaskHandle = osThreadCreate(osThread(analogTask), NULL);

    osThreadDef(pidTask, pid_task, osPriorityNormal, 0, 512);
    pidTaskHandle = osThreadCreate(osThread(pidTask), NULL);
}

void lvgl_task(void const * argument)
{
    lvgl_mutex_id = osMutexCreate(osMutex(lvgl_mutex));
    for(;;) {
        osDelay(5);
        osMutexWait(lvgl_mutex_id, osWaitForever);
        lv_task_handler();
        osMutexRelease(lvgl_mutex_id);
    }
}

void analog_task(void const * argument)
{
    osEvent evt;
    analog_init();
    analog_start();
    for (;;) {
        evt = osSignalWait(ANALOG_TASK_SIGNAL, osWaitForever);
        if (evt.status == osEventSignal)  {
            analog_process();
        }
    }
}

void pid_task(void const * argument)
{
    if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1) != HAL_OK) {
        /* PWM Generation Error */
        // Error_Handler();
    }
    pid_config();
    osDelay(2000);
    for(;;) {
        pid_try_pid();
        // osDelay(1000);
    }
}
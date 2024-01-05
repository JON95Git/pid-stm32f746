#include "app_tasks.h"
#include "tim.h"
#include "pid.h"

/* Mutexes */
osMutexDef (lvgl_mutex);
osMutexId  (lvgl_mutex_id);

/* Tasks handlers */
osThreadId lvglTaskHandle;
osThreadId pidTaskHandle;

void app_create_tasks(void)
{
    // osThreadDef(lvglTask, lvgl_task, osPriorityHigh, 0, 2048);
    // lvglTaskHandle = osThreadCreate(osThread(lvglTask), NULL);
    
    osThreadDef(pidTask, pid_task, osPriorityNormal, 0, 2048);
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

void pid_task(void const * argument)
{
    init_fatfs();
    pid_config();
    // Delay to move DC motor from inertia
    osDelay(2000);
    for(;;) {
        pid_process();
        osDelay(BASET_TIME);
    }
}
#ifndef __APP_TASKS_H
#define __APP_TASKS_H

#include "main.h"
#include "cmsis_os.h"
#include "lvgl.h"
#include "tft.h"
#include "touchpad.h"
#include "lv_arc.h"
#include "analog.h"
#include "system.h"

void app_create_tasks(void);
void lvgl_task(void const *argument);
void analog_task(void const *argument);
void pid_task(void const *argument); 

#endif /* __APP_TASKS_H */
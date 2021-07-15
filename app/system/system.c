#include "system.h"

void system_utils_init(void)
{
    RetargetInit(&huart1);
    printf("STM32 printf \n\r");
}

void error_handler(void)
{
    while (1)
    {
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(250);
    }
}
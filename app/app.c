#include "app.h"

void app_main(void)
{
    hardware_init();
    system_utils_init();
    lv_init();
    tft_init();
    touchpad_init();
    app_create_tasks();
    gui_app();
}
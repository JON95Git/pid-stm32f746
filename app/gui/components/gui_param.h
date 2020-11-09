#ifndef __GUI_PARAM_H
#define __GUI_PARAM_H

#ifdef EMBEDDED
#include "lvgl.h"
#include "pid.h"
#else
#include "lvgl/lvgl.h"
#endif
#include <stdio.h>
#include "gui_widgets.h"
#include "gui_spinbox.h"

#define USER_COLOR lv_color_hex(0x034885)

void gui_create_parameter_tab(lv_obj_t *parent);

#endif /* __GUI_PARAM_H */
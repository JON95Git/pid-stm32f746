#ifndef __GUI_GAUGE_H
#define __GUI_GAUGE_H

#ifdef EMBEDDED
#include "lvgl.h"
#include "analog.h"
#include "pid.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "gui_widgets.h"

#define ANALOG_RAW_TO_GAUGE_MAX_VALUE 41

void gui_create_gauge(lv_obj_t *parent);

#endif /* __GUI_GAUGE_H */
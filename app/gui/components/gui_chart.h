#ifndef __GUI_CHART_H
#define __GUI_CHART_H

#ifdef EMBEDDED
#include "lvgl.h"
#include "pid.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "gui_widgets.h"

#define CHART_OFFSET_VALUE 50

void gui_create_chart(lv_obj_t *parent);

#endif /* __GUI_CHART_H */
#ifndef __GUI_APP_H
#define __GUI_APP_H

#ifdef EMBEDDED
#include "lvgl.h"
#include "gui_chart.h"
#include "gui_gauge.h"
#include "gui_param.h"
#else
#include "lvgl/lvgl.h"
#include "components/gui_chart.h"
#include "components/gui_gauge.h"
#include "components/gui_param.h"
#endif
#include "gui_widgets.h"

// #define TABVIEW_LEFT

typedef struct {
    lv_group_t *group;
    lv_obj_t *tabview;
    lv_obj_t *tab_param;
    lv_obj_t *tab_gauge;
    lv_obj_t *tab_pid;
} gui_app_st;

void gui_app(void);

#endif /* __GUI_APP_H */
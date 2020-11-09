#ifndef __GUI_SPINBOX_H
#define __GUI_SPINBOX_H

#ifdef EMBEDDED
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "gui_widgets.h"

typedef struct {
    lv_obj_t *spinbox;
    lv_obj_t *plus_button;
    lv_obj_t *minus_button;
    lv_coord_t x_ofs;
    lv_coord_t y_ofs;
    int32_t value;;
} _gui_spinbox_st;

void gui_create_spinbox(lv_obj_t *parent, _gui_spinbox_st *spinbox_st);
void gui_create_rpm_spinbox(lv_obj_t *parent, _gui_spinbox_st *spinbox_st);
void gui_get_spinbox_value(lv_obj_t *spinbox, int32_t *value);
void gui_set_spinbox_value(lv_obj_t *spinbox, int32_t value);

#endif /* __GUI_SPINBOX_H */
#ifndef __GUI_WIDGETS_H
#define __GUI_WIDGETS_H

#ifdef EMBEDDED
#include "lvgl.h"
// #include "gui_hardware_interface.h"
#else
#include "lvgl/lvgl.h"
#endif

#define CHART_POINTS_NUMBER 1024
#define CHART_RANGE_2 200
#define CHART_RANGE 200
#define CHART_DOT_NUMBERS 45

typedef enum {
    GUI_CHART_UP = 0,
    GUI_CHART_DOWN,
} _gui_chart_state_series_t;

typedef struct {
    lv_obj_t *parent;
    const char *text;
    lv_align_t align;
    lv_coord_t x_ofs;
    lv_coord_t y_ofs;
    lv_obj_t *label;
} _gui_label_st;

typedef struct {
    lv_task_t *task_handle;
    lv_task_cb_t task_xcb;
    uint32_t period;
    lv_task_prio_t priority;
    void *parameter;
} _gui_task_st;;

typedef struct {
    lv_obj_t *chart;
    _gui_label_st chart_label;
    lv_chart_series_t *process_variable_line;
    lv_chart_series_t *setpoint_line;
    _gui_task_st chart_task;
} gui_chart_st;

typedef struct {
    lv_obj_t *gauge;
    lv_color_t needle_colors;
    _gui_task_st gauge_task;
} gui_gauge_st;

lv_obj_t *gui_create_label(_gui_label_st *label_st);
void gui_set_text_label(lv_obj_t *label, const char *text);
void gui_create_style(lv_style_t *style, const lv_font_t *font);
void gui_add_style_to_obj(lv_obj_t *obj, lv_style_t *style);
void gui_create_task(_gui_task_st *task_st);
void set_align(lv_obj_t *obj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
void set_size(lv_obj_t *obj, lv_coord_t size_w, lv_coord_t size_h);
void concatenate_strings(char *string_dst, char *string_src);
void int_to_string(int32_t integer, uint16_t string_len, char *string);
void float_to_int16(float float_point, int16_t *integer);

#endif /* __GUI_WIDGETS_H */
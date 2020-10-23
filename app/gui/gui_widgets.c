#include "gui_widgets.h"

void gui_set_text_label(lv_obj_t *label, const char *text)
{
    lv_label_set_text(label, text);
}

void gui_create_style(lv_style_t *style, const lv_font_t *font)
{
    lv_style_init(style);
    lv_style_set_text_font(style, LV_STATE_DEFAULT, font);
}

void gui_add_style_to_obj(lv_obj_t *obj, lv_style_t *style)
{
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
}

lv_obj_t *gui_create_label(_gui_label_st *label_st)
{
    lv_obj_t *label;
    label = lv_label_create(label_st->parent, NULL);
    lv_label_set_text(label, label_st->text);
    lv_obj_align(label, NULL, label_st->align, label_st->x_ofs, label_st->y_ofs);
    return label;
}

void gui_create_task(_gui_task_st *task_st)
{
    task_st->task_handle = lv_task_create(task_st->task_xcb, task_st->period, task_st->priority, task_st->parameter);
}

void set_size(lv_obj_t *obj, lv_coord_t size_w, lv_coord_t size_h)
{
    lv_obj_set_size(obj, size_w, size_h);
}

void set_align(lv_obj_t *obj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    lv_obj_align(obj, NULL, align, x_ofs, y_ofs);
}

void gui_set_gauge_value (lv_obj_t *gauge, uint8_t needle_id, int32_t value)
{
    lv_gauge_set_value(gauge, needle_id, value);
}

void gui_refresh_chart(lv_obj_t *chart)
{
    lv_chart_refresh(chart);
}

/** 
 * Utils
*/

void concatenate_strings(char *string_dst, char *string_src)
{
    strcat(string_dst, string_src);
}

void int_to_string(int32_t integer, uint16_t string_len, char *string)
{
    snprintf(string, string_len, "%ld", integer);
}

void float_to_int16(float float_point, int16_t *integer)
{
    *integer = (int16_t)(float_point + 0.5);
}
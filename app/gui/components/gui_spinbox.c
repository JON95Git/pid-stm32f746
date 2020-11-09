#include "gui_spinbox.h"

static lv_coord_t _gui_get_spinbox_height(lv_obj_t *spinbox);
static int32_t spinbox_value = 0;

static void lv_spinbox_increment_event_cb(lv_obj_t *btn, lv_event_t e)
{
    if(e == LV_EVENT_SHORT_CLICKED || e == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_obj_t *aux = btn->user_data;
        lv_spinbox_increment(aux);
        gui_get_spinbox_value(aux, &spinbox_value);
    }
}

static void lv_spinbox_decrement_event_cb(lv_obj_t *btn, lv_event_t e)
{
    if(e == LV_EVENT_SHORT_CLICKED || e == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_obj_t *aux = btn->user_data;
        lv_spinbox_decrement(aux);
        gui_get_spinbox_value(aux, &spinbox_value);
    }
}

static lv_coord_t _gui_get_spinbox_height(lv_obj_t *spinbox)
{
    lv_coord_t h = lv_obj_get_height(spinbox);
    return h;
}

static void _gui_create_spinbox_plus_button(lv_obj_t *parent, _gui_spinbox_st *spinbox_st)
{
    lv_coord_t h  = _gui_get_spinbox_height(spinbox_st->spinbox);
    spinbox_st->plus_button = lv_btn_create(parent, NULL);
    lv_obj_set_size(spinbox_st->plus_button, h, h);
    lv_obj_align(spinbox_st->plus_button, spinbox_st->spinbox, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_theme_apply(spinbox_st->plus_button, LV_THEME_SPINBOX_BTN);
    lv_obj_set_style_local_value_str(spinbox_st->plus_button, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_PLUS);
    lv_obj_set_event_cb(spinbox_st->plus_button, lv_spinbox_increment_event_cb);
    spinbox_st->plus_button->user_data = spinbox_st->spinbox;
}

static void _gui_create_spinbox_minus_button(lv_obj_t *parent, _gui_spinbox_st *spinbox_st)
{
    spinbox_st->minus_button = lv_btn_create(parent, spinbox_st->plus_button);
    lv_obj_align(spinbox_st->minus_button, spinbox_st->spinbox, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_event_cb(spinbox_st->minus_button, lv_spinbox_decrement_event_cb);
    lv_obj_set_style_local_value_str(spinbox_st->minus_button, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_MINUS);
    spinbox_st->minus_button->user_data = spinbox_st->spinbox;
}

static void _gui_create_spinbox(lv_obj_t *parent, _gui_spinbox_st *spinbox_st)
{
    spinbox_st->spinbox = lv_spinbox_create(parent, NULL);
    lv_spinbox_set_range(spinbox_st->spinbox, 0, 100);
    lv_spinbox_set_digit_format(spinbox_st->spinbox, 3, 2);
    lv_spinbox_step_prev(spinbox_st->spinbox);
    lv_obj_set_width(spinbox_st->spinbox, 50);
    lv_obj_align(spinbox_st->spinbox, NULL, LV_ALIGN_CENTER, spinbox_st->x_ofs, spinbox_st->y_ofs);
}

static void _gui_create_rpm_spinbox(lv_obj_t *parent, _gui_spinbox_st *spinbox_st)
{
    spinbox_st->spinbox = lv_spinbox_create(parent, NULL);
    lv_spinbox_set_range(spinbox_st->spinbox, 0, 200);
    lv_spinbox_set_digit_format(spinbox_st->spinbox, 3, 0);
    lv_spinbox_step_prev(spinbox_st->spinbox);
    lv_obj_set_width(spinbox_st->spinbox, 48);
    lv_obj_align(spinbox_st->spinbox, NULL, LV_ALIGN_CENTER, spinbox_st->x_ofs, spinbox_st->y_ofs);
}

void gui_create_rpm_spinbox(lv_obj_t *parent, _gui_spinbox_st *spinbox_st)
{
    _gui_create_rpm_spinbox(parent, spinbox_st);
    _gui_create_spinbox_plus_button(parent, spinbox_st);
    _gui_create_spinbox_minus_button(parent, spinbox_st);
}

void gui_create_spinbox(lv_obj_t *parent, _gui_spinbox_st *spinbox_st)
{
    _gui_create_spinbox(parent, spinbox_st);
    _gui_create_spinbox_plus_button(parent, spinbox_st);
    _gui_create_spinbox_minus_button(parent, spinbox_st);
}

void gui_get_spinbox_value(lv_obj_t *spinbox, int32_t *value)
{
    *value = lv_spinbox_get_value(spinbox);
}

void gui_set_spinbox_value(lv_obj_t *spinbox, int32_t value)
{
    lv_spinbox_set_value(spinbox, value);
}
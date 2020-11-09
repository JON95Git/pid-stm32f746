#include "gui_app.h"

static gui_app_st gui;
static void gui_create_pid_chart(lv_obj_t *parent);
static void gui_create_tabview_screen(void);

void gui_app(void)
{
    gui_create_tabview_screen();
    gui_create_parameter_tab(gui.tab_param);
    gui_create_gauge(gui.tab_gauge);
    gui_create_pid_chart(gui.tab_pid);
}

static void gui_create_tabview_screen(void)
{
    gui.tabview = lv_tabview_create(lv_scr_act(), NULL);
#ifdef TABVIEW_LEFT
    lv_tabview_set_btns_pos(gui.tabview, LV_TABVIEW_TAB_POS_LEFT);
    gui.tab_param = lv_tabview_add_tab(gui.tabview, LV_SYMBOL_SETTINGS);
    gui.tab_gauge = lv_tabview_add_tab(gui.tabview, LV_SYMBOL_EYE_OPEN);
    gui.tab_pid = lv_tabview_add_tab(gui.tabview, LV_SYMBOL_LOOP); 
    lv_obj_set_style_local_pad_left(gui.tabview, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, 1 * (LV_DPI / 10));
    lv_obj_set_style_local_pad_right(gui.tabview, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, 1 * (LV_DPI / 10));
#else
    gui.tab_param = lv_tabview_add_tab(gui.tabview, LV_SYMBOL_SETTINGS" Parameters");
    gui.tab_gauge = lv_tabview_add_tab(gui.tabview, LV_SYMBOL_EYE_OPEN" Monitor");
    gui.tab_pid = lv_tabview_add_tab(gui.tabview, LV_SYMBOL_LOOP" Graph");
    lv_obj_set_style_local_pad_bottom(gui.tabview, LV_TABVIEW_PART_TAB_BTN, LV_STATE_DEFAULT, 1);
#endif
    lv_obj_set_style_local_text_color(gui.tabview, LV_TABVIEW_PART_TAB_BTN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_text_color(gui.tabview, LV_TABVIEW_PART_TAB_BTN, LV_STATE_CHECKED, LV_COLOR_WHITE);
    lv_obj_set_style_local_text_color(gui.tabview, LV_TABVIEW_PART_TAB_BG, LV_STATE_CHECKED, LV_COLOR_WHITE);
    lv_obj_set_style_local_bg_color(gui.tabview, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, USER_COLOR);
}

static void gui_create_pid_chart(lv_obj_t *parent)
{
    gui_create_chart(parent);
}

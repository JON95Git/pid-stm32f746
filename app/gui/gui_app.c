#include "gui_app.h"

static gui_app_st gui;

static void gui_create_pid_chart(lv_obj_t *parent);
static void gui_create_tabview_screen(void);

void gui_app(void)
{
    gui_create_tabview_screen();
    gui_create_parameter_tab_components(gui.tab_param);
    gui_create_gauge(gui.tab_gauge);
    gui_create_pid_chart(gui.tab_pid);
}

static void gui_create_tabview_screen(void)
{
    gui.tabview = lv_tabview_create(lv_scr_act(), NULL);
    gui.tab_param = lv_tabview_add_tab(gui.tabview, "Parameter");
    gui.tab_gauge = lv_tabview_add_tab(gui.tabview, "System");
    gui.tab_pid = lv_tabview_add_tab(gui.tabview, "Graphics");
}

static void gui_create_pid_chart(lv_obj_t *parent)
{
    gui_create_chart(parent);
}

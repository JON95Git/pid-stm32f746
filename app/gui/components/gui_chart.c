#include "gui_chart.h"
#include <math.h>

static gui_chart_st chart_st;
static lv_style_t style;

static void update_chart_task(lv_task_t *task);
static void _gui_create_chart(lv_obj_t *parent);
static void _gui_define_chart_curves(void);
static void _gui_create_chart_label(lv_obj_t *parent, const char *string, lv_coord_t x_ofs, lv_coord_t y_ofs);
static void _gui_create_chart_task(void);
static void _gui_update_chart_points(gui_chart_st *chart, int16_t process_variable, int16_t setpoint);
static void _gui_create_chart_settings(lv_obj_t *parent);
static void _gui_chart_config(lv_obj_t *parent);
static void _gui_chart_config_texts(void);
static void _gui_chart_config_pads(void);
static void _gui_create_legend(lv_obj_t *parent);

void gui_create_chart(lv_obj_t *parent)
{
    _gui_create_chart(parent);
    _gui_define_chart_curves();
    _gui_create_chart_label(parent, "RPM", -140, 215);
    _gui_create_chart_label(parent, "Setpoint", 20, 215);
    _gui_create_legend(parent);
    _gui_create_chart_task();
}

static void _gui_create_chart(lv_obj_t *parent)
{
    chart_st.chart = lv_chart_create(parent, NULL);
    lv_style_init(&style);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, lv_color_hex(0xe9f1f7));
    lv_obj_add_style(chart_st.chart , LV_BTN_PART_MAIN, &style);
    set_size(chart_st.chart, 480, 220);
    set_align(chart_st.chart, LV_ALIGN_CENTER, 0, -12);
    _gui_create_chart_settings(parent);
    lv_chart_set_update_mode(chart_st.chart, LV_CHART_UPDATE_MODE_CIRCULAR);
}

static void _gui_create_chart_settings(lv_obj_t *parent)
{
    _gui_chart_config(parent);
    _gui_chart_config_texts();
    _gui_chart_config_pads();
}

static void _gui_chart_config(lv_obj_t *parent)
{
    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    lv_coord_t grid_h_chart = lv_page_get_height_grid(parent, 1, 1);
    lv_coord_t grid_w_chart = lv_page_get_width_grid(parent, disp_size <= LV_DISP_SIZE_LARGE ? 1 : 2, 1);
    lv_obj_set_width_margin(chart_st.chart, grid_w_chart);
    lv_obj_set_height_margin(chart_st.chart, grid_h_chart);
    lv_obj_set_drag_parent(chart_st.chart, true);
    lv_chart_set_div_line_count(chart_st.chart, 0, 0);
    lv_obj_set_style_local_border_opa(chart_st.chart, LV_CHART_PART_BG, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_line_width(chart_st.chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_local_size(chart_st.chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);/*radius of points*/
    lv_chart_set_point_count(chart_st.chart, CHART_POINTS_NUMBER);
    lv_chart_set_range(chart_st.chart, 0, CHART_RANGE);
    lv_chart_set_type(chart_st.chart, LV_CHART_TYPE_LINE);
}

static void _gui_chart_config_texts(void)
{
    lv_chart_set_y_tick_length(chart_st.chart, 0, 0);
    lv_chart_set_x_tick_length(chart_st.chart, 0, 0);
    lv_chart_set_y_tick_texts(chart_st.chart, "200\n180\n160\n140\n120\n100\n80\n60\n40\n20", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_x_tick_texts(chart_st.chart , "10\n20\n30\n40\n50\n60\n70\n80\n90\n100", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
}

static void _gui_chart_config_pads(void)
{
    lv_obj_set_style_local_pad_left(chart_st.chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 3 * (LV_DPI / 10));
    lv_obj_set_style_local_pad_bottom(chart_st.chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 2 * (LV_DPI / 10));
    lv_obj_set_style_local_pad_right(chart_st.chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 2 * (LV_DPI / 10));
    lv_obj_set_style_local_pad_top(chart_st.chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 1 * (LV_DPI / 10));
}

static void _gui_define_chart_curves(void)
{
    chart_st.setpoint_line = lv_chart_add_series(chart_st.chart, LV_COLOR_MAGENTA);
    chart_st.process_variable_line = lv_chart_add_series(chart_st.chart, LV_COLOR_PURPLE);

    lv_chart_refresh(chart_st.chart);
}

static void _gui_create_chart_label(lv_obj_t *parent, const char *string, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    chart_st.chart_label = (_gui_label_st){.parent = parent, 
                                .text = string, 
                                .align = LV_ALIGN_IN_TOP_MID, 
                                .x_ofs = x_ofs, 
                                .y_ofs = y_ofs};

    chart_st.chart_label.label = gui_create_label(&chart_st.chart_label);
    lv_chart_refresh(chart_st.chart);
}

static void _gui_create_chart_task(void)
{
    chart_st.chart_task = (_gui_task_st){ .task_xcb = update_chart_task, 
                                .period = 30, 
                                .priority = LV_TASK_PRIO_LOWEST,
                                .parameter = &chart_st};
    gui_create_task(&chart_st.chart_task);
}

static void update_chart_task(lv_task_t *task)
{
    int16_t process_variable, setpoint;
    gui_chart_st *chart = (gui_chart_st *)(task->user_data);
#ifdef EMBEDDED
    pid_get_data(&process_variable, &setpoint);
#else
    process_variable = 10;
    setpoint = 10;
#endif
    _gui_update_chart_points(chart, process_variable, setpoint);
}

static void _gui_update_chart_points(gui_chart_st *chart, int16_t process_variable, int16_t setpoint)
{
    for (int i = 0; i < CHART_POINTS_NUMBER; i++) {
        if (i == (CHART_POINTS_NUMBER - 1)) {
            chart->process_variable_line->points[i] = (int16_t)process_variable;
            chart->setpoint_line->points[i] = (int16_t)setpoint;
        } else {
            chart->process_variable_line->points[i] = chart->process_variable_line->points[i + 1];
            chart->setpoint_line->points[i] = chart->setpoint_line->points[i + 1];
        }
    }

    lv_chart_refresh(chart->chart);
}

static void _gui_create_legend(lv_obj_t *parent)
{
    static lv_point_t line_points[] = { {100, 200}, {120, 200}};

    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 3);
    lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_PURPLE);
    lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, true);

    static lv_style_t style_line2;
    lv_style_init(&style_line2);
    lv_style_set_line_width(&style_line2, LV_STATE_DEFAULT, 3);
    lv_style_set_line_color(&style_line2, LV_STATE_DEFAULT, LV_COLOR_MAGENTA);
    lv_style_set_line_rounded(&style_line2, LV_STATE_DEFAULT, true);

    lv_obj_t * line1;
    line1 = lv_line_create(parent, NULL);
    lv_line_set_points(line1, line_points, 2);
    lv_obj_add_style(line1, LV_LINE_PART_MAIN, &style_line);
    lv_obj_align(line1, NULL, LV_ALIGN_CENTER, -160, 0);

    lv_obj_t * line2;
    line2 = lv_line_create(parent, NULL);
    lv_line_set_points(line2, line_points, 2);
    lv_obj_add_style(line2, LV_LINE_PART_MAIN, &style_line2);
    lv_obj_align(line2, NULL, LV_ALIGN_CENTER, 15, 0);
}

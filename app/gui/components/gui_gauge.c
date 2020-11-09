#include "gui_gauge.h"

static _gui_label_st label_pwm_st;
static _gui_label_st label_percent_st;
static _gui_label_st label_rpm_st;
static gui_gauge_st gauge_st;
static lv_obj_t * lmeter;

static void update_gauge(lv_task_t * task);
static void _gui_create_gauge(lv_obj_t *parent);
static void _gui_set_gauge_needle(void);
static void _gui_create_gauge_task(void);

static void _gui_create_linemeter(lv_obj_t *parent);
static void _gui_create_param_label(lv_obj_t *parent, const char *string, lv_coord_t x_ofs, lv_coord_t y_ofs, _gui_label_st *label_pwm_st);

#ifndef EMBEDDED
static void get_analog_value_simulator(uint32_t *analog_value);
#endif

void gui_create_gauge(lv_obj_t *parent)
{
    _gui_create_gauge(parent);
    _gui_set_gauge_needle();
    _gui_create_gauge_task();
    lv_gauge_set_range(gauge_st.gauge, 0, 200);
    lv_gauge_set_critical_value(gauge_st.gauge, 160);
    lv_gauge_set_scale(gauge_st.gauge, 270, 21, 5);
    _gui_create_linemeter(parent);
    _gui_create_param_label(gauge_st.gauge, "RPM", 00,  60, &label_rpm_st);
}

static void _gui_create_gauge(lv_obj_t *parent)
{
    gauge_st.gauge = lv_gauge_create(parent, NULL);
}

static void _gui_set_gauge_needle(void)
{
    gauge_st.needle_colors = LV_COLOR_RED;
    lv_gauge_set_needle_count(gauge_st.gauge, 1, &gauge_st.needle_colors);
    set_size(gauge_st.gauge, 200, 200);
    set_align(gauge_st.gauge, LV_ALIGN_CENTER, 80, 0);
    lv_gauge_set_value(gauge_st.gauge, 0, 0);
}

static void _gui_create_gauge_task(void)
{
    gauge_st.gauge_task = (_gui_task_st){ .task_xcb = update_gauge, 
                                .period = 10, 
                                .priority = LV_TASK_PRIO_LOWEST,
                                .parameter = &gauge_st};
    gui_create_task(&gauge_st.gauge_task);
}

static void update_gauge(lv_task_t *task)
{
    gui_gauge_st *gauge = (gui_gauge_st *)(task->user_data);

#ifdef EMBEDDED
    uint16_t rpm;
    get_rpm(&rpm);
    lv_gauge_set_value(gauge->gauge, 0, (int32_t)rpm);
#else
    uint32_t analog_value, res;
    get_analog_value_simulator(&analog_value);
    res = (analog_value / ANALOG_RAW_TO_GAUGE_MAX_VALUE);
    lv_gauge_set_value(gauge->gauge, 0, (int32_t)analog_value);
#endif
}

#ifndef EMBEDDED
static void get_analog_value_simulator(uint32_t *analog_value)
{
    static int16_t analog;
    analog += 10;
    if (analog >= 4096) {
        analog = 0;
    }
    *analog_value = analog;
}
#endif


static void update_line_meter(lv_task_t * t)
{
    uint16_t pwm_duty;
#ifdef EMBEDDED
    get_pwm_duty(&pwm_duty);
#else
    pwm_duty = 500;
#endif
    char string[4];
    pwm_duty = pwm_duty/10;

    if (pwm_duty > 100) {
        pwm_duty = 100;
    }

    lv_linemeter_set_value(lmeter, pwm_duty);
    int_to_string(pwm_duty,4, string);
    gui_set_text_label(label_percent_st.label, string);
}

static void _gui_create_linemeter(lv_obj_t *parent)
{
    lmeter = lv_linemeter_create(parent, NULL);
    lv_linemeter_set_range(lmeter, 0, 100);
    lv_linemeter_set_value(lmeter, 00);
    lv_linemeter_set_scale(lmeter, 270, 10); 
    lv_obj_set_size(lmeter, 150, 150);
    lv_obj_align(lmeter, NULL, LV_ALIGN_CENTER, -100, 0);
    
    _gui_create_param_label(parent, "PWM", -100,  00, &label_pwm_st);
    _gui_create_param_label(parent, "00", -100,  30, &label_percent_st);
    lv_task_create(update_line_meter, 20, LV_TASK_PRIO_LOWEST, lmeter);
}

static void _gui_create_param_label(lv_obj_t *parent, const char *string, lv_coord_t x_ofs, lv_coord_t y_ofs, _gui_label_st *label_pwm_st)
{
    *label_pwm_st = (_gui_label_st){.parent = parent, 
                                .text = string, 
                                .align = LV_ALIGN_CENTER, 
                                .x_ofs = x_ofs, 
                                .y_ofs = y_ofs};

    label_pwm_st->label  = gui_create_label(label_pwm_st);
}
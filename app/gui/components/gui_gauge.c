#include "gui_gauge.h"

static gui_gauge_st gauge_st;

static void update_gauge(lv_task_t * task);
static void _gui_create_gauge(lv_obj_t *parent);
static void _gui_set_gauge_needle(void);
static void _gui_create_gauge_task(void);

#ifndef EMBEDDED
static void get_analog_value_simulator(uint32_t *analog_value);
#endif

void gui_create_gauge(lv_obj_t *parent)
{
    _gui_create_gauge(parent);
    _gui_set_gauge_needle();
    _gui_create_gauge_task();
}

static void _gui_create_gauge(lv_obj_t *parent)
{
    gauge_st.gauge = lv_gauge_create(parent, NULL);
}

static void _gui_set_gauge_needle(void)
{
    gauge_st.needle_colors = LV_COLOR_RED;
    lv_gauge_set_needle_count(gauge_st.gauge, 1, &gauge_st.needle_colors);
    set_size(gauge_st.gauge, 180, 180);
    set_align(gauge_st.gauge, LV_ALIGN_CENTER, 0, 0);
    lv_gauge_set_value(gauge_st.gauge, 0, 10);
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
#else
   get_analog_value_simulator(&analog_value);
#endif
    lv_gauge_set_value(gauge->gauge, 0, (int32_t)rpm/2);
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
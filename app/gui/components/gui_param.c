#include "gui_param.h"

static _gui_label_st kp_label;
static _gui_label_st ki_label;
static _gui_label_st kd_label;
static _gui_label_st sp_label;

static _gui_spinbox_st kp_spinbox;
static _gui_spinbox_st ki_spinbox;
static _gui_spinbox_st kd_spinbox;
static _gui_spinbox_st sp_spinbox;

static void gui_set_parameters(void);
static void gui_get_pid_data_screen(void);
static void gui_clean_pid_data_screen(void);
static void _gui_create_button(lv_obj_t *parent);
static void update_event_handler(lv_obj_t * obj, lv_event_t event);
static void clear_event_handler(lv_obj_t * obj, lv_event_t event);

static void _gui_create_param_label(lv_obj_t *parent, const char *string, lv_coord_t x_ofs, lv_coord_t y_ofs, _gui_label_st *label_st)
{
    *label_st = (_gui_label_st){.parent = parent, 
                                .text = string, 
                                .align = LV_ALIGN_CENTER, 
                                .x_ofs = x_ofs, 
                                .y_ofs = y_ofs};

    label_st->label  = gui_create_label(label_st);
}

static void _gui_create_spinbox_parameter_tab(lv_obj_t *parent, lv_coord_t x_ofs, lv_coord_t y_ofs, _gui_spinbox_st *spinbox)
{
    spinbox->x_ofs = x_ofs;
    spinbox->y_ofs = y_ofs;
    gui_create_spinbox(parent, spinbox);
}

static void _gui_create_labels(lv_obj_t *parent)
{
    _gui_create_param_label(parent, "KP", -200, -80+10, &kp_label);
    _gui_create_param_label(parent, "KI", -200, -10+10, &ki_label);
    _gui_create_param_label(parent, "KD", 20, -80+10, &kd_label);
    _gui_create_param_label(parent, "SP", 20, -10+10, &sp_label);
}

void gui_create_parameter_tab_components(lv_obj_t *parent)
{
    _gui_create_spinbox_parameter_tab(parent, -100, -80+10, &kp_spinbox);
    _gui_create_spinbox_parameter_tab(parent, -100, -10+10, &ki_spinbox);
    _gui_create_spinbox_parameter_tab(parent, 120, -80+10, &kd_spinbox);
    _gui_create_spinbox_parameter_tab(parent, 120, -10+10, &sp_spinbox);
    _gui_create_labels(parent);
    _gui_create_button(parent);
}

static void update_event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Updating PID data on screen...\n\r");
        gui_set_parameters();
    }
}

static void clear_event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Cleaning PID data on screen...\n\r");
        gui_clean_pid_data_screen();
        printf("Done. \n\r");
    }
}

static void _gui_create_button(lv_obj_t *parent)
{
    lv_obj_t *button_label;

    lv_obj_t *update_button = lv_btn_create(parent, NULL);
    lv_obj_set_event_cb(update_button, update_event_handler);
    lv_obj_align(update_button, NULL, LV_ALIGN_CENTER, 120, 40+10);

    button_label = lv_label_create(update_button, NULL);
    lv_label_set_text(button_label, "Update PID");

    lv_obj_t *clear_button = lv_btn_create(parent, NULL);
    lv_obj_set_event_cb(clear_button, clear_event_handler);
    lv_obj_align(clear_button, NULL, LV_ALIGN_CENTER, -100, 40+10);

    button_label = lv_label_create(clear_button, NULL);
    lv_label_set_text(button_label, "Clear PID");
}

static void gui_clean_pid_data_screen(void)
{
    gui_set_spinbox_value(kp_spinbox.spinbox, 0);
    gui_set_spinbox_value(ki_spinbox.spinbox, 0);
    gui_set_spinbox_value(kd_spinbox.spinbox, 0);
    gui_set_spinbox_value(sp_spinbox.spinbox, 0);
}

static void gui_get_pid_data_screen(void)
{
    gui_get_spinbox_value(kp_spinbox.spinbox, &kp_spinbox.value);
    gui_get_spinbox_value(ki_spinbox.spinbox, &ki_spinbox.value);
    gui_get_spinbox_value(kd_spinbox.spinbox, &kd_spinbox.value);
    gui_get_spinbox_value(sp_spinbox.spinbox, &sp_spinbox.value);
}

static void gui_set_parameters(void)
{
    gui_get_pid_data_screen();
#ifdef EMBEDDED
    pid_set_parameters(kp_spinbox.value, ki_spinbox.value, kd_spinbox.value, sp_spinbox.value);
#endif
}
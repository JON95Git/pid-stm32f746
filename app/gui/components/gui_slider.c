

static lv_obj_t *kp_slider;
static lv_obj_t *ki_slider;
static lv_obj_t *kd_slider;
static lv_obj_t *sp_slider;


static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Value: %d\n\r", lv_slider_get_value(obj));
    }
}

static void create_slider(lv_obj_t *parent, lv_obj_t *slider, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    slider = lv_slider_create(parent, NULL);
    lv_obj_align(slider, NULL, LV_ALIGN_CENTER, x_ofs, y_ofs);
    lv_obj_set_event_cb(slider, event_handler);
    set_size(slider, 100, 20);
}

void gui_slider(lv_obj_t *parent)
{
    // create_slider(parent, kp_slider, 0, -40);
    // create_slider(parent, ki_slider, 0, 60);
    // create_slider(parent, kd_slider, 250, -40);
    // create_slider(parent, sp_slider, 2

    kp_spinbox.x_ofs = -150;
    kp_spinbox.y_ofs = -50;
    gui_create_spinbox(parent, &kp_spinbox);

    ki_spinbox.x_ofs = -150;
    ki_spinbox.y_ofs = 50;
    gui_create_spinbox(parent, &ki_spinbox);

    kd_spinbox.x_ofs = 150;
    kd_spinbox.y_ofs = -50;
    gui_create_spinbox(parent, &kd_spinbox);

    sp_spinbox.x_ofs = 150;
    sp_spinbox.y_ofs = 50;
    gui_create_spinbox(parent, &sp_spinbox);

/*
    _gui_create_param_label(kp_slider, "kp", 0, -60, &kp_label);
    _gui_create_param_label(ki_slider, "ki", 0, 60, &ki_label);
    _gui_create_param_label(kd_slider, "kd", 250, -40, &kd_label);
    _gui_create_param_label(sp_slider, "sp", 250, 40, &sp_label);
*/
    // _gui_create_param_label(parent, "kp", -180, -70, &kp_label);
    // _gui_create_param_label(parent, "ki", -180, 30, &ki_label);
    // _gui_create_param_label(parent, "kd", 80, -70, &kd_label);
    // _gui_create_param_label(parent, "sp", 80, 30, &sp_label);
}










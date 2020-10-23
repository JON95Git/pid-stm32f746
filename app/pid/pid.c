#include "pid.h"

float pid_error;
uint32_t duty = 0;
float set_point = 600;
float process_variable;
float feedback_value;
uint32_t actuator;
arm_pid_instance_f32 PID;
volatile int32_t encoder_value;

volatile uint32_t rpm = 0;
volatile uint32_t pulsos = 0;
volatile bool is_print_variable = false;

static void update_duty_cycle(uint16_t duty_percent);
static void print_variables(void);

void pid_config(void)
{
    PID.Kp = PID_PARAM_KP;
    PID.Ki = PID_PARAM_KI;
    PID.Kd = PID_PARAM_KD;
    arm_pid_init_f32(&PID, 1);
}

void pid_get_parameters(uint32_t *kp, uint32_t *ki, uint32_t *kd, uint32_t *sp)
{
    // gui_get_parameters(&kp, &ki, &kd, &sp);
}

void pid_set_parameters(uint32_t kp, uint32_t ki, uint32_t kd, uint32_t sp)
{
    PID.Kp = kp;
    PID.Ki = ki;
    PID.Kd = kd;
    set_point = sp;
    arm_pid_reset_f32(&PID);
}

void pid_try_pid(void)
{
    /* calculo RPM */
    rpm_calculate();

    /* controle PID */
    feedback_value = rpm;
    pid_error = feedback_value - set_point; //try invert this
    process_variable = arm_pid_f32(&PID, pid_error);
    actuator = (int32_t)(process_variable + 0.5);
    duty = (uint32_t )100 - actuator;
    // update_duty_cycle(duty);

    TIM1->CCR1 = 280;
    if (is_print_variable) {
        print_variables();
        is_print_variable = false;
    }
}

void rpm_calculate(void)
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = timer_get_current_tick();

    if (interrupt_time - last_interrupt_time >= DEBOUNCE_TIME) {
        rpm = (60 * DEBOUNCE_TIME / PULSES_PER_REVOLUTION ) / (interrupt_time - last_interrupt_time) * pulsos;
        pulsos = 0;
        last_interrupt_time = timer_get_current_tick();
        is_print_variable = true;
    }
}

static void update_duty_cycle(uint16_t duty_percent)
{
    uint16_t duty_int32;
    
    if (duty_percent > 100) {
        duty_percent = 100;
    } else if (duty_percent < 0) {
        duty_percent = 0;
    }

    duty_int32 = duty_percent * 1000 / 100;

    TIM1->CCR1 = duty_int32;
}

void encoder_callback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3) {
        encoder_value = TIM3->CNT;
    }
    pulsos++;
}

static void print_variables(void)
{
    printf("RPM.............: %ld \n\r", rpm);
    printf("set_point.......: %.2f \n\r", set_point);
    printf("pid_error.......: %.2f \n\r", pid_error);
    
    printf("process_variable: %.2f \n\r", process_variable);
    printf("actuator........: %ld \n\r", actuator);
    printf("duty............: %ld \n\r", duty);
    // printf("encoder_value...: %ld \n\r", encoder_value);
    
    printf("---------------------------------------------\n\r");
    printf("---------------------------------------------\n\r");
    printf("---------------------------------------------\n\r");
}

void get_rpm(uint16_t *raw_rpm)
{
    *raw_rpm = rpm;
}
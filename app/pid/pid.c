#include "pid.h"
#include "stm32746g_discovery.h"

static float set_point = SET_POINT_INIT;
static float pid_output;
static float error;

static arm_pid_instance_f32 PID;
static uint32_t actuator;
static uint32_t duty = 0;
static volatile uint32_t rpm = 0;
static volatile uint32_t pulses = 0;

static void rpm_calculate(void);
static void pid_calculate(void);
static void update_duty_cycle(void);
#ifdef PID_DEBUG
static void print_variables(void);
#endif

void pid_config(void)
{
    PID.Kp = PID_PARAM_KP;
    PID.Ki = PID_PARAM_KI;
    PID.Kd = PID_PARAM_KD;
    arm_pid_init_f32(&PID, 1);
}

void pid_get_parameters(int32_t *kp, int32_t *ki, int32_t *kd, int32_t *sp)
{
    *kp = (int32_t) (PID_PARAM_KP + 0.5) * 10;
    *ki = (int32_t) (PID_PARAM_KI + 0.5) * 10;
    *kd = (int32_t) (PID_PARAM_KD + 0.5) * 5;
    *sp = (int32_t) (set_point + 0.5);
}

void pid_get_data(int16_t *pv, int16_t *sp)
{
    *pv = (int16_t) (rpm + 0.5);
    *sp = (int16_t) (set_point + 0.5);
}

void pid_set_parameters(uint32_t kp, uint32_t ki, uint32_t kd, uint32_t sp)
{
    PID.Kp = (kp * 1.0) / 10;
    PID.Ki = (ki * 1.0) / 10;
    PID.Kd = (kd * 1.0) / 10;
    set_point = sp;
    arm_pid_reset_f32(&PID);
}

void pid_process(void)
{
    rpm_calculate();
    pid_calculate();
    update_duty_cycle();
#ifdef PID_DEBUG
    print_variables();
#endif

}

void encoder_callback(TIM_HandleTypeDef *htim)
{
    pulses++;
}

void get_rpm(uint16_t *raw_rpm)
{
    *raw_rpm = rpm;
}

void get_pwm_duty(uint16_t *pwm_duty)
{
    *pwm_duty = duty;
}

static void pid_calculate(void)
{
    error = set_point - rpm;
    pid_output = arm_pid_f32(&PID, error);
    // Convert from float to uint32_t
    actuator = (int32_t)(pid_output + 0.5);
    // Normalize  duty cycle (range 0 to 10000 - 0% to 100%)
    duty = (uint32_t )actuator + (MAX_PWM_OUTPUT/2);

    if (duty > MAX_PWM_OUTPUT) {
        duty = MAX_PWM_OUTPUT;
    } else if (duty < 0){
        duty = 0;
    }
    
}

static void rpm_calculate(void)
{
    rpm = (60 * BASET_TIME / PULSES_PER_REVOLUTION ) / BASET_TIME * pulses;
    pulses = 0;
}

static void update_duty_cycle(void)
{
    TIM1->CCR1 = duty;
}

#ifdef PID_DEBUG
static void print_variables(void)
{
    printf("RPM.............: %ld \n\r", rpm);
    printf("KP..............: %.2f \n\r", PID.Kp);
    printf("KI..............: %.2f \n\r", PID.Ki);
    printf("KD..............: %.2f \n\r", PID.Kd);
    printf("set_point.......: %.2f \n\r", set_point);
    printf("error...........: %.2f \n\r", error);
    printf("pid_output......: %.2f \n\r", pid_output);
    printf("actuator........: %ld \n\r", actuator);
    printf("duty............: %ld \n\r", duty);
    printf("---------------------------------------------\n\r");
    printf("---------------------------------------------\n\r");
    printf("---------------------------------------------\n\r");
}
#endif
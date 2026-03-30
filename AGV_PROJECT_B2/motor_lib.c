#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"


void motor_R(float factor)
{
    int motor_PWM_R = PWM * factor;
    if (motor_PWM_R >= TOP_VALUE) motor_PWM_R = TOP_VALUE;
    OCR5C = motor_PWM_R;
}

void motor_L(float factor)
{
    int motor_PWM_L = PWM * factor;
    if (motor_PWM_L >= TOP_VALUE) motor_PWM_L = TOP_VALUE;
    OCR5A = motor_PWM_L;
}

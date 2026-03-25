#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"


void motor_R(int factor)
{
    OC5C = factor*PWM
}

void motor_L(int factor)
{
    OC5A = factor*PWM
}

motor

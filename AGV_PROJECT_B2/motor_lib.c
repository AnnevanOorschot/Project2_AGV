#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"


void motor_R(int factor)
{
    OCR5C = factor*PWM;
}

void motor_L(int factor)
{
    OCR5A = factor*PWM;
}

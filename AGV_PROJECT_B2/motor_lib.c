#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "module.h"

void motor_R(float factor)
{
    int motor_PWM_R = PWM * factor;
    if (motor_PWM_R >= TOP_VALUE) motor_PWM_R = TOP_VALUE;
    OCR4A = motor_PWM_R;
}

/// IFSTATEMENT VOOR PWM 0 EN 100

void motor_L(float factor)
{
    int motor_PWM_L = PWM * factor;
    if (motor_PWM_L >= TOP_VALUE) motor_PWM_L = TOP_VALUE;
    OCR5A = motor_PWM_L;
}

void motor_config(int mode, int kant)
{
    enum motor_actie actie = mode;
    enum richting motor = kant;
    if (kant == LINKS) // y = 0s
    {
        switch (mode)
        {
        case VOORUIT://CLOCKWISE
            {
                PWM_IN_3_PORT |= (1 << PWM_IN_3);   //HIGH
                PWM_IN_4_PORT &= ~(1 << PWM_IN_4);  //LOW
                break;
            }
        case ACHTERUIT://COUNTER CLOCKWISE
            {
                PWM_IN_3_PORT &= ~(1 << PWM_IN_3);  //LOW
                PWM_IN_4_PORT |= (1 << PWM_IN_4);   //HIGH
                break;
            }
        case REMMEN:
            {
                PWM_IN_3_PORT |= (1 << PWM_IN_3);   //HIGH
                PWM_IN_4_PORT |= (1 << PWM_IN_4);   //HIGH
                break;
            }
        }
    }

    if (motor == RECHTS) // y = 1
    {
        switch (actie)
        {
        case VOORUIT://CLOCKWISE
            {
                PWM_IN_1_PORT |= (1 << PWM_IN_1);   //HIGH
                PWM_IN_2_PORT &= ~(1 << PWM_IN_2);  //LOW
                break;
            }
        case ACHTERUIT://COUNTER CLOCKWISE
            {
                PWM_IN_1_PORT &= ~(1 << PWM_IN_1);  //LOW
                PWM_IN_2_PORT |= (1 << PWM_IN_2);   //HIGH
                break;
            }
        case REMMEN:
            {
                PWM_IN_1_PORT |= (1 << PWM_IN_1);   //HIGH
                PWM_IN_2_PORT |= (1 << PWM_IN_2);   //HIGH
                break;
            }
        }
    }
}

#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"

float ultrasoonAfstand_R(void)
{
    unsigned int counter = 0;
    ULTRASOON_TRIGGER_R_PORT |= (1 << ULTRASOON_TRIGGER_R);
    ULTRASOON_TRIGGER_R_PORT &= ~(1 << ULTRASOON_TRIGGER_R);
    while (!(ULTRASOON_ECHO_R_PIN & (1 << ULTRASOON_ECHO_R)))
    {
        counter++;
    }
    float time_measured = counter/(62*0.00001); //return as ms
    int afstand = time_measured * 320 * 100;
    return afstand;
}

float ultrasoonAfstand_L(void)
{
    unsigned int counter = 0;
    ULTRASOON_TRIGGER_L_PORT |= (1 << ULTRASOON_TRIGGER_L);
    ULTRASOON_TRIGGER_L_PORT &= ~(1 << ULTRASOON_TRIGGER_L);
    while (!(ULTRASOON_ECHO_L_PIN & (1 << ULTRASOON_ECHO_L)))
    {
        counter++;
    }
    float time_measured = counter/(62 * 0.000001); //return as ms
    int afstand = time_measured * 320 * 100;
    return afstand;
}

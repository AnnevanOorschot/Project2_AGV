#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"


void init_ultrasoon_sensor(void)
{
    //ULTRASOON Echo als output configureren
    ULTRASOON_ECHO_R_DDR |= (1 << ULTRASOON_ECHO_R);
    ULTRASOON_ECHO_L_DDR |= (1 << ULTRASOON_ECHO_L);

    //ULTRASOON Echo laagzetten
    ULTRASOON_ECHO_R_DDR &= ~(1 << ULTRASOON_ECHO_R);
    ULTRASOON_ECHO_L_DDR &= ~(1 << ULTRASOON_ECHO_L);

    //ULTRASOON Trigger als input configureren
    ULTRASOON_TRIGGER_R_DDR &= ~(1 << ULTRASOON_TRIGGER_R);
    ULTRASOON_TRIGGER_L_DDR &= ~(1 << ULTRASOON_TRIGGER_L);
}

void init_infrarood_sensor(void)
{
    //INFRAROOD AGV als input configureren
    INFRAROOD_AGV_R_DDR &= ~(1 << INFRAROOD_AGV_R);
    INFRAROOD_AGV_L_DDR &= ~(1 << INFRAROOD_AGV_L);

    //INFRAROOD MODULE als input configureren
    INFRAROOD_MODULE_R_DDR &= ~(1 << INFRAROOD_MODULE_R);
    INFRAROOD_MODULE_L_DDR &= ~(1 << INFRAROOD_MODULE_L);
}

void init_knopjes(void)
{
    //KNOPJES als input configuren
    KNOP_1_DDR &= ~(1 << KNOP_1);
    KNOP_2_DDR &= ~(1 << KNOP_2);
    KNOP_3_DDR &= ~(1 << KNOP_3);
    KNOP_4_DDR &= ~(1 << KNOP_4);
    KNOP_5_DDR &= ~(1 << KNOP_5);
}

void init_led(void)
{
    //LED als output configuren
    LED_1_DDR |= (1 << LED_1);
    LED_2_DDR |= (1 << LED_2);
    LED_3_DDR |= (1 << LED_3);

    //LED laag zetten
    LED_1_PORT &= ~(1 << LED_1);
    LED_2_PORT &= ~(1 << LED_2);
    LED_3_PORT &= ~(1 << LED_3);
}

void init_h_brug_dual(void)
{
    //PWM als output configureren
    PWM_R_DDR |= (1 << PWM_R);
    PWM_L_DDR |= (1 << PWM_L);

    //PWM laagzetten
    PWM_R_PORT &= ~(1 << PWM_R);
    PWM_L_PORT &= ~(1 << PWM_L);

    //IN als input
    IN_1_DDR &= ~(1 << IN_1);
    IN_2_DDR &= ~(1 << IN_2);
    IN_3_DDR &= ~(1 << IN_3);
    IN_4_DDR &= ~(1 << IN_4);
}

void init_noodstop(void)
{
    //NOODSTOP als input configureren
    NOODSTOP_DDR &= ~(1 << NOODSTOP);
}

void init_timer(void)
{
    ICR5 = TOP_VALUE;

    TCCR5A = (1 << WGM51) | (0 << WGM50) | (1 << COM5A1) | (0 << COM5A0);
    TCCR5B = (1 << WGM53) | (1 << WGM52) | (0 << CS52) | (0 << CS51) | (1 << CS50);
}

void init_function(void)
{
    init_ultrasoon_sensor();
    init_infrarood_sensor();
    init_knopjes();
    init_led();
    init_h_brug_dual();
    init_noodstop();
}

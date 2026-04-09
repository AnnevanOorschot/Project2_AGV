#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"


void init_ultrasoon_sensor(void)
{
    //ULTRASOON Echo als INPUT configureren
    ULTRASOON_ECHO_R_DDR &= ~(1 << ULTRASOON_ECHO_R);
    ULTRASOON_ECHO_L_DDR &= ~(1 << ULTRASOON_ECHO_L);

    //ULTRASOON Trigger als OUTPUT configureren
    ULTRASOON_TRIGGER_R_DDR |= (1 << ULTRASOON_TRIGGER_R);
    ULTRASOON_TRIGGER_L_DDR |= (1 << ULTRASOON_TRIGGER_L);

    //ULTRASOON Echo laagzetten
    ULTRASOON_TRIGGER_R_PORT &= ~(1 << ULTRASOON_ECHO_R);
    ULTRASOON_TRIGGER_L_PORT &= ~(1 << ULTRASOON_ECHO_L);
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
    KNOP_6_DDR &= ~(1 << KNOP_6);

    //KNOPJES pull-up aanzetten
    KNOP_1_PORT |= (1 << KNOP_1);
    KNOP_2_PORT |= (1 << KNOP_2);
    KNOP_3_PORT |= (1 << KNOP_3);
    KNOP_4_PORT |= (1 << KNOP_4);
    KNOP_5_PORT |= (1 << KNOP_5);
    KNOP_6_PORT |= (1 << KNOP_6);
}

void init_led(void)
{
    //LED als output configuren
    LED_1_DDR |= (1 << LED_1);
    LED_2_DDR |= (1 << LED_2);
    LED_3_DDR |= (1 << LED_3);

    //LED laag zetten
    LED_1_PORT |= (1 << LED_1);
    LED_2_PORT |= (1 << LED_2);
    LED_3_PORT |= (1 << LED_3);
}

void init_h_brug_dual(void)
{
    //PWM als output configureren
    PWM_R_DDR |= (1 << PWM_R);
    PWM_L_DDR |= (1 << PWM_L);

    //PWM laagzetten
    PWM_R_PORT &= ~(1 << PWM_R);
    PWM_L_PORT &= ~(1 << PWM_L);

    //IN als output
    PWM_IN_1_DDR |= (1 << PWM_IN_1); // IN 1 --> motor A = rechts
    PWM_IN_2_DDR |= (1 << PWM_IN_2); // IN 2 --> motor A = rechts
    PWM_IN_3_DDR |= (1 << PWM_IN_3); // IN 3 --> motor B = links
    PWM_IN_4_DDR |= (1 << PWM_IN_4); // IN 4 --> motor B = links

    //IN laagzetten
    PWM_IN_1_PORT &= ~(1 << PWM_IN_1); // IN 1 --> motor A = rechts
    PWM_IN_2_PORT &= ~(1 << PWM_IN_2); // IN 2 --> motor A = rechts
    PWM_IN_3_PORT &= ~(1 << PWM_IN_3); // IN 3 --> motor B = links
    PWM_IN_4_PORT &= ~(1 << PWM_IN_4); // IN 4 --> motor B = links
}

void init_noodstop(void)
{
    //NOODSTOP als input configureren
    NOODSTOP_DDR &= ~(1 << NOODSTOP);
}

void init_timer_PWM(void)
{
    ICR5 = TOP_VALUE;

    TCCR5A = (1 << WGM51) | (0 << WGM50) | (1 << COM5A1) | (0 << COM5A0);
    TCCR5B = (1 << WGM53) | (1 << WGM52) | (0 << CS52) | (1 << CS51) | (0 << CS50);

    ICR4 = TOP_VALUE;

    TCCR4A = (1 << WGM41) | (0 << WGM40) | (1 << COM4A1) | (0 << COM4A0);
    TCCR4B = (1 << WGM43) | (1 << WGM42) | (0 << CS42) | (1 << CS41) | (0 << CS40);
}

void init_test(void)
{
    // Display pinnen als output
    DDRH |= (1 << SDI_BIT) | (1 << SFTCLK_BIT);
    DDRG |= (1 << LCHCLK_BIT);

    // Timers en poorten resetten
    PORTG &= ~(1 << LCHCLK_BIT);
}

void init_timer(void) // timer 0.1 sec
{
    TCNT2 = RESET_VALUE_TIMER1;
    TCCR2A = 0;
    TCCR2B = (1 << CS12)|(0 << CS11)|(0 << CS10);
}

void init_function(void)
{
    init_ultrasoon_sensor();
    init_infrarood_sensor();
    init_knopjes();
    init_led();
    init_h_brug_dual();
    init_noodstop();
    init_timer_PWM();
    init_timer();
    init_test();
}

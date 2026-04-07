#include <avr/io.h>
#include <util/delay.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "programma_keuze.h"

uint16_t ultrasoonAfstand_R(void)
{
    // 1. Trigger
    ULTRASOON_TRIGGER_R_PORT &= ~(1 << ULTRASOON_TRIGGER_R);
    ULTRASOON_TRIGGER_R_PORT |= (1 << ULTRASOON_TRIGGER_R); _delay_us(10);
    ULTRASOON_TRIGGER_R_PORT &= ~(1 << ULTRASOON_TRIGGER_R);

    // 2. Wacht op echo
    uint32_t timeout = 10000;
    while (!(ULTRASOON_ECHO_R_PIN & (1 << ULTRASOON_ECHO_R)) && timeout--);
    if (timeout == 0) return 999;

    // 3. Timer starten (prescaler 8)
    TCNT1 = 0;
    TCCR1B = (1 << CS11);

    // 4. Wachten op einde echo
    while (ULTRASOON_ECHO_R_PIN & (1 << ULTRASOON_ECHO_R) && TCNT1 < OVERFLOW);
    TCCR1B = 0;

    // 5. Bereken afstand
    uint16_t distance = TCNT1 * 0.008575;

    // 6. Return waarde
    return distance;
}

uint16_t ultrasoonAfstand_L(void)
{
    // 1. Trigger
    ULTRASOON_TRIGGER_L_PORT &= ~(1 << ULTRASOON_TRIGGER_L); //_delay_us(2);
    ULTRASOON_TRIGGER_L_PORT |= (1 << ULTRASOON_TRIGGER_L); _delay_us(10);
    ULTRASOON_TRIGGER_L_PORT &= ~(1 << ULTRASOON_TRIGGER_L);

    // 2. Wacht op start echo
    uint32_t timeout = 10000;
    while(!(ULTRASOON_ECHO_L_PIN & (1 << ULTRASOON_ECHO_L)) && timeout--);
    if(timeout == 0) return 999; // Foutmelding

    // 3. Start timer (Prescaler 8 -> 1 tick = 0.5us)
    TCNT1 = 0;
    TCCR1B = (1 << CS11);

    // 4. Wacht op einde echo
    while((ULTRASOON_ECHO_L_PIN & (1 << ULTRASOON_ECHO_L)) && TCNT1 < OVERFLOW);
    TCCR1B = 0; // Stop timer

    // 5. Bereken: ticks * 0.5us * 0.0343 / 2
    uint16_t distance = TCNT1 * 0.008575;

    // 6. Return waarde
    return distance;
}

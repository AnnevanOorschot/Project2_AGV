#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "programma_keuze.h"
#include <util/delay.h>

int programma_keuze(void)
{
    init_function();
    enum programma {startUp, rechtdoor, keren_R, keren_L, pakketTellen, parkour};
    enum programma programma = startUp;
    int pressed = 1;
    int keuzeGemaakt = 0;
    while (keuzeGemaakt == 0)
    {
        if (!(KNOP_1_PIN & (1 << KNOP_1)) && pressed == 0)                              // knop 1 --> rechtdoor
        {
            programma = rechtdoor;
            pressed = 1;
            _delay_ms(5);
            PORTB &= ~(1 << PB7);
            PORTB |= (1 << PB6);
            PORTB |= (1 << PB5);
        }
        if (!(KNOP_2_PIN & (1 << KNOP_2)) && pressed == 0)                              // knop 2 --> keren R
        {
            programma = keren_R;
            pressed = 1;
            _delay_ms(5);
            PORTB &= ~(1 << PB6);
            PORTB |= (1 << PB7);
            PORTB |= (1 << PB5);
        }
        if (!(KNOP_3_PIN & (1 << KNOP_3)) && pressed == 0)                              // knop 3 --> keren L
        {
            programma = keren_L;
            pressed = 1;
            _delay_ms(5);
            PORTB &= ~(1 << PB5);
            PORTB |= (1 << PB7);
            PORTB |= (1 << PB6);
        }
        if (!(KNOP_4_PIN & (1 << KNOP_4)) && pressed == 0)                              // knop 4 --> pakket detectie
        {
            programma = pakketTellen;
            pressed = 1;
            _delay_ms(5);
        }
        if (!(KNOP_5_PIN & (1 << KNOP_5)) && pressed == 0)                              // knop 5 --> parkour
        {
            programma= parkour;
            pressed = 1;
            _delay_ms(5);
        }
        if (!(KNOP_6_PIN & (1 << KNOP_6)) && !(programma == startUp))      // knop 6 --> start programma
        {
            keuzeGemaakt = 1;
        }
        if (((KNOP_1_PIN & (1 << KNOP_1))||(KNOP_2_PIN & (1 << KNOP_2))||(KNOP_3_PIN & (1 << KNOP_3))||(KNOP_4_PIN & (1 << KNOP_4))||(KNOP_5_PIN & (1 << KNOP_5))) && pressed == 1)
        {
            pressed = 0;
            _delay_ms(5);
        }
    }
    return programma;
}



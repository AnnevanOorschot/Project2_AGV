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
    enum programma {startUp, rechtdoor, keren_L, keren_R, pakketTellen, parkour};
    enum programma programma = startUp;
    int pressed = FALSE;
    int keuzeGemaakt = FALSE;
    while (keuzeGemaakt == FALSE)
    {
        if (!(KNOP_1_PIN & (1 << KNOP_1)) && pressed == FALSE)                              /// knop 1 --> RECHTDOOR
        {
            programma = rechtdoor;
            pressed = TRUE;
            _delay_ms(5); //debounce
        }
        if (!(KNOP_2_PIN & (1 << KNOP_2)) && pressed == FALSE)                              /// knop 2 --> KEREN L
        {
            programma = keren_L;
            pressed = TRUE;
            _delay_ms(5); //debounce
        }
        if (!(KNOP_3_PIN & (1 << KNOP_3)) && pressed == FALSE)                              /// knop 3 --> KEREN R
        {
            programma = keren_R;
            pressed = TRUE;
            _delay_ms(5); //debounce
        }
        if (!(KNOP_4_PIN & (1 << KNOP_4)) && pressed == FALSE)                              /// knop 4 --> PAKKET TELLEN
        {
            programma = pakketTellen;
            pressed = TRUE;
            _delay_ms(5); //debounce
        }
        if (!(KNOP_5_PIN & (1 << KNOP_5)) && pressed == FALSE)                              /// knop 5 --> PARCOURSE
        {
            programma= parkour;
            pressed = TRUE;
            _delay_ms(5); //debounce
        }
        if (!(KNOP_6_PIN & (1 << KNOP_6)) && !(programma == startUp))                       /// knop 6 --> START PROGRAMMA
        {
            keuzeGemaakt = TRUE;
            _delay_ms(5); //debounce
        }
        if (((KNOP_1_PIN & (1 << KNOP_1))||(KNOP_2_PIN & (1 << KNOP_2))||(KNOP_3_PIN & (1 << KNOP_3))||(KNOP_4_PIN & (1 << KNOP_4))||(KNOP_5_PIN & (1 << KNOP_5))) && (pressed == TRUE))
        {
            pressed = FALSE;
            _delay_ms(5); //debounce
        }
    }
    return programma;
}



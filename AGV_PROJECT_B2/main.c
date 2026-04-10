/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "programma_keuze.h"
#include "test_func.h"
#include "module.h"

#define RECHTDOOR   1
#define KERENR  2
#define KERENL  3
#define PAKKETDETECTIE  4
#define PARKOUR 5
#define STARTUP 0



int main(void)
{
    init_function();
    blokjes_stop(5, 1);
    INFRAROOD_MODULE_ENABLE_L_PORT |= (1 << INFRAROOD_MODULE_ENABLE_L);
    INFRAROOD_MODULE_ENABLE_R_PORT |= (1 << INFRAROOD_MODULE_ENABLE_R);
    //padNavigeren(RECHTS);
    /*
    switch(programma_keuze())
        {//RECHTS
        case rechtdoor:
            {
                padNavigeren(RECHTS);
                break;
            }

        case keren_R:
            {

                padNavigeren(RECHTS);
                keren(RECHTS);
                padNavigeren(LINKS);
                break;
            }
        case keren_L:
            {
                padNavigeren(LINKS);
                keren(LINKS);
                padNavigeren(RECHTS);
                break;
            }
        case pakketTellen:
            {
                INFRAROOD_MODULE_ENABLE_R_PORT |= (1 << INFRAROOD_MODULE_ENABLE_R);
                INFRAROOD_MODULE_ENABLE_L_PORT |= (1 << INFRAROOD_MODULE_ENABLE_L);
                blokjes_stop(5, 1);
                //pakketDetectie(SET, 5);
                padNavigeren(RECHTS);
                break;
            }
        case parkour:
            {
                INFRAROOD_MODULE_ENABLE_R_PORT |= (1 << INFRAROOD_MODULE_ENABLE_R);
                INFRAROOD_MODULE_ENABLE_L_PORT |= (1 << INFRAROOD_MODULE_ENABLE_L);
                blokjes_stop(15,1);
                //pakketDetectie(SET, 15);
                padNavigeren(RECHTS);
                keren(RECHTS);
                padNavigeren(LINKS);
                keren(LINKS);
                padNavigeren(RECHTS);
                break;
            }
        }
    */
    while(1)
    {

    }

    return 0;
}




void OPSLAG(void)
{
        /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

        //padNavigeren();
        /*afstand_L = ultrasoonAfstand_L();
        afstand_R = ultrasoonAfstand_R();
        if (test_tick++ > 50)
        {
            if (afstand_L > afstand_R) diffAfstand = afstand_L - afstand_R;
            else if (afstand_R >= afstand_L) diffAfstand = afstand_R - afstand_L;
            test_tick = 0;
        }

        print_waarde(diffAfstand);

        while(1)
    {
        LED_1_PORT |= (1 << LED_1);
            count2++;
        if (TIFR1 & (1 << TOV1))
        {
            if (++test_count == 100)
            {
                PORTB &= ~(1 << PB7);
                PORTB &= ~(1 << PB6);
                PORTB &= ~(1 << PB5);
                PORTB &= ~(1 << PB4);
                TIFR1 = (1 << TOV1);
                break;
            }
            TCNT1 = RESET_VALUE_TIMER1;
            TIFR1 = (1 << TOV1);
        }
            print_waarde(count2);
    }
    while(1)
    {
        while(temp == 0)
        {
            print_waarde(test_count);
            if (TIFR1 & (1 << TOV1))
            {
                temp = 1;
                //LED_1_PORT &= ~(1 << LED_1);
                TIFR1 = (1 << TOV1);
            }
        }
        while(temp == 1)
        {
            print_waarde(count2);
            if (TIFR1 & (1 << TOV1))
            {
                temp = 0;
                //LED_1_PORT |= (1 << LED_1);
                TIFR1 = (1 << TOV1);
            }
        }
    }*/
}

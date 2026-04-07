/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "programma_keuze.h"

//ISR(TIMER1_OVF_vect)
//{
//    TCNT1 = 34286;
//}

int main(void)
{

    // Insert code
    init_function();
    motor_L(1.0);
    motor_R(1.0);
    motor_config(VOORUIT,LINKS);
    int test_count = 0;
    int temp = 0;
    int count2 = 0;


    while(1)
    {
        /*LED_2_PORT |= (1 << LED_2);
            count2++;
        if (TIFR1 & (1 << TOV1))
        {
            if (++test_count == 1)
            {
                LED_3_PORT |= (1 << LED_3);
                TIFR1 = (1 << TOV1);
                break;
            }
            TIFR1 = (1 << TOV1);
        }
            print_waarde(count2);*/


    }
    while(1)
    {
        while(temp == 0)
        {
            print_waarde(test_count);
            if (TIFR1 & (1 << TOV1))
            {
                temp = 1;
                LED_2_PORT &= ~(1 << LED_2);
                TIFR1 = (1 << TOV1);
            }
        }
        while(temp == 1)
        {
            print_waarde(count2);
            if (TIFR1 & (1 << TOV1))
            {
                temp = 0;
                LED_2_PORT |= (1 << LED_2);
                TIFR1 = (1 << TOV1);
            }
        }
    }
    return 0;
}




void OPSLAG(void)
{
    /*switch (programma)
        {
        case rechtdoor:
            {
                //volgorde van toestanden ...
                break;
            }

        case keren_R:
            {
                //volgorde van toestanden ...
                break;
            }
        case keren_L:
            {
                //volgorde van toestanden ...
                break;
            }
        case pakketDetectie:
            {
                //volgorde van toestanden ...
                break;
            }
        case parkour:
            {
                //volgorde van toestanden ...
                break;
            }
        }*/

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

        print_waarde(diffAfstand);*/
}

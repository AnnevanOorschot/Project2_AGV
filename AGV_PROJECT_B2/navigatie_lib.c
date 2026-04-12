#include <avr/io.h>
#include <util/delay.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "test_func.h"

float percentageSteering_R(int temp) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < temp)  percentageAfwijking = 0;
    else percentageAfwijking = (helftPadBreedte - temp)/helftPadBreedte;
    return percentageAfwijking;
}

float percentageSteering_L(int temp) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < temp)  percentageAfwijking = 0;
    else percentageAfwijking = (helftPadBreedte - temp)/helftPadBreedte;
    return percentageAfwijking;
}

void padNavigeren(int kant)
{
    if (kant == LINKS)  ///TEST
    {
        LED_1_PORT &= ~(1 << LED_1);
        LED_2_PORT &= ~(1 << LED_2);
    }
    int wandenWeg = 0;
    static unsigned int diffAfstand = 0;
    static unsigned int afstandL = 0;
    static unsigned int afstand_R = 0;
    //int wand = kant;
    motor_config(VOORUIT, LINKS);
    motor_config(VOORUIT, RECHTS);

    motor_L(1.0);
    motor_R(1.0);
    while (wandenWeg < 2)
    {
        afstandL = ultrasoonAfstand_L();
        afstandL = ultrasoonAfstand_L();
        afstand_R = ultrasoonAfstand_R();
        print_waarde(afstandL);

        if ((ultrasoonAfstand_R() > VERWEG) || (ultrasoonAfstand_L() > VERWEG) /*&& (wand == RECHTS)*/) wandenWeg++;
        //else if ((ultrasoonAfstand_L() > VERWEG) /*&& (wand == LINKS)*/) wandenWeg++;
        else
        {
            wandenWeg = 0;
            if (afstandL > afstand_R)
            {
                diffAfstand = afstandL - afstand_R;
                motor_L(1.0);
                motor_R(percentageSteering_R(diffAfstand));
            }

            if (afstand_R > afstandL)
            {
                diffAfstand = afstand_R - afstandL;
                motor_L(percentageSteering_L(diffAfstand));
                motor_R(1.0);
            }
        }
    }
}


void keren(int richting)
{
    int count = 0;
    int kant = richting;
    if (kant == RECHTS)
    {
        motor_L(1.7);
        motor_R(FACTOR_KEREN);
    }

    else if (kant == LINKS)
    {
        motor_L(FACTOR_KEREN);
        motor_R(1.7);
    }

    while (1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 38) {break;}
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER1;
        }
    }
    motor_L(0);
    motor_R(0);
}

void kerenR(void)
{
    int teller = 0;
    int count = 0;
    int temp = 0;
    while(temp == 0)
    {
    TCNT3 = RESET_VALUE_TIMER1;
    TCCR3A = 0;
    TCCR3B = (1 << CS32)|(0 << CS31)|(0 << CS30);
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    motor_L(0);
    motor_R(1);

    count = 0;
    while(1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 5)
            {
                break;
            }
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER1;
        }
    }
    motor_L(1);
    motor_R(1);

    TCNT2 = 6;
    count = 0;
    while (1)
    {
        if (TIFR2 & (1 << TOV2))
        {
            if (++count >= 400)     ///WP COUNT -> 300
            {
                break;
            }
            TIFR2 = (1 << TOV2);
            TCNT2 = 6;
        }
    }
    teller++;
    if (ultrasoonAfstand_L() < 20) {temp = 1;}
    //if (ultrasoonAfstand_R() < 20) {temp = 1;}
    }
}

void kerenLKlein(void)
{
    int teller = 0;
    int count = 0;
    int temp = 0;
    while(temp == 0)
    {
    TCNT3 = RESET_VALUE_TIMER1;
    TCCR3A = 0;
    TCCR3B = (1 << CS32)|(0 << CS31)|(0 << CS30);
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    motor_L(1);
    motor_R(0);

    count = 0;
    while(1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 5)
            {
                break;
            }
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER1;
        }
    }
    motor_L(1);
    motor_R(1);

    TCNT2 = 6;
    count = 0;
    while (1)
    {
        if (TIFR2 & (1 << TOV2))
        {
            if (++count >= 400)     ///WP COUNT -> 300
            {
                break;
            }
            TIFR2 = (1 << TOV2);
            TCNT2 = 6;
        }
    }
    teller++;
    //if (ultrasoonAfstand_L() < 20) {temp = 1;}
    if (ultrasoonAfstand_R() < 20) {temp = 1;}
    }
}

void kerenLGroot(void)
{
    int teller = 0;
    int count = 0;
    int temp = 0;
    while(temp == 0)
    {
    TCNT3 = RESET_VALUE_TIMER1;
    TCCR3A = 0;
    TCCR3B = (1 << CS32)|(0 << CS31)|(0 << CS30);
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    motor_L(1);
    motor_R(0);

    count = 0;
    while(1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 5)
            {
                break;
            }
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER1;
        }
    }
    motor_L(1);
    motor_R(1);

    TCNT2 = 6;
    count = 0;
    while (1)
    {
        if (TIFR2 & (1 << TOV2))
        {
            if (++count >= 350)     ///WP COUNT -> 350
            {
                break;
            }
            TIFR2 = (1 << TOV2);
            TCNT2 = 6;
        }
    }
    teller++;
    //if (ultrasoonAfstand_L() < 20) {temp = 1;}
    if (ultrasoonAfstand_R() < 20) {temp = 1;}
    }
}

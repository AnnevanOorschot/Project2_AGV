#include <avr/io.h>
#include <util/delay.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"

//PWM van de motor R bijstellen om in het midden van het pad te rijden
float percentageSteering_R(int diffAfstand)
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < diffAfstand)  percentageAfwijking = 0;
    else percentageAfwijking = (helftPadBreedte - diffAfstand)/helftPadBreedte;
    return percentageAfwijking;
}

//PWM van de motor L bijstellen om in het midden van het pad te rijden
float percentageSteering_L(int diffAfstand)
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < diffAfstand)  percentageAfwijking = 0;
    else percentageAfwijking = (helftPadBreedte - diffAfstand)/helftPadBreedte;
    return percentageAfwijking;
}

//functie om in het midden van het pad te blijven rijden
void padNavigeren(void)
{
    static unsigned int diffAfstand = 0;
    static unsigned int afstandL = 0;
    static unsigned int afstandR = 0;
    int wandenWeg = 0;
    int count = 0;

    motor_L(1.0);
    motor_R(1.0);
    while (wandenWeg < 2)   //kijken of de wanden twee keer niet gedetecteerd worden
    {
        afstandL = ultrasoonAfstand_L();
        afstandR = ultrasoonAfstand_R();

        if ((ultrasoonAfstand_R() > VERWEG) || (ultrasoonAfstand_L() > VERWEG)) wandenWeg++;    //wanden worden niet gedetecteerd
        else
        {
            wandenWeg = 0;
            if (afstandL > afstandR)
            {
                diffAfstand = afstandL - afstandR;
                motor_L(1.0);
                motor_R(percentageSteering_R(diffAfstand));
            }

            if (afstandR > afstandL)
            {
                diffAfstand = afstandR - afstandL;
                motor_L(percentageSteering_L(diffAfstand));
                motor_R(1.0);
            }
        }
    }
    motor_R(1.0);
    motor_L(1.0);

    //voor bij het einde van het pad doorrijden
    TCNT3 = RESET_VALUE_TIMER3;
    TCCR3A = 0;
    TCCR3B = (1 << CS32)|(0 << CS31)|(0 << CS30);
    LED_1_PORT &= ~(1 << LED_1);
    while (1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 6) {break;}
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER3;
        }
    }
    LED_2_PORT &= ~(1 << LED_2);
}

//functie voor het keren naar rechts
void kerenR(void)
{
    int teller = 0;
    int count = 0;
    int temp = 0;
    while(temp == 0)
    {
    TCNT3 = RESET_VALUE_TIMER3;
    TCCR3A = 0;
    TCCR3B = (1 << CS32)|(0 << CS31)|(0 << CS30);
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    motor_L(0);
    motor_R(1);

    count = 0;

    //timers om bij te sturen
    while(1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 5)
            {
                break;
            }
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER3;
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
            if (++count >= 400)
            {
                break;
            }
            TIFR2 = (1 << TOV2);
            TCNT2 = 6;
        }
    }
    teller++;
    if (ultrasoonAfstand_L() < 20) {temp = 1;}
    }
}

//functie om te keren naar links bij een kleine bocht
void kerenLKlein(void)
{
    int teller = 0;
    int count = 0;
    int temp = 0;
    while(temp == 0)
    {
    TCNT3 = RESET_VALUE_TIMER3;
    TCCR3A = 0;
    TCCR3B = (1 << CS32)|(0 << CS31)|(0 << CS30);
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    motor_L(1);
    motor_R(0);

    count = 0;

    //timer om bij te sturen
    while(1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 5)
            {
                break;
            }
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER3;
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

//functie om te keren naar links bij een grote bocht
void kerenLGroot(void)
{
    int teller = 0;
    int count = 0;
    int temp = 0;
    while(temp == 0)
    {
    TCNT3 = RESET_VALUE_TIMER3;
    TCCR3A = 0;
    TCCR3B = (1 << CS32)|(0 << CS31)|(0 << CS30);
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    motor_L(1);
    motor_R(0);

    count = 0;
    //timers om bij te sturen
    while(1)
    {
        if (TIFR3 & (1 << TOV3))
        {
            if (++count >= 5)
            {
                break;
            }
            TIFR3 = (1 << TOV3);
            TCNT3 = RESET_VALUE_TIMER3;
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

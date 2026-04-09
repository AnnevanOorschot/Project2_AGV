#include <avr/io.h>
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
    static int wandenWeg = 0;
    static int diffAfstand = 0;
    static int afstand_L = 0;
    static int afstand_R = 0;
    static int meet_tick = 0;

    motor_config(VOORUIT, LINKS);
    motor_config(VOORUIT, RECHTS);


    motor_L(1.0);
    motor_R(1.0);

    while (wandenWeg <= 5)
    {
        print_waarde(afstand_R);
        afstand_L = ultrasoonAfstand_L();
        afstand_R = ultrasoonAfstand_R();
        if ((ultrasoonAfstand_R() > VERWEG) && (kant == RECHTS)) wandenWeg++;
        else if ((ultrasoonAfstand_L() > VERWEG) && (kant == LINKS)) wandenWeg++;
        else
        {
            wandenWeg = 0;

            if (afstand_L > afstand_R)
            {
                diffAfstand = afstand_L - afstand_R;
                motor_L(1.0);
                motor_R(percentageSteering_R(diffAfstand));
            }

            if (afstand_R > afstand_L)
            {
                diffAfstand = afstand_R - afstand_L;
                motor_L(percentageSteering_L(diffAfstand));
                motor_R(1.0);
            }
            //else;
            //{
            //    diffAfstand = 0;
            //    motor_L(1.0);
            //    motor_R(1.0);
            //}

            if (afstand_R > VERWEG || afstand_L > VERWEG) diffAfstand = 999;
        }
    }
}


void keren(int richting)
{
    int count = 0;
    if (richting == RECHTS)
    {
        motor_L(1.0);
        motor_R(FACTOR_KEREN);
    }

    else if (richting == LINKS)
    {
        motor_L(FACTOR_KEREN);
        motor_R(1.0);
    }

    while (1)
    {
        if (TIFR1 & (1 << TOV1))
        {
            if (++count >= 38) {break;}
            TIFR1 = (1 << TOV1);
            TCNT1 = RESET_VALUE_TIMER1;
        }
    }
}

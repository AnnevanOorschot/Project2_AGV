#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"


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

void padNavigeren(void)
{
    static int wandenWeg = 0;
    static int diffAfstand = 0;
    static int afstand_L = 0;
    static int afstand_R = 0;
    static int meet_tick = 0;
    while (wandenWeg <= 5)
    {
        afstand_L = ultrasoonAfstand_L();
        afstand_R = ultrasoonAfstand_R();
        //if (ultrasoonAfstand_R() < 100 && ultrasoonAfstand_L() < 100) wandenWeg++;
        //else

        {
            if (meet_tick++ > 15 )
            {
            //wandenWeg = 0;

            //motor_R(percentageSteering_R());
            //motor_L(percentageSteering_L());

            if (afstand_L > afstand_R)
            {
                diffAfstand = afstand_L - afstand_R;
                motor_L(1.0);
                motor_R(percentageSteering_R(diffAfstand));
            }

            else if (afstand_R > afstand_L)
            {
                diffAfstand = afstand_R - afstand_L;
                motor_L(percentageSteering_L(diffAfstand));
                motor_R(1.0);
            }
            else
            {
                diffAfstand = 0;
                motor_L(1.0);
                motor_R(1.0);
            }

            if (afstand_R > 100 || afstand_L > 100) diffAfstand = 999;
            meet_tick = 0;
            }
        }
    }
}




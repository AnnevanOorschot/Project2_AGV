#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"

int diffUltrasoon(void)
{
    return (ultrasoonAfstand_R() - ultrasoonAfstand_L());
}

float percentageSteering_R(int diffAfstand)
{
    static float helftPadBreedte = HALF_PAD
    float percentageAfwijking = (helftPadBreedte - diffAfstand)/helftPadBreedte;
    return percentageAfwijking;
}

float percentageSteering_L(int diffAfstand)
{
    static float helftPadBreedte = HALF_PAD
    float percentageAfwijking = (helftPadBreedte + diffAfstand)/helftPadBreedte;
    return percentageAfwijking;
}


void padNavigeren(void)
{
    while (ultrasoonAfstand_R() < 100 || ultrasoonAfstand_L() < 100)
    {
        motor_R(percentageSteering_R());
        motor_L(percentageSteering_L());
    }
}


#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"

//int diffUltrasoon(void)
//{
//    return (ultrasoonAfstand_R() - ultrasoonAfstand_L());
//}

float percentageSteering_R(void) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    float diffUltrasoon = (ultrasoonAfstand_R() - ultrasoonAfstand_L());
    float percentageAfwijking = (helftPadBreedte - diffUltrasoon)/helftPadBreedte;
    return percentageAfwijking;
}

float percentageSteering_L(void) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    float diffUltrasoon = (ultrasoonAfstand_R() - ultrasoonAfstand_L());
    float percentageAfwijking = (helftPadBreedte + diffUltrasoon)/helftPadBreedte;
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


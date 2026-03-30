/*
 */

#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "programma_keuze.h"

int main(void)
{

    // Insert code
    init_function();
    enum programma programma = programma_keuze();
    while(1)
    {
        switch (programma)
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
        }
    }
    return 0;
}

#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "programma_keuze.h"

int programma_keuze(void)
{
    enum programma {startUp, rechtdoor, keren_R, keren_L, pakketDetectie, parkour};
    enum programma programma = startUp;
    while (1)
    {
        if (!(KNOP_1_PIN & (1 << KNOP_1))) {programma = rechtdoor;}             // knop 1 --> rechtdoor
        if (!(KNOP_2_PIN & (1 << KNOP_2))) {programma = keren_R;}               // knop 2 --> keren R
        if (!(KNOP_3_PIN & (1 << KNOP_3))) {programma = keren_L;}               // knop 3 --> keren L
        if (!(KNOP_4_PIN & (1 << KNOP_4))) {programma = pakketDetectie;}        // knop 4 --> pakket detectie
        if (!(KNOP_5_PIN & (1 << KNOP_5))) {programma= parkour;}                // knop 5 --> parkour
        if (!(KNOP_6_PIN & (1 << KNOP_6)) && !programma== startUp) {break;}     // knop 6 --> start programma
    }
    return programma;
}


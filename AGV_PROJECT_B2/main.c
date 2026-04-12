/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "programma_keuze.h"
#include "module.h"





int main(void)
{
    //initialisatie
    init_function();

    //programma kiezen door op een van de knoppen AGV te drukken en hem dan te starten
    switch(programma_keuze())
    {
    case rechtdoor:     //rechdoor opdracht
    {
        padNavigeren();
        break;
    }
    case keren_R:       //keer opdracht naar RECHTS
    {
        padNavigeren();
        kerenR();
        padNavigeren();
        break;
    }
    case keren_L:       //keer opdracht naar LINKS
    {
        padNavigeren();
        kerenLKlein();
        padNavigeren();
        break;
    }
    case pakketTellen:  //pakketten tellen opdracht tot 5 Blokjes
    {
        blokjes_gedetecteerd(2);
        INFRAROOD_MODULE_ENABLE_R_PORT |= (1 << INFRAROOD_MODULE_ENABLE_R);
        blokjes_gedetecteerd(1);
        INFRAROOD_MODULE_ENABLE_L_PORT |= (1 << INFRAROOD_MODULE_ENABLE_L);
        blokjes_stop(BLOKDETECTIE, SET);
        padNavigeren();
        break;
    }
    case parkour:       //Parkour tot 15 blokjes
    {
        blokjes_gedetecteerd(2);
        INFRAROOD_MODULE_ENABLE_R_PORT |= (1 << INFRAROOD_MODULE_ENABLE_R);
        blokjes_gedetecteerd(1);
        INFRAROOD_MODULE_ENABLE_L_PORT |= (1 << INFRAROOD_MODULE_ENABLE_L);
        blokjes_stop(PAROURBLOKJES, SET);
        padNavigeren();

        INFRAROOD_MODULE_ENABLE_R_PORT &= ~(1 << INFRAROOD_MODULE_ENABLE_R);
        INFRAROOD_MODULE_ENABLE_L_PORT &= ~(1 << INFRAROOD_MODULE_ENABLE_L);
        kerenR();

        blokjes_gedetecteerd(2);
        INFRAROOD_MODULE_ENABLE_R_PORT |= (1 << INFRAROOD_MODULE_ENABLE_R);
        blokjes_gedetecteerd(1);
        INFRAROOD_MODULE_ENABLE_L_PORT |= (1 << INFRAROOD_MODULE_ENABLE_L);
        padNavigeren();

        INFRAROOD_MODULE_ENABLE_R_PORT &= ~(1 << INFRAROOD_MODULE_ENABLE_R);
        INFRAROOD_MODULE_ENABLE_L_PORT &= ~(1 << INFRAROOD_MODULE_ENABLE_L);
        kerenLGroot();

        blokjes_gedetecteerd(2);
        INFRAROOD_MODULE_ENABLE_R_PORT |= (1 << INFRAROOD_MODULE_ENABLE_R);
        blokjes_gedetecteerd(1);
        INFRAROOD_MODULE_ENABLE_L_PORT |= (1 << INFRAROOD_MODULE_ENABLE_L);
        padNavigeren();
        break;
    }
    }
    //KLAAR
    while(1);
    return 0;
}

/*
 */

#include <avr/io.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"

int main(void)
{

    // Insert code
    init_function();
    while(1)
    {
        padNavigeren();
    }
    return 0;
}

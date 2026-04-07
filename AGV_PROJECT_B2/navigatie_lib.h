#ifndef NAVIGATIE_LIB_H_INCLUDED
#define NAVIGATIE_LIB_H_INCLUDED

#define HALF_PAD        15.00

//int diffUltrasoon(void);
float percentageSteering_R(int temp);
float percentageSteering_L(int temp);
void padNavigeren(void);

#endif // NAVIGATIE_LIB_H_INCLUDED

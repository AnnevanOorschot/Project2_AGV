#ifndef NAVIGATIE_LIB_H_INCLUDED
#define NAVIGATIE_LIB_H_INCLUDED

#define HALF_PAD        15.00
#define FACTOR_KEREN    0.8 //0.464285714286
#define VERWEG          30

//int diffUltrasoon(void);
float percentageSteering_R(int diffAfstand);
float percentageSteering_L(int diffAfstand);
void padNavigeren(void);
void kerenLKlein(void);
void kerenLGroot(void);
void kerenR(void);

#endif // NAVIGATIE_LIB_H_INCLUDED

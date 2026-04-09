#ifndef MOTOR_LIB_H_INCLUDED
#define MOTOR_LIB_H_INCLUDED

#define PWM TOP_VALUE*0.5
enum richting {RECHTS, LINKS};
enum motor_actie {VOORUIT, ACHTERUIT, REMMEN};

void motor_R(float factor);
void motor_L(float factor);
void motor_config(int mode, int kant);

#endif // MOTOR_LIB_H_INCLUDED

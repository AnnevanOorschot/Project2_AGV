#ifndef SENSOR_LIB_H_INCLUDED
#define SENSOR_LIB_H_INCLUDED

uint16_t ultrasoonAfstand_R(void);
uint16_t ultrasoonAfstand_L(void);

#define TIMEOUT     10000
#define TICKFACTOR  0.008575

#endif // SENSOR_LIB_H_INCLUDED

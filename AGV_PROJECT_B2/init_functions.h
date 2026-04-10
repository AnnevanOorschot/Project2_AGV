#ifndef INIT_FUNCTIONS_H_INCLUDED
#define INIT_FUNCTIONS_H_INCLUDED

// ULTRASOON //
#define ULTRASOON_ECHO_R                PC7
#define ULTRASOON_ECHO_R_DDR            DDRC
#define ULTRASOON_ECHO_R_PIN            PINC

#define ULTRASOON_TRIGGER_R             PC6
#define ULTRASOON_TRIGGER_R_DDR         DDRC
#define ULTRASOON_TRIGGER_R_PORT        PORTC

#define ULTRASOON_ECHO_L                PA6
#define ULTRASOON_ECHO_L_DDR            DDRA
#define ULTRASOON_ECHO_L_PIN            PINA

#define ULTRASOON_TRIGGER_L             PA7
#define ULTRASOON_TRIGGER_L_DDR         DDRA
#define ULTRASOON_TRIGGER_L_PORT        PORTA

// INFRAROOD //
#define INFRAROOD_AGV_R                 PD2
#define INFRAROOD_AGV_R_DDR             DDRD
#define INFRAROOD_AGV_R_PIN             PIND

#define INFRAROOD_AGV_L                 PD1
#define INFRAROOD_AGV_L_DDR             DDRD
#define INFRAROOD_AGV_L_PIN             PIND

#define INFRAROOD_MODULE_R              PE5
#define INFRAROOD_MODULE_R_DDR          DDRE
#define INFRAROOD_MODULE_R_PIN          PINE

#define INFRAROOD_MODULE_ENABLE_R       PC5
#define INFRAROOD_MODULE_ENABLE_R_DDR   DDRC
#define INFRAROOD_MODULE_ENABLE_R_PORT  PORTC

#define INFRAROOD_MODULE_L              PE4
#define INFRAROOD_MODULE_L_DDR          DDRE
#define INFRAROOD_MODULE_L_PIN          PINE

#define INFRAROOD_MODULE_ENABLE_L       PC4
#define INFRAROOD_MODULE_ENABLE_L_DDR   DDRC
#define INFRAROOD_MODULE_ENABLE_L_PORT  PORTC

// KNOPPEN //
#define KNOP_1                          PA0
#define KNOP_1_DDR                      DDRA
#define KNOP_1_PIN                      PINA
#define KNOP_1_PORT                     PORTA

#define KNOP_2                          PA1
#define KNOP_2_DDR                      DDRA
#define KNOP_2_PIN                      PINA
#define KNOP_2_PORT                     PORTA

#define KNOP_3                          PA2
#define KNOP_3_DDR                      DDRA
#define KNOP_3_PIN                      PINA
#define KNOP_3_PORT                     PORTA

#define KNOP_4                          PA3
#define KNOP_4_DDR                      DDRA
#define KNOP_4_PIN                      PINA
#define KNOP_4_PORT                     PORTA

#define KNOP_5                          PA4
#define KNOP_5_DDR                      DDRA
#define KNOP_5_PIN                      PINA
#define KNOP_5_PORT                     PORTA

#define KNOP_6                          PA5
#define KNOP_6_DDR                      DDRA
#define KNOP_6_PIN                      PINA
#define KNOP_6_PORT                     PORTA

// LED //
#define LED_1                           PB2
#define LED_1_DDR                       DDRB
#define LED_1_PORT                      PORTB

// LED module
#define LED_2                           PB1
#define LED_2_DDR                       DDRB
#define LED_2_PORT                      PORTB

// H-BRUG //
#define PWM_R                           PH3     // IPV PL5 --> PH3 voor timer 4
#define PWM_R_DDR                       DDRH
#define PWM_R_PORT                      PORTH

#define PWM_L                           PL3
#define PWM_L_DDR                       DDRL
#define PWM_L_PORT                      PORTL

#define PWM_IN_1                        PL6
#define PWM_IN_1_DDR                    DDRL
#define PWM_IN_1_PORT                   PORTL

#define PWM_IN_2                        PL4
#define PWM_IN_2_DDR                    DDRL
#define PWM_IN_2_PORT                   PORTL

#define PWM_IN_3                        PL2
#define PWM_IN_3_DDR                    DDRL
#define PWM_IN_3_PORT                   PORTL

#define PWM_IN_4                        PL0
#define PWM_IN_4_DDR                    DDRL
#define PWM_IN_4_PORT                   PORTL

// NOODSTOP //
#define NOODSTOP                        PD0
#define NOODSTOP_DDR                    DDRD
#define NOODSTOP_PIN                    PIND

// TEST FUNC //
#define SDI_BIT                         PH5    // Pin 8
#define SFTCLK_BIT                      PH4    // Pin 7
#define LCHCLK_BIT                      PG5    // Pin 4

// OVERIG //

#define TOP_VALUE                   40000UL
#define RESET_VALUE_TIMER1          59286UL

// FUNCTIES //
void init_ultrasoon_sensor(void);
void init_infrarood_sensor(void);
void init_knopjes(void);
void init_led(void);
void init_h_brug_dual(void);
void init_noodstop(void);
void init_function(void);
void init_timer_PWM(void);
void init_timer();
void init_test(void);
void init_display(void);


#endif // INIT_FUNCTIONS_H_INCLUDED

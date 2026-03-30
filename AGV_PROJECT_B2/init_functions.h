#ifndef INIT_FUNCTIONS_H_INCLUDED
#define INIT_FUNCTIONS_H_INCLUDED

// ULTRASOON //
#define ULTRASOON_ECHO_R            PC7
#define ULTRASOON_ECHO_R_DDR        DDRC
#define ULTRASOON_ECHO_R_PIN        PINC

#define ULTRASOON_TRIGGER_R         PC6
#define ULTRASOON_TRIGGER_R_DDR     DDRC
#define ULTRASOON_TRIGGER_R_PORT    PORTC

#define ULTRASOON_ECHO_L            PA6
#define ULTRASOON_ECHO_L_DDR        DDRA
#define ULTRASOON_ECHO_L_PIN        PINA

#define ULTRASOON_TRIGGER_L         PA7
#define ULTRASOON_TRIGGER_L_DDR     DDRA
#define ULTRASOON_TRIGGER_L_PORT    PORTA

// INFRAROOD //
#define INFRAROOD_AGV_R             PD2
#define INFRAROOD_AGV_R_DDR         DDRD
#define INFRAROOD_AGV_R_PIN         PIND

#define INFRAROOD_AGV_L             PD1
#define INFRAROOD_AGV_L_DDR         DDRD
#define INFRAROOD_AGV_L_PIN         PIND

#define INFRAROOD_MODULE_R          PE5
#define INFRAROOD_MODULE_R_DDR      DDRE
#define INFRAROOD_MODULE_R_PIN      PINE

#define INFRAROOD_MODULE_L          PE4
#define INFRAROOD_MODULE_L_DDR      DDRE
#define INFRAROOD_MODULE_L_PIN      PINE

// KNOPPEN //
#define KNOP_1                      PA0
#define KNOP_1_DDR                  DDRA
#define KNOP_1_PIN                  PINA
#define KNOP_1_PORT                 PORTA

#define KNOP_2                      PA1
#define KNOP_2_DDR                  DDRA
#define KNOP_2_PIN                  PINA
#define KNOP_2_PORT                 PORTA

#define KNOP_3                      PA2
#define KNOP_3_DDR                  DDRA
#define KNOP_3_PIN                  PINA
#define KNOP_3_PORT                 PORTA

#define KNOP_4                      PA3
#define KNOP_4_DDR                  DDRA
#define KNOP_4_PIN                  PINA
#define KNOP_4_PORT                 PORTA

#define KNOP_5                      PA4
#define KNOP_5_DDR                  DDRA
#define KNOP_5_PIN                  PINA
#define KNOP_5_PORT                 PORTA

#define KNOP_6                      PA5
#define KNOP_6_DDR                  DDRA
#define KNOP_6_PIN                  PINA
#define KNOP_6_PORT                 PORTA

// LED //
#define LED_1                       PB2
#define LED_1_DDR                   DDRB
#define LED_1_PORT                  PORTB

#define LED_2                       PB1
#define LED_2_DDR                   DDRB
#define LED_2_PORT                  PORTB

#define LED_3                       PB0
#define LED_3_DDR                   DDRB
#define LED_3_PORT                  PORTB

// H-BRUG //
#define PWM_R                       PL5
#define PWM_R_DDR                   DDRL
#define PWM_R_PORT                  PORTL

#define PWM_L                       PL3
#define PWM_L_DDR                   DDRL
#define PWM_L_PORT                  PORTL

#define IN_1                        PL6
#define IN_1_DDR                    DDRL
#define IN_1_PIN                    PORTL

#define IN_2                        PL4
#define IN_2_DDR                    DDRL
#define IN_2_PIN                    PORTL

#define IN_3                        PL2
#define IN_3_DDR                    DDRL
#define IN_3_PIN                    PORTL

#define IN_4                        PL0
#define IN_4_DDR                    DDRL
#define IN_4_PIN                    PORTL

// NOODSTOP //
#define NOODSTOP                    PD0
#define NOODSTOP_DDR                DDRD
#define NOODSTOP_PIN                PIND

// OVERIG //

#define TOP_VALUE                   40000UL

// FUNCTIES //
void init_ultrasoon_sensor(void);
void init_infrarood_sensor(void);
void init_knopjes(void);
void init_led(void);
void init_h_brug_dual(void);
void init_noodstop(void);
void init_function(void);
void init_timer(void);


#endif // INIT_FUNCTIONS_H_INCLUDED

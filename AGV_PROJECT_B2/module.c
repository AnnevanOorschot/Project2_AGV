#include <avr/io.h>
#include <avr/interrupt.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "module.h"
#include "test_func.h"

// Configuratie voor opdrachten
#define OPDRACHT_1_LIM 5    // Eerste opdracht: 5 blokjes
#define OPDRACHT_2_LIM 15   // Tweede opdracht: 15 blokjes
#define SELECT_OPDRACHT OPDRACHT_1_LIM  // Wijzig naar OPDRACHT_2_LIM voor opdracht 2

// Timers en delays
#define STOP_TIME 2000      // 2 seconden stop (ms)
#define BLINK_INTERVAL 500  // Knipper interval (ms)
#define DEBOUNCE_TIME 50    // Debounce tijd voor IR sensoren (ms)

// Globale variabelen (ALLEEN int/unsigned long)
volatile int blokjes_teller = 0;
volatile unsigned long stop_start_tijd = 0;
volatile int in_stop = 0;
volatile int opdracht_voltooid = 0;
volatile unsigned long laatste_blok_tijd = 0;
volatile int bocht_modus = 0;
volatile int led_knipper_state = 0;
volatile unsigned long laatste_blink_tijd = 0;

// 7-segment display waardes (0-9)
const uint8_t digit_patterns[10] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111
};

// === INTERRUPTS: ALLES GEBEUREN HIER! ===
ISR(INT1_vect) { // Links AGV (pin 20)
    ///block_detectie(); niet
}

ISR(INT2_vect) { // Rechts AGV (pin 19)
    ///block_detectie(); niet
}

ISR(INT4_vect) { // Links module (pin 2)
    block_detectie(pakketDetectie(READ_MODE,0));
}

ISR(INT5_vect) { // Rechts module (pin 3)
    block_detectie(pakketDetectie(READ_MODE,0));
}
int millis(void)
{
    return 0;
}
// Centrale block detectie functie (wordt door alle ISR's aangeroepen)
void block_detectie(int modus) {
    if (modus == TRUE)
    {
        if (!in_stop && !bocht_modus && !opdracht_voltooid) {
            unsigned long nu = millis();
            if (nu - laatste_blok_tijd > DEBOUNCE_TIME) {

                // 🚀 ALLES IN ISR:
                blokjes_teller++;                    // 1. Teller ++
                motoren_stop();                      // 2. Motoren STOP
                PORTB |= _BV(PB2);                   // 3. Blauw LED aan (pin 51)
                print_waarde(blokjes_teller);
                //update_7seg_display(blokjes_teller); // 4. Display update
                //motoren_stop();
                wachten(2, SEC);
                //stop_start_tijd = nu;                // 5. 2s timer starten
                //in_stop = 1;                         // 6. Stop modus aan
                //laatste_blok_tijd = nu;              // 7. Debounce reset

                // 8. Check opdracht voltooid
                if (blokjes_teller >= pakketDetectie(READ_OPDRACHT,0)) {
                    opdracht_voltooid = 1;
                }
            }
        }
    }
}



// === 7-SEGMENT DISPLAY ===
void update_7seg_display(int waarde) {
    // Haal cijfers uit waarde (0-9999)
    //int eenheden = waarde % 10;
    //int tientallen = (waarde / 10) % 10;
    //int honderden = (waarde / 100) % 10;
    //int duizenden = (waarde / 1000) % 10;

    // TODO: Pas aan je specifieke 7-seg driver (TM1637?)
    // Voorbeeld voor directe PORTG bediening:
    PORTG = (_BV(PG0) | _BV(PG1)); // Clock/DIO high (vereenvoudigd)
    // Implementeer je display protocol hier
}

// === LED FUNCTIES ===
void blauw_led_aan(void) {
    PORTB |= _BV(PB2);   // Pin 51
}

void blauw_led_uit(void) {
    PORTB &= ~_BV(PB2);  // Pin 51
}

// === MOTOR FUNCTIES ===
void motoren_stop(void) {
    motor_R(0.0);
    motor_L(0.0);
}

void motoren_start(void) {
    motor_R(1);
    motor_L(1);
}

// === KNIPPER FUNCTIE ===
void update_led_knipper(void) {
    unsigned long nu = millis();
    if (nu - laatste_blink_tijd >= BLINK_INTERVAL) {
        if (led_knipper_state == 0) {
            blauw_led_aan();
            led_knipper_state = 1;
        } else {
            blauw_led_uit();
            led_knipper_state = 0;
        }
        laatste_blink_tijd = nu;
    }
}

// === INITIALISATIE ===
void setup_module(void) {
    // Configureer pins
    DDRA |= _BV(PA0)|_BV(PA1)|_BV(PA2)|_BV(PA3)|_BV(PA4)|_BV(PA5); // Knoppen INPUT
    DDRB |= _BV(PB2)|_BV(PB1);      // LEDs OUTPUT
    DDRG |= _BV(PG0)|_BV(PG1);      // 7-seg OUTPUT

    // Interrupt config (falling edge voor IR sensoren)
    EICRA |= _BV(ISC11)|_BV(ISC10)|_BV(ISC21)|_BV(ISC20); // INT1+INT2
    EICRB |= _BV(ISC41)|_BV(ISC40)|_BV(ISC51)|_BV(ISC50); // INT4+INT5
    EIMSK |= _BV(INT1)|_BV(INT2)|_BV(INT4)|_BV(INT5);

    // Start condities
    blauw_led_uit();

    sei(); // Global interrupts AAN
}

// === MAIN LOOP (ALLEEN TIMERS) ===
void loop(void) {
    // 1. Stop timer (2 seconden)
    if (in_stop && !opdracht_voltooid) {
        if (millis() - stop_start_tijd >= STOP_TIME) {
            in_stop = 0;
            blauw_led_uit();
            motoren_start();
        }
    }

    // 2. Opdracht voltooid: knipper LED
    if (opdracht_voltooid) {
        update_led_knipper();
    }

    // 3. Bocht modus extern aansturen (bijv. vanuit navigatie)
    // bocht_modus = 1;  // Tijdens bocht
    // bocht_modus = 0;  // Na bocht
}

/// TOEGEVOEGD ///
int pakketDetectie(int mode, int opdracht)
{
    static int detectie = FALSE;
    static int aantal = 0;
    switch(mode)
    {
    case SET:
        {
            detectie = TRUE;
            aantal = opdracht;
            return 0;
        }
    case READ_MODE:
        {
            return detectie;
            break;
        }
    case READ_OPDRACHT:
        {
            return aantal;
            break;
        }
    }
    return FALSE;
}

void wachten(int num, int factor)
{
    int timerReset = 65536UL - (62500UL/factor);
    int wacht = 1;
    int count = 0;
    TCNT1 = timerReset;
    while (wacht)
    {
        if (TIFR1 & (1 << TOV1))
        {
            if (++count >= num)
            {
                wacht = 0;
            }
            TIFR1 = (1 << TOV1);
            TCNT1 = timerReset;
        }
        motoren_stop();
    }
}

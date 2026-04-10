#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "init_functions.h"
#include "sensor_lib.h"
#include "navigatie_lib.h"
#include "motor_lib.h"
#include "module.h"
#include "test_func.h"


//segment array
const uint8_t segmentMap[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void send_byte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        CLK_LOW();
        if (data & 0x01) DIO_HIGH(); else DIO_LOW();
        _delay_us(50);
        CLK_HIGH();
        _delay_us(50);
        data >>= 1;
    }
    // Wachten op ACK (Acknowledgement)
    CLK_LOW();
    DIO_INPUT();
    _delay_us(50);
    CLK_HIGH();
    _delay_us(50);
    CLK_LOW();
    DIO_OUTPUT();
}

void tm_start() {
    DIO_OUTPUT(); DIO_HIGH(); CLK_HIGH(); _delay_us(50);
    DIO_LOW(); _delay_us(50); CLK_LOW();
}

void tm_stop() {
    CLK_LOW(); DIO_LOW(); _delay_us(50);
    CLK_HIGH(); _delay_us(50); DIO_HIGH();
}

void tm1637_showNumber(uint16_t num) {
    uint8_t digits[4];
    digits[0] = num / 1000;
    digits[1] = (num / 100) % 10;
    digits[2] = (num / 10) % 10;
    digits[3] = num % 10;

    tm_start(); send_byte(0x40); tm_stop(); // Data command (auto increment)
    tm_start(); send_byte(0xC0);            // Start adres (eerste digit)

    uint8_t leadingZero = 1;
    for (int i = 0; i < 4; i++) {
        // Verberg nullen aan het begin, behalve bij het allerlaatste cijfer
        if (i < 3 && digits[i] == 0 && leadingZero) {
            send_byte(0x00);
        } else {
            leadingZero = 0;
            send_byte(segmentMap[digits[i]]);
        }
    }
    tm_stop();
}

int blokjes_gedetecteerd (void) {
    static int aantal = -2; //compenseert voor valse true bij opstarten
    aantal++;
    return (aantal);
}

int blokjes_stop(int taak, int instel) {
    static int blokjes_stoppen = 0;
    if (instel == 1) {
        blokjes_stoppen = taak;
    }

    return (blokjes_stoppen);
}

// infraroodsensor links detecteert blokje
ISR(INT4_vect) {
    int blokjes_stoppen = blokjes_stop(0,0);
    int aantal_blokjes = blokjes_gedetecteerd(); // rekening houden met dat ie aan het begin meteen dit gaat doen!
    //if (aantal_blokjes > 0) {
        tm1637_showNumber(aantal_blokjes);
        motor_R(0);
        motor_L(0);
        volatile int teller = 0;
        if (aantal_blokjes >= blokjes_stoppen) {
            TCNT0 = 0;
            while(1) {
                while (teller < cycles_per_seconde) {
                    if ((TIFR0 & (1 << TOV0))!= 0) {
                        TIFR0 = (1 << TOV0);
                        teller++;
                    }
                }
                LED_2_PORT ^= (1 << LED_2);
                teller = 0;
            }
        }
        else {
            TCNT0 = 0;
            while (teller < 2*cycles_per_seconde) {
                if ((TIFR0 & (1 << TOV0))!= 0) {
                    TIFR0 = (1 << TOV0);
                    teller++;
                    if (teller % (cycles_per_seconde/2) == 0) {
                        LED_2_PORT ^= (1 << LED_2);
                    }
                }
            }
            LED_2_PORT |= (1 << LED_2); // is dit inderdaad uit???
        }
    /*}
    else {
        tm1637_showNumber(0);
    }*/
}


// infraroodsensor rechts detecteert blokje
ISR(INT5_vect) {
    int blokjes_stoppen = blokjes_stop(0,0);
    int aantal_blokjes = blokjes_gedetecteerd(); // rekening houden met dat ie aan het begin meteen dit gaat doen!
    //if (aantal_blokjes > 0) {
        tm1637_showNumber(aantal_blokjes);
        motor_R(0);
        motor_L(0);
        volatile int teller = 0;
        if (aantal_blokjes >= blokjes_stoppen) {
            TCNT0 = 0;
            while(1) {
                while (teller < cycles_per_seconde) {
                    if ((TIFR0 & (1 << TOV0))!= 0) {
                        TIFR0 = (1 << TOV0);
                        teller++;
                    }
                }
                LED_2_PORT ^= (1 << LED_2);
                teller = 0;
            }
        }
        else {
            TCNT0 = 0;
            while (teller < 2*cycles_per_seconde) {
                if ((TIFR0 & (1 << TOV0))!= 0) {
                    TIFR0 = (1 << TOV0);
                    teller++;
                    if (teller % (cycles_per_seconde/2) == 0) {
                        LED_2_PORT ^= (1 << LED_2);
                    }
                }
            }
            LED_2_PORT |= (1 << LED_2); // is dit inderdaad uit???
        }
    /*}
    else {
        tm1637_showNumber(0);
    }*/
}

/*
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
*/

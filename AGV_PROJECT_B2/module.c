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
    //volatile int temp = 0;
    //temp++;
    int blokjes_stoppen = blokjes_stop(0,0);
    int aantal_blokjes = blokjes_gedetecteerd(); // rekening houden met dat ie aan het begin meteen dit gaat doen!
    //if (aantal_blokjes > 0) {
        tm1637_showNumber(aantal_blokjes);
        //tm1637_showNumber(temp);
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
    //volatile int temp = 100;
    //temp++;
    int blokjes_stoppen = blokjes_stop(0,0);
    int aantal_blokjes = blokjes_gedetecteerd(); // rekening houden met dat ie aan het begin meteen dit gaat doen!
    //if (aantal_blokjes > 0) {
        tm1637_showNumber(aantal_blokjes);
        //tm1637_showNumber(temp);
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


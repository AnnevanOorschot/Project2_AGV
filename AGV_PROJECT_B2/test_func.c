#include <avr/io.h>
#include <util/delay.h>
#include "test_func.h"
#include "init_functions.h"



void print_waarde(unsigned int temp)
{
    static unsigned char segmentcodes[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90
    };

    display_segment(segmentcodes[temp % 10], 3); // Eenheden
    _delay_us(5000);

    temp /= 10;
    display_segment(segmentcodes[temp % 10], 2); // Tientallen
    _delay_us(5000);

    temp /= 10;
    display_segment(segmentcodes[temp % 10], 1); // Honderdtallen
    _delay_us(5000);

    temp /= 10;
    display_segment(segmentcodes[temp % 10], 0); // Duizendtallen [segmentcodes[temp % 10], 0]
    _delay_us(250);
}

void display_segment(unsigned char segments, int display_nummer) {
    send_data(segments);              // Welke segmenten aan
    send_data(1 << display_nummer);   // Welk cijfer aan (positie)

    PORTG |= (1 << LCHCLK_BIT);       // Latch pulse
    PORTG &= ~(1 << LCHCLK_BIT);
}

void send_data(unsigned char data) {
    for (unsigned i = 0; i < 8; i++) {
        if (data & 0x80) PORTH |= (1 << SDI_BIT); // MSB first voor dit shield
        else PORTH &= ~(1 << SDI_BIT);

        data <<= 1;
        PORTH |= (1 << SFTCLK_BIT); // Clock pulse
        PORTH &= ~(1 << SFTCLK_BIT);
    }
}

/*void print_turd(void)
{
    display_segment(0x87, 0); // Eenheden
    _delay_us(250);

    display_segment(0xE3, 1); // Tientallen
    _delay_us(250);

    display_segment(0xAF, 2); // Honderdtallen
    _delay_us(250);

    display_segment(0xA1, 3); // Duizendtallen [segmentcodes[temp % 10], 0]
    _delay_us(250);
}*/

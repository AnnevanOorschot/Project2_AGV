#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

void block_detectie(int modus);
void motoren_stop(void);
void motoren_start(void);
void update_led_knipper(void);
void setup_module(void);
int pakketDetectie(int mode, int opdracht);
void wachten(int num, int factor);

#define cycles_per_seconde 61 // 16000000/2^8 = 62500, 62500/1024 = 61

//Display: DIO --> pin 2, CLK --> pin 3. (veranderd naar CLK pin 40 (PG1), DIO pin 41 (PG0))
#define CLK_LOW()    (PORTG &= ~(1 << PG1))
#define CLK_HIGH()   (PORTG |= (1 << PG1))
#define DIO_LOW()    (PORTG &= ~(1 << PG0))
#define DIO_HIGH()   (PORTG |= (1 << PG0))
#define DIO_OUTPUT() (DDRG  |= (1 << PG0))
#define DIO_INPUT()  (DDRG  &= ~(1 << PG0))

#define SET             1
#define BLOKDETECTIE    5
#define PAROURBLOKJES   15

void send_byte(uint8_t data);
void tm_start();
void tm_stop();
void tm1637_showNumber(uint16_t num);
int blokjes_gedetecteerd(int nieuw);
int blokjes_stop(int taak, int instel);

#endif // MODULE_H_INCLUDED

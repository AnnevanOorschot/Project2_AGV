#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

void block_detectie(int modus);
void motoren_stop(void);
void motoren_start(void);
void update_led_knipper(void);
void setup_module(void);
int pakketDetectie(int mode, int opdracht);
void wachten(int num, int factor);

/*
// Configuratie voor opdrachten
#define OPDRACHT_1_LIM 5    // Eerste opdracht: 5 blokjes
#define OPDRACHT_2_LIM 15   // Tweede opdracht: 15 blokjes
#define SELECT_OPDRACHT OPDRACHT_1_LIM  // Wijzig naar OPDRACHT_2_LIM voor opdracht 2

// Timers en delays
#define STOP_TIME 2000      // 2 seconden stop (ms)
#define BLINK_INTERVAL 500  // Knipper interval (ms)
#define DEBOUNCE_TIME 50    // Debounce tijd voor IR sensoren (ms)

#define TRUE    1
#define FALSE   0

#define SET             1
#define READ_MODE       2
#define READ_OPDRACHT   3

#define SEC         1
#define HALF_SEC    2
#define TENTH_SEC   10*/

#define cycles_per_seconde 61 // 16000000/2^8 = 62500, 62500/1024 = 61

//Display: DIO --> pin 2, CLK --> pin 3. (veranderd naar CLK pin 40 (PG1), DIO pin 41 (PG0))
#define CLK_LOW()    (PORTG &= ~(1 << PG1))
#define CLK_HIGH()   (PORTG |= (1 << PG1))
#define DIO_LOW()    (PORTG &= ~(1 << PG0))
#define DIO_HIGH()   (PORTG |= (1 << PG0))
#define DIO_OUTPUT() (DDRG  |= (1 << PG0))
#define DIO_INPUT()  (DDRG  &= ~(1 << PG0))

void send_byte(uint8_t data);
void tm_start();
void tm_stop();
void tm1637_showNumber(uint16_t num);
void maintest();
int blokjes_gedetecteerd(void);
int blokjes_stop(int taak, int instel);

#endif // MODULE_H_INCLUDED

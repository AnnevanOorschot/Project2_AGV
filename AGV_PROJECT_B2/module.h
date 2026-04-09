#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

void block_detectie(int modus);
void motoren_stop(void);
void motoren_start(void);
void update_led_knipper(void);
void setup_module(void);
int pakketDetectie(int mode, int opdracht);
void wachten(int num, int factor);


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
#define TENTH_SEC   10

#endif // MODULE_H_INCLUDED

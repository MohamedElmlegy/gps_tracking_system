#include "stdint.h"
#include <stdio.h>
#include <time.h>

void delay (int number_of_seconds)
{
int milli_seconds = 1000 * number_of_seconds;
clock_t start_time = clock();
while (clock() < start_time + milli_seconds);
}

#include "C:\Keil\UV4/tm4c123gh6pm.h"
#define PORTB_PINS_0123 (*((volatile int *) 0x4000503C))
#define PORTB_PIN_4 (*((volatile int *) 0x40005040))
#define PORTB_PIN_5 (*((volatile int *) 0x40005080))
#define PORTB_PIN_6 (*((volatile int *) 0x40005100))
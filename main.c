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

int main () 
{
	
 while (1)
 {
   int distance,w,x,y,z;
   PORTB_PIN_4 = 0x10;
   PORTB_PIN_6 = 0x00;
   PORTB_PIN_5 = 0x00;
		
   if (distance < 100)
   {
	x = distance % 10; //PORTB_PIN_4
	y = distance / 10; //PORTB_PIN_5
			
	PORTB_PIN_4 = 0x10;
	PORTB_PIN_5 = 0x00;
	PORTB_PIN_6 = 0x00;
	PORTB_PINS_0123 = x;
	delay (5);
			
	PORTB_PIN_4 = 0x00;
	PORTB_PIN_5 = 0x20;
	PORTB_PIN_6 = 0x00;
	PORTB_PINS_0123 = y;
	delay (5);
     }
	else if (distance > 100)
	{
	  x = distance % 10; //PORTB_PIN_4
	  z = distance / 10;
	  y = z % 10;  //PORTB_PIN_5
	  w = z / 10; //PORTB_PIN_6
			
	  PORTB_PIN_4 = 0x10;
	  PORTB_PIN_5 = 0x00;
	  PORTB_PIN_6 = 0x00;
	  PORTB_PINS_0123 = x;
	  delay (5);
			
	  PORTB_PIN_4 = 0x00;
	  PORTB_PIN_5 = 0x20;
	  PORTB_PIN_6 = 0x00;
	  PORTB_PINS_0123 = y;
	  delay (5);
			
	  PORTB_PIN_4 = 0x00;
	  PORTB_PIN_5 = 0x00;
	  PORTB_PIN_6 = 0x40;
	  PORTB_PINS_0123 = w;
	  delay (5);
}
}
}

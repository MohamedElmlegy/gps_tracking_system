#include "stdint.h"
#include "C:/Keil/tm4c123gh6pm.h"

void Red_LED_Init(void) {
	
	SYSCTL_RCGCGPIO_R |= 0x20;							// Clock enable
	while((SYSCTL_PRGPIO_R & 0x20) == 0);		// Delay
	
	GPIO_PORTF_LOCK_R = 0x4C4F434B;		// Unlock GPIO_PORTF_CR_R
	GPIO_PORTF_CR_R |= 0x02;					// Allow changes to PF123
	
	GPIO_PORTF_AFSEL_R &= ~0x02;		// Disable alternative fn
	GPIO_PORTF_PCTL_R &= ~0x02;			// To use PF123 as GPIO
	GPIO_PORTF_DIR_R |= 0x02;				// To use PF123 as output pins
	
	GPIO_PORTF_AMSEL_R &= ~0x02;		// Disable analog fn
	GPIO_PORTF_DEN_R |= 0x02;				// Enable digital
	
}

void PORTB_Init(void) {
	
	SYSCTL_RCGCGPIO_R |= 0x02;							// Clock enable
	while((SYSCTL_PRGPIO_R & 0x02) == 0);		// Delay
	
	GPIO_PORTB_AFSEL_R &= ~0xFF;				// Disable alternative fn
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;		// To use PORTB pins as GPIO
	GPIO_PORTB_DIR_R = 0xFF;						// To use PORTB pins as output pins
	
	GPIO_PORTB_AMSEL_R &= ~0xFF;		// Disable analog fn
	GPIO_PORTB_DEN_R = 0xFF;				// Enable digital

}
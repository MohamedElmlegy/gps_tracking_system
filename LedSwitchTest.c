#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h" 

#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define PF0       (*((volatile uint32_t *)0x40025004))
#define PF4       (*((volatile uint32_t *)0x40025040))
#define SWITCHES  (*((volatile uint32_t *)0x40025044))
#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
void SystemInit(){}
	void init(void)
	{
		
	SYSCTL_RCGCGPIO_R|=0x20;
	while((SYSCTL_PRGPIO_R&0x20)==0){};
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AFSEL_R =0;
		GPIO_PORTF_PCTL_R =0;
		GPIO_PORTF_AMSEL_R =0;
		GPIO_PORTF_DIR_R = 0x0E;
		GPIO_PORTF_DEN_R = 0x1F;
		GPIO_PORTF_PUR_R = 0x11;
		
	
	
	}
		
		int main()
		{
 		init();
			while(1)
			{
				if((GPIO_PORTF_DATA_R&0x01) == 0)
				{
				GPIO_PORTF_DATA_R |= 0x02;
				
				}
					else if((GPIO_PORTF_DATA_R&0x10) ==0)
					{
					GPIO_PORTF_DATA_R |= 0x04;
					}
						else if((GPIO_PORTF_DATA_R&0x11) == 0)
						{
							GPIO_PORTF_DATA_R |= 0x08;
						}
		else
		{
			GPIO_PORTF_DATA_R = 0;
			
		}
	}
		}

#include<C:/Users/Dell/Downloads/tm4c123gh6pm.h>
#include<F:/Dell/Documents/std_types.h>
void SystemInit(){};
void Seg_Port_Init(void);
void display(int x);
void delay(unsigned int x );
void Seg_Port_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x02 ;
	while((SYSCTL_RCGCGPIO_R & 0x02) == 0x00);
	GPIO_PORTB_LOCK_R = 0x4C4F434B ;
	GPIO_PORTB_CR_R |= 0xFF ;
  GPIO_PORTB_AFSEL_R &= ~0xFF ;
	GPIO_PORTB_PCTL_R &= ~0xFF ;
	GPIO_PORTB_AMSEL_R &= ~0xFF ;
	GPIO_PORTB_DIR_R |= 0xFF ;
	GPIO_PORTB_DEN_R |= 0xFF ;
	GPIO_PORTB_DATA_R &= ~0xFF ;
	
	SYSCTL_RCGCGPIO_R |= 0x10 ;
	while((SYSCTL_RCGCGPIO_R & 0x10) == 0x00);
	GPIO_PORTE_LOCK_R = 0x4C4F434B ;
	GPIO_PORTE_CR_R |= 0x0F ;
  GPIO_PORTE_AFSEL_R &= ~0x0F ;
	GPIO_PORTE_PCTL_R &= ~0x0F ;
	GPIO_PORTE_AMSEL_R &= ~0x0F ;
	GPIO_PORTE_DIR_R |= 0x0F ;
	GPIO_PORTE_DEN_R |= 0x0F ;
	GPIO_PORTE_DATA_R &= ~0xFF ;

	
}
void display(int x)
{
	int d_1 = x/100 ;
	int d_2 = (x / 10)%10 ; 
	int d_3 = x%10 ;
	
	GPIO_PORTB_DATA_R = (d_1|(d_2 << 4));
	GPIO_PORTE_DATA_R = d_3 ;		
}

int main()
{
	Seg_Port_Init();
	display(323);    // test 
}

#include<F:/Dell/Documents/tm4c123gh6pm.h>
#include<F:/Dell/Documents/std_types.h>

void SystemInit(void){};
void uart0_init(void);
char uart0_read(void);

	
void uart0_init(void)
{
	
	SYSCTL_RCGCUART_R |= 0X01 ;
	SYSCTL_RCGCGPIO_R |= 0X01 ;
	UART0_CTL_R &= ~0X0001 ;
	UART0_IBRD_R = 520 ;
	UART0_FBRD_R = 53 ;
	UART0_LCRH_R = 0X0070 ;
	UART0_CTL_R |=0X0301 ;
	GPIO_PORTA_AFSEL_R |= 0X03 ; 
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0XFFFFFF00)+0X00000011 ;  
	GPIO_PORTA_DEN_R |= 0X03; 
	GPIO_PORTA_AMSEL_R &= ~0X03; 
	
}
char uart0_read(void)
{
	while((UART0_FR_R&0X0020)!=0) ;
	return (UART0_DR_R) ;
}
int main()
{
	
	uart0_init();

}








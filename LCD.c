#include<C:/Users/Mohammed Adel/Desktop/keil/LCD.h>
#include<C:/Users/Mohammed Adel/Desktop/keil/std_types.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h" 

/* Functions Prototypes */
void SystemInit(){};
void LCD_Init (void)
{
	//1. Enable used PORTS of the LCD Module:
	//PORT_Init (Data_Command_PORT);
	SYSCTL_RCGCGPIO_R |= 0x02;
	while ((SYSCTL_PRGPIO_R&0x02) == 0){};
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xFF;
	GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTB_AMSEL_R &= ~0xFF;
	GPIO_PORTB_AFSEL_R &=~0xFF;
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
		
		
		//PORT_Init (E_RS_RW_PORT);
		
	SYSCTL_RCGCGPIO_R |= 0x10;
	while ((SYSCTL_PRGPIO_R&0x10) == 0){};
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0x05;
	GPIO_PORTB_DEN_R |= 0x05;
	GPIO_PORTB_AMSEL_R &= ~0x05;
	GPIO_PORTB_AFSEL_R &=~0x05;
	GPIO_PORTB_PCTL_R &= ~0x00000FFF;
	
	//2.Configure Pins E, RW, RS Pins as output pins:
  GPIO_PORTE_DIR_R = GPIO_PORTE_DIR_R | (1<<E) | (1<<RW) | (1<<RS);
	
	//2.Configure PORTD as output for LCD Data/Command:
	 GPIO_PORTB_DIR_R = 0xFF;
	
	//3.adjust cursor:
  LCD_SendCommand(Display_ON_CURSOR_OFF);
	
	//4./* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	LCD_SendCommand(Set_Two_Lines_Eight_Bits_Mode);
	
	/* clear LCD at the beginning */
	LCD_SendCommand(Clear_Display);	
}


void LCD_SendCommand (uint8_t command) 
{
	/* Instruction Mode RS=0 */
	//Clear_Bit(GPIO_PORTE_DATA_R,RS);  
	GPIO_PORTE_DATA_R&=(~(1<<RS));
	/* write data to LCD so RW=0 */
	//Clear_Bit(GPIO_PORTE_DATA_R,RW);   
	GPIO_PORTE_DATA_R&=(~(1<<RW));
	/* delay for processing Tas = 50ns */
	 delay_ms(1);
	
	/* Enable LCD E=1 */
	//Set_Bit(GPIO_PORTE_DATA_R,E);
	GPIO_PORTE_DATA_R|=(1<<E);
	/* delay for processing Tpw - Tdws = 190ns */
	delay_ms(1); 
	
	/* out the required command to the data bus B0 --> B7 */
	GPIO_PORTB_DATA_R = command; 
	
	/* delay for processing Tdsw = 100ns */
	delay_ms(1); 
	
	/* disable LCD E=0 */
	//Clear_Bit(GPIO_PORTE_DATA_R,E); 
	GPIO_PORTE_DATA_R&=(~(1<<E));
	/* delay for processing Th = 13ns */
	delay_ms(1); 
}


void LCD_Display_Character (uint8_t data)
{
	/* Data Mode RS=1 */
  //Set_Bit(GPIO_PORTE_DATA_R , RS); 
	GPIO_PORTE_DATA_R|=(1<<RS);
	/* write data to LCD so RW=0 */
	//Clear_Bit(GPIO_PORTE_DATA_R , RW);   
	GPIO_PORTE_DATA_R&=(~(1<<RW));
	/* delay for processing Tas = 50ns */
	delay_ms(1); 

	/* Enable LCD E=1 */
	//Set_Bit(GPIO_PORTE_DATA_R , E);
	GPIO_PORTE_DATA_R|=(1<<E);
	/* delay for processing Tpw - Tdws = 190ns */
	delay_ms(1); 
	
	/* out the required command to the data bus B0 --> B7 */
	GPIO_PORTB_DATA_R = data; 
	
	/* delay for processing Tdsw = 100ns */
	delay_ms(1); 
	
	/* disable LCD E=0 */
	//Clear_Bit(GPIO_PORTE_DATA_R , E); 
	GPIO_PORTE_DATA_R&=(~(1<<E));
	/* delay for processing Th = 13ns */
	delay_ms(1); 
}


void LCD_clearScreen(void)
{
	//clear display:
  LCD_SendCommand (Clear_Display);	
}


void LCD_Coursor_Position_On_Display (uint8_t row, uint8_t col)
{
	uint8_t Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_SendCommand (Address | SET_CURSOR_LOCATION); 
}


void LCD_Display_string(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_Display_Character (Str[i]);
		i++;
	}
}


void LCD_String_From_RowCOl (uint8_t row, uint8_t col, const uint8_t *str)
{
  LCD_Coursor_Position_On_Display (row,col); /* go to to the required LCD position */
	LCD_Display_string (str); /* display the string */

}


int itoa ( uint16_t num, char* str, uint8_t base ) 
{ 	uint8_t temp;
	  uint8_t start;
    uint8_t end;
    int i = 0;  
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return 0; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        uint16_t rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
		start = 0; 
    end = i -1; 
		
    while (start < end) 
    { temp = *(str+start);
			*(str+start) = *(str+end);
			*(str+end) = temp;
			
		    start++; 
      end--; 
    }
 return 0;
} 


void LCD_Display_Integer(uint16_t data)
{	
  uint8_t buff[16]; /* String to hold the ascii result */
  itoa(data,buff,10); /* 10 for decimal */
  LCD_Display_string(buff);
}
void delay_ms(uint32_t time){
	uint32_t i,j;
	for(j=0;j<time;j++)
	{
	for(i = 0;i < 3180;i++){}
	}
}
int main()
{
	LCD_Init();
	LCD_Coursor_Position_On_Display (0,0);
	LCD_Display_Integer(33);
}

#include<C:/Users/Mohammed Adel/Desktop/keil/std_types.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h" 

/* LCD Port Configuration */
#define RS                 0x00   //Pin PE0
#define RW                 0x01   //Pin PE1
#define E                  0x02   //Pin PE2
#define Data_Command_PORT  0x01
#define E_RS_RW_PORT       0x04


/* LCD Commands Configurations */
#define Clear_Display                 0x01
#define Display_ON_CURSOR_OFF         0x0C
#define Display_ON_CURSOR_ON          0x0E
#define SET_CURSOR_LOCATION           0x80
#define Set_Two_Lines_Eight_Bits_Mode 0x38

/* Set a certain bit in any register */
//#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
//#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))



/* Functions' Prototype */
void LCD_Init (void);
void LCD_SendCommand (uint8_t command);
void LCD_Display_Character (uint8_t data);
void LCD_Display_string (const uint8_t *str);
void LCD_Coursor_Position_On_Display (uint8_t row, uint8_t col);
void LCD_String_From_RowCOl (uint8_t row, uint8_t col, const uint8_t *str);
void LCD_Display_Integer(uint16_t data);
void LCD_clearScreen (void);
void delay_ms(uint32_t time);

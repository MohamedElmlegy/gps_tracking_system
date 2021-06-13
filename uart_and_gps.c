#include<F:/Dell/Documents/tm4c123gh6pm.h>
#include<F:/Dell/Documents/std_types.h>
#include<Math.h>
char C_longitude_dms[20] = {'0','0','0','0','0',
											'0','0','0','0','0',
											'0','0','0','0','0',
											'0','0','0','0','0'}	; 
char C_latitude_dms[20] =  {'0','0','0','0','0',
											'0','0','0','0','0',
											'0','0','0','0','0',
											'0','0','0','0','0'}	; 
int L1 = 0;
int L2 = 0;
void SystemInit(void){};
void uart0_init(void);
char uart0_read(void);
void gps_parse(void);
double toDouble(const char* s, int stop);
double toDecimal(double degrees);
	
void uart0_init(void)
{
	
	SYSCTL_RCGCUART_R |= 0x01 ;
	SYSCTL_RCGCGPIO_R |= 0x01 ;
	UART0_CTL_R &= ~0x0001 ;
	UART0_IBRD_R = 520 ;
	UART0_FBRD_R = 53 ;
	UART0_LCRH_R = 0x0070 ;
	UART0_CTL_R |=0x0301 ;
	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_AFSEL_R |= 0x03 ; 
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011 ;   
	GPIO_PORTA_AMSEL_R &= ~0x03; 
	
}
char uart0_read(void)
{
	while((UART0_FR_R&0x0020)!=0) ;
	return (UART0_DR_R) ;
}
void gps_parse(void)
{	
	int counter = 0 ;
	char r = uart0_read();
	if (r == '$')
	{
		r = uart0_read();
		if (r == 'G')
		{
			r = uart0_read();
			if (r == 'P')
			{
				r = uart0_read();
				if (r == 'G')
				{
						r = uart0_read();
						if (r == 'G')
						{
							r = uart0_read();
							while (r == 'A')
							{
								char c = uart0_read();
								if (c==',')
								{
									counter++ ; 
								}
								if (counter == 2 )
								{ int i = 0 ;
									c = uart0_read();
									while(c!=',')
									{									
										C_latitude_dms[i]= c ; 
										L1++;
										c = uart0_read();
										i++;				
									}
									counter++ ; 
								}
								if (counter == 3 )
								{ 
									int i = 0 ;
									c = uart0_read();
									while(c!=',')
									{									
										C_longitude_dms[i]= c ; 
										L2++;
										c = uart0_read();
										i++;				
									}		
									break;
								}
							}
						}
					}
				}
			}
		}
}
double toDouble(const char* s, int stop) {
	int reslut_d = 0;	int i = 0;
	float reslut_f = 0;
	float reminder;
	int c = 1;
	int n = 0 ;
	int j = i+1 ;
	for (i = 0; i < stop; i++)
	{
		if (s[i] == '.')
			break;
		reminder = (s[i] - '0');
		reslut_d = reslut_d * 10 + reminder;
	}
	for ( j = i+1; j < stop ; j++ ) 
	{
		reminder = (s[j] - '0');
		n = pow(10, c);
		reminder = reminder / n;
		reslut_f += reminder;
		c++ ;
	}

	return reslut_d + reslut_f;
}
double toDecimal(double dgreesAndMinutes)
{ 
	int degrees = dgreesAndMinutes / 100 ;
	double minutes = dgreesAndMinutes - degrees *100 ;  
	int m = minutes ; 
	double seconds = ( minutes - m) * 60 ; 
	double decimal = degrees + minutes / 60 +seconds / 3600 ;
	return decimal ;
}
int main()

{
	// initialize 7-segment
	// initialize led 
	// initialize uart
	uart0_init();

	while (1)
		{
			double D_longtitude_dms = 0 ;
			double D_latitude_dms = 0 ;
			double longtitude = 0 ;
			double latitude = 0 ;
			int distance = 0 ;
			while(distance < 100)
				{
					gps_parse();
			 	  D_longtitude_dms = toDouble(C_longitude_dms,L2) ;
				  D_latitude_dms = toDouble(C_latitude_dms,L1) ;
					longtitude = toDecimal(D_longtitude_dms);
					latitude = toDecimal(D_latitude_dms);
					//distnce = dstnc(longtitude_d,latitude_d)
					//display(distance)
				}
			//led on
		}
}








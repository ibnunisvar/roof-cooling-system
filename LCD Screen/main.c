#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "LCD16x2_4bit.h"
#define DHT11_PIN 6 //For DHT11
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

// DHT11 CODE
void Request()				/* Microcontroller send start pulse/request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);	/* set to high pin */
}
// DHT11 CODE
void Response()				/* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}
// BOTH DHT11 AND LCD CODE
uint8_t Receive_data()			/* receive data */
{	
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0); //Loop continue until PIND and (1<<DHT11_PIN) are become 0 /* check received bit 0 or 1  */ 
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

int main(void)
{	
	char data[5];
	lcdinit();			/* Initialize LCD */
	lcd_clear();			/* Clear LCD */
	lcd_gotoxy(0,0);		/* Enter column and row position */
	lcd_print("Humidity =");
	lcd_gotoxy(0,1);
	lcd_print("Temp = ");
	
    while(1)
	{	
		Request();		/* send start pulse */
		Response();		/* receive response */
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
		
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			lcd_gotoxy(0,0);
			lcd_print("Error");
		}
		
		else
		{	
			itoa(I_RH,data,10); //belongs to stdlib function.used to convert a number into a string,binary(I_RH)to decimal(data) 
			lcd_gotoxy(11,0);
			lcd_print(data);
			lcd_print(".");
			
			itoa(D_RH,data,10);
			lcd_print(data);
			lcd_print("%");

			itoa(I_Temp,data,10);
			lcd_gotoxy(6,1);
			lcd_print(data);
			lcd_print(".");
			
			itoa(D_Temp,data,10);
			lcd_print(data);
			lcddata(0xDF);
			lcd_print("C ");
			
			itoa(CheckSum,data,10);
			lcd_print(data);
			lcd_print(" ");
		}
				
	_delay_ms(10);
	}	
}

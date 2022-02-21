#ifndef F_CPU
#define F_CPU 1600000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>
void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);
	// ADC Enable and prescaler of 128
	
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
// read adc value
uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch;
	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);

	// wait for conversion to complete
	// ADSC becomes '0' again
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}

int main()
{
	DDRB=0xff;
	uint16_t adc_result0;
	int temp;


	// initialize adc
	adc_init();


	while(1)
	{
		adc_result0 = adc_read(0);      // read adc value at PA0
		
		temp=adc_result0/2.01;
		
		

		
		if(temp>=80)
		{
			PORTB=(1<<PINB0);
			
		}
		if (temp<=80)
		{

			PORTB=(0<<PINB0);
			
		}
	}
}
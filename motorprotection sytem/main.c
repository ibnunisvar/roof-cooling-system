/*
 * motor protection
 *
 * Created: 5/8/2021 9:06:56 AM
 * Author : niroshika
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#define relay PD0

// ADC initialization
void adc_init(){
	//AREF= AVcc
	ADMUX= (1<< REFS0);
	
	//ADC Enable 
	// 16000000/128=125000
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

//reading ADC value
uint16_t adc_read(uint8_t ch){
	//select the corresponding channel 0~7
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xf8)| ch; 
	
	//start single conversion
	//write '1' to ADSC
	ADCSRA |= (1<<ADSC);
	
	//wait for conversion to complete
	//ADSC becomes '0' again
	// still then, run loop continuously
	
	while(ADCSRA & (1<<ADSC));
	return(ADC);
}

int main(void)
{
    uint16_t adc_result0, adc_result1;
	DDRB = 0xff;
	DDRD = 0xff;
	int temp;
	double vin;
	double vout;
	adc_init();
    while (1) 
    {
		adc_result0=adc_read(0);
		adc_result1=adc_read(1);
		
		temp= adc_result1/2.01;
		vout = adc_result0 *0.00488;
		vin = (vout-2.5)/0.185;
		
		if(temp>=80){
			PORTB=(1<< PINB0);
		}
		
		if(temp<=80){
			PORTB=(0<< PINB0);
		}
		
		if(vin>=2){
			PORTD=(0<< relay);
		}
		
		if(vin<2){
			PORTD=(1<< relay);
		}	
    }
}




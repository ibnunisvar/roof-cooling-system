
#define F_CPU 16000000UL //clock speed 16MHz
#include <avr/io.h>  //AVR header
double vin;  
double vout;
unsigned int value;
#define relay PD0
void ADC_init(){
	DDRA=0x00;  //make ADC port as input
	ADCSRA=0x87; //enable ADC fr/128
	ADMUX=0x00;  //vref:AREF
}

double current(void){
	ADMUX &= ~(1<<0); //MUX0=0
	ADCSRA |=(1<<6);  //ADSC=1(ADC start conversion)
	while(ADIF == 0); //ADC conversion complete and the data registers are updated
	value = ADCL | ADCH<<8; //read value(save ADC reading into an integer variable value)
	vout= value*0.00488;
	vin= (vout-2.5)/0.185;
	return vin;	
}

int main(void)
{
	DDRD=0xff;
	ADC_init();// call ADC_init function
    while (1) 
    { 
		
	current(); //call current function
	if(vin>2){ //if exceed maximum current
		PORTD=(0<<relay);	//turn off relay
}
    if(vin<=2){
		PORTD=(1<<relay); //turn on relay
	}
	
}
}
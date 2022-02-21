/*
 * WaterLevelSensor.c
 *
 * Created: 29-Apr-21 4:05:18 PM
 *  Author: DELL
 */ 

#include "WaterLevelSensor.h"

// int TimerOverflow = 0;
// 
// ISR(TIMER1_OVF_vect)
// {
// 	TimerOverflow++;	/* Increment Timer Overflow count */
// }
// 
// void water_level_sensor()
// {
// 	long count;
// 	double distance;
// 
// 	DDRA = 0x01;		/* Make trigger pin as output */
// 	PORTD = 0xFF;		/* Turn on Pull-up */
// 	
// 	DDRC = 0xFF;
// 
// 	sei();			/* Enable global interrupt */
// 	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
// 	TCCR1A = 0;		/* Set all bit to zero Normal operation */
// 
// 	while(1)
// 	{
// 		/* Give 10us trigger pulse on trig. pin to HC-SR04 */
// 		PORTA |= (1 << Trigger_pin);
// 		_delay_us(10);
// 		PORTA &= (~(1 << Trigger_pin));
// 
// 		TCNT1 = 0;	/* Clear Timer counter */
// 		TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
// 		TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
// 		TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
// 
// 		/*Calculate width of Echo by Input Capture (ICP) */
// 
// 		while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
// 		TCNT1 = 0;	/* Clear Timer counter */
// 		TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
// 		TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
// 		TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
// 		TimerOverflow = 0;/* Clear Timer overflow count */
// 
// 		while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
// 		count = ICR1 + (65535 * TimerOverflow);	/* Take count */
// 		/* 8MHz Timer freq, sound speed =343 m/s */
// 		distance = (double)count / 466.47;
// 		distance=ceil(distance);
// 		
// 		if(distance>=75){
// 			PORTC = 0xFF;
// 		}
// 		else if(distance==10){
// 			PORTC = 0x00;
// 		}
// 
// 		_delay_ms(200);
// 	}
// }
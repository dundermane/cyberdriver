/*
Lets blink the ps_pwm pin


logical 0 :  PORTB &= ~(1<<PB0);
logical 1 :  PORTB |= (1<<PB0);

*/

#include <avr/io.h>

#define d_ps_pwm PD5
//PD5 is OC0B
#define d_a0 PD2
#define d_a1 PD3
#define d_a2 PD4
#define d_a3 PD6

void delay_ms(uint8_t ms) {
	uint16_t delay_count = 16000 / 64;
	volatile uint16_t i;
	
	while (ms != 0) {
		for (i=0; i != delay_count; i++);
		ms--;
	}
}

void a_vid(uint8_t grey) {
	
	PORTD = 0x00;
	PORTD |= ((grey % 2) << d_a0);
	grey >> 1;
	PORTD |= ((grey % 2) << d_a1);
	grey >> 1;
	PORTD |= ((grey % 2) << d_a2);
	grey >> 1;
	PORTD |= ((grey % 2) << d_a3);
	grey >> 1;
	
}

int main(void) {
	
	DDRD = 0xFF;  //All digital outs to 0
	PORTD = 0x00;


/**********
 PWM INIT
**********/
	TCCR0A = 0x00; //init tccr0a. probs dont need to do that tho
	OCR0A = 0x0F;
    OCR0B  = 0x03;                          // initial PWM pulse width
    DDRD   |= (1 << d_ps_pwm);                   // PWM output on PD5
    TCCR0A |= (1 << WGM00) | (1 << WGM01); // fast PWM with orc0a as top
    TCCR0B |= (1 << WGM02); //Because WGM2 is in a dif register. DUMB
    
    TCCR0A |= (1 << COM0B1); //OC0B duty low on compare match
    TCCR0B |= (1 << CS00);   //Clock Divider for pwm 

    
    
	for(;;) {
		uint8_t i;
		for(i = 0; i < 7; i++){
			a_vid(i);
			delay_ms(2000);
		}
	}

	return 0;
}

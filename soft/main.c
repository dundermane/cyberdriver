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

#define b_HODL PB5
#define b_HPL PB4
#define b_HCK PB3
#define b_VCK PB7
#define b_VPL PB6
#define b_RENE PB2
#define b_RENO PB1

void delay_ms(uint8_t ms) {
	uint16_t delay_count = 16000 / 64;
	volatile uint16_t i;
	
	while (ms != 0) {
		for (i=0; i != delay_count; i++);
		ms--;
	}
}

void a_vid(uint8_t grey) {
	

	PORTD &= ~(1<<d_a0);
	PORTD |= (grey % 2 << d_a0);
	PORTD &= ~(1<<d_a1);
	PORTD |= ((grey >> 1) % 2 << d_a1);
	PORTD &= ~(1<<d_a2);
	PORTD |= ((grey >> 2) % 2 << d_a2);
	PORTD &= ~(1<<d_a3);
	PORTD |= ((grey >> 3) % 2 << d_a3);
	
}

void dumpOnScreen(uint8_t rows, uint8_t cols, uint8_t *img){

//img is a pointer for the first item in array


}

int main(void) {
	
	DDRD = 0xFF;  //All digital outs to 0
	DDRB = 0xFF;
	PORTD = 0x00;
	PORTB = 0x00;


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

/************
 DISPLAY INIT
************/
    
	uint8_t image[40] = {0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
					   0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
					   0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
					   0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
					   0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
					   0x3, 0x3, 0x3, 0x3, 0x3, 0x3};
	
    uint8_t *img;

/***********
 Main Loop
***********/
	for(;;) {
	
	
		a_vid(0);
		delay_ms(2000);
		a_vid(15);
		delay_ms(2000);

		dumpOnScreen(6,6,&img[0]);		
	}

	return 0;
}

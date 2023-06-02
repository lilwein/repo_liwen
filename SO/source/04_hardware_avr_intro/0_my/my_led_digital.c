#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it

int main(void){
	// this initializes the printf/uart thingies
	printf_init(); 


	// the LED is connected to pin 13 that is the bit 7 of port b
	const uint8_t led_mask=(1<<7);	// 1 0 0 0 0 0 0 0
					   
					   // ~ led_mask = 0 1 1 1 1 1 1 1 


	// we connect the switch to pin 12 that is the bit 6 of port b
	const uint8_t p12_mask=(1<<6);	// 0 1 0 0 0 0 0 0

					   // ~ p12_mask = 1 0 1 1 1 1 1 1 


	DDRB |= led_mask;
	DDRB &= ~p12_mask;				// 1 0 * * * * * *


	PORTB |= p12_mask;				// * 1 * * * * * *
	PORTB &= ~led_mask;				// 0 1 * * * * * *


	while(1){
		int key = (PINB & p12_mask)  == 0;

		printf("key %d, led %s\n", key, key? "acceso":"spento");
		
		if (key) {
			// ho inserito il filo
			// accendo la luce
			PORTB |= led_mask;		// 1 1 * * * * * *
		}
		else{
			// ho tolto il filo
			// spengo la luce
			PORTB &= ~led_mask;		// 0 1 * * * * * *
		}

		_delay_ms(100);
	}
	
}

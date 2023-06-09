#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "../avr_common/uart.h" // this includes the printf and initializes it


ISR(INT0_vect) {
    // toggle status of bit 7 of port b
    // FILL HERE

}


int main() {
    GICR=0x40; // Enable External Interrupts INT0
    MCUCR=0x00; // Configure INT0 active low

    // configure ports (D as input , pull up , B as output on pin 7)
    // FILL HERE

    sei();
    while (1) {
        sleep_cpu ();
    }
}
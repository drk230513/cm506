/*
 * @brief A program for the EA NXP LPC4088QSB to flash LED1
 * @author David Kendall
 * @date July 2015
 */

#include <stdint.h>
#include <stdbool.h>

#define IOCON_P1_18 (*(volatile uint32_t *)(0x4002C0C8UL))
#define GPIOBASE   (0x20098000UL)
#define GPIO1DIR   (*(volatile uint32_t *)(GPIOBASE + 0x020))
#define GPIO1PIN   (*(volatile uint32_t *)(GPIOBASE + 0x034))

#define LED1PIN    (1UL << 18)

void delay(uint32_t ms);

int main() {
	IOCON_P1_18 = 0UL;      // configure as GPIO pin
	GPIO1DIR |= LED1PIN;    // set P1_18 as output pin
	while (true) {
		GPIO1PIN |= LED1PIN;  // set pin HIGH
		delay(1000);
		GPIO1PIN &= ~LED1PIN; // set pin LOW
		delay(1000);
	}
}

/*
 * @brief Waits approximately for a specified delay period
 * @param ms - specifies a delay period in milliseconds
 * @return - None
 *
 * delay(ms) causes a delay of ms milliseconds by looping repeatedly,
 * so using CPU cycles, e.g. delay(1000) should give approximately
 * a 1 second delay. Note this depends on the CPU clock speed and 
 * gives only an approximate delay. There are better ways of doing
 * this.
 */
void delay(uint32_t ms) {
	volatile uint32_t i;
	volatile uint32_t j;
	
	for (i=ms; i>0; i--) {
		for (j=11850; j>0; j--) {
			/* skip */
		}
	}	
}


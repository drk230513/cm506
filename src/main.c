/*
 * @brief A program for the EA NXP LPC4088QSB to flash LED1, LED2, LED3 and LED4.
 * @author David Kendall
 * @date July 2015
 */

#include <stdint.h>
#include <stdbool.h>

#define IOCON_P1_18 (*(volatile uint32_t *)(0x4002C0C8UL))   
#define IOCON_P0_13 (*(volatile uint32_t *)(0x4002C034UL))
#define IOCON_P1_13 (*(volatile uint32_t *)(0x4002C0B4UL))
#define IOCON_P2_19 (*(volatile uint32_t *)(0x4002C14CUL))   
#define GPIOBASE   (0x20098000UL)
#define GPIO0DIR   (*(volatile uint32_t *)(GPIOBASE + 0x000))
#define GPIO0PIN   (*(volatile uint32_t *)(GPIOBASE + 0x014))
#define GPIO1DIR   (*(volatile uint32_t *)(GPIOBASE + 0x020))
#define GPIO1PIN   (*(volatile uint32_t *)(GPIOBASE + 0x034))
#define GPIO2DIR   (*(volatile uint32_t *)(GPIOBASE + 0x040))
#define GPIO2PIN   (*(volatile uint32_t *)(GPIOBASE + 0x054))


#define LED1PIN    (1UL << 18)
#define LED2PIN    (1UL << 13)
#define LED3PIN    (1UL << 13)
#define LED4PIN    (1UL << 19)

void delay(uint32_t ms);

int main() {
	IOCON_P1_18 = 0;
	IOCON_P0_13 = 0x80; // Ensure digital mode is selected for type 'A' pin
	IOCON_P1_13 = 0;
	IOCON_P2_19 = 0;
	GPIO1DIR |= LED1PIN;
	GPIO0DIR |= LED2PIN;
	GPIO1DIR |= LED3PIN;
	GPIO2DIR |= LED4PIN;
	while (true) {
		GPIO1PIN ^= LED1PIN;
		GPIO0PIN ^= LED2PIN;
		GPIO1PIN ^= LED3PIN;
		GPIO2PIN ^= LED4PIN;
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


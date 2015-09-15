/*
 * @brief A program for the EA NXP LPC4088QSB to flash LED1, LED2, LED3 and LED4
          and the RGB LED.
 * @author David Kendall
 * @date July 2015
 */

#include <stdint.h>
#include <stdbool.h>

#define IOCON_P1_18 (*(volatile uint32_t *)(0x4002C0C8UL))   
#define IOCON_P0_13 (*(volatile uint32_t *)(0x4002C034UL))
#define IOCON_P1_5  (*(volatile uint32_t *)(0x4002C094UL))
#define IOCON_P1_7  (*(volatile uint32_t *)(0x4002C09CUL))
#define IOCON_P1_11 (*(volatile uint32_t *)(0x4002C0ACUL))
#define IOCON_P1_13 (*(volatile uint32_t *)(0x4002C0B4UL))
#define IOCON_P2_19 (*(volatile uint32_t *)(0x4002C14CUL))   
#define GPIOBASE   (0x20098000UL)
#define GPIO0DIR   (*(volatile uint32_t *)(GPIOBASE + 0x000))
#define GPIO0PIN   (*(volatile uint32_t *)(GPIOBASE + 0x014))
#define GPIO0SET   (*(volatile uint32_t *)(GPIOBASE + 0x018))
#define GPIO0CLR   (*(volatile uint32_t *)(GPIOBASE + 0x01c))
#define GPIO1DIR   (*(volatile uint32_t *)(GPIOBASE + 0x020))
#define GPIO1PIN   (*(volatile uint32_t *)(GPIOBASE + 0x034))
#define GPIO1SET   (*(volatile uint32_t *)(GPIOBASE + 0x038))
#define GPIO1CLR   (*(volatile uint32_t *)(GPIOBASE + 0x03c))
#define GPIO2DIR   (*(volatile uint32_t *)(GPIOBASE + 0x040))
#define GPIO2PIN   (*(volatile uint32_t *)(GPIOBASE + 0x054))
#define GPIO2SET   (*(volatile uint32_t *)(GPIOBASE + 0x058))
#define GPIO2CLR   (*(volatile uint32_t *)(GPIOBASE + 0x05c))


#define LED1PIN    (1UL << 18)
#define LED2PIN    (1UL << 13)
#define LED3PIN    (1UL << 13)
#define LED4PIN    (1UL << 19)
#define LEDRPIN    (1UL << 11)
#define LEDGPIN    (1UL << 5)
#define LEDBPIN    (1UL << 7)

void delay(uint32_t ms);

int main() {
	uint32_t rgbState = 0;
	
	IOCON_P1_18 &= ~0x1FUL;
	IOCON_P0_13 &= ~0x1FUL;
	IOCON_P1_13 &= ~0x1FUL;
	IOCON_P2_19 &= ~0x1FUL;
	IOCON_P1_5 &=  ~0x1FUL;
	IOCON_P1_7 &=  ~0x1FUL;
	IOCON_P1_11 &= ~0x1FUL;
	GPIO1DIR |= LED1PIN;
	GPIO0DIR |= LED2PIN;
	GPIO1DIR |= LED3PIN;
	GPIO2DIR |= LED4PIN;
	GPIO1DIR |= LEDRPIN;
	GPIO1DIR |= LEDGPIN;
	GPIO1DIR |= LEDBPIN;
	while (true) {
		GPIO1SET = LED1PIN;
		GPIO0SET = LED2PIN;
		GPIO1CLR = LED3PIN;
		GPIO2CLR = LED4PIN;
		switch (rgbState) {
			case 0: {
				GPIO1CLR = LEDRPIN;
				GPIO1SET = LEDGPIN | LEDBPIN;
				rgbState = 1;
				break;
			}
			case 1: {
				GPIO1CLR = LEDGPIN;
				GPIO1SET = LEDRPIN | LEDBPIN;
				rgbState = 2;
				break;
			}
			case 2: {
				GPIO1CLR = LEDBPIN;
				GPIO1SET = LEDRPIN | LEDGPIN;
				rgbState = 0;
				break;
			}
			default: {
				GPIO1CLR = LEDRPIN;
				GPIO1SET = LEDGPIN | LEDBPIN;
				rgbState = 1;
				break;
			}
		}
		delay(1000);
		GPIO1CLR = LED1PIN;
		GPIO0CLR = LED2PIN;
		GPIO1SET = LED3PIN;
		GPIO2SET = LED4PIN;
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


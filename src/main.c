/*
 * @brief A program for the EA NXP LPC4088QSB to flash LED1 and LED3.
 * @author David Kendall
 * @date July 2015
 */

#include <stdint.h>
#include <stdbool.h>

#define IOCON_P1_13 (*(volatile uint32_t *)(0x4002C0B4UL))
#define IOCON_P1_18 (*(volatile uint32_t *)(0x4002C0C8UL))   
#define GPIOBASE   (0x20098000UL)
#define GPIO1DIR   (*(volatile uint32_t *)(GPIOBASE + 0x020))
#define GPIO1PIN   (*(volatile uint32_t *)(GPIOBASE + 0x034))


#define LED1PIN    (1UL << 18)
#define LED3PIN    (1UL << 13)

void delay(uint32_t ms);
void skip(void);

int main() {
	IOCON_P1_13 &= ~0x1FUL;
	IOCON_P1_18 &= ~0x1FUL;
	GPIO1DIR |= LED1PIN;
	GPIO1DIR |= LED3PIN;
	while (true) {
		/*
		 * There's a puzzling bug here. LED1 remains on constantly.
		 * It should not. It does not when the program is stepped in
		 * the debugger. The bug disappears if you use a single write 
		 * to the pin, i.e. GPIO1PIN |= (LED1PIN | LED3PIN) and
		 * GPIO1PIN &= ~(LED1PIN | LED3PIN). It disappears if you
		 * insert a short delay between the writes, e.g. skip(). And it disappears
		 * if you update the pin by using the SET and CLR registers.
		 * So there's something about the timing of the consecutive writes 
		 * that causes the problem but I don't understand what it is.
		 */
		GPIO1PIN |= LED1PIN;
		// skip();
		GPIO1PIN |= LED3PIN;
		delay(1000);
		GPIO1PIN &= ~LED1PIN;
		// skip();
	  GPIO1PIN &= ~LED3PIN;
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

void skip(void) {
	volatile uint32_t i = 0;
	i = 1;
}


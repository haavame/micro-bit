#include <stdint.h>
#include <stdio.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main() {

	printf("Hello World!\n");
	printf("And Mars!\n");


	// Configure LED Matrix
	for (int i = 4; i <= 15; i++) {

		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;

	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		int maske1 = 0x04000000;
		maske1 = ~GPIO->IN & maske1;
		if(maske1){
			GPIO->OUTSET = (0b111 << 13);
		}

		int maske2 = 0x00020000;
		maske2 = ~GPIO->IN & maske2;
		if(maske2){
			GPIO->OUTCLR = (0b111 << 13);
		}
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}

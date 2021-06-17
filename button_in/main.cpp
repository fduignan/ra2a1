
// Simple example the reads the state of P201 and copies it's state to P400
#include <stdint.h>
#include "../include/ra2a1.h"


void delay(uint32_t dly);

void delay(volatile uint32_t dly)
{
	while (dly--);
}
int main()
{   
    int i=0;
	
	PORT4.PDR |= 1; // make P400 an output	
	PORT2.PDR &= ~(1<<1); // make P201 an input
	PMISC_PWPR = 0; // unlock PFS system
	PMISC_PWPR = (1 << 6);
	
	PFS_P4[0] &= ~(1 << 6); // make output push-pull
	PFS_P2[1] |= (1<<4); // enable pull-up on input pin
	while(1)
	{
		if (PORT2.PIDR & (1 << 1))
			PORT4.PODR |= 1;
		else		
			PORT4.PODR &= ~1;
		
	}	
}


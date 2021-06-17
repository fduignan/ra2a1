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

	PORT4.PDR = 1;	
	PMISC_PWPR = 0; // unlock PFS system
	PMISC_PWPR = (1 << 6);
	PFS_P4[0] &= ~(1 << 6); // make output push-pull
	while(1)
	{
		PORT4.PODR |= 1;
		delay(10000);
		PORT4.PODR &= ~1;
		delay(10000);
	}
	
}


#include <stdint.h>
#include "../include/ra2a1.h"

void SysTick_Handler(void);
void initSysTick(void);
void delay(uint32_t dly);






int main()
{   
    int i=0;

	PORT4.PDR = 1;	
	PMISC_PWPR = 0; // unlock PFS system
	PMISC_PWPR = (1 << 6);
	PFS_P4[0] &= ~(1 << 6); // make output push-pull
	initSysTick();
	enable_interrupts();
	while(1)
	{
		
	}
	
}
void delay(volatile uint32_t dly)
{
	while (dly--);
}
void initSysTick(void)
{
	// At power up, the system clock is set to MOCO / 16.  MOCO is nominally 8MHz but can be between 6.8MHz and 9.2MHz so calibration is necessary
	SysTick.SYST_RVR =  540-1; // nominallY 8/16 = 500kHz; tweak to get 1kHz
	SysTick.SYST_CVR = 100; // start at a low number
	SysTick.SYST_CSR = 7;   // enable counting and interrupts
}
void SysTick_Handler(void)
{
	PORT4.PODR ^= 1;
}

#include <stdint.h>
#include "../include/ra2a1.h"
#include "serial.h"
// Example that runs the system up to 32MHz and outputs a 1ms pulse on P400 
// using the SysTick interrupt

void SysTick_Handler(void);
void initSysTick(void);
void delay(uint32_t dly);
void initClock(void);

serial Serial0;

int main()
{   
    int i=0;
	
	PORT4.PDR = 1;	
	PMISC_PWPR = 0; // unlock PFS system
	PMISC_PWPR = (1 << 6);
	PFS_P4[0] &= ~(1 << 6); // make output push-pull
	//delay(100000);
	initClock();
	initSysTick();
	Serial0.begin();
	enable_interrupts();
	//Serial0.eputc('c');
	while(1)
	{
		delay(1000);
		Serial0.print("The value = ");
		Serial0.printHex(i++);
		Serial0.print("\r\n");
		if (Serial0.available())
		{
			Serial0.eputc(Serial0.egetc());
		}
	}
	
}
void delay(volatile uint32_t dly)
{
	while (dly--);
}
void initSysTick(void)
{
	// starup code sets the system clock to 8MHz
	SysTick.SYST_RVR =  32000-1; // divide to get 1ms timebase
	SysTick.SYST_CVR = 100; // start at a low number
	SysTick.SYST_CSR = 7;   // enable counting and interrupts
}
void SysTick_Handler(void)
{
	PORT4.PODR ^= 1;
}

void initClock(void)
{
	// Set all clocks to 32MHz

	// Must unlock the clock registers first
	SYSTEM_PRCR = 0xa501;
	SYSTEM_SCKDIVCR = 0; // set the system,PCLKB,PCLKD and FCLK clock divisors to 1	
	SYSTEM_HOCOCR &= ~1; // enable High speed Oscillator (32 MHz)
	while((SYSTEM_OSCSF & 1)==0); // wait for HOCO to stabilize	
	SYSTEM_SCKSCR = 0; // select HOCO as system clock
}

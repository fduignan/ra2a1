#include <stdint.h>
#include "sdadc24.h"
#include "../include/ra2a1.h"
void sdadc24::begin(void)
{	
	
	MSTPCRD &= ~(1 << 17); // take SDADC out of stop state
	// unlock the clock system 	
	SYSTEM_PRCR = 0xa501;
	SYSTEM_SDADCCKCR = 1; // must turn off SDADC clock first
	
	SDADC24.ADC1 = 0;
	SDADC24.ADC2 = 0;
	SDADC24.STC2 = 0; // make sure ADC is off first
	// assuming 32MHz clock is ADC clock.  Need to divide this down by 8
	SDADC24.STC1 = (1 << 10) + (1 << 9) + 6; // 2.0V reference, divide clock by 8
	// Now set the clock for the 24 bit sigma delta adc	
	SYSTEM_SDADCCKCR = 0x81; // HOCO = SDADC clock, enable SDADC clock
	SDADC24.STC2 = 1; // turn on ADBGR, SBIAS, and ADREG 
	volatile uint32_t dly=1000000;
	while(dly--); // wait for ADC to settle (should be at least 2ms)
	SDADC24.STC2 |= 2; // turn on  VBIAS, PGA and sigma-delta A/D converter
	dly=1000000;
	while(dly--); // wait for stabilization
// For the purposes of this initial test program ANSD0N/P101 (pin 23 on LQFP32) and ANSD0P/P100 (pin 24)
// will be used as a differential input.
// Pin configuration:
// TX is on pin: pin 8 on LQFP32 (TXD0_A).  This pin is also P407 PSEL : 00100b (b28-b24 of port function select register)
// RX if on pin: pin 7 on LQFP32 (RXD0_A).  This pin is also P408 PSEL : 00100b (b28-b24 of port function select register)	
	
	PMISC_PWPR = 0; // unlock PFS system
	PMISC_PWPR = (1 << 6);
	PORT1.PDR &= ~(3); // make the pins inputs
	PFS_P1[0] = (1 << 15); // select analogue mode
	PFS_P1[1] = (1 << 15); // select analogue mode
// And now the multiplexers and instrumentation amplifier
	SDADC24.PGAC[0] = 0; // gain of 1, oversampling x64, offset=0, differential mode, 8 average, don't average
	SDADC24.PGAC[0] |= (1 << 30) + (1 << 26)+(1<<27)+(1<<24)+(1<<25) + (1 << 7);//enable averaging and generate ADI when done, average 64 readings.  Oversampling=1024
// Start calibration
	SDADC24.CLBPR = 2; // unlock the calibration protection 
	SDADC24.CLBPR = 3;
	SDADC24.CLBC = 0;
	SDADC24.ADC1 |= 1; // set SDADSCM to 1 for calibration
	SDADC24.CLBSTR = 1;
	while ((SDADC24.CLBSSR & 1) == 0); // wait for calibration to start
	// now need to wait for calibration to complete
	while ((SDADC24.CLBSSR & 1) != 0); // wait for calibration to end
	
	ICU_IELSR[2]=0x43; // Map event 0x43 (ADC Interrupt) to ICU event 2
		
}
uint32_t sdadc24::read()
{
	SDADC24.ADC1 = 1 + (1 << 9)+(1<<10)+(1<<11)+(1<<12); // single scan mode, stop at adconversion on PGAC1.  Using software trigger
	SDADC24.ADC2 = 1; // start conversion
	while ( (ICU_IELSR[2] & (1 << 16))==0); // wait for interrupt flag
	ICU_IELSR[2] &= ~(1 << 16); // ack the interrupt request
	SDADC24.ADC1 =0;
	return (SDADC24.ADAR&0xffffff)<<8; // return right adjusted so that sign is treated properly
}

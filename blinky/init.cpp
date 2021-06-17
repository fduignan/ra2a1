#include <stdint.h>


void init(void);
void Default_Handler(void);

int main(void);
// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;


extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

typedef void (*fptr)(void);
// the section "vectors" is placed at the beginning of flash 
// by the linker script
#pragma GCC push_options
#pragma GCC optimize ("O0")

const fptr Vectors[] __attribute__((section(".vectors"))) ={
	(fptr)(0x20000000+32768), 	/* Top of stack () */ 
	init,   		/* Reset Handler */
	Default_Handler,	/* NMI */
	Default_Handler,	/* Hard Fault */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved  */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */ 
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* SVCall */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* PendSV */
	SysTick_Handler,	/* Systick */	
/* External interrupt handlers follow */
	SCI0_RX_Handler, 	/* 0: ICU.IELSR0 */
	SCI0_TX_Handler, 	/* 1: ICU.IELSR1 */
	Default_Handler, 	/* 2: ICU.IELSR2 */
	Default_Handler, 	/* 3: ICU.IELSR3 */
	Default_Handler, 	/* 4: ICU.IELSR4 */
	Default_Handler, 	/* 5: ICU.IELSR5 */
	Default_Handler, 	/* 6: ICU.IELSR6 */
	Default_Handler,    /* 7: ICU.IELSR7 */
	Default_Handler, 	/* 8: ICU.IELSR8 */
	Default_Handler, 	/* 9: ICU.IELSR9 */
	Default_Handler, 	/* 10: ICU.IELSR10 */
	Default_Handler, 	/* 11: ICU.IELSR11 */
	Default_Handler, 	/* 12: ICU.IELSR12 */
	Default_Handler, 	/* 13: ICU.IELSR13 */
	Default_Handler, 	/* 14: ICU.IELSR14 */
	Default_Handler, 	/* 15: ICU.IELSR15 */
	Default_Handler, 	/* 16: ICU.IELSR16 */
	Default_Handler, 	/* 17: ICU.IELSR17 */
	Default_Handler, 	/* 18: ICU.IELSR18 */
	Default_Handler, 	/* 19: ICU.IELSR19 */
	Default_Handler, 	/* 20: ICU.IELSR20*/
	Default_Handler, 	/* 21: ICU.IELSR21 */
	Default_Handler, 	/* 22: ICU.IELSR22 */
	Default_Handler, 	/* 23: ICU.IELSR23 */
	Default_Handler, 	/* 24: ICU.IELSR24 */
	Default_Handler, 	/* 25: ICU.IELSR25 */
	Default_Handler, 	/* 26: ICU.IELSR26 */
	Default_Handler, 	/* 27: ICU.IELSR27 */
	Default_Handler, 	/* 28: ICU.IELSR28 */
	Default_Handler, 	/* 29: ICU.IELSR29 */
	Default_Handler, 	/* 30: ICU.IELSR30 */
	Default_Handler 	/* 31: ICU.IELSR31 */
	
};

void init_array()
{
    // This function calls constructors for global and static objects
    uint32_t count;
    uint32_t i;
    
    count = __preinit_array_end - __preinit_array_start;
    for (i = 0; i < count; i++)
        __preinit_array_start[i] ();
    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++)
        __init_array_start[i] (); 
}
void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
    init_array();
	main();
}

void Default_Handler()
{
	while(1);
}
#pragma GCC pop_options

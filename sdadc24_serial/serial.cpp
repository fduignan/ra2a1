#include "serial.h"
#include <stdint.h>
#include "../include/ra2a1.h"
void delay(volatile uint32_t dly);
static serial *pSerial;  // need a pointer to the hopefully only instance of Serial for the interrupt service routine
void serial::begin()
{
    // assuming SCI0
	// 
    int BaudRate = 9600;
    pSerial = this;
	disable_interrupts();
	RXBuffer.head = RXBuffer.tail = RXBuffer.count = 0;
	TXBuffer.head = TXBuffer.tail = TXBuffer.count = 0;	
// Pin configuration:
// TX is on pin: pin 8 on LQFP32 (TXD0_A).  This pin is also P407 PSEL : 00100b (b28-b24 of port function select register)
// RX if on pin: pin 7 on LQFP32 (RXD0_A).  This pin is also P408 PSEL : 00100b (b28-b24 of port function select register)	
	
	PMISC_PWPR = 0; // unlock PFS system
	PMISC_PWPR = (1 << 6);
	PFS_P4[8] = (1 << 16) + (4 << 24);
	PFS_P4[7] = (1 << 16) + (4 << 24);
    
	MSTPCRB &= ~(1 << 31); // take SCI0 out of stop state

// Configure the serial communications interface
	SCI0.SCR = 0;	

// Set the baud rate    
	SCI0.SMR = 0;
	SCI0.SCMR = (1 << 4);
// Baud rate calculation (see page 602 of reference manual)
	/*
	 * N = (PCLKB/(64*2^(n-1)*BaudRate) - 1
	 * n=0, BaudRate = 9600, PCLKB = 32MHz so N = 103
	*/
	SCI0.BRR = 103; // give 9600 Baud approx with 32MHz PCLKB bus speed 
// Clear any pending interrupts
    
// Turn on Transmitter, Receiver and receive interrupts
	SCI0.SCR = (1 << 6) + (1 << 5) + (1 << 4);
// Will use IELSR0 for receive interrupts
// SCI0 RXI = Event number 0x71, TXI = Event number 0x72
	ICU_IELSR[0] =  0x71;
	ICU_IELSR[1] =  0x72;
// Enable SCI 0 interrupts in NVIC	
	NVIC.ISER[0] |= ( 3 ); // enable irq's 0 and 1 corresponding to ELSR0 and ELSR1
}
void serial::eputc(char c)
{
	uint32_t timeout=100000;
	while ( (TXBuffer.count >= SBUFSIZE) && (timeout--) ); // if buffer is full just wait
	if ( (SCI0.SCR & (1 << 7) )==0)  
	{ // transmitter was idle, turn it on and force out first character
        SCI0.SCR |= (1 << 7); // turn on transmitter interrupts
		SCI0.TDR = c;        
	} 
    else 
    {   // interrupt transmission is underway so add byte to the queue
        putBuf(TXBuffer,c);
    }    
}
char serial::egetc()
{
    // return next character in buffer (0 if empty)
    return getBuf(RXBuffer);
}
void serial::print(int Value)
{
    // Convert Value to a string equivalent and call the 
    // print(string) version of this function
    
    char Buffer[12]; // ints can be +/- 2 billion (approx) so buffer needs to be this big
    int index=10;    // Start filling buffer from the right
    Buffer[11]=0;    // ensure the buffer is terminated with a null
    if (Value < 0)  
    {
        Buffer[0]='-';  // insert a leading minus sign
        Value = -Value; // make Value positive
    }
    else
    {
        Buffer[0]='+';  // insert a leading plus sign
    }
    while(index > 0)  // go through all of the characters in the buffer
    {
        Buffer[index]=(Value % 10)+'0'; // convert the number to ASCII
        Value = Value / 10; // move on to the next digit
        index--;  
    }
    print(Buffer); // call string version of print
}
uint8_t serial::HexDigit(uint8_t digit)
{
	if ( (digit >= 0) && (digit < 10) )
	{
		return digit + 48;
	}
	if ( (digit >= 10) && (digit < 16) )
	{
		return digit + 55;
	}
	return '#';
	
}
void serial::printHex(uint32_t Value)
{
    // Convert Value to a string equivalent and call the 
    // print(string) version of this function
    
    char Buffer[9]; // ints can be +/- 2 billion (approx) so buffer needs to be this big
    int index=7;    // Start filling buffer from the right
    Buffer[8]=0;    // ensure the buffer is terminated with a null    
    while(index >= 0)  // go through all of the characters in the buffer
    {
        Buffer[index]=HexDigit(Value % 16); // convert the number to ASCII
        Value = Value >> 4; // move on to the next digit
        index--;  
    }
    print(Buffer); // call string version of print
}
void serial::print(char c)
{    
    eputc(c); // write out the character        
}
void serial::print(const char *String)
{
    while(*String) // keep going until a null is encountered
    {
        eputc(*String); // write out the next character
        String++;       // move the pointer along
    }
}
// Maybe the circular buffer code belongs in a more general purpose module
void serial::putBuf(SerialBuffer &sbuf, char c)
{
    if (sbuf.count < SBUFSIZE)
    {
        disable_interrupts();
        sbuf.count++;
        sbuf.buffer[sbuf.head] = c;
        sbuf.head=(sbuf.head+1) % SBUFSIZE;
        enable_interrupts();
    }
}
char serial::getBuf(SerialBuffer &sbuf)
{
    char c=0;
    if (sbuf.count >0 )
    {
        disable_interrupts();
        sbuf.count--;
        c=sbuf.buffer[sbuf.tail];
        sbuf.tail=(sbuf.tail+1) % SBUFSIZE;
        enable_interrupts();
    }
    return c;
}
int serial::available() 
{
    return RXBuffer.count;
}


void SCI0_RX_Handler(void)
{
	ICU_IELSR[0] &= ~(1 << 16); // clear Interrupt Request in IELSR0	
	uint8_t c=SCI0.RDR;
	pSerial->putBuf(pSerial->RXBuffer,c);
}
void SCI0_TX_Handler(void)
{
	ICU_IELSR[1] &= ~(1 << 16); // clear Interrupt Request in IELSR1	
	if (pSerial->TXBuffer.count)
	{
			SCI0.TDR = pSerial->getBuf(pSerial->TXBuffer);
	}
	else
	{
		// no more data lest, turn off the transmitter
		SCI0.SCR &= ~(1 << 7); // turn off transmitter interrupts
	}
	
}



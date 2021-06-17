#ifndef __serial_h
#define __serial_h
#define SBUFSIZE 128
#include <stdint.h>
typedef struct 
{
	volatile unsigned head,tail,count;
	char buffer[SBUFSIZE];
} SerialBuffer;

class serial {
public:
    serial() {};
    void begin();
    void print(int Value);
    void print(char c);
    void print(const char *Str);
	void printHex(uint32_t Value);
	uint8_t HexDigit(uint8_t digit);
    void eputc(char ch);
    char egetc();
    int available();
    
private:
    SerialBuffer TXBuffer,RXBuffer;
    friend void SCI0_RX_Handler(void);
	friend void SCI0_TX_Handler(void);
    void putBuf(SerialBuffer &sbuf, char c);
    char getBuf(SerialBuffer &sbuf);
};
#endif

#include <stdint.h>
class sdadc24 
{
public:
	sdadc24(){};
	void begin(void);
	uint32_t read();
};

#ifndef __RA2A1_H
#define __RA2A1_H
#include <stdint.h>
// Define some bitmasks
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

// Macros to enable/disable global interrupts
#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")
#define cpu_sleep() asm(" wfi ")


// Macros to reduce typing later on
#define  REGISTER_32(ADDRESS) (*((volatile uint32_t *)(ADDRESS)))
#define  REGISTER_16(ADDRESS) (*((volatile uint16_t *)(ADDRESS)))
#define  REGISTER_8(ADDRESS) (*((volatile uint8_t *)(ADDRESS)))
// Macros to enable/disable global interrupts
#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")

// Define some base addresses
#define MMPU_BASE 		0x40000000
#define SMPU_BASE 		0x40000C00
#define SPMON_BASE 		0x40000D00
#define MMF_BASE		0x40001000
#define SRAMCTRL_BASE	0x40002000
#define BUSCTRL_BASE 	0x40003000
#define DTCCTRL_BASE	0x40005400
#define ICUCTRL_BASE	0x40006000
#define DBG_BASE		0x4001B000
#define FCACHE_BASE		0x4001C000
#define SYSCTRL_BASE	0x4001E000
#define PCNTR1_BASE		0x40040000
#define PORT0_BASE		0x40040000
#define PORT1_BASE		0x40040020
#define PORT2_BASE		0x40040040
#define PORT3_BASE		0x40040060
#define PORT4_BASE		0x40040080
#define PORT5_BASE		0x400400A0
#define PORT9_BASE		0x40040120
#define PFS_BASE		0x40040800
#define PMISC_BASE		0x40040D00
#define ELCCTRL_BASE	0x40041000
#define RTC_BASE		0x40044000
#define WDT_BASE		0x40044200
#define IWDT_BASE		0x40044400
#define CAC_BASE		0x40044600
#define MSTP_BASE		0x40047000
#define CAN0_BASE		0x40050000
#define IIC0_BASE		0x40053000
#define IIC1_BASE		0x40053100
#define DOC_BASE		0x40054100
#define ADC160_BASE		0x4005C000
#define DAC12_BASE		0x4005E000
#define SCI0_BASE		0x40070000
#define SCI1_BASE		0x40070020
#define SCI9_BASE		0x40070120
#define SPI0_BASE		0x40072000
#define SPI1_BASE		0x40072100
#define CRC_BASE		0x40074000
#define GPT320_BASE		0x40078000
#define GPT161_BASE		0x40078100
#define GPT162_BASE		0x40078200
#define GPT163_BASE		0x40078300
#define GPT164_BASE		0x40078400
#define GPT165_BASE		0x40078500
#define GPT166_BASE		0x40078600
#define GPT_OPS_BASE	0x40078FF0
#define KINT_BASE		0x40080000
#define CTSU_BASE		0x40081000
#define AGT0_BASE		0x40084000
#define AGT1_BASE		0x40084100
#define ACMPHS0_BASE	0x40085000
#define ACMPLP_BASE		0x40085E00
#define OPAMP_BASE		0x40086800
#define USBFS_BASE		0x40090000
#define SDADC24_BASE	0x4009C000
#define DAC8_BASE		0x4009E000
#define TSN_BASE		0x407EC000
#define NVIC_BASE		0xE000E100


#define SysTick_BASE    0xE000E010
typedef struct {
	volatile uint16_t PODR;
	volatile uint16_t PDR;
	volatile uint16_t EIDR;
	volatile uint16_t PIDR;
	volatile uint16_t PORR;
	volatile uint16_t POSR;
	volatile uint16_t EORR;
	volatile uint16_t EOSR;
	
} PORT_Type;
#define PORT0 (*(PORT_Type *)PORT0_BASE)
#define PORT1 (*(PORT_Type *)PORT1_BASE)
#define PORT2 (*(PORT_Type *)PORT2_BASE)
#define PORT3 (*(PORT_Type *)PORT3_BASE)
#define PORT4 (*(PORT_Type *)PORT4_BASE)
#define PORT5 (*(PORT_Type *)PORT5_BASE)
#define PORT9 (*(PORT_Type *)PORT9_BASE)

// Function select registers - treat as an array.  Not all elements populated
#define PFS_P0 (& REGISTER_32(0x40040800))
#define PFS_P1 (& REGISTER_32(0x40040840))
#define PFS_P2 (& REGISTER_32(0x40040880))
#define PFS_P3 (& REGISTER_32(0x400408c0))
#define PFS_P4 (& REGISTER_32(0x40040900))
#define PFS_P5 (& REGISTER_32(0x40040940))
#define PFS_P9 (& REGISTER_32(0x40040a40))

#define PMISC_PWPR REGISTER_8(0x40040d03)


// System clock registers are scattered around various areas so will not use structures with them
#define SYSTEM_SCKDIVCR	REGISTER_32(0x4001e020)
#define SYSTEM_SCKSCR	REGISTER_8(0x4001e026)
#define SYSTEM_MEMWAIT	REGISTER_8(0x4001e031)
#define SYSTEM_MOSCCR 	REGISTER_8(0x4001e032)
#define SYSTEM_SOSCCR 	REGISTER_8(0x4001e480)
#define SYSTEM_LOCOCR 	REGISTER_8(0x4001e490)
#define SYSTEM_HOCOCR 	REGISTER_8(0x4001e036)
#define SYSTEM_MOCOCR 	REGISTER_8(0x4001e038)
#define SYSTEM_OSCSF 	REGISTER_8(0x4001e03c)
#define SYSTEM_OSTDCR 	REGISTER_8(0x4001e040)
#define SYSTEM_OSTDSR 	REGISTER_8(0x4001e041)
#define SYSTEM_MOSCWTCR	REGISTER_8(0x4001e0a2)
#define SYSTEM_HOCOWTCR REGISTER_8(0x4001e0a5)
#define SYSTEM_MOMCR	REGISTER_8(0x4001e413)
#define SYSTEM_SOMCR	REGISTER_8(0x4001e481)
#define SYSTEM_CKOCR	REGISTER_8(0x4001e03e)
#define SYSTEM_LOCOUTCR	REGISTER_8(0x4001e492)
#define SYSTEM_MOCOUTCR	REGISTER_8(0x4001e061)
#define SYSTEM_HOCOUTCR	REGISTER_8(0x4001e062)
#define SYSTEM_SDADCCKCR	REGISTER_8(0x4001e0d1)
#define MSTPCRA REGISTER_32(0x04001e01c)
#define MSTPCRB REGISTER_32(0x040047000)
#define MSTPCRC REGISTER_32(0x040047004)
#define MSTPCRD REGISTER_32(0x040047008)

#define SYSTEM_PRCR REGISTER_16(0x4001e3fe)
typedef struct {                                  
  volatile uint32_t  SYST_CSR;  // SysTick Control/Status register 
  volatile uint32_t  SYST_RVR;  // SysTick Reload Value Register   
  volatile uint32_t  SYST_CVR;  // SysTick Current Value Register
  volatile  uint32_t SYST_CALIB; // SysTick Calibration Value Register
} SysTick_Type;

#define SysTick                         (*(SysTick_Type            *) SysTick_BASE)


// SCI interfaces
typedef struct  {
	
	volatile uint8_t SMR; // Serial Mode Register at offset 0 (ignoring smart card interface for the moment which shares this address)
	volatile uint8_t BRR; // Baud Rate Register at offset 1
	volatile uint8_t SCR; // Serial Control Register at offset 2	(smart card shares this address too)
	volatile uint8_t TDR; // Transmit data register (8 bit) at offset 3	
	volatile uint8_t SSR; // Serial Status Register at offset 4 with SCMR=0 and FCR.FM = 0
	volatile uint8_t RDR; // Receive 8 bit Data Register at offset 5
	volatile uint8_t SCMR; // Smart Card Mode Register at offset 6
	volatile uint8_t SEMR; // Serial Extended Mode Register at offset 7
	volatile uint8_t SNFR; // Noise Filter Setting Register at offset 8
	volatile uint8_t SIMR1; // I2C Mode Register 1 at offset 9
	volatile uint8_t SIMR2; // I2C Mode Register 2 at offset 0x0a
	volatile uint8_t SIMR3; // I2C Mode Register 3 at offset 0x0b
	volatile uint8_t SISR; // I2C Status Register at offset 0x0c
	volatile uint8_t SPMR; // SPI Mode Register at offset 0x0d
	volatile uint16_t TDRHL; // Transmit 9 bit Data Register at offset 0x0e. FTDRHL shares this address
	volatile uint16_t RDRHL; // Receive 9 bit Data Register at offset 0x10 FRDRHL shares this address
	volatile uint8_t MDDR; // Modulation Duty Register at offset 0x12
	volatile uint8_t DCCR; // Data Compare Match Control Register at offset 0x13
	volatile uint16_t FCR; // Fifo Control Register at offset 0x14
	volatile uint16_t FDR; // Fifo Data Count Regiter at offset 0x16
	volatile uint16_t LSR; // Line Status Register at offset 0x18
	volatile uint16_t CDR; // Compare Data match register at offset 0x1a
	volatile uint8_t SPTR; // Serial Port Register at offset 0x1c 
	
} SCI_Type;

// The interrupt control unit is a sparsely populated structure so it's probably just as easy to
// not use a struct at all and just define the members 
#define ICU_IRQR (& REGISTER_8((ICUCTRL_BASE + 0)))
#define ICU_NMICR REGISTER_8((ICUCTRL_BASE + 0x100))
#define ICU_NMIER REGISTER_16((ICUCTRL_BASE + 0x120))
#define ICU_NMICLR REGISTER_16((ICUCTRL_BASE + 0x130))
#define ICU_NMISR REGISTER_16((ICUCTRL_BASE + 0x140))
#define ICU_WUPEN REGISTER_32((ICUCTRL_BASE + 0x1a0))
#define ICU_SELSR0 REGISTER_16((ICUCTRL_BASE + 0x200))
#define ICU_IELSR (& REGISTER_32((ICUCTRL_BASE + 0x300)))

#define SCI0 (*(SCI_Type *) SCI0_BASE)
#define SCI1 (*(SCI_Type *) SCI1_BASE)
#define SCI9 (*(SCI_Type *) SCI9_BASE)
#endif
typedef struct {              
  volatile uint32_t  ISER[2];		// Interrupt Set Enable Registers
  volatile uint32_t  RESERVED[30];		// padding
  volatile uint32_t  ICER[2];		// Interrupt Clear Enable Registers
  volatile uint32_t  RESERVED1[30];		// padding
  volatile uint32_t  ISPR[2];		// Interrupt Set Pending Registers
  volatile uint32_t  RESERVED2[30];		// padding
  volatile uint32_t  ICPR[2];		// Interrupt Clear Pending Registers
  volatile uint32_t  RESERVED3[30];		// padding
  volatile uint32_t  IABR[2];		// Interrupt Active Bit Registers
  volatile uint32_t  RESERVED4[30];		// padding
  volatile uint32_t  ITNS[2];		// Interrupt Target Non-secure Registers
  volatile uint32_t  RESERVED5[30];		// padding
  volatile uint32_t  IPR[12];		// Interrupt Priority Registers
} NVIC_Type;
#define NVIC (*((NVIC_Type *)NVIC_BASE))

typedef struct { // entries may work as 32 bit aligned quanties
	volatile uint32_t STC1; // at offset 0
	volatile uint32_t STC2; // at offset 4
	volatile uint32_t PGAC[5]; // starting at offset 8
	volatile uint32_t ADC1; // at offset 0x1c
	volatile uint32_t ADC2; // at offset 0x20
	volatile uint32_t ADCR; // at offset 0x24
	volatile uint32_t ADAR; // at offset 0x28
	volatile uint32_t Reserved0; // at offset 0x38
	volatile uint32_t CLBC; // at offset 0x30
	volatile uint32_t CLBSTR; // at offset 0x34
	volatile uint32_t Reserved1; // padding
	volatile uint32_t CLBSSR; // at offset 0x3c
	volatile uint32_t CLBPR; // at offset 0x40	
	volatile uint32_t Reserved2; // padding
	volatile uint32_t GCVLR[5]; // starting at offset 0x48
	volatile uint32_t OCVLR[5]; // starting at offset 0x5c		
} SDADC24_Type;
#define SDADC24 (*( (SDADC24_Type *)SDADC24_BASE) )

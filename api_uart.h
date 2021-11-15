
#ifndef _API_UART
#define  API_UART_EXTLBL 					extern
extern uint32_t API_UART_base [6];

#else
#define  API_UART_EXTLBL 

#define  _SRAM_BASE 		((uint32_t)0x20000000) // SRAM base address in the bit-band region
#define  _PERIPH_BASE 		((uint32_t)0x40000000) // Peripheral base address in the bit-band region

#define  _APB1PERIPH_BASE 	(_PERIPH_BASE + 0x00)
#define  _APB2PERIPH_BASE 	(_PERIPH_BASE + 0x10000)
#define  _AHBPERIPH_BASE 	(_PERIPH_BASE + 0x20000)

uint32_t API_UART_base [6] = {
	(_APB2PERIPH_BASE + 0x1000), 
	(_APB1PERIPH_BASE + 0x4400), 
	(_APB1PERIPH_BASE + 0x4800), 
	(_APB1PERIPH_BASE + 0x4C00), 
	(_APB1PERIPH_BASE + 0x5000), 
	(_APB2PERIPH_BASE + 0x1400)
};
#endif


#define  _SRAM_BASE 		((uint32_t)0x20000000) // SRAM base address in the bit-band region
#define  _PERIPH_BASE 		((uint32_t)0x40000000) // Peripheral base address in the bit-band region

#define  _APB1PERIPH_BASE 	(_PERIPH_BASE + 0x00)
#define  _APB2PERIPH_BASE 	(_PERIPH_BASE + 0x10000)
#define  _AHBPERIPH_BASE 	(_PERIPH_BASE + 0x20000)


#define  API_UART_SR 			((uint32_t)0x00)
#define  API_UART_DR 			((uint32_t)0x04)
#define  API_UART_BRR 			((uint32_t)0x08)
#define  API_UART_CR1 			((uint32_t)0x0C)
#define  API_UART_CR2 			((uint32_t)0x10)
#define  API_UART_CR3 			((uint32_t)0x14)
#define  API_UART_GTPR 			((uint32_t)0x18)

#define  API_UART_REG(NUM,REG) 	(*((uint32_t *)(API_UART_base [NUM] + REG)))

#define  API_UART_SR_PE 		((uint16_t)0x0001) // Parity Error
#define  API_UART_SR_FE 		((uint16_t)0x0002) // Framing Error
#define  API_UART_SR_NE 		((uint16_t)0x0004) // Noise Error Flag
#define  API_UART_SR_ORE 		((uint16_t)0x0008) // OverRun Error
#define  API_UART_SR_IDLE 		((uint16_t)0x0010) // IDLE line detected
#define  API_UART_SR_RXNE 		((uint16_t)0x0020) // Read Data Register Not Empty
#define  API_UART_SR_TC 		((uint16_t)0x0040) // Transmission Complete
#define  API_UART_SR_TXE 		((uint16_t)0x0080) // Transmit Data Register Empty
#define  API_UART_SR_LBD 		((uint16_t)0x0100) // LIN Break Detection Flag
#define  API_UART_SR_CTS 		((uint16_t)0x0200) // CTS Flag

#define  API_UART_CR1_SBK 		((uint16_t)0x0001) // Send Break
#define  API_UART_CR1_RWU 		((uint16_t)0x0002) // Receiver wakeup
#define  API_UART_CR1_RE 		((uint16_t)0x0004) // Receiver Enable
#define  API_UART_CR1_TE 		((uint16_t)0x0008) // Transmitter Enable
#define  API_UART_CR1_IDLEIE 	((uint16_t)0x0010) // IDLE Interrupt Enable
#define  API_UART_CR1_RXNEIE 	((uint16_t)0x0020) // RXNE Interrupt Enable
#define  API_UART_CR1_TCIE 		((uint16_t)0x0040) // Transmission Complete Interrupt Enable
#define  API_UART_CR1_TXEIE 	((uint16_t)0x0080) // PE Interrupt Enable
#define  API_UART_CR1_PEIE 		((uint16_t)0x0100) // PE Interrupt Enable
#define  API_UART_CR1_PS 		((uint16_t)0x0200) // Parity Selection
#define  API_UART_CR1_PCE 		((uint16_t)0x0400) // Parity Control Enable
#define  API_UART_CR1_WAKE 		((uint16_t)0x0800) // Wakeup method
#define  API_UART_CR1_M 		((uint16_t)0x1000) // Word length
#define  API_UART_CR1_UE 		((uint16_t)0x2000) // API_UART Enable
#define  API_UART_CR1_OVER8 	((uint16_t)0x8000) // API_UART Oversmapling 8-bits

#define  API_UART_CR2_ADD 		((uint16_t)0x000F) // Address of the API_UART node
#define  API_UART_CR2_LBDL 		((uint16_t)0x0020) // LIN Break Detection Length
#define  API_UART_CR2_LBDIE 	((uint16_t)0x0040) // LIN Break Detection Interrupt Enable
#define  API_UART_CR2_LBCL 		((uint16_t)0x0100) // Last Bit Clock pulse
#define  API_UART_CR2_CPHA 		((uint16_t)0x0200) // Clock Phase
#define  API_UART_CR2_CPOL 		((uint16_t)0x0400) // Clock Polarity
#define  API_UART_CR2_CLKEN 	((uint16_t)0x0800) // Clock Enable
#define  API_UART_CR2_STOP 		((uint16_t)0x3000) // STOP[1:0] bits (STOP bits)
#define  API_UART_CR2_STOP_0 	((uint16_t)0x1000) // Bit 0
#define  API_UART_CR2_STOP_1 	((uint16_t)0x2000) // Bit 1
#define  API_UART_CR2_LINEN 	((uint16_t)0x4000) // LIN mode enable

#define  API_UART_CR3_EIE 		((uint16_t)0x0001) // Error Interrupt Enable
#define  API_UART_CR3_IREN 		((uint16_t)0x0002) // IrDA mode Enable
#define  API_UART_CR3_IRLP 		((uint16_t)0x0004) // IrDA Low-Power
#define  API_UART_CR3_HDSEL 	((uint16_t)0x0008) // Half-Duplex Selection
#define  API_UART_CR3_NACK 		((uint16_t)0x0010) // Smartcard NACK enable
#define  API_UART_CR3_SCEN 		((uint16_t)0x0020) // Smartcard mode enable
#define  API_UART_CR3_DMAR 		((uint16_t)0x0040) // DMA Enable Receiver
#define  API_UART_CR3_DMAT 		((uint16_t)0x0080) // DMA Enable Transmitter
#define  API_UART_CR3_RTSE 		((uint16_t)0x0100) // RTS Enable
#define  API_UART_CR3_CTSE 		((uint16_t)0x0200) // CTS Enable
#define  API_UART_CR3_CTSIE 	((uint16_t)0x0400) // CTS Interrupt Enable
#define  API_UART_CR3_ONEBIT 	((uint16_t)0x0800) // One Bit method




#define  API_UART_COUNT 		6
#define  API_UART1 				0
#define  API_UART2 				1
#define  API_UART3 				2
#define  API_UART4 				3
#define  API_UART5 				4
#define  API_UART6 				5

typedef void (*API_UART_pFnk) (uint32_t);

typedef struct {
	int 		num;

	uint8_t * 	ptr_data_Tx;
	int 		data_Tx_len;
	int 		data_Tx_index;
	API_UART_pFnk 	callback_Tx;

	API_UART_pFnk 	callback_Rx;
} API_UART_t;


typedef enum {
	API_UART_PARITY_EVEN 	= 0, 
	API_UART_PARITY_ODD 	= 1
} API_UART_parity_t;

typedef enum {
	API_UART_STOP_1 	= 0, 
	API_UART_STOP_05 	= 1, 
	API_UART_STOP_2 	= 2, 
	API_UART_STOP_15 	= 3
} API_UART_stop_t;





API_UART_EXTLBL void API_UART_Init (
		API_UART_t *, 
		int, 
		uint32_t, 
		uint32_t, 
		API_UART_parity_t, 
		API_UART_stop_t);

API_UART_EXTLBL void API_UART_set_baud 		(API_UART_t *, uint32_t, uint32_t);
API_UART_EXTLBL void API_UART_set_parity 	(API_UART_t *, API_UART_parity_t);
API_UART_EXTLBL void API_UART_set_stop 		(API_UART_t *, API_UART_stop_t);

API_UART_EXTLBL void API_UART_set_callback_Tx (API_UART_t *, API_UART_pFnk);
API_UART_EXTLBL void API_UART_set_callback_Rx (API_UART_t *, API_UART_pFnk);


API_UART_EXTLBL void API_UART_transmit 		(API_UART_t *, uint8_t *, int);


API_UART_EXTLBL void API_UART_IRQ_Handler 	(API_UART_t *);

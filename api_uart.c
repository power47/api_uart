#include <stdio.h>
#include <stdint.h>

#define  _API_UART
#include "api_uart.h"



void API_UART_Init ( 
		API_UART_t * pAPI_UART, 
		int num, 
		uint32_t clock, 
		uint32_t baud, 
		API_UART_parity_t parity, 
		API_UART_stop_t stop)
{
	if (num >= API_UART_COUNT)
		return;


	pAPI_UART -> num = num;

	pAPI_UART -> ptr_data_Tx = NULL;
	pAPI_UART -> data_Tx_len = 0;
	pAPI_UART -> data_Tx_index = 0;
	pAPI_UART -> callback_Tx = NULL;

	pAPI_UART -> callback_Rx = NULL;


	API_UART_REG(pAPI_UART->num, API_UART_CR1) = 0x00;
	API_UART_REG(pAPI_UART->num, API_UART_CR2) = 0x00;
	API_UART_REG(pAPI_UART->num, API_UART_CR3) = 0x00;

	API_UART_REG(pAPI_UART->num, API_UART_CR1) |= API_UART_CR1_UE; 		// 8-bit word

	API_UART_REG(pAPI_UART->num, API_UART_CR1) &= ~API_UART_CR1_M; 		// 8-bit word

	API_UART_set_parity (pAPI_UART, parity);

	API_UART_set_stop (pAPI_UART, stop);

	API_UART_set_baud (pAPI_UART, baud, clock);
}



void API_UART_set_baud (API_UART_t * pAPI_UART, uint32_t baud, uint32_t clock)
{
	uint32_t div;
	uint32_t mant;
	uint32_t fraq;


	div = (uint32_t)((((uint64_t)(clock))*100U)/(16U*((uint64_t)(baud))));

	mant = (uint32_t)(div / 100U);
	fraq = (uint32_t)(((div - (mant * 100U)) * 16U) / 10U);


	API_UART_REG(pAPI_UART -> num, API_UART_BRR) = (mant << 4) + (fraq & 0x0F);
}



void API_UART_set_parity (API_UART_t * pAPI_UART, API_UART_parity_t parity)
{
	if (parity == API_UART_PARITY_ODD)
	{
		API_UART_REG(pAPI_UART->num, API_UART_CR1) |=  API_UART_CR1_PCE;
	}
	else
	{
		API_UART_REG(pAPI_UART->num, API_UART_CR1) &= ~API_UART_CR1_PCE;
	}
}



void API_UART_set_stop (API_UART_t * pAPI_UART, API_UART_stop_t stop)
{
	if 		(stop == API_UART_STOP_1)
	{
		API_UART_REG(pAPI_UART->num, API_UART_CR2) &= ~API_UART_CR2_STOP_0;
		API_UART_REG(pAPI_UART->num, API_UART_CR2) &= ~API_UART_CR2_STOP_1;
	}
	else if (stop == API_UART_STOP_05)
	{
		API_UART_REG(pAPI_UART->num, API_UART_CR2) |=  API_UART_CR2_STOP_0;
		API_UART_REG(pAPI_UART->num, API_UART_CR2) &= ~API_UART_CR2_STOP_1;
	}
	else if (stop == API_UART_STOP_2)
	{
		API_UART_REG(pAPI_UART->num, API_UART_CR2) &= ~API_UART_CR2_STOP_0;
		API_UART_REG(pAPI_UART->num, API_UART_CR2) |=  API_UART_CR2_STOP_1;
	}
	else
	{
		API_UART_REG(pAPI_UART->num, API_UART_CR2) |=  API_UART_CR2_STOP_0;
		API_UART_REG(pAPI_UART->num, API_UART_CR2) |=  API_UART_CR2_STOP_1;
	}
}



void API_UART_set_callback_Tx (API_UART_t * pAPI_UART, API_UART_pFnk fnc)
{
	pAPI_UART -> callback_Tx = fnc;

	API_UART_REG(pAPI_UART->num,API_UART_CR1) |=  API_UART_CR1_TE;
	API_UART_REG(pAPI_UART->num,API_UART_CR1) |=  API_UART_CR1_TXEIE;
	API_UART_REG(pAPI_UART->num,API_UART_CR3) &= ~API_UART_CR3_DMAT;
}

void API_UART_set_callback_Rx (API_UART_t * pAPI_UART, API_UART_pFnk fnc)
{
	pAPI_UART -> callback_Rx = fnc;

	API_UART_REG(pAPI_UART->num,API_UART_CR1) |=  API_UART_CR1_RE;
	API_UART_REG(pAPI_UART->num,API_UART_CR1) |=  API_UART_CR1_RXNEIE;
	API_UART_REG(pAPI_UART->num,API_UART_CR3) &= ~API_UART_CR3_DMAR;
}



void API_UART_transmit (API_UART_t * pAPI_UART, uint8_t * p_data, int p_data_len)
{
	if (pAPI_UART -> data_Tx_index != 0 || 
		pAPI_UART -> data_Tx_len != 0)
		return;


	pAPI_UART -> ptr_data_Tx = p_data;
	pAPI_UART -> data_Tx_len = p_data_len;
	pAPI_UART -> data_Tx_index = 0;

	API_UART_REG(pAPI_UART -> num, API_UART_DR) = *(pAPI_UART -> ptr_data_Tx + pAPI_UART -> data_Tx_index);
}



void API_UART_IRQ_Handler (API_UART_t * pAPI_UART)
{
	if (API_UART_REG(pAPI_UART -> num, API_UART_SR) & API_UART_SR_TXE)
	{
		pAPI_UART -> data_Tx_index ++;
		if (pAPI_UART -> data_Tx_index < pAPI_UART -> data_Tx_len)
		{
			API_UART_REG(pAPI_UART -> num, API_UART_SR) = ~API_UART_SR_TXE;
			API_UART_REG(pAPI_UART -> num, API_UART_DR) = *(pAPI_UART -> ptr_data_Tx + pAPI_UART -> data_Tx_index);
		}
		else
		{
			pAPI_UART -> data_Tx_index = 0;
			pAPI_UART -> data_Tx_len = 0;

			if (pAPI_UART -> callback_Tx != NULL)
			{
				(pAPI_UART -> callback_Tx) (0);
			}
		}
	}

	if (API_UART_REG(pAPI_UART -> num, API_UART_SR) & API_UART_SR_RXNE)
	{
		API_UART_REG(pAPI_UART -> num, API_UART_SR) = ~API_UART_SR_RXNE;

		if (pAPI_UART -> callback_Rx != NULL)
		{
			(pAPI_UART -> callback_Rx) (API_UART_REG(pAPI_UART -> num, API_UART_DR));
		}
	}
}

/** @file SPI.c
 * 	@brief Hardware abstraction functions for SPI
 *
 * 	These functions provide an abstraction layer for the CC430 SPI peripheral.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "SPI.h"

/* faraday hardware allocations */
#include "../REVA_Faraday.h"


/* DEFINITIONS */
#define SPI_DUMMY_BYTE 0x00

void spi_tx(unsigned char tx){
	  while (!(UCB0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
	  UCB0TXBUF = tx;                     // Transmit first character
}

unsigned char spi_rx_byte(unsigned char delay_cycles){
	//Send dummy byte to shift SPI registers out of SRAM into RX CC430
	spi_tx(SPI_DUMMY_BYTE); //dummy

	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	unsigned char rx_byte;
	rx_byte = UCB0RXBUF;
	return rx_byte;
}

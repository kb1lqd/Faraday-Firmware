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





/** @name SPI HAL Variables
*
* 	These variables are used for the SPI hardware abstraction layer.
*
@{**/
//volatile unsigned char chip_select_active; /**< A byte that indicates whether any chip select is active OR if none are active */
volatile unsigned char chip_select_bitmask; /**< This bitmask holds 8 bits that indicate which peripheral chip selects to manipulate and function as a set and hold configuration */
/** @}*/



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

unsigned char spi_enable_chip_select(unsigned char SPI_HAL_CS){
	// This function is meant as a central control for chip select functionality between multiple devices

	if (chip_select_bitmask == 0){
		// No chip selects currently active - OK to activate a chip select output.

		// Set chip select bitmask global variable to new value to hold current state (mostly for debugging, at this time)
		chip_select_bitmask = SPI_HAL_CS;

		switch(chip_select_bitmask){
		case SPI_HAL_CS_SRAM: // SRAM device
			Faraday_SRAM_CS_Enable();
			break;
		default: //Default - Should NEVER get here
			__no_operation();
			break;
		}
	}
	else{
		// A chip select is still active! This should never happen and will potentially cause race condition errors.
		__no_operation();
		return 0;
	}
}

unsigned char spi_disable_chip_select(unsigned char SPI_HAL_CS){
	// This function is meant as a central control for chip select functionality between multiple devices

	if (chip_select_bitmask != 0){
		// No chip selects currently active - OK to activate a chip select output.
		switch(chip_select_bitmask){
		case SPI_HAL_CS_SRAM: // SRAM device
			Faraday_SRAM_CS_Disable();
			break;
		default: //Default - Should NEVER get here
			__no_operation();
			break;
		}

		// Set chip select bitmask global variable to default state (0x00) (mostly for debugging, at this time)
		chip_select_bitmask = 0x00;
	}
	else{
		// A chip select is still active! This should never happen and will potentially cause race condition errors.
		__no_operation();
		return 0;
	}
}

static void Faraday_SRAM_CS_Enable(void){
	//Active LOW
	P5OUT &= ~SRAM_CS;
}

static void Faraday_SRAM_CS_Disable(void){
	//Active LOW
	P5OUT |= SRAM_CS;
}

static void Faraday_SRAM_Hold_Enable(void){
	//Active LOW
	P5OUT &= ~SRAM_HOLD;
}

static void Faraday_SRAM_Hold_Disable(void){
	//Active LOW
	P5OUT |= SRAM_HOLD;
}

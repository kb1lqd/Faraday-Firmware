/*
 * c2120.c
 *
 *  Created on: Sep 13, 2017
 *      Author: Brent
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "c2120.h"
#include "SPI.h"

unsigned char C2120_Read_Register(unsigned char addr){
	unsigned char readbyte;
		//Send the WRITE command
		spi_tx(C2120_CMD_CONFIG);


		spi_tx(addr);
		spi_tx(SPI_DUMMY_BYTE);
		__delay_cycles(6500);

		readbyte = spi_rx_byte(50);


		return readbyte; //Return byte in SPI RX
	//}
}

unsigned char C2120_Read_Version(void){
	volatile unsigned char verbyte;

		//Send the WRITE command
		spi_tx(C2120_CMD_VER);

		spi_tx(0x00);
		verbyte = spi_rx_byte(50); //Return byte in SPI RX
		verbyte = spi_rx_byte(50); //Return byte in SPI RX


		return 1;
}



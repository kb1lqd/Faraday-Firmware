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

unsigned char C2120_Write_Register(unsigned char addr, unsigned char value){
	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(C2120_CMD_WRITE_REG);
	__delay_cycles(6500);
	spi_tx(addr);
	__delay_cycles(6500);
	spi_tx(value);
	__delay_cycles(6500);

	spi_disable_chip_select(SPI_HAL_CS_I2C);
}

unsigned char C2120_Read_Register(unsigned char addr){
	unsigned char readbyte;

	spi_enable_chip_select(SPI_HAL_CS_I2C);
		//Send the WRITE command
		spi_tx(C2120_CMD_CONFIG);


		spi_tx(addr);
		spi_tx(SPI_DUMMY_BYTE);
		__delay_cycles(6500);

		readbyte = spi_rx_byte(50);

		spi_disable_chip_select(SPI_HAL_CS_I2C);


		return readbyte; //Return byte in SPI RX
	//}
}

unsigned char C2120_Read_Version(void){
	volatile unsigned char verbyteh, verbytel;

	spi_enable_chip_select(SPI_HAL_CS_I2C);

	//Send the WRITE command
	spi_tx(C2120_CMD_VER);
	spi_tx(0x00);
	spi_tx(SPI_DUMMY_BYTE);
	__delay_cycles(6500);
	verbyteh = spi_rx_byte(50); //Return byte in SPI RX
	spi_tx(SPI_DUMMY_BYTE);
	__delay_cycles(3500);
	verbytel = spi_rx_byte(50); //Return byte in SPI RX

	spi_disable_chip_select(SPI_HAL_CS_I2C);
	__no_operation();


		return 1;
}



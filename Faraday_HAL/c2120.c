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

	//Enable the device chip select
	if(spi_enable_chip_select(SPI_HAL_CS_I2C) == 0){
		__no_operation(); // SPI CS conflict!
	}
	else{

		//Delay post transmission
		__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

		//Send the WRITE command
		spi_tx(C2120_CMD_CONFIG);
		__delay_cycles(50);

		spi_tx(addr);
		__delay_cycles(50);

		//spi_tx(0x00);
		//__delay_cycles(50);
		spi_tx(0x00);
		__delay_cycles(50);


		//Delay post transmission
		__delay_cycles(50);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
		spi_disable_chip_select(SPI_HAL_CS_I2C);

		return spi_rx_byte(50); //Return byte in SPI RX
	}
}

unsigned char C2120_Read_Version(void){
	volatile unsigned char verbyte;

	//Enable the device chip select
	if(spi_enable_chip_select(SPI_HAL_CS_I2C) == 0){
		__no_operation(); // SPI CS conflict!
	}
	else{

		//Delay post transmission
		__delay_cycles(500); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

		//Send the WRITE command
		spi_tx(C2120_CMD_VER);
		__delay_cycles(500);

		spi_tx(0x00);
		__delay_cycles(500);
		//spi_tx(0x00);
		__delay_cycles(500);
		verbyte = spi_rx_byte(50); //Return byte in SPI RX
		//spi_tx(0x00);
		__delay_cycles(500);
		verbyte = spi_rx_byte(50); //Return byte in SPI RX


		//Delay post transmission
		__delay_cycles(500);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
		spi_disable_chip_select(SPI_HAL_CS_I2C);

		return 1;
	}
}



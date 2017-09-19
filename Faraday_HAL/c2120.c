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
	__delay_cycles(10000);
	spi_tx(addr);
	__delay_cycles(10000);
	spi_tx(value);
	__delay_cycles(10000);

	spi_disable_chip_select(SPI_HAL_CS_I2C);
}

unsigned char C2120_Read_Register(unsigned char addr){
	unsigned char readbyte;

	spi_enable_chip_select(SPI_HAL_CS_I2C);

	//Send the WRITE command
	spi_tx(C2120_CMD_CONFIG);
	spi_tx(addr);
	spi_tx(SPI_DUMMY_BYTE);
	spi_tx(SPI_DUMMY_BYTE);

	__delay_cycles(SPI_BYTE_CYCLES*4);
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
	__delay_cycles(SPI_BYTE_CYCLES*3);
	verbyteh = spi_rx_byte(50); //Return byte in SPI RX
	spi_tx(SPI_DUMMY_BYTE);
	__delay_cycles(SPI_BYTE_CYCLES*1);
	verbytel = spi_rx_byte(50); //Return byte in SPI RX

	spi_disable_chip_select(SPI_HAL_CS_I2C);
	__no_operation();


		return 1;
}

unsigned char C2120_Get_IOCONFIG(void){
	return C2120_Read_Register(C2120_REG_IOCONFIG);
}

unsigned char C2120_Get_I2CCLOCK(void){
	return C2120_Read_Register(C2120_REG_I2CCLOCK);
}

unsigned char C2120_Get_I2CTO(void){
	return C2120_Read_Register(C2120_REG_I2CTO);
}

unsigned char C2120_Get_I2CSTAT(void){
	return C2120_Read_Register(C2120_REG_I2CSTAT);
}

unsigned char C2120_Get_I2CADR(void){
	return C2120_Read_Register(C2120_REG_I2CADR);
}

unsigned char C2120_Get_RXBUFF(void){
	return C2120_Read_Register(C2120_REG_RXBUFF);
}

unsigned char C2120_Get_IOCONFIG2(void){
	return C2120_Read_Register(C2120_REG_IOCONFIG2);
}

unsigned char C2120_Get_EDGEINT(void){
	return C2120_Read_Register(C2120_REG_EDGEINT);
}

unsigned char C2120_Get_I2CTO2(void){
	return C2120_Read_Register(C2120_REG_I2CTO2);
}


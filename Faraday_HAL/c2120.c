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
#include "../External_Sensors/bmp180.h"

void test_c2120(void){
	//SPI External Testing
	volatile unsigned char testspi, cp2120i, rxbufi2c;

	init_SPI_Clk_11();

	testspi = C2120_Read_Register(0x00);
	testspi = C2120_Read_Register(0x07);
	C2120_Write_Register(0x00, 0xAA);
	C2120_Write_Register(0x07, 0xAA);
	/*
	for(cp2120i=0;cp2120i<0xFF;cp2120i++){
		C2120_Write_Register(0x01, cp2120i);
		__delay_cycles(1000000);
	}
	*/
	testspi = C2120_Read_Register(0x00);
	testspi = C2120_Read_Register(0x07);
	testspi = C2120_Read_Register(0x01);

	testspi = C2120_Get_I2CTO2();
	testspi = C2120_Get_I2CCLOCK();
	testspi = C2120_Get_I2CTO();
	testspi = C2120_Get_I2CSTAT();
	testspi = C2120_Get_I2CADR();
	testspi = C2120_Get_RXBUFF();
	testspi = C2120_Get_IOCONFIG2();
	testspi = C2120_Get_EDGEINT();
	testspi = C2120_Get_I2CTO2();

	__no_operation();
	C2120_Read_Version();
	__no_operation();

	volatile unsigned char bmpbuffer[32];

	CP2120_Write_Reg(BMP180_ADDRESS_WRITE, BMP180_ADDRESS_ID);
//	C2120_Write_Reg_I2C(BMP180_ADDRESS_WRITE, BMP180_ADDRESS_ID);
//	testspi = 0x00;
//	while(!(testspi==C2120_I2C_ACK)){
//			__delay_cycles(SPI_BYTE_CYCLES);
//			testspi = C2120_Get_I2CSTAT();
//			//If NAK received try again
//			if(testspi==C2120_I2C_SLAVE_ADDR_NAK){
//				C2120_Write_Reg_I2C(BMP180_ADDRESS_WRITE, BMP180_ADDRESS_ID);
//			}
//		}
	C2120_Read_Reg_I2C(BMP180_ADDRESS_READ, 1);
	testspi = 0x00;
	while(!(testspi==C2120_I2C_ACK)){
			__delay_cycles(SPI_BYTE_CYCLES);
			testspi = C2120_Get_I2CSTAT();
		}

	C2120_Read_I2C_Buffer(bmpbuffer, 1);

	C2120_Write_Reg_I2C(BMP180_ADDRESS_WRITE, 0xD0);
	testspi = 0x00;
	while(!(testspi==0xF0)){
			__delay_cycles(SPI_BYTE_CYCLES);
			testspi = C2120_Get_I2CSTAT();
		}
	C2120_Read_Reg_I2C(BMP180_ADDRESS_READ, 1);
	testspi = 0x00;
	while(!(testspi==0xF0)){
			__delay_cycles(SPI_BYTE_CYCLES);
			testspi = C2120_Get_I2CSTAT();
		}
	C2120_Read_I2C_Buffer(bmpbuffer, 1);
}

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


unsigned char CP2120_Write_Reg(unsigned char devicewriteaddr, unsigned char regaddr){
	unsigned char testspi = 0x00;
	C2120_Write_Reg_I2C(devicewriteaddr, regaddr);
	while(!(testspi==C2120_I2C_ACK)){
			__delay_cycles(SPI_BYTE_CYCLES);
			testspi = C2120_Get_I2CSTAT();
			//If NAK received try again
			if(testspi==C2120_I2C_SLAVE_ADDR_NAK){
				C2120_Write_Reg_I2C(devicewriteaddr, regaddr);
			}
		}
}

unsigned char C2120_Write_Reg_I2C(unsigned char devicewriteaddr, unsigned char regaddr){

	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(C2120_I2C_WRITE);
	spi_tx(0x02); // 2 bytes to write [DEVICE ADDR, DEVICE REGISTER]
	spi_tx(devicewriteaddr);
	spi_tx(regaddr);
	__delay_cycles(SPI_BYTE_CYCLES*5);
	spi_disable_chip_select(SPI_HAL_CS_I2C);

	return 1;
}

unsigned char C2120_Read_Reg_I2C(unsigned char devicereadaddr, unsigned char bytecount){
	volatile unsigned char verbyteh, verbytel;

	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(C2120_I2C_READ);
	spi_tx(bytecount);
	spi_tx(devicereadaddr);
	__delay_cycles(SPI_BYTE_CYCLES*4);

	spi_disable_chip_select(SPI_HAL_CS_I2C);

	return 1;
}

unsigned char C2120_Read_I2C_Buffer(unsigned char *buffer, unsigned char bytecount){
	//Make multiple byte capable!
	unsigned char readbyte, i;

	spi_enable_chip_select(SPI_HAL_CS_I2C);
	__delay_cycles(SPI_BYTE_CYCLES);
	//Send the WRITE command
	spi_tx(C2120_REG_RXBUFF);
	spi_tx(SPI_DUMMY_BYTE);
	//__delay_cycles(SPI_BYTE_CYCLES*2);
	for(i=0; i<bytecount; i++){
		spi_tx(SPI_DUMMY_BYTE);
		__delay_cycles(SPI_BYTE_CYCLES*5);
		buffer[i] = spi_rx_byte(50);
		__delay_cycles(SPI_BYTE_CYCLES);

	}

	spi_disable_chip_select(SPI_HAL_CS_I2C);


	return 1; //Return 1 for success
	//}
}

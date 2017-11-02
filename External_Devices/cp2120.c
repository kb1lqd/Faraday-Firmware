/** @file cp2120.c
 * 	@brief Provides a library to interact with the CP2120 SPI to I2C module
 *
 * 	This program provides an interface library to interact with the CP2120
 * 	SPI to I2C module. It is used to allow Faraday to interact with I2C items without switching
 * 	USCI modes. Do note that the SPI phase/polarity needs to be "11" configuration to use this
 * 	module.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cp2120.h"
#include "cc430f6137.h"
#include "../Faraday_Init.h"

/* USCI includes */
#include "../Faraday_HAL/SPI.h"
//#include "../External_Sensors/bmp180.h"

void test_CP2120(void){
	//SPI External Testing
	volatile unsigned char testspi, cp2120i, rxbufi2c;

	init_SPI_Clk_11();

	testspi = CP2120_Read_Register(0x00);
	testspi = CP2120_Read_Register(0x07);
	CP2120_Write_Register(0x00, 0xAA);
	CP2120_Write_Register(0x07, 0xAA);

	for(cp2120i=0;cp2120i<0xFF;cp2120i++){
		CP2120_Write_Register(0x01, cp2120i);
		__delay_cycles(100000);
	}

	testspi = CP2120_Read_Register(0x00);
	testspi = CP2120_Read_Register(0x07);
	testspi = CP2120_Read_Register(0x01);

	testspi = CP2120_Get_I2CTO2();
	testspi = CP2120_Get_I2CCLOCK();
	testspi = CP2120_Get_I2CTO();
	testspi = CP2120_Get_I2CSTAT();
	testspi = CP2120_Get_I2CADR();
	testspi = CP2120_Get_RXBUFF();
	testspi = CP2120_Get_IOCONFIG2();
	testspi = CP2120_Get_EDGEINT();
	testspi = CP2120_Get_I2CTO2();

	__no_operation();
	CP2120_Read_Version();
	__no_operation();

}

unsigned char CP2120_Write_Register(unsigned char addr, unsigned char value){
	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(CP2120_CMD_WRITE_REG);
	__delay_cycles(10000);
	spi_tx(addr);
	__delay_cycles(10000);
	spi_tx(value);
	__delay_cycles(10000);

	spi_disable_chip_select(SPI_HAL_CS_I2C);

	return 1;
}

unsigned char CP2120_Read_Register(unsigned char addr){
	unsigned char readbyte;

	spi_enable_chip_select(SPI_HAL_CS_I2C);

	//Send the WRITE command
	spi_tx(CP2120_CMD_CONFIG);
	spi_tx(addr);
	spi_tx(SPI_DUMMY_BYTE);
	spi_tx(SPI_DUMMY_BYTE);

	__delay_cycles(SPI_BYTE_CYCLES*4);
	readbyte = spi_rx_byte(50);

	spi_disable_chip_select(SPI_HAL_CS_I2C);


	return readbyte; //Return byte in SPI RX
	//}
}

unsigned char CP2120_Read_Version(void){
	volatile unsigned char verbyteh, verbytel;

	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(CP2120_CMD_VER);
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

unsigned char CP2120_Get_IOCONFIG(void){
	return CP2120_Read_Register(CP2120_REG_IOCONFIG);
}

unsigned char CP2120_Get_I2CCLOCK(void){
	return CP2120_Read_Register(CP2120_REG_I2CCLOCK);
}

unsigned char CP2120_Get_I2CTO(void){
	return CP2120_Read_Register(CP2120_REG_I2CTO);
}

unsigned char CP2120_Get_I2CSTAT(void){
	return CP2120_Read_Register(CP2120_REG_I2CSTAT);
}

unsigned char CP2120_Get_I2CADR(void){
	return CP2120_Read_Register(CP2120_REG_I2CADR);
}

unsigned char CP2120_Get_RXBUFF(void){
	return CP2120_Read_Register(CP2120_REG_RXBUFF);
}

unsigned char CP2120_Get_IOCONFIG2(void){
	return CP2120_Read_Register(CP2120_REG_IOCONFIG2);
}

unsigned char CP2120_Get_EDGEINT(void){
	return CP2120_Read_Register(CP2120_REG_EDGEINT);
}

unsigned char CP2120_Get_I2CTO2(void){
	return CP2120_Read_Register(CP2120_REG_I2CTO2);
}


unsigned char CP2120_Write_I2C_Bytes(unsigned char *buffer, unsigned char len){
	unsigned char testspi = 0x00;
	CP2120_Write_Bytes_I2C(buffer, len);
	while(!(testspi==CP2120_I2C_ACK)){
			__delay_cycles(SPI_BYTE_CYCLES);
			testspi = CP2120_Get_I2CSTAT();
			//If NAK received try again
			if(testspi==CP2120_I2C_SLAVE_ADDR_NAK){
				CP2120_Write_Bytes_I2C(buffer, len);
			}
		}
}

unsigned char CP2120_Write_I2C_Reg(unsigned char devicewriteaddr, unsigned char regaddr){
	unsigned char testspi = 0x00;
	CP2120_Write_Reg_I2C(devicewriteaddr, regaddr);
	while(!(testspi==CP2120_I2C_ACK)){
			__delay_cycles(SPI_BYTE_CYCLES);
			testspi = CP2120_Get_I2CSTAT();
			//If NAK received try again
			if(testspi==CP2120_I2C_SLAVE_ADDR_NAK){
				CP2120_Write_Reg_I2C(devicewriteaddr, regaddr);
			}
		}
}

unsigned char CP2120_Write_Bytes_I2C(unsigned char *bytes, unsigned char len){
	unsigned char i;
	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(CP2120_I2C_WRITE);
	spi_tx(len); // length of bytes to write over I2C (starting with device address)
	for(i==0; i<len; i++){
		spi_tx(bytes[i]);
		__delay_cycles(SPI_BYTE_CYCLES);
	}
	__delay_cycles(SPI_BYTE_CYCLES*5);
	spi_disable_chip_select(SPI_HAL_CS_I2C);

	return 1;
}

unsigned char CP2120_Write_Reg_I2C(unsigned char devicewriteaddr, unsigned char regaddr){

	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(CP2120_I2C_WRITE);
	spi_tx(0x02); // 2 bytes to write [DEVICE ADDR, DEVICE REGISTER]
	spi_tx(devicewriteaddr);
	spi_tx(regaddr);
	__delay_cycles(SPI_BYTE_CYCLES*5);
	spi_disable_chip_select(SPI_HAL_CS_I2C);

	return 1;
}

unsigned char CP2120_Read_I2C_Reg(unsigned char deviceaddr, unsigned char *bmpbuffer, unsigned char len){
	unsigned char testspi = 0x00;
	CP2120_Read_Reg_I2C(deviceaddr, len);

	while(!(testspi==CP2120_I2C_ACK)){
			__delay_cycles(SPI_BYTE_CYCLES);
			testspi = CP2120_Get_I2CSTAT();
		}

	CP2120_Read_I2C_Buffer(bmpbuffer, len);
}

unsigned char CP2120_Read_Reg_I2C(unsigned char devicereadaddr, unsigned char bytecount){
	volatile unsigned char verbyteh, verbytel;

	spi_enable_chip_select(SPI_HAL_CS_I2C);
	//Send the WRITE command
	spi_tx(CP2120_I2C_READ);
	spi_tx(bytecount);
	spi_tx(devicereadaddr);
	__delay_cycles(SPI_BYTE_CYCLES*4);

	spi_disable_chip_select(SPI_HAL_CS_I2C);

	return 1;
}

unsigned char CP2120_Read_I2C_Buffer(unsigned char *buffer, unsigned char bytecount){
	//Make multiple byte capable!
	unsigned char readbyte, i;

	spi_enable_chip_select(SPI_HAL_CS_I2C);
	__delay_cycles(SPI_BYTE_CYCLES);
	//Send the WRITE command
	spi_tx(CP2120_REG_RXBUFF);
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


/*
 * c2120.h
 *
 *  Created on: Sep 13, 2017
 *      Author: Brent
 */

#ifndef FARADAY_HAL_CP2120_H_
#define FARADAY_HAL_CP2120_H_

#define C2120_SPI_I2C_INT BIT5 //P2.5
#define C2120_SPI_CS BIT1 //P1.1
#define C2120_CMD_WRITE_REG 0x20 //Write internal register command
#define C2120_CMD_CONFIG 0x21 //Read internal register command
#define C2120_CMD_VER 0x40 //Read Version command
#define C2120_REG_IOCONFIG 0x00 // IOCONFIG register address
#define C2120_REG_I2CTO2 0x01 // I2CTO2 register address
#define C2120_REG_I2CCLOCK 0x02 // IOCONFIG register address
#define C2120_REG_I2CTO 0x03 // I2CTO register address
#define C2120_REG_I2CSTAT 0x04 // I2CSTAT register address
#define C2120_REG_I2CADR 0x05 // I2CADR register address
#define C2120_REG_RXBUFF 0x06 // RXBUFF register address
#define C2120_REG_IOCONFIG2 0x07 // IOCONFIG2 register address
#define C2120_REG_EDGEINT 0x09 // EDGEINT register address
#define C2120_REG_I2CTO2 0x09 // I2CTO2 register address

#define C2120_I2C_ACK 0xF0 // I2C SUCCESS (ACK)
#define C2120_I2C_SLAVE_ADDR_NAK 0xF1 // I2C Slave address NACKed
#define C2120_I2C_SLAVE_DATA_NAK 0xF2 // I2C Slave data NACKed
#define C2120_I2C_INPROGRESS 0xF3 // I2C Transaction in progress
#define C2120_I2C_TIMEOUT 0xF8 // I2C Transaction timed out
#define C2120_I2C_TXRXOVERFLOW 0xF9 // Command’s Bytes to Transmit Byte and Data Buffer Size do not match, or Read Buffer read number of bytes greater than buffer count.
#define C2120_I2C_SCLLOW 0xFA // 2C SCL Low time-out, using timer configured in I2CTO2.
#define C2120_I2C_BUSNOTFREE // I2C bus free detect has been disabled, and the bus is not free.


#define C2120_I2C_WRITE 0x00 // Write I2C slave
#define C2120_I2C_READ 0x01 // Read I2C slave

void test_c2120(void);
unsigned char C2120_Write_Register(unsigned char addr, unsigned char value);
unsigned char C2120_Read_Register(unsigned char addr);
unsigned char C2120_Read_Version(void);

unsigned char C2120_Get_I2CTO2(void);
unsigned char C2120_Get_I2CCLOCK(void);
unsigned char C2120_Get_I2CTO(void);
unsigned char C2120_Get_I2CSTAT(void);
unsigned char C2120_Get_I2CADR(void);
unsigned char C2120_Get_RXBUFF(void);
unsigned char C2120_Get_IOCONFIG2(void);
unsigned char C2120_Get_EDGEINT(void);
unsigned char C2120_Get_I2CTO2(void);

unsigned char CP2120_Write_I2C_Bytes(unsigned char *buffer, unsigned char len);
unsigned char C2120_Write_Bytes_I2C(unsigned char *bytes, unsigned char len);

unsigned char CP2120_Write_Reg(unsigned char devicewriteaddr, unsigned char regaddr);
unsigned char C2120_Write_Reg_I2C(unsigned char deviceaddr, unsigned char regaddr);
unsigned char CP2120_Read_I2C_Reg(unsigned char deviceaddr, unsigned char *bmpbuffer, unsigned char len);
unsigned char C2120_Read_Reg_I2C(unsigned char devicereadaddr, unsigned char bytecount);
unsigned char C2120_Read_I2C_Buffer(unsigned char *buffer, unsigned char bytecount);

//BMP180 Functions
unsigned int CP2120_BMP180_Get_Cal(unsigned char cal_addr_msb, unsigned char cal_addr_lsb);

#endif /* FARADAY_HAL_CP2120_H_ */

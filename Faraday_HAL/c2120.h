/*
 * c2120.h
 *
 *  Created on: Sep 13, 2017
 *      Author: Brent
 */

#ifndef FARADAY_HAL_C2120_H_
#define FARADAY_HAL_C2120_H_

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

#endif /* FARADAY_HAL_C2120_H_ */

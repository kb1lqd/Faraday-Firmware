/*
 * c2120.h
 *
 *  Created on: Sep 13, 2017
 *      Author: Brent
 */

#ifndef FARADAY_HAL_C2120_H_
#define FARADAY_HAL_C2120_H_

#define C2120_SPI_CS BIT1 //P1.1
#define C2120_CMD_WRITE_REG 0x20 //Write internal register command
#define C2120_CMD_CONFIG 0x21 //Read internal register command
#define C2120_CMD_VER 0x40 //Read Version command
#define C2120_REG_IOSTATE 0x01 //Read Version command

unsigned char C2120_Write_Register(unsigned char addr, unsigned char value);
unsigned char C2120_Read_Register(unsigned char addr);
unsigned char C2120_Read_Version(void);

#endif /* FARADAY_HAL_C2120_H_ */

/*
 * lsm303.c
 *
 *  Created on: Nov 1, 2017
 *      Author: Brent
 */


#include "lsm303.h"
#include "cp2120.h"

void lsm303_test(void){
	volatile unsigned char testbuffer[32];

	unsigned char databytes[8];
	databytes[0] = LSM303_MAG_ADDRESS_WRITE;
	databytes[1] = LSM303_MAG_CTRL_REG1_A;

	CP2120_Write_I2C_Bytes(&databytes, 2, 1);
	CP2120_Read_I2C_Reg(LSM303_MAG_ADDRESS_READ, &testbuffer, 1, 0x00);

	__no_operation();
}


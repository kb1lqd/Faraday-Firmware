/*
 * bmp180.c
 *
 *  Created on: Sep 18, 2017
 *      Author: Brent
 */
#include "bmp180.h"
#include "../Faraday_HAL/cp2120.h";

void BMP180_Test(void){
	volatile unsigned char bmpbuffer[32];

	//CP2120_Write_I2C_Reg(BMP180_ADDRESS_WRITE, BMP180_ADDRESS_ID);
	//CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmpbuffer, 1);

	unsigned char databytes[8];
	volatile unsigned char bmp180_temp_msb, bmp180_temp_lsb;
	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = BMP180_ADDRESS_ID;

	CP2120_Write_I2C_Bytes(&databytes, 2);
	CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmpbuffer, 1);

	//Get CAL Data TEMP
	volatile unsigned char bmp180_ac1_msb, bmp180_ac1_lsb;
	volatile unsigned int bmp180_ac1, bmp180_ac2, bmp180_ac3, bmp180_ac4;
	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = BMP180_CAL_ADDR_AC1_MSB;
	CP2120_Write_I2C_Bytes(&databytes, 2);
	CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmp180_ac1_msb, 1);

	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = BMP180_CAL_ADDR_AC1_LSB;
	CP2120_Write_I2C_Bytes(&databytes, 2);
	CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmp180_ac1_lsb, 1);

	bmp180_ac1 = 0x00;
	bmp180_ac1 = bmp180_ac1_lsb;
	bmp180_ac1 |= (bmp180_ac1_msb<<8);

	bmp180_ac1 = 0x00;
	bmp180_ac1 = BMP180_Get_Cal(BMP180_CAL_ADDR_AC1_MSB, BMP180_CAL_ADDR_AC1_LSB);
	bmp180_ac2 = BMP180_Get_Cal(BMP180_CAL_ADDR_AC2_MSB, BMP180_CAL_ADDR_AC2_LSB);
	bmp180_ac3 = BMP180_Get_Cal(BMP180_CAL_ADDR_AC3_MSB, BMP180_CAL_ADDR_AC3_LSB);
	bmp180_ac4 = BMP180_Get_Cal(BMP180_CAL_ADDR_AC4_MSB, BMP180_CAL_ADDR_AC4_LSB);

	//START Temp conversion
	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = 0xF4;
	databytes[2] = 0x2E;
	CP2120_Write_I2C_Bytes(&databytes, 3);

	//Get Temp MSB
	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = 0xF6;
	CP2120_Write_I2C_Bytes(&databytes, 2);
	CP2120_Read_I2C_Reg(BMP180_ADDRESS_READ, &bmpbuffer, 1);
	bmp180_temp_msb = bmpbuffer[0];

	//Get Temp LSB
	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = 0xF7;
	CP2120_Write_I2C_Bytes(&databytes, 2);
	CP2120_Read_I2C_Reg(BMP180_ADDRESS_READ, &bmpbuffer, 1);
	bmp180_temp_lsb = bmpbuffer[0];


	CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmpbuffer, 1);

	//CP2120_Write_I2C_Reg(BMP180_ADDRESS_WRITE, 0x2E);
	//CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmpbuffer, 1);
}


unsigned int BMP180_Get_Cal(unsigned char cal_addr_msb, unsigned char cal_addr_lsb){
	unsigned char databytes[8];
	volatile unsigned char bmp180_cal_msb, bmp180_cal_lsb;
	volatile unsigned int bmp180_cal;
	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = cal_addr_msb;
	CP2120_Write_I2C_Bytes(&databytes, 2);
	CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmp180_cal_msb, 1);

	databytes[0] = BMP180_ADDRESS_WRITE;
	databytes[1] = cal_addr_lsb;
	CP2120_Write_I2C_Bytes(&databytes, 2);
	CP2120_Read_I2C_Reg(BMP180_ADDRESS_WRITE, &bmp180_cal_lsb, 1);

	bmp180_cal = 0x00;
	bmp180_cal = bmp180_cal_lsb;
	bmp180_cal |= (bmp180_cal_msb<<8);

	return bmp180_cal;
}

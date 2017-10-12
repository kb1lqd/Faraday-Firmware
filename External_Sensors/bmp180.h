/*
 * bmp180.h
 *
 *  Created on: Sep 18, 2017
 *      Author: Brent
 */

#ifndef EXTERNAL_SENSORS_BMP180_H_
#define EXTERNAL_SENSORS_BMP180_H_

// Main Addresses
#define BMP180_ADDRESS_WRITE 0xEE
#define BMP180_ADDRESS_READ 0xEF

// Global Addresses
#define BMP180_ADDRESS_ID 0xD0

// Calibration Data Addresses
#define BMP180_CAL_ADDR_AC1_MSB 0xAA
#define BMP180_CAL_ADDR_AC1_LSB 0xAB
#define BMP180_CAL_ADDR_AC2_MSB 0xAC
#define BMP180_CAL_ADDR_AC2_LSB 0xAD
#define BMP180_CAL_ADDR_AC3_MSB 0xAE
#define BMP180_CAL_ADDR_AC3_LSB 0xAF
#define BMP180_CAL_ADDR_AC4_MSB 0xB0
#define BMP180_CAL_ADDR_AC4_LSB 0xB1
#define BMP180_CAL_ADDR_AC5_MSB 0xB2
#define BMP180_CAL_ADDR_AC5_LSB 0xB3
#define BMP180_CAL_ADDR_AC6_MSB 0xB4
#define BMP180_CAL_ADDR_AC6_LSB 0xB5
#define BMP180_CAL_ADDR_B1_MSB 0xB6
#define BMP180_CAL_ADDR_B1_LSB 0xB7
#define BMP180_CAL_ADDR_B2_MSB 0xB8
#define BMP180_CAL_ADDR_B2_LSB 0xB9
#define BMP180_CAL_ADDR_MB_MSB 0xBA
#define BMP180_CAL_ADDR_MB_LSB 0xBB
#define BMP180_CAL_ADDR_MC_MSB 0xBC
#define BMP180_CAL_ADDR_MC_LSB 0xBD
#define BMP180_CAL_ADDR_MD_MSB 0xBE
#define BMP180_CAL_ADDR_MD_LSB 0xBF

void BMP180_Test(void);
unsigned int BMP180_Get_Cal(unsigned char cal_addr_msb, unsigned char cal_addr_lsb);

#endif /* EXTERNAL_SENSORS_BMP180_H_ */

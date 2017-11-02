/*
 * lsm303.h
 *
 *  Created on: Nov 1, 2017
 *      Author: Brent
 */

#ifndef EXTERNAL_DEVICES_LSM303_H_
#define EXTERNAL_DEVICES_LSM303_H_

/** @name LSM303 Device I2C Addresses
* 	@brief LSM303 Device I2C Addresses
@{**/
#define LSM303_ACCEL_ADDRESS_WRITE 0x32
#define LSM303_ACCEL_ADDRESS_READ 0x33
#define LSM303_MAG_ADDRESS_WRITE 0x3C
#define LSM303_MAG_ADDRESS_READ 0x3D
/** @}*/

/** @name LSM303 Magnetic Register Addresses
* 	@brief Memory addresses pointing to the magnetic devicew registers.
@{**/
#define LSM303_MAG_CTRL_REG1_A 0x20
/** @}*/


void lsm303_test(void);

#endif /* EXTERNAL_DEVICES_LSM303_H_ */

/** @file cp2120.h
 * 	@brief Provides a library to interact with the CP2120 SPI to I2C module
 *
 * 	This program provides an interface library to interact with the CP2120
 * 	SPI to I2C module. It is used to allow Faraday to interact with I2C items without switching
 * 	USCI modes. Do note that the SPI phase/polarity needs to be "11" configuration to use this
 * 	module.
 *
 */

#ifndef FARADAY_HAL_CP2120_H_
#define FARADAY_HAL_CP2120_H_

/** @name CP2120 SPI/I2C Wiring
* 	@brief Definitions that define the physical wiring of signals to the CP2120 module.
@{**/
#define CP2120_SPI_I2C_INT BIT5 //P2.5
#define CP2120_SPI_CS BIT1 //P1.1
/** @}*/

/** @name CP2120 register addresses
* 	@brief CP2120 internal register address definitions.
@{**/
#define CP2120_CMD_WRITE_REG 0x20 /**< Write internal register command */
#define CP2120_CMD_CONFIG 0x21 /**< Read internal register command */
#define CP2120_CMD_VER 0x40 /**< Read Version command */
#define CP2120_REG_IOCONFIG 0x00 /**< IOCONFIG register address */
#define CP2120_REG_I2CTO2 0x01 /**< I2CTO2 register address */
#define CP2120_REG_I2CCLOCK 0x02 /**< IOCONFIG register address */
#define CP2120_REG_I2CTO 0x03 /**< I2CTO register address */
#define CP2120_REG_I2CSTAT 0x04 /**< I2CSTAT register address */
#define CP2120_REG_I2CADR 0x05 /**< I2CADR register address */
#define CP2120_REG_RXBUFF 0x06 /**< RXBUFF register address */
#define CP2120_REG_IOCONFIG2 0x07 /**< IOCONFIG2 register address */
#define CP2120_REG_EDGEINT 0x09 /**< EDGEINT register address */
#define CP2120_REG_I2CTO2 0x09 /**< I2CTO2 register address */
/** @}*/


/** @name CP2120 I2C Status Codes
* 	@brief Status codes that describe the current state of the I2C device.
@{**/
#define CP2120_I2C_ACK 0xF0 /**< I2C SUCCESS (ACK) */
#define CP2120_I2C_SLAVE_ADDR_NAK 0xF1 /**< I2C Slave address NACKed */
#define CP2120_I2C_SLAVE_DATA_NAK 0xF2 /**< I2C Slave data NACKed */
#define CP2120_I2C_INPROGRESS 0xF3 /**< I2C Transaction in progress */
#define CP2120_I2C_TIMEOUT 0xF8 /**< I2C Transaction timed out */
#define CP2120_I2C_TXRXOVERFLOW 0xF9 /**< Command’s Bytes to Transmit Byte and Data Buffer Size do not match, or Read Buffer read number of bytes greater than buffer count. */
#define CP2120_I2C_SCLLOW 0xFA /**< I2C SCL Low time-out, using timer configured in I2CTO2. */
#define CP2120_I2C_BUSNOTFREE 0xFB/**< I2C bus free detect has been disabled, and the bus is not free. */
/** @}*/

/** @name CP2120 I2C READ/WRITE Commands
* 	@brief Command values that control READ/WRITE actions for the CP2120
@{**/
#define CP2120_I2C_WRITE 0x00 /**< Write I2C slave */
#define CP2120_I2C_READ 0x01 /**< Read I2C slave */
/** @}*/

/**@brief Simple testing function to example the CP2120
 *
 * Simple testing function to example the CP2120
 *
 *
 */
void test_CP2120(void);

/**@brief SPI Write to a single register
 *
 * SPI Write to a single register.
 *
 * @param addr CP2120 register address
 * @param value Value to write into the address
 *
 * @return 1
 *
 */
unsigned char CP2120_Write_Register(unsigned char addr, unsigned char value);

/**@brief SPI Read from a single register
 *
 * SPI Read from a single register.
 *
 * @param addr CP2120 register address
 *
 * @return Value read from register
 *
 */
unsigned char CP2120_Read_Register(unsigned char addr);

/**@brief CP2120 SPI read device version
 *
 * Reads the CP2120 version data. Currently only for debug as it returns nothing useful.
 *
 * @return 1
 *
 *
 */
unsigned char CP2120_Read_Version(void);

/**@brief Get I2CTO2 from CP2120
 *
 *
 *
 * @return I2CTO2
 *
 */
unsigned char CP2120_Get_I2CTO2(void);

/**@brief Get I2CCLOCK from CP2120
 *
 *
 *
 * @return I2CCLOCK
 *
 */
unsigned char CP2120_Get_I2CCLOCK(void);

/**@brief Get I2CTO from CP2120
 *
 *
 *
 * @return I2CTO
 *
 */
unsigned char CP2120_Get_I2CTO(void);

/**@brief Get I2CSTAT from CP2120
 *
 *
 *
 * @return I2CSTAT
 *
 */
unsigned char CP2120_Get_I2CSTAT(void);

/**@brief Get I2CADR from CP2120
 *
 *
 *
 * @return I2CADR
 *
 */
unsigned char CP2120_Get_I2CADR(void);

/**@brief Get RXBUFF from CP2120
 *
 *
 *
 * @return RXBUFF
 *
 */
unsigned char CP2120_Get_RXBUFF(void);

/**@brief Get IOCONFIG2 from CP2120
 *
 *
 *
 * @return IOCONFIG2
 *
 */
unsigned char CP2120_Get_IOCONFIG2(void);

/**@brief Get EDGEINT from CP2120
 *
 *
 *
 * @return EDGEINT
 *
 */
unsigned char CP2120_Get_EDGEINT(void);

/**@brief Write bytearray over I2C
 *
 * Write bytearray over I2C. Internal use, do not use.
 *
 * @param buffer Pointer to the array to write
 * @param len Length of data in bytes to write
 * @param getack_flag When not 0x00 this forces the function to wait for ACK from I2C device
 *
 */
unsigned char CP2120_Write_I2C_Bytes(unsigned char *buffer, unsigned char len, unsigned char getack_flag);

/**@brief Write bytearray over I2C
 *
 * Write bytearray over I2C. This is the high level function safe to use in application.
 *
 * @param bytes Pointer to the array to write
 * @param len Length of data in bytes to write
 *
 */
unsigned char CP2120_Write_Bytes_I2C(unsigned char *bytes, unsigned char len);

/**@brief Write I2C Register function (Low Level)
 *
 *	Low level function used by higher level functions to write bytes to I2C bus. Do not use unless you know what you are doing.
 *
 * @param devicewriteaddr Address of the device to write to
 * @param regaddr Register address to write into
 *
 */
unsigned char CP2120_Write_Reg(unsigned char devicewriteaddr, unsigned char regaddr);

/**@brief Write I2C Register function (High Level)
 *
 *	Higer level function to Write bytes into an I2C bus device. This function simply sends a write to the device to acknoledge what register will be written/read. (Deprecated?)
 *
 * @param deviceaddr Address of the device to write into
 * @param regaddr Register address for the intended register to interact with after the write
 * @param getack_flag When not 0x00 this forces the function to wait for ACK from I2C device
 *
 */
unsigned char CP2120_Write_I2C_Reg(unsigned char devicewriteaddr, unsigned char regaddr, unsigned char getack_flag);

/**@brief Read I2C Register function (Low Level)
 *
 *	Low level function used by higher level functions to Read bytes from an I2C bus device. Do not use unless you know what you are doing.
 *
 * @param deviceaddr Address of the device to read from
 * @param bmpbuffer Pointer to array to read into
 * @param len Length of bytes to read from device
 * @param getack_flag When not 0x00 this forces the function to wait for ACK from I2C device
 *
 */
unsigned char CP2120_Read_I2C_Reg(unsigned char deviceaddr, unsigned char *bmpbuffer, unsigned char len, unsigned char getack_flag);

/**@brief Read I2C Register function (High Level)
 *
 *	Higer level function to Read bytes from an I2C bus device.
 *
 * @param devicereadaddr Address of the device to read from
 * @param bytecount Length of bytes to read from device
 *
 */
unsigned char CP2120_Read_Reg_I2C(unsigned char devicereadaddr, unsigned char bytecount);

/**@brief Read data from CP2120 RX data buffer
 *
 * Reads data from the CP2120 reciever buffer.
 *
 * @param buffer Pointer to buffer array to save recieved data read into
 * @param bytecount Length in bytes to read
 *
 */
unsigned char CP2120_Read_I2C_Buffer(unsigned char *buffer, unsigned char bytecount);


#endif /* FARADAY_HAL_CP2120_H_ */

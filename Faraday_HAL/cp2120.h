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
#define CP2120_I2C_BUSNOTFREE /**< I2C bus free detect has been disabled, and the bus is not free. */
/** @}*/

/** @name CP2120 I2C READ/WRITE Commands
* 	@brief Command values that control READ/WRITE actions for the CP2120
@{**/
#define CP2120_I2C_WRITE 0x00 /**< Write I2C slave */
#define CP2120_I2C_READ 0x01 /**< Read I2C slave */
/** @}*/

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
void test_CP2120(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Write_Register(unsigned char addr, unsigned char value);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Read_Register(unsigned char addr);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Read_Version(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_I2CTO2(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_I2CCLOCK(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_I2CTO(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_I2CSTAT(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_I2CADR(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_RXBUFF(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_IOCONFIG2(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_EDGEINT(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Get_I2CTO2(void);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Write_I2C_Bytes(unsigned char *buffer, unsigned char len);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Write_Bytes_I2C(unsigned char *bytes, unsigned char len);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Write_Reg(unsigned char devicewriteaddr, unsigned char regaddr);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Write_Reg_I2C(unsigned char deviceaddr, unsigned char regaddr);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Read_I2C_Reg(unsigned char deviceaddr, unsigned char *bmpbuffer, unsigned char len);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Read_Reg_I2C(unsigned char devicereadaddr, unsigned char bytecount);

/**@brief
 *
 *
 *
 * @param data_pointer
 * @param
 *
 */
unsigned char CP2120_Read_I2C_Buffer(unsigned char *buffer, unsigned char bytecount);


#endif /* FARADAY_HAL_CP2120_H_ */

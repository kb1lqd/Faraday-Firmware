/** @file SPI.h
 * 	@brief Hardware abstraction functions for SPI
 *
 * 	These functions provide an abstraction layer for the CC430 SPI peripheral.
 *
 */

#ifndef FARADAY_HAL_SPI_H_
#define FARADAY_HAL_SPI_H_


/* DEFINITIONS */
#define SPI_DUMMY_BYTE 0x00
#define SPI_HAL_CS_SRAM BIT0
#define SPI_HAL_CS_I2C BIT1

/**@brief Shift a byte into the SPI transmit register (polling)
 *
 * This is the main function used to directly shift a byte into the SPI transmit register
 * to transmit the byte over SPI.
 *
 * @note This routine is a polling method SPI interaction.
 *
 *
 */
void spi_tx(unsigned char tx);
unsigned char spi_rx_byte(unsigned char delay_cycles);
unsigned char spi_enable_chip_select(unsigned char SPI_HAL_CS);
unsigned char spi_disable_chip_select(unsigned char SPI_HAL_CS);
void Faraday_SRAM_CS_Enable(void);
void Faraday_SRAM_CS_Disable(void);
void Faraday_SRAM_Hold_Enable(void); // Useful for when devloping a priority switching SPI interface
void Faraday_SRAM_Hold_Disable(void); // Useful for when devloping a priority switching SPI interface

#endif /* FARADAY_HAL_SPI_H_ */

/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       sx1276.c
 * \brief      SX1276 RF chip driver
 *
 * \version    2.0.0 
 * \date       May 6 2013
 * \author     Gregory Cristian
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#include "sx1276-Hal.h"
#include "spi.h"
//#include "intrins.h"

uint16_t HW_SPI_InOut( uint16_t txData )
{
  uint16_t rxData ;

  HAL_SPI_TransmitReceive_DMA( &hspi1, ( uint8_t * ) &txData, ( uint8_t* ) &rxData, 1);	

  return rxData;
}

/*!
 * \brief Initializes the radio interface I/Os
 */
void SX1276InitIo( void )
{

    

}

/*!
 * \brief Set the radio reset pin state
 * 
 * \param state New reset pin state
 */
void SX1276SetReset( uint8_t state )
{
 if( state == RADIO_RESET_ON )
    
			RF_RES=0;
		
		else
			RF_RES=1;
}
/*!
 * \brief Writes the radio register at the specified address
 *
 * \param [IN]: addr Register address
 * \param [IN]: data New register value
 */
void SX1276Write( uint8_t addr, uint8_t data )
{
	  SX1276WriteBuffer( addr, &data, 1 );
}
/*!
 * \brief Reads the radio register at the specified address
 *
 * \param [IN]: addr Register address
 * \param [OUT]: data Register value
 */
void SX1276Read( uint8_t addr, uint8_t *data )
{
//		    uint8_t data;
    SX1276ReadBuffer( addr, data, 1 );
//    return data;
}
/*!
 * \brief Writes multiple radio registers starting at address
 *
 * \param [IN] addr   First Radio register address
 * \param [IN] buffer Buffer containing the new register's values
 * \param [IN] size   Number of registers to be written
 */
void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
		uint8_t i;
		RF_CS=0; //NSS = 1;
			HW_SPI_InOut( addr | 0x80 );
			for( i = 0; i < size; i++ )
			{
						HW_SPI_InOut( buffer[i] );
			}
		RF_CS=1; //NSS = 1;


}
/*!
 * \brief Reads multiple radio registers starting at address
 *
 * \param [IN] addr First Radio register address
 * \param [OUT] buffer Buffer where to copy the registers data
 * \param [IN] size Number of registers to be read
 */
void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;
		RF_CS=0; //NSS = 0;

    HW_SPI_InOut( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
          buffer[i] = HW_SPI_InOut( 0 );
    }

		RF_CS=1;//NSS = 1;
}

/*!
 * \brief Writes the buffer contents to the radio FIFO
 *
 * \param [IN] buffer Buffer containing data to be put on the FIFO.
 * \param [IN] size Number of bytes to be written to the FIFO
 */
void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
   SX1276WriteBuffer( 0, buffer, size );

}

/*!
 * \brief Reads the contents of the radio FIFO
 *
 * \param [OUT] buffer Buffer where to copy the FIFO read data.
 * \param [IN] size Number of bytes to be read from the FIFO
 */
void SX1276ReadFifo( uint8_t *buffer, uint8_t size )
{
   SX1276ReadBuffer( 0, buffer, size );
}

inline uint8_t SX1276ReadDio0( void )
{
    return   PAin->b12;
}

inline uint8_t SX1276ReadDio1( void )
{
    return   PAin->b15;
}

inline uint8_t SX1276ReadDio2( void )
{
    return  PBin->b3;
}

inline uint8_t SX1276ReadDio3( void )
{
    return   PBin->b4;
}

inline uint8_t SX1276ReadDio4( void )
{
    return   PBin->b5;
}

inline uint8_t SX1276ReadDio5( void )
{
    return   0;
}

inline void SX1276WriteRxTx( uint8_t txEnable )
{
    if( txEnable != 0 )
    {
    PA_TX=0;
		PA_RX=1;
    }
    else
    {
 		PA_TX=1;
		PA_RX=0;
    }
}





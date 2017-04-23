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
//#include "spi.h"
//#include "intrins.h"
static void delay(uint32_t n)
{
	while(n--);
}
static uint8_t SPI_SendByte(uint16_t txData)  
{  
	
	
//	uint16_t rxData ;

//  HAL_SPI_TransmitReceive( &hspi1, ( uint8_t * ) &txData, ( uint8_t* ) &rxData, 1, HAL_MAX_DELAY);	

//  return rxData;
//			uint8_t aTxBuffer[2]={byte};
//	   uint8_t aRxBuffer[2]={0};
////	
//	  if(HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)aTxBuffer, (uint8_t *)aRxBuffer, 1,100) != HAL_OK)
//  {
//    /* Transfer error in transmission process */
//    Error_Handler();
//  }
////  while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
////  {
////  } 	
//	return aRxBuffer[0];
//	while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY); 
//  SPI_SendData8(SPI2,TxData);  
//  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);   
//  return SPI_ReceiveData8(SPI2); 
	
//		uint8_t dat=0;
//   while(!SPI1->SR&(1<<1));//ÅÐ¶Ï·¢ËÍ»º³åÆ÷ÊÇ·ñÎª¿Õ
//   SPI1->DR=byte;
//   while(!(SPI1->SR&0X01));//ÅÐ¶ÏÊÇ·ñ½ÓÊÕÆ÷²»¿Õ
//   dat=SPI1->DR;
//   return dat;
	 
	 
//while((SPI1->SR&1<<1)==0)//??????
//			while((SPI1->SR&1<<1)==0);
//    SPI1->DR = byte;
//    while((SPI1->SR&1<<0)==0);
//    return SPI1->DR;

//		while((SPI1->SR && 1<<1)==0);
//    SPI1->DR = byte;
//    while((SPI1->SR && 1<<0)==0);
//    return SPI1->DR;


// while ((SPI1->SR & SPI_FLAG_TXE) == RESET){}//??????  
//	
//	SPI1->DR = byte; //????SPIx????byte  ??
//		
// while ((SPI1->SR & SPI_FLAG_RXNE) == RESET){} //???????byte  
// 
//	return SPI1->DR;; //????SPIx???????	

//unsigned char  n=8; // ?MISO??????????,??? 
//unsigned char tdata; 
//SCK = 1; //???? 
////SS1 = 0; //???? 
//while(n--) 
//{ 
////		_nop_(); 
//	delay(1);
//		SCK = 0; //???? 
////		_nop_(); 
//		 delay(1);
//		tdata = tdata<<1; // ????,?_crol_(temp,1) 
//		if(MISO == 1) 
//		tdata = tdata|0x01; // ???????1,?????????1 
//		else 
//		tdata = tdata&0xfe; // ??????????0 
//		if((byte&0x80) == 0x80) // ???????????1????1 
//		{ 
//		M0SI = 1; // ???1 
//		} 
//		else 
//		 
//		M0SI = 0; // ?????0 
//		 
//		byte = byte<<1; // ?????? 
//		 
//		SCK=1; 
//} 
//return(tdata); 

u16 bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) 
   	{
		if(txData & 0x80)
		M0SI1;         
		else
		M0SI0;
		txData = (txData << 1);          
		SCK1; 
		delay(1);
		if(MISO)                    
		txData |= 0x01;       		  
		SCK0; 
		delay(1);           		 
   	}
    return(txData); 
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
		SX1276ReadBuffer( addr, data, 1 );
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
//	uint8_t aTxBuffer[1]={addr | 0x80 };
     RF_CS=0; //NSS = 0;
//	HAL_Delay(1);
//		  while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
//  {
//  } 
//	if(HAL_SPI_Transmit(&hspi1, (uint8_t*)aTxBuffer,1,100) != HAL_OK)
//  {
//    /* Transfer error in transmission process */
//    Error_Handler();
//  }
//	
//	  while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
//  {
//  } 
//		if(HAL_SPI_Transmit(&hspi1, (uint8_t*)buffer,size,100) != HAL_OK)
//  {
//    /* Transfer error in transmission process */
//    Error_Handler();
//  }
//	

	 SPI_SendByte( addr | 0x80 ); /* Bit_7=1 equal write */
    for( i = 0; i < size; i++ )
    {
        SPI_SendByte( buffer[i] );
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
//	HAL_Delay(1);
//	  while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
//  {
//  } 	
//	 if(HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)(addr & 0x7F) , (uint8_t *)buffer, size,100) != HAL_OK)
//  {
//    /* Transfer error in transmission process */
//    Error_Handler();
//  }

	 SPI_SendByte( addr & 0x7F ); /* Bit_7=0 equal read */
    for( i = 0; i < size; i++ )
    {
        buffer[i] = SPI_SendByte( 0 );
    }
//	
	RF_CS=1;;//NSS = 1;
}

/*!
 * \brief Writes the buffer contents to the radio FIFO
 *
 * \param [IN] buffer Buffer containing data to be put on the FIFO.
 * \param [IN] size Number of bytes to be written to the FIFO
 */
void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
//  	uint8_t i;
//     RF_CS=0; //NSS = 0;
//	  SPI_SendByte( 0 & 0x7F ); /* Bit_7=0 equal read */
//    for( i = 0; i < size; i++ )
//    {
//        SPI_SendByte( buffer[i] );
//    }
//	RF_CS=1; //NSS = 1;

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
//   uint8_t i;
//	RF_CS=0; //NSS = 0;
//	 SPI_SendByte( 0 & 0x7F ); /* Bit_7=0 equal read */
//    for( i = 0; i < size; i++ )
//    {
//        buffer[i] = SPI_SendByte( 0 );
//    }
//	
//	RF_CS=1;;//NSS = 1;
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

//static void RFInit()  
//{  
//    Radio->LoRaSetOpMode( RFLR_OPMODE_STANDBY );  
//    // set the RF settings  
//    Radio->LoRaSetPa20dBm( false );  
//    Radio->LoRaSetRFPower( 5 );  
//    Radio->LoRaSetSpreadingFactor( 7 ); // SF6 only operates in implicit header mode.  
//    Radio->LoRaSetErrorCoding( 1 );  
//    Radio->LoRaSetPacketCrcOn( 0 );  
//    Radio->LoRaSetSignalBandwidth( 7 );  
//    Radio->LoRaSetImplicitHeaderOn( 0 );    
//    Radio->LoRaSetSymbTimeout( 0x3FF );  
//    Radio->LoRaSetPayloadLength( 128 );  
//    Radio->LoRaSetLowDatarateOptimize( true );  
//    Radio->LoRaSetFreqHopOn(false);      
//    Radio->LoRaSetRxSingleOn(true);  
//    Radio->LoRaSetPreambleLength( 6 );   
//    Radio->LoRaSetOpMode( RFLR_OPMODE_STANDBY );  
//}  



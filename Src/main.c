/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
////////////BSP/////////////
#include "oled.h"
#include "bsp.h"
#include "string.h"
//////////RF////////////////
#include "radio.h"
#include "platform.h"
#include "sx1276.h"
#include "sx1276-Fsk.h"
#include "sx1276-Hal.h"
#include "sx1276-LoRa.h"
////////////////////////////
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define oled
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
static uint16_t TRSIZE  =   13;//BUFFER_SIZE-3
#define BUFFER_SIZE                                 16 // Define the payload size here
static uint16_t BufferSize = BUFFER_SIZE;			// RF buffer size
static uint8_t Sendbuffer[BUFFER_SIZE]={ 0, 1, 2, 3, 4, 5 ,6,7,8,9,10,11,12,0,0,0};					// RF buffer
static uint8_t Ascbuffer[BUFFER_SIZE]={ 0, 1, 2, 3, 4, 5 ,6,7,8,9,10,11,12,0,0,0};

//static uint8_t EnableMaster = true; 				// Master/Slave selection

tRadioDriver *Radio = NULL;



/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void OnMaster( void );
void OnSlave( void );
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  uint8_t test=0,RISS=0 ;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();

  /* USER CODE BEGIN 2 */
	
#ifdef oled
  MX_I2C1_Init();
		OLED_Init();			//��ʼ��OLED  
		OLED_ShowString(0,0,"oledok",16);
		HAL_Delay(1000);
		OLED_Clear();
#endif

		SX1276Read(0x42,&test);//??0x12
 if(test!=0x12)
 {
#ifdef oled
	 	   OLED_ShowString(0,0,"ERROR1",16);
#endif	 
	 ledR=0;
		 while(1)
		 {
		 }
 }
  
 SX1276Read(0x44,&test);//??0x2D
  if(test!=0x2D)
 {	
#ifdef oled	 
	 OLED_ShowString(0,0,"ERROR2",16);
#endif
	 ledR=0;
		 while(1)
		 {
		 }
 }
	Radio = RadioDriverInit( ); 
    Radio->Init( );
    Radio->StartRx( );
#ifdef oled	 
		OLED_ShowString(0,0,"sx1278ok",16);
  OLED_Clear();
								OLED_ShowString(0,0,"mtx:",16);
								OLED_ShowNum(35,0,Sendbuffer[(TRSIZE+1)],3,16);
								OLED_ShowString(65,0,"asc:",16);
								OLED_ShowNum(100,0,Sendbuffer[TRSIZE],3,16);
								OLED_ShowString(0,2,"riss:",16);
 								OLED_ShowString(45,2,"s",16);
 								OLED_ShowString(90,2,"m",16);
 

#endif
	ledB=0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		#ifdef oled	
			OnSlave();
//		HAL_Delay(50);
		
		OLED_ShowNum(60,2,RISS,3,16);
		#else
		
		OnMaster();	
		HAL_Delay(500);
		Sendbuffer[(TRSIZE+2)]=RISS;
		#endif

  RISS=(uint8_t)SX1276LoRaGetPacketRssi();
	
	}	
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
 uint8_t RFWrite(uint8_t* buff, uint8_t size);
uint8_t RFRead(uint8_t* buff );
void OnMaster( void )
{
	uint8_t  buff[BUFFER_SIZE]={0};
	uint8_t i,error = 0;
	RFWrite(Sendbuffer,BufferSize);

	if( RFRead(buff) > 0 )
	{
		for (i=0, error=0; i<TRSIZE; i++ )
            {
                if (buff[i] != Ascbuffer[i])     { error=2; break; }
								else error=1;
            }
						if (error==1)    
							{ 
//								OLED_ShowNum(105,0,buff[TRSIZE],3,16);
								 ledB=!ledB;
							Sendbuffer[TRSIZE]++;
								
							}
				
	}
//	OLED_ShowNum(35,0,Sendbuffer[TRSIZE],3,16); 
	ledR=!ledR;
 		Sendbuffer[(TRSIZE+1)]++;
}								


void OnSlave( void )
{
	    uint8_t error = 0;
    uint8_t i;
uint8_t  buff[BUFFER_SIZE]={0};   
        if( RFRead(buff) > 0 )
        {
            for (i=0, error=0; i<TRSIZE; i++ )
            {
                if (Sendbuffer[i] != buff[i])     { error=2; break; }
								else error=1;
            }
							if (error==1)    
							{ 
                // Indicates on a LED that the received frame is a PING
				
								 RFWrite( Ascbuffer, BufferSize );
							#ifdef oled

								OLED_ShowNum(35,0,buff[(TRSIZE+1)],3,16);

								OLED_ShowNum(100,0,buff[TRSIZE],3,16);
								OLED_ShowNum(105,2,buff[(TRSIZE+2)],3,16);
							#endif	
							
                ledB=!ledB;
            }
        }
}


 uint8_t RFWrite(uint8_t* buff, uint8_t size)
{
  //  Radio->LoRaSetRFFrequency( freq );// 478750000   DownChannel[10]
    Radio->SetTxPacket( buff, size);
    while( Radio->Process( ) != RF_TX_DONE );
     	Radio->StartRx( );
    return size;
}
uint8_t RFRead(uint8_t* buff )
{
  uint32_t result;
 	uint16_t RxLen;

// Radio->LoRaSetRFFrequency( freq ); 
 	


	 while( 1 )
	 {
		result = Radio->Process( );///SX1276LoRaProcess
		 if( (result == RF_RX_DONE) || (result == RF_RX_TIMEOUT) )
		 {
			 break;
		 }
	 }

		 if( result == RF_RX_DONE )//RFBuffer
		 {
			 Radio->GetRxPacket( buff, &RxLen );
			 
			 return RxLen;
		 }
		else
		 {
			return 0;
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
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

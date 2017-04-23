/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#include "usart.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/******************************************************************************
           �������´��룬֧��printf������������Ҫѡ��use MicroLIB
******************************************************************************/

//#if Printf_Support_En == 1

//#ifdef __ICCARM__  //IAR֧��

///**
//  *****************************************************************************
//  * @Name   : �ض���out_char����
//  *
//  * @Brief  : none
//  *
//  * @Input  : ch�������ַ�
//  *
//  * @Output : none
//  *
//  * @Return : none
//  *****************************************************************************
//**/
//int putchar(int c)
//{
//	uint16_t timeout = 0;
//	
//	
//	USART_SendData(USART1, (uint16_t)c);  //��������
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)  //ѭ�����ͣ�ֱ���������
//	{
//		timeout++;
//		if (timeout > 800)
//		{
//			timeout = 0;
//			break;
//		}
//	}
//	
//	return c;
//}


//#else  //MDK֧��

//#pragma import(__use_no_semihosting)
////
////��׼����Ҫ��֧�ֺ���
////
//struct __FILE 
//{ 
//	int handle; 

//};
///* FILE is typedef�� d in stdio.h. */
//FILE __stdout;
////
////����_sys_exit()�Ա���ʹ�ð�����ģʽ
////
//_sys_exit(int x)
//{
//	x = x;
//}

///**
//  *****************************************************************************
//  * @Name   : �ض���fputc����
//  *
//  * @Brief  : none
//  *
//  * @Input  : ch�������ַ�
//  *           *f: FILEָ��
//  *
//  * @Output : none
//  *
//  * @Return : none
//  *****************************************************************************
//**/
//int fputc(int ch, FILE *f)
//{
//	uint16_t timeout = 0;
//	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)  //ѭ�����ͣ�ֱ���������
//	{
//		timeout++;
//		if (timeout > 800)
//		{
//			timeout = 0;
//			break;
//		}
//	}
//	USART_SendData(USART1, (uint16_t)ch);  //��������
//	
//	return ch;
//}

//#endif

//#else

///**
//  *****************************************************************************
//  * @Name   : ���ڷ���һ���ֽ�
//  *
//  * @Brief  : none
//  *
//  * @Input  : byte�������ַ�
//  *
//  * @Output : none
//  *
//  * @Return : none
//  *****************************************************************************
//**/
//void uart_sendbyte(uint8_t byte)
//{
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//	USART_SendData(USART1, byte);
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//}

///**
//  *****************************************************************************
//  * @Name   : ���ڷ����ַ���
//  *
//  * @Brief  : none
//  *
//  * @Input  : *str�������ַ���
//  *
//  * @Output : none
//  *
//  * @Return : none
//  *****************************************************************************
//**/
//void uart_senfstring(uint8_t * str)
//{
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//	while (*str != '\0')
//	{
//		USART_SendData(USART1, *(str++));
//		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//	}
//}

///**
//  *****************************************************************************
//  * @Name   : ���ڸ�ʽ����ӡ
//  *
//  * @Brief  : none
//  *
//  * @Input  : *format����ʽ���ַ���
//  *           ...:     �䳤����
//  *
//  * @Output : none
//  *
//  * @Return : none
//  *****************************************************************************
//**/
//#include <stdarg.h>
//void uart_printf(char *format, ...)
//{
//	va_list ap;
//	char string[512];
//	
//	va_start(ap, format);
//	vsprintf(string, format, ap);
//	va_end(ap);
//	
//	uart_senfstring((uint8_t *)string);
//}

//#endif

/*************************************   end   *******************************/

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_7B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  }
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

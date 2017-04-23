#ifndef _GPIOBIT_h
#define _GPIOBIT_h
/******************************************************************************
                              位带操作相关宏定义
                       参考《CM3权威指南》第87 ~ 92页
******************************************************************************/
//#define  __CORTEX_M  0x00
#if __CORTEX_M == 0x00  //Cortex-M0

typedef struct
{
	unsigned short int b0  : 1;
	unsigned short int b1  : 1;
	unsigned short int b2  : 1;
	unsigned short int b3  : 1;
	unsigned short int b4  : 1;
	unsigned short int b5  : 1;
	unsigned short int b6  : 1;
	unsigned short int b7  : 1;
	unsigned short int b8  : 1;
	unsigned short int b9  : 1;
	unsigned short int b10 : 1;
	unsigned short int b11 : 1;
	unsigned short int b12 : 1;
	unsigned short int b13 : 1;
	unsigned short int b14 : 1;
	unsigned short int b15 : 1;
} REG16_TypeDef;

#elif __CORTEX_M == 0x03 || __CORTEX_M == 0x04  //Cortex-M3 or Cortex-M4

#define BITBAND(addr, bitnum)                    ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr)                           *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)                   MEM_ADDR(BITBAND(addr, bitnum))

#endif

/******************************************************************************
                                  GPIO地址映射
                          基地址加上寄存器偏移地址组成
******************************************************************************/

#if __CORTEX_M == 0x00  //Cortex-M0

#define GPIOA_ODR_Addr                           (GPIOA_BASE + 0x14)  //0x48000014
#define GPIOB_ODR_Addr                           (GPIOB_BASE + 0x14)  //0x48000414
#define GPIOC_ODR_Addr                           (GPIOC_BASE + 0x14)  //0x48000814
#define GPIOD_ODR_Addr                           (GPIOD_BASE + 0x14)  //0x48000C14
#define GPIOE_ODR_Addr                           (GPIOE_BASE + 0x14)  //0x48001014
#define GPIOF_ODR_Addr                           (GPIOF_BASE + 0x14)  //0x48001414

#define GPIOA_IDR_Addr                           (GPIOA_BASE + 0x10)  //0x48000010
#define GPIOB_IDR_Addr                           (GPIOB_BASE + 0x10)  //0x48000410
#define GPIOC_IDR_Addr                           (GPIOC_BASE + 0x10)  //0x48000810
#define GPIOD_IDR_Addr                           (GPIOD_BASE + 0x10)  //0x48000C10
#define GPIOE_IDR_Addr                           (GPIOE_BASE + 0x10)  //0x48001010
#define GPIOF_IDR_Addr                           (GPIOF_BASE + 0x10)  //0x48001410

#elif __CORTEX_M == 0x03  //Cortex-M3

#define GPIOA_ODR_Addr                           (GPIOA_BASE + 0x0C)  //0x4001080C
#define GPIOB_ODR_Addr                           (GPIOB_BASE + 0x0C)  //0x40010C0C
#define GPIOC_ODR_Addr                           (GPIOC_BASE + 0x0C)  //0x4001100C
#define GPIOD_ODR_Addr                           (GPIOD_BASE + 0x0C)  //0x4001140C
#define GPIOE_ODR_Addr                           (GPIOE_BASE + 0x0C)  //0x4001180C
#define GPIOF_ODR_Addr                           (GPIOF_BASE + 0x0C)  //0x40011A0C
#define GPIOG_ODR_Addr                           (GPIOG_BASE + 0x0C)  //0x40011E0C

#define GPIOA_IDR_Addr                           (GPIOA_BASE + 0x08)  //0x40010808
#define GPIOB_IDR_Addr                           (GPIOB_BASE + 0x08)  //0x40010C08
#define GPIOC_IDR_Addr                           (GPIOC_BASE + 0x08)  //0x40011008
#define GPIOD_IDR_Addr                           (GPIOD_BASE + 0x08)  //0x40011408
#define GPIOE_IDR_Addr                           (GPIOE_BASE + 0x08)  //0x40011808
#define GPIOF_IDR_Addr                           (GPIOF_BASE + 0x08)  //0x40011A08
#define GPIOG_IDR_Addr                           (GPIOG_BASE + 0x08)  //0x40011E08

#elif __CORTEX_M == 0x04  //Cortex-M4

#define GPIOA_ODR_Addr                           (GPIOA_BASE + 0x14)  //0x40020014
#define GPIOB_ODR_Addr                           (GPIOB_BASE + 0x14)  //0x40020414
#define GPIOC_ODR_Addr                           (GPIOC_BASE + 0x14)  //0x40020814
#define GPIOD_ODR_Addr                           (GPIOD_BASE + 0x14)  //0x40020C14
#define GPIOE_ODR_Addr                           (GPIOE_BASE + 0x14)  //0x40021014
#define GPIOF_ODR_Addr                           (GPIOF_BASE + 0x14)  //0x40021414
#define GPIOG_ODR_Addr                           (GPIOG_BASE + 0x14)  //0x40021814

#define GPIOA_IDR_Addr                           (GPIOA_BASE + 0x10)  //0x40020010
#define GPIOB_IDR_Addr                           (GPIOB_BASE + 0x10)  //0x40020410
#define GPIOC_IDR_Addr                           (GPIOC_BASE + 0x10)  //0x40020810
#define GPIOD_IDR_Addr                           (GPIOD_BASE + 0x10)  //0x40020C10
#define GPIOE_IDR_Addr                           (GPIOE_BASE + 0x10)  //0x40021010
#define GPIOF_IDR_Addr                           (GPIOF_BASE + 0x10)  //0x40021410
#define GPIOG_IDR_Addr                           (GPIOG_BASE + 0x10)  //0x40021810

#endif

/******************************************************************************
                       实现单一IO操作，类似于51的IO操作
                              n值要小于IO具体数目
******************************************************************************/

#if __CORTEX_M == 0x00  //Cortex-M0

#define PAout                                    ((volatile REG16_TypeDef *)GPIOA_ODR_Addr)
#define PAin                                     ((volatile REG16_TypeDef *)GPIOA_IDR_Addr)

#define PBout                                    ((volatile REG16_TypeDef *)GPIOB_ODR_Addr)
#define PBin                                     ((volatile REG16_TypeDef *)GPIOB_IDR_Addr)

#define PCout                                    ((volatile REG16_TypeDef *)GPIOC_ODR_Addr)
#define PCin                                     ((volatile REG16_TypeDef *)GPIOC_IDR_Addr)

#define PDout                                    ((volatile REG16_TypeDef *)GPIOD_ODR_Addr)
#define PDin                                     ((volatile REG16_TypeDef *)GPIOD_IDR_Addr)

#define PEout                                    ((volatile REG16_TypeDef *)GPIOE_ODR_Addr)
#define PEin                                     ((volatile REG16_TypeDef *)GPIOE_IDR_Addr)

#define PFout                                    ((volatile REG16_TypeDef *)GPIOF_ODR_Addr)
#define PFin                                     ((volatile REG16_TypeDef *)GPIOF_IDR_Addr)

#elif __CORTEX_M == 0x03 || __CORTEX_M == 0x04  //Cortex-M3 or Cortex-M4

#define PAout(n)                                 BIT_ADDR(GPIOA_ODR_Addr, n)  //输出 
#define PAin(n)                                  BIT_ADDR(GPIOA_IDR_Addr, n)  //输入 

#define PBout(n)                                 BIT_ADDR(GPIOB_ODR_Addr, n)  //输出 
#define PBin(n)                                  BIT_ADDR(GPIOB_IDR_Addr, n)  //输入 

#define PCout(n)                                 BIT_ADDR(GPIOC_ODR_Addr, n)  //输出 
#define PCin(n)                                  BIT_ADDR(GPIOC_IDR_Addr, n)  //输入 

#define PDout(n)                                 BIT_ADDR(GPIOD_ODR_Addr, n)  //输出 
#define PDin(n)                                  BIT_ADDR(GPIOD_IDR_Addr, n)  //输入 

#define PEout(n)                                 BIT_ADDR(GPIOE_ODR_Addr, n)  //输出 
#define PEin(n)                                  BIT_ADDR(GPIOE_IDR_Addr, n)  //输入

#define PFout(n)                                 BIT_ADDR(GPIOF_ODR_Addr, n)  //输出 
#define PFin(n)                                  BIT_ADDR(GPIOF_IDR_Addr, n)  //输入

#define PGout(n)                                 BIT_ADDR(GPIOG_ODR_Addr, n)  //输出 
#define PGin(n)                                  BIT_ADDR(GPIOG_IDR_Addr, n)  //输入

#endif

//typedef enum {FALSE = 0, TRUE = !FALSE} bool;

#if __CORTEX_M == 0x00  //Cortex-M0

typedef unsigned       char u8;
typedef unsigned short int  u16;
typedef unsigned       int  u32;

#endif

#endif  /* end gpio_bit.h */

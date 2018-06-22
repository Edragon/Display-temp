#ifndef _SPI_TOUCH_H_
#define _SPI_TOUCH_H_

#include "stm32f0xx.h"
// ------------------------------------
// Ó²¼þÁ¬½Ó£ºPB10---T-INT
//           PA4----T-CS 
//           PA5----T-CLK
//           PA6----T-OUT
// 					 PA7----T-DIN
//          SPI1-- AF0
//
// -------------------------------------
#define TOUCH_INT_PIN        GPIO_Pin_10
#define TOUCH_INT_PORT       GPIOB
#define TOUCH_INT_PIN_SCK    RCC_AHBPeriph_GPIOB

#define TOUCH_CS_PIN        GPIO_Pin_4
#define TOUCH_CS_PORT       GPIOA
#define TOUCH_CS_PIN_SCK    RCC_AHBPeriph_GPIOA

#define TOUCH_SCK_PIN        GPIO_Pin_5
#define TOUCH_SCK_PORT       GPIOA
#define TOUCH_SCK_PIN_SCK    RCC_AHBPeriph_GPIOA
#define TOUCH_SCK_SOURCE     GPIO_PinSource5
#define TOUCH_SCK_AF         GPIO_AF_0

#define TOUCH_MISO_PIN       GPIO_Pin_6
#define TOUCH_MISO_PORT      GPIOA
#define TOUCH_MISO_PIN_SCK   RCC_AHBPeriph_GPIOA
#define TOUCH_MISO_SOURCE    GPIO_PinSource6
#define TOUCH_MISO_AF        GPIO_AF_0

#define TOUCH_MOSI_PIN       GPIO_Pin_7
#define TOUCH_MOSI_PORT      GPIOA
#define TOUCH_MOSI_PIN_SCK   RCC_AHBPeriph_GPIOA
#define TOUCH_MOSI_SOURCE    GPIO_PinSource7
#define TOUCH_MOSI_AF        GPIO_AF_0


#define TOUCH_SPI1               RCC_APB2Periph_SPI1



void AD7845_Init(void);
void TOUCH_EXT_Int(void);

#endif  /* _SPI_TOUCH_H_ */
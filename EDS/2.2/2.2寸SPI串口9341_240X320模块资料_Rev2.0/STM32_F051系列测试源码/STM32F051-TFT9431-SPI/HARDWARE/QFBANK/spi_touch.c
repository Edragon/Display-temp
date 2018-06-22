#include "spi_touch.h"


	/******************************************************
* 函数名：AD7845_Init();
* 描述  ：初始化ADC784的spi接口
* 输入  : 首先配置时钟，然后配置GPIO，最后配置ADC端口复用
* 输出  ：无
* 注意  ：
*********************************************************/ 
void AD7845_Init(void)
{ 
	//设置需要配置的参数
	GPIO_InitTypeDef  GPIO_InitStruct;
  SPI_InitTypeDef   SPI_InitStruct;
	//配置时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	 RCC_AHBPeriphClockCmd(TOUCH_CS_PIN_SCK|TOUCH_SCK_PIN_SCK|TOUCH_MISO_PIN_SCK | TOUCH_MOSI_PIN_SCK|TOUCH_INT_PIN_SCK , ENABLE);
	 RCC_APB2PeriphClockCmd(TOUCH_SPI1, ENABLE); 
	//配置spi使用到的GPIO端口
	
// 	/< Configure TOUCH_SPI pins: SCK */
  GPIO_InitStruct.GPIO_Pin = TOUCH_SCK_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(TOUCH_SCK_PORT, &GPIO_InitStruct);

  /*!< Configure TOUCH_SPI pins: MISO */
  GPIO_InitStruct.GPIO_Pin = TOUCH_MISO_PIN;
  GPIO_Init(TOUCH_MISO_PORT, &GPIO_InitStruct);

  /*!< Configure TOUCH_SPI pins: MOSI */
  GPIO_InitStruct.GPIO_Pin =TOUCH_MOSI_PIN;
  GPIO_Init(TOUCH_MOSI_PORT, &GPIO_InitStruct);

  /*!< Configure TOUCH_CS_PIN pin */
  GPIO_InitStruct.GPIO_Pin =TOUCH_CS_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(TOUCH_CS_PORT, &GPIO_InitStruct);
	
   /*!< Configure TOUCH_TIN_PIN pin */
	GPIO_InitStruct.GPIO_Pin =TOUCH_INT_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(TOUCH_INT_PORT, &GPIO_InitStruct);
	//复用配置
  GPIO_PinAFConfig(TOUCH_SCK_PORT, TOUCH_SCK_SOURCE, TOUCH_SCK_AF);
  GPIO_PinAFConfig(TOUCH_MISO_PORT, TOUCH_MISO_SOURCE, TOUCH_MISO_AF); 
  GPIO_PinAFConfig(TOUCH_MOSI_PORT, TOUCH_MOSI_SOURCE, TOUCH_MOSI_AF);
	
	//配置spi
	SPI_TOUCH_CS_HIGH();
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStruct);
  
  SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
  
  SPI_Cmd(SPI1, ENABLE); /*!< TOUCH_SPI enable */
	
	}
	/******************************************************
* 函数名：TOUCH_INT()；
* 描述  ：AD7845中断嵌套
* 输入  : 
* 输出  ：
* 注意  ：
*********************************************************/    	
void TOUCH_EXT_Int(void)
	{ 
	
		NVIC_InitTypeDef NVIC_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		
		NVIC_InitStruct.NVIC_IRQChannel = EXTI4_15_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
		
		
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10);
		EXTI_InitStruct.EXTI_Line = EXTI_Line10;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStruct); 
		
		
		}
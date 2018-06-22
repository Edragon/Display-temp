
#include "stm32f0xx.h"
#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_Level_3;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_SetBits(GPIOC, GPIO_Pin_8|GPIO_Pin_9);
}






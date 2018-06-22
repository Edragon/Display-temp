#ifndef     __LED_H
#define	__LED_H

#include "stm32f0xx.h"

void LED_Init(void);

#define LED3_SET	 GPIO_ResetBits(GPIOC,GPIO_Pin_9)
#define LED4_SET	 GPIO_ResetBits(GPIOC,GPIO_Pin_8)

#define LED3_CLR   GPIO_ResetBits(GPIOC,GPIO_Pin_9)
#define LED4_CLR   GPIO_ResetBits(GPIOC,GPIO_Pin_8)

#define LED3_TOG {GPIO_WriteBit(GPIOC, GPIO_Pin_9,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9))));}

#define LED4_TOG {GPIO_WriteBit(GPIOC, GPIO_Pin_8,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_8))));}

#endif /* __LED_H */


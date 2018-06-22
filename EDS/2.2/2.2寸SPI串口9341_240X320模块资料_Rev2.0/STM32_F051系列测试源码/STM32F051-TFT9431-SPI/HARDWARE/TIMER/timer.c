#include "stm32f0xx.h"
#include "time.h"
#include "usmart.h"
uint16_t PrescalerValue = 0;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

/*����ʱ��(TIM14CLK) ����ΪAPB1 ʱ�� (PCLK1),  TIM14CLK = PCLK1 = SystemCoreClock = 48 MHz
 �� TIM14 ����ʱ�� ��Ϊ6 MHz, Ԥ��Ƶ�����԰������湫ʽ����*/

void TIM14_Init(u16 arr,u16 psc)
{
NVIC_InitTypeDef NVIC_InitStructure;
	
TIM_DeInit(TIM14);//�ȸ�λ
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

PrescalerValue = (uint16_t) (SystemCoreClock  / 6000000) - 1;
TIM_PrescalerConfig(TIM14, PrescalerValue, TIM_PSCReloadMode_Immediate);
	
TIM_TimeBaseStructure.TIM_Period = arr;
TIM_TimeBaseStructure.TIM_Prescaler = psc;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//TIM_TimeBaseStructure.TIM_RepetitionCounter
TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
TIM_ITConfig(TIM14, TIM_IT_Update|TIM_IT_Trigger, ENABLE);
TIM_Cmd(TIM14, ENABLE);
}

void TIM14_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)
  {
    usmart_scan();//ִ��usmartɨ��		
  }
	TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
}


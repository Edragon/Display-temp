#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RBT6,主频72M  单片机工作电压3.3V
//按键输入，驱动代码
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtech.net
//淘宝网站：http://qdtech.taobao.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:QDtech2008@gmail.com 
//Skype:QDtech2008
//技术交流QQ群:324828016
//创建日期:2013/5/13
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
 
void KEY_Init(void) //IO初始化
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	//init GPIOA.13,GPIOA.15  上拉输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//init GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 

	GPIO_Init(GPIOA, &GPIO_InitStructure);
		 

}
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//按键按松开标志	
 
 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)
		{
	 
			 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
			return 1;
		}
		else if(KEY1==0)
		{
	 	 
	     	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
			return 2;
		}
		else if(KEY2==1)
		{
	 
	    	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
			return 3;
		}
	}else if(KEY0==1&&KEY1==1&&KEY2==0)key_up=1; 	    
 
 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	return 0;// 无按键按下
}

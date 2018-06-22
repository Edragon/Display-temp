/*********************************************************************************/	 
//STM32液晶屏开发板示例程序
//技术支持:www.tjc1688.com
//深圳市淘晶驰电子有限公司
//更多资料：http://tftmcu.taobao.com									  
/*********************************************************************************/	
#include "sys.h"

void NVIC_Configuration(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

}
void inttohex(u16 value,u8 *hex)
{
	u16 x1;
	hex[0]=value/(16*16*16)+'0';
	x1=value%(16*16*16);
	hex[1]=x1/(16*16)+'0';
	x1=value%(16*16);
	hex[2]=x1/16+'0';
	x1=value%16;
	hex[3]=x1+'0';	
	hex[4]=' ';		 

}


#ifndef __SYSTEM_H
#define __SYSTEM_H 			   
#include "stdio.h"
//typedef unsigned char u8;
//typedef unsigned int u16;
//typedef unsigned long u32;
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1	//使能（1）/禁止（0）串口1接收
#define EN_USART2_RX 			1	//使能（1）/禁止（0）串口1接收 

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void USART1_Init(u32 bound);
void USART2_Init(u32 bound);
////////////////////////////////////////////////////////////////////////////////// 	 
void Delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif






























#ifndef __SYSTEM_H
#define __SYSTEM_H 			   
#include "stdio.h"
//typedef unsigned char u8;
//typedef unsigned int u16;
//typedef unsigned long u32;
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1	//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX 			1	//ʹ�ܣ�1��/��ֹ��0������1���� 

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void USART1_Init(u32 bound);
void USART2_Init(u32 bound);
////////////////////////////////////////////////////////////////////////////////// 	 
void Delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif






























#include "stm32f0xx.h"
#include "stdint.h"
#include "system.h"
#include "led.h"
#include "TFT_SPI.h"
#include "usmart.h"

unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

void Redraw_Mainmenu(void)
{
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,0,BLUE,GRAY0,"ȫ�����Ӽ���");
	TFT_DrawFont_GBK16(16,20,RED,GRAY0,"Һ�����Գ���");
	DisplayButtonDown(15,38,113,58); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,40,YELLOW,GRAY0,"��ɫ������");
	DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,70,BLUE,GRAY0,"������ʾ����");
	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,100,RED,GRAY0,"ͼƬ��ʾ����");

	TFT_DrawFont_GBK16(16,120,BLUE,GRAY0,"S1:Move.    ");
	TFT_DrawFont_GBK16(16,140,RED,GRAY0, "S2:Sellect  ");
	delay_ms(1000);
	delay_ms(1000);

	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[5]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[4]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[3]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[2]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[1]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[0]);	
}

void Num_Test(void)
{
	u8 i=0;
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
	delay_ms(1000);
	TFT_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
	TFT_DrawFont_Num32((i%3)*40,32*(i/3)+30,RED,GRAY0,Num[i+1]);
	delay_ms(100);
	}
	delay_ms(1000);
	
}
//������ʾ����ȫ�����Ӽ����̳���Ϊרע����רҵ
void Font_Test(void)
{
	u8 x_offset;
#ifdef H_VIEW  //��������˺�����ʾ
	x_offset=40;
#else
	x_offset=0;
#endif
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,10,BLUE,GRAY0,  "   ������ʾ����   ");
	delay_ms(1000);
	TFT_Clear(WHITE);
	TFT_DrawFont_GBK16(x_offset,10,RED,WHITE,  "     ȫ�����Ӽ������޹�˾      ");
	TFT_DrawFont_GBK16(x_offset,30,RED,WHITE,  "         QDtech .,LTD         ");
	TFT_DrawFont_GBK24(x_offset,50,BLUE,WHITE, "           ��ӭ��            ");
	TFT_DrawFont_GBK16(x_offset,100,GREEN,WHITE,   "     ȫ�̼���֧��     ");	
	TFT_DrawFont_GBK16(x_offset,120,RED,YELLOW,   "http://qdtech.taobao.com");
	TFT_DrawFont_GBK16(x_offset,140,RED,YELLOW,   "E-Mail:QDtech2008@gmail.com");
	TFT_DrawFont_GBK16(x_offset,160,RED,YELLOW,   "��������Ⱥ:324828016");	
	TFT_DrawFont_GBK16(x_offset,180,BLUE,WHITE,   "Tel:15989313508 ");
	delay_ms(3000);	
}

void Color_Test(void)
{
	u8 i=2;
	TFT_Clear(GRAY0);
	
	TFT_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
	delay_ms(1000);

	while(i--)
	{
	  TFT_Clear(WHITE);
		delay_ms(1000);
		LED3_TOG;
	  TFT_Clear(BLACK);
		delay_ms(1000);
		LED4_TOG;
	  TFT_Clear(RED);  
		delay_ms(1000);
		LED3_TOG;
  	TFT_Clear(GREEN);
		delay_ms(1000);
		LED4_TOG;
  	TFT_Clear(BLUE); 
		delay_ms(1000);
		LED3_TOG;LED4_TOG;
	}		
}

int main(void)
{
	SystemInit(); //���ڲ�8M��Ƶ��48MHz, system_stm32f0xx.c�ж�����HSI
	Delay_init();
	LED_Init();
	TFT_Init();
	USART2_Init(9600); //��ΪUSART1ʱ��ҲҪ��fputc����
	usmart_dev.init(SystemCoreClock/1000000); //SystemFrequency
	TFT_Clear(WHITE);
	TFT_LED_SET;
	
  while(1) 
  {
		Redraw_Mainmenu();//�򵥲˵�����
		Color_Test();//��ˢ������
		Num_Test();//�����������ʾ
		Font_Test();//��Ӣ�Ĳ���  
		LED3_TOG;
		TFT_Clear(WHITE);  
		delay_ms(1000);
		TFT_Clear(WHITE);  
		TFT_DrawFont_GBK16(10,50,BLUE,GRAY0,"���Գɹ�.");
		delay_ms(1000);
  }
 
}

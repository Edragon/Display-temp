#ifndef __TFT_DRIVER_H  //����ģ��SPI�ӿڷ�ʽ
#define __TFT_DRIVER_H

#define H_VIEW   1     //����Ϊ������ʾ         

#ifdef H_VIEW
				#define X_MAX_PIXEL	        320
				#define Y_MAX_PIXEL	        240
#else
				#define X_MAX_PIXEL	        240
				#define Y_MAX_PIXEL	        320 
#endif

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111

//Һ�����ƿ���1�������궨��
#define	TFT_CS_SET  	GPIO_SetBits(GPIOB, GPIO_Pin_0)  //CS -PB0
#define	TFT_RST_SET  	GPIO_SetBits(GPIOD, GPIO_Pin_2)  //RST-PD2
#define	TFT_LED_SET  	GPIO_SetBits(GPIOB, GPIO_Pin_2)  //LED-PB2
#define	TFT_RS_SET  	GPIO_SetBits(GPIOB, GPIO_Pin_1)  //RS -PB1
#define	TFT_MOSI_SET 	GPIO_SetBits(GPIOA, GPIO_Pin_7)  //MOSI-PA7
#define	TFT_MISO_SET 	GPIO_SetBits(GPIOA, GPIO_Pin_6)  //MISO-PA6
#define	TFT_SCL_SET  	GPIO_SetBits(GPIOA, GPIO_Pin_5)  //SCL-PA5

//Һ�����ƿ���0�������궨��
#define	TFT_CS_CLR  	GPIO_ResetBits(GPIOB, GPIO_Pin_0)  
#define	TFT_RST_CLR  	GPIO_ResetBits(GPIOD, GPIO_Pin_2)    
#define	TFT_LED_CLR  	GPIO_ResetBits(GPIOB, GPIO_Pin_2)  
#define	TFT_RS_CLR  	GPIO_ResetBits(GPIOB, GPIO_Pin_1)    
#define	TFT_MOSI_CLR 	GPIO_ResetBits(GPIOA, GPIO_Pin_7) 
#define	TFT_MISO_CLR 	GPIO_ResetBits(GPIOA, GPIO_Pin_6)   
#define	TFT_SCL_CLR  	GPIO_ResetBits(GPIOA, GPIO_Pin_5)    

void TFT_Init(void);
void TFT_Clear(u16 Color);
void TFT_SetXY(u16 x,u16 y);
void TFT_DrawPoint(u16 x,u16 y,u16 Data);
//u16 TFT_ReadPoint(u16 x,u16 y);
void TFT_Circle(u16 X,u16 Y,u16 R,u16 fc); 
void TFT_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);  
void TFT_box(u16 x, u16 y, u16 w, u16 h,u16 bc);
void TFT_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
void TFT_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void TFT_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void TFT_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num) ;

#endif

#ifndef __TFT_DRIVER_H
#define __TFT_DRIVER_H

#ifdef H_VIEW
	#define X_MAX_PIXEL	        320
	#define Y_MAX_PIXEL	        240
#else
	#define X_MAX_PIXEL	        240
	#define Y_MAX_PIXEL	        320 
#endif
typedef  unsigned int uint16_t;
typedef  unsigned int uint16;
typedef  unsigned int u16;
typedef  unsigned char uint8_t ;
typedef  unsigned char uint8;
typedef  unsigned char u8;
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

//液晶控制口置1操作语句宏定义
#define	TFT_CS_SET  	PORTB.OUT |=  (1 << 1)    
#define	TFT_RS_SET  	PORTB.OUT |=  (1 << 2)    
#define	TFT_SDA_SET  	PORTD.OUT |=  (1 << 5) 
#define	TFT_SCL_SET  	PORTD.OUT |=  (1 << 7)    
#define	TFT_RST_SET  	PORTB.OUT |=  (1 << 3)    
#define	TFT_LED_SET  	PORTB.OUT |=  (1 << 0)    

//液晶控制口置0操作语句宏定义
#define	TFT_CS_CLR  	PORTB.OUT &= ~(1 << 1)     
#define	TFT_RS_CLR  	PORTB.OUT &= ~(1 << 2)     
#define	TFT_SDA_CLR  	PORTD.OUT &= ~(1 << 5)     
#define	TFT_SCL_CLR  	PORTD.OUT &= ~(1 << 7)     
#define	TFT_RST_CLR  	PORTB.OUT &= ~(1 << 3)     
#define	TFT_LED_CLR  	PORTB.OUT &= ~(1 << 0)   

void TFT_Init(void);
void TFT_Clear(u16 Color);
void TFT_SetXY(u16 x,u16 y);
void TFT_DrawPoint(u16 x,u16 y,u16 Data);
//u16 TFT_ReadPoint(u16 x,u16 y);//(本程序不读点)

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

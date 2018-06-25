#ifndef __TOUCH_H
#define __TOUCH_H	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STC51,晶振30M  单片机工作电压3.3V
//QDtech-TFT液晶驱动 for C51
//中景园电子
//淘宝网站:https://shop73023976.taobao.com/?spm=2013.1.1000126.d21.o6byVe
//我司提供技术支持，任何技术问题欢迎随时交流学习
//手机:15989313508（冯工） 

//创建日期:2016-04-17
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 中景园电子2009-2019
//All rights reserved
//********************************************************************************
	
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //触摸IC读坐标积存器
#define  CMD_RDY  0x90
//IO连接
//sfr   P4    = 0xC0;


sbit DCLK	   =    P3^6;   
sbit TCS        =    P3^7;
sbit DIN       =    P3^4;	
sbit DOUT      =    P3^5;																						   
sbit Penirq    =    P4^0;   //检测触摸屏响应信号

struct tp_pix_
{
	u16 x;
	u16 y;
};
struct tp_pixu32_
{
	u32 x;
	u32 y;
};
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //当前触控坐标的AD值,前触控坐标的像素值   
extern u16 vx,vy;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
extern u16 chx,chy;//默认像素点坐标为0时的AD起始值
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //绘图函数
u16 ReadFromCharFrom7843();         //SPI 读数据
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);
u8 Convert_Pos(void);
#endif  
	 
	 




#include <15f104.h>
#include<intrins.h>
#include"ds3231.h"
#include"tm1650.h"

#define uchar unsigned char
#define uint  unsigned int

uchar i, mode,flash;
uchar left,right; //显示缓冲
uchar CODE[] = {0xFc,0x84,0xBA,0xAE,0xC6,0x6E,0x7E,0xA4,0xFe,0xEe,0x00};//0-9,灭
bit sec;//1HZ秒点闪烁

void display()
{
	if(left/16)TM1650_Set(0x68, CODE[left/16]);else TM1650_Set(0x68, CODE[10]);
	TM1650_Set(0x6A, CODE[left%16]);

    TM1650_Set(0x6c, CODE[right/16]);
	TM1650_Set(0x6E, CODE[right%16]|sec);
}

void Timer_init()		 //定时器，用于调整时间时数码管的闪烁
{
	TMOD=0X01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=0;
	ET0=1;
	INT_CLKO=0x10;//开启外部中断2，下降沿触发
	EA=1;
}

void normal()
{
	left = read_ds3231(2);
	right = read_ds3231(1);
	if((left>=0x21)||(left<7))
	TM1650_Set(0x48,0x21);//夜间降低显示亮度
	else
	TM1650_Set(0x48,0x61);//日间提高显示亮度
}
void DS3232_init()
{
	if(read_ds3231(7)!=0x22)
	{
	
	write_ds3231(0x00,0x00);  //second
	write_ds3231(0x01,0x11); //minute
	write_ds3231(0x02,0x20); //hour
	write_ds3231(0x06,0x15);//year
	write_ds3231(0x05,0x11);//month
	write_ds3231(0x04,0x13);//date
	write_ds3231(0x07,0x22);// 用闹钟寄存器判断是否掉电
	}
}
void main()
{
	uchar temp;
	Timer_init();
	TM1650_Set(0x48,0x61);//初始化为6级灰度，开显示
	DS3232_init();	 // DS3231掉电时初始化一下
	write_ds3231(0x0e,0x00);  //设置INT位为1HZ方波输出
	while(1)
	{
		    if(Scan_Key()==0x47)
			{
			    mode++;
				if(mode>3)
				{
					mode=0;
					normal();
				}
				while(Scan_Key()==0x47);
			} 
	
	switch (mode)
	{
		case 0:					 //正常显示状态，12：34
		{
			if(INT_CLKO!=0x10)
			INT_CLKO=0x10;
			break;
		}
		case 1:	        			//小时调整界面 12：
		{
			INT_CLKO=0x00;
			sec=1;
			TR0=1;
			right = read_ds3231(1);
			
			if(flash) left = read_ds3231(2);
			else      left = 0xaa;
			
			display();
				 
			if(Scan_Key()==0x77)
			{
				temp=read_ds3231(2);
				temp=((temp>>4)*10)+(temp&0x0f);
				temp++;
				if(temp>=24)temp=0;
				temp = ((temp/10)<<4)|(temp%10);
				write_ds3231(0x02,temp);
				left=read_ds3231(2);
				display();
				while(Scan_Key()==0x77);
				
			}
			break;
		}

		case 2:	//minute adjust
		{
			INT_CLKO=0x00;
			sec=1;
			TR0=1;
			left = read_ds3231(2);
			if(flash) right = read_ds3231(1);
			else	  right = 0xaa;
			display();	 
			if(Scan_Key()==0x77)
			{
				temp=read_ds3231(1);
				temp=((temp>>4)*10)+(temp&0x0f);
				temp++;
				if(temp>=60)temp=0;
				temp = ((temp/10)<<4)|(temp%10);
				write_ds3231(0x01,temp);
				right=read_ds3231(1);
				display();
				while(Scan_Key()==0x77);
			}
			break;
		}
		
		case 3:						 //秒显示与归零状态  :55
		{
			INT_CLKO=0x00;
			sec=1;
			TR0=0;
			left= 0xaa;
			right = read_ds3231(0);
			display();
			if(Scan_Key()==0x77)
			{
				write_ds3231(0x00,0x00);
				right = read_ds3231(0);
				display();
				while(Scan_Key()==0x77);
			}
			break;
		}
		
	
	} 
	} 	
	
		
}
void timer0() interrupt 1
{
	uchar flag;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	flag++;
	if(flag==5)
	{
		flag=0;
		flash=!flash;
	}
}
void int2() interrupt 10   //DS3231输出1HZ方波，每个下降沿更新时间，冒号闪烁
{
	sec=!sec;
	normal();
	display();
}	

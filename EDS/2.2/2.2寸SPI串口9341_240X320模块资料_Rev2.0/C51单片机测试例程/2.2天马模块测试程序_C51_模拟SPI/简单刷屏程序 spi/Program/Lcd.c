
//     
/***************************************************/

#include<reg51.h>
#include<absacc.h>
#include<intrins.h>
#include<string.h>
#define uchar unsigned char
#define uint unsigned int

//引脚连接定义
sbit cs        =P0^0;//片选
sbit reset     =P0^1;//复位
sbit rs        =P0^2;//地址/数据切换
sbit sda       =P1^5;// SDI  MOSI
sbit scl       =P1^7;//时钟
//SDO引脚可以不连接

uchar bdata bitdata;
sbit bit7=bitdata^7;
sbit bit6=bitdata^6;
sbit bit5=bitdata^5;
sbit bit4=bitdata^4;
sbit bit3=bitdata^3;
sbit bit2=bitdata^2;
sbit bit1=bitdata^1;
sbit bit0=bitdata^0;


void  delay(uint t);


void delay(uint time)
{
 uint i,j;
  for(i=0;i<time;i++)
   for(j=0;j<2500;j++);
}

void  write_command(uchar c)
{
	cs=0;

	rs=0;
	bitdata=c;

	sda=bit7;scl=0;scl=1;
	sda=bit6;scl=0;scl=1;
	sda=bit5;scl=0;scl=1;
	sda=bit4;scl=0;scl=1;
	sda=bit3;scl=0;scl=1;
	sda=bit2;scl=0;scl=1;
	sda=bit1;scl=0;scl=1;
	sda=bit0;scl=0;scl=1;
	cs=1;      
}

void  write_data(uchar d)
{
	cs=0;
	rs=1;
	bitdata=d;
	sda=bit7;scl=0;scl=1;
	sda=bit6;scl=0;scl=1;
	sda=bit5;scl=0;scl=1;
	sda=bit4;scl=0;scl=1;
	sda=bit3;scl=0;scl=1;
	sda=bit2;scl=0;scl=1;
	sda=bit1;scl=0;scl=1;
	sda=bit0;scl=0;scl=1;
	cs=1;
}

void wr_com16(unsigned char i,unsigned char j)    
{         
	cs=0;

	rs=1;
	bitdata=i;

	sda=bit7;scl=0;scl=1;
	sda=bit6;scl=0;scl=1;
	sda=bit5;scl=0;scl=1;
	sda=bit4;scl=0;scl=1;
	sda=bit3;scl=0;scl=1;
	sda=bit2;scl=0;scl=1;
	sda=bit1;scl=0;scl=1;
	sda=bit0;scl=0;scl=1;
	cs=1;  
	cs=0;


	rs=1;
	bitdata=j;

	sda=bit7;scl=0;scl=1;
	sda=bit6;scl=0;scl=1;
	sda=bit5;scl=0;scl=1;
	sda=bit4;scl=0;scl=1;
	sda=bit3;scl=0;scl=1;
	sda=bit2;scl=0;scl=1;
	sda=bit1;scl=0;scl=1;
	sda=bit0;scl=0;scl=1;
	cs=1; 
 
}
//////////////////////////////////////////////////////////////////////////////////////////////

void lcd_initial()
{

		reset=0;
		delay(100);
		reset=1;
		delay(100);
	
		//2.2inch TM2.2-G2.2 Init 20171020 
	write_command(0x11);  
	write_data(0x00); 

	write_command(0xCF);  
	write_data(0X00); 
	write_data(0XC1); 
	write_data(0X30);

	write_command(0xED);  
	write_data(0X64); 
	write_data(0X03); 
	write_data(0X12);
	write_data(0X81);

	write_command(0xE8);  
	write_data(0X85); 
	write_data(0X11); 
	write_data(0X78);

	write_command(0xF6);  
	write_data(0X01); 
	write_data(0X30); 
	write_data(0X00);

	write_command(0xCB);  
	write_data(0X39); 
	write_data(0X2C); 
	write_data(0X00);
	write_data(0X34);
	write_data(0X05);

	write_command(0xF7);  
	write_data(0X20); 

	write_command(0xEA);  
	write_data(0X00); 
	write_data(0X00); 

	write_command(0xC0);  
	write_data(0X20); 

	write_command(0xC1);  
	write_data(0X11); 

	write_command(0xC5);  
	write_data(0X31); 
	write_data(0X3C); 

	write_command(0xC7);  
	write_data(0XA9); 

	write_command(0x3A);  
	write_data(0X55); 
	
  write_command(0x36);  
	write_data(0x48);//竖屏参数 

	write_command(0xB1);  
	write_data(0X00); 
	write_data(0X18); 

	write_command(0xB4);  
	write_data(0X00); 
	write_data(0X00); 

	write_command(0xF2);  
	write_data(0X00); 

	write_command(0x26);  
	write_data(0X01); 

	write_command(0xE0);  
	write_data(0X0F); 
	write_data(0X17); 
	write_data(0X14); 
	write_data(0X09); 
	write_data(0X0C); 
	write_data(0X06); 
	write_data(0X43); 
	write_data(0X75); 
	write_data(0X36); 
	write_data(0X08); 
	write_data(0X13); 
	write_data(0X05); 
	write_data(0X10); 
	write_data(0X0B); 
	write_data(0X08); 


	write_command(0xE1);  
	write_data(0X00); 
	write_data(0X1F); 
	write_data(0X23); 
	write_data(0X03); 
	write_data(0X0E); 
	write_data(0X04); 
	write_data(0X39); 
	write_data(0X25); 
	write_data(0X4D); 
	write_data(0X06); 
	write_data(0X0D); 
	write_data(0X0B); 
	write_data(0X33); 
	write_data(0X37); 
	write_data(0X0F); 

	write_command(0x29);  	

}
 void addset(unsigned int x,unsigned int y)
{
		write_command(0x2a);
		wr_com16(x>>8,x);
		write_command(0x2b);
		wr_com16(y>>8,y);
		write_command(0x2c);
}

void dsp_single_colour(DH,DL)
{
	unsigned int i,j;
	addset(0,0);
	for (i=0;i<320;i++)
    for (j=0;j<240;j++)
        wr_com16(DH,DL);    

}

main()
{
		lcd_initial();
      while(1)
		{

			Disp_gradscal(); //灰阶
			dsp_single_colour(0x84,0x10);//灰色
			dsp_single_colour(0xff,0xff);//白色
			dsp_single_colour(0x00,0x00);//黑色
			dsp_single_colour(0xf8,0x00);//红色
			dsp_single_colour(0x07,0xe0);//绿色
			dsp_single_colour(0x00,0x1f);//蓝色

    }

 }




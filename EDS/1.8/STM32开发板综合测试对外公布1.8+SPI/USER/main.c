/*********************************************************************************/	 
//STM32液晶屏开发板示例程序
//技术支持:www.tjc1688.com
//深圳市淘晶驰电子有限公司
//更多资料：http://tftmcu.taobao.com

//硬件SPI1接口: 硬件采用STM32f103VCT6
//TFT_CS连STM32	 PA4
//RESET连STM32	 PB0
//TFT_A0连STM32	 PC4
//TFT_SDA连STM32 SPI1_MOSI
//TFT_SCK连STM32 SPI1_SCK									  
/*********************************************************************************/	
#include "led.h"
#include "delay.h"
#include "key.h"
//#include "sys.h"
#include "lcd.h"	
#include "font.h" 

#define LCD_W 128
#define LCD_H 160


_lcd_dev lcddev;

u8 xx=0;
u8 state=0;
u8 idfind(u8 *buf,u8 *val,u8 len);


void beepms(u16 va);

//m^n函数
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	



//void refshow(void);//刷新显示	 
//u8 stringfind(u8 *buf,u8 *val);
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
{
	while((SPIx->SR&SPI_I2S_FLAG_TXE)==RESET);		//等待发送区空	  
	SPIx->DR=Byte;	 	//发送一个byte   
	while((SPIx->SR&SPI_I2S_FLAG_RXNE)==RESET);//等待接收完一个byte  
	return SPIx->DR;          	     //返回收到的数据			
} 

void LCD_Writ_Bus(u8 da)   //串行数据写入
{

 SPI_WriteByte(SPI1,da);

} 
void LCD_WR_DATA8(u8 da) //发送数据-8位参数
{
    LCD_RS_SET;		     //RS=1
	LCD_Writ_Bus(da);
}  
 void LCD_WR_DATA(u16 da)
{
    LCD_RS_SET;
	LCD_Writ_Bus(da>>8);
	LCD_Writ_Bus(da);
}	  
void LCD_WR_REG(u8 da)	 
{
    LCD_RS_RESET;
	LCD_Writ_Bus(da);
}
 void LCD_WR_REG_DATA(u16 reg,int da)
{
    LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
void Address_set(u16 x1,u16 y1,u16 x2,u16 y2)
{  
   LCD_WR_REG(0x2a);
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);

}

		 
//清屏函数
//Color:要清屏的填充色
void LCD_Clear(u16 Color)
{
	u8 VH,VL;
	u16 i,j;
	VH=Color>>8;
	VL=Color;	
	Address_set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
	 {
	  for (j=0;j<LCD_H;j++)
	   	{
        	 LCD_WR_DATA8(VH);
			 LCD_WR_DATA8(VL);	
	    }
	  }
}
//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;

	      			     
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	Address_set(x,y,x+8-1,y+16-1);      //设置光标位置
	if(!mode) //非叠加方式
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //调用1206字体
			else temp=asc2_1608[num][t];		 //调用1608字体 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				//LCD_DrawPoint(x,y);
				LCD_WR_DATA(POINT_COLOR);	
				temp>>=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//超区域了
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//超区域了
					break;
				} 
			}  	 
	    }    
	}else//叠加方式
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //调用1206字体		 LCD_ShowChar(x,y,*p,size,1);
			else temp=asc2_1608[num][t];		 //调用1608字体 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_WR_DATA(POINT_COLOR);//LCD_DrawPoint(x,y); 
				temp>>=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//超区域了
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//超区域了
					break; 
				}	 
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);	 
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }  
}

void showhanzi(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j;
	unsigned char *temp=hanzi;    
    Address_set(x,y,x+31,y+31); //设置区域      
	temp+=index*128;	
	for(j=0;j<128;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
		 	if((*temp&(1<<i))!=0)
			{
				LCD_WR_DATA(POINT_COLOR);
			} 
			else
			{
				LCD_WR_DATA(BACK_COLOR);
			}   
		}
		temp++;
	 }
}

void xianshi()
{
	
	LCD_Clear(RED);	
	delay_ms(1000);
	LCD_Clear(GREEN);
	delay_ms(1000);
	LCD_Clear(BLUE);
	delay_ms(1000);
	LCD_Clear(WHITE);
	BACK_COLOR=YELLOW;
	POINT_COLOR=RED;
	showhanzi(5,5,0);   //电
	showhanzi(37,5,1); 	//子
//	showhanzi(69,4,2);	//发
//	showhanzi(101,4,3);	//烧
//	showhanzi(133,4,4);	//老
//	showhanzi(165,4,5);	//友
	BACK_COLOR=YELLOW;
	POINT_COLOR=RED;
	LCD_ShowString(5,50,200,16,16,"tftmcu.taobao.com");	


}

void showimage() //显示40*40图片
{
  	int i,j,k;
	xianshi(); //显示信息
	for(k=2;k<4;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Address_set(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<1600;i++)
			 {				
			  	 LCD_WR_DATA8(image[i*2+1]);	 //发送颜色数据
				 LCD_WR_DATA8(image[i*2]);					
			 }	
		 }
	}
		
}	

void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
	beep=0;
}					
int main(void)
 {	 
	lcddev.height=160;
	lcddev.width=128;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
    SPI1_Init();
	LCD_Init();
	showimage();
	while(1);
}



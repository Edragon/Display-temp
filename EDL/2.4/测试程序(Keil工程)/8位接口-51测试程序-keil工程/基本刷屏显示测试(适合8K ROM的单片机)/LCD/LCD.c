#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h>
#include <font\font.h>
/* http://ttmcu.taobao.com 
代码测试环境:单片机STC12LE5A60S2,晶振33M  单片机工作电压3.3V
程序默认IO连接方式：
控制线：RS-P3^5;    WR-P3^6;   RD-P3^7;   CS-P1^0;   REST-P1^2;
数据线: DB0-DB7悬空  DB8-DB15依次连接P2^0-P2^7;
触摸功能连接方式：(不使用触摸可不连接)
T_CLK-P1^7;  T_CS-P1^4;  T_DIN-P3^0;  T_OUT-P3^1;  T_IRQ-P3^4;
*/
u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色
void LCD_Writ_COLORBus(char VH,char VL)   //颜色数据写入总线
{
  LCD_DataPortH=VH;	
	LCD_WR=0;
	LCD_WR=1; 
	LCD_DataPortH=VL;	
	LCD_WR=0;
	LCD_WR=1; 
}
void LCD_Writ_COMBus(char da)   //寄存器数据写入总线
{
  LCD_DataPortH=da;	
	LCD_WR=0;
	LCD_WR=1; 
}
void LCD_WR_DATA8(char VH,char VL) //发送颜色数据-8位参数
{
  LCD_RS=1;
	LCD_Writ_COLORBus(VH,VL);
}  
void LCD_WR_DATA(int da) //发送颜色数据-16位参数
{
  LCD_RS=1;
	LCD_Writ_COLORBus(da>>8,da);
}	  
void LCD_WR_COMDATA(char da)//发送寄存器数据
{
  LCD_RS=1;
	LCD_Writ_COMBus(da);
} 
void LCD_WR_REG(char da)	 //写寄存器
{	
  LCD_RS=0;
	LCD_Writ_COMBus(da); //寄存器数据写入总线
}
 void LCD_WR_REG_DATA(char reg,char da)
{
  LCD_WR_REG(reg);
	LCD_WR_COMDATA(da);
}
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	 LCD_WR_REG(0x2A);
   LCD_WR_COMDATA(x1>>8);
   LCD_WR_COMDATA(x1);
   LCD_WR_COMDATA(x2>>8);
   LCD_WR_COMDATA(x2);
  
   LCD_WR_REG(0x2B);
   LCD_WR_COMDATA(y1>>8);
   LCD_WR_COMDATA(y1);
   LCD_WR_COMDATA(y2>>8);
   LCD_WR_COMDATA(y2);	
   LCD_WR_REG(0x2c);								 
}
void Lcd_Init(void)
{

//调用一次这些函数，免得编译的时候提示警告
   	LCD_CS =1;
	if(LCD_CS==0)
	{
	   LCD_WR_REG_DATA(0,0);
	   LCD_ShowString(0,0," ");
	   LCD_ShowNum(0,0,0,0);
	   LCD_Show2Num(0,0,0,0);
	   LCD_DrawPoint_big(0,0);
	   LCD_DrawRectangle(0,0,0,0);
	   Draw_Circle(0,0,0);
 	 }
	LCD_RD=1;
	LCD_WR=1;
	LCD_REST=0;
	delayms(20);	//此处保证要有5ms以上才能保证复位稳定,推荐20ms
	LCD_REST=1;	
	delayms(20);	//此处保证要有5ms以上才能保证复位稳定,推荐20ms		
	LCD_CS =0;  //打开片选使能

  //************* Start Initial Sequence **********//
LCD_WR_REG(0xcf); 
LCD_WR_COMDATA(0x00);
LCD_WR_COMDATA(0xc1);
LCD_WR_COMDATA(0x30);

LCD_WR_REG(0xed); 
LCD_WR_COMDATA(0x64);
LCD_WR_COMDATA(0x03);
LCD_WR_COMDATA(0x12);
LCD_WR_COMDATA(0x81);

LCD_WR_REG(0xcb); 
LCD_WR_COMDATA(0x39);
LCD_WR_COMDATA(0x2c);
LCD_WR_COMDATA(0x00);
LCD_WR_COMDATA(0x34);
LCD_WR_COMDATA(0x02);

LCD_WR_REG(0xea); 
LCD_WR_COMDATA(0x00);
LCD_WR_COMDATA(0x00);

LCD_WR_REG(0xe8); 
LCD_WR_COMDATA(0x85);
LCD_WR_COMDATA(0x10);
LCD_WR_COMDATA(0x79);

LCD_WR_REG(0xC0); //Power control
LCD_WR_COMDATA(0x23); //VRH[5:0]

LCD_WR_REG(0xC1); //Power control
LCD_WR_COMDATA(0x11); //SAP[2:0];BT[3:0]

LCD_WR_REG(0xC2);
LCD_WR_COMDATA(0x11);

LCD_WR_REG(0xC5); //VCM control
LCD_WR_COMDATA(0x3d);
LCD_WR_COMDATA(0x30);

LCD_WR_REG(0xc7); 
LCD_WR_COMDATA(0xaa);

LCD_WR_REG(0x3A); 
LCD_WR_COMDATA(0x55);

LCD_WR_REG(0x36); // Memory Access Control
LCD_WR_COMDATA(0x08);

LCD_WR_REG(0xB1); // Frame Rate Control
LCD_WR_COMDATA(0x00);
LCD_WR_COMDATA(0x11);

LCD_WR_REG(0xB6); // Display Function Control
LCD_WR_COMDATA(0x0a);
LCD_WR_COMDATA(0xa2);

LCD_WR_REG(0xF2); // 3Gamma Function Disable
LCD_WR_COMDATA(0x00);

LCD_WR_REG(0xF7);
LCD_WR_COMDATA(0x20);

LCD_WR_REG(0xF1);
LCD_WR_COMDATA(0x01);
LCD_WR_COMDATA(0x30);

LCD_WR_REG(0x26); //Gamma curve selected
LCD_WR_COMDATA(0x01);

LCD_WR_REG(0xE0); //Set Gamma
LCD_WR_COMDATA(0x0f);
LCD_WR_COMDATA(0x3f);
LCD_WR_COMDATA(0x2f);
LCD_WR_COMDATA(0x0c);
LCD_WR_COMDATA(0x10);
LCD_WR_COMDATA(0x0a);
LCD_WR_COMDATA(0x53);
LCD_WR_COMDATA(0xd5);
LCD_WR_COMDATA(0x40);
LCD_WR_COMDATA(0x0a);
LCD_WR_COMDATA(0x13);
LCD_WR_COMDATA(0x03);
LCD_WR_COMDATA(0x08);
LCD_WR_COMDATA(0x03);
LCD_WR_COMDATA(0x00);

LCD_WR_REG(0xE1); //Set Gamma
LCD_WR_COMDATA(0x00);
LCD_WR_COMDATA(0x00);
LCD_WR_COMDATA(0x10);
LCD_WR_COMDATA(0x03);
LCD_WR_COMDATA(0x0f);
LCD_WR_COMDATA(0x05);
LCD_WR_COMDATA(0x2c);
LCD_WR_COMDATA(0xa2);
LCD_WR_COMDATA(0x3f);
LCD_WR_COMDATA(0x05);
LCD_WR_COMDATA(0x0e);
LCD_WR_COMDATA(0x0c);
LCD_WR_COMDATA(0x37);
LCD_WR_COMDATA(0x3c);
LCD_WR_COMDATA(0x0F);
LCD_WR_REG(0x11); //Exit Sleep
delayms(80);//此处必须要延时80ms或者更多
LCD_WR_REG(0x29); //display on
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
        	 LCD_WR_DATA8(VH,VL);
	    }

	  }
}
//画点
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(u16 x,u16 y)
{
	Address_set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(POINT_COLOR); 	    
} 	 
//画一个大点
//POINT_COLOR:此点的颜色
void LCD_DrawPoint_big(u16 x,u16 y)
{
	LCD_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
} 
//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//设置光标位置 	    
	} 					  	    
}  
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//画矩形
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3           
		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0-a,y0+b);             //1       
		LCD_DrawPoint(x0-b,y0-a);             //7           
		LCD_DrawPoint(x0-a,y0-b);             //2             
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-b,y0+a);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b);
	}
} 
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"
//mode:叠加方式(1)还是非叠加方式(0)
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"

//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode)
{
    u8 temp;
    u8 pos,t;
	u16 x0=x;
	u16 colortemp=POINT_COLOR;      
    if(x>LCD_W-16||y>LCD_H-16)return;	    
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	Address_set(x,y,x+8-1,y+16-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_WR_DATA(POINT_COLOR);	
				temp>>=1; 
				x++;
		    }
			x=x0;
			y++;
		}	
	}else//叠加方式
	{
		for(pos=0;pos<16;pos++)
		{
		    temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点     
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n函数
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//color:颜色
//num:数值(0~4294967295);	
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len)
{         	
	u8 t,temp;
	u8 enshow=0;
	num=(u16)num;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+8*t,y,' ',0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0); 
	}
} 
//显示2个数字
//x,y:起点坐标
//num:数值(0~99);	 
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len)
{         	
	u8 t,temp;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 	LCD_ShowChar(x+8*t,y,temp+'0',0); 
	}
} 
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void LCD_ShowString(u16 x,u16 y,const u8 *p)
{         
    while(*p!='\0')
    {       
        if(x>LCD_W-16){x=0;y+=16;}
        if(y>LCD_H-16){y=x=0;LCD_Clear(RED);}
        LCD_ShowChar(x,y,*p,0);
        x+=8;
        p++;
    }  
}













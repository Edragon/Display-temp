#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h>
#include <font\font.h>
#include <touch\touch.h>
/* 
代码测试环境:单片机STC12LE5A60S2,晶振33M  单片机工作电压3.3V
程序默认IO连接方式：
sbit LCD_CS     =P0^0;     //片选	
sbit LCD_DC     =P0^2;	  //数据/命令切换
sbit LCD_SDI    =P1^5;	  //数据
sbit LCD_SCK    =P1^7;	  //时钟
sbit LCD_REST   =P0^1;	  //复位  
触摸功能连接方式：(不使用触摸可不连接)
T_CLK-P1^7;  T_CS-P1^4;  T_DIN-P3^0;  T_OUT-P3^1;  T_IRQ-P3^4;
*/		
sbit key1=P3^2;
sbit key2=P3^3;
sbit key3=P3^4;
u8 ref=0;//刷新显示

u8 jiance() //检测触摸和按键
{
	if (tpstate()==0) //如果触摸按下，则进入绘图程序
	 {
	 	LCD_Clear(WHITE); //清屏
		BACK_COLOR=WHITE;
		POINT_COLOR=RED;
	 	point();
		return 1;
	 }	
	if(key1==0)	//如果按键1按下,进入校准程序 
	   {
		Touch_Adjust();//校准
		return 1;
	   }
	 if(key2==0)	//三色刷屏
	   {
		 LCD_Clear(RED);
		 delayms(3000);
		 LCD_Clear(GREEN);
		 delayms(3000);
		 LCD_Clear(BLUE);
		 delayms(3000);
		 return 1;
	   }
	   return 0;
}
void xianshi()//显示信息
{   
	u16 lx,ly;
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	//显示32*32汉字
	showhanzi32(0,0,0);	 //淘
	showhanzi32(40,0,1); //晶
	showhanzi32(80,0,2); //驰
	//显示16*16汉字
	showhanzi16(0,35,0);	  //专
	showhanzi16(20,35,1);	  //注
	showhanzi16(40,35,2);	  //显
	showhanzi16(60,35,3);	  //示
	showhanzi16(80,35,4);	  //方
	showhanzi16(100,35,5);	  //案
    LCD_ShowString(0,55,"2.8 TFT SPI 240*320");
	lx=0;ly=75;			
	LCD_ShowString(lx,ly,"VX:");lx+=40;LCD_ShowNum(lx,ly,vx,5);					
	lx+=60;
	LCD_ShowString(lx,ly,"Vy:");lx+=40;LCD_ShowNum(lx,ly,vy,5);					
	lx=0;ly=95; 
	LCD_ShowString(lx,ly,"CHX:");lx+=40;LCD_ShowNum(lx,ly,chx,5);					
	lx+=60; 
	LCD_ShowString(lx,ly,"CHY:");lx+=40;LCD_ShowNum(lx,ly,chy,5);
}
void showimage() //显示40*40图片
{
  	int i,j,k; 
	LCD_Clear(WHITE); //清屏  
	xianshi(); //显示信息
	for(k=3;k<8;k++)
	{
	   	for(j=0;j<6;j++)
		{	
			Address_set(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<1600;i++)
			 { 	
				 if(jiance()) //检测触摸和按键
				 {	
				 	ref=1;
				  	return;	
				 }		
			  	 LCD_WR_DATA8(image[i*2+1]);	 
				 LCD_WR_DATA8(image[i*2]);				
			 }	
		 }
	}
	ref=0;				
}
main()
{ 
	spistar()  ;//模拟SPI初始化
	Lcd_Init();   //tft初始化
	LCD_Clear(WHITE); //清屏
	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 
    showimage(); //显示40*40图片

	while(1)
	{
	    if(jiance()) //检测触摸和按键
	  {	
	  	showimage(); //显示40*40图片
	  }
	  if(ref){showimage();} //显示40*40图片

    }


}


#include "window.h"

uint8 SelectMenuNow; // 记录选中了哪个选项

void MenuShow(void)
{
	LCD_Clear(WHITE);	   // 清屏
	POINT_COLOR = BLACK;
	BACK_COLOR = WHITE;
	LCD_ShowString(15, 90, (uint8*)Menu[0]); //	加载文字
	LCD_ShowString(90, 90, (uint8*)Menu[1]);
	LCD_ShowString(165, 90, (uint8*)Menu[2]);
	LCD_ShowString(15, 190, (uint8*)Menu[3]);
	LCD_ShowString(90, 190, (uint8*)Menu[4]);
	LCD_ShowString(165, 190,(uint8*)Menu[5]);
	LCD_ShowString(15, 290, (uint8*)Menu[6]);
	LCD_ShowString(90, 290, (uint8*)Menu[7]);
	LCD_ShowString(165, 290, (uint8*)Menu[8]);

	TFTBmpDisplay("hand/EBOOK.bmp", 15,15);	// 加载图标		
	TFTBmpDisplay("hand/EPEN.bmp", 90,15);		
	TFTBmpDisplay("hand/EPHOTO.bmp", 165,15);	
	TFTBmpDisplay("hand/LED.bmp", 15,115);	
	TFTBmpDisplay("hand/ADC.bmp", 90,115);	
	TFTBmpDisplay("hand/RF.bmp", 165,115);	
	TFTBmpDisplay("hand/I2C.bmp", 15,215);	
	TFTBmpDisplay("hand/UART.bmp", 90,215);	
	TFTBmpDisplay("hand/KEY.bmp", 165,215);	

	SelectMenuNow = 0; // 标记没有按键
}




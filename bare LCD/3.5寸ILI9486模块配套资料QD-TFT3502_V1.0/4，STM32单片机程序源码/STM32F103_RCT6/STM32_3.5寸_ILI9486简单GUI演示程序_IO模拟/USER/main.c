#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include"GUItest.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//²âÊÔÓ²¼þ£ºµ¥Æ¬»úSTM32F103RBT6,ÕýµãÔ­×ÓMiniSTM32¿ª·¢°å,Ö÷Æµ72MHZ
//QDtech-TFTÒº¾§Çý¶¯ for STM32 IOÄ£Äâ
//xiao·ë@ShenZhen QDtech co.,LTD
//¹«Ë¾ÍøÕ¾:www.qdtech.net
//ÌÔ±¦ÍøÕ¾£ºhttp://qdtech.taobao.com
//ÎÒË¾Ìá¹©¼¼ÊõÖ§³Ö£¬ÈÎºÎ¼¼ÊõÎÊÌâ»¶Ó­ËæÊ±½»Á÷Ñ§Ï°
//¹Ì»°(´«Õæ) :+86 0755-23594567 
//ÊÖ»ú:15989313508£¨·ë¹¤£© 
//ÓÊÏä:QDtech2008@gmail.com 
//Skype:QDtech2008
//¼¼Êõ½»Á÷QQÈº:324828016
//´´½¨ÈÕÆÚ:2013/5/13
//°æ±¾£ºV1.1
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ÉîÛÚÊÐÈ«¶¯µç×Ó¼¼ÊõÓÐÏÞ¹«Ë¾ 2009-2019
//All rights reserved
/****************************************************************************************************
//=======================================Òº¾§ÆÁÊý¾ÝÏß½ÓÏß==========================================//
STM32 PB×é½ÓÒº¾§ÆÁDB0~DB15,¾ÙÀýÒÀ´ÎÎªDB0½ÓPB0,..DB15½ÓPB15.   
//=======================================Òº¾§ÆÁ¿ØÖÆÏß½ÓÏß==========================================//
//LCD_CS	½ÓPC9	//Æ¬Ñ¡ÐÅºÅ
//LCD_RS	½ÓPC8	//¼Ä´æÆ÷/Êý¾ÝÑ¡ÔñÐÅºÅ
//LCD_WR	½ÓPC7	//Ð´ÐÅºÅ
//LCD_RD	½ÓPC6	//¶ÁÐÅºÅ
//LCD_RST	½ÓPC5	//¸´Î»ÐÅºÅ
//LCD_LED	½ÓPC10	//±³¹â¿ØÖÆÐÅºÅ(¸ßµçÆ½µãÁÁ)
//=========================================´¥ÃþÆÁ´¥½ÓÏß=========================================//
//²»Ê¹ÓÃ´¥Ãþ»òÕßÄ£¿é±¾Éí²»´ø´¥Ãþ£¬Ôò¿É²»Á¬½Ó
//MO(MISO)	½ÓPC2	//SPI×ÜÏßÊä³ö
//MI(MOSI)	½ÓPC3	//SPI×ÜÏßÊäÈë
//PEN		½ÓPC1	//´¥ÃþÆÁÖÐ¶ÏÐÅºÅ
//TCS		½ÓPC13	//´¥ÃþICÆ¬Ñ¡
//CLK		½ÓPC0	//SPI×ÜÏßÊ±ÖÓ
**************************************************************************************************/	

int main(void)
{		
	SystemInit();//³õÊ¼»¯RCC ÉèÖÃÏµÍ³Ö÷ÆµÎª72MHZ
	delay_init(72);	     //ÑÓÊ±³õÊ¼»¯
	LCD_Init();	   //Òº¾§ÆÁ³õÊ¼»¯

	while(1)
	{			
		main_test(); 		//²âÊÔÖ÷½çÃæ
		Test_Color();  		//¼òµ¥Ë¢ÆÁÌî³ä²âÊÔ
		Test_FillRec();		//GUI¾ØÐÎ»æÍ¼²âÊÔ
		Test_Circle(); 		//GUI»­Ô²²âÊÔ
		English_Font_test();//Ó¢ÎÄ×ÖÌåÊ¾Àý²âÊÔ
		Chinese_Font_test();//ÖÐÎÄ×ÖÌåÊ¾Àý²âÊÔ
		Pic_test();			//Í¼Æ¬ÏÔÊ¾Ê¾Àý²âÊÔ	
		POINT_Demo();		// Loading ÑÝÊ¾ 
		ComboDemo();		// ÏÂÀ­ÁÐ±íÑÝÊ¾
		ProgresBar_Demo();	// ½ø¶ÈÌõÑÝÊ¾		
		BarReport_Demo();	// ÌõÐÎ±¨±íÑÝÊ¾
		Window_Demo();		// ´°¿ÚÑÝÊ¾	 
		Button_Demo();		// °´Å¥ÑÝ¾
		//Touch_Test();		//´¥ÃþÆÁÊÖÐ´²âÊÔ
	}				  
	
 }


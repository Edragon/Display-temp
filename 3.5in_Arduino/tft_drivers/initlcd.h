void LCD_GPIO_Init(void)
{
	......
//Init the GPIOs for LCD	
}
void LCD_RESET(void)
{
	LCD_RST_CLR;
	delay_ms(100);	
	LCD_RST_SET;
	delay_ms(50);
}
void LCD_Init(void)
{
	//LCD_GPIO_Init();//Init the GPIOs for LCD
	//LCD_RESET();//You should ResetLCD before Init.
	
	//ILI9486³õÊ¼»¯
	LCD_Write_COM(0XF9);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x08);
	
	LCD_Write_COM(0xC0);
	LCD_Write_DATA(0x19);//VREG1OUT POSITIVE
	LCD_Write_DATA(0x1a);//VREG2OUT NEGATIVE
	
	LCD_Write_COM(0xC1);
	LCD_Write_DATA(0x45);//VGH,VGL    VGH>=14V.
	LCD_Write_DATA(0x00);
	
	LCD_Write_COM(0xC2);
	LCD_Write_DATA(0x33);
	
	LCD_Write_COM(0XC5);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x28);//VCM_REG[7:0]. <=0X80.
		
	LCD_Write_COM(0xB1);//OSC Freq set.
	LCD_Write_DATA(0x90);//0xA0=62HZ,0XB0 =70HZ, <=0XB0.
	LCD_Write_DATA(0x11);
	
	LCD_Write_COM(0xB4);
	LCD_Write_DATA(0x02); //2 DOT FRAME MODE,F<=70HZ.
	
	LCD_Write_COM(0xB6);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x22);//0 GS SS SM ISC[3:0];
	LCD_Write_DATA(0x3B);
		
	LCD_Write_COM(0xB7);
	LCD_Write_DATA(0x07);
	
	LCD_Write_COM(0xE0);
	LCD_Write_DATA(0x1F);
	LCD_Write_DATA(0x25);
	LCD_Write_DATA(0x22);
	LCD_Write_DATA(0x0B);
	LCD_Write_DATA(0x06);
	LCD_Write_DATA(0x0A);
	LCD_Write_DATA(0x4E);
	LCD_Write_DATA(0xC6);
	LCD_Write_DATA(0x39);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	
	LCD_Write_COM(0XE1);
	LCD_Write_DATA(0x1F);
	LCD_Write_DATA(0x3F);
	LCD_Write_DATA(0x3F);
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x1F);
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x46);
	LCD_Write_DATA(0x49);
	LCD_Write_DATA(0x31);
	LCD_Write_DATA(0x05);
	LCD_Write_DATA(0x09);
	LCD_Write_DATA(0x03);
	LCD_Write_DATA(0x1C);
	LCD_Write_DATA(0x1A);
	LCD_Write_DATA(0x00);
	
	LCD_Write_COM(0XF1);
	LCD_Write_DATA(0x36);
	LCD_Write_DATA(0x04);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x3C);
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0xA4);
	LCD_Write_DATA(0x02);
	
	LCD_Write_COM(0XF2);
	LCD_Write_DATA(0x18);
	LCD_Write_DATA(0xA3);
	LCD_Write_DATA(0x12);
	LCD_Write_DATA(0x02);
	LCD_Write_DATA(0x32);
	LCD_Write_DATA(0x12);
	LCD_Write_DATA(0xFF);
	LCD_Write_DATA(0x32);
	LCD_Write_DATA(0x00);
	
	LCD_Write_COM(0XF4);
	LCD_Write_DATA(0x40);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x08);
	LCD_Write_DATA(0x91);
	LCD_Write_DATA(0x04);
	
	LCD_Write_COM(0XF8);
	LCD_Write_DATA(0x21);
	LCD_Write_DATA(0x04);
	
	LCD_Write_COM(0x36);
	LCD_Write_DATA(0x0A);
	
	LCD_Write_COM(0x3A);
	LCD_Write_DATA(0x55);
	
	LCD_Write_COM(0x11);
	delay(120);
	//LCD_Write_COM(0x21);
	LCD_Write_COM(0x29);
}


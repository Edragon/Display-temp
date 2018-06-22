#include "stm32f0xx.h"
#include "system.h"
#include "font.h"
#include "TFT_SPI.h"

//spi дһ���ֽ�
u8 SPI_WriteByte(uint8_t Data)
{
  /*!< �жϷ��ͻ����Ƿ�Ϊ��*/
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}  
  SPI_SendData8(SPI1, Data);/*!< �����ֽ� */
  /*!< �жϽ��ջ����Ƿ�Ϊ��*/
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){}
  /*!< ���ض�ȡ���ֽ� */ 
  return SPI_ReceiveData8(SPI1);
} 

//Ӳ��SPI����
void SPI1_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  SPI_InitTypeDef   SPI_InitStruct;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOD, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); //RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); //

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2; //PD2--RST
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;  //0x01Ϊ���
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;//�ٶ����
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//0x00Ϊ�������
  //GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;//������
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  GPIO_SetBits(GPIOD,GPIO_Pin_2); //��1
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2; //CS,RS,LED-BL
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;  //0x01Ϊ���
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;//�ٶ����
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//0x00Ϊ�������
  //GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;//������
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2); //��1

  /*!< Configure SD_SPI pins: SCK-PA5,MISO-PA6,MOSI-PA7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP; 
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* Connect PXx to SD_SPI_SCK */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
  /* Connect PXx to SD_SPI_MISO */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0); 
  /* Connect PXx to SD_SPI_MOSI */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);

  /*!< SD_SPI Config */
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//2,4,8,16,32...
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStruct);
  SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
  SPI_Cmd(SPI1, ENABLE); /*!< SD_SPI enable */
	TFT_CS_CLR;
}

void TFT_WriteIndex(u8 Index)
{
   TFT_RS_CLR;
   SPI_WriteByte(Index);
}

void TFT_WriteData(u8 Data)
{
   TFT_RS_SET;
   SPI_WriteByte(Data);
}

void TFT_WriteData16Bit(u8 DataH,u8 DataL)
{
	TFT_WriteData(DataH);
	TFT_WriteData(DataL);
}

void TFT_WriteIndex16Bit(u8 DataH,u8 DataL)
{
	TFT_WriteIndex(DataH);
	TFT_WriteIndex(DataL);
}

void TFT_Init(void)
{
	SPI1_Init();
	TFT_RST_CLR;
	delay_ms(100);
	TFT_RST_SET;
	delay_ms(50);
	//2.2inch TM2.2-G2.2 Init 20171020 
	TFT_WriteIndex(0x11);  
	TFT_WriteData(0x00); 

	TFT_WriteIndex(0xCF);  
	TFT_WriteData(0X00); 
	TFT_WriteData(0XC1); 
	TFT_WriteData(0X30);

	TFT_WriteIndex(0xED);  
	TFT_WriteData(0X64); 
	TFT_WriteData(0X03); 
	TFT_WriteData(0X12);
	TFT_WriteData(0X81);

	TFT_WriteIndex(0xE8);  
	TFT_WriteData(0X85); 
	TFT_WriteData(0X11); 
	TFT_WriteData(0X78);

	TFT_WriteIndex(0xF6);  
	TFT_WriteData(0X01); 
	TFT_WriteData(0X30); 
	TFT_WriteData(0X00);

	TFT_WriteIndex(0xCB);  
	TFT_WriteData(0X39); 
	TFT_WriteData(0X2C); 
	TFT_WriteData(0X00);
	TFT_WriteData(0X34);
	TFT_WriteData(0X05);

	TFT_WriteIndex(0xF7);  
	TFT_WriteData(0X20); 

	TFT_WriteIndex(0xEA);  
	TFT_WriteData(0X00); 
	TFT_WriteData(0X00); 

	TFT_WriteIndex(0xC0);  
	TFT_WriteData(0X20); 

	TFT_WriteIndex(0xC1);  
	TFT_WriteData(0X11); 

	TFT_WriteIndex(0xC5);  
	TFT_WriteData(0X31); 
	TFT_WriteData(0X3C); 

	TFT_WriteIndex(0xC7);  
	TFT_WriteData(0XA9); 

	TFT_WriteIndex(0x3A);  
	TFT_WriteData(0X55); 
	
  TFT_WriteIndex(0x36);  
	#if H_VIEW
		 TFT_WriteData(0xE8);//��������
	#else
		 TFT_WriteData(0x48);//�������� 
	#endif

	TFT_WriteIndex(0xB1);  
	TFT_WriteData(0X00); 
	TFT_WriteData(0X18); 

	TFT_WriteIndex(0xB4);  
	TFT_WriteData(0X00); 
	TFT_WriteData(0X00); 

	TFT_WriteIndex(0xF2);  
	TFT_WriteData(0X00); 

	TFT_WriteIndex(0x26);  
	TFT_WriteData(0X01); 

	TFT_WriteIndex(0xE0);  
	TFT_WriteData(0X0F); 
	TFT_WriteData(0X17); 
	TFT_WriteData(0X14); 
	TFT_WriteData(0X09); 
	TFT_WriteData(0X0C); 
	TFT_WriteData(0X06); 
	TFT_WriteData(0X43); 
	TFT_WriteData(0X75); 
	TFT_WriteData(0X36); 
	TFT_WriteData(0X08); 
	TFT_WriteData(0X13); 
	TFT_WriteData(0X05); 
	TFT_WriteData(0X10); 
	TFT_WriteData(0X0B); 
	TFT_WriteData(0X08); 


	TFT_WriteIndex(0xE1);  
	TFT_WriteData(0X00); 
	TFT_WriteData(0X1F); 
	TFT_WriteData(0X23); 
	TFT_WriteData(0X03); 
	TFT_WriteData(0X0E); 
	TFT_WriteData(0X04); 
	TFT_WriteData(0X39); 
	TFT_WriteData(0X25); 
	TFT_WriteData(0X4D); 
	TFT_WriteData(0X06); 
	TFT_WriteData(0X0D); 
	TFT_WriteData(0X0B); 
	TFT_WriteData(0X33); 
	TFT_WriteData(0X37); 
	TFT_WriteData(0X0F); 

	TFT_WriteIndex(0x29);  	
}


/*************************************************
��������TFT_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�,Y_IncMode��ʾ������y������x
����ֵ����
*************************************************/
void TFT_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{	
	TFT_WriteIndex(0x2a);
	TFT_WriteData16Bit(x_start>>8,x_start);
	TFT_WriteData16Bit(x_end>>8,x_end);
	TFT_WriteIndex(0x2b);
	TFT_WriteData16Bit(y_start>>8,y_start);
	TFT_WriteData16Bit(y_end>>8,y_end);
	TFT_WriteIndex(0x2c);

}

/*************************************************
��������TFT_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void TFT_SetXY(u16 x,u16 y)
{
  TFT_WriteIndex(0x2a);
	TFT_WriteData16Bit(x>>8,x);
	TFT_WriteIndex(0x2b);
	TFT_WriteData16Bit(y>>8,y);
	TFT_WriteIndex(0x2c);
}

	
/*************************************************
��������TFT_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����
*************************************************/
void TFT_DrawPoint(u16 x,u16 y,u16 Data)
{
	TFT_SetXY(x,y);
	TFT_WriteData(Data>>8);
	TFT_WriteData(Data);
}    

/*****************************************
 �������ܣ���TFTĳһ�����ɫ                          
 ���ڲ�����color  ����ɫֵ                                 
******************************************/
u16 TFT_ReadPoint(u16 x,u16 y)
{
  u8 r,g,b;
	u16 R,G,B,Data;
	TFT_SetXY(x,y);  
	TFT_CS_CLR;
	TFT_WriteIndex(0X2E); //��һ��д���������
  TFT_RS_SET;
	TFT_RS_CLR; //��������
  SPI_WriteByte(0xff);//�ڶ��οն�дDUMMY CLOCK
	r=SPI_WriteByte(0xff); //����λ��Ч
	g=SPI_WriteByte(0xff); //����λ��Ч
	b=SPI_WriteByte(0xff); //����λ��Ч
	TFT_CS_SET;
	R = (r<<1)&0x00FF;
	G = g&0x00FF;
	B = (b<<1)&0x00FF;
	Data = 	(R<<8)|(G<<5)|(B>>3);
	return Data;
}
/*
		r=LCD->LCD_RAM;  		  						
		delay_us(2);	  
		b=LCD->LCD_RAM; 
		g=r&0XFF;//9341Ҫ�����ζ���
		g<<=8;
		return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
*/

/*************************************************
��������TFT_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void TFT_Clear(u16 Color)               
{	
   unsigned int i,m;
   TFT_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   TFT_RS_SET;
   
   for(i=0;i<Y_MAX_PIXEL;i++)
   {
    for(m=0;m<X_MAX_PIXEL;m++)
      {	 
		SPI_WriteByte(Color>>8);
		SPI_WriteByte(Color);
      }   
	}
}


void TFT_Circle(u16 X,u16 Y,u16 R,u16 fc) 
{//Bresenham�㷨 
    unsigned short  a,b; 
    int c; 
    a=0; 
    b=R; 
    c=3-2*R; 
    while (a<b) 
    { 
        TFT_DrawPoint(X+a,Y+b,fc);     //        7 
        TFT_DrawPoint(X-a,Y+b,fc);     //        6 
        TFT_DrawPoint(X+a,Y-b,fc);     //        2 
        TFT_DrawPoint(X-a,Y-b,fc);     //        3 
        TFT_DrawPoint(X+b,Y+a,fc);     //        8 
        TFT_DrawPoint(X-b,Y+a,fc);     //        5 
        TFT_DrawPoint(X+b,Y-a,fc);     //        1 
        TFT_DrawPoint(X-b,Y-a,fc);     //        4 

        if(c<0) c=c+4*a+6; 
        else 
        { 
            c=c+4*(a-b)+10; 
            b-=1; 
        } 
       a+=1; 
    } 
    if (a==b) 
    { 
        TFT_DrawPoint(X+a,Y+b,fc); 
        TFT_DrawPoint(X+a,Y+b,fc); 
        TFT_DrawPoint(X+a,Y-b,fc); 
        TFT_DrawPoint(X-a,Y-b,fc); 
        TFT_DrawPoint(X+b,Y+a,fc); 
        TFT_DrawPoint(X-b,Y+a,fc); 
        TFT_DrawPoint(X+b,Y-a,fc); 
        TFT_DrawPoint(X-b,Y-a,fc); 
    } 
	
} 
//���ߺ�����ʹ��Bresenham �����㷨
void TFT_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color)   
{
int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2, 
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping	

	TFT_SetXY(x0,y0);
	dx = x1-x0;//����x����
	dy = y1-y0;//����y����

	if (dx>=0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;  
	} 
	
	if (dy>=0)
	{
		y_inc = 1;
	} 
	else
	{
		y_inc = -1;
		dy    = -dy; 
	} 

	dx2 = dx << 1;
	dy2 = dy << 1;

	if (dx > dy)//x�������y���룬��ôÿ��x����ֻ��һ���㣬ÿ��y���������ɸ���
	{//���ߵĵ�������x���룬��x���������
		// initialize error term
		error = dy2 - dx; 

		// draw the line
		for (index=0; index <= dx; index++)//Ҫ���ĵ������ᳬ��x����
		{
			//����
			TFT_DrawPoint(x0,y0,Color);
			
			// test if error has overflowed
			if (error >= 0) //�Ƿ���Ҫ����y����ֵ
			{
				error-=dx2;

				// move to next line
				y0+=y_inc;//����y����ֵ
			} // end if error overflowed

			// adjust the error term
			error+=dy2;

			// move to the next pixel
			x0+=x_inc;//x����ֵÿ�λ���󶼵���1
		} // end for
	} // end if |slope| <= 1
	else//y�����x�ᣬ��ÿ��y����ֻ��һ���㣬x�����ɸ���
	{//��y��Ϊ��������
		// initialize error term
		error = dx2 - dy; 

		// draw the line
		for (index=0; index <= dy; index++)
		{
			// set the pixel
			TFT_DrawPoint(x0,y0,Color);

			// test if error overflowed
			if (error >= 0)
			{
				error-=dy2;

				// move to next line
				x0+=x_inc;
			} // end if error overflowed

			// adjust the error term
			error+=dx2;

			// move to the next pixel
			y0+=y_inc;
		} // end for
	} // end else |slope| > 1
}

void TFT_box(u16 x, u16 y, u16 w, u16 h,u16 bc)
{
	TFT_DrawLine(x,y,x+w,y,0xEF7D);
	TFT_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
	TFT_DrawLine(x,y+h,x+w,y+h,0x2965);
	TFT_DrawLine(x,y,x,y+h,0xEF7D);
    TFT_DrawLine(x+1,y+1,x+1+w-2,y+1+h-2,bc);
}
void TFT_box2(u16 x,u16 y,u16 w,u16 h, u8 mode)
{
	if (mode==0)	{
		TFT_DrawLine(x,y,x+w,y,0xEF7D);
		TFT_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
		TFT_DrawLine(x,y+h,x+w,y+h,0x2965);
		TFT_DrawLine(x,y,x,y+h,0xEF7D);
		}
	if (mode==1)	{
		TFT_DrawLine(x,y,x+w,y,0x2965);
		TFT_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xEF7D);
		TFT_DrawLine(x,y+h,x+w,y+h,0xEF7D);
		TFT_DrawLine(x,y,x,y+h,0x2965);
	}
	if (mode==2)	{
		TFT_DrawLine(x,y,x+w,y,0xffff);
		TFT_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xffff);
		TFT_DrawLine(x,y+h,x+w,y+h,0xffff);
		TFT_DrawLine(x,y,x,y+h,0xffff);
	}
}


/**************************************************************************************
��������: ����Ļ��ʾһ͹��İ�ť��
��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
��    ��: ��
**************************************************************************************/
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
{
	TFT_DrawLine(x1,  y1,  x2,y1, WHITE); //H
	TFT_DrawLine(x1,  y1,  x1,y2, WHITE); //V
	
	TFT_DrawLine(x1+1,y2-1,x2,y2-1, GRAY1);  //H
	TFT_DrawLine(x1,  y2,  x2,y2, GRAY2);  //H
	TFT_DrawLine(x2-1,y1+1,x2-1,y2, GRAY1);  //V
  TFT_DrawLine(x2  ,y1  ,x2,y2, GRAY2); //V
}

/**************************************************************************************
��������: ����Ļ��ʾһ���µİ�ť��
��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
��    ��: ��
**************************************************************************************/
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2)
{
	TFT_DrawLine(x1,  y1,  x2,y1, GRAY2);  //H
	TFT_DrawLine(x1+1,y1+1,x2,y1+1, GRAY1);  //H
	TFT_DrawLine(x1,  y1,  x1,y2, GRAY2);  //V
	TFT_DrawLine(x1+1,y1+1,x1+1,y2, GRAY1);  //V
	TFT_DrawLine(x1,  y2,  x2,y2, WHITE);  //H
	TFT_DrawLine(x2,  y1,  x2,y2, WHITE);  //V
}

void TFT_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) < 128) 
		{
			k=*s;
			if (k==13) 
			{
				x=x0;
				y+=16;
			}
			else 
			{
				if (k>32) k-=32; else k=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[k*16+i]&(0x80>>j))	TFT_DrawPoint(x+j,y+i,fc);
						else 
						{
							if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
						}
					}
				x+=8;
			}
			s++;
		}
			
		else 
		{
		

			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x80>>j))	TFT_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	TFT_DrawPoint(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) TFT_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		} 
		
	}
}

void TFT_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k;

	while(*s) 
	{
		if( *s < 0x80 ) 
		{
			k=*s;
			if (k>32) k-=32; else k=0;

		    for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	
					TFT_DrawPoint(x+j,y+i,fc);
					else 
					{
						if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
					}
				}
			s++;x+=8;
		}
		else 
		{

			for (k=0;k<hz24_num;k++) 
			{
			  if ((hz24[k].Index[0]==*(s))&&(hz24[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<24;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3]&(0x80>>j))
								TFT_DrawPoint(x+j,y+i,fc);
								else 
								{
									if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+1]&(0x80>>j))	TFT_DrawPoint(x+j+8,y+i,fc);
								else {
									if (fc!=bc) TFT_DrawPoint(x+j+8,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+2]&(0x80>>j))	
								TFT_DrawPoint(x+j+16,y+i,fc);
								else 
								{
									if (fc!=bc) TFT_DrawPoint(x+j+16,y+i,bc);
								}
							}
				    }
			  }
			}
			s+=2;x+=24;
		}
	}
}
void TFT_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num)
{
	unsigned char i,j,k,c;
	//TFT_text_any(x+94+i*42,y+34,32,32,0x7E8,0x0,sz32,knum[i]);
//	w=w/8;

    for(i=0;i<32;i++)
	{
		for(j=0;j<4;j++) 
		{
			c=*(sz32+num*32*4+i*4+j);
			for (k=0;k<8;k++)	
			{
	
		    	if(c&(0x80>>k))	TFT_DrawPoint(x+j*8+k,y+i,fc);
				else {
					if (fc!=bc) TFT_DrawPoint(x+j*8+k,y+i,bc);
				}
			}
		}
	}
}



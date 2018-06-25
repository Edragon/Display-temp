#include"GUItest.h"
#include "lcd.h"
#include "string.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
 void delay (int cnt) 
{
  int i;
	i=5000*cnt;
  while (i--);

}
void Gui_ShowString(u16 x,u16 y,u8 *p)
{   /*      
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {   
		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
		return;     
        Gui_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
        x+=size/2;
        p++;
    } */ 

	LCD_ShowString(x,y,16,p,1);
} 


void Gui_ShowChar(u16 x,u16 y,u8 num)
{

	LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,num,16,1);
}

/*********************************/
/* �������ܣ���ʾԲ��5*5         */
/*********************************/
void LCD_Draw5Point(uint16_t x, uint16_t y, uint16_t color)
{
	POINT_COLOR=color;
	LCD_DrawPoint(x-1,y-2);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_DrawPoint(x-2,y-1);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_DrawPoint(x-2,y);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_DrawPoint(x-2,y+1);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_DrawPoint(x-1,y+2);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);

}


/*********************************/
/* �������ܣ���ʾԲ��9*9         */
/*********************************/
void LCD_Draw9Point(uint16_t x, uint16_t y, uint16_t color)
{
	POINT_COLOR=color;
	LCD_DrawPoint(x-1,y-4);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_DrawPoint(x-4,y-1);
	LCD_DrawPoint(x-4,y);
	LCD_DrawPoint(x-4,y+1);
	LCD_DrawPoint(x+4,y-1);
	LCD_DrawPoint(x+4,y);
	LCD_DrawPoint(x+4,y+1);
	LCD_DrawPoint(x-1,y+4);
	LCD_WR_DATA(POINT_COLOR);
	LCD_WR_DATA(POINT_COLOR);
	LCD_Fill(x-3,y-3,x+3,y+3, color);
}
/***********************************/
/* �������ܣ���ʾ��ťȡ��״̬      */
/***********************************/
void EscButton(uint16_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend)
{
	POINT_COLOR=LGRAY;
	LCD_DrawLine(xstart, ystart, xend, ystart);//����������1
	LCD_DrawLine(xstart, ystart, xstart, yend);//���������1
	POINT_COLOR=WHITE;
	LCD_DrawLine(xstart+1, ystart+1, xend-1, ystart+1);//����������2
	LCD_DrawLine(xstart+1, ystart+1, xstart+1, yend-1);//���������2
	POINT_COLOR=BLACK;
	LCD_DrawLine(xstart, yend, xend, yend);//���ײ�����1
	LCD_DrawLine(xend, ystart, xend, yend);//���ұ�����1
	POINT_COLOR=DARKGRAY;
	LCD_DrawLine(xstart+1, yend-1, xend-1, yend-1);//���ײ�����2
	LCD_DrawLine(xend-1, ystart+1, xend-1, yend-1);//���ұ�����2
}
/*******************************/
/* �������ܣ���ʾ��׼��ť      */
/*******************************/
void Draw_Button(uint16_t xstart,uint16_t ystart,uint16_t xend,uint16_t yend)
{
	EscButton(xstart, ystart, xend, yend);
	LCD_Fill(xstart+2, ystart+2, xend-2, yend-2,LGRAY);//����м���ɫ
}

/***********************************/
/* �������ܣ���ʾ��ťѡ��״̬      */
/***********************************/
void SetButton(uint8_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend)
{
	POINT_COLOR=BLACK;
	LCD_DrawLine(xstart, ystart, xend, ystart);//����������1
	LCD_DrawLine(xstart, ystart, xstart, yend);//���������1
	POINT_COLOR=DARKGRAY;
	LCD_DrawLine(xstart+1, ystart+1, xend-1, ystart+1);//����������2
	LCD_DrawLine(xstart+1, ystart+1, xstart+1, yend-1);//���������2
	POINT_COLOR=LGRAY;
	LCD_DrawLine(xstart+1, yend-1, xend-1, yend-1);//���ײ�����1
	LCD_DrawLine(xend-1, ystart+1, xend-1, yend-1);//���ұ�����1	
	POINT_COLOR=WHITE;
	LCD_DrawLine(xstart, yend, xend, yend);//���ײ�����2
	LCD_DrawLine(xend, ystart, xend, yend);//���ұ�����2
}




/***********************************/
/* �������ܣ���ʾһ�����������    */
/***********************************/
void Draw_TextBox(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend)
{
	POINT_COLOR=DARKGRAY;
	LCD_DrawLine(xstart, ystart, xend, ystart);//����������1
	LCD_DrawLine(xstart, ystart+1, xstart, yend);//����������1
	POINT_COLOR=BLACK;
	LCD_DrawLine(xstart+1, ystart+1, xend-1, ystart+1);//����������2
	LCD_DrawLine(xstart+1, ystart+2, xstart+1, yend-1);//����������2
	POINT_COLOR=WHITE;
	LCD_DrawLine(xstart, yend, xend, yend);//���ײ�����1
	LCD_DrawLine(xend, ystart, xend, yend);//����������1
	POINT_COLOR=LGRAY;
	LCD_DrawLine(xstart+1, yend-1, xend-1, yend-1);//���ײ�����2
	LCD_DrawLine(xend-1, ystart+1, xend-1, yend-1);//����������2
	LCD_Fill(xstart+2, ystart+2, xend-2, yend-2,WHITE);	
}
/***********************************/
/* �������ܣ���ʾһ�����ڣ�        */
/* ˵    ����caption:��������      */
/***********************************/
void Draw_Window(uint16_t xstart,uint16_t ystart,uint16_t xend,uint16_t yend,uint8_t* caption)
{
	Draw_Button(xstart, ystart, xend, yend);   // ��ʾ���崰��
	LCD_Fill(xstart+3, ystart+3, xend-3, ystart+25, DARKBLUE);	 // ��ʾ������
	Draw_TextBox(xstart+3, ystart+29, xend-3, yend-3); // ��ʾ�ı�������
	POINT_COLOR = WHITE;
	BACK_COLOR = DARKBLUE;
	Show_Str(xstart+5, ystart+6,POINT_COLOR,BACK_COLOR,caption,16,1);

}

/*******************************************/	  
/* �������ܣ���ʾһ��Frame                 */
/* ˵    �����ڵ��ô˺���ʱ����Ҫ�Ȱ���Ҫ  */
/*           ���õķ�Χ�ڱ���ɫ����ΪLGRAY */
/*******************************************/
void Draw_Frame(uint16_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend,uint8_t *FrameName)
{
 	POINT_COLOR = DARKGRAY;
	LCD_DrawLine(xstart, ystart, xend, ystart);	  // �ϱ߿�
	LCD_DrawLine(xstart, yend, xend, yend);	// �±߿�
	LCD_DrawLine(xstart, ystart, xstart, yend);	// ��߿�
	LCD_DrawLine(xend, ystart, xend, yend);	   // �ұ߿�

	POINT_COLOR = WHITE;
	LCD_DrawLine(xstart+1, ystart+1, xend-1, ystart+1); // �ϱ߿�ƹ�
	LCD_DrawLine(xstart, yend+1, xend+1, yend+1);  // �±߿�ƹ�
	LCD_DrawLine(xstart+1, ystart+1, xstart+1, yend-1);	  // ��߿�ƹ�
	LCD_DrawLine(xend+1, ystart, xend+1, yend+1);		 // �ұ߿�ƹ�

	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	Gui_ShowString(xstart+5, ystart-6, FrameName);	 // ��ʾFrame����
}


/***********************************/
/* �������ܣ�LOADING.....          */
/***********************************/
void POINT_Demo(void)
{
	uint8_t x=lcddev.width/2,y=lcddev.height/2,r=20,t,m,i;

	t = 7*r/10;
	m =100;	//��ʾ�ٶȺ���ֵ
	
	DrawTestPage("GUI Loading");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
	POINT_COLOR = WHITE;
	BACK_COLOR = BLACK;
	Gui_ShowString((lcddev.width-96)/2, lcddev.height/2+r+10, "Loading.....");
	for(i=0;i<2;i++)
	{
		LCD_Draw9Point(x, y-r, WHITE); //����һ����
		delay(m);
		LCD_Draw9Point(x+t, y-t, WHITE); //���ڶ�����
		delay(m);
		LCD_Draw9Point(x, y-r, BLACK); //ɾ����һ����
		delay(m);
		LCD_Draw9Point(x+r, y, WHITE); //����������
		delay(m);
		LCD_Draw9Point(x+t, y-t, BLACK);  //ɾ���ڶ�����
		delay(m);
		LCD_Draw9Point(x+t, y+t, WHITE);  //�����ĸ���
		delay(m);
		LCD_Draw9Point(x+r, y, BLACK); //ɾ����������
		delay(m);
		LCD_Draw9Point(x, y+r, WHITE);  //���������
		delay(m);
		LCD_Draw9Point(x+t, y+t, BLACK);  //ɾ�����ĸ���
		delay(m);
		LCD_Draw9Point(x-t, y+t, WHITE);  //����������
		delay(m);
		LCD_Draw9Point(x, y+r, BLACK);  //ɾ���������
		delay(m);
		LCD_Draw9Point(x-r, y, WHITE);  //�����߸���
		delay(m);
		LCD_Draw9Point(x-t, y+t, BLACK);  //ɾ����������
		delay(m);
		LCD_Draw9Point(x-t, y-t, WHITE);  //���ڰ˸���
		delay(m);
		LCD_Draw9Point(x-r, y, BLACK);  //ɾ�����߸���
		delay(m);
		LCD_Draw9Point(x-t, y-t, BLACK);  //ɾ���ڰ˸���
		delay(m);
	}
}


/******************************************/
/* �������ܣ���ɫ��ʾ���ۿ�ˢ���ٶ�       */
/******************************************/ 
void RGB_Demo(void)
{
	uint8_t i;

	LCD_Clear(BLUE);
	for(i=0;i<10;i++)
	{
	LCD_Fill(0, 0,100,100,YELLOW);
	LCD_Fill(0, 0,120,120,RED);
	LCD_Fill(0, 0,140,140,GREEN);
	LCD_Fill(0, 0,160,160,PINK);
	LCD_Fill(0, 0,180,180,GRAY);
	LCD_Fill(0, 0,200,200,ORANGE);
	LCD_Fill(0, 0,200,200,PORPO);
	LCD_Fill(0, 0,200,200,LGRAYBLUE);
	LCD_Fill(0, 0,200,200,BLUE);
	}
	LCD_Clear(BLUE);
}

/******************************************/
/* �������ܣ��������α���                 */
/******************************************/ 
void BarReport_Demo(void)
{
	uint16_t i;	

	DrawTestPage("GUI BarReport");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
	POINT_COLOR = WHITE;
	//��������
	LCD_DrawLine(20, 50, 20, 210);
	LCD_DrawLine(10, 60, 20, 50);
	LCD_DrawLine(30, 60, 20, 50);
	//��������
	LCD_DrawLine(20, 210, 220, 210);
	LCD_DrawLine(210, 200, 220, 210);
	LCD_DrawLine(210, 220, 220, 210);
	//������
	LCD_Fill(35, 80, 55, 209,RED);
	LCD_Fill(75, 130, 95, 209,YELLOW);
	LCD_Fill(115, 60, 135, 209,BLUE);
	LCD_Fill(155, 90, 175, 209,GREEN);
	//���ν���
	delay(50);
	for(i=81;i<209;i++) //��ɫ������
	{
		LCD_Fill(35, 80, 55, i,BLACK);
		delay(10);
	}
	for(i=208;i>100;i--) //��ɫ������
	{
		LCD_Fill(35, i, 55, 209,RED);
		delay(10);
	}
	for(i=129;i>80;i--) //��ɫ������
	{
		LCD_Fill(75, i, 95, 130,YELLOW);
		delay(10);
	}
	for(i=25;i<160;i++) //��ɫ������
	{
		LCD_Fill(115, 24, 135, i,BLACK);
		delay(10);
	}						
}


/******************************************/
/* �������ܣ���������ʾ                   */
/******************************************/ 
void ProgresBar_Demo(void)
{
	uint8_t i,num=1;
	u16 x1=20;
	u16 y1=30;
	u16 x2=150;//130
	u16 y2=130;//100
	
		
	DrawTestPage("GUI ProgresBar");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
	Draw_Button(x1, y1, x2, y2);   // ��ʾ���崰��
	LCD_Fill(x1+3, y1+3, x2-3, y2-75, DARKBLUE);	 // ��ʾ������ 
	Gui_ShowString(x1+25, y1+5, "ProgresBar"); // ��ť��д��
	Draw_Button(x1+5, y1+70, x2-75, y2-5);  // ��ʾ��һ����ť
	Draw_Button(x1+75, y1+70, x2-5, y2-5);  // ��ʾ�ڶ�����ť
	POINT_COLOR=BLACK;	
	BACK_COLOR=LGRAY;
	Show_Str(x1+14, y1+74,POINT_COLOR,BACK_COLOR,"ȷ��",16,1);
	Show_Str(x1+84, y1+74, POINT_COLOR,BACK_COLOR,"ȡ��",16,1);
	Gui_ShowString(x1+80, y1+35, "%");	  
	for(i=x1+26;i<x2-5;i++)
	{
		LCD_Fill(x1+5, y1+53, i, y1+68, RED);
		delay(40);
		LCD_ShowNum(x1+62, y1+35, num,2,16);
		num++;
	}
}


/******************************************/
/* �������ܣ����ڼ�ͷ����ͼ��(����)       */
/******************************************/ 
void Draw_DirectButton(uint16_t xstart, uint16_t ystart)
{
	POINT_COLOR=BLACK;
	LCD_DrawLine(xstart+6, ystart+8, xstart+14, ystart+8);
	LCD_DrawLine(xstart+7, ystart+9, xstart+13, ystart+9);
	LCD_DrawLine(xstart+8, ystart+10, xstart+12, ystart+10);
	LCD_DrawPoint(xstart+9,ystart+11);LCD_DrawPoint(xstart+10,ystart+11);LCD_DrawPoint(xstart+11,ystart+11);
	LCD_DrawPoint(xstart+10,ystart+12);
}

/******************************************/
/* �������ܣ�comboЧ����ʾ                */
/******************************************/ 
void ComboDemo(void)
{
	DrawTestPage("GUI Combo");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,GRAY);
	//��һ�����������
	Draw_TextBox(50, 50, 200, 73);
	//�������б�ť(19*19)����
	Draw_Button(179, 52, 198, 71);
	Draw_DirectButton(179,52);
	delay(500);
	delay(500);
	delay(500);
	SetButton(179, 52, 198, 71);
	LCD_Fill(183, 56, 194, 67, LGRAY);
   	Draw_DirectButton(180,53);
	delay(500);
	delay(500);
	delay(500);
	EscButton(179, 52, 198, 71);
	LCD_Fill(183, 56, 194, 67, LGRAY);
	Draw_DirectButton(179,52);
	//���������б�
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(50, 74, 200, 143);
	LCD_Fill(51, 75, 199, 142, WHITE);
	//д�б��е�����
	LCD_Fill(51, 75, 199, 97, DARKBLUE); //��һ��Ĭ��Ϊѡ��״̬
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	Gui_ShowString(53, 79, "STM ICP Bridge");

	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	Gui_ShowString(53, 101, "STM PP Bridge");
	Gui_ShowString(53, 124, "None ISP");
	delay(500);
	delay(500);
	delay(500);
	//ѡ�еڶ���
	LCD_Fill(51, 75, 199, 97, WHITE);	   //��ȡ����һ��
	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	Gui_ShowString(53, 79, "STM ICP Bridge");

	LCD_Fill(51, 98, 199, 120, DARKBLUE);  //ѡ�еڶ���
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	Gui_ShowString(53, 101, "STM PP Bridge");
	delay(500);
	delay(500);
	delay(500);
	//ѡ�е�����
	LCD_Fill(51, 98, 199, 120, WHITE);//��ȡ��ѡ�еĵڶ���
	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	Gui_ShowString(53, 101, "STM PP Bridge");

	LCD_Fill(51, 121, 199, 142, DARKBLUE);//ѡ�е�����
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	Gui_ShowString(53, 124, "None ISP");
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	//���
	LCD_Fill(50, 74, 200, 143, LGRAY);
}

/******************************************/
/* �������ܣ�WindowЧ����ʾ               */
/******************************************/ 
void Window_Demo(void)
{

	uint16_t xstart=2,ystart=30,xend=lcddev.width*2/3,yend=lcddev.height-30;
	uint8_t i=3;
	DrawTestPage("GUI Window");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,GRAY);
	do
	{
		Draw_Window(xstart,ystart,xend,yend,"ȷ��");
		delay(500);
		delay(500);
		xstart+=15;ystart+=15;xend-=30;yend-=30;
	}while(--i);
}

/******************************************/
/* �������ܣ�ButtonЧ����ʾ               */
/******************************************/ 
void Button_Demo(void)
{		  	
	DrawTestPage("GUI Button");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Draw_TextBox(30, 60, 170, 90);	 // ��ʾһ�����������
	Draw_Button(180, 60, 230, 90);			 // ��ʾ1����ť
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	Show_Str(187,67,POINT_COLOR,BACK_COLOR,"����",16,1);

	
	POINT_COLOR = BLUE;
	BACK_COLOR = WHITE;
	Gui_ShowString(30,38,"News");
	LCD_DrawLine(30,55,62,55);
	Gui_ShowString(118,38,"Pic");
	LCD_DrawLine(118,55,150,55);
	POINT_COLOR = BLACK;
	Gui_ShowString(70,38,"Label");
	delay(500);
	delay(500);
	delay(500);
	
	Gui_ShowChar(35, 67, 'C');
	delay(500);
	Gui_ShowChar(43, 67, 'o');
	delay(500);
	Gui_ShowChar(51, 67, 'r');
	delay(500);
	Gui_ShowChar(58, 67, 't');
	delay(500);
	Gui_ShowChar(66, 67, 'e');
	delay(500);
	Gui_ShowChar(74, 67, 'x');
	delay(500);
	Gui_ShowChar(82, 67, '-');
	delay(500);
	Gui_ShowChar(88, 67, 'M');
	delay(500);


	SetButton(180, 60, 230, 90);			 // ���¡���������ť
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	Show_Str(187,67,POINT_COLOR,BACK_COLOR,"����",16,1);
	delay(500);

	EscButton(180, 60, 230, 90);			 // �ſ�����������ť
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	Show_Str(187,67,POINT_COLOR,BACK_COLOR,"����",16,1);
	POINT_COLOR = RED;
	BACK_COLOR = WHITE;		 
	Gui_ShowString(12,100,"The ARM Cortex-M is a group" );
	Gui_ShowString(12,120,"of 32-bit RISC ARM processor" );
	Gui_ShowString(12,140,"cores licensed by ARM Holdings." );
	Gui_ShowString(12,160,"The cores are intended for " );
	Gui_ShowString(12,180,"microcontroller use,and consist");
	Gui_ShowString(12,200,"of the Cortex-M0/M1/M2/M3/M4.");
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
	delay(500);
}

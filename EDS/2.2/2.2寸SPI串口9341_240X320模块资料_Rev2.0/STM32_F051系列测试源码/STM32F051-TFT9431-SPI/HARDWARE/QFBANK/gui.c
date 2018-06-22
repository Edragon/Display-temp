#include "gui.h"
#include "ili9328.h"
#include "stdint.h"
#include "delay.h"

/*********************************/
/* �������ܣ���ʾԲ��5*5         */
/*********************************/
void TFT_Draw5Point(uint16_t x, uint16_t y, uint16_t color)
{
	POINT_COLOR=color;
	TFT_DrawPoint(x-1,y-2);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_DrawPoint(x-2,y-1);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_DrawPoint(x-2,y);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_DrawPoint(x-2,y+1);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_DrawPoint(x-1,y+2);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);

}


/*********************************/
/* �������ܣ���ʾԲ��9*9         */
/*********************************/
void TFT_Draw9Point(uint16_t x, uint16_t y, uint16_t color)
{
	POINT_COLOR=color;
	TFT_DrawPoint(x-1,y-4);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_DrawPoint(x-4,y-1);
	TFT_DrawPoint(x-4,y);
	TFT_DrawPoint(x-4,y+1);
	TFT_DrawPoint(x+4,y-1);
	TFT_DrawPoint(x+4,y);
	TFT_DrawPoint(x+4,y+1);
	TFT_DrawPoint(x-1,y+4);
	TFT_WR_DATA(POINT_COLOR);
	TFT_WR_DATA(POINT_COLOR);
	TFT_Fill(x-3,y-3,x+3,y+3, color);
}

/*******************************/
/* �������ܣ���ʾ��׼��ť      */
/*******************************/
void Draw_Button(uint16_t xstart,uint16_t ystart,uint16_t xend,uint16_t yend)
{
	EscButton(xstart, ystart, xend, yend);
	TFT_Fill(xstart+2, ystart+2, xend-2, yend-2,LGRAY);//����м���ɫ
}

/***********************************/
/* �������ܣ���ʾ��ťѡ��״̬      */
/***********************************/
void SetButton(uint8_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend)
{
	POINT_COLOR=BLACK;
	TFT_DrawLine(xstart, ystart, xend, ystart);//����������1
	TFT_DrawLine(xstart, ystart, xstart, yend);//���������1
	POINT_COLOR=DARKGRAY;
	TFT_DrawLine(xstart+1, ystart+1, xend-1, ystart+1);//����������2
	TFT_DrawLine(xstart+1, ystart+1, xstart+1, yend-1);//���������2
	POINT_COLOR=LGRAY;
	TFT_DrawLine(xstart+1, yend-1, xend-1, yend-1);//���ײ�����1
	TFT_DrawLine(xend-1, ystart+1, xend-1, yend-1);//���ұ�����1	
	POINT_COLOR=WHITE;
	TFT_DrawLine(xstart, yend, xend, yend);//���ײ�����2
	TFT_DrawLine(xend, ystart, xend, yend);//���ұ�����2
}

/***********************************/
/* �������ܣ���ʾ��ťȡ��״̬      */
/***********************************/
void EscButton(uint16_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend)
{
	POINT_COLOR=LGRAY;
	TFT_DrawLine(xstart, ystart, xend, ystart);//����������1
	TFT_DrawLine(xstart, ystart, xstart, yend);//���������1
	POINT_COLOR=WHITE;
	TFT_DrawLine(xstart+1, ystart+1, xend-1, ystart+1);//����������2
	TFT_DrawLine(xstart+1, ystart+1, xstart+1, yend-1);//���������2
	POINT_COLOR=BLACK;
	TFT_DrawLine(xstart, yend, xend, yend);//���ײ�����1
	TFT_DrawLine(xend, ystart, xend, yend);//���ұ�����1
	POINT_COLOR=DARKGRAY;
	TFT_DrawLine(xstart+1, yend-1, xend-1, yend-1);//���ײ�����2
	TFT_DrawLine(xend-1, ystart+1, xend-1, yend-1);//���ұ�����2
}


/***********************************/
/* �������ܣ���ʾһ�����������    */
/***********************************/
void Draw_TextBox(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend)
{
	POINT_COLOR=DARKGRAY;
	TFT_DrawLine(xstart, ystart, xend, ystart);//����������1
	TFT_DrawLine(xstart, ystart+1, xstart, yend);//����������1
	POINT_COLOR=BLACK;
	TFT_DrawLine(xstart+1, ystart+1, xend-1, ystart+1);//����������2
	TFT_DrawLine(xstart+1, ystart+2, xstart+1, yend-1);//����������2
	POINT_COLOR=WHITE;
	TFT_DrawLine(xstart, yend, xend, yend);//���ײ�����1
	TFT_DrawLine(xend, ystart, xend, yend);//����������1
	POINT_COLOR=LGRAY;
	TFT_DrawLine(xstart+1, yend-1, xend-1, yend-1);//���ײ�����2
	TFT_DrawLine(xend-1, ystart+1, xend-1, yend-1);//����������2
	TFT_Fill(xstart+2, ystart+2, xend-2, yend-2,WHITE);	
}
/***********************************/
/* �������ܣ���ʾһ�����ڣ�        */
/* ˵    ����caption:��������      */
/***********************************/
void Draw_Window(uint16_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend,uint8_t* caption)
{
	Draw_Button(xstart, ystart, xend, yend);   // ��ʾ���崰��
	TFT_Fill(xstart+3, ystart+3, xend-3, ystart+25, DARKBLUE);	 // ��ʾ������
	Draw_TextBox(xstart+3, ystart+29, xend-3, yend-3); // ��ʾ�ı�������
	POINT_COLOR = WHITE;
	BACK_COLOR = DARKBLUE;
	TFT_ShowString(xstart+5, ystart+6, caption);
}

/*******************************************/	  
/* �������ܣ���ʾһ��Frame                 */
/* ˵    �����ڵ��ô˺���ʱ����Ҫ�Ȱ���Ҫ  */
/*           ���õķ�Χ�ڱ���ɫ����ΪLGRAY */
/*******************************************/
void Draw_Frame(uint16_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend,uint8_t *FrameName)
{
 	POINT_COLOR = DARKGRAY;
	TFT_DrawLine(xstart, ystart, xend, ystart);	  // �ϱ߿�
	TFT_DrawLine(xstart, yend, xend, yend);	// �±߿�
	TFT_DrawLine(xstart, ystart, xstart, yend);	// ��߿�
	TFT_DrawLine(xend, ystart, xend, yend);	   // �ұ߿�

	POINT_COLOR = WHITE;
	TFT_DrawLine(xstart+1, ystart+1, xend-1, ystart+1); // �ϱ߿�ƹ�
	TFT_DrawLine(xstart, yend+1, xend+1, yend+1);  // �±߿�ƹ�
	TFT_DrawLine(xstart+1, ystart+1, xstart+1, yend-1);	  // ��߿�ƹ�
	TFT_DrawLine(xend+1, ystart, xend+1, yend+1);		 // �ұ߿�ƹ�

	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	TFT_ShowString(xstart+5, ystart-6, FrameName);	 // ��ʾFrame����
}

/***********************************/
/* �������ܣ�LOADING.....          */
/***********************************/
void POINT_Demo(void)
{
	uint8_t x=120,y=160,r=20,t,m,i;

	t = 7*r/10;
	m =50;	//��ʾ�ٶȺ���ֵ
	
	TFT_Clear(BLACK);
	POINT_COLOR = WHITE;
	BACK_COLOR = BLACK;
	TFT_ShowString(90, 190, "Loading.....");
	for(i=0;i<2;i++)
	{
		TFT_Draw9Point(x, y-r, WHITE); //����һ����
		delay_ms(m);
		TFT_Draw9Point(x+t, y-t, WHITE); //���ڶ�����
		delay_ms(m);
		TFT_Draw9Point(x, y-r, BLACK); //ɾ����һ����
		delay_ms(m);
		TFT_Draw9Point(x+r, y, WHITE); //����������
		delay_ms(m);
		TFT_Draw9Point(x+t, y-t, BLACK);  //ɾ���ڶ�����
		delay_ms(m);
		TFT_Draw9Point(x+t, y+t, WHITE);  //�����ĸ���
		delay_ms(m);
		TFT_Draw9Point(x+r, y, BLACK); //ɾ����������
		delay_ms(m);
		TFT_Draw9Point(x, y+r, WHITE);  //���������
		delay_ms(m);
		TFT_Draw9Point(x+t, y+t, BLACK);  //ɾ�����ĸ���
		delay_ms(m);
		TFT_Draw9Point(x-t, y+t, WHITE);  //����������
		delay_ms(m);
		TFT_Draw9Point(x, y+r, BLACK);  //ɾ���������
		delay_ms(m);
		TFT_Draw9Point(x-r, y, WHITE);  //�����߸���
		delay_ms(m);
		TFT_Draw9Point(x-t, y+t, BLACK);  //ɾ����������
		delay_ms(m);
		TFT_Draw9Point(x-t, y-t, WHITE);  //���ڰ˸���
		delay_ms(m);
		TFT_Draw9Point(x-r, y, BLACK);  //ɾ�����߸���
		delay_ms(m);
		TFT_Draw9Point(x-t, y-t, BLACK);  //ɾ���ڰ˸���
		delay_ms(m);
	}
}


/******************************************/
/* �������ܣ���ɫ��ʾ���ۿ�ˢ���ٶ�       */
/******************************************/ 
void RGB_Demo(void)
{
	uint8 i;

	TFT_Clear(BLUE);
	for(i=0;i<3;i++)
	{
	TFT_Fill(0, 0,100,100,YELLOW);
	TFT_Fill(0, 0,120,120,RED);
	TFT_Fill(0, 0,140,140,GREEN);
	TFT_Fill(0, 0,160,160,PINK);
	TFT_Fill(0, 0,180,180,GRAY);
	TFT_Fill(0, 0,200,200,ORANGE);
	TFT_Fill(0, 0,200,200,PORPO);
	TFT_Fill(0, 0,200,200,LGRAYBLUE);
	TFT_Fill(0, 0,200,200,BLUE);
	}
	TFT_Clear(BLUE);
}

/******************************************/
/* �������ܣ��������α���                 */
/******************************************/ 
void BarReport_Demo(void)
{
	uint16_t i;	

	TFT_Clear(BLACK);
	POINT_COLOR = WHITE;
	//��������
	TFT_DrawLine(20, 140, 20, 300);
	TFT_DrawLine(10, 150, 20, 140);
	TFT_DrawLine(30, 150, 20, 140);
	//��������
	TFT_DrawLine(20, 300, 220, 300);
	TFT_DrawLine(210, 290, 220, 300);
	TFT_DrawLine(210, 310, 220, 300);
	//������
	TFT_Fill(35, 170, 55, 299,RED);
	TFT_Fill(75, 220, 95, 299,YELLOW);
	TFT_Fill(115, 150, 135, 299,BLUE);
	TFT_Fill(155, 180, 175, 299,GREEN);
	//���ν���
	delay_ms(50);
	for(i=171;i<299;i++) //��ɫ������
	{
		TFT_Fill(35, 170, 55, i,BLACK);
		delay_ms(10);
	}
	for(i=298;i>190;i--) //��ɫ������
	{
		TFT_Fill(35, i, 55, 299,RED);
		delay_ms(10);
	}
	for(i=219;i>170;i--) //��ɫ������
	{
		TFT_Fill(75, i, 95, 220,YELLOW);
		delay_ms(10);
	}
	for(i=115;i<250;i++) //��ɫ������
	{
		TFT_Fill(115, 114, 135, i,BLACK);
		delay_ms(10);
	}						
}


/******************************************/
/* �������ܣ���������ʾ                   */
/******************************************/ 
void ProgresBar_Demo(void)
{
	uint8_t i,num=1;
		
	TFT_Clear(BLUE);	   // ������ʾ��ɫ
	Draw_Button(100, 210, 230, 310);   // ��ʾ���崰��
	TFT_Fill(103, 213, 227, 235, DARKBLUE);	 // ��ʾ������ 
	Draw_Button(105, 280, 155, 305);  // ��ʾ��һ����ť
	Draw_Button(175, 280, 225, 305);  // ��ʾ�ڶ�����ť
	POINT_COLOR=BLACK;	
	BACK_COLOR=LGRAY;
	TFT_ShowString( 114, 284, "ȷ��"); // ��ť��д��
	TFT_ShowString( 184, 284, "�˳�");
	TFT_ShowString(180, 245, "%");	  
	for(i=126;i<225;i++)
	{
		TFT_Fill(105, 263, i, 278, RED);
		delay_ms(40);
		TFT_ShowNum(162, 245, num,2);
		num++;
	}
}


/******************************************/
/* �������ܣ����ڼ�ͷ����ͼ��(����)       */
/******************************************/ 
void Draw_DirectButton(uint16_t xstart, uint16_t ystart)
{
	POINT_COLOR=BLACK;
	TFT_DrawLine(xstart+6, ystart+8, xstart+14, ystart+8);
	TFT_DrawLine(xstart+7, ystart+9, xstart+13, ystart+9);
	TFT_DrawLine(xstart+8, ystart+10, xstart+12, ystart+10);
	TFT_DrawPoint(xstart+9,ystart+11);TFT_DrawPoint(xstart+10,ystart+11);TFT_DrawPoint(xstart+11,ystart+11);
	TFT_DrawPoint(xstart+10,ystart+12);
}

/******************************************/
/* �������ܣ�comboЧ����ʾ                */
/******************************************/ 
void ComboDemo(void)
{
	TFT_Clear(GRAY);
	//��һ�����������
	Draw_TextBox(50, 50, 200, 73);
	//�������б�ť(19*19)����
	Draw_Button(179, 52, 198, 71);
	Draw_DirectButton(179,52);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	SetButton(179, 52, 198, 71);
	TFT_Fill(183, 56, 194, 67, LGRAY);
   	Draw_DirectButton(180,53);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	EscButton(179, 52, 198, 71);
	TFT_Fill(183, 56, 194, 67, LGRAY);
	Draw_DirectButton(179,52);
	//���������б�
	TFT_DrawRectage(50, 74, 200, 143, BLACK);
	TFT_Fill(51, 75, 199, 142, WHITE);
	//д�б��е�����
	TFT_Fill(51, 75, 199, 97, DARKBLUE); //��һ��Ĭ��Ϊѡ��״̬
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	TFT_ShowString(53, 79, "NXP ICP Bridge");

	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	TFT_ShowString(53, 101, "NXP PP Bridge");
	TFT_ShowString(53, 124, "None ISP");
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	//ѡ�еڶ���
	TFT_Fill(51, 75, 199, 97, WHITE);	   //��ȡ����һ��
	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	TFT_ShowString(53, 79, "NXP ICP Bridge");

	TFT_Fill(51, 98, 199, 120, DARKBLUE);  //ѡ�еڶ���
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	TFT_ShowString(53, 101, "NXP PP Bridge");
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	//ѡ�е�����
	TFT_Fill(51, 98, 199, 120, WHITE);//��ȡ��ѡ�еĵڶ���
	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	TFT_ShowString(53, 101, "NXP PP Bridge");

	TFT_Fill(51, 121, 199, 142, DARKBLUE);//ѡ�е�����
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	TFT_ShowString(53, 124, "None ISP");
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	//���
	TFT_Fill(50, 74, 200, 143, LGRAY);
}

/******************************************/
/* �������ܣ�WindowЧ����ʾ               */
/******************************************/ 
void Window_Demo(void)
{
	uint16_t xstart=0,ystart=0,xend=239,yend=319;
	uint8_t i=5;

	do
	{
		Draw_Window(xstart,ystart,xend,yend,"������");
		delay_ms(500);
		delay_ms(500);
		xstart+=15;ystart+=15;xend-=30;yend-=30;
	}while(--i);
}

/******************************************/
/* �������ܣ�ButtonЧ����ʾ               */
/******************************************/ 
void Button_Demo(void)
{		
	TFT_Clear(WHITE);
	Draw_TextBox(30, 60, 170, 90);	 // ��ʾһ�����������
	Draw_Button(180, 60, 230, 90);			 // ��ʾ1����ť
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	TFT_ShowString(187,67,"����");		 // ��ť��д��
	
	POINT_COLOR = BLUE;
	BACK_COLOR = WHITE;
	TFT_ShowString(30,38,"����");
	TFT_DrawLine(30,55,62,55);
	TFT_ShowString(110,38,"ͼƬ");
	TFT_DrawLine(110,55,142,55);
	POINT_COLOR = BLACK;
	TFT_ShowString(70,38,"��ǩ");
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	
	TFT_ShowChar(35, 67, 'C');
	delay_ms(500);
	TFT_ShowChar(43, 67, 'o');
	delay_ms(500);
	TFT_ShowChar(51, 67, 'r');
	delay_ms(500);
	TFT_ShowChar(58, 67, 't');
	delay_ms(500);
	TFT_ShowChar(66, 67, 'e');
	delay_ms(500);
	TFT_ShowChar(74, 67, 'x');
	delay_ms(500);
	TFT_ShowChar(82, 67, '-');
	delay_ms(500);
	TFT_ShowChar(88, 67, 'M');
	delay_ms(500);
	TFT_ShowChar(96, 67, '0');
	delay_ms(500);

	SetButton(180, 60, 230, 90);			 // ���¡���������ť
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	TFT_ShowString(188,68,"����");		 
	delay_ms(500);

	EscButton(180, 60, 230, 90);			 // �ſ�����������ť
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	TFT_ShowString(187,67,"����");
	POINT_COLOR = BLACK;
	BACK_COLOR = WHITE;		 
	TFT_ShowString(12,100,"ARM Cortex-M0�����������е���С���ܺ���ͺ���Ч��ߵ�ARM���������ô������������С���ܺļ��Ͳ�������Ĵ��������٣���ʹ�ÿ�����Ա�ܹ���8λ���豸ʵ��32λ�豸�����ܣ��Ӷ�ʡ��16λ�豸���з����衣Cortex-M0 ���������͵�����Ҳʹ�������Բ�����ģ��ͻ���ź��豸�С�");
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
}











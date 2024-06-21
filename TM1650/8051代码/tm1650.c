#include<15F104.h>
#include"tm1650.h"
void Delay_us(uint i) //us��ʱ
{
	for(;i>0;i--)
	{
		_nop_();
//		_nop_();
//		_nop_();
//		_nop_();
//		_nop_();
	}
}
void I2CStart(void)	//��ʼ�ź�
{
	CLK_H;
	DIO_H;
	Delay_us(5);
	DIO_L;
	
}

void I2Cask(void) //ACK�ź�
{
	uchar timeout = 1;
	CLK_H;
	Delay_us(5);
	CLK_L;
	while((DIO)&&(timeout<=100))
	{
	  timeout++;	
	}
	Delay_us(5);
	CLK_L;
}

void I2CStop(void) //ֹͣ�ź�
{
	CLK_H;
	DIO_L;
	Delay_us(5);
	DIO_H;
}

void I2CWrByte(uchar oneByte) //дһ���ֽڸ�λ��ǰ����λ�ں�
{
	uchar i;
	CLK_L;
	Delay_us(1);
	for(i=0;i<8;i++)
	{	
		oneByte = oneByte<<1;
		DIO = CY;
		CLK_L;
		Delay_us(5);
		CLK_H;
		Delay_us(5);
		CLK_L;
	}
}

uchar Scan_Key(void)	  // ����ɨ��
{
	uchar i;
	uchar rekey;
	I2CStart();
	I2CWrByte(0x49);//����������
	I2Cask();
	//DIO_H;
	for(i=0;i<8;i++)
	{
	   CLK_H;
	   rekey = rekey<<1;
	   if(DIO)
	   {
	   	rekey++;
	   } 
	   Delay_us(5);
	   CLK_L;	
	}
	I2Cask();
	I2CStop();
	return(rekey);
}


void TM1650_Set(uchar add,uchar dat) //�������ʾ
{
	//д�Դ����Ӹߵ�ַ��ʼд
	I2CStart();
	I2CWrByte(add); //��һ���Դ��ַ
	I2Cask();
	I2CWrByte(dat);
	I2Cask();
	I2CStop();
}
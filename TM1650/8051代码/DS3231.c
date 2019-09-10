#include <15f104.h>
#include<intrins.h>
#include"ds3231.h"

void delay()//΢�뼶��ʱ
{ ;; }

void start()//��ʼ�ź�
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();	
}

void stop()//ֹͣ�ź�
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}

bit respons()  //Ӧ��
{
	uchar i;
	i=0;
	scl=1;
	delay();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay();
	return(1);
}
void write_i2c(uchar dat)//��IIC�豸д��1BYTE������
{
	uchar i,temp;
	temp=dat;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		scl=0;
	    delay();
		sda=CY;
		delay();
		scl=1;
		delay();
	}
	scl=0;
	delay();
	sda=1;
	delay();
}

uchar read_i2c()
{
	uchar i,k;
	scl=0;
	delay();
	sda=1;
	delay();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay();
		k=(k<<1)|sda;
		scl=0;
		delay();
	}
	return k;
	
}
void write_ds3231(uchar address,uchar dat)	//��DS3231��ĳ����ַд��1byte����
{
	start();
	write_i2c(0xd0);
	while(!respons());
	write_i2c(address);
	while(!respons());
	write_i2c(dat);
	while(!respons());
	stop();
}

uchar read_ds3231(uchar address)	 //��DS3231��ĳ����ַ��ȡ1byte����
{
	uchar dat;
	start();
	write_i2c(0xd0);
	while(!respons());
	write_i2c(address);
	while(!respons()); 
	start();
	write_i2c(0xd1);
	while(!respons());
	dat=read_i2c();
	stop();
	return dat;
} 
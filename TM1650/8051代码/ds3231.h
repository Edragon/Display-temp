#ifndef __DS3231_H__
#define __DS3231_H__
#define uchar unsigned char
#define uint  unsigned int
sbit sda=P3^1;
sbit scl=P3^0;

uchar read_ds3231(uchar address);	 //��IIC�豸��ĳ����ַ��ȡ1byte����
void write_ds3231(uchar address,uchar dat);

#endif
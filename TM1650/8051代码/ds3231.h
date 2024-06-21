#ifndef __DS3231_H__
#define __DS3231_H__
#define uchar unsigned char
#define uint  unsigned int
sbit sda=P3^1;
sbit scl=P3^0;

uchar read_ds3231(uchar address);	 //从IIC设备的某个地址读取1byte数据
void write_ds3231(uchar address,uchar dat);

#endif
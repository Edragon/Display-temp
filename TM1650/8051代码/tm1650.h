#ifndef __TM1650_H__
#define __TM1650_H__
#include<15f104.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit DIO=P3^3;
sbit CLK=P3^2;

#define CLK_H  CLK = 1
#define CLK_L  CLK = 0

#define DIO_H  DIO = 1
#define DIO_L  DIO = 0

void TM1650_Set(uchar add,uchar dat);
uchar Scan_Key(void);


#endif
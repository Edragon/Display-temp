#ifndef __SDUPDATA_H
#define __SDUPDATA_H

#include "stm32f0xx.h"
#include "w25x16.h"
#include "ili9328.h"
#include "stdio.h"						 //printf函数库文件
#include "string.h"						 //字符串库文件
#include "integer.h"
#include "ffconf.h"
#include "diskio.h"
#include "ff.h"

#define EN_UPDATE_FONT //使能字体更新,通过关闭这里实现禁止字库更新

 
extern uint32_t FONT16ADDR ;
extern uint32_t FONT12ADDR ;
extern uint32_t UNI2GBKADDR;

uint8_t Update_Font(void);//更新字库   
uint8_t Font_Init(void);//初始化字库


#endif /* _SDUPDATA_H */
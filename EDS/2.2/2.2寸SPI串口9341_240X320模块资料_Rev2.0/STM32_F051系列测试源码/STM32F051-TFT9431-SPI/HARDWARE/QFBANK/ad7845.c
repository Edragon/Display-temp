// ------------------------------------
// 硬件连接：PB10---T-INT
//           PA4----T-CS 
//           PA5----T-CLK
//           PA6----T-OUT
// 					 PA7----T-DIN
//           SPI1-- AF0
//
// -------------------------------------
#include "ad7845.h"


// A/D 通道选择命令字和工作寄存器
#define	CHX 	0x90 	//通道X+的选择控制字	
#define	CHY 	0xd0	//通道Y+的选择控制字 


static void Delayus( int k)
{
 int j;
    
    for(j=k; j > 0; j--);    
}


static uint16_t RD_AD(uint8_t cmd) 
{
 uint8_t temp;
 uint16_t buf=0;
	
    //buf=GPIOD->IDR;
    //if(isBit16(buf, 9)==1)
    //   return(0);
    
    SPI_TOUCH_CS_LOW()   //TP_CS(0);

    //os_dly_wait(1);//300ms后再采样1次
    Delayus(50);
    
    SPI_Send_Byte(cmd);
    
    temp=SPI_Send_Byte(0xff);
    buf = temp;
    buf <<= 8;
    temp = SPI_Send_Byte(0xff);
    
 
   SPI_TOUCH_CS_HIGH(); //TP_CS(1);
    
    
    
    buf += temp;
    
    buf>>=4;//只有12位有效
    //buf&=0x0fff;
    return(buf);
}

//定义采样参数 ReadLoop采集次数， LOSS_DATA丢掉最大值，最小值个数

#define ReadLoop 13 //连续采集次数必须>3
#define LOSS_DATA 5 //丢掉最大最小数据个数
/*
功能：采集TP坐标数据

输出：
  xValue X坐标采集到的值,  yValue Y坐标采集到的值
返回：
  0=无效数据，1=有效数据

说明：采集13次，然后排序，保留中间3次取平均值
*/
uint8_t Read_XY(uint16_t *xValue, uint16_t *yValue) 
{ 
 uint16_t i, j;
 uint16_t bufX[ReadLoop];
 uint16_t bufY[ReadLoop];
 uint32_t sumX;
 uint32_t sumY;
 uint16_t val;
    
    //连续采集X坐标，Y坐标数据
    for(i=0; i<ReadLoop; i++)
    {
       //如果采集还没完，触摸已经抬起，那么放弃该次采集
       if(TP_IRQ)
          return(0);
       
       //while(TP_BUSY);
       //Delayus(5);
       bufX[i]=RD_AD(CHY);
       
       //while(TP_BUSY);
       //Delayus(5);
       bufY[i]=RD_AD(CHX);
       
       Delayus(5);
    }
    
    
    //对采集数据排序
    for(i=0; i<ReadLoop-1; i++)
    {
       for(j=i+1; j<ReadLoop; j++)
       {
          if(bufX[i]>bufX[j])
          {
             val=bufX[i];
             bufX[i]=bufX[j];
             bufX[j]=val;
          }
          
          if(bufY[i]>bufY[j])
          {
             val=bufY[i];
             bufY[i]=bufY[j];
             bufY[j]=val;
          }
       }
    }
    
    //丢掉最大最小数据后求和
    sumX=0;sumY=0;
    for(i=LOSS_DATA; i<ReadLoop-LOSS_DATA; i++)
    {
       sumX += bufX[i];
       sumY += bufY[i];
    }
    
    //取平均值
    *xValue=sumX/(ReadLoop-2*LOSS_DATA);
    *yValue=sumY/(ReadLoop-2*LOSS_DATA);
    
    return (1);    
}


/*
功能：采集TP坐标数据
输出：
  x：x坐标
  y：y坐标
返回：
  0=无效数据，1=有效数据
*/
uint8_t TP_GetAdXY(uint16_t *x, uint16_t *y) 
{
 uint8_t flag;
    
    if(TP_IRQ)
       return(0);
    flag=Read_XY(x, y);
    
    if(flag==0)
       return(0);
      
    //一般情况，X,Y都比0大，具体你根据实际情况定，小于一定范围的可以认为是无效数据
    if(*x<100 || *y<100)
       return(0);
    else
       return(1);
}

extern void Delay(unsigned long time);
/*
功能：本函数连续采样2次，间隔时间由delay参数确定,2次采样结果+-50范围内才算有效
2次是指连续采集到2个处理后的有效数据，本例实际是采集2*13=26次数据
输出：
  x：x坐标
  y：y坐标
输入：
  delay：采样间隔时间，单位ms

返回：
  0=无效数据，1=有效数据
*/
uint8_t TP_GetAdXY2(uint16_t *x, uint16_t *y, uint32_t delay) 
{uint16_t x1,y1;
 uint16_t x2,y2;
 uint8_t flag;
 //u16 adx,ady;
 

    flag=TP_GetAdXY(&x1, &y1);
    
    if(flag==0)
       return(0);
    
    //os_dly_wait(delay/OS_TIME);//300ms后再采样1次
	Delay(delay);
    
    flag=TP_GetAdXY(&x2, &y2);
    
    if(flag==0)
       return(0);
    
    //两次采样结果必须保持在一定范围内，该数值根据你实际情况定
    if( ( (x2<=x1 && x1<x2+50) || (x1<=x2 && x2<x1+50) )//前后两次采样在+-50内
     && ( (y2<=y1 && y1<y2+50) || (y1<=y2 && y2<y1+50) ) )
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return(1);
    }
    else
       return(0);
}





int setCalibrationMatrix( POINT * displayPtr,
                          POINT * screenPtr,
                          MATRIX * matrixPtr)
{

    int  retValue = OK ;



    matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) -
                         ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;

    if ( matrixPtr->Divider == 0 )
    {
        retValue = NOT_OK ;
    }
    else
    {
        matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) -
                        ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;

        matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) -
                        ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;

        matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                        (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                        (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;

        matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) -
                        ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;

        matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) -
                        ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;

        matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                        (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                        (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
    }

    return( retValue ) ;

} /* end of setCalibrationMatrix() */

int getDisplayPoint( POINT * displayPtr,
                     POINT * screenPtr,
                     MATRIX * matrixPtr )
{
    int  retValue = OK ;


    if ( matrixPtr->Divider != 0 )
    {

        /* Operation order is important since we are doing integer */
        /*  math. Make sure you add all terms together before      */
        /*  dividing, so that the remainder is not rounded off     */
        /*  prematurely.                                           */

        displayPtr->x = ( (matrixPtr->An * screenPtr->x) +
                          (matrixPtr->Bn * screenPtr->y) +
                          matrixPtr->Cn
                        ) / matrixPtr->Divider ;

        displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) +
                          (matrixPtr->En * screenPtr->y) +
                          matrixPtr->Fn
                        ) / matrixPtr->Divider ;
    }
    else
    {
        retValue = NOT_OK ;
    }

    return( retValue ) ;

} /* end of getDisplayPoint() */
#ifndef _AD7845_H_
#define _AD7845_H_

#include "stm32f0xx.h"
#include  "ili9328.h"


#ifndef		_CALIBRATE_C_
	#define		EXTERN         extern
#else
	#define		EXTERN
#endif



#ifndef		OK
	#define		OK		        0
	#define		NOT_OK		   -1
#endif



#define			INT32				long

#define  TP_IRQ   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define SPI_TOUCH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_TOUCH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)


/****************************************************/
/*                                                  */
/* Structures                                       */
/*                                                  */
/****************************************************/

typedef struct
{ 
   INT32    x;
   INT32    y;
}POINT;


#define  MATRIX_Type  INT32

typedef struct
{
							/* This arrangement of values facilitates 
							 *  calculations within getDisplayPoint() 
							 */
   MATRIX_Type    An;     /* A = An/Divider */
   MATRIX_Type    Bn;     /* B = Bn/Divider */
   MATRIX_Type    Cn;     /* C = Cn/Divider */
   MATRIX_Type    Dn;     /* D = Dn/Divider */
   MATRIX_Type    En;     /* E = En/Divider */
   MATRIX_Type    Fn;     /* F = Fn/Divider */
   MATRIX_Type    Divider ;
}MATRIX;




/****************************************************/
/*                                                  */
/* Function declarations                            */
/*                                                  */
/****************************************************/


EXTERN int setCalibrationMatrix( POINT * display,
                                 POINT * screen,
                                 MATRIX * matrix) ;


EXTERN int getDisplayPoint( POINT * display,
                            POINT * screen,
                            MATRIX * matrix ) ;

void TP_Init(void);

uint8_t TP_GetAdXY(uint16_t *x, uint16_t *y);
uint8_t TP_GetAdXY2(uint16_t *x, uint16_t *y, uint32_t delay);
uint8_t TP_GetLCDXY(uint16_t *x, uint16_t *y);







#endif  /* _AD7845_H_ */

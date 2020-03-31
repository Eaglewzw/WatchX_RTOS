#ifndef __OLED_H
#define __OLED_H

#include "driver/gpio.h"


/****************时钟线*********************/
#define OLED_SCLK_PINS  (GPIO_NUM_4)

/****************数据线*********************/
#define OLED_SDIN_PINS  (GPIO_NUM_5)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


#define OLED_SCLK_Clr()    gpio_set_level(OLED_SCLK_PINS, 0)
#define OLED_SCLK_Set()    gpio_set_level(OLED_SCLK_PINS, 1)

#define OLED_SDIN_Clr()    gpio_set_level(OLED_SDIN_PINS, 0)
#define OLED_SDIN_Set()    gpio_set_level(OLED_SDIN_PINS, 1)


#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	   


//-----------------OLED端口定义----------------  					   
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[]);
#endif  



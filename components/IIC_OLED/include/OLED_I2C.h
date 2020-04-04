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


#define SIZE        16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64


#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }

typedef enum
{
    Black = 0,
    White,      /*显示屏点亮为白色*/
}Color;



//-----------------OLED端口定义----------------  					   	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void OLED_DrawHorizontalLine(int16_t x, int16_t y, int16_t length);
void OLED_DrawVerticalLine(int16_t x, int16_t y, int16_t length);
void OLED_DrawRect(int16_t x, int16_t y, int16_t width, int16_t height);
void OLED_FillRect(int16_t xMove, int16_t yMove, int16_t width, int16_t height);
void OLED_DrawCircle(int16_t x0, int16_t y0, int16_t radius);
void OLED_DrawCircleQuads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads);
void OLED_FillCircle(int16_t x0, int16_t y0, int16_t radius);
void OLED_DrawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress);
void OLED_Init(void);
#endif  



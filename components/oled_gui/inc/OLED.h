#ifndef __INCLUDE_OLED_H__
#define __INCLUDE_OLED_H__


//#include "SSD1306_SPI.h"

#include "SSD1306_I2C.h"

#define LCD_SIZE_WIDTH      (128)
#define LCD_SIZE_HEIGHT     (64)
#define LCD_SIZE_COLUMNS    (LCD_SIZE_WIDTH)
#define LCD_SIZE_PAGES      (LCD_SIZE_HEIGHT/8)

typedef enum
{
	OLED_COLOR_BKG = 0,
	OLED_COLOR_FRG = 1,
	OLED_COLOR_TRS = 2,
}OLED_COLOR;

//Common operation
#define SET_PAGE_BIT(PAGE, Bit)		((PAGE) = (PAGE) | (0x01 << (Bit)))
#define CLR_PAGE_BIT(PAGE, Bit)		((PAGE) = (PAGE) & (~(0x01 << (Bit))))
#define GET_PAGE_BIT(PAGE, Bit)		((((PAGE) & (0x01 << (Bit)))>0)?1:0)

void        OLED_SetPixel(int iPosX, int iPosY, int iColor);
int			OLED_GetPixel(int iPosX, int iPosY);
void        OLED_Initialize(void);
void        OLED_ClearDisplay(void);
void        OLED_RefreshScreen(void);

#endif /* __INCLUDE_OLED_H__ */

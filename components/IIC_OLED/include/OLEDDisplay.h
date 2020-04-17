#ifndef  _OLEDDISPLAY_h
#define  _OLEDDISPLAY_h



#define OLED_CMD              0	   //写命令
#define OLED_DATA             1	   //写数据

#define Height                64   //定义OLED显示屏的高度
#define Width                 128  //定义OLED显示屏的宽度


// Header Values
#define JUMPTABLE_BYTES 4
#define JUMPTABLE_LSB   1
#define JUMPTABLE_SIZE  2
#define JUMPTABLE_WIDTH 3
#define JUMPTABLE_START 4

#define WIDTH_POS       0
#define HEIGHT_POS      1
#define FIRST_CHAR_POS  2
#define CHAR_NUM_POS    3


#define pgm_read_byte(addr)   (*(const unsigned char *)(addr))
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#define MAX(a, b) (((a)>(b)) ? (a) : (b))

typedef enum{
  BLACK = 0,       //字体黑色(不显示)
  WHITE = 1,       //字体白色(显示)
  INVERSE = 2      //闪烁效果
}OLEDDISPLAY_COLOR;

typedef enum{
  TEXT_ALIGN_LEFT = 0,
  TEXT_ALIGN_RIGHT = 1,
  TEXT_ALIGN_CENTER = 2,
  TEXT_ALIGN_CENTER_BOTH = 3
}OLEDDISPLAY_TEXT_ALIGNMENT;


/*-----------------OLED端口定义----------------*/  					   	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_SetPixel(uint8_t x, uint8_t y);
void OLED_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void OLED_DrawHorizontalLine(int16_t x, int16_t y, int16_t length);
void OLED_DrawVerticalLine(int16_t x, int16_t y, int16_t length);
void OLED_DrawRect(int16_t x, int16_t y, int16_t width, int16_t height);
void OLED_FillRect(int16_t xMove, int16_t yMove, int16_t width, int16_t height);
void OLED_DrawCircle(int16_t x0, int16_t y0, int16_t radius);
void OLED_DrawCircleQuads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads);
void OLED_FillCircle(int16_t x0, int16_t y0, int16_t radius);
void OLED_DrawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress);
void OLED_DrawXbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm);
void OLED_SetContrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect);
void OLED_SetBrightness(uint8_t brightness);
void OLED_SetFont(const uint8_t *fontData);
void OLED_SetTextAlignment(OLEDDISPLAY_TEXT_ALIGNMENT TextAlignment);
void OLED_SetColor(OLEDDISPLAY_COLOR Color);
void OLED_DrawString(int16_t xMove, int16_t yMove, char *strUser);
void OLED_DrawStringMaxWidth(int16_t xMove, int16_t yMove, uint16_t maxLineWidth, char *strUser);
void OLED_Init(void);


#endif


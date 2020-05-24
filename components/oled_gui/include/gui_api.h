#ifndef  GUI_API_h
#define  GUI_API_h

#include "gui_typedef.h"
#include "ssd1306_i2c.h"


/* Header Values */
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



/* 总行数y 总列数 x */
#define  GUIXMAX	GUI_LCM_XMAX
#define  GUIYMAX	GUI_LCM_YMAX



/* 打开显示 */  					   	    
void gui_display_on(void);
/* 熄灭显示屏 */
void gui_display_off(void);
/* 刷新显示屏中RAM的数据 */
void gui_refresh_gram(void);
/* 清除显示屏数据 */
void gui_clear_gram(void);
/* 在显示屏中点亮一个像素点 */
void gui_set_pixel(uint8_t x, uint8_t y,GuiColor Color);
/* 画一条线 */
void gui_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1,GuiColor Color);
/* 画一条水平线 */
void gui_draw_hline(int16_t x, int16_t y, int16_t length,GuiColor Color);
/* 画一条垂直线 */
void gui_draw_vline(int16_t x, int16_t y, int16_t length,GuiColor Color);
/* 画一个矩形 */
void gui_draw_rect(int16_t x, int16_t y, int16_t width, int16_t height,GuiColor Color);
/* 画一个实心矩形 */
void gui_draw_frect(int16_t xMove, int16_t yMove, int16_t width, int16_t height,GuiColor Color);
/* 画一个圆 */
void gui_draw_circle(int16_t x0, int16_t y0, int16_t radius,GuiColor Color);
/* 画一段圆弧 */
void gui_draw_circlequads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads,GuiColor Color);
/* 画一个实心圆 */
void gui_draw_fcircle(int16_t x0, int16_t y0, int16_t radius,GuiColor Color);
/*画一个进度条 */
void gui_draw_progressbar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress,GuiColor Color);
/* 画图 */
void gui_drawxbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm,GuiColor Color);
/* 设置屏幕灰度对比 */
void gui_set_contrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect);
/* 设置屏幕亮度 */
void gui_set_brightness(uint8_t brightness);
/* 设置屏幕字体*/
void gui_set_font(const uint8_t *FontData);
/* 设置字体对齐方式 */
void gui_set_text_alignment(OLEDDISPLAY_TEXT_ALIGNMENT TextAlignment);
/* 在屏幕上写一行字符串 */
void gui_draw_string(int16_t xMove, int16_t yMove, char *strUser,GuiColor Color);
/* 在屏幕上写一个较长的字符串 */
void gui_draw_lstring(int16_t xMove, int16_t yMove, uint16_t maxLineGUIXMAX, char *strUser,GuiColor Color);


/*在屏幕上添加一个窗口*/
int8_t gui_add_win(Win *pWindow);
/* 显示窗口 */
void gui_window_disp(void);
/* 删除顶层窗口 */
void gui_top_win_delete(void);
/* 获取顶层窗口 */
Win *gui_top_win_get(void);
/* 窗口初始化 */
void gui_windows_init(void);



/* 交换前景色和背景色 */
void gui_exchange_color(void);
/* 获取前景色 */
GuiColor gui_get_forecolor(void);
/* 获取背景色 */
GuiColor gui_get_backcolor(void);
/* 设置背景色 */
void gui_set_backcolor(GuiColor Color);
/* 设置前景色 */
void gui_set_forecolor(GuiColor Color);

#endif


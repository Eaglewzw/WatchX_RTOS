#ifndef _SSD1306I2C_h
#define _SSD1306I2C_h



/****************时钟线*********************/
#define OLED_SCLK_PINS  (GPIO_NUM_4)
/****************数据线*********************/
#define OLED_SDIN_PINS  (GPIO_NUM_5)


#define OLED_SCLK_Clr()    gpio_set_level(OLED_SCLK_PINS, 0)
#define OLED_SCLK_Set()    gpio_set_level(OLED_SCLK_PINS, 1)

#define OLED_SDIN_Clr()    gpio_set_level(OLED_SDIN_PINS, 0)
#define OLED_SDIN_Set()    gpio_set_level(OLED_SDIN_PINS, 1)

void OLED_WR_Byte(uint8_t dat, uint8_t cmd);

#endif  



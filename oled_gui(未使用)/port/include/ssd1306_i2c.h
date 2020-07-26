#ifndef SSD1306_I2C_h
#define SSD1306_I2C_h

#include "driver/gpio.h"

#define SSD1306_CMD              0	   //写命令
#define SSD1306_DATA             1	   //写数据

/****************时钟线**********************/
#define ssd1306_sclk_pins      (GPIO_NUM_4)
/****************数据线**********************/
#define ssd1306_sdat_pins      (GPIO_NUM_5)


#define ssd1306_sclk_clr()    gpio_set_level(ssd1306_sclk_pins, 0)
#define ssd1306_sclk_set()    gpio_set_level(ssd1306_sclk_pins, 1)

#define ssd1306_sdat_clr()    gpio_set_level(ssd1306_sdat_pins, 0)
#define ssd1306_sdat_set()    gpio_set_level(ssd1306_sdat_pins, 1)

/*写一个字节的数据*/
void ssd1306_write_byte(uint8_t dat, uint8_t cmd);
/*显示屏驱动初始化*/
void ssd1306_init(void);
#endif  



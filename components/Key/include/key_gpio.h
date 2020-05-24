#ifndef _KEYGPIO_H
#define _KEYGPIO_H

#include "driver/gpio.h"

#define SetKeyGpio                GPIO_NUM_13
#define UpKeyGpio                 GPIO_NUM_12
#define DownKeyGpio               GPIO_NUM_14
#define BackKeyGpio               GPIO_NUM_0


#define  SetKeyLevel              gpio_get_level(SetKeyGpio) 
#define  UpKeyLevel               gpio_get_level(UpKeyGpio) 
#define  DownKeyLevel             gpio_get_level(DownKeyGpio) 
#define  BackKeyLevel             gpio_get_level(BackKeyGpio) 


/* 按键引脚初始化 */
void key_gpio_init(void);

#endif
#include "KeyGpio.h"



/**
  * @brief	: 初始化按键GPIO引脚
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */
void KeyGpio_Init()
{
    /*************************************
    *    set按键   ----->  GPIO13(下拉)  *
    *    UP按键    ----->  GPIO12(上拉)  *
    *    DOWN按键  ----->  GPIO14(上拉)  *
    *    Back按键  ----->  GPIO 0(上拉)  *
    **************************************/
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;//输入模式
    io_conf.pin_bit_mask = (1ULL<<SetKeyGpio);
    io_conf.pull_down_en = 1;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<UpKeyGpio)| (1ULL<<DownKeyGpio)|(1ULL<<BackKeyGpio);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
}




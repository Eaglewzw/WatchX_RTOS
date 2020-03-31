#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_task_wdt.h"
#include "driver/hw_timer.h"
#include "OLED_I2C.h"
#include "KEY.h"

static const char *TAG = "Test";

void hw_timer_callback(void *arg);


void app_main(void)
{
    int KeyCode=0;

    hw_timer_init(hw_timer_callback, NULL);
   
    hw_timer_alarm_us(10000, true);
   
    hw_timer_deinit();

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL<<GPIO_NUM_16);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    gpio_set_level(GPIO_NUM_16, 1);


    OLED_Init();
    Key_Init();
    hw_timer_init(hw_timer_callback,NULL);
    hw_timer_alarm_us(10000, true);  //每隔10ms进行一次按键扫描

    for(;;) 
    {
        /*KeyCode = Key_Fifo_Get();
        ESP_LOGI(TAG,"KeyCode:%d \n",KeyCode);
        printf("This is MAIN Task! \n");
        vTaskDelay(500/portTICK_RATE_MS);//释放CPU资源
        gpio_set_level(GPIO_NUM_16, 1);
        vTaskDelay(500/portTICK_RATE_MS);//释放CPU资源*/
    }
    vTaskStartScheduler();//启动任务调度

}


void hw_timer_callback(void *arg)
{
    static int state = 0;
    //每隔10ms进行一次按键扫描，并将按键情况写入FIFO
    Key_Scan();
}




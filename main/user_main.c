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
#include "OLEDDisplay.h"
#include "KeyFifo.h"
#include "OLEDImage.h"

static const char *TAG = "Test";

void hw_timer_callback(void *arg);


void app_main(void)
{
    uint8_t KeyCode=0;
    char *buffer;
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
        KeyCode = Key_Fifo_Get();
        
        OLED_DrawXbm(10, 10, 40, 40, Image_Test);
        OLED_DrawXbm(20, 20, 40, 40, Image_Test1);

        ESP_LOGI(TAG,"KeyCode:%d \n",KeyCode);
        printf("This is MAIN Task! \n");
        gpio_set_level(GPIO_NUM_16, 0);
        vTaskDelay(500/portTICK_RATE_MS);//释放CPU资源
        gpio_set_level(GPIO_NUM_16, 1);
        vTaskDelay(500/portTICK_RATE_MS);//释放CPU资源*/
    }
    vTaskStartScheduler();//启动任务调度

}



void hw_timer_callback(void *arg)
{
    static int cnt = 0;
    cnt++;
    //每隔10ms进行一次按键扫描，并将按键情况写入FIFO
    Key_Scan();
    if(cnt == 100)
    {
        OLED_Refresh_Gram();
        cnt = 0;
    }

}








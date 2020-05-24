#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_task_wdt.h"
#include "driver/hw_timer.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "tcpip_adapter.h"
#include "esp_smartconfig.h"
#include "smartconfig_ack.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "key_fifo.h"
#include "gui_api.h"

static EventGroupHandle_t wifi_event_group;
static const char *TAG = "Test";


#define WIFI_CONNECTED_BIT    BIT0   //wifi连接成标志功
#define WIFI_FAIL_BIT         BIT1   //wifi连接失败标志
#define WIFI_MODE_SWITCH_BIT  BIT2   //是否智能联网模式
#define ESPTOUCH_DONE_BIT     BIT3   //智能配网完成

#define EXAMPLE_ESP_MAXIMUM_RETRY  5 //最大尝试次数


static void smartconfig_task(void * parm);
static void event_handle(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data);
static void sc_callback(smartconfig_status_t status, void *pdata);
static void WatchX_System_Init(void);
void hw_timer_callback(void *arg);




void app_main(void)
{
    uint8_t KeyCode=0;
    WatchX_System_Init();
    for(; ;) 
    {
        gui_draw_string(0, 0, "agshdejrktly;u", WHITE);
        gpio_set_level(GPIO_NUM_16, 0);
        vTaskDelay(500/portTICK_RATE_MS);//释放CPU资源
        gpio_set_level(GPIO_NUM_16, 1);
        vTaskDelay(500/portTICK_RATE_MS);//释放CPU资源*/
        KeyCode = key_fifo_get();
        ESP_LOGI(TAG,"KeyCode:%d \n",KeyCode);
        printf("This is MAIN Task! \n");
        
    }
    vTaskStartScheduler();//启动任务调度

}



void WatchX_System_Init(void)
{

    gpio_config_t io_conf;  
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL<<GPIO_NUM_16);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);           /* 震动模块管脚初始化 */
    gpio_set_level(GPIO_NUM_16, 1);


    key_init();                      /* 按键初始化 */
    ssd1306_init();                  /* 显示屏驱动初始化 */
    gui_windows_init();
    gui_clear_gram();

    ESP_ERROR_CHECK(nvs_flash_init() );  /* 初始化非易失性存储库 (NVS) */
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());/* 创建默认事件循环 */
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();/* 初始化WiFi */
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );


    wifi_event_group = xEventGroupCreate();/* 创建事件组 */
    wifi_config_t wifi_info; /*获取存储的WiFi信息*/
    wifi_interface_t wifi_interface=ESP_IF_WIFI_STA;/* 获取存储wifi的模式,此处需要赋值初始化 */
    uint16_t wifi_scan_number=20;/*扫描最大ap数*/
    uint16_t ap_count = 0;
    wifi_ap_record_t ap_info[20];
    memset(ap_info, 0, sizeof(ap_info));

    esp_wifi_get_config(wifi_interface, &wifi_info);/*获取存储的WiFi信息*/

    ESP_LOGI(TAG, "LAST SSID \t\t%s\n", wifi_info.sta.ssid);
    ESP_LOGI(TAG, "LAST PSK  \t\t%s\n", wifi_info.sta.password);
    //ESP_LOGI(TAG, "LAST MODE \t\t%d\n", wifi_interface);


    /* 将事件处理程序注册到系统默认事件循环，分别是WiFi事件和IP地址事件 */
    ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handle, NULL) );
    ESP_ERROR_CHECK( esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &event_handle, NULL) );
    printf("esp_event_handler_register  \n");
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) ); /* 设置WiFi的工作模式为 STA */


    /* 启动WiFi连接 */
    ESP_ERROR_CHECK( esp_wifi_start() );
    //ESP_ERROR_CHECK( esp_wifi_connect() );  
    printf("wifi_init_sta finished. \n");
    /*若为首次启动，wifi的ssid和password皆为空*/
    printf("wifi scan started \n");
    if(strlen((const char*)wifi_info.sta.ssid)!=0){
        printf("wifi ssid not null \n");
        ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&wifi_scan_number, ap_info));
        ESP_LOGI(TAG, "ap_count: %d \n", ap_count);
        for (int i = 0; i < ap_count;i++){
            ESP_LOGI(TAG, "scan_wifi: %s\n", ap_info[i].ssid);
            if( strcmp( (const char*) wifi_info.sta.ssid, (const char*)ap_info[i].ssid) == 0 ){
                printf("find same wifi name. \n");
                ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_info) ); 
                ESP_ERROR_CHECK( esp_wifi_start() );
                xEventGroupSetBits(wifi_event_group, WIFI_MODE_SWITCH_BIT);
                break;
            }
        }  
    }



    xTaskCreate(smartconfig_task, "smartconfig_task", 2048, NULL, 10, NULL); 

    EventBits_t bits = xEventGroupWaitBits(wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT) {
        printf("wifi connect \n");
    } else if (bits & WIFI_FAIL_BIT) {
        printf("wifi disconnect \n");
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT \n");
    }

    ESP_ERROR_CHECK( esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handle) );
    ESP_ERROR_CHECK( esp_event_handler_unregister(IP_EVENT, ESP_EVENT_ANY_ID, &event_handle) );
    hw_timer_init(hw_timer_callback, NULL);
    hw_timer_alarm_us(10000, true);  //每隔10ms进行一次按键扫描
    printf("WatchX_System_Init finished \n");

}





static void event_handle(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    static int retry_num = 0;
    system_event_sta_disconnected_t *event = (system_event_sta_disconnected_t *)event_data;

    printf("This is event_handle \n");
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_ERROR_CHECK( esp_wifi_connect() );
        
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (event->reason == WIFI_REASON_BASIC_RATE_NOT_SUPPORT) {
            /*Switch to 802.11 bgn mode */
            esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCAL_11B | WIFI_PROTOCAL_11G | WIFI_PROTOCAL_11N);
        }
        if (retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            ESP_ERROR_CHECK( esp_wifi_connect() );
            retry_num++;
            ESP_LOGI(TAG, "Wi-Fi disconnected, trying to reconnect... \n");
        } else {
            xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");

    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        printf("on_got_ip  \n");
        retry_num = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);

    }
}



static void smartconfig_task(void * parm)
{
    EventBits_t uxBits;
    EventBits_t isSmartConfig_Bits;

    isSmartConfig_Bits = xEventGroupWaitBits(wifi_event_group, WIFI_MODE_SWITCH_BIT, false, false, portMAX_DELAY); 
    if(isSmartConfig_Bits & WIFI_MODE_SWITCH_BIT) { 
        /*do nothing*/
    }else
    {
        ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH_AIRKISS) );
        ESP_ERROR_CHECK( esp_smartconfig_start(sc_callback) );
    }
    
    while(1){
         /*  不是等待所有都要置位，只要有一个满足条件就好 */
        uxBits = xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT | ESPTOUCH_DONE_BIT, true, false, portMAX_DELAY); 
        if(uxBits & WIFI_CONNECTED_BIT) {
            ESP_LOGI(TAG, "WiFi Connected to ap");
        }
        if(uxBits & ESPTOUCH_DONE_BIT) {
            ESP_LOGI(TAG, "smartconfig over");
            esp_smartconfig_stop();
            vTaskSuspend(NULL);
        }
    }
}



/**
  * @brief	: 智能连接的回调函数 
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */
static void sc_callback(smartconfig_status_t status, void *pdata)
{
    switch (status) {
        case SC_STATUS_WAIT:
            ESP_LOGI(TAG, "SC_STATUS_WAIT");
            break;
        case SC_STATUS_FIND_CHANNEL:
            ESP_LOGI(TAG, "SC_STATUS_FINDING_CHANNEL");
            break;
        case SC_STATUS_GETTING_SSID_PSWD:
            ESP_LOGI(TAG, "SC_STATUS_GETTING_SSID_PSWD");
            break;
        case SC_STATUS_LINK:
            ESP_LOGI(TAG, "SC_STATUS_LINK");
            wifi_config_t *wifi_config = pdata;
            ESP_LOGI(TAG, "SSID:%s", wifi_config->sta.ssid);
            ESP_LOGI(TAG, "PASSWORD:%s", wifi_config->sta.password);
            ESP_ERROR_CHECK( esp_wifi_disconnect() );
            ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, wifi_config) );
            ESP_ERROR_CHECK( esp_wifi_connect() );
            break;
        case SC_STATUS_LINK_OVER:
            ESP_LOGI(TAG, "SC_STATUS_LINK_OVER");
            if (pdata != NULL) {
                sc_callback_data_t *sc_callback_data = (sc_callback_data_t *)pdata;
                switch (sc_callback_data->type) {
                    case SC_ACK_TYPE_ESPTOUCH:
                        ESP_LOGI(TAG, "Phone ip: %d.%d.%d.%d", sc_callback_data->ip[0], sc_callback_data->ip[1], sc_callback_data->ip[2], sc_callback_data->ip[3]);
                        ESP_LOGI(TAG, "TYPE: ESPTOUCH");
                        break;
                    case SC_ACK_TYPE_AIRKISS:
                        ESP_LOGI(TAG, "TYPE: AIRKISS");
                        break;
                    default:
                        ESP_LOGE(TAG, "TYPE: ERROR");
                        break;
                }
            }
            xEventGroupSetBits(wifi_event_group, ESPTOUCH_DONE_BIT);
            break;
        default:
            break;
    }
}



void hw_timer_callback(void *arg)
{
    //每隔10ms进行一次按键扫描，并将按键情况写入FIFO
    static int cnt = 0;
    cnt++;
    key_scan();
    if(cnt==10)
    {
        gui_refresh_gram();
        cnt = 0;
    }
}






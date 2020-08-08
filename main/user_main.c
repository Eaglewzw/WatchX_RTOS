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
#include "OLED.h"
#include "SGUI_Basic.h"
#include "SGUI_IconResource.h"
#include "SGUI_Text.h"
#include "SGUI_FontResource.h"

static EventGroupHandle_t wifi_event_group;
static const char *TAG = "Test";


#define WIFI_CONNECTED_BIT    BIT0   
#define WIFI_FAIL_BIT         BIT1   
#define WIFI_AUTO_MODE        BIT2  
#define WIFI_SMART_MODE       BIT3   
#define ESPTOUCH_DONE_BIT     BIT4  

#define EXAMPLE_ESP_MAXIMUM_RETRY  5



SGUI_SCR_DEV     OLED_Device;//屏幕设备结构体定义


static void event_handle(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data);
static void sc_callback(smartconfig_status_t status, void *pdata);
static void WatchX_System_Init(void);
void hw_timer_callback(void *arg);




void app_main(void)
{
    uint8_t KeyCode=0;
	SGUI_RECT Area;
	SGUI_POINT Offest_Point;

	
	Area.iX = 0;
	Area.iY = 0;
	Area.iHeight = 64;
	Area.iWidth = 128;
	Offest_Point.iX = 0;
	Offest_Point.iY = 0;//向下偏移

    WatchX_System_Init();
    for(; ;) 
    {

        //SGUI_Text_DrawText(&OLED_Device, "LOVE U U", &DEFAULT_ArialMT_Plain_24, &Area, &Offest_Point, SGUI_DRAW_NORMAL);
        //Area.iY = 30;
        SGUI_Text_DrawText(&OLED_Device, "王昭武", &DEFAULT_GB2312_16X16, &Area, &Offest_Point, SGUI_DRAW_NORMAL);
        Offest_Point.iY --;
        if (Offest_Point.iY == -28)
        {
            Offest_Point.iY = 0;

        }
        OLED_RefreshScreen();
        gpio_set_level(GPIO_NUM_16, 0);
        vTaskDelay(100 / portTICK_RATE_MS);
        gpio_set_level(GPIO_NUM_16, 1);
        vTaskDelay(100 / portTICK_RATE_MS);
        KeyCode = key_fifo_get();
        ESP_LOGI(TAG,"KeyCode:%d \n",KeyCode);
        printf("This is MAIN Task! \n");
        
        
    }
    vTaskStartScheduler();

}



void WatchX_System_Init(void)
{

    uint8_t i = 0, j = 0;
    SGUI_RECT Logo_Icon_Area;  //开机界面图标区域
	SGUI_POINT Logo_Icon_Offest; //

    int wifi_connect_mode = 0;
    gpio_config_t io_conf;  
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL<<GPIO_NUM_16);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);                                
    gpio_set_level(GPIO_NUM_16, 1);


    key_init();                                                             
    OLED_Initialize();
   
	SGUI_SystemIF_MemorySet(&OLED_Device, 0x00, sizeof(OLED_Device));
	
    // 初始化显示屏尺寸大小
	OLED_Device.stSize.iWidth = 128;           
	OLED_Device.stSize.iHeight = 64;

	OLED_Device.fnSetPixel = OLED_SetPixel; 	// Initialize interface object. 
	OLED_Device.fnGetPixel = OLED_GetPixel;
	OLED_Device.fnClear = OLED_ClearDisplay;
	OLED_Device.fnSyncBuffer = OLED_RefreshScreen;
	
	Logo_Icon_Area.iX = 0;  
    Logo_Icon_Area.iY = 0;
    Logo_Icon_Area.iHeight = 64;
    Logo_Icon_Area.iWidth = 128;
	Logo_Icon_Offest.iX = 0;
	Logo_Icon_Offest.iY = 0;
  
    SGUI_Basic_DrawBitMap(&OLED_Device, &Logo_Icon_Area, &Logo_Icon_Offest, &LOT_WiFi_LOGO, SGUI_DRAW_NORMAL);//显示开机Logo图标
    //刷新屏幕
    OLED_RefreshScreen(); 

    //延迟一段时间
    for (j=0; j<2; j++)
    {
        for (i=0; i<200; i++)
        {
            os_delay_us(50000);//5ms
        }
    }
    SGUI_Basic_ClearScreen(&OLED_Device);


    ESP_ERROR_CHECK(nvs_flash_init() );                    
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());      
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();    
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

    ESP_ERROR_CHECK( esp_wifi_start() ); 
   
    wifi_event_group = xEventGroupCreate();              
    wifi_config_t wifi_info;                        
    wifi_interface_t wifi_interface=ESP_IF_WIFI_STA;      
    uint16_t wifi_scan_number=20;                        
    uint16_t ap_count = 0;
    wifi_ap_record_t ap_info[20];
    
    memset(ap_info, 0, sizeof(ap_info));
    
    esp_wifi_get_config(wifi_interface, &wifi_info);      
    ESP_LOGI(TAG, "LAST SSID \t\t%s\n", wifi_info.sta.ssid);
    ESP_LOGI(TAG, "LAST PSK  \t\t%s\n", wifi_info.sta.password);
    ESP_LOGI(TAG, "LAST MODE \t\t%d\n", wifi_interface);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start() );               

 
    printf("wifi_init_sta finished. \n");
    printf("wifi scan started \n");
    
    ESP_ERROR_CHECK( esp_wifi_scan_start(NULL, true) );
    ESP_ERROR_CHECK( esp_wifi_scan_get_ap_num(&ap_count) );
    ESP_ERROR_CHECK( esp_wifi_scan_get_ap_records(&wifi_scan_number, ap_info) );
    ESP_LOGI(TAG, "ap_count: %d \n", ap_count);
  

    
    if ( strlen( (const char*)wifi_info.sta.ssid) != 0 ){
        printf("wifi ssid not null \n");
        for (int i=0; i<ap_count; i++){
            ESP_LOGI(TAG, "scan_wifi: %s\n", ap_info[i].ssid);
            if ( strcmp( (const char*) wifi_info.sta.ssid, (const char*)ap_info[i].ssid) == 0 ){
                printf("find same wifi name. \n");
                ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_info) ); 
                ESP_ERROR_CHECK( esp_wifi_connect() );
                wifi_connect_mode = 1;
                break;
            }
        }  
    }

    if (wifi_connect_mode){
        xEventGroupSetBits(wifi_event_group, WIFI_AUTO_MODE);
    }else{
        ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH_AIRKISS) );
        ESP_ERROR_CHECK( esp_esptouch_set_timeout(250) );
        ESP_ERROR_CHECK( esp_smartconfig_fast_mode(true) );
        ESP_ERROR_CHECK( esp_smartconfig_start(sc_callback) );
        xEventGroupSetBits(wifi_event_group, WIFI_SMART_MODE);
    }
  
    ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handle, NULL) );
    ESP_ERROR_CHECK( esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &event_handle, NULL) );
    printf("esp_event_handler_register  \n");

    
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
    hw_timer_alarm_us(10000, true); 
    printf("WatchX_System_Init finished \n");
    SGUI_Basic_ClearScreen(&OLED_Device);

}


static void event_handle(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    static int retry_num = 0;
    system_event_sta_disconnected_t *event = (system_event_sta_disconnected_t *)event_data;

    printf("This is event_handle \n");
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        EventBits_t isSmartConfig_Bits;
        isSmartConfig_Bits = xEventGroupWaitBits(wifi_event_group, WIFI_AUTO_MODE | WIFI_SMART_MODE,  pdFALSE, pdFALSE, portMAX_DELAY); 
        if(isSmartConfig_Bits & WIFI_SMART_MODE) { 
            if (event->reason == WIFI_REASON_BASIC_RATE_NOT_SUPPORT) {
                /*Switch to 802.11 bgn mode */
                esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCAL_11B | WIFI_PROTOCAL_11G | WIFI_PROTOCAL_11N);
            }
        } else if(isSmartConfig_Bits & WIFI_AUTO_MODE){
            if (retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
                ESP_ERROR_CHECK( esp_wifi_connect() );
                retry_num++;
                ESP_LOGI(TAG, "Wi-Fi disconnected, trying to reconnect... \n");
            }else{
                xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
            }
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        printf("on_got_ip  \n");
        retry_num = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);

    }
}





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

    key_scan();

}






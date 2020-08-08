#ifndef KEY_FIFI_H
#define KEY_FIFO_H



#define KEY_COUNT           4       // 按键个数  
#define KEY_FIFO_SIZE       10      // 按键FIFO大小  
#define KEY_FILTER_TIME     5       // 按键滤波时间50ms(单位时间为10ms), 只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件  
#define KEY_LONG_TIME       0       // 长按时间 0:表示不检测长按键; 其他:检测长按键的时间  
#define KEY_REPEAT_SPEED    0       // 长按键连发速度,0:表示不支持连发,上报长按事件;其他:连发按下  

//定义按键ID
typedef enum
{ 
    SetKey =0 ,   //设置键 
    UpKey     ,   //Up键
    DownKey   ,   //Down键
    BackKey   ,  //返回键
}Key_ID;

//按键各种状态定义状态
typedef enum  
{  
    Key_None = 0,              /* 0 表示按键事件 */  

    SetKey_Down,               /* 1 设置键按下 */ 
    SetKey_Up,                 /* 2 设置键弹起 */  
    SetKey_Long,               /* 3 设置键长按 */  

    UpKey_Down,                /* 4 Up键按下 */ 
    UpKey_Up,                  /* 5 Up键弹起 */  
    UpKey_Long,                /* 6 Up键长按 */  

    DownKey_Down,              /* 7 Down键按下 */ 
    DownKey_Up,                /* 8 Down键弹起 */  
    DownKey_Long,              /* 9 Down键长按 */  

    BackKey_Down,              /* 10 Back键按下 */ 
    BackKey_Up,                /* 11 Back键弹起 */  
    BackKey_Long,              /* 12 Back键长按 */      

}KeyPressType;  


typedef struct  
{  

    /* 下面是一个函数指针，指向判断按键手否按下的函数 */  
    uint8_t (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */  

    uint8_t  Count;         /* 滤波器计数器 */  

    uint8_t  State;         /* 按键当前状态（按下还是弹起） */  

    uint16_t LongCount;     /* 长按计数器 */  

    uint16_t LongTime;      /* 按键按下持续时间, 0表示不检测长按 */  

    uint8_t  RepeatSpeed;   /* 连续按键周期 */  

    uint8_t  RepeatCount;   /* 连续按键计数器 */  

}NewKey;  



// 定义一个按键FIFO变量
typedef struct  
{  
    uint8_t Buf[KEY_FIFO_SIZE];     /*  键值缓冲区   */  
    uint8_t Read;                   /*  缓冲区读指针 */  
    uint8_t Write;                  /*  缓冲区写指针 */  

}KeyFifo;

void key_init(void);
void key_fifo_init(void);
void key_fifo_clear(void);
uint8_t key_fifo_get(void);
uint8_t key_get_state(Key_ID ucKeyID);
void ket_set_param(uint8_t ucKeyID, uint16_t LongTime, uint8_t RepeatSpeed);
void key_scan(void);
void key_fifo_put(uint8_t KeyCode);  
void key_detect(uint8_t i);  
#endif
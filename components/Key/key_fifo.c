#include "key_gpio.h"
#include "key_fifo.h"


static NewKey Button[KEY_COUNT];//定义四个按键
static KeyFifo ButtonFifo;

static uint8_t IsSetKeyDown(void)  {if (SetKeyLevel == 1) return 1;else return 0;}
static uint8_t IsUpKeyDown(void)   {if (UpKeyLevel == 0) return 1;else return 0;}
static uint8_t IsDownKeyDown(void) {if (DownKeyLevel == 0) return 1;else return 0;}
static uint8_t IsBackKeyDown(void) {if (BackKeyLevel == 0) return 1;else return 0;}



/**
  * @brief	: 初始化按键GPIO引脚、按键FIFO的值
  * @note	  : 无  
  * @param 	: 无
  * @retval	: 无
  */
void key_init(void)
{
    key_gpio_init();
    key_fifo_init();
}




void key_fifo_init(void)  
{  

    uint8_t i;  
    /* 对按键FIFO读写指针清零 */  
    ButtonFifo.Read = 0;  
    ButtonFifo.Write = 0;  

    /* 给每个按键结构体成员变量赋一组缺省值 */  
    for (i = 0; i < KEY_COUNT; i++)  
    {  
        Button[i].LongTime = KEY_LONG_TIME;         /* 长按时间 0 表示不检测长按键事件 */  
        Button[i].Count = KEY_FILTER_TIME / 2;      /* 计数器设置为滤波时间的一半 */  
        Button[i].State = 0;                        /* 按键缺省状态，0为未按下 */             
        Button[i].RepeatSpeed = KEY_REPEAT_SPEED;   /* 按键连发的速度，0表示不支持连发 */  
        Button[i].RepeatCount = 0;                  /* 连发计数器 */  

    }  

    /* 判断按键按下的函数 */  
    Button[0].IsKeyDownFunc = IsSetKeyDown;  
    Button[1].IsKeyDownFunc = IsUpKeyDown;  
    Button[2].IsKeyDownFunc = IsDownKeyDown;  
    Button[3].IsKeyDownFunc = IsBackKeyDown;  

}  


/**
  * @brief	: 清空按键FIFO缓冲区
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */
void key_fifo_clear(void)
{
	ButtonFifo.Read = ButtonFifo.Write;
}
 
/**
  * @brief	: 从按键FIFO缓冲区读取一个键值
  * @note	: 无  
  * @param 	:
  * @retval	: 按键代码
  */
uint8_t key_fifo_get(void)
{
	uint8_t ret;
 
	if (ButtonFifo.Read == ButtonFifo.Write)
	{
		return  Key_None;
	}
	else
	{
		ret = ButtonFifo.Buf[ButtonFifo.Read];
		if (++ButtonFifo.Read >= KEY_FIFO_SIZE)
		{
			ButtonFifo.Read = 0;
		}
		return ret;
	}
}
/**
  * @brief	: 读取按键的状态
  * @note	: 无  
  * @param 	: ucKeyID : 按键ID，从0开始
  * @retval	: 1 表示按下， 0 表示未按下
  */
uint8_t key_get_state(Key_ID ucKeyID)
{
	return Button[ucKeyID].State;
}
/**
  * @brief	: 设置按键参数
  * @note	: 无  
  * @param 	: ucKeyID : 按键ID，从0开始
  *			  LongTime : 长按事件时间
  *			  RepeatSpeed : 连发速度
  * @retval	: 无
  */
void key_set_param(uint8_t ucKeyID, uint16_t LongTime, uint8_t  RepeatSpeed)
{
	Button[ucKeyID].LongTime = LongTime;	     	 /* 长按时间 0 表示不检测长按键事件 */
	Button[ucKeyID].RepeatSpeed = RepeatSpeed;	 /* 长按键连发的速度，0表示不支持连发 */
	Button[ucKeyID].RepeatCount = 0;			       /* 连发计数器 */
}
 
/**
  * @brief	: 扫描所有按键。非阻塞，被周期性的调用（如systick中断）
  * @note	  : 无  
  * @param 	: 无
  * @retval	: 无
  */
void key_scan(void)
{
	uint8_t i;
 
	for (i = 0; i < KEY_COUNT; i++)
	{
		key_detect(i);
	}
}


/**
  * @brief	: 将1个键值压入按键FIFO缓冲区
  * @note	: 无  
  * @param 	: KeyCode : 按键代码
  * @retval	: 无
  */
void key_fifo_put(uint8_t KeyCode)
{
	ButtonFifo.Buf[ButtonFifo.Write] = KeyCode;
 
	if (++ButtonFifo.Write  >= KEY_FIFO_SIZE)
	{
		ButtonFifo.Write = 0;
	}
}
/**
  * @brief	: 检测一个按键。非阻塞状态，必须被周期性的调用
  * @note	: 无  
  * @param 	: 按键数
  * @retval	: 无
  */
void key_detect(uint8_t i)
{
	NewKey *pBtn;
 
	pBtn = &Button[i];
	if (pBtn->IsKeyDownFunc())
	{// 按键按下
		if (pBtn->Count < KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count < 2 * KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;
 
				/* 发送按钮按下的消息(此处和枚举类型数值要相同) */
				key_fifo_put((uint8_t)(3 * i + 1));
			}
      //长按情况
			if (pBtn->LongTime > 0)
			{
                if (pBtn->LongCount < pBtn->LongTime)
                {
                    /* 发送按钮持续按下的消息 */
                    if (++pBtn->LongCount == pBtn->LongTime)
                    {
                        if (pBtn->RepeatSpeed > 0)
                        {
                            pBtn->LongCount = 0;
                            
                            if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
                            {
                                pBtn->RepeatCount = 0;
                                /* 常按键后，每隔10ms发送1个按键 */
                                key_fifo_put((uint8_t)(3 * i + 1));
                            }          
                        }
                        else
                        {
                            /* 键值放入按键FIFO */
                            key_fifo_put((uint8_t)(3 * i + 3));
                        }
                    }
                }
			}
		}
	}
	else
	{// 按键抬起
		if(pBtn->Count > KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;
 
				/* 发送按钮弹起的消息 */
				key_fifo_put((uint8_t)(3 * i + 2));
			}
		}
		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}


#ifndef GUI_TYPEDEF_H
#define	GUI_TYPEDEF_H

#include <stdint.h>
#include "gui_config.h"

#ifndef  NULL
  #define  NULL 0
#endif


typedef uint8_t GuiColor;

enum
{
  BLACK   = 0,    //字体黑色(不显示)
  WHITE   = 1,    //字体白色(显示)
  INVERSE = 2     //闪烁效果
};



/* 窗口定义 */
typedef struct{
    uint8_t                          x;
    uint8_t                          y;
    uint8_t                       wide;
    uint8_t                      hight;
    const char                  *title;    // 定义标题栏指针(NULL为不显示)
    void (*WindowFunction)(void *param);    // 窗口对应的服务程序
    void                       * param;    //参数
}Win;

/* 窗口管理 */
struct GuiWinManage{
    uint8_t pWin;                      //窗口数
    Win *winStack[GUIWINMANAGE_NUM];	 //窗口堆栈(指针数组)
};



typedef enum{
  TEXT_ALIGN_LEFT = 0,
  TEXT_ALIGN_RIGHT = 1,
  TEXT_ALIGN_CENTER = 2,
  TEXT_ALIGN_CENTER_BOTH = 3
}OLEDDISPLAY_TEXT_ALIGNMENT;






#endif /* GUITYPEDEF_H */

/* END */
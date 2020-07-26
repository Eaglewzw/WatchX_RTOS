
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



/********OLED对象*************/
typedef strcut {

  int fb_w;							     /* width of FrameBuffer  */
  int fb_h;							     /* height of FrameBuffer */
  uint8_t* fbmem;						 /* FrameBuffer 			 */
  int  IsCited;              /* point to another one? */
}oled_config_t;



typedef struct{
	int m_nRange;		// 移动范围
	int m_nSize;		// 中间按钮的大小
	int m_nPos;			// 当前位置

  int m_nStatus;		// 0：不显示；1：显示
	int m_nMode;		// 1：垂直滚动条；2：水平滚动条
	int m_x;
	int m_y;
	int m_w;
	int m_h;			// 大小位置(滚动条的宽度强制设为13)

}scrollbar_config_t;


/* 窗口定义 */
typedef struct{
    uint8_t                           x;
    uint8_t                           y;
    uint8_t                        wide;
    uint8_t                       hight;
    const char*                   title;     // 定义标题栏指针(NULL为不显示)
    scrollbar_config_t*     v_scrollbar;     // 纵向滚动条
	  scrollbar_config_t*     h_scrollbar;     // 横向滚动条
    void*                         param;     //参数
}win_config_t;







/* 窗口管理 */
struct GuiWinManage{
    uint8_t pWin;                      //窗口数
    win_config_t *winStack[GUIWINMANAGE_NUM];	 //窗口堆栈(指针数组)
};



typedef enum{
  TEXT_ALIGN_LEFT = 0,
  TEXT_ALIGN_RIGHT = 1,
  TEXT_ALIGN_CENTER = 2,
  TEXT_ALIGN_CENTER_BOTH = 3
}OLEDDISPLAY_TEXT_ALIGNMENT;






#endif /* GUITYPEDEF_H */

/* END */
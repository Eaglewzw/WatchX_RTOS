#include "gui_api.h"


void gui_scrollBar_init(scrollbar_config_t* ScrollBar)
{
	ScrollBar->m_nStatus  = 0;		// 0：不显示；1：显示
	ScrollBar->m_nMode	  = 0;		// 1：垂直滚动条；2：水平滚动条
	ScrollBar->m_x		  = 0;
	ScrollBar->m_y		  = 0;
	ScrollBar->m_w		  = 0;
	ScrollBar->m_h		  = 0;		// 位置
	ScrollBar->m_nRange   = 2;		// 移动范围
	ScrollBar->m_nSize    = 1;		// 中间按钮的大小
	ScrollBar->m_nPos	  = 0;		// 当前位置

}


// 创建滚动条（应指定水平还是垂直）
int gui_scrollbar_create (scrollbar_config_t* ScrollBar, int nMode, int x, int y, int w, int h, int nRange, int nSize, int nPos)
{
	ScrollBar->m_x  = x;
	ScrollBar->m_y  = y;

	if (ScrollBar->nMode == 1)	// 垂直滚动条
	{
		ScrollBar->m_w = 13;
		ScrollBar->m_h = h;
		if (ScrollBar->m_h < 20){
			ScrollBar->m_h = 20;
		}	
	}
	else if (ScrollBar->nMode == 2)
	{
		ScrollBar->m_w = w;
		ScrollBar->m_h = 13;
		if (ScrollBar->m_w < 20){
			ScrollBar->m_w = 20;
		}
			
	}
	else
	{
		return FALSE;
	}

	ScrollBar->m_nStatus = 1;
	ScrollBar->m_nMode	  = nMode;

	if (! SetRange (ScrollBar->nRange))
		return FALSE;

	if (! SetSize (ScrollBar->nSize))
		return FALSE;

	if (! SetPos (ScrollBar->nPos))
		return FALSE;

	return TRUE;
}



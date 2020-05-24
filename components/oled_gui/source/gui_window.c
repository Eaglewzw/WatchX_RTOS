/**
  * @file      gui_config.h
  * @author    Eagle
  * @version   V1.0.0
  * @date      2020/04/17
  * @brief     窗口管理
  */

#include "gui_api.h"

/* 窗口管理结构 */
static struct GuiWinManage winManage;

/**
  *@brief : 绘制窗口
  *@param : pWindow 窗口指针
  *@retval: None
  */
void gui_draw_window(Win *pWindow)
{
	GuiColor forecolor,backcolor; 

	forecolor = gui_get_forecolor();
	backcolor=  gui_get_backcolor();

	if(pWindow->x + pWindow->wide - 1 > GUIXMAX || pWindow->y + pWindow->hight - 1 > GUIYMAX ||pWindow->x < 0 || pWindow->y < 0 || pWindow->wide == 0 || pWindow->hight == 0)
	{
		   return;
	}
	//将内部填充黑色
	gui_draw_frect(pWindow->x, pWindow->y, pWindow->wide , pWindow->hight , backcolor);
	gui_draw_rect(pWindow->x, pWindow->y,  pWindow->wide , pWindow->hight , forecolor);
	if(pWindow->title != NULL){
		gui_draw_hline(pWindow->x, pWindow->y+15 ,pWindow->x + pWindow->wide, forecolor);
		gui_draw_string(pWindow->x + 2, pWindow->y + 2,pWindow->title,WHITE);
	}
	gui_refresh_gram();
}

/**
  *@brief :  添加窗口
  *@param :  pWindow 窗口指针
  *@retval: 0 成功 -1 失败
  */
int8_t gui_add_win(Win *pWindow)
{
	gui_draw_window(pWindow);
	if(winManage.pWin >= GUIWINMANAGE_NUM){
		return -1;
	}
	winManage.winStack[winManage.pWin] = pWindow;
	winManage.pWin ++;
	return 0;
}

/**
  *@brief:  执行顶层窗口
  *@param:  None
  *@retval: None
  */
void gui_window_disp(void)
{
	if(winManage.pWin == 0 || winManage.pWin > GUIWINMANAGE_NUM){
		return;
	}
	Win *pThis = winManage.winStack[winManage.pWin - 1];
	pThis->WindowFunction(pThis->param);
}

/**
  *@brief  删除当前窗口
  *@param  None
  *@retval None
  */
void gui_top_win_delete(void)
{
	if(winManage.pWin <= 1 || winManage.pWin > GUIWINMANAGE_NUM){
		return;
	}
	winManage.pWin --;
}

/**
  *@brief:  获取顶层窗口
  *@param:  None
  *@retval: 顶层窗口
  */
Win *gui_top_win_get(void)
{
	Win *pTopWin = NULL;
	
	if(winManage.pWin >= 1){
		pTopWin = winManage.winStack[winManage.pWin - 1];
	}
	return pTopWin;
}

void gui_windows_init(void)
{
	winManage.pWin = 0;
}
/* END */
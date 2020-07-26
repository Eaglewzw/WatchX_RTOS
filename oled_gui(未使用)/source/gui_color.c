/**
  * @file      gui_config.h
  * @author    Eagle
  * @version   V1.0.0
  * @date      2020/04/17
  * @brief     颜色管理
  */

#include "gui_api.h"

/* 定义前景色及背景色 */
static GuiColor forecolor = WHITE,backcolor = BLACK;

/**
  *@brief : 获取前景色
  *@param :  None
  *@retval: 返回前景色
  */
GuiColor gui_get_forecolor(void)
{
	return forecolor;
}

/**
  *@brief 设置前景色
  *@param  colour 前景色
  *@retval None
  */
void gui_set_forecolor(GuiColor Color)
{
	forecolor = Color;
}

/**
  *@brief 获取背景色
  *@param  None
  *@retval 返回背景色
  */
GuiColor gui_get_backcolor(void)
{
	return backcolor;
}
/**
  *@brief 设置背景色
  *@param  colour 背景色
  *@retval None
  */
void gui_set_backcolor(GuiColor Color)
{
	backcolor = Color;
}

/**
  *@brief 交换前景色和背景色
  *@param  None
  *@retval None
  */
void gui_exchange_color(void)
{
	GuiColor Color;
	Color = forecolor;
	forecolor = backcolor;
	backcolor = Color;
}

/* END */
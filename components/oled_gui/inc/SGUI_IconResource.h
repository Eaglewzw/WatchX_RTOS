#ifndef _INCLUDE_SGUI_RESOURCE_H_
#define _INCLUDE_SGUI_RESOURCE_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"
#include "SGUI_Config.h"
//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//


#ifdef _PER_COLUMN_TYPE_ //逐行取模下
SGUI_BMP_RESOURCE_DECLARE(LOT_WiFi_LOGO);
#endif


#ifdef _COLUMN_LINE_MODE_ //列行取模的方式下
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_ERROR_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_INFORMATION_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_QUESTION_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_WARNING_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_ERROR_24);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_INFORMATION_24);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_QUESTION_24);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_WARNING_24);
SGUI_BMP_RESOURCE_DECLARE(SGUI_MENU_ICON_MOVEUP_W5H3);
SGUI_BMP_RESOURCE_DECLARE(SGUI_MENU_ICON_MOVEDOWN_W5H3);
#endif


#endif // _INCLUDE_SGUI_RESOURCE_H_

#ifndef _INCLUDE_SIMPLE_GUI_CONFIG_H_
#define _INCLUDE_SIMPLE_GUI_CONFIG_H_

//=======================================================================//
//= Used for SimpleGUI virtual SDK.									    =//
//=======================================================================//

//= OLED显示屏取模方式.									    =//
//列行式取模方式：阴码+逆向+列行式
//逐行式取模方式：阴码+逆向+逐行式
//逐列式
//默认使用第二种方法
//=======================================================================//
//#define _COLUMN_LINE_MODE_
//#define _LINE_BY_LINE_
#define _PER_COLUMN_TYPE_


#ifdef _COLUMN_LINE_MODE_
 #define _SIMPLE_GUI_ENCODE_TEXT_SRC_		("UTF-8")
 #define _SIMPLE_GUI_ENCODE_TEXT_DEST_		("GB2312")
#endif // _SIMPLE_GUI_ENCODE_TEXT_
//#define _SIMPLE_GUI_IN_VIRTUAL_SDK_
//#define	_SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_

//=======================================================================//
//= Used for SimpleGUI interface.									    =//
//=======================================================================//
//#define _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_

//=======================================================================//

#endif // _INCLUDE_SIMPLE_GUI_CONFIG_H_

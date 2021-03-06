/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_IconResource.c										**/
/** Author: XuYulin														**/
/** Description: Simple GUI basic drawing operating interface.			**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_IconResource.h"


#ifdef _PER_COLUMN_TYPE_  //逐行模式下
SGUI_BMP_RESOURCE_DEFINE(LOT_WiFi_LOGO, 128, 64,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x3F,0x00,0x00,0x00,0x00,
0x00,0x00,0xF0,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x3F,0x00,0x00,0x00,0x00,
0x00,0xC0,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x39,0x00,0x00,0xC0,0x00,
0x00,0xC0,0x7F,0x38,0x00,0x00,0xC0,0x00,0x00,0xC0,0x0F,0x38,0x00,0x00,0xC0,0x00,
0x00,0xC0,0x01,0x38,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0xC0,0x00,
0x00,0x00,0x00,0x08,0x00,0x00,0xC0,0x00,0x00,0x00,0x80,0x07,0x00,0x00,0xC0,0x00,
0x00,0x00,0xF0,0x1F,0x00,0x00,0xC0,0x00,0x00,0x00,0xF8,0x3F,0x00,0x00,0xC0,0x00,
0x00,0x00,0xFC,0x3F,0x00,0x00,0xC0,0x00,0x00,0x00,0xFF,0x3F,0x00,0x00,0xC0,0x00,
0x00,0x00,0x7F,0x7E,0x00,0x00,0xC0,0x00,0x00,0x80,0x1F,0x78,0x00,0x00,0xC0,0x00,
0x00,0xC0,0x07,0x78,0x00,0x00,0xC0,0x00,0x00,0xC0,0x03,0x38,0x00,0x00,0xC0,0x00,
0x00,0xC0,0x03,0x3C,0x00,0x00,0x00,0x04,0x00,0xC0,0x01,0x3C,0x00,0x00,0x80,0x07,
0x00,0xE0,0x01,0x1E,0x00,0x00,0xF0,0x07,0x00,0xE0,0x83,0x1F,0x00,0x00,0xF0,0x07,
0x00,0xC0,0xFF,0x0F,0x00,0x00,0xF0,0x01,0x00,0xC0,0xFF,0x07,0x00,0x00,0x70,0x06,
0x00,0xC0,0xFF,0x03,0x00,0x00,0xF0,0x07,0x00,0x80,0xFF,0x01,0x00,0x00,0xF0,0x07,
0x00,0x00,0x7F,0x00,0x00,0x00,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x04,
0x00,0x00,0x01,0x20,0x00,0x00,0xB0,0x07,0x00,0xC0,0x01,0x3C,0x00,0x00,0xF0,0x07,
0x00,0xC0,0x81,0x3F,0x00,0x00,0xF0,0x07,0x00,0xC0,0xF1,0x3F,0x00,0x00,0xF0,0x03,
0x00,0xC0,0xFF,0x3F,0x00,0x00,0x20,0x07,0x00,0xC0,0xFF,0x1F,0x00,0x00,0xA0,0x07,
0x00,0xC0,0xFF,0x03,0x00,0x00,0xB0,0x07,0x00,0xC0,0x7F,0x00,0x00,0x00,0xB0,0x06,
0x00,0xC0,0x0F,0x00,0x00,0x00,0xB0,0x07,0x00,0xC0,0x01,0x00,0x00,0x00,0xF0,0x07,
0x00,0xC0,0x01,0x00,0x00,0x00,0xF0,0x07,0x00,0xC0,0x01,0x00,0x00,0x00,0xF0,0x01,
0x00,0xC0,0x01,0x00,0x00,0x00,0xC0,0x07,0x00,0xC0,0x01,0x00,0x00,0x00,0xE0,0x07,
0x00,0x40,0x00,0x00,0x00,0x00,0xF0,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x07,
0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x07,
0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x07,0x00,0x00,0xF8,0x3F,0x00,0x00,0xFE,0x07,
0x00,0xC0,0xFF,0x3F,0x00,0x00,0xFE,0x01,0x00,0xC0,0xFF,0x3F,0x00,0x00,0xBE,0x03,
0x00,0xC0,0xFF,0x3F,0x00,0x00,0xE6,0x07,0x00,0xC0,0xFF,0x3F,0x00,0x00,0xE0,0x07,
0x00,0xC0,0xC7,0x1F,0x00,0x00,0xF0,0x06,0x00,0x00,0xE0,0x0F,0x00,0x00,0xB0,0x06,
0x00,0x00,0xF8,0x03,0x00,0x00,0xF0,0x06,0x00,0x00,0xFE,0x00,0x00,0x00,0xF0,0x06,
0x00,0x00,0x7F,0x00,0x00,0x00,0xF0,0x00,0x00,0xC0,0xFF,0x3F,0x00,0x00,0x60,0x00,
0x00,0xC0,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x3F,0x00,0x00,0x00,0x00,
0x00,0xC0,0xFF,0x3F,0x00,0x00,0x00,0x04,0x00,0xC0,0xFF,0x3F,0x00,0x00,0x80,0x07,
0x00,0x40,0xC0,0x1F,0x00,0x00,0xF0,0x07,0x00,0x00,0xF0,0x07,0x00,0x00,0xFE,0x07,
0x00,0x00,0xFC,0x03,0x00,0x00,0xFE,0x07,0x00,0x00,0xFF,0x00,0x00,0x00,0x7E,0x06,
0x00,0xC0,0x3F,0x00,0x00,0x00,0x36,0x07,0x00,0xC0,0x1F,0x3C,0x00,0x00,0xF0,0x47,
0x00,0xC0,0x07,0x3F,0x00,0x00,0xF0,0x63,0x00,0xC0,0x01,0x7F,0x00,0x00,0xF0,0x61,
0x00,0xC0,0xB0,0x7F,0x00,0x00,0x60,0x70,0x00,0x00,0xB8,0x7F,0x00,0x00,0xF0,0x7F,
0x00,0x00,0xB8,0x3B,0x00,0x00,0xF0,0x3F,0x00,0x00,0x9C,0x39,0x00,0x00,0xF0,0x1F,
0x00,0x00,0xDC,0x3F,0x00,0x00,0xC0,0x07,0x00,0x00,0xDC,0x3F,0x00,0x00,0xE0,0x03,
0x00,0x00,0xFC,0x3F,0x00,0x00,0xF0,0x00,0x00,0x00,0xFC,0x3F,0x00,0x00,0x70,0x00,
0x00,0x00,0xFC,0x07,0x00,0x00,0x10,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3F,0x00,0x00,0x00,0x07,
0x00,0x00,0xFC,0x7F,0x00,0x00,0xE0,0x07,0x00,0x00,0xFC,0x7F,0x00,0x00,0xFC,0x07,
0x00,0x00,0xFF,0x7F,0x00,0x00,0xFE,0x07,0x00,0x00,0xFF,0x7F,0x00,0x00,0x7E,0x06,
0x00,0x80,0xFF,0x38,0x00,0x00,0x66,0x06,0x00,0x80,0x3F,0x08,0x00,0x00,0x66,0x02,
0x00,0x80,0x3F,0x00,0x00,0x00,0x26,0x07,0x00,0x00,0x9C,0x1F,0x00,0x00,0xA6,0x07,
0x00,0x00,0xCC,0x3F,0x00,0x00,0xB0,0x07,0x00,0x00,0xE0,0x3F,0x00,0x00,0xB0,0x06,
0x00,0x00,0xF0,0x7F,0x00,0x00,0xB0,0x07,0x00,0x00,0xF8,0x7F,0x00,0x00,0xF0,0x07,
0x00,0x00,0x78,0x78,0x00,0x00,0xF0,0x07,0x00,0x00,0x3C,0x78,0x00,0x00,0xF0,0x31,
0x00,0x00,0x3C,0x38,0x00,0x00,0xC0,0x37,0x00,0x00,0x1C,0x38,0x00,0x00,0xE0,0x37,
0x00,0x00,0x3C,0x08,0x00,0x00,0xE0,0x37,0x00,0x00,0x3C,0x30,0x00,0x00,0xF0,0x3F,
0x00,0x00,0x3C,0x3E,0x00,0x00,0x30,0x3E,0x00,0x00,0xC0,0x3F,0x00,0x00,0xF0,0x1F,
0x00,0x00,0xF8,0x3F,0x00,0x00,0xF0,0x1F,0x00,0x00,0xFF,0x3F,0x00,0x00,0xF0,0x07,
0x00,0xE0,0xFF,0x07,0x00,0x00,0xF0,0x05,0x00,0xE0,0xFF,0x00,0x00,0x00,0xB0,0x07,
0x00,0xE0,0x3F,0x20,0x00,0x00,0xF0,0x07,0x00,0xE0,0x3B,0x3C,0x00,0x00,0xFE,0x07,
0x00,0x60,0xBC,0x3F,0x00,0x00,0xFE,0x01,0x00,0x00,0xFC,0x3F,0x00,0x00,0xBE,0x03,
0x00,0x00,0xFC,0x3F,0x00,0x00,0xE6,0x07,0x00,0x00,0xFC,0x0F,0x00,0x00,0xE0,0x07,
0x00,0x00,0xFC,0x03,0x00,0x00,0xF0,0x06,0x00,0x00,0x78,0x00,0x00,0x00,0xB0,0x06,
0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x06,
0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
#endif





#ifdef _COLUMN_LINE_MODE_  //列行取模的方式下
//=======================================================================//
//= Static variable define.												=//
//=======================================================================//
SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_ERROR_16, 16, 16,
0xFF,0x01,0x01,0x19,0x39,0x71,0xE1,0xC1,0xC1,0xE1,0x71,0x39,0x19,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x98,0x9C,0x8E,0x87,0x83,0x83,0x87,0x8E,0x9C,0x98,0x80,0x80,0xFF);

SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_INFORMATION_16, 16, 16,
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0xED,0xED,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xBF,0xBF,0x80,0x80,0x80,0x80,0x80,0x80,0xFF);

SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_QUESTION_16, 16, 16,
0xFF,0x01,0x01,0x01,0x31,0x39,0x1D,0x0D,0x0D,0x9D,0xF9,0xF1,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xB6,0xB7,0x83,0x81,0x80,0x80,0x80,0x80,0xFF);

SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_WARNING_16, 16, 16,
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0xFD,0xFD,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xB7,0xB7,0x80,0x80,0x80,0x80,0x80,0x80,0xFF);

SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_ERROR_24, 24, 24,
0xFF,0x01,0x01,0x01,0x71,0xF1,0xF1,0xE1,0xC1,0x81,0x01,0x01,0x01,0x01,0x81,0xC1,0xE1,0xF1,0xF1,0x71,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x81,0xC3,0xE7,0xFF,0xFF,0x7E,0x7E,0xFF,0xFF,0xE7,0xC3,0x81,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x8E,0x8F,0x8F,0x87,0x83,0x81,0x80,0x80,0x80,0x80,0x81,0x83,0x87,0x8F,0x8F,0x8E,0x80,0x80,0x80,0xFF);

SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_INFORMATION_24, 24, 24,
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x79,0x79,0x79,0x79,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x98,0x9F,0x9F,0x9F,0x9F,0x98,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF);

SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_QUESTION_24, 24, 24,
0xFF,0x01,0x01,0x01,0x01,0x01,0xC1,0xE1,0xF1,0xF1,0x79,0x79,0x79,0x79,0xF1,0xF1,0xE1,0xC1,0x81,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x00,0xC0,0xE0,0xF0,0xF8,0x7C,0x3F,0x1F,0x0F,0x07,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x9E,0x9E,0x9E,0x9E,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF);

SGUI_BMP_RESOURCE_DEFINE(SGUI_RES_ICON_WARNING_24, 24, 24,
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xF1,0xF9,0xF9,0xF1,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x9E,0x9E,0x9E,0x9E,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF);


#endif


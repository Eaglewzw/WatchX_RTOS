#ifndef _INCLUDED_SGUI_FONT_SOURCE_H_
#define _INCLUDED_SGUI_FONT_SOURCE_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"

// Header Values
#define JUMPTABLE_BYTES 4

#define JUMPTABLE_LSB   1
#define JUMPTABLE_SIZE  2
#define JUMPTABLE_WIDTH 3
#define JUMPTABLE_START 4

#define WIDTH_POS 0
#define HEIGHT_POS 1
#define FIRST_CHAR_POS 2
#define CHAR_NUM_POS 3

#define pgm_read_byte(addr)   (*(const unsigned char *)(addr))

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
extern const SGUI_FONT_RES  DEFAULT_ArialMT_Plain_10;
extern const SGUI_FONT_RES 	DEFAULT_ArialMT_Plain_16;
extern const SGUI_FONT_RES 	DEFAULT_ArialMT_Plain_24;

#endif // _INCLUDED_SGUI_FONT_SOURCE_H_

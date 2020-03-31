#ifndef OLEDDISPLAYUI_h
#define OLEDDISPLAYUI_h

#include "OLED_I2C.h"

//动画方向
enum AnimationDirection {
    SLIDE_UP,
    SLIDE_DOWN,
    SLIDE_LEFT,
    SLIDE_RIGHT
};


//指示器位置
enum IndicatorPosition {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};


//指示器方向
enum IndicatorDirection {
  LEFT_RIGHT,
  RIGHT_LEFT
};

enum FrameState {
  IN_TRANSITION,
  FIXED
};


const uint8_t ANIMATION_activeSymbol[] = {
  0x00, 0x18, 0x3c, 0x7e, 0x7e, 0x3c, 0x18, 0x00
};

const uint8_t ANIMATION_inactiveSymbol[] = {
  0x00, 0x0, 0x0, 0x18, 0x18, 0x0, 0x0, 0x00
};



#endif
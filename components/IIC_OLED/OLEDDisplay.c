#include "driver/gpio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "SSD1306I2C.h"
#include "OLEDDisplayFonts.h"
#include "OLEDDisplay.h"


uint8_t OLED_BUFFER[Width * Height / 8];  //OLED显示屏缓冲区
const uint8_t *fontData=ArialMT_Plain_10;  //字体   
OLEDDISPLAY_COLOR   color=WHITE;       //颜色     
OLEDDISPLAY_TEXT_ALIGNMENT textAlignment=TEXT_ALIGN_LEFT; //字体对齐方式



/**
  * @brief	: 开启OLED显示   
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}


/**
  * @brief	: 关闭OLED显示   
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */  
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}	




/**
  * @brief	: 更新显存到LCD		 
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */  
void OLED_Refresh_Gram(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
      OLED_WR_Byte(OLED_BUFFER[n+i*128], OLED_DATA);
  }   
}


/**
  * @brief	: 清屏，将数据全部填入零
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */  
void OLED_Clear(void)  
{  	    
  memset(OLED_BUFFER,0x00,sizeof(OLED_BUFFER)); 
	OLED_Refresh_Gram();//更新显示
}



/**
  * @brief	: 画点 
  * @note	  : 无
  * @param 	: x:0~127  y:0~63  t:1 填充 0,清空  
  * @retval	: 无
  */  
void OLED_SetPixel(uint8_t x,uint8_t y)
{
  if (x >= 0 && x < Width && y >= 0 && y < Height) {
    switch (color) {
      case WHITE:    OLED_BUFFER[x + (y / 8)* Width ] |=  (1 << (y & 7)); break;
      case BLACK:    OLED_BUFFER[x + (y / 8)* Width ] &= ~(1 << (y & 7)); break;
      case INVERSE:  OLED_BUFFER[x + (y / 8)* Width ] ^=  (1 << (y & 7)); break;
    }
  }	    
}

/**
  * @brief	: 画一条线段
  * @note	: x的取值0-127,y的取值范围为0-64
  * @param 	: x0,y0为起始坐标，x1,y1为终点坐标  
  * @retval	: 无
  */  
void OLED_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    _swap_int16_t(x0, y0);
    _swap_int16_t(x1, y1);
  }

  if (x0 > x1) {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      OLED_SetPixel(y0, x0);
    } else {
      OLED_SetPixel(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


/**
  * @brief	: 画一个水平线
  * @note	: 无
  * @param 	: x和y为起始坐标,length为长度
  * @retval	: 无
  */  
void OLED_DrawHorizontalLine(int16_t x, int16_t y, int16_t length)
{
	int8_t i = 0;
	if (y < 0 || y >=Width) { return; }

	if (x < 0) 
	{
		length += x;
		x = 0;
	}

	if ( (x + length) >Width)
	{
		length = (Width - x);
	}

	if (length <= 0) { return; }
	for (i = 0; i < length;i++)
		OLED_SetPixel(x+i, y);
}


/**
  * @brief	: 画一个垂直线
  * @note	: 无
  * @param 	: x和y为起始坐标,length为长度
  * @retval	: 无
  */  	
void OLED_DrawVerticalLine(int16_t x, int16_t y, int16_t length) 
{
	int8_t i = 0;
	if (x < 0 || x >= Width) return;

	if (y < 0) {
		length += y;
		y = 0;
	}

	if ( (y + length) > Height) {
		length = (Height - y);
	}

	if (length <= 0) return;
	for (i = 0; i < length;i++)
		OLED_SetPixel(x, y+i);
}

/**
  * @brief	: 画一个非实心的矩形
  * @note	: 无
  * @param 	: x和y为起始坐标,width和height分别为宽度(0~127)和高度(0~64)  
  * @retval	: 无
  */  	
void OLED_DrawRect(int16_t x, int16_t y, int16_t width, int16_t height) {
	OLED_DrawHorizontalLine(x, y, width);
	OLED_DrawVerticalLine(x, y, height);
	OLED_DrawVerticalLine(x + width - 1, y, height);
	OLED_DrawHorizontalLine(x, y + height - 1, width);
}


/**
  * @brief	: 画一个实心的矩形
  * @note	: 无
  * @param 	: xMov和yMov为起始坐标,width和height分别为宽度(0~127)和高度(0~64)  
  * @retval	: 无
  */  	
void OLED_FillRect(int16_t xMove, int16_t yMove, int16_t width, int16_t height) {
	for (int16_t x = xMove; x < xMove + width; x++) {
		OLED_DrawVerticalLine(x, yMove, height);
	}
}



/**
  * @brief	: 画一个圆
  * @note	: 无
  * @param 	: x和y为起始坐标,radius为半径 
  * @retval	: 无
  */  
void OLED_DrawCircle(int16_t x0, int16_t y0, int16_t radius) {
  	int16_t x = 0, y = radius;
	int16_t dp = 1 - radius;
	do {
		if (dp < 0)
			dp = dp + (x++) * 2 + 3;
		else
			dp = dp + (x++) * 2 - (y--) * 2 + 5;

		OLED_SetPixel(x0 + x, y0 + y);     //For the 8 octants
		OLED_SetPixel(x0 - x, y0 + y);
		OLED_SetPixel(x0 + x, y0 - y);
		OLED_SetPixel(x0 - x, y0 - y);
		OLED_SetPixel(x0 + y, y0 + x);
		OLED_SetPixel(x0 - y, y0 + x);
		OLED_SetPixel(x0 + y, y0 - x);
		OLED_SetPixel(x0 - y, y0 - x);

	} while (x < y);

  OLED_SetPixel(x0 + radius, y0);
  OLED_SetPixel(x0, y0 + radius);
  OLED_SetPixel(x0 - radius, y0);
  OLED_SetPixel(x0, y0 - radius);
}


/**
  * @brief	: 画一条1/4的圆弧线
  * @note	: 无
  * @param 	: x和y为起始坐标,radius为半径，quads:选择对于的情况，共八种
  * @retval	: 无
  */  
void OLED_DrawCircleQuads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads) {
  int16_t x = 0, y = radius;
  int16_t dp = 1 - radius;
  while (x < y) {
    if (dp < 0)
      dp = dp + (x++) * 2 + 3;
    else
      dp = dp + (x++) * 2 - (y--) * 2 + 5;
    if (quads & 0x1) {
      OLED_SetPixel(x0 + x, y0 - y);
      OLED_SetPixel(x0 + y, y0 - x);
    }
    if (quads & 0x2) {
      OLED_SetPixel(x0 - y, y0 - x);
      OLED_SetPixel(x0 - x, y0 - y);
    }
    if (quads & 0x4) {
      OLED_SetPixel(x0 - y, y0 + x);
      OLED_SetPixel(x0 - x, y0 + y);
    }
    if (quads & 0x8) {
      OLED_SetPixel(x0 + x, y0 + y);
      OLED_SetPixel(x0 + y, y0 + x);
    }
  }
  if (quads & 0x1 && quads & 0x8) {
    OLED_SetPixel(x0 + radius, y0);
  }
  if (quads & 0x4 && quads & 0x8) {
    OLED_SetPixel(x0, y0 + radius);
  }
  if (quads & 0x2 && quads & 0x4) {
    OLED_SetPixel(x0 - radius, y0);
  }
  if (quads & 0x1 && quads & 0x2) {
    OLED_SetPixel(x0, y0 - radius);
  }
}

/**
  * @brief	: 画一个实心圆
  * @note	: 无
  * @param 	: x和y为起始坐标,radius为半径 
  * @retval	: 无
  */  
void OLED_FillCircle(int16_t x0, int16_t y0, int16_t radius) {
  int16_t x = 0, y = radius;
	int16_t dp = 1 - radius;
	do {
		if (dp < 0)
      dp = dp + (x++) * 2 + 3;
    else
      dp = dp + (x++) * 2 - (y--) * 2 + 5;

    OLED_DrawHorizontalLine(x0 - x, y0 - y, 2*x);
    OLED_DrawHorizontalLine(x0 - x, y0 + y, 2*x);
    OLED_DrawHorizontalLine(x0 - y, y0 - x, 2*y);
    OLED_DrawHorizontalLine(x0 - y, y0 + x, 2*y);


	} while (x < y);
  OLED_DrawHorizontalLine(x0 - radius, y0, 2 * radius);

}

/**
  * @brief	: 画一个进度条
  * @note	: 无
  * @param 	: x和y为起始坐标,width和height分别为宽度(0~127)和高度(0~64), progress为进度占比
  * @retval	: 无
  */  
void OLED_DrawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress) {
  uint16_t radius = height / 2;
  uint16_t xRadius = x + radius;
  uint16_t yRadius = y + radius;
  uint16_t doubleRadius = 2 * radius;
  uint16_t innerRadius = radius - 2;

  OLED_DrawCircleQuads(xRadius, yRadius, radius, 0b00000110);
  OLED_DrawHorizontalLine(xRadius, y, width - doubleRadius + 1);
  OLED_DrawHorizontalLine(xRadius, y + height, width - doubleRadius + 1);
  OLED_DrawCircleQuads(x + width - radius, yRadius, radius, 0b00001001);

  uint16_t maxProgressWidth = (width - doubleRadius + 1) * progress / 100;

  OLED_FillCircle(xRadius, yRadius, innerRadius);
  OLED_FillRect(xRadius + 1, y + 2, maxProgressWidth, height - 3);
  OLED_FillCircle(xRadius + maxProgressWidth, yRadius, innerRadius);
}



/**
  * @brief	: 画一幅图片
  * @note 	: 取模方式:阴码+逐行式+逆向+C51
  * @param 	: x和y为起始坐标,width和height分别为宽度(0~127)和高度(0~64), xbm为图片首地址
  * @retval	: 无
  */  
void OLED_DrawXbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm) {
  int16_t widthInXbm = (width + 7) / 8;
  uint8_t data = 0;

  for(int16_t y = 0; y < height; y++) {
    for(int16_t x = 0; x < width; x++ ) {
      if (x & 7) {
        data >>= 1; // Move a bit
      } else {  // Read new data every 8 bit
        data =pgm_read_byte(xbm + (x / 8) + y * widthInXbm);
      }
      // if there is a bit draw it
      if (data & 0x01) {
        OLED_SetPixel(xMove + x, yMove + y);
      }
    }
  }
}


/**
  * @brief	: 显示屏亮度
  * @note 	: 
  * @param 	: 
  * @retval	: 无
  */  
void OLED_SetContrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect) 
{
    OLED_WR_Byte(0xD9,OLED_CMD); //0xD9
    OLED_WR_Byte(precharge,OLED_CMD); //0xF1 default, to lower the contrast, put 1-1F
    OLED_WR_Byte(0x81,OLED_CMD);
    OLED_WR_Byte(contrast,OLED_CMD); // 0-255
    OLED_WR_Byte(0xDB,OLED_CMD); //0xDB, (additionally needed to lower the contrast)
    OLED_WR_Byte(comdetect,OLED_CMD);	//0x40 default, to lower the contrast, put 0
    OLED_WR_Byte(0xA4,OLED_CMD);
    OLED_WR_Byte(0xA6,OLED_CMD);
    OLED_WR_Byte(0xAF,OLED_CMD);
}


/**
  * @brief	: OLED显示屏亮度改变
  * @note 	: 
  * @param 	: Brightness为亮度值
  * @retval	: 无
  */  
void OLED_SetBrightness(uint8_t brightness) 
{
    uint8_t contrast = brightness;
    if (brightness < 128) {
        // Magic values to get a smooth/ step-free transition
        contrast = brightness * 1.171;
    } else {
        contrast = brightness * 1.171 - 43;
    }

    uint8_t precharge = 241;
    if (brightness == 0) {
        precharge = 0;
    }
    uint8_t comdetect = brightness / 8;
    OLED_SetContrast(contrast, precharge, comdetect);
}


/**
  * @brief	: 设置字体
  * @note 	: 放入字体首地址
  * @param 	: 
  * @retval	: 无
  */  
void OLED_SetFont(const uint8_t *FontData)
{
  fontData = FontData;
}


/**
  * @brief	: 设置字体对齐方式
  * @note 	: 
  * @param 	: 
  * @retval	: 无
  */  
void OLED_SetTextAlignment(OLEDDISPLAY_TEXT_ALIGNMENT TextAlignment) 
{
  textAlignment = TextAlignment;
}


/**
  * @brief	: 设置颜色
  * @note 	: 
  * @param 	: 
  * @retval	: 无
  */  
void OLED_SetColor(OLEDDISPLAY_COLOR   Color)
{
  color = Color;
}





char DefaultFontTableLookup(const uint8_t ch) {
    // UTF-8 to font table index converter
    // Code form http://playground.arduino.cc/Main/Utf8ascii
	static uint8_t LASTCHAR;

	if (ch < 128) { // Standard ASCII-set 0..0x7F handling
		LASTCHAR = 0;
		return ch;
	}

	uint8_t last = LASTCHAR;   // get last char
	LASTCHAR = ch;

	switch (last) {    // conversion depnding on first UTF8-character
		case 0xC2: return (uint8_t) ch;
		case 0xC3: return (uint8_t) (ch | 0xC0);
		case 0x82: if (ch == 0xAC) return (uint8_t) 0x80;    // special case Euro-symbol
	}

	return (uint8_t) 0; // otherwise: return zero, if character has to be ignored
}


void inline drawInternal(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *data, uint16_t offset, uint16_t bytesInData) 
{
  if (width < 0 || height < 0) return;
  if (yMove + height < 0 || yMove > Height)  return;
  if (xMove + width  < 0 || xMove > Width)   return;

  uint8_t  rasterHeight = 1 + ((height - 1) >> 3); // fast ceil(height / 8.0)
  int8_t   yOffset      = yMove & 7;

  bytesInData = bytesInData == 0 ? width * rasterHeight : bytesInData;

  int16_t initYMove   = yMove;
  int8_t  initYOffset = yOffset;


  for (uint16_t i = 0; i < bytesInData; i++) {

    // Reset if next horizontal drawing phase is started.
    if ( i % rasterHeight == 0) {
      yMove   = initYMove;
      yOffset = initYOffset;
    }

    uint8_t currentByte = pgm_read_byte(data + offset + i);

    int16_t xPos = xMove + (i / rasterHeight);
    int16_t yPos = ((yMove >> 3) + (i % rasterHeight)) * Width;

//    int16_t yScreenPos = yMove + yOffset;
    int16_t dataPos    = xPos  + yPos;

    if (dataPos >=  0  && dataPos < (Width * Height / 8) &&
        xPos    >=  0  && xPos    < Width ) {

      if (yOffset >= 0) {
        switch (color) {
          case WHITE:   OLED_BUFFER[dataPos] |= currentByte << yOffset; break;
          case BLACK:   OLED_BUFFER[dataPos] &= ~(currentByte << yOffset); break;
          case INVERSE: OLED_BUFFER[dataPos] ^= currentByte << yOffset; break;
        }

        if (dataPos < ((Width * Height / 8) - Width)) {
          switch (color) {
            case WHITE:   OLED_BUFFER[dataPos + Width] |= currentByte >> (8 - yOffset); break;
            case BLACK:   OLED_BUFFER[dataPos + Width] &= ~(currentByte >> (8 - yOffset)); break;
            case INVERSE: OLED_BUFFER[dataPos + Width] ^= currentByte >> (8 - yOffset); break;
          }
        }
      } else {
        // Make new offset position
        yOffset = -yOffset;

        switch (color) {
          case WHITE:   OLED_BUFFER[dataPos] |= currentByte >> yOffset; break;
          case BLACK:   OLED_BUFFER[dataPos] &= ~(currentByte >> yOffset); break;
          case INVERSE: OLED_BUFFER[dataPos] ^= currentByte >> yOffset; break;
        }

        // Prepare for next iteration by moving one block up
        yMove -= 8;

        // and setting the new yOffset
        yOffset = 8 - yOffset;
      }

    }
  }
}

uint16_t getStringWidth(const char* text, uint16_t length) 
{
  uint16_t firstChar        = pgm_read_byte(fontData + FIRST_CHAR_POS);

  uint16_t stringWidth = 0;
  uint16_t maxWidth = 0;

  while (length--) {
    stringWidth += pgm_read_byte(fontData + JUMPTABLE_START + (text[length] - firstChar) * JUMPTABLE_BYTES + JUMPTABLE_WIDTH);
    if (text[length] == 10) {
      maxWidth = MAX(maxWidth, stringWidth);
      stringWidth = 0;
    }
  }

  return MAX(maxWidth, stringWidth);
}


void drawStringInternal(int16_t xMove, int16_t yMove, char* text, uint16_t textLength, uint16_t textWidth) {
  uint8_t textHeight       = pgm_read_byte(fontData + HEIGHT_POS);
  uint8_t firstChar        = pgm_read_byte(fontData + FIRST_CHAR_POS);
  uint16_t sizeOfJumpTable = pgm_read_byte(fontData + CHAR_NUM_POS)  * JUMPTABLE_BYTES;

  uint16_t cursorX         = 0;
  uint16_t cursorY         = 0;

  switch (textAlignment) {
    case TEXT_ALIGN_CENTER_BOTH:
      yMove -= textHeight >> 1;
    // Fallthrough
    case TEXT_ALIGN_CENTER:
      xMove -= textWidth >> 1; // divide by 2
      break;
    case TEXT_ALIGN_RIGHT:
      xMove -= textWidth;
      break;
    case TEXT_ALIGN_LEFT:
      break;
  }

  // Don't draw anything if it is not on the screen.
  if (xMove + textWidth  < 0 || xMove > Width ) {return;}
  if (yMove + textHeight < 0 || yMove > Width ) {return;}

  for (uint16_t j = 0; j < textLength; j++) {
    int16_t xPos = xMove + cursorX;
    int16_t yPos = yMove + cursorY;

    uint8_t code = text[j];
    if (code >= firstChar) {
      uint8_t charCode = code - firstChar;

      // 4 Bytes per char code
      uint8_t msbJumpToChar    = pgm_read_byte( fontData + JUMPTABLE_START + charCode * JUMPTABLE_BYTES );                  // MSB \ JumpAddress
      uint8_t lsbJumpToChar    = pgm_read_byte( fontData + JUMPTABLE_START + charCode * JUMPTABLE_BYTES + JUMPTABLE_LSB);   // LSB /
      uint8_t charByteSize     = pgm_read_byte( fontData + JUMPTABLE_START + charCode * JUMPTABLE_BYTES + JUMPTABLE_SIZE);  // Size
      uint8_t currentCharWidth = pgm_read_byte( fontData + JUMPTABLE_START + charCode * JUMPTABLE_BYTES + JUMPTABLE_WIDTH); // Width

      // Test if the char is drawable
      if (!(msbJumpToChar == 255 && lsbJumpToChar == 255)) {
        // Get the position of the char data
        uint16_t charDataPosition = JUMPTABLE_START + sizeOfJumpTable + ((msbJumpToChar << 8) + lsbJumpToChar);
        drawInternal(xPos, yPos, currentCharWidth, textHeight, fontData, charDataPosition, charByteSize);
      }
      cursorX += currentCharWidth;
    }
  }
}



/**
  * @brief	: 在显示屏中显示一行字符串
  * @note	  : 注意该函数不会换行
  * @param 	: xMove和yMove为起始坐标, strUser为输入的字符串
  * @retval	: 无
  */  	
void OLED_DrawString(int16_t xMove, int16_t yMove, char *strUser) 
{
  uint16_t lineHeight = pgm_read_byte(fontData + HEIGHT_POS);
  uint16_t k = 0;
  uint16_t len = strlen(strUser) + 1;

  // Copy the string into a char array
  char* text = (char*) malloc(len * sizeof(char));
  if(!text) {
    printf("Can't allocate another char array! \n");
  }
  for (uint8_t i = 0; i < len;i++)
    text[i] = *(strUser + i);
  len--;

  for (uint16_t i=0; i < len; i++) {
    char c = DefaultFontTableLookup(text[i]);
    if (c!=0) {
      text[k++]=c;
    }
  }
  text[k]=0;

  uint16_t yOffset = 0;
  // If the string should be centered vertically too
  // we need to now how heigh the string is.
  if (textAlignment == TEXT_ALIGN_CENTER_BOTH) {
    uint16_t lb = 0;
    // Find number of linebreaks in text
    for (uint16_t i=0;text[i] != 0; i++) {
      lb += (text[i] == 10);
    }
    // Calculate center
    yOffset = (lb * lineHeight) / 2;
  }

  uint16_t line = 0;
  char* textPart = strtok(text,"\n");
  while (textPart != NULL) {
    uint16_t length = strlen(textPart);
    drawStringInternal(xMove, yMove - yOffset + (line++) * lineHeight, textPart, length, getStringWidth(textPart, length));
    textPart = strtok(NULL, "\n");
  }
  free(text);

}

/**
  * @brief	: 在显示屏中显示字符串
  * @note	  : 注意该函数可换行
  * @param 	: xMove和yMove为起始坐标, maxLineWidth为字符串个数,strUser为输入的字符串
  * @retval	: 无
  */ 	
void OLED_DrawStringMaxWidth(int16_t xMove, int16_t yMove, uint16_t maxLineWidth, char* strUser)
{
  uint16_t firstChar  = pgm_read_byte(fontData + FIRST_CHAR_POS);
  uint16_t lineHeight = pgm_read_byte(fontData + HEIGHT_POS);
  uint16_t k = 0;
  uint16_t len = strlen(strUser) + 1;

  // Copy the string into a char array
  char* text = (char*) malloc(len * sizeof(char));
  if(!text) {
    printf("Can't allocate another char array! \n");
  }
  for (uint8_t i = 0; i < len;i++)
    text[i] = *(strUser + i);
  len--;

  for (uint16_t i=0; i < len; i++) {
    char c = DefaultFontTableLookup(text[i]);
    if (c!=0) {
      text[k++]=c;
    }
  }
  text[k]=0;

  uint16_t length = strlen(text);
  uint16_t lastDrawnPos = 0;
  uint16_t lineNumber = 0;
  uint16_t strWidth = 0;

  uint16_t preferredBreakpoint = 0;
  uint16_t widthAtBreakpoint = 0;

  for (uint16_t i = 0; i < length; i++) {
    strWidth += pgm_read_byte(fontData + JUMPTABLE_START + (text[i] - firstChar) * JUMPTABLE_BYTES + JUMPTABLE_WIDTH);

    // Always try to break on a space or dash
    if (text[i] == ' ' || text[i]== '-') {
      preferredBreakpoint = i;
      widthAtBreakpoint = strWidth;
    }

    if (strWidth >= maxLineWidth) {
      if (preferredBreakpoint == 0) {
        preferredBreakpoint = i;
        widthAtBreakpoint = strWidth;
      }
      drawStringInternal(xMove, yMove + (lineNumber++) * lineHeight , &text[lastDrawnPos], preferredBreakpoint - lastDrawnPos, widthAtBreakpoint);
      lastDrawnPos = preferredBreakpoint + 1;
      // It is possible that we did not draw all letters to i so we need
      // to account for the width of the chars from `i - preferredBreakpoint`
      // by calculating the width we did not draw yet.
      strWidth = strWidth - widthAtBreakpoint;
      preferredBreakpoint = 0;
    }
  }

  // Draw last part if needed
  if (lastDrawnPos < length) {
    drawStringInternal(xMove, yMove + lineNumber * lineHeight , &text[lastDrawnPos], length - lastDrawnPos, getStringWidth(&text[lastDrawnPos], length - lastDrawnPos));
  }

  free(text);
}




/**
  * @brief	: 初始化OLED 
  * @note	: 无
  * @param 	: 无  
  * @retval	: 无
  */  			    
void OLED_Init(void)
{

	/*****************管脚初始化************************
	*             SCLK ---------------->GPIO4
	*             SDA  ---------------->GPIO5
	****************************************************
	*/
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL<<OLED_SCLK_PINS) |(1ULL<<OLED_SDIN_PINS);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);


    OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
    OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping      0xa0左右反置 0xa1正常
    OLED_WR_Byte(0xC8,OLED_CMD);//--Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00,OLED_CMD);//-not offset
    OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
    OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
    OLED_WR_Byte(0x12,OLED_CMD);
    OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
    OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
    OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
    OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
    OLED_Clear();

}  






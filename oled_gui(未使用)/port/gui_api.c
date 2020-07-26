#include "driver/gpio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "ssd1306_i2c.h"
#include "oled_fonts.h"
#include "gui_api.h"


uint8_t OLED_BUFFER[GUIXMAX *  GUIYMAX / 8];  //OLED显示屏缓冲区
const uint8_t *fontData=ArialMT_Plain_10;  //字体   
OLEDDISPLAY_TEXT_ALIGNMENT textAlignment=TEXT_ALIGN_LEFT; //字体对齐方式



/**
  * @brief	: 开启OLED显示   
  * @note	  : 无  
  * @param 	: 无
  * @retval	: 无
  */
void gui_display_on(void)
{
	ssd1306_write_byte(0X8D,SSD1306_CMD);  //SET DCDC命令
	ssd1306_write_byte(0X14,SSD1306_CMD);  //DCDC ON
	ssd1306_write_byte(0XAF,SSD1306_CMD);  //DISPLAY ON
}


/**
  * @brief	: 关闭OLED显示   
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */  
void gui_display_off(void)
{
	ssd1306_write_byte(0X8D,SSD1306_CMD);  //SET DCDC命令
	ssd1306_write_byte(0X10,SSD1306_CMD);  //DCDC OFF
	ssd1306_write_byte(0XAE,SSD1306_CMD);  //DISPLAY OFF
}	




/**
  * @brief	: 更新显存到LCD		 
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */  
void gui_refresh_gram(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		ssd1306_write_byte (0xb0+i,SSD1306_CMD);    //设置页地址（0~7）
		ssd1306_write_byte (0x00,SSD1306_CMD);      //设置显示位置—列低地址
		ssd1306_write_byte (0x10,SSD1306_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
      ssd1306_write_byte(OLED_BUFFER[n+i*128], SSD1306_DATA);
  }   
}


/**
  * @brief	: 清屏，将数据全部填入零
  * @note	: 无  
  * @param 	: 无
  * @retval	: 无
  */  
void gui_clear_gram(void) 
{  	    
  memset(OLED_BUFFER,0x00,sizeof(OLED_BUFFER)); 
	gui_refresh_gram();//更新显示
}



/**
  * @brief	: 画点 
  * @note	  : 无
  * @param 	: x:0~127  y:0~63  t:1 填充 0,清空  
  * @retval	: 无
  */  
void gui_set_pixel(uint8_t x, uint8_t y,GuiColor Color)
{
  if (x >= 0 && x < GUIXMAX && y >= 0 && y <  GUIYMAX) 
  {
    switch (Color) {
      case WHITE:    OLED_BUFFER[x + (y / 8)* GUIXMAX ] |=  (1 << (y & 7)); break;
      case BLACK:    OLED_BUFFER[x + (y / 8)* GUIXMAX ] &= ~(1 << (y & 7)); break;
      case INVERSE:  OLED_BUFFER[x + (y / 8)* GUIXMAX ] ^=  (1 << (y & 7)); break;
    }
  }
 
}


/**
  * @brief	: 获取屏幕某点的像素 
  * @note	  : 无
  * @param 	: x:0~127  y:0~63   
  * @retval	: 返回值为0或1，-1表示出错
  */  
int gui_get_pixel(uint8_t x, uint8_t y)
{
  int eColor=-1;
  if (x >= 0 && x < GUIXMAX && y >= 0 && y <  GUIYMAX) 
  {
    eColor = OLED_BUFFER[x + (y / 8) * GUIXMAX]; 

  }else{
    eColor=-1;  
  }
  return eColor;
}




/**
  * @brief	: 画一条线段
  * @note	: x的取值0-127,y的取值范围为0-64
  * @param 	: x0,y0为起始坐标，x1,y1为终点坐标  
  * @retval	: 无
  */  
void gui_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1,GuiColor Color)
 {
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
      gui_set_pixel(y0, x0,Color);
    } else {
      gui_set_pixel(x0, y0,Color);
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
void gui_draw_hline(int16_t x, int16_t y, int16_t length,GuiColor Color)
{
	int8_t i = 0;
	if (y < 0 || y >=GUIXMAX) { return; }

	if (x < 0) 
	{
		length += x;
		x = 0;
	}

	if ( (x + length) >GUIXMAX)
	{
		length = (GUIXMAX - x);
	}

	if (length <= 0) { return; }
	for (i = 0; i < length;i++)
		gui_set_pixel(x+i, y,Color);
 
}


/**
  * @brief	: 画一个垂直线
  * @note	  : 无
  * @param 	: x和y为起始坐标,length为长度
  * @retval	: 无
  */  	
void gui_draw_vline(int16_t x, int16_t y, int16_t length,GuiColor Color) 
{
	int8_t i = 0;
	if (x < 0 || x >= GUIXMAX) return;

	if (y < 0) {
		length += y;
		y = 0;
	}

	if ( (y + length) >  GUIYMAX) {
		length = ( GUIYMAX - y);
	}

	if (length <= 0) return;
	for (i = 0; i < length;i++)
		gui_set_pixel(x, y+i,Color);

}

/**
  * @brief	: 画一个非实心的矩形
  * @note	  : 无
  * @param 	: x和y为起始坐标,width和height分别为宽度(0~127)和高度(0~64)  
  * @retval	: 无
  */  	
void gui_draw_rect(int16_t x, int16_t y, int16_t width, int16_t height,GuiColor Color) {
	gui_draw_hline(x, y, width,Color);
	gui_draw_vline(x, y, height,Color);
	gui_draw_vline(x + width - 1, y, height,Color);
	gui_draw_hline(x, y + height - 1, width,Color);
 
}


/**
  * @brief	: 画一个实心的矩形
  * @note	  : 无
  * @param 	: xMov和yMov为起始坐标,width和height分别为宽度(0~127)和高度(0~64)  
  * @retval	: 无
  */  	
void gui_draw_frect(int16_t xMove, int16_t yMove, int16_t width, int16_t height,GuiColor Color) 
{
	for (int16_t x = xMove; x < xMove + width; x++) {
		gui_draw_vline(x, yMove, height,Color);
	}
  
}



/**
  * @brief	: 画一个圆
  * @note	  : 无
  * @param 	: x和y为起始坐标,radius为半径 
  * @retval	: 无
  */  
void gui_draw_circle(int16_t x0, int16_t y0, int16_t radius,GuiColor Color) 
{
  	int16_t x = 0, y = radius;
	int16_t dp = 1 - radius;
	do {
		if (dp < 0)
			dp = dp + (x++) * 2 + 3;
		else
			dp = dp + (x++) * 2 - (y--) * 2 + 5;

		gui_set_pixel(x0 + x, y0 + y,Color);     //For the 8 octants
		gui_set_pixel(x0 - x, y0 + y,Color);
		gui_set_pixel(x0 + x, y0 - y,Color);
		gui_set_pixel(x0 - x, y0 - y,Color);
		gui_set_pixel(x0 + y, y0 + x,Color);
		gui_set_pixel(x0 - y, y0 + x,Color);
		gui_set_pixel(x0 + y, y0 - x,Color);
		gui_set_pixel(x0 - y, y0 - x,Color);

	} while (x < y);

  gui_set_pixel(x0 + radius, y0, Color);
  gui_set_pixel(x0, y0 + radius, Color);
  gui_set_pixel(x0 - radius, y0, Color);
  gui_set_pixel(x0, y0 - radius, Color);
 
}


/**
  * @brief	: 画一条1/4的圆弧线
  * @note	  : 无
  * @param 	: x和y为起始坐标,radius为半径，quads:选择对于的情况，共八种
  * @retval	: 无
  */  
void gui_draw_circlequads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads,GuiColor Color) {
  int16_t x = 0, y = radius;
  int16_t dp = 1 - radius;
  while (x < y) {
    if (dp < 0)
      dp = dp + (x++) * 2 + 3;
    else
      dp = dp + (x++) * 2 - (y--) * 2 + 5;
    if (quads & 0x1) {
      gui_set_pixel(x0 + x, y0 - y, Color);
      gui_set_pixel(x0 + y, y0 - x, Color);
    }
    if (quads & 0x2) {
      gui_set_pixel(x0 - y, y0 - x, Color);
      gui_set_pixel(x0 - x, y0 - y, Color);
    }
    if (quads & 0x4) {
      gui_set_pixel(x0 - y, y0 + x, Color);
      gui_set_pixel(x0 - x, y0 + y, Color);
    }
    if (quads & 0x8) {
      gui_set_pixel(x0 + x, y0 + y, Color);
      gui_set_pixel(x0 + y, y0 + x, Color);
    }
  }
  if (quads & 0x1 && quads & 0x8) {
    gui_set_pixel(x0 + radius, y0, Color);
  }
  if (quads & 0x4 && quads & 0x8) {
    gui_set_pixel(x0, y0 + radius, Color);
  }
  if (quads & 0x2 && quads & 0x4) {
    gui_set_pixel(x0 - radius, y0, Color);
  }
  if (quads & 0x1 && quads & 0x2) {
    gui_set_pixel(x0, y0 - radius, Color);
  }
 
}

/**
  * @brief	: 画一个实心圆
  * @note	  : 无
  * @param 	: x和y为起始坐标,radius为半径 
  * @retval	: 无
  */  
void gui_draw_fcircle(int16_t x0, int16_t y0, int16_t radius,GuiColor Color) 
{
  int16_t x = 0, y = radius;
	int16_t dp = 1 - radius;
	do {
		if (dp < 0)
      dp = dp + (x++) * 2 + 3;
    else
      dp = dp + (x++) * 2 - (y--) * 2 + 5;

    gui_draw_hline(x0 - x, y0 - y, 2*x, Color);
    gui_draw_hline(x0 - x, y0 + y, 2*x, Color);
    gui_draw_hline(x0 - y, y0 - x, 2*y, Color);
    gui_draw_hline(x0 - y, y0 + x, 2*y, Color);


	} while (x < y);
  gui_draw_hline(x0 - radius, y0, 2 * radius, Color);
 

}

/**
  * @brief	: 画一个进度条
  * @note	  : 无
  * @param 	: x和y为起始坐标,width和height分别为宽度(0~127)和高度(0~64), progress为进度占比
  * @retval	: 无
  */  
void OLED_DrawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress,GuiColor Color)
{
  uint16_t radius = height / 2;
  uint16_t xRadius = x + radius;
  uint16_t yRadius = y + radius;
  uint16_t doubleRadius = 2 * radius;
  uint16_t innerRadius = radius - 2;

  gui_draw_circlequads(xRadius, yRadius, radius, 0b00000110, Color);
  gui_draw_hline(xRadius, y, width - doubleRadius + 1, Color);
  gui_draw_hline(xRadius, y + height, width - doubleRadius + 1, Color);
  gui_draw_circlequads(x + width - radius, yRadius, radius, 0b00001001, Color);

  uint16_t maxProgressGUIXMAX = (width - doubleRadius + 1) * progress / 100;

  gui_draw_fcircle(xRadius, yRadius, innerRadius, Color);
  gui_draw_frect(xRadius + 1, y + 2, maxProgressGUIXMAX, height - 3, Color);
  gui_draw_fcircle(xRadius + maxProgressGUIXMAX, yRadius, innerRadius, Color);
  
}



/**
  * @brief	: 画一幅图片
  * @note 	: 取模方式:阴码+逐行式+逆向+C51
  * @param 	: x和y为起始坐标,width和height分别为宽度(0~127)和高度(0~64), xbm为图片首地址
  * @retval	: 无
  */  
void gui_drawxbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm,GuiColor Color) 
{
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
        gui_set_pixel(xMove + x, yMove + y, Color);
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
void gui_set_contrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect)
{
    ssd1306_write_byte(0xD9,SSD1306_CMD); //0xD9
    ssd1306_write_byte(precharge,SSD1306_CMD); //0xF1 default, to lower the contrast, put 1-1F
    ssd1306_write_byte(0x81,SSD1306_CMD);
    ssd1306_write_byte(contrast,SSD1306_CMD); // 0-255
    ssd1306_write_byte(0xDB,SSD1306_CMD); //0xDB, (additionally needed to lower the contrast)
    ssd1306_write_byte(comdetect,SSD1306_CMD);	//0x40 default, to lower the contrast, put 0
    ssd1306_write_byte(0xA4,SSD1306_CMD);
    ssd1306_write_byte(0xA6,SSD1306_CMD);
    ssd1306_write_byte(0xAF,SSD1306_CMD);
}


/**
  * @brief	: OLED显示屏亮度改变
  * @note 	: 
  * @param 	: Brightness为亮度值
  * @retval	: 无
  */  
void gui_set_brightness(uint8_t brightness)
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
    gui_set_contrast(contrast, precharge, comdetect);
}


/**
  * @brief	: 设置字体
  * @note 	: 放入字体首地址
  * @param 	: 
  * @retval	: 无
  */  
void gui_set_font(const uint8_t *FontData)
{
  fontData = FontData;
}


/**
  * @brief	: 设置字体对齐方式
  * @note 	: 
  * @param 	: 
  * @retval	: 无
  */  
void gui_set_text_alignment(OLEDDISPLAY_TEXT_ALIGNMENT TextAlignment) 
{
  textAlignment = TextAlignment;
}





char DefaultFontTableLookup(const uint8_t ch) 
{
    // UTF-8 to font table index converter
    // Code form http://playground.arduino.cc/Main/Utf8ascii
	static uint8_t LASTCHAR;

	if (ch < 128) 
  { // Standard ASCII-set 0..0x7F handling
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


void inline drawInternal(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *data, uint16_t offset, uint16_t bytesInData, GuiColor Color) 
{
  if (width < 0 || height < 0) return;
  if (yMove + height < 0 || yMove >  GUIYMAX)  return;
  if (xMove + width  < 0 || xMove > GUIXMAX)   return;

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
    int16_t yPos = ((yMove >> 3) + (i % rasterHeight)) * GUIXMAX;

//    int16_t yScreenPos = yMove + yOffset;
    int16_t dataPos    = xPos  + yPos;

    if (dataPos >=  0  && dataPos < (GUIXMAX *  GUIYMAX / 8) &&
        xPos    >=  0  && xPos    < GUIXMAX ) {

      if (yOffset >= 0) {
        switch (Color) {
          case WHITE:   OLED_BUFFER[dataPos] |= currentByte << yOffset; break;
          case BLACK:   OLED_BUFFER[dataPos] &= ~(currentByte << yOffset); break;
          case INVERSE: OLED_BUFFER[dataPos] ^= currentByte << yOffset; break;
        }

        if (dataPos < ((GUIXMAX *  GUIYMAX / 8) - GUIXMAX)) {
          switch (Color) {
            case WHITE:   OLED_BUFFER[dataPos + GUIXMAX] |= currentByte >> (8 - yOffset); break;
            case BLACK:   OLED_BUFFER[dataPos + GUIXMAX] &= ~(currentByte >> (8 - yOffset)); break;
            case INVERSE: OLED_BUFFER[dataPos + GUIXMAX] ^= currentByte >> (8 - yOffset); break;
          }
        }
      } else {
        // Make new offset position
        yOffset = -yOffset;

        switch (Color) {
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


void drawStringInternal(int16_t xMove, int16_t yMove, char* text, uint16_t textLength,  uint16_t textWidth,GuiColor Color) 
{
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
  if (xMove + textWidth  < 0 || xMove > GUI_LCM_XMAX ) {return;}
  if (yMove + textHeight < 0 || yMove > GUI_LCM_XMAX ) {return;}

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
        drawInternal(xPos, yPos, currentCharWidth, textHeight, fontData, charDataPosition, charByteSize, Color);
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
void gui_draw_string(int16_t xMove, int16_t yMove, char *strUser,GuiColor Color)
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
    drawStringInternal(xMove, yMove - yOffset + (line++) * lineHeight, textPart, length, getStringWidth(textPart, length),Color);
    textPart = strtok(NULL, "\n");
  }
  free(text);

}

/**
  * @brief	: 在显示屏中显示字符串
  * @note	  : 注意该函数可换行
  * @param 	: xMove和yMove为起始坐标, maxLineGUIXMAX为字符串个数,strUser为输入的字符串
  * @retval	: 无
  */ 	
void gui_draw_lstring(int16_t xMove, int16_t yMove, uint16_t maxLineWidth, char *strUser,GuiColor Color)
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
      drawStringInternal(xMove, yMove + (lineNumber++) * lineHeight, &text[lastDrawnPos], preferredBreakpoint - lastDrawnPos, widthAtBreakpoint,Color);
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
    drawStringInternal(xMove, yMove + lineNumber * lineHeight , &text[lastDrawnPos], length - lastDrawnPos, getStringWidth(&text[lastDrawnPos], length - lastDrawnPos),Color);
  }

  free(text);
}











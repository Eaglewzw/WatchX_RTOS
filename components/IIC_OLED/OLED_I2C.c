#include "OLED_I2C.h"
#include "OLEDFONT.h"
#include "stdlib.h"
#include "math.h"


 static uint8_t OLED_GRAM[128][8];	
void IIC_Start()
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}


void IIC_Stop()
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

void IIC_Wait_Ack()
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}


void Write_IIC_Byte(uint8_t IIC_Byte)
{
	uint8_t i;
	uint8_t m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}


}

void Write_IIC_Command(uint8_t IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

void Write_IIC_Data(uint8_t IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
	IIC_Stop();
}


//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	if(cmd)
	{
   		Write_IIC_Data(dat);
	}
	else {
   		Write_IIC_Command(dat);	
	}
}





/**********************************************************
 *                        OLED顶层函数                    *
 ********************************************************** 
 */


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
			OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
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
	uint8_t i,n;	
	for(i=0;i<8;i++)
		for(n=0;n<128;n++)
			OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//更新显示
}



/**
  * @brief	: 画点 
  * @note	: 无
  * @param 	: x:0~127  y:0~63  t:1 填充 0,清空  
  * @retval	: 无
  */  
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t)
{
	uint8_t pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
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
      OLED_DrawPoint(y0, x0,White);
    } else {
      OLED_DrawPoint(x0, y0,White);
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
	if (y < 0 || y >= 128) { return; }

	if (x < 0) 
	{
		length += x;
		x = 0;
	}

	if ( (x + length) >128)
	{
		length = (128 - x);
	}

	if (length <= 0) { return; }
	for (i = 0; i < length;i++)
		OLED_DrawPoint(x+i, y, White);
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
	if (x < 0 || x >= 128) return;

	if (y < 0) {
		length += y;
		y = 0;
	}

	if ( (y + length) > 64) {
		length = (64 - y);
	}

	if (length <= 0) return;
	for (i = 0; i < length;i++)
		OLED_DrawPoint(x, y+i, White);
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

		OLED_DrawPoint(x0 + x, y0 + y,White);     //For the 8 octants
		OLED_DrawPoint(x0 - x, y0 + y,White);
		OLED_DrawPoint(x0 + x, y0 - y,White);
		OLED_DrawPoint(x0 - x, y0 - y,White);
		OLED_DrawPoint(x0 + y, y0 + x,White);
		OLED_DrawPoint(x0 - y, y0 + x,White);
		OLED_DrawPoint(x0 + y, y0 - x,White);
		OLED_DrawPoint(x0 - y, y0 - x,White);

	} while (x < y);

  OLED_DrawPoint(x0 + radius, y0,White);
  OLED_DrawPoint(x0, y0 + radius,White);
  OLED_DrawPoint(x0 - radius, y0,White);
  OLED_DrawPoint(x0, y0 - radius,White);
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
      OLED_DrawPoint(x0 + x, y0 - y,White);
      OLED_DrawPoint(x0 + y, y0 - x,White);
    }
    if (quads & 0x2) {
      OLED_DrawPoint(x0 - y, y0 - x,White);
      OLED_DrawPoint(x0 - x, y0 - y,White);
    }
    if (quads & 0x4) {
      OLED_DrawPoint(x0 - y, y0 + x,White);
      OLED_DrawPoint(x0 - x, y0 + y,White);
    }
    if (quads & 0x8) {
      OLED_DrawPoint(x0 + x, y0 + y,White);
      OLED_DrawPoint(x0 + y, y0 + x,White);
    }
  }
  if (quads & 0x1 && quads & 0x8) {
    OLED_DrawPoint(x0 + radius, y0,White);
  }
  if (quads & 0x4 && quads & 0x8) {
    OLED_DrawPoint(x0, y0 + radius,White);
  }
  if (quads & 0x2 && quads & 0x4) {
    OLED_DrawPoint(x0 - radius, y0,White);
  }
  if (quads & 0x1 && quads & 0x2) {
    OLED_DrawPoint(x0, y0 - radius,White);
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
	OLED_WR_Byte(0xC0,OLED_CMD);//--Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
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

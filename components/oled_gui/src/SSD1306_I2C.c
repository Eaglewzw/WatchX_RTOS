#include "SSD1306_I2C.h"
#include "driver/gpio.h"


#define     SSD1306_I2C_PIN_IDX_SCL         (GPIO_NUM_4)
#define     SSD1306_I2C_PIN_IDX_SDA         (GPIO_NUM_5)


//#define     SSD1306_I2C_PIN_IDX_SCL         (GPIO_NUM_14)
//#define     SSD1306_I2C_PIN_IDX_SDA         (GPIO_NUM_2)

#define     SSD1306_PIN_HIGH(IDX)           gpio_set_level(IDX, 1)
#define     SSD1306_PIN_LOW(IDX)            gpio_set_level(IDX, 0)




static void SSD1306_I2C_WriteByte(uint8_t uiData);
static void SSD1306_I2C_START(void);
static void SSD1306_I2C_STOP(void);
static void SSD1306_I2C_WAIT_ACK(void);


void SSD1306_I2C_START(void)
{
	SSD1306_PIN_HIGH(SSD1306_I2C_PIN_IDX_SCL);
	SSD1306_PIN_HIGH(SSD1306_I2C_PIN_IDX_SDA);
	SSD1306_PIN_LOW(SSD1306_I2C_PIN_IDX_SDA);
	SSD1306_PIN_LOW(SSD1306_I2C_PIN_IDX_SCL);
}


void SSD1306_I2C_STOP(void)
{
//	ssd1306_sclk_set() ;
	
	SSD1306_PIN_LOW(SSD1306_I2C_PIN_IDX_SDA);
	SSD1306_PIN_HIGH(SSD1306_I2C_PIN_IDX_SDA);	
}

void SSD1306_I2C_WAIT_ACK(void)
{
	SSD1306_PIN_HIGH(SSD1306_I2C_PIN_IDX_SCL);
	SSD1306_PIN_LOW(SSD1306_I2C_PIN_IDX_SCL);
}

/*****************************************************************************/
/** Function Name:	SSD1306_I2C_WriteByte.                                  **/
/** Purpose:		Simulate I2C communication timing to write a byte		**/
/**					to OLED controler.										**/
/** Resources:		Simulate I2C GPIO.										**/
/** Params:																	**/
/**	@uiData:		Byte will be write.										**/
/** Return:			None.													**/
/** Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_I2C_WriteByte(uint8_t uiData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint16_t                i;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	
	
	SSD1306_PIN_LOW(SSD1306_I2C_PIN_IDX_SCL);
	for(i=0;i<8;i++)
	{
		if((uiData << i) & 0x80)
		{
			SSD1306_PIN_HIGH(SSD1306_I2C_PIN_IDX_SDA);
		}
		else
		{
			SSD1306_PIN_LOW(SSD1306_I2C_PIN_IDX_SDA);
		}
		SSD1306_PIN_HIGH(SSD1306_I2C_PIN_IDX_SCL);
		SSD1306_PIN_LOW(SSD1306_I2C_PIN_IDX_SCL);
	}
}

/*****************************************************************************/
/* Function Name:	SSD1306_WriteData.										**/
/* Purpose:			Write a data byte to OLED coltroler.					**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiData:			One byte data will be write.						**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_I2C_WriteData(uint8_t uiData)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SSD1306_I2C_START();
	SSD1306_I2C_WriteByte(0x78);			//D/C#=0; R/W#=0
	SSD1306_I2C_WAIT_ACK();	
	SSD1306_I2C_WriteByte(0x40);			//write data
	SSD1306_I2C_WAIT_ACK();	
	SSD1306_I2C_WriteByte(uiData);
	SSD1306_I2C_WAIT_ACK();	
	SSD1306_I2C_STOP();

}

/*****************************************************************************/
/* Function Name:	SSD1306_WriteCommand.									**/
/* Purpose:			Write a command byte to OLED coltroler.					**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiData:			One byte command will be write.						**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_I2C_WriteCommand(uint8_t uiCommand)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SSD1306_I2C_START();
	SSD1306_I2C_WriteByte(0x78);           //Slave address,SA0=0
	SSD1306_I2C_WAIT_ACK();	
	SSD1306_I2C_WriteByte(0x00);			//write command
	SSD1306_I2C_WAIT_ACK();	
	SSD1306_I2C_WriteByte(uiCommand); 
	SSD1306_I2C_WAIT_ACK();	
	SSD1306_I2C_STOP();
}

/*****************************************************************************/
/* Function Name:	OLED_SetPosition.										**/
/* Purpose:			Set current position of page and colomn.				**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiColumn:			Position of column.									**/
/*	@uiPage:			Position of page.									**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_I2C_SetPosition(uint8_t uiColumn, uint8_t uiPage)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SSD1306_I2C_WriteCommand(0xB0 | uiPage);
	SSD1306_I2C_WriteCommand(((uiColumn & 0xF0)>>4)|0x10);
	SSD1306_I2C_WriteCommand((uiColumn & 0x0F));
}

/*****************************************************************************/
/* Function Name:	SSD1306_I2C_Fill.												**/
/* Purpose:			Fill screen.											**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiColumn:			Position of column.									**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_I2C_Fill(uint8_t uiByte)//全屏填充
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint8_t uiPage, uiColumn;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	for(uiPage=0; uiPage<8; uiPage++)
	{
		SSD1306_I2C_WriteCommand(0xb0 | uiPage);
		SSD1306_I2C_WriteCommand(0x00);
		SSD1306_I2C_WriteCommand(0x10);
		for(uiColumn=0; uiColumn<128; uiColumn++)
		{
			SSD1306_I2C_WriteData(uiByte);
		}
	}
}

/*****************************************************************************/
/* Function Name:	SSD1306_I2C_Clear.												**/
/* Purpose:			Clear screen display.									**/
/* Resources:		None.													**/
/* Params:			None.													**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_I2C_Clear(void)//清屏
{
	SSD1306_I2C_Fill(0x00);
}

/*****************************************************************************/
/** Function Name:	SSD1306_Initialize										**/
/** Purpose:		Run the device initialize sequence.						**/
/** Resources:		None.													**/
/** Params:			None.													**/
/** Return:			None.													**/
/** Limitation:		Initialize sequence must executed after power on 500ms.	**/
/*****************************************************************************/
void SSD1306_I2C_Initialize(void)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Initialize GPIO
	gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL<<SSD1306_I2C_PIN_IDX_SCL) |(1ULL<<SSD1306_I2C_PIN_IDX_SDA);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);


	SSD1306_I2C_WriteCommand(0xae);
	SSD1306_I2C_WriteCommand(0xae);//--turn off oled panel
	SSD1306_I2C_WriteCommand(0x00);//---set low column address
	SSD1306_I2C_WriteCommand(0x10);//---set high column address
	SSD1306_I2C_WriteCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	SSD1306_I2C_WriteCommand(0x81);//--set contrast control register
	SSD1306_I2C_WriteCommand(0xcf); // Set SEG Output Current Brightness
	SSD1306_I2C_WriteCommand(0xa1);//--Set SEG/Column Mapping     0xa0,0xa1
	SSD1306_I2C_WriteCommand(0xc8);//Set COM/Row Scan Direction   0xc0,0xc8
	SSD1306_I2C_WriteCommand(0xa6);//--set normal display
	SSD1306_I2C_WriteCommand(0xa8);//--set multiplex ratio(1 to 64)
	SSD1306_I2C_WriteCommand(0x3f);//--1/64 duty
	SSD1306_I2C_WriteCommand(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	SSD1306_I2C_WriteCommand(0x00);//-not offset
	SSD1306_I2C_WriteCommand(0xd5);//--set display clock divide ratio/oscillator frequency
	SSD1306_I2C_WriteCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	SSD1306_I2C_WriteCommand(0xd9);//--set pre-charge period
	SSD1306_I2C_WriteCommand(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	SSD1306_I2C_WriteCommand(0xda);//--set com pins hardware configuration
	SSD1306_I2C_WriteCommand(0x12);
	SSD1306_I2C_WriteCommand(0xdb);//--set vcomh
	SSD1306_I2C_WriteCommand(0x40);//Set VCOM Deselect Level
	SSD1306_I2C_WriteCommand(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	SSD1306_I2C_WriteCommand(0x02);//
	SSD1306_I2C_WriteCommand(0x8d);//--set Charge Pump enable/disable
	SSD1306_I2C_WriteCommand(0x14);//--set(0x10) disable
	SSD1306_I2C_WriteCommand(0xa4);// Disable Entire Display On (0xa4/0xa5)
	SSD1306_I2C_WriteCommand(0xa6);// Disable Inverse Display On (0xa6/a7)
	SSD1306_I2C_WriteCommand(0xaf);//--turn on oled panel
	SSD1306_I2C_Fill(0x00);
	SSD1306_I2C_SetPosition(0,0);
}

void OLED_BMP(uint32_t uiPosX, uint32_t uiPosY, uint32_t uiWidth, uint32_t uiHeight, uint8_t *pData)
{
	uint16_t	uiColumnIndex, uiPageIndex;
	uint16_t	uiColumnCount, uiPageCount;
	uint32_t	uiDataIndex;

	uiColumnCount = (uint16_t)uiWidth;
	if(uiHeight%8==0)
	{
		uiPageCount=uiHeight/8;
	}
	else
	{
		uiPageCount=uiHeight/8+1;
	}
	uiDataIndex = 0;

	for(uiPageIndex=uiPosY; uiPageIndex<uiPageCount; uiPageIndex++)
	{
		SSD1306_I2C_SetPosition(uiPosX, uiPageIndex);
		for(uiColumnIndex=uiPosX; uiColumnIndex<uiColumnCount; uiColumnIndex++)
		{
			SSD1306_I2C_WriteData(*(pData+uiDataIndex));
			uiDataIndex++;
		}
	}
}

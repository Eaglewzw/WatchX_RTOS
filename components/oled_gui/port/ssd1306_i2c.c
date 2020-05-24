#include "ssd1306_i2c.h"

void iic_start(void)
{
	ssd1306_sclk_set() ;
	ssd1306_sdat_set();
	ssd1306_sdat_clr();
	ssd1306_sclk_clr();
}


void iic_stop(void)
{
	ssd1306_sclk_set() ;
	ssd1306_sdat_clr();
	ssd1306_sdat_set();
}

void iic_wait_ack(void)
{
	ssd1306_sclk_set() ;
	ssd1306_sclk_clr();
}


void iic_write_byte(uint8_t iic_byte)
{
	uint8_t i;
	uint8_t m,data;
	data=iic_byte;
	ssd1306_sclk_clr();
	for(i=0;i<8;i++)		
	{
		m=data;
		m=m&0x80;
		if(m==0x80)
			ssd1306_sdat_set();
		else 
			ssd1306_sdat_clr();
			data=data<<1;
		ssd1306_sclk_set();
		ssd1306_sclk_clr();
	}


}

void iic_write_command(uint8_t iic_command)
{
	iic_start();
	iic_write_byte(0x78);            //Slave address,SA0=0
	iic_wait_ack();	
	iic_write_byte(0x00);			//write command
	iic_wait_ack();	
	iic_write_byte(iic_command); 
	iic_wait_ack();	
	iic_stop();
}

void iic_write_data(uint8_t iic_data)
{
	iic_start();
	iic_write_byte(0x78);			//D/C#=0; R/W#=0
	iic_wait_ack();	
	iic_write_byte(0x40);			//write data
	iic_wait_ack();	
	iic_write_byte(iic_data);
	iic_wait_ack();	
	iic_stop();
}


/**
  * @brief	: 向SSD1306写入一个字节
  * @note	: 无
  * @param 	: dat:要写入的数据/命令   cmd:数据/命令标志 0,表示命令;1,表示数据    
  * @retval	: 无
  */ 
void ssd1306_write_byte(uint8_t dat,uint8_t cmd)
{
	if(cmd)
	{
   		iic_write_data(dat);
	}
	else {
   		iic_write_command(dat);	
	}
}


/**
  * @brief	: 初始化OLED 
  * @note	: 无
  * @param 	: 无  
  * @retval	: 无
  */  			    
void ssd1306_init(void)
{

	/*****************管脚初始化************************
	*             SCLK ---------------->GPIO4
	*             SDA  ---------------->GPIO5
	****************************************************
	*/
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL<<ssd1306_sclk_pins) |(1ULL<<ssd1306_sdat_pins);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);


    ssd1306_write_byte(0xAE,SSD1306_CMD);//--turn off oled panel
    ssd1306_write_byte(0x00,SSD1306_CMD);//---set low column address
    ssd1306_write_byte(0x10,SSD1306_CMD);//---set high column address
    ssd1306_write_byte(0x40,SSD1306_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    ssd1306_write_byte(0x81,SSD1306_CMD);//--set contrast control register
    ssd1306_write_byte(0xCF,SSD1306_CMD); // Set SEG Output Current Brightness
    ssd1306_write_byte(0xA1,SSD1306_CMD);//--Set SEG/Column Mapping      0xa0左右反置 0xa1正常
    ssd1306_write_byte(0xC8,SSD1306_CMD);//--Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    ssd1306_write_byte(0xA6,SSD1306_CMD);//--set normal display
    ssd1306_write_byte(0xA8,SSD1306_CMD);//--set multiplex ratio(1 to 64)
    ssd1306_write_byte(0x3f,SSD1306_CMD);//--1/64 duty
    ssd1306_write_byte(0xD3,SSD1306_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    ssd1306_write_byte(0x00,SSD1306_CMD);//-not offset
    ssd1306_write_byte(0xd5,SSD1306_CMD);//--set display clock divide ratio/oscillator frequency
    ssd1306_write_byte(0x80,SSD1306_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    ssd1306_write_byte(0xD9,SSD1306_CMD);//--set pre-charge period
    ssd1306_write_byte(0xF1,SSD1306_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    ssd1306_write_byte(0xDA,SSD1306_CMD);//--set com pins hardware configuration
    ssd1306_write_byte(0x12,SSD1306_CMD);
    ssd1306_write_byte(0xDB,SSD1306_CMD);//--set vcomh
    ssd1306_write_byte(0x40,SSD1306_CMD);//Set VCOM Deselect Level
    ssd1306_write_byte(0x20,SSD1306_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
    ssd1306_write_byte(0x02,SSD1306_CMD);//
    ssd1306_write_byte(0x8D,SSD1306_CMD);//--set Charge Pump enable/disable
    ssd1306_write_byte(0x14,SSD1306_CMD);//--set(0x10) disable
    ssd1306_write_byte(0xA4,SSD1306_CMD);// Disable Entire Display On (0xa4/0xa5)
    ssd1306_write_byte(0xA6,SSD1306_CMD);// Disable Inverse Display On (0xa6/a7) 
    ssd1306_write_byte(0xAF,SSD1306_CMD);//--turn on oled panel

}  
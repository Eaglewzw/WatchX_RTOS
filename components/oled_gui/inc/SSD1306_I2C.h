#ifndef SSD1306_I2C_h
#define SSD1306_I2C_h

#include <stdint.h>
#include <stddef.h>

void SSD1306_I2C_Initialize(void);
void SSD1306_I2C_SetPosition(uint8_t uiColumn, uint8_t uiPage);
void SSD1306_I2C_Fill(uint8_t bmp_dat);
void SSD1306_I2C_Clear(void);
void SSD1306_I2C_WriteData(uint8_t uiData);
void SSD1306_I2C_WriteCommand(uint8_t cmd);

#endif  



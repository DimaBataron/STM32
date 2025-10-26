

#include <main.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <font.h>
#include "handl_ssd1306.h"

extern uint8_t ComArr[];
extern uint8_t ComArrSet[];
extern uint8_t *ptrCom;
extern uint8_t *ptrNexCom;
extern uint16_t Size;


#define DISPTYPE_ssd1306        0       // OLED-дисплей с контроллером ssd1306


// С каким типом дисплея будет работать модуль disp1color
#define DISP1COLOR_type         DISPTYPE_ssd1306

// Размеры дисплея в пикселях
#define DISP1COLOR_Width        128
#define DISP1COLOR_Height       64

#define BufLen ( ((DISP1COLOR_Width* DISP1COLOR_Height) / 8)+1  )

// Процедура инициализирует 1-цветый дисплей
void disp1color_Init(void);

void disp1color_FillScreenbuff(uint8_t FillValue);

int16_t disp1color_printf(uint8_t X, uint8_t Y, uint8_t FontID, const char *args, ...);

int16_t disp1color_DrawString(uint8_t X, uint8_t Y, uint8_t FontID, uint8_t *Str);

int16_t disp1color_DrawString_Invert(uint8_t X, uint8_t Y, uint8_t FontID, uint8_t *Str);

uint8_t disp1color_DrawChar(uint8_t X, uint8_t Y, uint8_t FontID, uint8_t Char, uint8_t Invert);

void disp1color_DrawPixel(uint8_t X, uint8_t Y, uint8_t State);

void disp1color_DrawPixel_Invert(uint8_t X, uint8_t Y, uint8_t State);

uint16_t GetIndex( uint8_t X, uint8_t Y);

void disp1color_UpdateFromBuff(void);

//void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);

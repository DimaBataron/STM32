

#include<main.h>
//==============================================================================
// Коды команд дисплея
//==============================================================================

#define CMD_SetContrast                 0x81
#define CMD_AllPixRAM                   0xA4
#define CMD_AllPixOn                    0xA5
#define CMD_SetInverseOff               0xA6
#define CMD_SetInverseOn                0xA7
#define CMD_Sleep                       0xAE
#define CMD_Wake                        0xAF
#define CMD_Lock                        0xFD

#define CMD_DeactivateScroll            0x2E
// Команды из раздела Addressing Setting
// Команда выбора режима автосдвига указателя в памяти кадра
#define CMD_SetMemAdressingMode         0x20
// Команды выбора диапазона изменения страницы и колонки при автосдвиге указателя в памяти кадра
// Применяется для режимов автосдвига SSD1306_Adressing_Horizontal и SSD1306_Adressing_Vertical
#define CMD_SetColumnAddr               0x21
#define CMD_SetPageAddr                 0x22


#define CMD_PageAddrMode_SetPage        0xB0
#define CMD_PageAddrMode_StartColumnLo  0x00
#define CMD_PageAddrMode_StartColumnHi  0x10


#define CMD_SetDisplayStartLine         0x40
#define CMD_SetSegmentRemap             0xA0
#define CMD_SetMultiplexRatio           0xA8
#define CMD_SetCOMoutScanDirection      0xC0
#define CMD_SetDisplayOffset            0xD3
#define CMD_SetCOMPinsConfig            0xDA


#define CMD_SetDisplayClockDivider      0xD5
#define CMD_SetPrechargePeriod          0xD9
#define CMD_SetVCOMHDeselectLevel       0xDB

// Команды из раздела Charge Pump
#define CMD_ChargePumpSetting           0x8D

void SSD1306_Init(uint8_t Width, uint8_t Height);

void SSD1306_DisplayFullUpdate(uint8_t *pBuff, uint16_t BuffLen);

void SSD1306_SendCOM();

void SendData(uint8_t *pBuff, uint16_t BuffLen);


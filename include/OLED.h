#ifndef _OLED_H_
#define _OLED_H_

#include <Arduino.h>
#include "OLED_Font.h"

#define OLED_SDA 13
#define OLED_SCK 14

extern int32_t humidity;
extern int32_t temperature;

void OLED_i2c_start(void);
void OLED_i2c_stop(void);
void OLED_i2c_write_byte(uint8_t byte);
void OLED_Write_Command(uint8_t command);
void OLED_Write_Data(uint8_t data);
void OLED_Set_Cursor(uint8_t Y, uint8_t X);
void OLED_ClearAll(void);
void OLED_Clear(uint8_t Line, uint8_t Column,uint8_t Length);
void OLED_Show_Char(uint8_t Line, uint8_t Column, char Char);
void OLED_Show_Char_CN(uint8_t Line, uint8_t Column,const uint8_t font[][16], uint8_t Length);
void OLED_Show_String(uint8_t Line, uint8_t Column, char *String);
uint32_t OLED_Pow(uint32_t X, uint32_t Y);
void OLED_Show_SignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_Init(void);

#endif
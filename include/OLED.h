#ifndef _OLED_H_
#define _OLED_H_

#include <Arduino.h>
#include <Wire.h>
#include "OLED_Font.h"
#include "I2C_Config.h"
#include "getTime.h"

// OLED显示参数
#define OLED_WIDTH  128
#define OLED_HEIGHT 64
#define OLED_PAGES  8  // HEIGHT/8

// OLED控制函数
bool OLED_Write_Command(uint8_t command);
bool OLED_Write_Data(uint8_t data);
bool OLED_Write_Data_Batch(const uint8_t* data, uint8_t length);
bool OLED_Set_Cursor(uint8_t Y, uint8_t X);
bool OLED_ClearAll(void);
bool OLED_Clear(uint8_t Line, uint8_t Column, uint8_t Length);
bool OLED_Clear_Rect(uint8_t startLine, uint8_t startColumn, uint8_t endLine, uint8_t endColumn);

// OLED显示函数
bool OLED_Show_Char(uint8_t Line, uint8_t Column, char Char);
bool OLED_Show_Char_CN(uint8_t Line, uint8_t Column, const uint8_t font[][16], uint8_t Length);
bool OLED_Show_String(uint8_t Line, uint8_t Column, char *String);
uint32_t OLED_Pow(uint32_t X, uint32_t Y);
bool OLED_Show_SignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

// OLED初始化
bool OLED_Init(void);

// AHT20调用
void OLED_AHT20_display(int32_t tem,int32_t hum);

// PWM调用
void OLED_fan_speed_display(int level, bool flag);

// time调用
void OLED_time_display(int flag, int month, int day, int hour, int minute);

// weather调用
void OLED_weather_display(const char* lastWeather, const char* weather);

#endif
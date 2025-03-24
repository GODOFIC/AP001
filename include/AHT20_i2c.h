#ifndef _AHT20_I2C_H_
#define _AHT20_I2C_H_

#include <Arduino.h>
#include <Wire.h>
#include "OLED.h"
#include "I2C_Config.h"

// 命令字节
#define AHT20_CMD_INIT      0xBE
#define AHT20_CMD_MEASURE   0xAC
#define AHT20_CMD_STATUS    0x71

// 函数声明

bool isCalibrated(void);
uint8_t readStatus(void);
bool initAHT20(void);
bool readData(void);

void AHT20_setup(void);
bool AHT20_measurement(void);


#endif
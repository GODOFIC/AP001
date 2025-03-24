#ifndef _I2C_CONFIG_H_
#define _I2C_CONFIG_H_

#include <Arduino.h>
#include <Wire.h>

// I2C引脚定义
#define I2C_SDA 14  // 共享的SDA引脚
#define I2C_SCL 12  // 共享的SCL引脚

// I2C地址定义
#define OLED_ADDR 0x3C  // 0x78 >> 1
#define AHT20_ADDR 0x38

// 初始化共享I2C总线
void init_shared_i2c(void);

#endif
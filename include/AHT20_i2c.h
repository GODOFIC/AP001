#ifndef _AHT20_I2C_H_
#define _AHT20_I2C_H_

#include <Arduino.h>
#include "OLED.h"

// 传感器相关定义
#define AHT20_ADDR 0x38  // AHT20 I2C 地址

#define TH_SDA 21  // 设置 TH_SDA 引脚
#define TH_SCL 22  // 设置 TH_SCL 引脚

void i2c_start(void);
void i2c_stop(void);
void send_ack(void);
void send_nack(void);
bool wait_for_ack(void);
void i2c_write_byte(uint8_t byte);
uint8_t i2c_read_byte(void);
void AHT20_setup(void);
bool isCalibrated(void);
uint8_t readStatus(void);
void initAHT20(void);
void AHT20_measurement(void);
void readData(void);
void OLED_displayMeasurement(void);

#endif

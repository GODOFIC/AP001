#include "I2C_Config.h"

// 初始化共享I2C总线
void init_shared_i2c(void) {
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(100000); // 设置I2C时钟频率为100kHz
  Serial.println("Shared I2C bus initialized");
}


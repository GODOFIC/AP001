#include "AHT20_i2c.h"

int32_t temperature = 0;   // 温度
int32_t humidity = 0;      // 相对湿度


// 初始化AHT20
void AHT20_setup(void) 
{
  // 共享I2C总线已在main.cpp中初始化
  delay(40);  // 上电后等待 40ms

  // 初始化传感器
  if (!isCalibrated()) 
  {
    initAHT20();  // 初始化传感器
  }

  delay(100);
  AHT20_measurement();
}

// 检查校准位
bool isCalibrated(void) 
{
  uint8_t status = readStatus();  // 读取状态字
  return status & 0x08;           // 检查 Bit[3] 是否为 1（校准使能位）
}

// 读取状态字
uint8_t readStatus(void) 
{
  Wire.beginTransmission(AHT20_ADDR);
  Wire.write(AHT20_CMD_STATUS);  // 发送获取状态字的命令
  uint8_t error = Wire.endTransmission();
  
  if (error != 0) {
    Serial.printf("AHT20 status command error: %d\n", error);
    return 0;
  }
  
  // 读取状态字节
  if (Wire.requestFrom(AHT20_ADDR, 1) != 1) {
    Serial.println("Error requesting status byte from AHT20");
    return 0;
  }
  
  return Wire.read();
}

// 初始化 AHT20
bool initAHT20(void) 
{
  Wire.beginTransmission(AHT20_ADDR);
  Wire.write(AHT20_CMD_INIT);  // 发送初始化命令
  Wire.write(0x08);            // 发送第一个参数字节
  Wire.write(0x00);            // 发送第二个参数字节
  uint8_t error = Wire.endTransmission();
  
  if (error != 0) {
    Serial.printf("AHT20 init error: %d\n", error);
    return false;
  }

  delay(10);  // 等待初始化完成
  return true;
}

// 触发测量并读取温湿度数据
bool AHT20_measurement(void) 
{
  // 发送 测量命令
  Wire.beginTransmission(AHT20_ADDR);
  Wire.write(AHT20_CMD_MEASURE);  // 发送测量命令
  Wire.write(0x33);               // 第一个参数
  Wire.write(0x00);               // 第二个参数
  uint8_t error = Wire.endTransmission();
  
  if (error != 0) {
    Serial.printf("AHT20 measurement command error: %d\n", error);
    return false;
  }

  delay(80);  // 等待 80ms 进行测量

  // 检查测量完成状态
  uint8_t attempts = 0;
  while ((readStatus() & 0x80) && attempts < 10) { // 测量完成位为0
    delay(10);
    attempts++;
  }
  
  if (attempts >= 10) {
    Serial.println("AHT20 measurement timeout");
    return false;
  }

  // 读取测量数据
  if (!readData()) {
    return false;
  }

  // 更新OLED显示
  OLED_AHT20_display(temperature, humidity);
  return true;
}

// 读取温湿度数据
bool readData(void) 
{
  // 请求6个字节的数据（状态+湿度+温度）
  if (Wire.requestFrom(AHT20_ADDR, 6) != 6) {
    Serial.println("Error requesting data from AHT20");
    return false;
  }
  
  uint8_t data[6];
  for (int i = 0; i < 6; i++) {
    data[i] = Wire.read();
  }
  
  // 解析湿度和温度
  int32_t humidity_raw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
  int32_t temperature_raw = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];

  humidity = humidity_raw * 100 / 1048576;
  temperature = temperature_raw * 200 / 1048576 - 50;

  // 串口输出数据
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.print("   ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  return true;
}



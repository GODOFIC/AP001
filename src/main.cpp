#include <Arduino.h>
#include "I2C_Config.h"
#include "AHT20_i2c.h"
#include "OLED.h"
#include "getTime.h"
#include "fan_control.h"

u_int8_t count = 0;    // 用于记录时间间隔
bool firstRun = true; // 标志变量，记录是否为第一次运行

#define delay_time_ms 200

void setup() 
{
  Serial.begin(74880); // 串口初始化
  Serial.println("System starting...");
  
  // 初始化共享I2C总线
  init_shared_i2c();
  
  OLED_Init();

  fan_init();
  
  // 初始化AHT20
  AHT20_setup();
  
  // 初始化WiFi
  WiFi_init();
  
  Serial.println("System initialization complete");
}

void loop() 
{
  if (firstRun) 
  {
    if(!AHT20_measurement()) {
      Serial.println("First AHT20 measurement failed");
    }
    firstRun = false; // 将标志变量设为false，表示已完成第一次运行
  } 
  else 
  {
    // 判断是否达到4秒间隔
    if ((count * delay_time_ms) >= 4000) 
    {
      if(!AHT20_measurement()) {
        Serial.println("AHT20 measurement failed");
      }
      count = 0;
    }
  }
  
  wifi_time_flush(); // 更新时间显示
  polling_fan_button();
  delay(delay_time_ms); 
  
  count++;
}
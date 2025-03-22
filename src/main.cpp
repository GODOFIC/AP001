#include <Arduino.h>
#include "AHT20_i2c.h"
#include "OLED.h"
#include "PWM_Interrupt.h"
#include "getTime.h"

u_int8_t count = 0;    // 用于记录时间间隔
bool firstRun = true; // 标志变量，记录是否为第一次运行

void setup() 
{
  Serial.begin(115200); // 串口初始化

  OLED_Init(); // 初始化 OLED 并显示提示信息（温湿度，风扇状态）

  PWM_Interrupt_init(); // 初始化 PWM中断
  //Serial.println("");
  //Serial.print("Temperature: ");
  AHT20_setup(); // 初始化 ATH20_I2C

  WiFi_init(); // 初始化 WIFI
}


void loop() 
{
  
  if (firstRun) 
  {
    AHT20_measurement(); // 第一次立即获取温湿度数据
    firstRun = false; // 将标志变量设为false，表示已完成第一次运行
  } 
  else 
  {
    // 判断是否达到4秒间隔
    if (count == 10) 
    {
      AHT20_measurement(); // 获取温湿度数据
      count = 0;
    }
  }
  
  

  OLED_displayTime(); // 更新时间显示

  delay(1000); //1秒延时以更新时间
  
  count++;
  
}
    
   



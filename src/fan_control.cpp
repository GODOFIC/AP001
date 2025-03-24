#include "fan_control.h"

// PWM 占空比（档位）
int fanSpeedLevels[] = {25, 50, 75, 100};  // 风扇四档：25%, 50%, 75%, 100%
int currentLevel = 0;   // 当前风速档位
bool isFanOn = 0;   // 风扇开关状态

void fan_init()
{
  // 初始化 EEPROM(1字节)
  EEPROM.begin(1);  
    
  // 设置引脚模式为上拉输入模式
  pinMode(fan_switch, INPUT_PULLUP);
  pinMode(fan_speed_ctl, INPUT_PULLUP);

  
  // 引脚20为风扇的睡眠控制引脚
  pinMode(fan_power, OUTPUT);   
  digitalWrite(fan_power, LOW); // 风扇未睡眠引脚为低电平(高电平有效)
  
  
  // 从 EEPROM 中读取上次风扇档位
  currentLevel = EEPROM.read(EEPROM_ADDR);
  if (currentLevel < 0 || currentLevel > 3) 
  {
    currentLevel = 0;  // 如果数据不合法，设置为第一档
    EEPROM.write(EEPROM_ADDR, currentLevel);   // 保存到 EEPROM
    EEPROM.commit();       // 提交更改
  }
  
}

// 风扇开关控制
void handle_fan_switch() 
{
  if (!isFanOn) 
  {
    pinMode(fan_pwm, OUTPUT);  // 设置 PWM 输出引脚
    isFanOn = 1;
    digitalWrite(fan_power, HIGH);
    analogWrite(fan_pwm, map(fanSpeedLevels[currentLevel], 0, 100, 0, 255));  // 开启风扇并设定当前档位
    OLED_fan_speed_display(currentLevel, true); // OLED显示当前风档
  } 
  else 
  {
    isFanOn = 0;  
    digitalWrite(fan_power, LOW);
    pinMode(fan_pwm, INPUT);  // 将引脚设置为输入模式，恢复到未初始化状态
    OLED_fan_speed_display(currentLevel, false);
  }
}

// 风速控制按键中断处理函数
void handle_fan_speed_ctl() 
{ 
  if(!isFanOn)
    return;

  if (currentLevel < 3) 
  {
    currentLevel++;
    analogWrite(fan_pwm, map(fanSpeedLevels[currentLevel], 0, 100, 0, 255));  // 设置较高的风速档位
    OLED_fan_speed_display(currentLevel, true);
    EEPROM.write(EEPROM_ADDR, currentLevel);  // 保存当前档位
    EEPROM.commit(); // 提交更改
  } 
  else if(currentLevel == 3)
  {
    currentLevel = 0;
    analogWrite(fan_pwm, map(fanSpeedLevels[currentLevel], 0, 100, 0, 255));  // 设置较低的风速档位
    OLED_fan_speed_display(currentLevel, true);
    EEPROM.write(EEPROM_ADDR, currentLevel);  // 保存当前档位
    EEPROM.commit();// 提交更改

  }
}

void polling_fan_button() 
{ 
  if (digitalRead(fan_switch) == LOW) 
  {
    handle_fan_switch();
  }
  if (digitalRead(fan_speed_ctl) == LOW) 
  {
    handle_fan_speed_ctl();
  }
}


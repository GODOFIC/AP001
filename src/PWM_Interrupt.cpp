#include "PWM_Interrupt.h"

// PWM 占空比（档位）
int fanSpeedLevels[] = {25, 50, 75, 100};  // 风扇四档：25%, 50%, 75%, 100%
int currentLevel = 0;   // 当前风速档位
bool isFanOn = false;   // 风扇开关状态
bool isSleeping = false; // 睡眠模式状态

void PWM_Interrupt_init()
{
  // 初始化 EEPROM(1字节)
  EEPROM.begin(1);  
    
  // 设置引脚模式为上拉输入模式
  pinMode(fanSwitch, INPUT_PULLUP);
  pinMode(fanSleepOn, INPUT_PULLUP);
  pinMode(fanSlow, INPUT_PULLUP);
  pinMode(fanRise, INPUT_PULLUP);
  
  // 引脚20为风扇的睡眠控制引脚
  pinMode(fanSleepPower, OUTPUT);   
  digitalWrite(fanSleepPower, HIGH); // 风扇未睡眠引脚为高电平(低电平有效)
  
  
  // 从 EEPROM 中读取上次风扇档位
  currentLevel = EEPROM.read(EEPROM_ADDR);
  if (currentLevel < 0 || currentLevel > 3) 
  {
    currentLevel = 0;  // 如果数据不合法，设置为第一档
    EEPROM.write(EEPROM_ADDR, currentLevel);   // 保存到 EEPROM
    EEPROM.commit();       // 提交更改
  }

  // 设定中断
  attachInterrupt(digitalPinToInterrupt(fanSwitch), handleButton9, FALLING);
  attachInterrupt(digitalPinToInterrupt(fanSleepOn), handleButton10, FALLING);
  attachInterrupt(digitalPinToInterrupt(fanSlow), handleButton12, FALLING);
  attachInterrupt(digitalPinToInterrupt(fanRise), handleButton13, FALLING);
}

// 风扇开关控制（引脚9按下）
void IRAM_ATTR handleButton9() 
{
  if (!isFanOn) 
  {
    pinMode(fanPWM, OUTPUT);  // 设置 PWM 输出引脚
    isFanOn = true;
    analogWrite(fanPWM, map(fanSpeedLevels[currentLevel], 0, 100, 0, 1023));  // 开启风扇并设定当前档位
    PWM_OLED_displayLevel(currentLevel); // OLED显示当前风档
  } 
  else 
  {
    isFanOn = false;  
    pinMode(fanPWM, INPUT);  // 将引脚设置为输入模式，恢复到未初始化状态
    OLED_Clear(3, 10, 4); //清除Line 3 后 4 Column的内容
    OLED_Show_Char_CN(3, 10, font_Off, 2); // 显示“关闭”
  }
}

// 睡眠模式控制（引脚10按下）
void IRAM_ATTR handleButton10() 
{
  if (isFanOn && !isSleeping) 
  {
    isSleeping = true;
    pinMode(fanPWM, INPUT);  // 将引脚设置为输入模式，恢复到未初始化状态
    digitalWrite(fanSleepPower, LOW); // 风扇睡眠引脚设置为低电平，开启睡眠
    OLED_Clear(3, 10, 4); //清除Line3内容
    OLED_Show_Char_CN(3, 10, font_sleep, 2); // 显示“睡眠”
  } 
  else if (isSleeping) 
  {
    isSleeping = false;
    digitalWrite(fanSleepPower, HIGH); // 风扇睡眠引脚设置为高电平，关闭睡眠
    pinMode(fanPWM, OUTPUT);  // 设置 PWM 输出引脚
    analogWrite(fanPWM, map(fanSpeedLevels[currentLevel], 0, 100, 0, 1023));  // 恢复到上一次档位
    PWM_OLED_displayLevel(currentLevel);
  }
}

// 降低风速（引脚12按下）
void IRAM_ATTR handleButton12() 
{
  if (isFanOn && !isSleeping) 
  {
    if (currentLevel > 0) 
    {
      currentLevel--;
      analogWrite(fanPWM, map(fanSpeedLevels[currentLevel], 0, 100, 0, 1023));  // 设置较低的风速档位
      PWM_OLED_displayLevel(currentLevel);
      EEPROM.write(EEPROM_ADDR, currentLevel);  // 保存当前档位
      EEPROM.commit(); // 提交更改
    } 
  }
  else if(isSleeping) 
  {
    isSleeping = false;
    digitalWrite(fanSleepPower, HIGH); // 风扇睡眠引脚设置为高电平，关闭睡眠
    pinMode(fanPWM, OUTPUT);  // 设置 PWM 输出引脚
    analogWrite(fanPWM, map(fanSpeedLevels[currentLevel], 0, 100, 0, 1023));  // 恢复到上一次档位
    PWM_OLED_displayLevel(currentLevel);
  }
}

// 提升风速（引脚13按下）
void IRAM_ATTR handleButton13() 
{
  if (isFanOn && !isSleeping) 
  {
    if (currentLevel < 3) 
    {
      currentLevel++;
      analogWrite(fanPWM, map(fanSpeedLevels[currentLevel], 0, 100, 0, 1023));  // 设置较高的风速档位
      PWM_OLED_displayLevel(currentLevel);
      EEPROM.write(EEPROM_ADDR, currentLevel);  // 保存当前档位
      EEPROM.commit(); // 提交更改
    } 
  }
  else if(isSleeping) 
  {
    isSleeping = false;
    digitalWrite(fanSleepPower, HIGH); // 风扇睡眠引脚设置为高电平，关闭睡眠
    pinMode(fanPWM, OUTPUT);  // 设置 PWM 输出引脚
    analogWrite(fanPWM, map(fanSpeedLevels[currentLevel], 0, 100, 0, 1023));  // 恢复到上一次档位
    PWM_OLED_displayLevel(currentLevel);  
  }
}

void PWM_OLED_displayLevel(int level)
{
  OLED_Clear(3, 10, 4); //清除Line 3 后 4 Column的内容

  switch (level)
  {
  case 0:
    OLED_Show_Char_CN(3, 10, font_low, 2);
    break;
  case 1:
    OLED_Show_Char_CN(3, 10, font_middle, 2);
    break;
  case 2:
    OLED_Show_Char_CN(3, 10, font_high, 2);
    break;
  case 3:
    OLED_Show_Char_CN(3, 10, font_superstrong, 2);
    break;
  default:
    Serial.print(" OLED fan level error!");
    break;
  }
}

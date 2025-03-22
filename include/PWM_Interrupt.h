#ifndef _PWM_Interrupt_H_
#define _PWM_Interrupt_H_

#include <Arduino.h>
#include <EEPROM.h>
#include "OLED.h"


// 引脚定义
#define fanSwitch 8  // 风扇开关按键
#define fanSleepOn 9 // 睡眠模式按键
#define fanSlow 10 // 降低风速按键
#define fanRise 12 // 提升风速按键
#define fanPWM 16     // PWM 输出引脚（风扇控制）
#define fanSleepPower 24   // 风扇睡眠引脚

// EEPROM 地址
#define EEPROM_ADDR 0  // EEPROM 保存风速档位





// 初始化函数声明
void PWM_Interrupt_init();

// OLED 显示函数声明
void PWM_OLED_displayLevel(int level);

// 中断服务函数声明
void IRAM_ATTR handleButton9();
void IRAM_ATTR handleButton10();
void IRAM_ATTR handleButton12();
void IRAM_ATTR handleButton13();

#endif
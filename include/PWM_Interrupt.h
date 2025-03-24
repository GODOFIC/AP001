#ifndef _PWM_Interrupt_H_
#define _PWM_Interrupt_H_

#include <Arduino.h>
#include <EEPROM.h>
#include "OLED.h"




// 引脚定义
#define fan_switch 13  // 风扇开关按键 
#define fan_speed_ctl 16 // 风速控制按键

#define fan_power 5   // 风扇开关引脚
#define fan_pwm 4

// EEPROM 地址
#define EEPROM_ADDR 0  // EEPROM 保存风速档位

// 初始化函数声明
void PWM_Interrupt_init();

// 中断服务函数声明
void IRAM_ATTR handle_fan_switch();
void IRAM_ATTR handle_fan_speed_ctl();

#endif
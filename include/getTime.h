#ifndef _GET_TIME_H_
#define _GET_TIME_H_

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "OLED.h"
#include "OLED_Font.h"
extern "C" 
{
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
}

void WiFi_init(void);
void getTime(void);
void OLED_displayTime(void);

#endif
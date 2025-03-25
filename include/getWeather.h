#ifndef _GET_WEATHER_H_
#define _GET_WEATHER_H_

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "OLED.h"

void weather_display(const char* weather);
void getWeather(void);

#endif
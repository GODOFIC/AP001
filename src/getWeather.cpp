#include "getWeather.h"

// 配置参数
const String key = "3595e3947a0d548a4c225233ccc26993";   // 高德开放平台获取的key
const String city = "350211";                            // 城市adcode  集美350211 鲤城区350502 北京110000
const String extensions = "all";                        // base 或 all base为实况天气 all为预报天气
const String output = "JSON";                            // JSON 或 XML

// 合成 URL
const String URL_PATH  = String("/v3/weather/weatherInfo?")
                 + "key=" + key 
                 + "&city=" + city 
                 + "&extensions=" + extensions
                 + "&output=" + output;

#define MAX_WEATHER_LEN 1000
char lastWeather[MAX_WEATHER_LEN] ;

// 获取天气数据
void getWeather(void) 
{
  WiFiClientSecure  client;
  client.setInsecure(); // 禁用证书验证
  HTTPClient https;

  Serial.println("[HTTPS] Starting request...");
  
  // 开始 HTTP 请求
  if (https.begin(client, "restapi.amap.com", 443, URL_PATH, true)) 
  { // 配置 URL
    Serial.println("[HTTPS] Connection established.");
    Serial.print("URL: ");
    Serial.println("restapi.amap.com" + URL_PATH);

    // 发送 GET 请求
    int httpCode = https.GET();

    if (httpCode > 0) 
    {
      // 成功响应 HTTP 请求
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) { // 检查 HTTP 状态码
        String payload = https.getString(); // 获取响应数据
        Serial.println("Response payload:");
        Serial.println(payload);

        // 解析 JSON 数据
        JsonDocument doc; // 自动分配内存
        DeserializationError error = deserializeJson(doc, payload);

        if (error) 
        {
          Serial.print("JSON 解析失败: ");
          Serial.println(error.f_str());
        } 
        else 
        {
          // 提取并打印天气字段
          const char* weather = doc["forecasts"][0]["casts"][0]["dayweather"];
          Serial.print("天气预报: ");
          Serial.println(weather);
          OLED_weather_display(lastWeather, weather);
          if (strlen(weather) < MAX_WEATHER_LEN) 
          {
            strcpy(lastWeather, weather); // 复制字符串内容
          } 
          else 
          {
            Serial.printf("字符串过长，无法复制！\n");
            return ;
          }
        }
      }
    } 
    else 
    {
      // 失败的 HTTP 请求
      Serial.printf("[HTTPS] GET failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    // 结束 HTTP 请求
    https.end();
  } 
  else 
  {
    Serial.println("[HTTPS] Unable to connect.");
  }
}


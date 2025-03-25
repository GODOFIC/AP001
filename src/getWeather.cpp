#include "getWeather.h"

// 配置参数
const String key = "3595e3947a0d548a4c225233ccc26993";   // 高德开放平台获取的key
const String city = "350211";                            // 城市adcode  集美350211 鲤城区350502 北京110000
const String extensions = "base";                        // base 或 all
const String output = "JSON";                            // JSON 或 XML

// 合成 URL
const String URL = String("https://restapi.amap.com/v3/weather/weatherInfo?")
                 + "key=" + key 
                 + "&city=" + city 
                 + "&extensions=" + extensions 
                 + "&output=" + output;

#define MAX_WEATHER_LEN 100
char lastWeather[MAX_WEATHER_LEN] ;

// 获取天气数据
void getWeather(void) 
{
  WiFiClient client;
  HTTPClient https;

  Serial.println("[HTTPS] Starting request...");
  
  // 开始 HTTP 请求
  if (https.begin(client, URL)) 
  { // 配置 URL
    Serial.println("[HTTPS] Connection established.");
    Serial.print("URL: ");
    Serial.println(URL);

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
          const char* weather = doc["lives"][0]["weather"];
          Serial.print("天气: ");
          Serial.println(weather);
          weather_display(weather);
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

void weather_display(const char* weather)
{
  if(strcmp(lastWeather, weather) == 0)
  {
    return ;
  }
  
  OLED_Clear(2, 6, 11);

  if (strcmp(weather, "晴") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_qing, 1);
  }
  else if (strcmp(weather, "少云") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_shaoyun, 2);
  }
  else if (strcmp(weather, "晴间多云") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_qingjianduoyun, 4);
  }
  else if (strcmp(weather, "多云") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_duoyun, 2);
  }
  else if (strcmp(weather, "阴") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_yin, 1);
  }
  else if (strcmp(weather, "有风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_youfeng, 2);
  }
  else if (strcmp(weather, "微风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_weifeng, 2);
  }
  else if (strcmp(weather, "和风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_hefeng, 2);
  }
  else if (strcmp(weather, "清风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_qingfeng, 2);
  }
  else if (strcmp(weather, "强风/劲风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_qiangfeng, 2);
  }
  else if (strcmp(weather, "疾风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_jifeng, 2);
  }
  else if (strcmp(weather, "大风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_dafeng, 2);
  }
  else if (strcmp(weather, "烈风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_liefeng, 2);
  }
  else if (strcmp(weather, "风暴") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_fengbao, 2);
  }
  else if (strcmp(weather, "狂暴风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_kuangbaofeng, 3);
  }
  else if (strcmp(weather, "飓风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_jufeng, 2);
  }
  else if (strcmp(weather, "热带风暴") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_redaifengbao, 4);
  }
  else if (strcmp(weather, "平静") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_pingjing, 2);
  }
  else if (strcmp(weather, "霾") == 0 || strcmp(weather, "中度霾") == 0 || strcmp(weather, "重度霾") == 0 || strcmp(weather, "严重霾") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_mai, 1);
  }
  else if (strcmp(weather, "阵雨") == 0 || strcmp(weather, "雷阵雨") == 0 || strcmp(weather, "雷阵雨并伴有冰雹") == 0 || strcmp(weather, "大暴雨") == 0 || strcmp(weather, "特大暴雨") == 0 || strcmp(weather, "强阵雨") == 0 || strcmp(weather, "强雷阵雨") == 0 || strcmp(weather, "极端降雨") == 0 || strcmp(weather, "毛毛雨/细雨") == 0 || strcmp(weather, "雨") == 0 || strcmp(weather,"小雨-中雨") == 0|| strcmp(weather, "中雨-大雨") == 0 || strcmp(weather, "大雨-暴雨") == 0 || strcmp(weather, "暴雨-大暴雨") == 0 || strcmp(weather, "大暴雨-特大暴雨") == 0 || strcmp(weather, "雨雪天气") == 0 || strcmp(weather, "雨夹雪") == 0 || strcmp(weather, "阵雨夹雪") == 0 || strcmp(weather, "冻雨") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_yu, 1);
  }
  else if (strcmp(weather, "小雨") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_xiaoyu, 2);
  }
  else if (strcmp(weather, "中雨") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_zhongyu, 2);
  }
  else if (strcmp(weather, "大雨") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_dayu, 2);
  }
  else if (strcmp(weather, "暴雨") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_baoyu, 2);
  }
  else if (strcmp(weather, "雪") == 0 || strcmp(weather, "阵雪") == 0 || strcmp(weather, "小雪") == 0 || strcmp(weather, "中雪") == 0 || strcmp(weather, "大雪") == 0 || strcmp(weather, "暴雪") == 0 || strcmp(weather, "小雪-中雪") == 0 || strcmp(weather, "中雪-大雪") == 0 || strcmp(weather, "大雪-暴雪") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_xue, 1);
  }
  else if (strcmp(weather, "浮尘") == 0 || strcmp(weather, "扬沙") == 0 || strcmp(weather, "沙尘暴") == 0 || strcmp(weather, "强沙尘暴") == 0 || strcmp(weather, "龙卷风") == 0)
  {
      OLED_Show_Char_CN(2, 6, font_fuchen, 2);
  }
  else if (strcmp(weather, "雾") == 0 || strcmp(weather, "浓雾") == 0 || strcmp(weather, "强浓雾") == 0 || strcmp(weather, "轻雾") == 0 || strcmp(weather, "大雾") == 0 || strcmp(weather, "特强大雾") == 0 )
  {
      OLED_Show_Char_CN(2, 6, font_wu, 1);
  }
  else
  {
      OLED_Show_Char_CN(2, 6, font_weizhi, 2);
  }
}


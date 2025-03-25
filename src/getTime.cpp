#include "getTime.h"

// 替换为您的 WiFi 网络名称和密码

#ifdef _CAMPUS_NET
const char* ssid     = "HQU";
const char* username = "2215105045";
const char* password = "Zy296428";
#else
const char* ssid     = "Xiaomi_B506"; 
const char* password = "zhx654321";
#endif

// 定义 NTP 客户端以获取时间
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 8 * 3600, 60000);  // 8*3600 是时区偏移量（北京时间）

int month = 0;
int day = 0;
int hour = 0;
int minute = 0;

int lastMonth = 0;
int lastDay = 0;  
int lastHour = 0;
int lastMinute = 0;

int counter = 0;

void WiFi_init(void)  
{
  WiFi.disconnect(true);  // 断开现有 Wi-Fi 连接
  WiFi.mode(WIFI_STA);    // 设置 Wi-Fi 模式为 STA（客户端模式）
  
  #ifdef _CAMPUS_NET   // 使用WPA2-企业认证连接WiFi
    struct station_config config;
    memset(&config, 0, sizeof(config));
    strcpy(reinterpret_cast<char*>(config.ssid), ssid);
    wifi_station_set_config(&config);

    // 启用WPA2企业认证
    wifi_station_set_wpa2_enterprise_auth(1);

    wifi_station_set_enterprise_identity((uint8_t *)username, strlen(username)); 
    wifi_station_set_enterprise_username((uint8_t *)username, strlen(username)); 
    wifi_station_set_enterprise_password((uint8_t *)password, strlen(password));

    wifi_station_connect();
  #else   // 使用WAP2-个人认证连接WiFi（正常家用wifi）,只需设置正确的ssid和password
    WiFi.begin(ssid, password);
  #endif

  Serial.print("正在连接到 ");
  Serial.println(ssid);
  while ( WiFi.status() != WL_CONNECTED ) 
  {
    delay (500);
    Serial.print(".");
    counter++;
    if(counter >= 20)
    {
      Serial.println("WiFi 连接失败");
      ESP.restart();
      
    }
  }
  counter = 0;

  Serial.println("");
  Serial.println("WiFi 已连接");
  Serial.println("IP 地址: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();

  while(!timeClient.forceUpdate())
  {
    if(counter >= 20)
    {
      Serial.println("NTP 服务器连接失败，请检查网络连接或服务器地址。");
      ESP.restart();  // 重启设备以重新尝试
    }
    counter++;
  }
  counter = 0;
}

void getTime(void) 
{
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  
  // 获取时间结构
  time_t localEpochTime = epochTime; // 已经包含时区偏移量
  struct tm *ptm = gmtime(&localEpochTime);
  
  month = ptm->tm_mon + 1;
  day = ptm->tm_mday;
  hour = ptm->tm_hour;
  minute = ptm->tm_min;

  
}

void wifi_time_flush(void) 
{
  if (WiFi.status() != WL_CONNECTED)
  {
    wifi_station_connect();
    Serial.println("Wifi 连接失败，正在重连...");
    Serial.print("正在连接到 ");
    Serial.println(ssid);
    while ( WiFi.status() != WL_CONNECTED ) 
    {
      
      delay (500);
      Serial.print(".");
      counter++;
      if(counter >= 20)
      {
        Serial.println("WiFi 连接失败");
        ESP.restart();
        counter = 0;
      }
    }
  }
  
  getTime();

  int flag = 0;
  if(month != lastMonth)
  {
    flag = 1;
  }
  else if(day != lastDay)
  {
    flag = 2;
  }
  else if(hour != lastHour)
  {
    flag = 3;
  }
  else if(minute != lastMinute)
  {
    flag = 4;
  }
  else
  {
    return;
  }
  

  OLED_time_display(flag,month,day,hour,minute);
  
  lastMonth = month;
  lastDay = day;
  lastHour = hour;
  lastMinute = minute;

  // 格式化输出月日时分
  Serial.print(month);
  Serial.print("月");
  Serial.print(day);
  Serial.print("日 ");
  
  if (hour < 10) 
  {
    Serial.print("0");
  }
  Serial.print(hour);
  Serial.print(":");
  if (minute < 10) 
  {
    Serial.print("0");
  }
  Serial.println(minute);
  

  
}
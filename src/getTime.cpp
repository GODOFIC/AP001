#include "getTime.h"

extern uint8_t Row;
extern uint8_t Column;

// 替换为您的 WiFi 网络名称和密码
const char* ssid     = "HQU";
const char* username = "学号";
const char* password = "校园网密码";


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
  
  #if 1   // 使用WPA2-企业认证连接WiFi
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

void OLED_displayTime(void) 
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
  
  // case中没有break会继续执行之后的case代码
  // 如果月改变更新所有时间项
  // 如果日改变更新日时分
  // 以此类推
  // 可以实现在分改变时仅刷新OLED上的分而不刷新其他项
  
  int sizeOfMonth = (month >= 10) ? 2 : 1;
  int sizeOfDay = (day >= 10) ? 2 : 1;
  
  switch (flag) 
  {
    case 1:
        OLED_Show_SignedNum(4, 1, month, sizeOfMonth);
        OLED_Show_Char_CN(4, (1 + sizeOfMonth), font_month, 1);

    case 2:
        OLED_Show_SignedNum(4, (3 + sizeOfMonth), day, sizeOfDay);
        OLED_Show_Char_CN(4, (3 + sizeOfMonth + sizeOfDay), font_day, 1);
        OLED_Show_Char(4, (5 + sizeOfMonth + sizeOfDay), ' ');

    case 3:
        if (hour < 10) 
        {
            OLED_Show_Char(4, (6 + sizeOfMonth + sizeOfDay), '0');
            OLED_Show_SignedNum(4, (7 + sizeOfMonth + sizeOfDay), hour, 1);
        } 
        else 
        {
            OLED_Show_SignedNum(4, (6 + sizeOfMonth + sizeOfDay), hour, 2);
        }
        OLED_Show_Char(4, (8 + sizeOfMonth + sizeOfDay), ':');

    case 4:
        
        if (minute < 10) 
        {
            OLED_Show_Char(4, (9 + sizeOfMonth + sizeOfDay), '0');
            OLED_Show_SignedNum(4, (10 + sizeOfMonth + sizeOfDay), minute, 1);
        } 
        else 
        {
            OLED_Show_SignedNum(4, (9 + sizeOfMonth + sizeOfDay), minute, 2);
        }

        // 确保后面没有其他显示
        OLED_Clear(4, (11 + sizeOfMonth + sizeOfDay), (16 - (11 + sizeOfMonth + sizeOfDay) + 1));
        break;

    default:
        break;
}
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
  

  // 如果OLED显示因为未知原因时不时出现整体向下移动的情况启用下列代码
  #if 1
  
  OLED_Write_Command(0x40); //重新刷新显示开始行

  #endif
}
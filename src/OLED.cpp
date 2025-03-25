#include "OLED.h"

// OLED写命令
bool OLED_Write_Command(uint8_t command) 
{
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(0x00); // 命令模式
  Wire.write(command);
  uint8_t status = Wire.endTransmission();
  
  if (status != 0) {
    Serial.printf("OLED_Write_Command Error: %d\n", status);
    return false;
  }
  return true;
}

// OLED写数据
bool OLED_Write_Data(uint8_t data) 
{
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(0x40); // 数据模式
  Wire.write(data);
  uint8_t status = Wire.endTransmission();
  
  if (status != 0) {
    Serial.printf("OLED_Write_Data Error: %d\n", status);
    return false;
  }
  return true;
}

// 批量写入数据
bool OLED_Write_Data_Batch(const uint8_t* data, uint8_t length) 
{
  if (length > 32) { // Wire库缓冲区大小通常为32字节
    uint8_t chunks = length / 30; // 留出空间给控制字节
    uint8_t remainder = length % 30;
    
    for (uint8_t i = 0; i < chunks; i++) {
      Wire.beginTransmission(OLED_ADDR);
      Wire.write(0x40); // 数据模式
      for (uint8_t j = 0; j < 30; j++) {
        Wire.write(data[i * 30 + j]);
      }
      uint8_t status = Wire.endTransmission();
      if (status != 0) {
        Serial.printf("OLED_Write_Data_Batch Error: %d\n", status);
        return false;
      }
    }
    
    if (remainder > 0) {
      Wire.beginTransmission(OLED_ADDR);
      Wire.write(0x40); // 数据模式
      for (uint8_t j = 0; j < remainder; j++) {
        Wire.write(data[chunks * 30 + j]);
      }
      uint8_t status = Wire.endTransmission();
      if (status != 0) {
        Serial.printf("OLED_Write_Data_Batch Error: %d\n", status);
        return false;
      }
    }
    
    return true;
  } else {
    Wire.beginTransmission(OLED_ADDR);
    Wire.write(0x40); // 数据模式
    for (uint8_t i = 0; i < length; i++) {
      Wire.write(data[i]);
    }
    uint8_t status = Wire.endTransmission();
    
    if (status != 0) {
      Serial.printf("OLED_Write_Data_Batch Error: %d\n", status);
      return false;
    }
    return true;
  }
}

// OLED设置光标位置
// Y 以左上角为原点，向下方向的坐标，范围：0~7
// X 以左上角为原点，向右方向的坐标，范围：0~127
bool OLED_Set_Cursor(uint8_t Y, uint8_t X) 
{
  if(Y >= OLED_PAGES) {
    Serial.printf("OLED_Set_Cursor() Error: Y out of range (0-%d), got %d\n", OLED_PAGES-1, Y);
    return false;
  }
  if(X >= OLED_WIDTH) {
    Serial.printf("OLED_Set_Cursor() Error: X out of range (0-%d), got %d\n", OLED_WIDTH-1, X);
    return false;
  }
  
  if(!OLED_Write_Command(0xB0 + Y)) return false;
  if(!OLED_Write_Command(0x00 + (X & 0x0F))) return false;
  if(!OLED_Write_Command(0x10 + ((X & 0xF0) >> 4))) return false;
  
  return true;
}

// OLED全部清屏
bool OLED_ClearAll(void) 
{
  uint8_t j;
  uint8_t zeroBuffer[128] = {0}; // 创建一个全0的缓冲区
  
  for (j = 0; j < OLED_PAGES; j++) 
  {
    if(!OLED_Set_Cursor(j, 0)) return false;
    if(!OLED_Write_Data_Batch(zeroBuffer, 128)) return false;
  }
  return true;
}

// OLED分区清除
// Line 行（1~4）
// Column 列（1~16）
// Length 要清除的长度(1~16)
// 1个Length清除一行一列
bool OLED_Clear(uint8_t Line, uint8_t Column, uint8_t Length) 
{
  if(Line < 1 || Line > 4) {
    Serial.printf("OLED_Clear() Error: Line out of range (1-4), got %d\n", Line);
    return false;
  }
  if(Column < 1 || Column > 16) {
    Serial.printf("OLED_Clear() Error: Column out of range (1-16), got %d\n", Column);
    return false;
  }
  if(Length < 1 || Length > 16 || Column + Length - 1 > 16) {
    Serial.printf("OLED_Clear() Error: Invalid length %d at column %d\n", Length, Column);
    return false;
  }
  
  uint8_t zeroBuffer[128] = {0};
  uint8_t dataLength = Length * 8;
  
  // 清除上半部分
  if(!OLED_Set_Cursor((Line - 1) * 2, (Column - 1) * 8)) return false;
  if(!OLED_Write_Data_Batch(zeroBuffer, dataLength)) return false;
  
  // 清除下半部分
  if(!OLED_Set_Cursor((Line - 1) * 2 + 1, (Column - 1) * 8)) return false;
  if(!OLED_Write_Data_Batch(zeroBuffer, dataLength)) return false;
  
  return true;
}

// OLED显示一个字符
// Line 行（1~4）
// Column 列（1~16）
// Char 要显示的字符（ASCII可见字符）
bool OLED_Show_Char(uint8_t Line, uint8_t Column, char Char)
{
  if(Line < 1 || Line > 4) {
    Serial.printf("OLED_Show_Char() Error: Line out of range (1-4), got %d\n", Line);
    return false;
  }
  if(Column < 1 || Column > 16) {
    Serial.printf("OLED_Show_Char() Error: Column out of range (1-16), got %d\n", Column);
    return false;
  }
  if(Char < ' ' || Char > '~') {
    Serial.printf("OLED_Show_Char() Error: Character out of range (ASCII 32-126), got %d\n", Char);
    return false;
  }
  
  // 上半部分
  if(!OLED_Set_Cursor((Line - 1) * 2, (Column - 1) * 8)) return false;
  if(!OLED_Write_Data_Batch(&OLED_F8x16[Char - ' '][0], 8)) return false;
  
  // 下半部分
  if(!OLED_Set_Cursor((Line - 1) * 2 + 1, (Column - 1) * 8)) return false;
  if(!OLED_Write_Data_Batch(&OLED_F8x16[Char - ' '][8], 8)) return false;
  
  return true;
}

// OLED显示一个中文字
// Line 行（1~4）
// Column 列（1~15）
// font[][16] 中文字符数组
// Length 要显示的字数(1~8)
bool OLED_Show_Char_CN(uint8_t Line, uint8_t Column, const uint8_t font[][16], uint8_t Length)
{
  if(Line < 1 || Line > 4) {
    Serial.printf("OLED_Show_Char_CN() Error: Line out of range (1-4), got %d\n", Line);
    return false;
  }
  if(Column < 1 || Column > 15) {
    Serial.printf("OLED_Show_Char_CN() Error: Column out of range (1-15), got %d\n", Column);
    return false;
  }
  if(Length < 1 || Length > 8 || Column + Length*2 - 1 > 16) {
    Serial.printf("OLED_Show_Char_CN() Error: Invalid length %d at column %d\n", Length, Column);
    return false;
  }
  
  for(uint8_t j = 0; j < Length; j++) {
    uint8_t currentCol = Column + j*2;
    uint8_t fontIdx = j*2;
    
    // 上半部分
    if(!OLED_Set_Cursor((Line - 1) * 2, (currentCol - 1) * 8)) return false;
    if(!OLED_Write_Data_Batch(font[fontIdx], 16)) return false;
    
    // 下半部分
    if(!OLED_Set_Cursor((Line - 1) * 2 + 1, (currentCol - 1) * 8)) return false;
    if(!OLED_Write_Data_Batch(font[fontIdx + 1], 16)) return false;
  }
  
  return true;
}

// OLED显示字符串
// Line 行（1~4）
// Column 列（1~16）
// String 要显示的字符串
bool OLED_Show_String(uint8_t Line, uint8_t Column, char *String)
{
  if(Line < 1 || Line > 4) {
    Serial.printf("OLED_Show_String() Error: Line out of range (1-4), got %d\n", Line);
    return false;
  }
  if(Column < 1 || Column > 16) {
    Serial.printf("OLED_Show_String() Error: Column out of range (1-16), got %d\n", Column);
    return false;
  }
  
  uint8_t i;
  for (i = 0; String[i] != '\0' && Column + i <= 16; i++) {
    if(!OLED_Show_Char(Line, Column + i, String[i])) return false;
  }
  
  return true;
}

// OLED次方函数
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
  uint32_t Result = 1;
  while (Y--) {
    Result *= X;
  }
  return Result;
}

// OLED显示数字（十进制，带符号数）
// Line 起始行位置，范围：1~4
// Column 起始列位置，范围：1~16
// Number 要显示的数字，范围：-2147483648~2147483647
// Length 要显示数字的长度，范围：1~10
bool OLED_Show_SignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
  if(Line < 1 || Line > 4) {
    Serial.printf("OLED_Show_SignedNum() Error: Line out of range (1-4), got %d\n", Line);
    return false;
  }
  if(Column < 1 || Column > 16) {
    Serial.printf("OLED_Show_SignedNum() Error: Column out of range (1-16), got %d\n", Column);
    return false;
  }
  if(Length < 1 || Length > 10) {
    Serial.printf("OLED_Show_SignedNum() Error: Length out of range (1-10), got %d\n", Length);
    return false;
  }
  
  uint8_t Column1;
  uint32_t tempNumber;
  
  // 检查负数是否需要额外一位显示'-'符号
  if (Number < 0 && Column + Length > 16) {
    Serial.printf("OLED_Show_SignedNum() Error: Not enough space for negative number\n");
    return false;
  }
  
  if (Number >= 0) {
    Column1 = Column;
    tempNumber = Number;
  } else {
    if(!OLED_Show_Char(Line, Column, '-')) return false;
    tempNumber = -Number;
    Column1 = Column + 1;
  }
  
  // 数字前面的位补零
  for (uint8_t i = 0; i < Length; i++) {
    if(Column1 + i > 16) {
      Serial.printf("OLED_Show_SignedNum() Error: Number exceeds display width\n");
      return false;
    }
    
    uint8_t digit = tempNumber / OLED_Pow(10, Length - i - 1) % 10;
    if(!OLED_Show_Char(Line, Column1 + i, digit + '0')) return false;
  }
  
  return true;
}

// OLED清除矩形区域
// startLine, startColumn: 起始行列位置(1-4, 1-16)
// endLine, endColumn: 结束行列位置(1-4, 1-16)
bool OLED_Clear_Rect(uint8_t startLine, uint8_t startColumn, uint8_t endLine, uint8_t endColumn)
{
  if(startLine < 1 || startLine > 4 || endLine < 1 || endLine > 4 || startLine > endLine) {
    Serial.printf("OLED_Clear_Rect() Error: Line out of range (1-4), got %d-%d\n", startLine, endLine);
    return false;
  }
  if(startColumn < 1 || startColumn > 16 || endColumn < 1 || endColumn > 16 || startColumn > endColumn) {
    Serial.printf("OLED_Clear_Rect() Error: Column out of range (1-16), got %d-%d\n", startColumn, endColumn);
    return false;
  }
  
  for(uint8_t line = startLine; line <= endLine; line++) {
    if(!OLED_Clear(line, startColumn, endColumn - startColumn + 1)) return false;
  }
  
  return true;
}

// OLED初始化
bool OLED_Init(void)
{
  // 共享I2C总线已在main.cpp中初始化
  delay(200);  // 等待OLED上电稳定
  
  // OLED初始化命令序列
  if(!OLED_Write_Command(0xAE)) return false;  // 关闭显示
  
  if(!OLED_Write_Command(0xD5)) return false;  // 设置显示时钟分频比/振荡器频率
  if(!OLED_Write_Command(0x80)) return false;
  
  if(!OLED_Write_Command(0xA8)) return false;  // 设置多路复用率
  if(!OLED_Write_Command(0x3F)) return false;
  
  if(!OLED_Write_Command(0xD3)) return false;  // 设置显示偏移
  if(!OLED_Write_Command(0x00)) return false;
  
  if(!OLED_Write_Command(0x40)) return false;  // 设置显示开始行
  
  if(!OLED_Write_Command(0xA1)) return false;  // 设置左右方向，0xA1正常 0xA0左右反置
  
  if(!OLED_Write_Command(0xC8)) return false;  // 设置上下方向，0xC8正常 0xC0上下反置

  if(!OLED_Write_Command(0xDA)) return false;  // 设置COM引脚硬件配置
  if(!OLED_Write_Command(0x12)) return false;
  
  if(!OLED_Write_Command(0x81)) return false;  // 设置对比度控制
  if(!OLED_Write_Command(0xCF)) return false;

  if(!OLED_Write_Command(0xD9)) return false;  // 设置预充电周期
  if(!OLED_Write_Command(0xF1)) return false;

  if(!OLED_Write_Command(0xDB)) return false;  // 设置VCOMH取消选择级别
  if(!OLED_Write_Command(0x30)) return false;

  if(!OLED_Write_Command(0xA4)) return false;  // 设置整个显示打开/关闭

  if(!OLED_Write_Command(0xA6)) return false;  // 设置正常/倒转显示

  if(!OLED_Write_Command(0x8D)) return false;  // 设置充电泵
  if(!OLED_Write_Command(0x14)) return false;

  if(!OLED_Write_Command(0xAF)) return false;  // 开启显示
    
  if(!OLED_ClearAll()) return false;           // OLED清屏
  
  // 显示温湿度提示信息
  if(!OLED_Show_Char_CN(4, 1, font_temperature, 2)) return false;
  if(!OLED_Show_Char(4, 5, ':')) return false;
  
  if(!OLED_Show_Char_CN(4, 9, font_humidity, 2)) return false;
  if(!OLED_Show_Char(4, 13, ':')) return false;

  // 显示"天气:"
  OLED_Show_Char_CN(3, 1, font_tianqi, 2); 
  OLED_Show_Char(3, 5, ':'); 

  // 显示风扇档位提示信息
  if(!OLED_Show_Char_CN(2, 1, font_FanStatus, 4)) return false; // 显示"风扇状态"
  if(!OLED_Show_Char(2, 9, ':')) return false; // 显示":"
  if(!OLED_Show_Char_CN(2, 10, font_Off, 2)) return false; // 显示"关闭"
  
  
  return true;
}

void OLED_AHT20_display(int32_t tem,int32_t hum)
{
  if((tem >= 100) || (hum >= 100) || (tem < 0) || (hum < 0))
  {
    Serial.println("Invalid temperature or humidity value");
    return;
  }

  static int32_t lastTemperature = 0;
  static int32_t lastHumidity = 0;

  bool needUpdate = false;
  
  // 检查温度或湿度是否变化
  if((tem != lastTemperature) || (hum != lastHumidity)) 
  {
    needUpdate = true;
  }
  
  // 只有在需要更新时才进行显示刷新
  if(needUpdate)
  {
    // 更新温度显示
    if(!OLED_Clear(4, 6, 2)) {
      Serial.println("Failed to clear temperature area");
      return;
    }
    if(!OLED_Show_SignedNum(4, 6, tem, 2)) {
      Serial.println("Failed to show temperature");
      return;
    }
    
    // 更新湿度显示
    if(!OLED_Clear(4, 14, 2)) {
      Serial.println("Failed to clear humidity area");
      return;
    }
    if(!OLED_Show_SignedNum(4, 14, hum, 2)) {
      Serial.println("Failed to show humidity");
      return;
    }
    
    // 更新上次记录的值
    lastTemperature = tem;
    lastHumidity = hum;
  }
}

// flag表示风扇开关状态
void OLED_fan_speed_display(int level, bool flag)
{
  if(!flag)
  {
    OLED_Clear(2, 10, 4); //清除Line 3 后 4 Column的内容
    OLED_Show_Char_CN(2, 10, font_Off, 2); // 显示“关闭”
    return;
  }
  
  OLED_Clear(2, 10, 4); //清除Line 3 后 4 Column的内容

  switch (level)
  {
  case 0:
    OLED_Show_Char_CN(2, 10, font_low, 2);
    break;
  case 1:
    OLED_Show_Char_CN(2, 10, font_middle, 2);
    break;
  case 2:
    OLED_Show_Char_CN(2, 10, font_high, 2);
    break;
  case 3:
    OLED_Show_Char_CN(2, 10, font_superstrong, 2);
    break;
  default:
    Serial.print(" OLED fan level error!");
    break;
  }
}

// case中没有break会继续执行之后的case代码
  // 如果月改变更新所有时间项
  // 如果日改变更新日时分
  // 以此类推
  // 可以实现在分改变时仅刷新OLED上的分而不刷新其他项

void OLED_time_display(int flag, int month, int day, int hour, int minute)
{
  int sizeOfMonth = (month >= 10) ? 2 : 1;
  int sizeOfDay = (day >= 10) ? 2 : 1;

  switch (flag) 
  {
    case 1:
        OLED_Show_SignedNum(1, 1, month, sizeOfMonth);
        OLED_Show_Char_CN(1, (1 + sizeOfMonth), font_month, 1);

    case 2:
        OLED_Show_SignedNum(1, (3 + sizeOfMonth), day, sizeOfDay);
        OLED_Show_Char_CN(1, (3 + sizeOfMonth + sizeOfDay), font_day, 1);
        OLED_Show_Char(1, (5 + sizeOfMonth + sizeOfDay), ' ');

    case 3:
        if (hour < 10) 
        {
            OLED_Show_Char(1, (6 + sizeOfMonth + sizeOfDay), '0');
            OLED_Show_SignedNum(1, (7 + sizeOfMonth + sizeOfDay), hour, 1);
        } 
        else 
        {
            OLED_Show_SignedNum(1, (6 + sizeOfMonth + sizeOfDay), hour, 2);
        }
        OLED_Show_Char(1, (8 + sizeOfMonth + sizeOfDay), ':');

    case 4:
        
        if (minute < 10) 
        {
            OLED_Show_Char(1, (9 + sizeOfMonth + sizeOfDay), '0');
            OLED_Show_SignedNum(1, (10 + sizeOfMonth + sizeOfDay), minute, 1);
        } 
        else 
        {
            OLED_Show_SignedNum(1, (9 + sizeOfMonth + sizeOfDay), minute, 2);
        }

        // 确保后面没有其他显示
        OLED_Clear(1, (11 + sizeOfMonth + sizeOfDay), (16 - (11 + sizeOfMonth + sizeOfDay) + 1));
        break;

    default:
        break;
  }

  // 如果OLED显示因为未知原因时不时出现整体向下移动的情况启用下列代码
  #if 1
  
  OLED_Write_Command(0x40); //重新刷新显示开始行

  #endif
}

void OLED_weather_display(const char* lastWeather, const char* weather)
{
  if(strcmp(lastWeather, weather) == 0)
  {
    return ;
  }
  
  OLED_Clear(3, 6, 11);

  if (strcmp(weather, "晴") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_qing, 1);
  }
  else if (strcmp(weather, "少云") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_shaoyun, 2);
  }
  else if (strcmp(weather, "晴间多云") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_qingjianduoyun, 4);
  }
  else if (strcmp(weather, "多云") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_duoyun, 2);
  }
  else if (strcmp(weather, "阴") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_yin, 1);
  }
  else if (strcmp(weather, "有风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_youfeng, 2);
  }
  else if (strcmp(weather, "微风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_weifeng, 2);
  }
  else if (strcmp(weather, "和风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_hefeng, 2);
  }
  else if (strcmp(weather, "清风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_qingfeng, 2);
  }
  else if (strcmp(weather, "强风/劲风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_qiangfeng, 2);
  }
  else if (strcmp(weather, "疾风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_jifeng, 2);
  }
  else if (strcmp(weather, "大风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_dafeng, 2);
  }
  else if (strcmp(weather, "烈风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_liefeng, 2);
  }
  else if (strcmp(weather, "风暴") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_fengbao, 2);
  }
  else if (strcmp(weather, "狂暴风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_kuangbaofeng, 3);
  }
  else if (strcmp(weather, "飓风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_jufeng, 2);
  }
  else if (strcmp(weather, "热带风暴") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_redaifengbao, 4);
  }
  else if (strcmp(weather, "平静") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_pingjing, 2);
  }
  else if (strcmp(weather, "霾") == 0 || strcmp(weather, "中度霾") == 0 || strcmp(weather, "重度霾") == 0 || strcmp(weather, "严重霾") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_mai, 1);
  }
  else if (strcmp(weather, "阵雨") == 0 || strcmp(weather, "雷阵雨") == 0 || strcmp(weather, "雷阵雨并伴有冰雹") == 0 || strcmp(weather, "大暴雨") == 0 || strcmp(weather, "特大暴雨") == 0 || strcmp(weather, "强阵雨") == 0 || strcmp(weather, "强雷阵雨") == 0 || strcmp(weather, "极端降雨") == 0 || strcmp(weather, "毛毛雨/细雨") == 0 || strcmp(weather, "雨") == 0 || strcmp(weather,"小雨-中雨") == 0|| strcmp(weather, "中雨-大雨") == 0 || strcmp(weather, "大雨-暴雨") == 0 || strcmp(weather, "暴雨-大暴雨") == 0 || strcmp(weather, "大暴雨-特大暴雨") == 0 || strcmp(weather, "雨雪天气") == 0 || strcmp(weather, "雨夹雪") == 0 || strcmp(weather, "阵雨夹雪") == 0 || strcmp(weather, "冻雨") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_yu, 1);
  }
  else if (strcmp(weather, "小雨") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_xiaoyu, 2);
  }
  else if (strcmp(weather, "中雨") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_zhongyu, 2);
  }
  else if (strcmp(weather, "大雨") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_dayu, 2);
  }
  else if (strcmp(weather, "暴雨") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_baoyu, 2);
  }
  else if (strcmp(weather, "雪") == 0 || strcmp(weather, "阵雪") == 0 || strcmp(weather, "小雪") == 0 || strcmp(weather, "中雪") == 0 || strcmp(weather, "大雪") == 0 || strcmp(weather, "暴雪") == 0 || strcmp(weather, "小雪-中雪") == 0 || strcmp(weather, "中雪-大雪") == 0 || strcmp(weather, "大雪-暴雪") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_xue, 1);
  }
  else if (strcmp(weather, "浮尘") == 0 || strcmp(weather, "扬沙") == 0 || strcmp(weather, "沙尘暴") == 0 || strcmp(weather, "强沙尘暴") == 0 || strcmp(weather, "龙卷风") == 0)
  {
      OLED_Show_Char_CN(3, 6, font_fuchen, 2);
  }
  else if (strcmp(weather, "雾") == 0 || strcmp(weather, "浓雾") == 0 || strcmp(weather, "强浓雾") == 0 || strcmp(weather, "轻雾") == 0 || strcmp(weather, "大雾") == 0 || strcmp(weather, "特强大雾") == 0 )
  {
      OLED_Show_Char_CN(3, 6, font_wu, 1);
  }
  else
  {
      OLED_Show_Char_CN(3, 6, font_weizhi, 2);
  }
}
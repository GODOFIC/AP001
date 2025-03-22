#include "OLED.h"

// I2C 开始信号
void OLED_i2c_start(void) 
{

  digitalWrite(OLED_SDA, HIGH);
  digitalWrite(OLED_SCK, HIGH);
  delayMicroseconds(4);
  digitalWrite(OLED_SDA, LOW);
  delayMicroseconds(4);
  digitalWrite(OLED_SCK, LOW);
  delayMicroseconds(4);
}

// I2C 停止信号
void OLED_i2c_stop(void) 
{
  
  digitalWrite(OLED_SDA, LOW);
  digitalWrite(OLED_SCK, HIGH);
  delayMicroseconds(4);
  digitalWrite(OLED_SDA, HIGH);
  delayMicroseconds(4);
}


// I2C 发送字节
void OLED_i2c_write_byte(uint8_t byte)
 {
  for (int i = 0; i < 8; i++) 
  {   
    digitalWrite(OLED_SDA, (byte & 0x80) ? HIGH : LOW);  // 发送字节的每一位
    delayMicroseconds(4);
    digitalWrite(OLED_SCK, HIGH);
    delayMicroseconds(4);
    digitalWrite(OLED_SCK, LOW);
    delayMicroseconds(4);
    byte <<= 1;
   }
    digitalWrite(OLED_SCK, HIGH);   //额外的一个时钟，不处理应答信号
    digitalWrite(OLED_SCK, LOW);
}

// OLED写命令
void OLED_Write_Command(uint8_t command) 
{
  OLED_i2c_start();
  OLED_i2c_write_byte(0x78);
  OLED_i2c_write_byte(0x00);
  OLED_i2c_write_byte(command);
  OLED_i2c_stop();
}

// OLED写数据
void OLED_Write_Data(uint8_t data) 
{
  OLED_i2c_start();
  OLED_i2c_write_byte(0x78);
  OLED_i2c_write_byte(0x40);
  OLED_i2c_write_byte(data);
  OLED_i2c_stop();
}

// OLED设置光标位置
//Y 以左上角为原点，向下方向的坐标，范围：0~7
//X 以左上角为原点，向右方向的坐标，范围：0~127
void OLED_Set_Cursor(uint8_t Y, uint8_t X) 
{
  if(Y > 7)
  {
    Serial.print("OLED_Set_Cursor() Error: Y out of range\n");
    return;
  }
  if(X > 127)
  {
    Serial.print("OLED_Set_Cursor() Error: X out of range\n");
    return;
  }
  
  OLED_Write_Command(0xB0 + Y);  
  OLED_Write_Command(0x00 + (X & 0x0F));  
  OLED_Write_Command(0x10 + ((X & 0xF0) >> 4)); 
}

// OLED全部清屏
void OLED_ClearAll(void) 
{
  uint8_t i, j;
  for (j = 0; j < 8; j++) 
  {
    OLED_Set_Cursor(j, 0);
    for (i = 0; i < 128; i++) 
    {
      OLED_Write_Data(0x00);
    }
  }
}

// OLED分区清除
// Line 行（1~4）
// Column 列（1~16）
// Length 要清除的长度(1~16)
// 1个Length清除一行一列
void OLED_Clear(uint8_t Line, uint8_t Column,uint8_t Length) 
{
  uint8_t i;
 
  OLED_Set_Cursor((Line - 1) * 2, (Column - 1) * 8);
  for (i = 0; i < (Length * 8); i++) 
    {
      OLED_Write_Data(0x00);
    }
  OLED_Set_Cursor((Line - 1) * 2 + 1, (Column - 1) * 8);
  for (i = 0; i < (Length * 8); i++) 
    {
      OLED_Write_Data(0x00);
    }
    
  
}

// OLED显示一个字符
// Line 行（1~4）
// Column 列（1~16）
// Char 要显示的字符（ASCII可见字符）
void OLED_Show_Char(uint8_t Line, uint8_t Column, char Char)
{
  uint8_t i;
  OLED_Set_Cursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
  for (i = 0; i < 8; i++)
	{
	  OLED_Write_Data(OLED_F8x16[Char - ' '][i]);			//显示上半部分内容
	}
  OLED_Set_Cursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
  for (i = 0; i < 8; i++)
	{
		OLED_Write_Data(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内容
	}
}

// OLED显示一个中文字
// Line 行（1~4）
// Column 列（1~15）
// font[][16] 中文字符数组
// Length 要显示的长度(1~8)
// 必须确保一行剩余能写的长度不小于要写的长度
void OLED_Show_Char_CN(uint8_t Line, uint8_t Column, const uint8_t font[][16], uint8_t Length)
{
  uint8_t i, j;
  for(j = 0; j < (2 * Length); j+=2)
  {
    OLED_Set_Cursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
    for (i = 0; i < 16; i++)
    {
      OLED_Write_Data(font[j][i]);			//显示上半部分内容
    }
      OLED_Set_Cursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	  for (i = 0; i < 16; i++)
	  {
		  OLED_Write_Data(font[j + 1][i]);		//显示下半部分内容
	  }

    Column += 2;
  }
}

// OLED显示字符串
// Line 行（1~4）
// Column 列（1~15）
void OLED_Show_String(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_Show_Char(Line, Column + i, String[i]);
	}
}

// OLED次方函数
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

//  OLED显示数字（十进制，带符号数）
//  Line 起始行位置，范围：1~4
//  Column 起始列位置，范围：1~16
//  Number 要显示的数字，范围：-2147483648~2147483647
//  Length 要显示数字的长度，范围：1~10
void OLED_Show_SignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
  uint8_t Column1;
	uint32_t tempNumber;
	if (Number >= 0)
	{
		Column1 = Column;
		tempNumber = Number;
	}
	else
	{
		OLED_Show_Char(Line, Column, '-');
		tempNumber = -Number;
    Column1 = Column + 1;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_Show_Char(Line, Column1 + i, tempNumber / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

void OLED_Init(void)
{
  pinMode(OLED_SDA, OUTPUT_OPEN_DRAIN);
  pinMode(OLED_SCK, OUTPUT_OPEN_DRAIN);

  digitalWrite(OLED_SDA, HIGH);
  digitalWrite(OLED_SCK, HIGH);
  
  delay(200);
	
	OLED_Write_Command(0xAE);	//关闭显示
	
	OLED_Write_Command(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_Write_Command(0x80);
	
	OLED_Write_Command(0xA8);	//设置多路复用率
	OLED_Write_Command(0x3F);
	
	OLED_Write_Command(0xD3);	//设置显示偏移
	OLED_Write_Command(0x00);
	
	OLED_Write_Command(0x40);	//设置显示开始行
	
	OLED_Write_Command(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_Write_Command(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_Write_Command(0xDA);	//设置COM引脚硬件配置
	OLED_Write_Command(0x12);
	
	OLED_Write_Command(0x81);	//设置对比度控制
	OLED_Write_Command(0xCF);

	OLED_Write_Command(0xD9);	//设置预充电周期
	OLED_Write_Command(0xF1);

	OLED_Write_Command(0xDB);	//设置VCOMH取消选择级别
	OLED_Write_Command(0x30);

	OLED_Write_Command(0xA4);	//设置整个显示打开/关闭

	OLED_Write_Command(0xA6);	//设置正常/倒转显示

	OLED_Write_Command(0x8D);	//设置充电泵
	OLED_Write_Command(0x14);

	OLED_Write_Command(0xAF);	//开启显示
		
	OLED_ClearAll();				//OLED清屏
  
  // 显示温湿度提示信息
	OLED_Show_Char_CN(1, 1, font_temperature, 2);
	OLED_Show_Char(1, 5, ':');
  OLED_Show_Char_CN(1, 6, font_waitToMeasure, 4);
	
	OLED_Show_Char_CN(2, 1, font_humidity, 2);
	OLED_Show_Char(2, 5, ':');
  OLED_Show_Char_CN(2, 6, font_waitToMeasure, 4);

  // 显示风扇档位提示信息
  OLED_Show_Char_CN(3, 1, font_FanStatus, 4); // 显示“风扇状态”
  OLED_Show_Char(3, 9, ':'); // 显示“:”
  OLED_Show_Char_CN(3, 10, font_Off, 2); // 显示“关闭”

}



#include "AHT20_i2c.h"

int32_t temperature = 0; //温度
int32_t humidity = 0;//相对湿度

int32_t lastTemperature = 0; //上次温度
int32_t lastHumidity = 0;//上次湿度

// I2C 开始信号
void i2c_start(void) 
{

  digitalWrite(TH_SDA, HIGH);
  digitalWrite(TH_SCL, HIGH);
  delayMicroseconds(4);
  digitalWrite(TH_SDA, LOW);
  delayMicroseconds(4);
  digitalWrite(TH_SCL, LOW);
  delayMicroseconds(4);
}

// I2C 停止信号
void i2c_stop(void) 
{
  
  digitalWrite(TH_SDA, LOW);
  digitalWrite(TH_SCL, HIGH);
  delayMicroseconds(4);
  digitalWrite(TH_SDA, HIGH);
  delayMicroseconds(4);
}

// 发送 ACK（应答信号）
void send_ack(void) 
{
  
  digitalWrite(TH_SDA, LOW);  // 发送 ACK 信号，TH_SDA 拉低
  delayMicroseconds(4);
  digitalWrite(TH_SCL, HIGH);
  delayMicroseconds(4);
  
}

// 发送 NACK（非应答信号）
void send_nack(void) 
{
  
  digitalWrite(TH_SDA, HIGH);  // 发送 NACK 信号，TH_SDA 拉高
  delayMicroseconds(4);
  digitalWrite(TH_SCL, HIGH);
  delayMicroseconds(4);
  digitalWrite(TH_SCL, LOW);
  delayMicroseconds(4);
}

// 等待 ACK 信号
bool wait_for_ack(void)
 {
  digitalWrite(TH_SDA, HIGH);  // 准备接收 ACK
  delayMicroseconds(4);
  digitalWrite(TH_SCL, HIGH);
  delayMicroseconds(4);
  
  bool ack = !digitalRead(TH_SDA);  // 如果 TH_SDA 拉低，表示收到 ACK 
  
  
  return ack;
}

// I2C 发送字节
void i2c_write_byte(uint8_t byte)
 {
  digitalWrite(TH_SCL, LOW);  // 准备发送数据
  delayMicroseconds(4);
  
  for (int i = 0; i < 8; i++) 
  {   
    digitalWrite(TH_SDA, (byte & 0x80) ? HIGH : LOW);  // 发送字节的每一位
    delayMicroseconds(4);
    digitalWrite(TH_SCL, HIGH);
    delayMicroseconds(4);
    digitalWrite(TH_SCL, LOW);
    delayMicroseconds(4);
    byte <<= 1;
    
  }
}

// I2C 读取字节
uint8_t i2c_read_byte(void)
 {
  uint8_t byte = 0;
  digitalWrite(TH_SCL, LOW); // 准备接收数据
  delayMicroseconds(4);
   
  digitalWrite(TH_SDA, HIGH);
  for (int i = 0; i < 8; i++) 
  {
    digitalWrite(TH_SCL, HIGH);
    delayMicroseconds(4);
    byte <<= 1;
    if (digitalRead(TH_SDA)) 
    {
      byte |= 1;
    }
    digitalWrite(TH_SCL, LOW);
    delayMicroseconds(4);
  }
  
  return byte;
}

void AHT20_setup(void) 
{
  // 初始化
  pinMode(TH_SDA, OUTPUT_OPEN_DRAIN);
  pinMode(TH_SCL, OUTPUT_OPEN_DRAIN);
  delay(40);  // 上电后等待 40ms

  // 初始化传感器
  if (!isCalibrated()) 
  {
    initAHT20();  // 初始化传感器
  }
}

bool isCalibrated(void) 
{
  uint8_t status = readStatus();  // 读取状态字
  return status & 0x08;           // 检查 Bit[3] 是否为 1（校准使能位）
}

// 读取状态字
uint8_t readStatus(void) 
{
  uint8_t status;

  // 开始 I2C 通信
  i2c_start();
  i2c_write_byte(AHT20_ADDR << 1);  // 发送 AHT20 地址和写命令
  wait_for_ack();
  i2c_write_byte(0x71);  // 发送获取状态字的命令
  wait_for_ack();

  // 重新开始 I2C 通信以读取数据
  i2c_start();
  i2c_write_byte((AHT20_ADDR << 1) | 0x01);  // 发送 AHT20 地址和读命令
  wait_for_ack();
  status = i2c_read_byte();  // 读取状态字
  send_nack();               // 发送 NACK，结束传输
  i2c_stop();
  
  return status;
}

// 初始化 AHT20
void initAHT20(void) 
{
  // 开始 I2C 通信
  i2c_start();
  i2c_write_byte(AHT20_ADDR << 1);  // 发送 AHT20 地址和写命令
  wait_for_ack();
  i2c_write_byte(0xBE);  // 发送初始化命令
  wait_for_ack();
  i2c_write_byte(0x08);  // 发送第一个参数字节
  wait_for_ack();
  i2c_write_byte(0x00);  // 发送第二个参数字节
  wait_for_ack();
  i2c_stop();

  delay(10);  // 等待 10ms
}

// 触发测量并读取温湿度数据
void AHT20_measurement(void) 
{
  // 发送 0xAC 命令，触发测量
  i2c_start();
  i2c_write_byte(AHT20_ADDR << 1);  // 发送写命令
  wait_for_ack();
  i2c_write_byte(0xAC);  // 触发测量命令
  wait_for_ack();
  i2c_write_byte(0x33);  // 第一个参数
  wait_for_ack();
  i2c_write_byte(0x00);  // 第二个参数
  wait_for_ack();
  i2c_stop();

  delay(80);  // 等待 80ms 进行测量

  
  // 检查状态字的 Bit[7] 是否为 0，表示测量完成
  while (!(readStatus() & 0x80)) 
  {
    delay(10);  // 如果未完成，继续等待
  }

  // 读取测量数据
  readData();

  //
  OLED_displayMeasurement();
}

// 读取温湿度数据
void readData(void) 
{
  uint8_t data[6];  // 保存 6 个字节的数据

  // 发送读取命令
  i2c_start();
  i2c_write_byte((AHT20_ADDR << 1) | 0x01);  // 发送读命令
  wait_for_ack();

  // 连续读取 5 个字节
  for (int i = 0; i < 5; i++) 
  {
    data[i] = i2c_read_byte();
    if (i < 4) {
      send_ack();  // 发送 ACK
    } else {
      send_nack();  // 最后一个字节发送 NACK
    }
  }
  i2c_stop();

  // 解析湿度和温度
  int32_t humidity_temp = (data[1] << 12) | (data[2] << 4) | (data[3] >> 4);
  int32_t temperature_temp = ((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5];

  humidity = humidity_temp * 100 / 1048576;
  temperature = temperature_temp * 200 / 1048576 - 50;

  OLED_displayMeasurement();
  
  // 串口输出数据

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.print("   ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
}

void OLED_displayMeasurement(void)
{
  if(temperature != lastTemperature) // 如果温度和湿度没有变化，则不更新显示
  {
    OLED_Clear(1, 6, 11); // 清除温度显示
    OLED_Show_SignedNum(1, 6, temperature, 2); // 更新温度
  }
	
  if(humidity != lastHumidity) // 如果温度和湿度没有变化，则不更新显示
  {
	  OLED_Clear(2, 6, 11); // 清除湿度显示
	  OLED_Show_SignedNum(2, 6, humidity, 2); // 更新湿度
  }
  lastTemperature = temperature; // 更新上次温度
  lastHumidity = humidity; // 更新上次湿度 
}

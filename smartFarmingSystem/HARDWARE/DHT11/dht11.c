#include "dht11.h"

extern TIM_HandleTypeDef htim4;

static void DATA_OUTPUT(u8 flg); // DATA输出
static u8 DATA_INPUT(void);      // DATA输入
static u8 DH11_Read_Byte(void);  // DH11读信号

u8 DH11_Read(void); // 读取DH11温度和湿度

static void Test(void); // 测试程序

DH11_DATA DH11_data;

void Delay_us(uint16_t us)
{ // 微秒延时
  uint16_t differ = 0xffff - us - 5;
  __HAL_TIM_SET_COUNTER(&htim4, differ); // 设定TIM1计数器起始值
  HAL_TIM_Base_Start(&htim4);            // 启动定时器

  while (differ < 0xffff - 5)
  {                                         // 判断
    differ = __HAL_TIM_GET_COUNTER(&htim4); // 查询计数器的计数值
  }
  HAL_TIM_Base_Stop(&htim4);
}

void DATA_OUTPUT(u8 flg)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);

  if (flg == 0)
  {
    DATA_RESET();
  }
  else
  {
    DATA_SET();
  }
}

u8 DATA_INPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  u8 flg = 0;

  GPIO_InitStruct.Pin = DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);

  if (DATA_READ() == GPIO_PIN_RESET)
  {
    flg = 0;
  }
  else
  {
    flg = 1;
  }

  return flg;
}

u8 DH11_Read_Byte(void)
{
  u8 ReadDat = 0;
  u8 temp = 0;
  u8 retry = 0;
  u8 i = 0;

  for (i = 0; i < 8; i++)
  {
    while (DATA_READ() == 0 && retry < 100) // 等待直到DHT11输出高电平
    {
      Delay_us(1);
      retry++;
    }
    retry = 0;
    Delay_us(40);
    if (DATA_READ() == 1)
    {
      temp = 1;
    }
    else
    {
      temp = 0;
    }
    while (DATA_READ() == 1 && retry < 100) // 等待直到DHT11输出低电平，表示退出。本轮1bit信号接收完毕。
    {
      Delay_us(1);
      retry++;
    }
    retry = 0;
    ReadDat <<= 1;
    ReadDat |= temp;
  }

  return ReadDat;
}

u8 DH11_Read(void)
{
  u8 retry = 0;
  u8 i = 0;

  DATA_OUTPUT(0); // 设置为输出模式，MCU向DH11发送信号
  HAL_Delay(18);  // 延迟18毫秒
  DATA_SET();     // 设置数据线为高电平
  Delay_us(20);   // 延迟20微秒

  DATA_INPUT(); // 设置为输入模式，准备接收DH11发送的数据
  Delay_us(20); // 延迟20微秒

  // 检测DH11是否响应
  if (DATA_READ() == 0) // 如果数据线为低电平，说明DH11已经响应
  {
    // 等待数据线拉高
    while (DATA_READ() == 0 && retry < 100)
    {
      Delay_us(1); // 延迟1微秒
      retry++;
    }
    retry = 0;

    // 等待数据线拉低
    while (DATA_READ() == 1 && retry < 100)
    {
      Delay_us(1); // 延迟1微秒
      retry++;
    }
    retry = 0;

    // 读取数据
    for (i = 0; i < 5; i++) // 数据格式：Data[0]湿度整数位，Data[1]湿度小数位，Data[2]温度整数位，Data[3]温度小数位，Data[4]校验和
    {
      DH11_data.Data[i] = DH11_Read_Byte(); // 读取一个字节数据
    }
    Delay_us(50); // 延迟50微秒

    // 数据校验
    u32 sum = DH11_data.Data[0] + DH11_data.Data[1] + DH11_data.Data[2] + DH11_data.Data[3]; // 计算校验和
    if ((sum) == DH11_data.Data[4])                                                          // 如果校验和匹配
    {
      DH11_data.humidity = DH11_data.Data[0] + DH11_data.Data[1] / 10.0; // 获取湿度值（包含小数）
      DH11_data.temp = DH11_data.Data[2] + DH11_data.Data[3] / 10.0;     // 获取温度值（包含小数）
      return 1;                                                          // 返回成功
    }
  }
  return 0; // 返回失败
}

void Test(void)
{
  if (DH11_Read())
  {
    DH11_data.index++;
    if (DH11_data.index >= 128)
    {
      DH11_data.index = 0;
    }
  }
}
void DH11_Task(void)
{
  Test();
}

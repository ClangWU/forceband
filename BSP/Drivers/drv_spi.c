/**
  ******************************************************************************
  * File Name          : ADS1256_SPI.c
  * Description        : 实现了freertos任务配置
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_spi.h"

/*------模拟SPI八字节发送接收函数-----*/
uint8_t SPI_SORT_TR(uint8_t TxData)
{
	uint8_t RxData=0;
	SCLK(0);							//时钟线拉低
	delay_us_nos(1);							//片选拉低后需要一个延时
	for(uint8_t i=0;i<8;i++)
	{
		if(TxData&0x80)
		{
			MOSI(1);
		}
		else
		{
			MOSI(0);
		}
		SCLK(1);
		delay_us_nos(1);						//ADS1256 要求 SCL高电平和低电平持续时间最小 200ns
		TxData <<= 1;
		RxData <<= 1;
		SCLK(0);						//ADS1256 是在SCK下降沿采样DIN数据, 数据必须维持 50nS
		if (MISO_READ())		//判断从机发的最高位
		{
			RxData++;
		}	
		delay_us_nos(1);
	}
	return RxData;
}









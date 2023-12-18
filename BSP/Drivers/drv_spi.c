/**
  ******************************************************************************
  * File Name          : ADS1256_SPI.c
  * Description        : ʵ����freertos��������
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_spi.h"

/*------ģ��SPI���ֽڷ��ͽ��պ���-----*/
uint8_t SPI_SORT_TR(uint8_t TxData)
{
	uint8_t RxData=0;
	SCLK(0);							//ʱ��������
	delay_us_nos(1);							//Ƭѡ���ͺ���Ҫһ����ʱ
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
		delay_us_nos(1);						//ADS1256 Ҫ�� SCL�ߵ�ƽ�͵͵�ƽ����ʱ����С 200ns
		TxData <<= 1;
		RxData <<= 1;
		SCLK(0);						//ADS1256 ����SCK�½��ز���DIN����, ���ݱ���ά�� 50nS
		if (MISO_READ())		//�жϴӻ��������λ
		{
			RxData++;
		}	
		delay_us_nos(1);
	}
	return RxData;
}









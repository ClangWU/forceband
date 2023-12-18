/**
  ******************************************************************************
  * File Name          : ADS1256_SPI.h
  * Description        : 提供了模拟SPI函数与AD模块通信.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADS1256_SPI_H
#define __ADS1256_SPI_H
#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "drv_timer.h"
/*---------------------ADS模拟SPI引脚操作宏定义---------------------*/
/**Simulation SPI GPIO Configuration
    PB1     ------> ADS_SCLK
    PB0     ------> ADS_MOSI
    PB5     ------> ADS_MISO
		PB3     ------> ADS_CS
		PB4     ------> ADS_DRDY
    */
#define SCLK(state)			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,(GPIO_PinState)state)
#define MOSI(state) 		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(GPIO_PinState)state)
#define MISO_READ() 		HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)
#define CS(state)				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,(GPIO_PinState)state)

/*------API函数接口-----*/
uint8_t SPI_SORT_TR(uint8_t TxData);
#ifdef __cplusplus
}
#endif
#endif /*__ ADS1256_SPI_H */



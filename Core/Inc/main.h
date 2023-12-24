/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32g4xx_hal.h"
#include "Service_Devices.h"
#include "Service_Communication.h"
#include "System_Config.h"
#include "System_DataPool.h"

#include <cstdint>
#include <string.h>
#include <BSP.h>
#include <stdio.h>
#include "tim.h"
#include "gpio.h"
#include "math.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define M_PI 3.14159
#define ang2rad(angle) ((double)(angle) / 180.0 *M_PI) 
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
#pragma pack(1)
typedef struct
{
	uint8_t head;
	int start_cmd;
	int grip_cmd;
	uint8_t end;
}PackToPC_Def;
#pragma pack()

typedef union
{
	uint8_t UsartData[10];
	PackToPC_Def PackToPC;
}PackToPCUnionDef;

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M4_Pin GPIO_PIN_0
#define M4_GPIO_Port GPIOA
#define TX2_Pin GPIO_PIN_2
#define TX2_GPIO_Port GPIOA
#define RX2_Pin GPIO_PIN_3
#define RX2_GPIO_Port GPIOA
#define M2_Pin GPIO_PIN_0
#define M2_GPIO_Port GPIOB
#define M1_Pin GPIO_PIN_1
#define M1_GPIO_Port GPIOB
#define ENPIN_Pin GPIO_PIN_2
#define ENPIN_GPIO_Port GPIOB
#define M6_Pin GPIO_PIN_15
#define M6_GPIO_Port GPIOB
#define M7_Pin GPIO_PIN_8
#define M7_GPIO_Port GPIOA
#define M8_Pin GPIO_PIN_9
#define M8_GPIO_Port GPIOA
#define M3_Pin GPIO_PIN_10
#define M3_GPIO_Port GPIOA
#define key_start_Pin GPIO_PIN_15
#define key_start_GPIO_Port GPIOA
#define M5_Pin GPIO_PIN_5
#define M5_GPIO_Port GPIOB
#define key_grip_Pin GPIO_PIN_9
#define key_grip_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
void pulse_1(int force, int theta);
void pulse_2(int force, int theta);
void pulse_3(int force, int theta);
void pulse_4(int force, int theta);
void pulse_5(int force, int theta);
void pulse_6(int force, int theta);
void pulse_7(int force, int theta);
void pulse_8(int force, int theta);
void cal_pulse_interpolated(int force, int theta);
void cal_pulse_single(float force, int theta);
uint16_t mapFloatToUInt16(float input);
void any_pulse(float force, int num); 

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

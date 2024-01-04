/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
// 2200-2700  2700-3100 3100-4000
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM15_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV3;
  RCC_OscInitStruct.PLL.PLLN = 126;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint16_t mapFloatToUInt16(float input) {
    if (input < 0.0f) {
        return 2000;
    } else if (input > 10.0f) {
        return 4199;
    }
    return (uint16_t)(((uint32_t)input * (4199.0f - 2000.0f) / 10.0f) + 2000.0f);
}
void cal_pulse_interpolated(int force, int theta){
	//1- get theta
	//2- classify
	//3- calpulse
	if(0<= theta && theta < 45)
		pulse_1(force, theta);
	else if(45<= theta && theta < 90)
		pulse_2(force, theta);
	else if(90<= theta && theta < 135)
		pulse_3(force, theta);
	else if(135<= theta && theta < 180)
		pulse_4(force, theta);
	else if(180<= theta && theta < 225)
		pulse_5(force, theta);
	else if(225<= theta && theta < 270)
		pulse_6(force, theta);
	else if(270<= theta && theta < 315)
		pulse_7(force, theta);
	else // 315< theta < 360
		pulse_8(force, theta);
}
void pulse_1(int force, int theta){
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	
	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = (float)force * sin(ang2rad(theta)) / 0.707;
	float f_orth = (float)force * cos(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, _compare_2);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, _compare_1);//2
}
void pulse_2(int force, int theta){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	
	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = (float)force * cos(ang2rad(theta)) / 0.707;
	float f_orth = (float)force * sin(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, _compare_1);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, _compare_2);//3
}
void pulse_3(int force, int theta){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	
	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = -(float)force * cos(ang2rad(theta)) / 0.707;
	float f_orth = (float)force * sin(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, _compare_1);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, _compare_2);//4
}
void pulse_4(int force, int theta){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	
	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = (float)force * sin(ang2rad(theta)) / 0.707;
	float f_orth = -(float)force * cos(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, _compare_1);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, _compare_2);//5
}
void pulse_5(int force, int theta){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
//	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8	

	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = -(float)force * sin(ang2rad(theta)) / 0.707;
	float f_orth = -(float)force * cos(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, _compare_1);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, _compare_2);//6
}
void pulse_6(int force, int theta){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
//	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	
	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = -(float)force * cos(ang2rad(theta)) / 0.707;
	float f_orth = -(float)force * sin(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, _compare_1);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, _compare_2);//7
}
void pulse_7(int force, int theta){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	
	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = (float)force * cos(ang2rad(theta)) / 0.707;
	float f_orth = -(float)force * sin(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, _compare_1);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _compare_2);//8
	
}
void pulse_8(int force, int theta){
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	
	uint16_t _compare_1;
	uint16_t _compare_2;
	float f_diag = -(float)force * sin(ang2rad(theta)) / 0.707;
	float f_orth = (float)force * cos(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _compare_1);//8
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, _compare_2);//1
}

void cal_pulse_single(float force, float theta) {
    if (theta < 0.0f || theta > 360.0f) {
        printf("Error: Invalid theta value\n");
        return;
    }
    int motorNumber = (int)((((int)theta ) / 30) % 12 + 1);
	any_pulse(force, motorNumber);
}

void any_pulse(float force, int num){
	uint16_t _compare;
	_compare = mapFloatToUInt16(force);
	if (num < 0 || num > 12) {
        // 处理无效的 num 值
        printf("Error: Invalid motor number\n");
        return;
    }
	switch (num){
		case 6:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, _compare);//1
		
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12

			break;
		case 5:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, _compare);//2
		
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 4:
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, _compare);//3

			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 3:
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, _compare);//4
		
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
//			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 2:
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, _compare);//5
		
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 1:
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _compare);//6

			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 12:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, _compare);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
//			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 11:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, _compare);//8
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 10:
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, _compare);//9
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 9:
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, _compare);//10
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
//			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 8:
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, _compare);//11
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
//			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		case 7:
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, _compare);//12
		
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//4
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//5
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//6
		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//7
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);//8
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);//9
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);//10
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);//11
//			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);//12
			break;
		
	}
}
//clang
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, _compare);//1
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, _compare);//2
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, _compare);//3
//			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, _compare);//4
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, _compare);//5
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _compare);//6
//			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, _compare);//7
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, _compare);//8
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, _compare);//9
//			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, _compare);//10
//			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, _compare);//11
//			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, _compare);//12



/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	System_Tasks_Init();
	osThreadTerminate(defaultTaskHandle); 
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */



//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim15,TIM_CHANNEL_4);

//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, _pulse);//1
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, _pulse);//2
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, _pulse);//3
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, _pulse);//4
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, _pulse);//5
//	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, _pulse);//6
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, _pulse);//7
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _pulse);//8

//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4, _pulse);
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, _pulse);
//	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, _pulse);
//	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, _pulse);
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, _pulse);
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, _pulse);	
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, _pulse);
//	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_4, _pulse);

//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
//	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8

/* USER CODE END Application */


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
#include "tim.h"
#include "gpio.h"
#include "math.h"
#include <cstdint>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int16_t _pulse = 4000;
int16_t _angle = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define M_PI 3.14159
#define ang2rad(angle) ((double)(angle) / 180.0 *M_PI) 
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
	int add_flag =1;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim15,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	
  /* Infinite loop */
  for(;;)
  {
	if(_angle > 359)
		add_flag = 0;
	if(_angle < 0)
		add_flag = 1;
	
	if(add_flag)
		_angle += 1;
	else
		_angle -= 1;
	
	cal_pulse(19, _angle);
	
    osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
uint16_t mapFloatToUInt16(double input) {
    if (input < 0.0f) {
        return 2500;
    } else if (input > 20.0f) {
        return 4199;
    }
    return (uint16_t)(((uint32_t)input * (4199.0f - 2500.0f) / 20.0f) + 2500.0f);
}

void cal_pulse(int force, int theta){
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
	double f_diag = (double)force * sin(ang2rad(theta)) / 0.707;
	double f_orth = (double)force * cos(ang2rad(theta)) - f_diag * 0.707;
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
	double f_diag = (double)force * cos(ang2rad(theta)) / 0.707;
	double f_orth = (double)force * sin(ang2rad(theta)) - f_diag * 0.707;
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
	double f_diag = -(double)force * cos(ang2rad(theta)) / 0.707;
	double f_orth = (double)force * sin(ang2rad(theta)) - f_diag * 0.707;
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
	double f_diag = (double)force * sin(ang2rad(theta)) / 0.707;
	double f_orth = -(double)force * cos(ang2rad(theta)) - f_diag * 0.707;
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
	double f_diag = -(double)force * sin(ang2rad(theta)) / 0.707;
	double f_orth = -(double)force * cos(ang2rad(theta)) - f_diag * 0.707;
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
	double f_diag = -(double)force * cos(ang2rad(theta)) / 0.707;
	double f_orth = -(double)force * sin(ang2rad(theta)) - f_diag * 0.707;
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
	double f_diag = (double)force * cos(ang2rad(theta)) / 0.707;
	double f_orth = -(double)force * sin(ang2rad(theta)) - f_diag * 0.707;
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
	double f_diag = -(double)force * sin(ang2rad(theta)) / 0.707;
	double f_orth = (double)force * cos(ang2rad(theta)) - f_diag * 0.707;
	_compare_1 = mapFloatToUInt16(f_diag);
	_compare_2 = mapFloatToUInt16(f_orth);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _compare_1);//8
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, _compare_2);//1
}
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


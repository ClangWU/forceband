/**
  ******************************************************************************
  * @file   System_DataPool.h
  * @brief  All used resources are contained in this file.
  ******************************************************************************
  * @note
  *  - User can define datas including variables ,structs ,and arrays in
  *    this file, which are used in deffrient tasks or services.
**/
#ifndef _DATA_POOL_H_
#define _DATA_POOL_H_

/* Includes ------------------------------------------------------------------*/
/* Middlewares & Drivers Support */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "stm32g4xx_hal.h"
#include <BSP.h>

/* Macro Definitions ---------------------------------------------------------*/
#define Tiny_Stack_Size       64
#define Small_Stack_Size      128
#define Normal_Stack_Size     256
#define Large_Stack_Size      512
#define Huge_Stack_Size       1024
#define PriorityVeryLow       1
#define PriorityLow           2
#define PriorityBelowNormal   3
#define PriorityNormal        4
#define PriorityAboveNormal   5
#define PriorityHigh          6
#define PrioritySuperHigh     7
#define PriorityRealtime      8

/* HAL Handlers --------------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

/* RTOS Resources ------------------------------------------------------------*/
/* Queues */
extern QueueHandle_t  USART_RxPort;
extern QueueHandle_t  USART_TxPort;
extern QueueHandle_t  CAN1_TxPort;
extern QueueHandle_t  CAN2_TxPort;
extern QueueHandle_t  ADC_QueueHandle;
extern QueueHandle_t  RMMotor_QueueHandle;
extern QueueHandle_t  SuperRelay_QueueHandle;
extern QueueHandle_t  IMU_QueueHandle;
extern QueueHandle_t  NUC_QueueHandle;
extern QueueHandle_t  Referee_QueueHandle;
/* Semaphores */
/* Mutexes */
/* Notifications */
/* Other Resources -----------------------------------------------------------*/
#define USART1_RX_BUFFER_SIZE 64
#define USART2_RX_BUFFER_SIZE 64
#define USART3_RX_BUFFER_SIZE 128


extern uint8_t Uart1_Rx_Buff[USART1_RX_BUFFER_SIZE];
extern uint8_t Uart2_Rx_Buff[USART2_RX_BUFFER_SIZE];
extern uint8_t Uart3_Rx_Buff[USART3_RX_BUFFER_SIZE];


//暂时被遗忘在这,统一标准接口制定后再集中回收
#ifndef __UUCOBTypeDef_DEFINED
#define __UUCOBTypeDef_DEFINED
#endif


#endif
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

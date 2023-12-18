/**
  ******************************************************************************
  * @file   System_config.cpp
  * @brief  Deploy resources,tasks and services in this file.
  ******************************************************************************
  * @note
  *  - Before running your Task you should first include your headers and init- 
  *    ialize used resources in "System_Resource_Init()". This function will be 
  *    called before tasks Start.
  *    
  *  - All tasks should be created in "System_Tasks_Init()", this function will
  *    be called in 'defaultTask()'.
  *
  ===============================================================================
                                    Task List
  ===============================================================================
  * <table>
  * <tr><th>Task Name     <th>Priority          <th>Frequency/Hz    <th>Stack/Byte
  * <tr><td>              <td>                  <td>                <td>    
  * </table>
  *
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
/* User support package & SRML */
//#include "SEGGER_SYSVIEW.h"
/* Private variables ---------------------------------------------------------*/

/*Founctions------------------------------------------------------------------*/
/**
* @brief Load drivers ,modules, and data resources for tasks.
* @note  Edit this function to add Init-functions and configurations.
*/
void System_Resource_Init(void)
{
  /* Drivers Init ---------------------*/
//	Uart_Init(&huart1, Uart1_Rx_Buff, USART1_RX_BUFFER_SIZE, User_UART1_RxCpltCallback);
//	Uart_Init(&huart2, Uart2_Rx_Buff, USART2_RX_BUFFER_SIZE, User_UART2_RxCpltCallback);

  /* RTOS resources Init --------------*/
	//Receive Force Sensor Data
	USART_RxPort       = xQueueCreate(2,sizeof(USART_COB));
  /* Other resources Init -------------*/
	//Vibra Motor
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim15,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

  /* Modules Init ---------------------*/
  /* Service configurations -----------*/
  
}  


/**
* @brief Load and start User Tasks. 
* @note  Edit this function to add tasks into the activated tasks list.
*/
void System_Tasks_Init(void)
{ 
  /* Syetem Service init --------------*/
	System_Resource_Init();
	Service_Devices_Init();
  /* Applications Init ----------------*/

}

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/


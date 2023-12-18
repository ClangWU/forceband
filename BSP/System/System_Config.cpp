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
#include "System_Config.h"
#include "System_DataPool.h"
#include <stdio.h>
#include <string.h>
/* Service */
#include "adc.h"
#include "Service_Devices.h"
//#include "Service_Debug.h"
#include "Service_Communication.h"
/* User support package & SRML */
#include <BSP.h>
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
	Uart_Init(&huart1, Uart1_Rx_Buff, USART1_RX_BUFFER_SIZE, User_UART1_RxCpltCallback);

  /* RTOS resources Init --------------*/
	//Receive Force Sensor Data
	USART_RxPort       = xQueueCreate(2,sizeof(USART_COB));
	ADC_QueueHandle    = xQueueCreate(2,sizeof(USART_COB));
  /* Other resources Init -------------*/
	//Vibra Motor
	//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	
	HAL_ADCEx_Calibration_Start(&hadc1); 
	HAL_ADC_Start(&hadc1);
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
  Service_Devices_Init();
  /* Applications Init ----------------*/

}

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/


/**
  ******************************************************************************
  * @file   Service_Devices.cpp
  * @brief  Devices service running file.
  ******************************************************************************
  * @note
  *  - Before running your devices, just do what you want ~ !
  *  - More devices or using other classification is decided by yourself ~ !
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
#include "Service_Devices.h"
#include "Service_Communication.h"
#include "System_Config.h"
#include "main.h"


/* Private define ------------------------------------------------------------*/
TaskHandle_t Vibra_Handle;
TaskHandle_t JoyStick_Handle;

/* Private variables ---------------------------------------------------------*/
//uint32_t motor_fb_test =5000;
/* Private function declarations ---------------------------------------------*/
//void Device_Actuators(void *arg);
void Vibra_Task(void *arg);
void JoyStick_Task(void *arg);

/* Exported devices ----------------------------------------------------------*/
/* Motor & ESC & Other actuators*/
/* Remote control */
float force_sensor;

/* IMU & NUC & Other sensors */
uint16_t motor_fb = 8000;

/* Other boards */

/* Function prototypes -------------------------------------------------------*/
//stand by for redify
uint16_t mapToRange(float data)
{
    float minInput = 0;       // 输入数据的最小值
    float maxInput = 4095;    // 输入数据的最大值
    float minOutput = 8000;   // 输出范围的最小值
    float maxOutput = 20000;  // 输出范围的最大值
    
    // 执行线性插值
    return (uint16_t)(((uint32_t)(data - minInput) * (maxOutput - minOutput) / (maxInput - minInput)) + minOutput);
}

/**
* @brief  Initialization of device management service
* @param  None.
* @return None.
*/
void Service_Devices_Init(void)
{
//	xTaskCreate(JoyStick_Task,   "UartTransmit" ,    Normal_Stack_Size   ,   NULL    ,   PriorityHigh,   &JoyStick_Handle);
	xTaskCreate(Vibra_Task,		"Vibra_Task"	,	Normal_Stack_Size	,	NULL	,	PriorityHigh	,	&Vibra_Handle);
}

void JoyStick_Task(void *arg){
	USART_COB adc_buff;
	static uint16_t _buffer = 0;
	float int_buffer = 0;
	PackToPCUnionDef _PackToPCUnion;
	_PackToPCUnion.PackToPC.head = 0x44;
	_PackToPCUnion.PackToPC.end  = 0x55;
	for(;;)
	{
//		if(xQueueReceive(ADC_QueueHandle, &adc_buff, 0) == pdTRUE){
//			if(adc_buff.len == 2){
//				memcpy(&_buffer,adc_buff.address,2);
//		int_buffer = (int)_buffer - 2048;

//			}
//		}
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1,100);
//		if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC))
//		   adc_buffer[0] =  HAL_ADC_GetValue(&hadc1);
//		int_buffer = (int)(adc_buffer[0]) - 2048;
				int_buffer =  0.66;

		_PackToPCUnion.PackToPC.ad_data = int_buffer;
		HAL_UART_Transmit_DMA(&huart1, _PackToPCUnion.UsartData, sizeof(_PackToPCUnion.PackToPC));

		vTaskDelay(1 / portTICK_RATE_MS);
	}
}


void Vibra_Task(void *arg)
{
	USART_COB _buffer;
//	xLastWakeTime_t = xTaskGetTickCount();
	int add_flag = 1;
	for(;;)
	{
		if(xQueueReceive(USART_RxPort, &_buffer, 0) == pdTRUE){
			if (_buffer.len == 4){
				memcpy(&force_sensor,_buffer.address,_buffer.len);
								//handle - +
				motor_fb = mapToRange(force_sensor);
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, motor_fb);
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, motor_fb);
				
//				if(motor_fb > 19990)
//					add_flag = 0;
//				if(motor_fb < 6000)
//					add_flag = 1;
//				if(add_flag)
//					motor_fb += 10;
//				else
//					motor_fb -= 10;
//				vTaskDelay(5 / portTICK_RATE_MS);
	}}}	//8000 - 19999
}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//	switch(GPIO_Pin)
//	{
//		case add_key_Pin:
//			_PackToPCUnion.PackToPC.coef += 0.1;
//			break;
//		case sub_key_Pin:
//			_PackToPCUnion.PackToPC.coef -= 0.1;
//			break;
//	}
//}	

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	static USART_COB ADC_COB;
	if(ADC_QueueHandle != NULL){
		ADC_COB.port_num = 1;
		ADC_COB.len = 2;
		ADC_COB.address  = adc_buffer;
		xQueueSendFromISR(ADC_QueueHandle,&ADC_COB,0);
	}
}

/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

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
#include "main.h"


/* Private define ------------------------------------------------------------*/
TaskHandle_t Vibra_Handle;
TaskHandle_t Key_Handle;

/* Private variables ---------------------------------------------------------*/
//uint32_t motor_fb_test =5000;
/* Private function declarations ---------------------------------------------*/
//void Device_Actuators(void *arg);
void Vibra_Task(void *arg);
void Key_Task(void *arg);

/* Exported devices ----------------------------------------------------------*/
/* Motor & ESC & Other actuators*/
/* Remote control */
float force_sensor;
_NUCComRx NUCComRxData;

/* IMU & NUC & Other sensors */
int16_t _pulse = 4000;
int16_t _angle = 0;

	char str[40];	

/* Other boards */

/* Function prototypes -------------------------------------------------------*/
//stand by for redify

/**
* @brief  Initialization of device management service
* @param  None.
* @return None.
*/
void Service_Devices_Init(void)
{	
	BaseType_t xreturn = xTaskCreate(Vibra_Task,	"Vibra_Task",	Normal_Stack_Size,   NULL,	PriorityHigh,	&Vibra_Handle);
	xTaskCreate(Key_Task,   "Key_Task" ,     Tiny_Stack_Size,   NULL,   PriorityHigh,   &Key_Handle);
}

void Key_Task(void *arg){
//	static uint16_t _buffer = 0;
//	float int_buffer = 0;
	uint16_t _grip = 0x01;
	uint16_t _start = 0x01;
	
	uint16_t _grip_front =1;
	uint16_t _grip_mid =1;
	uint16_t _grip_last =1;

	uint16_t _start_front =1;
	uint16_t _start_mid =1;
	uint16_t _start_last =1;
	
	uint16_t _grip_temp;
	uint16_t _start_temp;

	bool grip_flag = 0;
	bool start_flag = 0;

	PackToPCUnionDef _PackToPCUnion;
	_PackToPCUnion.PackToPC.head = 0x44;
	_PackToPCUnion.PackToPC.end  = 0x55;

	for(;;)
	{
		_grip_temp = HAL_GPIO_ReadPin(key_grip_GPIO_Port, key_grip_Pin);
		if(HAL_GPIO_ReadPin(key_grip_GPIO_Port, key_grip_Pin)==_grip_temp)
			_grip = _grip_temp;
		if(_grip == 1)
		{
			if(_grip_mid ==1)	
				_grip_front = 1;
			else
				_grip_last = 1;
		}
		else
		{
			if(_grip_front  == 1){
				_grip_mid = 0;
				_grip_last = 0;
			}
		}
			
		if(_grip_front == 1 && _grip_mid == 0 && _grip_last ==1){
			if(grip_flag == 0){
				_PackToPCUnion.PackToPC.grip_cmd = 0x1111;
				grip_flag = 1;
			}else{
				_PackToPCUnion.PackToPC.grip_cmd = 0x2222;
				grip_flag = 0;
			}
			
			_grip_front =1;
			_grip_mid = 1;
			_grip_last = 1;
		}else
			_PackToPCUnion.PackToPC.grip_cmd = 0;

		
		_start_temp = HAL_GPIO_ReadPin(key_start_GPIO_Port, key_start_Pin);
		if(HAL_GPIO_ReadPin(key_start_GPIO_Port, key_start_Pin)==_start_temp)
			_start = _start_temp;
		
		if(_start == 1)
		{
			if(_start_mid ==1)	
				_start_front = 1;
			else
				_start_last = 1;
		}
		else
		{
			if(_start_front  == 1){
				_start_mid = 0;
				_start_last = 0;
			}
		}
			
		if(_start_front == 1 && _start_mid == 0 && _start_last ==1){
			if(start_flag == 0){
				_PackToPCUnion.PackToPC.start_cmd = 0x1111;
				start_flag = 1;
			}else{
				_PackToPCUnion.PackToPC.start_cmd = 0x2222;
				start_flag = 0;
			}
			_start_front =1;
			_start_mid = 1;
			_start_last = 1;
		}else
			_PackToPCUnion.PackToPC.start_cmd = 0;
		
//		HAL_UART_Transmit(&huart2, _PackToPCUnion.UsartData, sizeof(_PackToPCUnion.PackToPC), 50);	//串口发送函数

		vTaskDelay(500 / portTICK_RATE_MS);
	}
}


void Vibra_Task(void *arg)
{
	USART_COB _buffer;
	
	TickType_t xLastWakeTime_t;
	xLastWakeTime_t = xTaskGetTickCount();
	static TickType_t _xTicksToWait = pdMS_TO_TICKS(1);
	static float force_sensor = 0;
	uint16_t _compare_1;
	uint16_t _compare_2;
	
	int8_t longBuff[0x08];

	int add_flag = 1;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);//1
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);//2
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//3
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);//4
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);//5
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);//6
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);//7
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//8
	for(;;)
	{
		if (xQueueReceive(NUC_QueueHandle, &_buffer, _xTicksToWait) == pdTRUE)
		{
			if(_buffer.len == 0x04)
			{
				memcpy(&force_sensor,_buffer.address,_buffer.len);
				if(force_sensor >= 0.0f){
					_compare_1 = mapFloatToUInt16(force_sensor);
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, _compare_1);		
				}
				else{
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);		
				}
			}
			else if(_buffer.len == 0x08){
				memcpy(longBuff, _buffer.address, _buffer.len);
				memcpy(&NUCComRxData, longBuff, 8);//收2个 即为2*4个字节
			}
		}		
		vTaskDelayUntil(&xLastWakeTime_t,1);
	}
}

//			if(_angle > 359)
//				add_flag = 0;
//			if(_angle < 0)
//				add_flag = 1;
//			
//			if(add_flag)
//				_angle += 1;
//			else
//				_angle -= 1;
//			
//			cal_pulse_interpolated(19, _angle);


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


/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

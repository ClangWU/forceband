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

/* IMU & NUC & Other sensors */
int16_t _pulse = 4000;
int16_t _angle = 0;

	char str[40];	

/* Other boards */

/* Function prototypes -------------------------------------------------------*/
//stand by for redify
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
	int _start_temp;
	int _grip_temp;
	PackToPCUnionDef _PackToPCUnion;
	_PackToPCUnion.PackToPC.head = 0x44;
	_PackToPCUnion.PackToPC.end  = 0x55;

	for(;;)
	{
		_grip_temp = HAL_GPIO_ReadPin(key_grip_GPIO_Port, key_grip_Pin);
		if(HAL_GPIO_ReadPin(key_grip_GPIO_Port, key_grip_Pin)==_grip_temp)
			_grip = _grip_temp;
		
		_start_temp = HAL_GPIO_ReadPin(key_start_GPIO_Port, key_start_Pin);
		if(HAL_GPIO_ReadPin(key_start_GPIO_Port, key_start_Pin)==_start_temp)
			_start = _start_temp;
		
		_PackToPCUnion.PackToPC.start_cmd = _start;
		_PackToPCUnion.PackToPC.grip_cmd = _grip;

//		HAL_UART_Transmit_DMA(&huart1, _PackToPCUnion.UsartData, sizeof(_PackToPCUnion.PackToPC));

		
		sprintf(str, "%04d:Hello,world.\r\n", _start);		//将counter的值打印到str数组中
//		HAL_UART_Transmit(&huart2,(unsigned char *)str, strlen(str), 50);	//串口发送函数
//		HAL_UART_Transmit_DMA(&huart1, "666", 3);

		vTaskDelay(500 / portTICK_RATE_MS);
	}
}


void Vibra_Task(void *arg)
{
//	USART_COB _buffer;
//	xLastWakeTime_t = xTaskGetTickCount();
	int add_flag = 1;
	
//	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_4);
//	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Stop(&htim15,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
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
		if(_angle > 359)
			add_flag = 0;
		if(_angle < 0)
			add_flag = 1;
		
		if(add_flag)
			_angle += 1;
		else
			_angle -= 1;
		
//		cal_pulse(19, _angle);
		
//		if(xQueueReceive(USART_RxPort, &_buffer, 0) == pdTRUE){
//			if (_buffer.len == 4){
//				memcpy(&force_sensor,_buffer.address,_buffer.len);
				
		vTaskDelay(50 / portTICK_RATE_MS);
	}
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


/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

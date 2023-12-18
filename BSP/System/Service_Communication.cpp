/**
  ***********************************************************************************
  * @file   : Service_Communication.cpp
  * @brief  : Communication support file.This file provides access ports to interface
  *           with connected devices.
  ***********************************************************************************
                                 ##### Port List #####
  =================================================================================
  |Port Name     Physical-Layer     Data-Link-Layer    Application-Layer    Number
  |————————————————————————————————————————
  |EXAMPLE_Port       CAN1               CAN                CUSTOM            0
  |CAN2_Port          CAN2               CAN                Custom            1
  |EBUG_Port         USART1             Custom              Custom            2
  |USART2_Port       USART2              DBUS               DJI-DR16          3
  *
**/
/* Includes ------------------------------------------------------------------*/
#include "Service_Communication.h"

/* Private define ------------------------------------------------------------*/


uint16_t mapFloatToUInt16(float input) {
    // 首先，确保输入值在0到5之间
    if (input < 0.0f) {
        return 5000;
    } else if (input > 20.0f) {
        return 20000;
    }
    return static_cast<uint16_t>((input * (20000.0f - 5000.0f) / 20.0f) + 5000.0f);
}

void Task_SendADC(void *arg);
/**
* @brief  Initialization of communication service
* @param  None.
* @return None.
*/
void Service_Communication_Init(void)
{ 
  //xTaskCreate(Task_SendADC,"Com.Usart TxPort" , Tiny_Stack_Size,    NULL, PriorityHigh,   &UartTransmitPort_Handle);
}

/*---------------------------------------------- USART Manager --------------------------------------------*/
/*Task Define ---------------------------*/
TaskHandle_t UartTransmitPort_Handle;

/*Function Prototypes--------------------*/
/**
* @brief  Tasks for USART Management.
          Attention:In this version we passing the pointer of data not copying
          data itself and we only have one buff zone, so user need to process 
          the data as soon as possible in case of over-write.
* @param  None.
* @return None.
*/
void Task_SendADC (void *arg)
{
  /* Cache for Task */
  /* Pre-Load for task */
  /* Infinite loop */
  for(;;)
  {
    /* Usart Receive Port*/
//    HAL_UART_Transmit_DMA(&huart1, _PackToPCUnion.UsartData, sizeof(_PackToPCUnion.PackToPC));
	vTaskDelay(2 / portTICK_RATE_MS);
  }
}

/**
* @brief  Callback function in USART Interrupt
* @param  None.
* @return None.
*/

uint32_t User_UART1_RxCpltCallback(uint8_t* Recv_Data, uint16_t ReceiveLen)
{
	static USART_COB Usart_RxCOB;
	float force_sensor;
	uint16_t _compare_1;
	uint16_t _compare_2;
	if (USART_RxPort!=NULL){
		Usart_RxCOB.port_num=1;
		Usart_RxCOB.len=ReceiveLen;
		Usart_RxCOB.address=Recv_Data;
		memcpy(&force_sensor,Usart_RxCOB.address,Usart_RxCOB.len);
//		if(force_sensor >= 0.0f){
			_compare_1 = mapFloatToUInt16(force_sensor);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, _compare_1);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, _compare_1);
	}
	return 0;
}

uint32_t User_UART2_RxCpltCallback(uint8_t* Recv_Data, uint16_t ReceiveLen)
{
	static USART_COB Usart_RxCOB;
	float force_sensor;
	uint16_t _compare_1;
	uint16_t _compare_2;
	if (USART_RxPort!=NULL){
		Usart_RxCOB.port_num=1;
		Usart_RxCOB.len=ReceiveLen;
		Usart_RxCOB.address=Recv_Data;
		memcpy(&force_sensor,Usart_RxCOB.address,Usart_RxCOB.len);
//		if(force_sensor >= 0.0f){
			_compare_1 = mapFloatToUInt16(force_sensor);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, _compare_1);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, _compare_1);
	}
	return 0;
}

void Usart_Tx_Pack(QueueHandle_t Queue_Usart_TxPort,uint8_t port_num,uint16_t len,void* address)
{
	USART_COB Usart_TxCOB;
	Usart_TxCOB.port_num=port_num;
	Usart_TxCOB.address=address;
	Usart_TxCOB.len=len;
	xQueueSend(Queue_Usart_TxPort,&Usart_TxCOB,0);
}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//	_PackToPCUnion.PackToPC.ad_data = ad_value;
//}
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

/**
  **********************************************************************************
  * @file   ：Service_Communication.h
  * @brief  ：Header of Service_Communication.cpp
  **********************************************************************************
**/
#ifndef  _SERVICE_COMMUNICATE_H_
#define  _SERVICE_COMMUNICATE_H_

#include "System_DataPool.h"
#include "main.h"
#ifdef  __cplusplus
extern "C"{
#endif
/*------------------------------ System Handlers ------------------------------*/
extern uint16_t ad_value;
extern TaskHandle_t UartTransmitPort_Handle;

/*------------------------------Function prototypes ---------------------------*/
uint32_t User_UART1_RxCpltCallback(uint8_t* Recv_Data, uint16_t ReceiveLen);
uint32_t User_UART2_RxCpltCallback(uint8_t* Recv_Data, uint16_t ReceiveLen);

void Usart_Tx_Pack(QueueHandle_t Queue_Usart_TxPort,uint8_t port_num,uint16_t len,void* address);
	
void Service_Communication_Init(void);

#ifdef  __cplusplus
}
#endif
#endif  

/************************* COPYRIGHT SCUT-ROBOTLAB *****END OF FILE****************/


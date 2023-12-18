/**
  ******************************************************************************
  * Copyright (c) 2019 - ~, SCUT-RobotLab Development Team
  * @file    drv_gpio.h
  * @author  
  * @brief   
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have any 
  * bugs, update the version Number, write dowm your name and the date. The most
  * important thing is make sure the users will have clear and definite under-
  * standing through your new brief.
  *
  * <h2><center>&copy; Copyright (c) 2019 - ~, SCUT-RobotLab Development Team.
  * All rights reserved.</center></h2>
  ******************************************************************************
  */
#ifndef  _DRV_GPIO_H
#define  _DRV_GPIO_H

#ifdef  __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32f1xx_hal.h>
/* Private macros ------------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
typedef struct
{
	uint32_t count;
	uint32_t time_bef;
	float inval;
	uint8_t  isinit;
}EXTI_Count;
	
typedef struct
{
	EXTI_Count GPIO0;
	EXTI_Count GPIO1;
	EXTI_Count GPIO2;
	EXTI_Count GPIO3;
	EXTI_Count GPIO4;
	EXTI_Count GPIO5;
	EXTI_Count GPIO6;
	EXTI_Count GPIO7;
	EXTI_Count GPIO8;
	EXTI_Count GPIO9;
	EXTI_Count GPIO10;
	EXTI_Count GPIO11;
	EXTI_Count GPIO12;
	EXTI_Count GPIO13;
}EXTI_GPIOx;
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
extern EXTI_GPIOx Exti_GPIO;
extern uint32_t check1;
extern uint32_t check2;
extern uint32_t check3;
/* Exported variables ---------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/



#ifdef  __cplusplus
}
#endif

#endif 
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

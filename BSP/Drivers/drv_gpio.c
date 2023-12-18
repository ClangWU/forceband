/**
  ******************************************************************************
  * Copyright (c) 2019 - ~, SCUT-RobotLab Development Team
  * @file    drv_timer.c
  * @author  
  * @brief   
  * @date    2019-06-12
  * @version 2.0
  * @par Change Log：
  * <table>
  * <tr><th>Date        <th>Version  <th>Author         <th>Description
  * <tr><td>2019-06-12  <td> 1.0     <td>Mentos Seetoo  <td>Creator
  * <tr><td>2019-10-28  <td> 2.0     <td>Mentos Seetoo  <td>Add Timer manage object.
  * </table>
  *
  ==============================================================================
                            How to use this driver  
  ==============================================================================
    @note
      -# 
		
    @warning
      -# 
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
/* Includes ------------------------------------------------------------------*/
#include "drv_gpio.h"
#include "drv_timer.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
EXTI_GPIOx Exti_GPIO;
/* Private function declarations ---------------------------------------------*/
/* function prototypes -------------------------------------------------------*/
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	switch(GPIO_Pin)
//	{
//		case GPIO_PIN_0: Exti_GPIO.GPIO0.count++;
//			break;
//		case GPIO_PIN_1: 
//		{
//			Exti_GPIO.GPIO1.count++;
//			if(Exti_GPIO.GPIO1.isinit == 0) 
//			{
//				Exti_GPIO.GPIO1.time_bef = Get_SystemTimer();
//				Exti_GPIO.GPIO1.isinit = 1;
//			}
//			else
//			{
//				uint32_t time = 0;
//				time = Get_SystemTimer();
//				Exti_GPIO.GPIO1.inval = (time - Exti_GPIO.GPIO1.time_bef)/1000000.0f;
//				Exti_GPIO.GPIO1.time_bef = time;
//			}
//		}
//			break;
//		case GPIO_PIN_2: Exti_GPIO.GPIO2.count++;
//			break;
//		case GPIO_PIN_3: Exti_GPIO.GPIO3.count++;
//			break;
//		case GPIO_PIN_4: 
//		{
//			Exti_GPIO.GPIO4.count++;
//			if(Exti_GPIO.GPIO4.isinit == 0) 
//			{
//				Exti_GPIO.GPIO4.time_bef = Get_SystemTimer();
//				Exti_GPIO.GPIO4.isinit = 1;
//			}
//			else
//			{
//				uint32_t time = 0;
//				time = Get_SystemTimer();
//				Exti_GPIO.GPIO4.inval = (time - Exti_GPIO.GPIO4.time_bef)/1000000.0f;
//				Exti_GPIO.GPIO4.time_bef = time;
//			}
//		}
//			break;
//		case GPIO_PIN_5: 
//		{
//			Exti_GPIO.GPIO5.count++;
//			if(Exti_GPIO.GPIO5.isinit == 0) 
//			{
//				Exti_GPIO.GPIO5.time_bef = Get_SystemTimer();
//				Exti_GPIO.GPIO5.isinit = 1;
//			}
//			else
//			{
//				uint32_t time = 0;
//				time = Get_SystemTimer();
//				Exti_GPIO.GPIO5.inval = (time - Exti_GPIO.GPIO5.time_bef)/1000000.0f;
//				Exti_GPIO.GPIO5.time_bef = time;
//			}
//		}
//			break;
//		case GPIO_PIN_6: Exti_GPIO.GPIO6.count++;
//			break;
//		case GPIO_PIN_7: Exti_GPIO.GPIO7.count++;
//			break;
//		case GPIO_PIN_8: Exti_GPIO.GPIO8.count++;
//			break;
//		case GPIO_PIN_9: Exti_GPIO.GPIO9.count++;
//			break;
//		case GPIO_PIN_10: Exti_GPIO.GPIO10.count++;
//			break;
//		case GPIO_PIN_11: 
//		{
//			Exti_GPIO.GPIO11.count++;
//			if(Exti_GPIO.GPIO11.isinit == 0) 
//			{
//				Exti_GPIO.GPIO11.time_bef = Get_SystemTimer();
//				Exti_GPIO.GPIO11.isinit = 1;
//			}
//			else
//			{
//				uint32_t time = 0;
//				time = Get_SystemTimer();
//				Exti_GPIO.GPIO11.inval = (time - Exti_GPIO.GPIO11.time_bef)/1000000.0f;
//				Exti_GPIO.GPIO11.time_bef = time;
//			}
//		}
//			break;
//		case GPIO_PIN_12: Exti_GPIO.GPIO12.count++;
//			break;
//		case GPIO_PIN_13: Exti_GPIO.GPIO13.count++;
//			break;
//		default: break;
//	}
//}



/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

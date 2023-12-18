/**
  ******************************************************************************
  * @file    SRML.h
  * @brief   Header to include the whole library.
  * @version 0.0.1
  ******************************************************************************
  * MOST IMPORTANTLY, this library is not open source for developers from other
  * schools' robot team currently. Plz make sure your code is under your supervision.
  * 
  * Thank for @mannychen @HuanpengLu and other pioneers who have put forward such 
  * architechure, and the endeavors of all developers.
  * 
  * By downloading, copying, installing or using the software you agree to this license.
  * If you do not agree to this license, do not download, install,
  * copy or use the software.
  * 
  *                          License Agreement
  *                For SCUT RobotLab Middleware Layer Library
  * 
  * Copyright (c) 2019 - ~, SCUT RobotLab Development Team, all rights reserved.
  * 
  * This file includes all of the headers of SRML.
  * 
  * Before using this library, plz make sure that u have read the README document
  * carefully,  
  *    @note
  *     - Plz do not modifiy this file(Except for developer).
  *     - Plz remember to update the version number.
  */

#include <bsp_config.h>
/* Devices header begin */
#if USE_MPU6050
#include "Devices/MPU6050/mpu6050_config.h"
#endif
#if USE_SRML_FATFS
#include "Devices/Flash/FATFS/diskio.h"
#endif
/* Devices header end */

/* Components header begin */
#if USE_I2C
#include "Components/drv_i2c.h"
#endif
#if USE_SPI
#include "Components/drv_spi.h"
#endif
#if USE_CAN
#include "Components/drv_can.h"
#endif
#if USE_UART
#include "drv_uart.h"
#endif
#if USE_TIMER
#include "drv_timer.h"
#endif
#if USE_FLASH
#include "Components/drv_flash.h"
#endif
/* Components header end */

/* Algorithms header begin */
#if USE_PID
//#include "Algorithm/PID.h"
#endif
#if USE_FILTER
//#include "Algorithm/filters.h"
#endif
#if USE_MYMAT
//#include "Algorithm/myMat.h"
#endif
#if USE_KALMAN
//#include "Algorithm/kalman.h"
#endif
#if USE_TRACK_GENERATOR
//#include "Algorithm/track_generator.h"
#endif
/* Algorithms header end */

/* Protocols header begin */
#if USE_SERIAL_LINE_IP
#include "Protocol/SerialLineIP.h"
#endif
/* Protocols header end */

/* Utilities header begin */
#if USE_MYASSERT
#include "Utility/myAssert.h"
#endif
#if USE_LIST
#include "Utility/linux_list.h"
#endif
#if USE_SYSLOG
#include "Utility/sys_log.h"
#endif
#if USE_SYSANALYSIS
#include "Utility/sys_analysis.h"
#endif
/* Utilities header end */

/**
  * @}
  */


/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

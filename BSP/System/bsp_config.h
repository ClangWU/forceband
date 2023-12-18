#ifndef __SRML_CONFIG_H__
#define __SRML_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Drivers ----------------------------------------------------*/
#define USE_MPU6050                  0
#define USE_FATFS                    0	

#define USE_I2C                      0
#define USE_SPI                      0
#define USE_CAN                      0
#define USE_UART                     1
#define USE_TIMER                    1
#define USE_FLASH                    0
/* Middlewares -----------------------------------------------*/
#define USE_PID                      1
#define USE_FILTER                   0
#define USE_MYMAT                    0
#define USE_KALMAN                   0
#define USE_TRACK_GENERATOR          0

#define USE_SERIAL_LINE_IP           0
  
#define USE_MYASSERT                 0
#define USE_LIST                     0
#define USESYSLOG                    0
#define USE_SYSANALYSIS              0


#ifdef __cplusplus
}
#endif

#endif
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

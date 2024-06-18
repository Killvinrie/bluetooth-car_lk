#ifndef __SCCB_H
#define __SCCB_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "main.h"
#define SCL_H         HAL_GPIO_WritePin(SCCB_SCL_GPIO_Port,SCCB_SCL_Pin , 1)
#define SCL_L         HAL_GPIO_WritePin(SCCB_SCL_GPIO_Port,SCCB_SCL_Pin , 0)
   
#define SDA_H         HAL_GPIO_WritePin(SCCB_SDA_GPIO_Port,SCCB_SDA_Pin , 1)
#define SDA_L         HAL_GPIO_WritePin(SCCB_SDA_GPIO_Port,SCCB_SDA_Pin , 0)

#define SCL_read      HAL_GPIO_ReadPin(SCCB_SCL_GPIO_Port, SCCB_SCL_Pin)
#define SDA_read      HAL_GPIO_ReadPin(SCCB_SDA_GPIO_Port, SCCB_SDA_Pin)

#define ADDR_OV7725   0x42

int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte);
int SCCB_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint8_t ReadAddress);

#endif 

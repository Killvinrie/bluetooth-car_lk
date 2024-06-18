/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern uint8_t Ov7725_vsync;
extern volatile uint8_t frame_count;
void Delay_tick(uint32_t ms);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HREF_Pin GPIO_PIN_2
#define HREF_GPIO_Port GPIOC
#define VSYNC_Pin GPIO_PIN_3
#define VSYNC_GPIO_Port GPIOC
#define VSYNC_EXTI_IRQn EXTI3_IRQn
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define KEY1_EXTI_IRQn EXTI0_IRQn
#define RRST_Pin GPIO_PIN_2
#define RRST_GPIO_Port GPIOA
#define FIFO_OE_Pin GPIO_PIN_3
#define FIFO_OE_GPIO_Port GPIOA
#define DC_Pin GPIO_PIN_4
#define DC_GPIO_Port GPIOA
#define WRST_Pin GPIO_PIN_4
#define WRST_GPIO_Port GPIOC
#define RCLK_Pin GPIO_PIN_5
#define RCLK_GPIO_Port GPIOC
#define LED_G_Pin GPIO_PIN_0
#define LED_G_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_1
#define CS_GPIO_Port GPIOB
#define D2_Pin GPIO_PIN_10
#define D2_GPIO_Port GPIOB
#define D3_Pin GPIO_PIN_11
#define D3_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_13
#define D5_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_14
#define D6_GPIO_Port GPIOB
#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOB
#define HC05_TX_Pin GPIO_PIN_8
#define HC05_TX_GPIO_Port GPIOD
#define HC05_RX_Pin GPIO_PIN_9
#define HC05_RX_GPIO_Port GPIOD
#define SCCB_SCL_Pin GPIO_PIN_6
#define SCCB_SCL_GPIO_Port GPIOC
#define SCCB_SDA_Pin GPIO_PIN_7
#define SCCB_SDA_GPIO_Port GPIOC
#define CH340TX_Pin GPIO_PIN_9
#define CH340TX_GPIO_Port GPIOA
#define CH340RX_Pin GPIO_PIN_10
#define CH340RX_GPIO_Port GPIOA
#define FIFO_WEN_Pin GPIO_PIN_3
#define FIFO_WEN_GPIO_Port GPIOD
#define MPU6050_SCL_Pin GPIO_PIN_6
#define MPU6050_SCL_GPIO_Port GPIOB
#define MPU6050_SDA_Pin GPIO_PIN_7
#define MPU6050_SDA_GPIO_Port GPIOB
#define D0_Pin GPIO_PIN_8
#define D0_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_9
#define D1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

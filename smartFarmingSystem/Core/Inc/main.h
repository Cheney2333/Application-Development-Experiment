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
  void PWM_Breath(int delay_ms);
  void OLEDShow(void);
  void adjustBrightness(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define PWM_LED_Pin GPIO_PIN_0
#define PWM_LED_GPIO_Port GPIOA
#define PWM_MOTOR_Pin GPIO_PIN_6
#define PWM_MOTOR_GPIO_Port GPIOA
#define IN1_Pin GPIO_PIN_14
#define IN1_GPIO_Port GPIOB
#define IN2_Pin GPIO_PIN_15
#define IN2_GPIO_Port GPIOB
#define DHT11_DATA_Pin GPIO_PIN_8
#define DHT11_DATA_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define ADC_CHANNEL_COUNT 1   // ADC通道数量
#define ADC_AVERAGE_COUNT 100 // 单个通道采样值，用来取平均�??
#define V25 1.43              // unit: V
#define AVG_SLOPE 4.3         // unit: mV/摄氏�?
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

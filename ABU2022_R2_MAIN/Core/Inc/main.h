/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f7xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR6_0_Pin GPIO_PIN_13
#define MOTOR6_0_GPIO_Port GPIOC
#define MOTOR6_1_Pin GPIO_PIN_14
#define MOTOR6_1_GPIO_Port GPIOC
#define MOTOR7_0_Pin GPIO_PIN_15
#define MOTOR7_0_GPIO_Port GPIOC
#define MOTOR7_1_Pin GPIO_PIN_0
#define MOTOR7_1_GPIO_Port GPIOF
#define AIR2_0_Pin GPIO_PIN_2
#define AIR2_0_GPIO_Port GPIOF
#define AIR2_1_Pin GPIO_PIN_3
#define AIR2_1_GPIO_Port GPIOF
#define AIR2_2_Pin GPIO_PIN_4
#define AIR2_2_GPIO_Port GPIOF
#define AIR2_3_Pin GPIO_PIN_5
#define AIR2_3_GPIO_Port GPIOF
#define MOTOR0_0_Pin GPIO_PIN_0
#define MOTOR0_0_GPIO_Port GPIOC
#define MOTOR0_1_Pin GPIO_PIN_1
#define MOTOR0_1_GPIO_Port GPIOC
#define MOTOR1_0_Pin GPIO_PIN_2
#define MOTOR1_0_GPIO_Port GPIOC
#define MOTOR1_1_Pin GPIO_PIN_3
#define MOTOR1_1_GPIO_Port GPIOC
#define MOTOR2_0_Pin GPIO_PIN_4
#define MOTOR2_0_GPIO_Port GPIOA
#define MOTOR2_1_Pin GPIO_PIN_6
#define MOTOR2_1_GPIO_Port GPIOA
#define MOTOR3_0_Pin GPIO_PIN_7
#define MOTOR3_0_GPIO_Port GPIOA
#define MOTOR3_1_Pin GPIO_PIN_4
#define MOTOR3_1_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_5
#define LED0_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_2
#define LED3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_11
#define LED4_GPIO_Port GPIOF
#define LED5_Pin GPIO_PIN_12
#define LED5_GPIO_Port GPIOF
#define LED6_Pin GPIO_PIN_13
#define LED6_GPIO_Port GPIOF
#define LED7_Pin GPIO_PIN_14
#define LED7_GPIO_Port GPIOF
#define PUSH_SW0_Pin GPIO_PIN_15
#define PUSH_SW0_GPIO_Port GPIOF
#define PUSH_SW1_Pin GPIO_PIN_0
#define PUSH_SW1_GPIO_Port GPIOG
#define PUSH_SW2_Pin GPIO_PIN_1
#define PUSH_SW2_GPIO_Port GPIOG
#define PUSH_SW3_Pin GPIO_PIN_7
#define PUSH_SW3_GPIO_Port GPIOE
#define AIR3_3_Pin GPIO_PIN_12
#define AIR3_3_GPIO_Port GPIOE
#define AIR3_1_Pin GPIO_PIN_13
#define AIR3_1_GPIO_Port GPIOE
#define AIR3_2_Pin GPIO_PIN_14
#define AIR3_2_GPIO_Port GPIOE
#define AIR3_0_Pin GPIO_PIN_15
#define AIR3_0_GPIO_Port GPIOE
#define MOTOR4_0_Pin GPIO_PIN_8
#define MOTOR4_0_GPIO_Port GPIOD
#define MOTOR4_1_Pin GPIO_PIN_9
#define MOTOR4_1_GPIO_Port GPIOD
#define MOTOR5_0_Pin GPIO_PIN_10
#define MOTOR5_0_GPIO_Port GPIOD
#define MOTOR5_1_Pin GPIO_PIN_11
#define MOTOR5_1_GPIO_Port GPIOD
#define AIR0_0_Pin GPIO_PIN_0
#define AIR0_0_GPIO_Port GPIOD
#define AIR0_1_Pin GPIO_PIN_1
#define AIR0_1_GPIO_Port GPIOD
#define AIR1_0_Pin GPIO_PIN_2
#define AIR1_0_GPIO_Port GPIOD
#define AIR1_1_Pin GPIO_PIN_3
#define AIR1_1_GPIO_Port GPIOD
#define LIMIT_SW0_Pin GPIO_PIN_4
#define LIMIT_SW0_GPIO_Port GPIOD
#define LIMIT_SW1_Pin GPIO_PIN_5
#define LIMIT_SW1_GPIO_Port GPIOD
#define LIMIT_SW2_Pin GPIO_PIN_6
#define LIMIT_SW2_GPIO_Port GPIOD
#define LIMIT_SW3_Pin GPIO_PIN_7
#define LIMIT_SW3_GPIO_Port GPIOD
#define LIMIT_SW4_Pin GPIO_PIN_9
#define LIMIT_SW4_GPIO_Port GPIOG
#define LIMIT_SW5_Pin GPIO_PIN_10
#define LIMIT_SW5_GPIO_Port GPIOG
#define LIMIT_SW6_Pin GPIO_PIN_11
#define LIMIT_SW6_GPIO_Port GPIOG
#define LIMIT_SW7_Pin GPIO_PIN_12
#define LIMIT_SW7_GPIO_Port GPIOG
#define LIMIT_SW8_Pin GPIO_PIN_13
#define LIMIT_SW8_GPIO_Port GPIOG
#define LIMIT_SW9_Pin GPIO_PIN_14
#define LIMIT_SW9_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */
/* define LED */
#define LED0_ON 					(HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET))
#define LED0_OFF 					(HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET))
#define LED0_TOGGLE					(HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin))
#define LED1_ON 					(HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET))
#define LED1_OFF 					(HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET))
#define LED1_TOGGLE 				(HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin))
#define LED2_ON 					(HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET))
#define LED2_OFF 					(HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET))
#define LED2_TOGGLE 				(HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin))
#define LED3_ON 					(HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET))
#define LED3_OFF 					(HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET))
#define LED3_TOGGLE 				(HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin))
#define LED4_ON 					(HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET))
#define LED4_OFF 					(HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET))
#define LED4_TOGGLE					(HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin))
#define LED5_ON 					(HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET))
#define LED5_OFF 					(HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET))
#define LED5_TOGGLE 				(HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin))
#define LED6_ON 					(HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET))
#define LED6_OFF 					(HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET))
#define LED6_TOGGLE 				(HAL_GPIO_TogglePin(LED6_GPIO_Port, LED6_Pin))
#define LED7_ON 					(HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET))
#define LED7_OFF 					(HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET))
#define LED7_TOGGLE 				(HAL_GPIO_TogglePin(LED7_GPIO_Port, LED7_Pin))

/* define PUSH_SW */
#define PUSH_SW0_ON					(HAL_GPIO_ReadPin(PUSH_SW0_GPIO_Port, PUSH_SW0_Pin) == GPIO_PIN_RESET)
#define PUSH_SW0_OFF				(HAL_GPIO_ReadPin(PUSH_SW0_GPIO_Port, PUSH_SW0_Pin) == GPIO_PIN_SET)
#define PUSH_SW1_ON					(HAL_GPIO_ReadPin(PUSH_SW1_GPIO_Port, PUSH_SW1_Pin) == GPIO_PIN_RESET)
#define PUSH_SW1_OFF				(HAL_GPIO_ReadPin(PUSH_SW1_GPIO_Port, PUSH_SW1_Pin) == GPIO_PIN_SET)
#define PUSH_SW2_ON					(HAL_GPIO_ReadPin(PUSH_SW2_GPIO_Port, PUSH_SW2_Pin) == GPIO_PIN_RESET)
#define PUSH_SW2_OFF				(HAL_GPIO_ReadPin(PUSH_SW2_GPIO_Port, PUSH_SW2_Pin) == GPIO_PIN_SET)
#define PUSH_SW3_ON					(HAL_GPIO_ReadPin(PUSH_SW3_GPIO_Port, PUSH_SW3_Pin) == GPIO_PIN_RESET)
#define PUSH_SW3_OFF				(HAL_GPIO_ReadPin(PUSH_SW3_GPIO_Port, PUSH_SW3_Pin) == GPIO_PIN_SET)

/* define LIMIT_SW */
#define LIMIT_SW0_ON				(HAL_GPIO_ReadPin(LIMIT_SW0_GPIO_Port, LIMIT_SW0_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW0_OFF				(HAL_GPIO_ReadPin(LIMIT_SW0_GPIO_Port, LIMIT_SW0_Pin) == GPIO_PIN_SET)
#define LIMIT_SW1_ON				(HAL_GPIO_ReadPin(LIMIT_SW1_GPIO_Port, LIMIT_SW1_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW1_OFF				(HAL_GPIO_ReadPin(LIMIT_SW1_GPIO_Port, LIMIT_SW1_Pin) == GPIO_PIN_SET)
#define LIMIT_SW2_ON				(HAL_GPIO_ReadPin(LIMIT_SW2_GPIO_Port, LIMIT_SW2_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW2_OFF				(HAL_GPIO_ReadPin(LIMIT_SW2_GPIO_Port, LIMIT_SW2_Pin) == GPIO_PIN_SET)
#define LIMIT_SW3_ON				(HAL_GPIO_ReadPin(LIMIT_SW3_GPIO_Port, LIMIT_SW3_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW3_OFF				(HAL_GPIO_ReadPin(LIMIT_SW3_GPIO_Port, LIMIT_SW3_Pin) == GPIO_PIN_SET)
#define LIMIT_SW4_ON				(HAL_GPIO_ReadPin(LIMIT_SW4_GPIO_Port, LIMIT_SW4_Pin) == GPIO_PIN_SET)
#define LIMIT_SW4_OFF				(HAL_GPIO_ReadPin(LIMIT_SW4_GPIO_Port, LIMIT_SW4_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW5_ON				(HAL_GPIO_ReadPin(LIMIT_SW5_GPIO_Port, LIMIT_SW5_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW5_OFF				(HAL_GPIO_ReadPin(LIMIT_SW5_GPIO_Port, LIMIT_SW5_Pin) == GPIO_PIN_SET)
#define LIMIT_SW6_ON				(HAL_GPIO_ReadPin(LIMIT_SW6_GPIO_Port, LIMIT_SW6_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW6_OFF				(HAL_GPIO_ReadPin(LIMIT_SW6_GPIO_Port, LIMIT_SW6_Pin) == GPIO_PIN_SET)
#define LIMIT_SW7_ON				(HAL_GPIO_ReadPin(LIMIT_SW7_GPIO_Port, LIMIT_SW7_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW7_OFF				(HAL_GPIO_ReadPin(LIMIT_SW7_GPIO_Port, LIMIT_SW7_Pin) == GPIO_PIN_SET)
#define LIMIT_SW8_ON				(HAL_GPIO_ReadPin(LIMIT_SW8_GPIO_Port, LIMIT_SW8_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW8_OFF				(HAL_GPIO_ReadPin(LIMIT_SW8_GPIO_Port, LIMIT_SW8_Pin) == GPIO_PIN_SET)
#define LIMIT_SW9_ON				(HAL_GPIO_ReadPin(LIMIT_SW9_GPIO_Port, LIMIT_SW9_Pin) == GPIO_PIN_RESET)
#define LIMIT_SW9_OFF				(HAL_GPIO_ReadPin(LIMIT_SW9_GPIO_Port, LIMIT_SW9_Pin) == GPIO_PIN_SET)

/*
 * AIR0_0		disc1_0
 * AIR0_1		disc1_1
 * AIR1_0		disc1_table0
 * AIR1_1		disc1_table1
 * AIR2_0		pile0_1
 * AIR2_1		pile0_0
 * AIR2_2		pile1_1
 * AIR2_3		pile1_0
 */
/* define AIR */
#define AIR0_0_ON					(HAL_GPIO_WritePin(AIR0_0_GPIO_Port, AIR0_0_Pin, GPIO_PIN_RESET))
#define AIR0_0_OFF					(HAL_GPIO_WritePin(AIR0_0_GPIO_Port, AIR0_0_Pin, GPIO_PIN_SET))
#define AIR0_1_ON					(HAL_GPIO_WritePin(AIR0_1_GPIO_Port, AIR0_1_Pin, GPIO_PIN_RESET))
#define AIR0_1_OFF					(HAL_GPIO_WritePin(AIR0_1_GPIO_Port, AIR0_1_Pin, GPIO_PIN_SET))
#define AIR1_0_ON					(HAL_GPIO_WritePin(AIR1_0_GPIO_Port, AIR1_0_Pin, GPIO_PIN_RESET))
#define AIR1_0_OFF					(HAL_GPIO_WritePin(AIR1_0_GPIO_Port, AIR1_0_Pin, GPIO_PIN_SET))
#define AIR1_1_ON					(HAL_GPIO_WritePin(AIR1_1_GPIO_Port, AIR1_1_Pin, GPIO_PIN_RESET))
#define AIR1_1_OFF					(HAL_GPIO_WritePin(AIR1_1_GPIO_Port, AIR1_1_Pin, GPIO_PIN_SET))
#define AIR2_0_ON					(HAL_GPIO_WritePin(AIR2_0_GPIO_Port, AIR2_0_Pin, GPIO_PIN_SET))
#define AIR2_0_OFF					(HAL_GPIO_WritePin(AIR2_0_GPIO_Port, AIR2_0_Pin, GPIO_PIN_RESET))
#define AIR2_1_ON					(HAL_GPIO_WritePin(AIR2_1_GPIO_Port, AIR2_1_Pin, GPIO_PIN_SET))
#define AIR2_1_OFF					(HAL_GPIO_WritePin(AIR2_1_GPIO_Port, AIR2_1_Pin, GPIO_PIN_RESET))
#define AIR2_2_ON					(HAL_GPIO_WritePin(AIR2_2_GPIO_Port, AIR2_2_Pin, GPIO_PIN_SET))
#define AIR2_2_OFF					(HAL_GPIO_WritePin(AIR2_2_GPIO_Port, AIR2_2_Pin, GPIO_PIN_RESET))
#define AIR2_3_ON					(HAL_GPIO_WritePin(AIR2_3_GPIO_Port, AIR2_3_Pin, GPIO_PIN_SET))
#define AIR2_3_OFF					(HAL_GPIO_WritePin(AIR2_3_GPIO_Port, AIR2_3_Pin, GPIO_PIN_RESET))

#define AIR3_0_ON					(HAL_GPIO_WritePin(AIR3_0_GPIO_Port, AIR3_0_Pin, GPIO_PIN_SET))
#define AIR3_0_OFF					(HAL_GPIO_WritePin(AIR3_0_GPIO_Port, AIR3_0_Pin, GPIO_PIN_RESET))
#define AIR3_1_ON					(HAL_GPIO_WritePin(AIR3_1_GPIO_Port, AIR3_1_Pin, GPIO_PIN_SET))
#define AIR3_1_OFF					(HAL_GPIO_WritePin(AIR3_1_GPIO_Port, AIR3_1_Pin, GPIO_PIN_RESET))
#define AIR3_2_ON					(HAL_GPIO_WritePin(AIR3_2_GPIO_Port, AIR3_2_Pin, GPIO_PIN_SET))
#define AIR3_2_OFF					(HAL_GPIO_WritePin(AIR3_2_GPIO_Port, AIR3_2_Pin, GPIO_PIN_RESET))
#define AIR3_3_ON					(HAL_GPIO_WritePin(AIR3_3_GPIO_Port, AIR3_3_Pin, GPIO_PIN_SET))
#define AIR3_3_OFF					(HAL_GPIO_WritePin(AIR3_3_GPIO_Port, AIR3_3_Pin, GPIO_PIN_RESET))

enum {
	lagori_init,			// 初期状態
	lagori_reset,			// 初期化
	lagori_arm_mode,		// 待機状態
	lagori_disc_fix,		// 立っているディスクを直す
	lagori_arm_on,			// ディスクをつかむ
	lagori_lift_up,			// 昇降を上げる
	partition_on,			// 仕切りを出す
	lagori_arm_off,			// ディスクをはなす
	partition_off,			// 仕切りを戻す
	lagori_lift_down,		// 昇降を下げる
	lagori_pile,			// 収納したディスクを積む
	pile2
} lagori_mode;

enum {
	mode1,
	mode2
} pile_mode;

enum {
	mode_on,
	mode_off
} arm_mode;

enum {
	air_on,
	air_off
} air_mode1;

enum {
	air2_on,
	air2_off
} air_mode2;

enum {
	camera_on1,
	camera_on2,
	camera_off
} camera_state;

enum {
	part_on,
	part_off
} partition_mode;

enum {
	no_air,
	air_up_on,
	air_down_on,
} partition_air;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

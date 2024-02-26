/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can_com.h"
#include "control.h"
#include "control_main.h"
#include "controller.h"
#include "encoder.h"
#include "motor.h"
#include "servo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void initialize();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t pid_stats = 0;
uint8_t disc_number = 0;
uint8_t pile_state = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_CAN2_Init();
  MX_TIM4_Init();
  MX_TIM9_Init();
  MX_TIM12_Init();
  MX_CAN3_Init();
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  initialize();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  print("lagori_mode = %d:disc_num = %d\r\n",lagori_mode,get_raspi1().disc);
	  switch (lagori_mode)
	  {
	  case lagori_init:
		  if(GetController().bits.Maru)
		  {
			  LED0_OFF;
			  LED1_OFF;
			  LED2_OFF;
			  LED3_OFF;
			  lagori_mode = lagori_reset;
		  }
		  break;

	  case lagori_reset:
		  while(LIMIT_SW6_OFF)
		  {
			  Motor_6(40);
		  }

		  if(LIMIT_SW6_ON)
		  {
			  Motor_6(0);
		  }

		  while(LIMIT_SW4_OFF)
		  {
			  Motor_5(-15);
		  }

		  if(LIMIT_SW4_ON)
		  {
			  Motor_5(0);
		  }

		  if(LIMIT_SW0_OFF)
		  {
			  Motor_0(-35);
		  }
		  else if(LIMIT_SW0_ON)
		  {
			  LED0_ON;
			  Motor_0(0);
		  }

		  if(LIMIT_SW1_OFF)
		  {
			  Motor_1(-17);
		  }
		  else if(LIMIT_SW1_ON)
		  {
			  LED1_ON;
			  Motor_1(0);
		  }

		  if(LIMIT_SW2_OFF)
		  {
			  Motor_2(-30);
		  }
		  else if(LIMIT_SW2_ON)
		  {
			  LED2_ON;
			  Motor_2(0);
		  }

		  if(LIMIT_SW3_OFF)
		  {
			  Motor_3(-17);
		  }
		  else if(LIMIT_SW3_ON)
		  {
			  LED3_ON;
			  Motor_3(0);
		  }

		  if(LIMIT_SW0_ON && LIMIT_SW1_ON && LIMIT_SW2_ON && LIMIT_SW3_ON)
		  {
			  LED0_ON;
			  LED1_ON;
			  LED2_ON;
			  LED3_ON;
			  Motor_0(0);
			  Motor_1(0);
			  Motor_2(0);
			  Motor_3(0);
			  Motor_6(0);

			  HAL_Delay(200);

			  set_lift_r(0.01);
			  set_lift_l(0);
			  set_arm_right(0);
			  set_arm_left(0);
			  set_partition(0.0);

			  set_target_arm_right(0);
			  set_target_arm_left(0);
			  set_target_lift_right(0);
			  set_target_lift_left(0);
			  set_target_partition(0.0);
			  pid_stats = 1;

			  HAL_Delay(200);

			  lagori_mode = lagori_arm_mode;
		  }
		  break;

	  case lagori_arm_mode:
		  if(GetController().bits.Maru)
		  {
			  set_target_arm_right(get_arm_right_value());
			  set_target_arm_left(get_arm_left_value());
			  pid_stats = 1;
			  if(camera_state == camera_on1)
			  {
				  if(pile_mode == mode1)
				  {
					  disc_number = get_raspi1().disc_camera1;
				  }
				  else if(pile_mode == mode2)
				  {
					  disc_number = get_raspi1().disc_camera2;
				  }

				  if(disc_number >= 1 && disc_number <= 5)
				  {
					  if(get_raspi1().state)
					  {
						  while(arm_ready(0.0) == 0)
						  {
							  LED1_TOGGLE;
						  }
						  lagori_mode = lagori_disc_fix;
					  }
					  else
					  {
						  lagori_mode = lagori_arm_on;
					  }
				  }
			  }
			  else if(camera_state == camera_on2)
			  {
				  if((get_raspi1().disc_camera1 >= 1) && (get_raspi1().disc_camera1 <= 5))
				  {
					  disc_number = get_raspi1().disc_camera1;
				  }
				  else if((get_disc_count() >= 1) && (get_disc_count() <= 5))
				  {
					  disc_number = get_disc_count();
				  }

				  if(disc_number >= 1 && disc_number <= 5)
				  {
					  lagori_mode = lagori_arm_on;
				  }
			  }
		  }
		  else if(GetController().bits.Sankaku)
		  {
			  lagori_mode = lagori_pile;
		  }
		  else if(GetController().bits.Shikaku)
		  {
			  disc_count();
		  }
		  else if(GetController().bits.Batu)
		  {
			  pid_stats = 0;
			  arm_mode_change();
		  }
		  else if(GetController().bits.Start)
		  {
			  camera_state_change();
		  }
		  break;

	  case lagori_disc_fix:
		  switch(disc_number)
		  {
		  case 1:
			  while(lift_right_ready(0.167) == 0)
			  {
				  LED0_TOGGLE;
			  }
			  break;

		  case 2:
			  while(lift_right_ready(0.18) == 0)
			  {
				  LED0_TOGGLE;
			  }

			  break;

		  case 3:
			  while(lift_right_ready(0.26) == 0)
			  {
				  LED0_TOGGLE;
			  }

			  break;

		  case 4:
			  while(lift_right_ready(0.28) == 0)
			  {
				  LED0_TOGGLE;
			  }

			  break;

		  case 5:
			  while(lift_right_ready(0.38) == 0)
			  {
				  LED0_TOGGLE;
			  }

			  break;
		  }

		  while(arm_right_ready(0.4) == 0)
		  {
			  LED1_TOGGLE;
			  Motor_7(50);
		  }

		  if(disc_number == 1)
		  {
			  while(lift_right_ready(0.24) == 0)
			  {
				  LED0_TOGGLE;
			  }
		  }

		  while(arm_right_ready(0.0) == 0)
		  {
			  LED1_TOGGLE;
		  }
		  HAL_Delay(1200);

		  while(lift_right_ready(0.0) == 0)
		  {
			  LED0_TOGGLE;
		  }

		  reset_value();
		  lagori_mode = lagori_arm_mode;

		  break;

	  case lagori_arm_on:
		  switch(disc_number)
		  {
		  case 1:
			  arm_right_ready(0.29);

			  while(arm_left_ready(0.32) == 0)
			  {
				  LED1_TOGGLE;
			  }
			  arm_left_ready(0.35);

			  break;

		  case 2:
			  arm_left_ready(0.12);

			  while(arm_right_ready(0.365) == 0)
			  {
				  LED1_TOGGLE;
			  }
			  arm_right_ready(0.4);

			  break;

		  case 3:
			  arm_left_ready(0.145);

			  while(arm_right_ready(0.270) == 0)
			  {
				  LED1_TOGGLE;
			  }
			  arm_right_ready(0.31);
			  break;

		  case 4:
			  arm_left_ready(0.09);

			  while(arm_right_ready(0.17) == 0)
			  {
				  LED1_TOGGLE;
			  }
			  arm_right_ready(0.24);
			  break;

		  case 5:
			  arm_left_ready(0.1);

			  while(arm_right_ready(0.11) == 0)
			  {
				  LED1_TOGGLE;
			  }
			  arm_right_ready(0.15);

			  break;
		  }

		  HAL_Delay(100);
		  lagori_mode = lagori_lift_up;

		  break;

	  case lagori_lift_up:
		  switch(disc_number)
		  {
		  case 1:
			  lift_up_1();

			  break;

		  case 2:
			  lift_up_2();
			  break;

		  case 3:
			  lift_up_3();
			  break;

		  case 4:
			  if(camera_state == camera_on1)
			  {
				  while(!lift_ready(HIGHT4_CAMERA))
				  {
					  LED0_TOGGLE;
				  }
				  partition_mode = part_on;
				  partition_air = air_down_on;
			  }
			  else
			  {
				  while(!lift_ready(HIGHT4))
				  {
					  LED0_TOGGLE;
				  }
			  }
			  break;

		  case 5:
			  if(camera_state == camera_on1)
			  {
				  while(!lift_ready(HIGHT5))
				  {
					  LED0_TOGGLE;
				  }
				  partition_mode = part_off;
			  }
			  else
			  {
				  while(!lift_ready(HIGHT5))
				  {
					  LED0_TOGGLE;
				  }
			  }
			  break;
		  }

		  if(camera_state == camera_on1)
		  {
			  if(partition_air == air_up_on)
			  {
				  AIR2_0_OFF;
			  }
			  else if(partition_air == air_down_on)
			  {
				  AIR2_1_OFF;
			  }

			  if(partition_mode == part_on)
			  {
				  lagori_mode = partition_on;
			  }
			  else
			  {
				  while(1)
				  {
					  if(GetController().bits.Maru)
					  {
						  lagori_mode = lagori_arm_off;
						  break;
					  }

					  if(disc_number == 1)
					  {
						  if(GetController().bits.Batu)
						  {
							  arm_left_ready(0.44);
							  arm_right_ready(0.22);
						  }
						  else if(GetController().bits.Sankaku)
						  {
							  arm_right_ready(0.44);
							  arm_left_ready(0.22);
						  }
					  }
					  else if(disc_number == 2)
					  {
						  if(GetController().bits.Batu)
						  {
							  arm_left_ready(0.28);
							  arm_right_ready(0.27);
						  }
						  else if(GetController().bits.Sankaku)
						  {
							  arm_right_ready(0.44);
							  arm_left_ready(0.14);
						  }
					  }
				  }
			  }
		  }
		  else
		  {
			  while(1)
			  {
				  if(GetController().bits.Maru)
				  {
					  lagori_mode = lagori_arm_off;
					  break;
				  }

				  if(disc_number == 1)
				  {
					  if(GetController().bits.Batu)
					  {
						  arm_left_ready(0.44);
						  arm_right_ready(0.22);
					  }
					  else if(GetController().bits.Sankaku)
					  {
						  arm_right_ready(0.44);
						  arm_left_ready(0.22);
					  }
				  }
				  else if(disc_number == 2)
				  {
					  if(GetController().bits.Batu)
					  {
						  arm_left_ready(0.28);
						  arm_right_ready(0.27);
					  }
					  else if(GetController().bits.Sankaku)
					  {
						  arm_right_ready(0.44);
						  arm_left_ready(0.14);
					  }
				  }
			  }
		  }
		  break;

	  case partition_on:
		  pile_state = 0;
		  if(disc_number == 4)
		  {
			  while(partition_ready(2.1) == 0)
			  {
				  LED2_TOGGLE;
			  }
		  }
		  else
		  {
			  while(partition_ready(2.0) == 0)
			  {
				  LED2_TOGGLE;
			  }
		  }

		  lagori_mode = lagori_arm_off;
		  break;

	  case lagori_arm_off:
		  while(arm_ready(0.0) == 0)
		  {
			  LED1_TOGGLE;
		  }

		  if(camera_state == camera_on1)
		  {
			  if(disc_number == 5)
			  {
				  lift_ready(0.22);
			  }
			  else if(partition_mode == part_on)
			  {
				  if((disc_number == 2 || disc_number == 3) && (partition_air != air_down_on))
				  {
					  lift_ready(0.0);
				  }
			  }
		  }

		  if(camera_state == camera_on1)
		  {
			  if(partition_mode == part_on)
			  {
				  if(partition_air == air_up_on)
				  {
					  AIR2_0_ON;
					  HAL_Delay(40);
				  }
				  else if(partition_air == air_down_on)
				  {
					  AIR2_1_ON;
					  HAL_Delay(80);
				  }
				  lagori_mode = partition_off;
				  HAL_Delay(20);
			  }
			  else if(disc_number == 5)
			  {
				  while(1)
				  {
					  if(GetController().bits.Batu)
					  {
						  lagori_mode = lagori_lift_down;
						  break;
					  }
					  else if(GetController().bits.Sankaku)
					  {
						  lagori_mode = lagori_pile;
						  break;
					  }
				  }
			  }
			  else
			  {
				  while(1)
				  {
					  if(GetController().bits.Maru)
					  {
						  lagori_mode = lagori_lift_down;
						  break;
					  }
				  }
			  }
		  }
		  else if(camera_state == camera_on2 || camera_state == camera_off)
		  {
			  while(1)
			  {
				  if(GetController().bits.Maru)
				  {
					  lagori_mode = lagori_lift_down;
					  break;
				  }
			  }
		  }
		  break;

	  case partition_off:
		  AIR3_0_OFF;
		  AIR3_1_OFF;
		  AIR3_2_OFF;
		  pile_state = 0;
		  partition_ready(0.23);
		  HAL_Delay(400);

		  if(partition_air == air_down_on)
		  {
			  lift_ready(0.0);
		  }

		  reset_value();
		  partition_air = no_air;
		  partition_mode = part_off;
		  lagori_mode = lagori_arm_mode;
		  break;

	  case lagori_lift_down:
		  while(lift_ready(0.0) == 0)
		  {
			  LED0_TOGGLE;
		  }

		  AIR3_0_OFF;
		  AIR3_1_OFF;
		  AIR3_2_OFF;
		  reset_value();
		  partition_air = no_air;
		  partition_mode = part_off;
		  lagori_mode = lagori_arm_mode;
		  break;

	  case lagori_pile:
		  pile_state = 0;
		  partition_ready(1.95);

		  if(partition_ready(1.95))
		  {
			  AIR2_0_OFF;
			  AIR2_1_OFF;

			  if(LIMIT_SW5_OFF)
			  {
				  Motor_6(-70);
			  }
			  else if(LIMIT_SW5_ON)
			  {
				  Motor_6(0);
				  AIR2_0_OFF;
				  AIR2_1_OFF;
				  HAL_Delay(150);
				  lagori_mode = pile2;
			  }
		  }
		  else if(get_partition_value() > 1.4 && get_partition_value() < 1.7)
		  {
			  if(LIMIT_SW5_OFF)
			  {
				  Motor_6(-70);
			  }
			  else if(LIMIT_SW5_ON)
			  {
				  Motor_6(0);
			  }
		  }
		  break;

	  case pile2:
		  pile_state = 1;
		  while(partition_ready(0.5) == 0)
		  {
			  LED2_TOGGLE;
		  }

		  pile_state = 0;
		  while(partition_ready(0.05) == 0)
		  {
			  LED2_TOGGLE;
		  }

		  while(LIMIT_SW6_OFF)
		  {
			  Motor_6(50);
		  }

		  if(LIMIT_SW6_ON)
		  {
			  Motor_6(0);
		  }

		  while(1)
		  {
			  if(GetController().bits.Maru)
			  {
				  AIR3_0_OFF;
				  AIR3_1_OFF;
				  AIR3_2_OFF;
				  reset_value();
				  partition_air = no_air;
				  partition_mode = part_off;
				  lagori_mode = lagori_lift_down;
				  break;
			  }
		  }
		  break;
	  }

	  if(GetController().bits.Up)
	  {
		  air_mode_change1();
	  }
//	  else if(GetController().bits.Down)
//	  {
//		  air_mode_change2();
//	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void initialize()
{
	InitCan();
	init_encoder();
	motor_on_init();
	init_pid_value();
	AIR2_0_OFF;
	AIR2_1_OFF;

	AIR3_0_OFF;
	AIR3_1_OFF;
	AIR3_2_OFF;
	AIR3_3_OFF;

	lagori_mode = lagori_init;
	arm_mode = mode_on;
	pile_mode = mode1;
	air_mode1 = air_on;
	air_mode2 = air2_off;
	camera_state = camera_on1;
	partition_mode = part_off;
	partition_air = no_air;
	disc_number = 0;
	pid_stats = 0;
	init_raspi1_value();
	reset_loss_count();
	setdata(1);
	setdata_part(0);

	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// 25msec
	if (htim == &htim6){
		enc_update();
		UpdateCan_raspi1();

		if(GetController().bits.L_2 || GetController().bits.Select)
		{
			reset_counter();

			if(get_reset_count() > 5)
			{
				All_Motor(0);
				pid_stats = 0;
				HAL_NVIC_SystemReset();
			}
		}
		else
		{
			if(pid_stats)
			{
				control_on_update();
				if(pile_state){
					partition_control_pile();
				}else{
					partition_control();
				}
			}
		}
		slicer();
		disc_led();
	}

	// 50msec
	if(htim == &htim7){
		UpdateController();
		SendData();
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

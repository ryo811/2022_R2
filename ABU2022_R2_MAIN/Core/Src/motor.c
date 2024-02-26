/*
 * motor.c
 *
 *  Created on: 2021/02/23
 *      Author: 涼
 */

#include "motor.h"

/**
 * @brief モータの初期化
 */
void motor_on_init() {
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);		// motor0
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);		// motor1
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);		// motor2
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);		// motor3
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);		// motor4
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);		// motor5
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);		// motor6
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);		// motor7
}

/**
 * @brief モータの緊急停止
 */
void stop_motor_pwm() {
	HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
}

/****************************************************************************
 * @function  	:motor_control
 * @explain		:
 * @parameter 	[int](motor_number)各モーターの識別番号
 * @parameter 	[int](percentage)出力パーセンテージ（正負で回転方向を判断）
 * @caution		パーセンテージ95以上でブレーキ
 ***************************************************************************/
/**
 * @brief 各モーターに任意の出力と方向でPWMを出す関数
 * @brief パーセンテージ95より上でブレーキ?
 * @param motor_number: 各モーターの識別番号
 * @param percentage: 出力パーセンテージ（正負で回転方向を判断）
 */
void motor_control(int motor_number, int percentage) {
	int output = 0;
	int direction = 1;

	if (percentage < 0) {
		direction = -1;
		percentage = -percentage;
	}

	//ブレーキ?
	if (percentage > 95) {
		while(1){
			Motor_0(0);
		}
	}

	//フリー(ResRes)
	if (percentage == 0) {
		direction = 2;
	}

	switch (motor_number) {
	case 0:
		motor_output_connecter(MOTOR0_0_GPIO_Port, MOTOR0_0_Pin,
		MOTOR0_1_GPIO_Port, MOTOR0_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, output);

		break;
	case 1:
		motor_output_connecter(MOTOR1_0_GPIO_Port, MOTOR1_0_Pin,
				MOTOR1_1_GPIO_Port, MOTOR1_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, output);

		break;
	case 2:
		motor_output_connecter(MOTOR2_0_GPIO_Port, MOTOR2_0_Pin,
				MOTOR2_1_GPIO_Port, MOTOR2_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, output);

		break;
	case 3:
		motor_output_connecter(MOTOR3_0_GPIO_Port, MOTOR3_0_Pin,
				MOTOR3_1_GPIO_Port, MOTOR3_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, output);

		break;
	case 4:
		motor_output_connecter(MOTOR4_0_GPIO_Port, MOTOR4_0_Pin,
				MOTOR4_1_GPIO_Port, MOTOR4_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, output);

		break;
	case 5:
		motor_output_connecter(MOTOR5_0_GPIO_Port, MOTOR5_0_Pin,
				MOTOR5_1_GPIO_Port, MOTOR5_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, output);

		break;
	case 6:
		motor_output_connecter(MOTOR6_0_GPIO_Port, MOTOR6_0_Pin,
				MOTOR6_1_GPIO_Port, MOTOR6_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, output);

		break;
	case 7:
		motor_output_connecter(MOTOR7_0_GPIO_Port, MOTOR7_0_Pin,
				MOTOR7_1_GPIO_Port, MOTOR7_1_Pin, direction);

		output = (int) (1079 * ((float) percentage / 100.0));
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, output);

		break;
	default:
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 0);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, 0);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, 0);
		break;
	}
}

/**
 * @brief モータの回転方向の決定
 * @param *MOTOR_0_Port: _0のGPIO_Port
 * @param MOTOR_0_Pin: _0のGPIO_Pin
 * @param *MOTOR_1_Port: _1のGPIO_Port
 * @param MOTOR_1_Pin: _1のGPIO_Pin
 * @param direction: 0で無回転
 */
void motor_output_connecter(GPIO_TypeDef *MOTOR_0_Port, uint16_t MOTOR_0_Pin,
		GPIO_TypeDef *MOTOR_1_Port, uint16_t MOTOR_1_Pin, int direction) {
	switch (direction) {
	case -1:
		HAL_GPIO_WritePin(MOTOR_0_Port, MOTOR_0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_1_Port, MOTOR_1_Pin, GPIO_PIN_SET);
		break;
	case 0:
		HAL_GPIO_WritePin(MOTOR_0_Port, MOTOR_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_1_Port, MOTOR_1_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(MOTOR_0_Port, MOTOR_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_1_Port, MOTOR_1_Pin, GPIO_PIN_RESET);
		break;
	}
}

#include "servo.h"

/*
 * @brief サーボモータの初期化
 */
void init_servo()
{
	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
}

/*
 * @brief サーボモータの緊急停止
 */
void stop_servo_pwm()
{
	HAL_TIM_PWM_Stop(&htim13, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
}

void servo_control(int servo_number, int pulse)
{
	switch(servo_number)
	{
	case 0:
		__HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, pulse);
		break;

	case 1:
		__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, pulse);
		break;

	default:
		__HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 0);
		break;
	}
}

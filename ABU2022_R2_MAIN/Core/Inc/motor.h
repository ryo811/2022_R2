/*
 * motor.h
 *
 *  Created on: 2021/02/23
 *      Author: 豸ｼ
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "tim.h"

/*
 * MOTOR_0		蜿ｳ繧｢繝ｼ繝�
 * MOTOR_1		譏�髯搾ｼ亥承�ｼ�
 * MOTOR_2		蟾ｦ繧｢繝ｼ繝�
 * MOTOR_3		譏�髯搾ｼ亥ｷｦ�ｼ�
 * MOTOR_4
 * MOTOR_5		莉募��繧�
 * MOTOR_6		辷ｪ
 * MOTOR_7
 */
#define Motor_0(percent)					motor_control(0, percent)
#define Motor_1(percent)					motor_control(1, -percent)
#define Motor_2(percent)					motor_control(2, -percent)
#define Motor_3(percent)					motor_control(3, percent)
#define Motor_4(percent)					motor_control(4, percent)
#define Motor_5(percent)					motor_control(5, percent)
#define Motor_6(percent)					motor_control(6, percent)
#define Motor_7(percent)					motor_control(7, percent)
#define All_Motor(percent)					(Motor_0(percent), Motor_1(percent), Motor_2(percent), Motor_3(percent), Motor_4(percent), Motor_5(percent), Motor_6(percent), Motor_7(percent))

void motor_on_init();
void stop_motor_pwm();
void motor_control(int motor_number, int percentage);
void motor_output_connecter(GPIO_TypeDef *MOTOR_0_Port, uint16_t MOTOR_0_Pin,
		GPIO_TypeDef *MOTOR_1_Port, uint16_t MOTOR_1_Pin, int direction);

#endif /* INC_MOTOR_H_ */

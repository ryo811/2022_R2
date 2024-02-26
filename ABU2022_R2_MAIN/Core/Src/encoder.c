/*
 * encoder.c
 *
 *  Created on: 2021/02/22
 *      Author: 涼
 */

#include "encoder.h"

static float arm_right_value;
static float arm_left_value;
static lift_value lift_right;
static lift_value lift_left;
static float partition_value;

void init_encoder(void){
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);		//encoder0
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);		//encoder1
	HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);		//encoder2
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);		//encoder3
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);		//encoder4

	__HAL_TIM_SET_COUNTER(&htim2, ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim1, ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim8, ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim3, ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim4, ENC_ZERO_POINT);
}

int32_t get_encoder0(void){
	register int32_t diff = 0;

	diff = -(__HAL_TIM_GET_COUNTER(&htim2) - ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim2, ENC_ZERO_POINT);

	return diff;
}

int32_t get_encoder1(void){
	register int32_t diff = 0;

	diff = (__HAL_TIM_GET_COUNTER(&htim1) - ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim1, ENC_ZERO_POINT);

	return diff;
}

int32_t get_encoder2(void){
	register int32_t diff = 0;

	diff = (__HAL_TIM_GET_COUNTER(&htim8) - ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim8, ENC_ZERO_POINT);

	return diff;
}

int32_t get_encoder3(void){
	register int32_t diff = 0;

	diff = -(__HAL_TIM_GET_COUNTER(&htim3) - ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim3, ENC_ZERO_POINT);

	return diff;
}

int32_t get_encoder4(void){
	register int32_t diff = 0;

	diff = -(__HAL_TIM_GET_COUNTER(&htim4) - ENC_ZERO_POINT);
	__HAL_TIM_SET_COUNTER(&htim4, ENC_ZERO_POINT);

	return diff;
}

void enc_update(void)
{
//	print("enc0: %d enc1: %d enc2: %d enc3: %d\n\r", get_encoder0(), get_encoder1(), get_encoder2(), get_encoder3());

	lift_right.velocity = (float)((get_encoder1()) * ENCODER_COEFFICIENT_LIFT) / 0.025;
	lift_right.position += lift_right.velocity * 0.025 ;
	lift_left.velocity = (float)((get_encoder3()) * ENCODER_COEFFICIENT_LIFT) / 0.025;
	lift_left.position += lift_left.velocity * 0.025;
	arm_right_value += (float)(get_encoder0()) * ENCODER_COEFFICIENT_ARM;
	arm_left_value += (float)(get_encoder2()) * ENCODER_COEFFICIENT_ARM;
//	partition_value += (float)((get_encoder4() / (EDGE_EVALUATION * ENCODER_PULSE)) * D_PI);
	partition_value += (float)((get_encoder4() / (2.0 * ENCODER_PULSE)) * D_PI);

//	print("pos lift_r: %f lift_l: %f\n\r", lift_right.position, lift_left.position);
//	print("vel lift_r: %f lift_l: %f\n\r", lift_right.velocity, lift_left.velocity);
//	print("arm_r: %f arm_l: %f\n\r", arm_right_value, arm_left_value);
//	print("rad: %f\n\r", partition_value);
//	print("angle: %f\n\r", angle(partition_value));

}

float get_arm_right_value(void)
{
	return arm_right_value;
}

float get_arm_left_value(void)
{
	return arm_left_value;
}

lift_value get_lift_right_value(void)
{
	return lift_right;
}

lift_value get_lift_left_value(void)
{
	return lift_left;
}

float get_partition_value(void)
{
	return partition_value;
}

void set_lift_r(float value)
{
	lift_right.position = value;
}

void set_lift_l(float value)
{
	lift_left.position = value;
}

void set_arm_right(float value)
{
	arm_right_value = value;
}

void set_arm_left(float value)
{
	arm_left_value = value;
}

void set_partition(float value)
{
	partition_value = value;
}

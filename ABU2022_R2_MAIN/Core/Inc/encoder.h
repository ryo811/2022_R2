/*
 * encoder.h
 *
 *  Created on: 2021/02/22
 *      Author: 涼
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "math.h"
#include "tim.h"
#include "usart.h"
#include "control_main.h"

#define ENC_ZERO_POINT				(0x7FFF)

#define PI_2						(1.57079632)
#define PI_3						(1.04719755)
#define D_PI_3						(2.09439510)
#define PI							(3.14159265f)
#define D_PI						(6.28318530)
#define H_PI						(1.57079632f)
#define Q_PI						(0.78539816f)
#define Q3_PI						(2.35619449f)
#define Q5_PI						(3.92699082f)
#define Q7_PI						(5.49778714f)

#define ENCODER_PULSE				(2048.0f)	// PPR
#define EDGE_EVALUATION				(4.0f)		// 逓倍

//#define ENCODER_DIAMETER_ARM		(0.045f)	//　アーム
//#define ENCODER_DIAMETER_LIFT		(0.02991f)	//　昇降
#define ENCODER_DIAMETER_ARM		(0.045)	//　アーム
#define ENCODER_DIAMETER_LIFT		(0.02991)	//　昇降
#define ENCODER_COEFFICIENT_ARM		(((ENCODER_DIAMETER_ARM * 1.4) * PI) / (EDGE_EVALUATION * ENCODER_PULSE))
#define ENCODER_COEFFICIENT_LIFT	(((ENCODER_DIAMETER_LIFT * 2.1) * PI) / (EDGE_EVALUATION * ENCODER_PULSE))

typedef struct {
	float position;
	float velocity;
} lift_value;

void init_encoder(void);

void update_wheel_velocity(void);

int32_t get_encoder0(void);
int32_t get_encoder1(void);
int32_t get_encoder2(void);
int32_t get_encoder3(void);
void enc_update(void);
float get_arm_right_value(void);
float get_arm_left_value(void);
lift_value get_lift_right_value(void);
lift_value get_lift_left_value(void);
float get_partition_value(void);
void set_lift_r(float value);
void set_lift_l(float value);
void set_arm_right(float value);
void set_arm_left(float value);
void set_partition(float value);

#endif /* INC_ENCODER_H_ */

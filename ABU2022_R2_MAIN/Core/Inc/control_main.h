#ifndef INC_CONTROL_MAIN_H_
#define INC_CONTROL_MAIN_H_

#include "main.h"
#include "motor.h"
#include "pid.h"
#include "control.h"
#include "usart.h"
#include "can_com.h"

#define IS_EQUAL_FROAT_RAD(x,y)			(ABS((x) - (y)) < RAD(5.0))
#define RAD(x)							((x / 180.0) * PI)
#define angle(x)						((x / PI) * 180.0)

enum {
	Gain1,
	Gain2
} Parition_Gain;

#define HIGHT1							1.018	// 1番目のディスクの高さ
#define HIGHT2							0.88	// 2番目のディスクの高さ
#define HIGHT2_CAMERA					1.005	// 2番目のディスクの高さ（仕切り）
#define HIGHT3							0.78	// 3番目のディスクの高さ
#define HIGHT3_CAMERA					0.745	// 3番目のディスクの高さ（仕切り）
#define HIGHT4							0.53	// 4番目のディスクの高さ
#define HIGHT4_CAMERA					0.49	// 4番目のディスクの高さ（仕切り）
#define HIGHT5							0.37	// 5番目のディスクの高さ

// motor_max_output
#define MOTOR_MAX_OUTPUT5_HIGH			80
#define MOTOR_MAX_OUTPUT5_LOW			60
#define MOTOR_MAX_OUTPUT6				70

void init_partition(void);
uint8_t partition_ready(float rad);
void partition_control(void);
void partition_control_pile(void);
void SetPositionGain_partition(pid_gain *gain, float target, float observation_value);
void set_target_partition(float value);

void reset_value(void);

void lift_up_1(void);
void lift_up_2(void);
void lift_up_3(void);
void reset_loss_count(void);

void arm_mode_change(void);
void pile_mode_change(void);
void air_mode_change(void);
void air_mode_change1(void);
void air_mode_change2(void);
void camera_state_change(void);
void disc_count(void);
void reset_disc_count(void);
uint8_t get_disc_count(void);

void reset_counter(void);
uint8_t get_reset_count(void);
void counter_reset(void);

void slicer(void);
void disc_led(void);

#endif /* INC_CONTROL_MAIN_H_ */

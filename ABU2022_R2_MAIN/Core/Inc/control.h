#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#include "motor.h"
#include "usart.h"
#include "pid.h"
#include "math.h"
#include "encoder.h"
#include "controller.h"
#include "control_main.h"

#define IS_EQUAL_FROAT_POSITION_ARM(x,y)	(ABS((x) - (y)) < 0.01)
#define IS_EQUAL_FROAT_POSITION_LIFT(x,y)	(ABS((x) - (y)) < 0.012)
#define IS_EQUAL_FROAT_VELOCITY(x,y) 	(ABS((x) - (y)) < 0.000001)

// motor_max_output
#define MOTOR_MAX_OUTPUT0				80
#define MOTOR_MAX_OUTPUT1				60
#define MOTOR_MAX_OUTPUT2				80
#define MOTOR_MAX_OUTPUT3				60

#define lift_max_velocity				(1.6)

typedef struct {
	float value;
	float prev_value;
	uint8_t count;
	uint8_t check_count;
} check_value;

void error_stop(int output, float encoder_value);

void init_pid_value(void);
void init_arm_right(void);
void init_arm_left(void);
void init_lift_right(void);
void init_lift_left(void);
void reset_pid_value(control_value *control, pid_value *pid);
void control_on_update(void);
uint8_t arm_ready(float position);
uint8_t arm_right_ready(float position);
uint8_t arm_left_ready(float position);
uint8_t lift_ready(float position);
uint8_t lift_right_ready(float position);
uint8_t lift_left_ready(float position);
void arm_right_control(void);
void arm_left_control(void);
void lift_right_control(void);
void lift_left_control(void);
void SetPositionGain_arm(pid_gain *gain, float target, float observation_value);
void SetGain_lift_right(pid_gain *pos_gain, pid_gain *vel_gain, float target, float observation_value);
void SetGain_lift_left(pid_gain *pos_gain, pid_gain *vel_gain, float target, float observation_value);
void set_target_arm_right(float value);
void set_target_arm_left(float value);
void set_target_lift_right(float value);
void set_target_lift_left(float value);
float get_target_arm_right(void);
float get_target_arm_left(void);

#endif /* INC_CONTROL_H_ */

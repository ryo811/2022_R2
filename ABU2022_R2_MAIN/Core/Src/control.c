#include "control.h"

static control_value arm_right_value;
static pid_value arm_right_pid;
static pid_gain arm_right_gain;

static control_value arm_left_value;
static pid_value arm_left_pid;
static pid_gain arm_left_gain;

static control_value lift_r_vel_value;
static pid_value lift_r_vel_pid;
static pid_gain lift_r_vel_gain;

static control_value lift_r_pos_value;
static pid_value lift_r_pos_pid;
static pid_gain lift_r_pos_gain;

static control_value lift_l_vel_value;
static pid_value lift_l_vel_pid;
static pid_gain lift_l_vel_gain;

static control_value lift_l_pos_value;
static pid_value lift_l_pos_pid;
static pid_gain lift_l_pos_gain;

static float target_arm_right;
static float target_arm_left;
static float target_lift_right;
static float target_lift_left;

void init_pid_value(void)
{
	init_arm_right();
	init_arm_left();
	init_lift_right();
	init_lift_left();
	init_partition();
}

void init_arm_right(void){
	arm_right_gain.kp = 4.0f;
	arm_right_gain.ki = 0.14f;
	arm_right_gain.kd = 0.95f;

	arm_right_value.target = 0.0;
	arm_right_value.manipulate = 0.0;
	arm_right_value.output = 0;
	arm_right_pid.prev_prev_bias = 0.0;
	arm_right_pid.prev_bias = 0.0;
	arm_right_pid.bias = 0.0;
	arm_right_pid.prev_op_value = 0.0;
	arm_right_pid.op_value = 0.0;
	arm_right_pid.prev_delta_d = 0.0;
	arm_right_pid.sigma = 0.0;
}

void init_arm_left(void){
//	arm_left_gain.kp = 4.0;
//	arm_left_gain.ki = 0.15f;
//	arm_left_gain.kd = 0.95f;
	arm_left_gain.kp = 4.0;
//	arm_left_gain.ki = 0.012f;
	arm_left_gain.ki = 0.02f;
	arm_left_gain.kd = 0.95f;

	arm_left_value.target = 0.0;
	arm_left_value.manipulate = 0.0;
	arm_left_value.output = 0;
	arm_left_pid.prev_prev_bias = 0.0;
	arm_left_pid.prev_bias = 0.0;
	arm_left_pid.bias = 0.0;
	arm_left_pid.prev_op_value = 0.0;
	arm_left_pid.op_value = 0.0;
	arm_left_pid.prev_delta_d = 0.0;
	arm_left_pid.sigma = 0.0;
}

void init_lift_right(void){
//	lift_r_pos_gain.kp = 2.5f;
//	lift_r_pos_gain.ki = 0.004f;
//	lift_r_pos_gain.kd = 0.98f;

	lift_r_pos_gain.kp = 2.5f;
	lift_r_pos_gain.ki = 0.005f;
	lift_r_pos_gain.kd = 0.98f;

	lift_r_pos_value.target = 0.0;
	lift_r_pos_value.manipulate = 0.0;
	lift_r_pos_value.output = 0;
	lift_r_pos_pid.prev_prev_bias = 0.0;
	lift_r_pos_pid.prev_bias = 0.0;
	lift_r_pos_pid.bias = 0.0;
	lift_r_pos_pid.prev_op_value = 0.0;
	lift_r_pos_pid.op_value = 0.0;
	lift_r_pos_pid.prev_delta_d = 0.0;
	lift_r_pos_pid.sigma = 0.0;

//	lift_r_vel_gain.kp = 1.5f;
//	lift_r_vel_gain.ki = 0.04f;
//	lift_r_vel_gain.kd = 0.98f;

//	lift_r_vel_gain.kp = 1.3f;
//	lift_r_vel_gain.ki = 0.024f;
//	lift_r_vel_gain.kd = 0.98f;

	lift_r_vel_gain.kp = 1.2f;
	lift_r_vel_gain.ki = 0.005f;
	lift_r_vel_gain.kd = 0.98f;

	lift_r_vel_value.target = 0.0;
	lift_r_vel_value.manipulate = 0.0;
	lift_r_vel_value.output = 0;
	lift_r_vel_pid.prev_prev_bias = 0.0;
	lift_r_vel_pid.prev_bias = 0.0;
	lift_r_vel_pid.bias = 0.0;
	lift_r_vel_pid.prev_op_value = 0.0;
	lift_r_vel_pid.op_value = 0.0;
	lift_r_vel_pid.prev_delta_d = 0.0;
	lift_r_vel_pid.sigma = 0.0;
}

void init_lift_left(void){
//	lift_l_pos_gain.kp = 2.7f;
//	lift_l_pos_gain.ki = 0.013f;
//	lift_l_pos_gain.kd = 0.98f;

	lift_l_pos_gain.kp = 2.5f;
	lift_l_pos_gain.ki = 0.005f;
	lift_l_pos_gain.kd = 0.98f;

	lift_l_pos_value.target = 0.0;
	lift_l_pos_value.manipulate = 0.0;
	lift_l_pos_value.output = 0;
	lift_l_pos_pid.prev_prev_bias = 0.0;
	lift_l_pos_pid.prev_bias = 0.0;
	lift_l_pos_pid.bias = 0.0;
	lift_l_pos_pid.prev_op_value = 0.0;
	lift_l_pos_pid.op_value = 0.0;
	lift_l_pos_pid.prev_delta_d = 0.0;
	lift_l_pos_pid.sigma = 0.0;

//	lift_l_vel_gain.kp = 1.5f;
//	lift_l_vel_gain.ki = 0.08f;
//	lift_l_vel_gain.kd = 0.98f;

	lift_l_vel_gain.kp = 1.2f;
	lift_l_vel_gain.ki = 0.005f;
	lift_l_vel_gain.kd = 0.98f;

	lift_l_vel_value.target = 0.0;
	lift_l_vel_value.manipulate = 0.0;
	lift_l_vel_value.output = 0;
	lift_l_vel_pid.prev_prev_bias = 0.0;
	lift_l_vel_pid.prev_bias = 0.0;
	lift_l_vel_pid.bias = 0.0;
	lift_l_vel_pid.prev_op_value = 0.0;
	lift_l_vel_pid.op_value = 0.0;
	lift_l_vel_pid.prev_delta_d = 0.0;
	lift_l_vel_pid.sigma = 0.0;
}

void reset_pid_value(control_value *control, pid_value *pid)
{
	control->manipulate = 0.0;
	control->output = 0;
	pid->prev_prev_bias = 0.0;
	pid->prev_bias = 0.0;
	pid->bias = 0.0;
	pid->prev_op_value = 0.0;
	pid->op_value = 0.0;
	pid->prev_delta_d = 0.0;
	pid->sigma = 0.0;
}

void control_on_update(void)
{
	arm_right_control();
	arm_left_control();
	lift_right_control();
	lift_left_control();
}

uint8_t arm_ready(float position)
{
	uint8_t return_value = 0;

	if(get_arm_right_value() < (position - 0.01) || get_arm_right_value() > (position + 0.01)
			|| get_arm_left_value() < (position - 0.01) || get_arm_left_value() > (position + 0.01))
	{
		target_arm_right = position;
		target_arm_left = position;
	}
	else
	{
		return_value = 1;
	}

	return return_value;
}

uint8_t arm_right_ready(float position)
{
	uint8_t return_value = 0;

	if(get_arm_right_value() < (position - 0.01) || get_arm_right_value() > (position + 0.01))
	{
		target_arm_right = position;
	}
	else
	{
		return_value = 1;
	}

	return return_value;
}

uint8_t arm_left_ready(float position)
{
	uint8_t return_value = 0;

	if(get_arm_left_value() < (position - 0.01) || get_arm_left_value() > (position + 0.01))
	{
		target_arm_left = position;
	}
	else
	{
		return_value = 1;
	}

	return return_value;
}

uint8_t lift_ready(float position)
{
	uint8_t return_value = 0;

	if(get_lift_right_value().position < (position - 0.02) || get_lift_right_value().position > (position + 0.02)
			|| get_lift_left_value().position < (position - 0.012) || get_lift_left_value().position > (position + 0.012))
	{
		target_lift_right = position;
		target_lift_left = position;
	}
	else
	{
		return_value = 1;
	}

	return return_value;
}

uint8_t lift_right_ready(float position)
{
	uint8_t return_value = 0;

	if(get_lift_right_value().position < (position - 0.012) || get_lift_right_value().position > (position + 0.012))
	{
		target_lift_right = position;
	}
	else
	{
		return_value = 1;
	}

	return return_value;
}

uint8_t lift_left_ready(float position)
{
	uint8_t return_value = 0;

	if(get_lift_left_value().position < (position - 0.015) || get_lift_left_value().position > (position + 0.015))
	{
		target_lift_left = position;
	}
	else
	{
		return_value = 1;
	}

	return return_value;
}

void arm_right_control(){
	arm_right_value.target = target_arm_right;

	SetPositionGain_arm(&arm_right_gain, arm_right_value.target, get_arm_right_value());

	if (IS_EQUAL_FROAT_POSITION_ARM(target_arm_right, get_arm_right_value())) {
		//無効時処理
		reset_pid_value(&arm_right_value, &arm_right_pid);
	}
	else
	{
		PID_position_control(get_arm_right_value(), &arm_right_value, &arm_right_pid, &arm_right_gain);
	}

	arm_right_value.output = (int)(arm_right_value.manipulate * MOTOR_MAX_OUTPUT0);

	if(arm_right_value.output < 0)
	{
		if(LIMIT_SW0_ON)
		{
			Motor_0(0);
			set_arm_right(0);
		}
		else
		{
			Motor_0(arm_right_value.output);
		}
	}
	else
	{
		Motor_0(arm_right_value.output);
	}
}

void arm_left_control(){
	arm_left_value.target = target_arm_left;

	SetPositionGain_arm(&arm_left_gain, arm_left_value.target, get_arm_left_value());

	if (IS_EQUAL_FROAT_POSITION_ARM(target_arm_left, get_arm_left_value())) {
		//無効時処理
		reset_pid_value(&arm_left_value, &arm_left_pid);
	}
	else
	{
		PID_position_control(get_arm_left_value(), &arm_left_value, &arm_left_pid, &arm_left_gain);
	}

//	Set_output_value_arm(arm_value.target, get_arm_value());

	arm_left_value.output = (int)(arm_left_value.manipulate * MOTOR_MAX_OUTPUT2);

	if(arm_left_value.output < 0)
	{
		if(LIMIT_SW2_ON)
		{
			Motor_2(0);
			set_arm_left(0);
		}
		else
		{
			Motor_2(arm_left_value.output);
		}
	}
	else
	{
		Motor_2(arm_left_value.output);
	}
}

void lift_right_control(){
	lift_r_pos_value.target = target_lift_right;

	SetGain_lift_right(&lift_r_pos_gain, &lift_r_vel_gain, lift_r_pos_value.target, get_lift_right_value().position);

	// 位置型pid
	if (IS_EQUAL_FROAT_POSITION_LIFT(target_lift_right, get_lift_right_value().position)) {
		//無効時処理
		reset_pid_value(&lift_r_pos_value, &lift_r_pos_pid);
	}
	else
	{
		PID_position_control(get_lift_right_value().position, &lift_r_pos_value, &lift_r_pos_pid, &lift_r_pos_gain);
	}

	lift_r_vel_value.target = lift_r_pos_value.manipulate * lift_max_velocity;

	// 速度型pid
	if (IS_EQUAL_FROAT_VELOCITY(lift_r_vel_value.target, get_lift_right_value().velocity)) {
		//無効時処理
		reset_pid_value(&lift_r_vel_value, &lift_r_vel_pid);
	}
	else
	{
		PID_speed_control(get_lift_right_value().velocity, &lift_r_vel_value, &lift_r_vel_pid, &lift_r_vel_gain);
	}

	lift_r_vel_value.output = (int)(lift_r_vel_value.manipulate * MOTOR_MAX_OUTPUT1);

	if(lift_r_vel_value.output < 0)
	{
		if(LIMIT_SW1_ON)
		{
			Motor_1(0);
			set_lift_r(0.01);
		}
		else
		{
			Motor_1(lift_r_vel_value.output);
		}
	}
	else
	{
		Motor_1(lift_r_vel_value.output);
	}
}

void lift_left_control(){
	lift_l_pos_value.target = target_lift_left;

	SetGain_lift_left(&lift_l_pos_gain, &lift_l_vel_gain, lift_l_pos_value.target, get_lift_left_value().position);

	// 位置型pid
	if (IS_EQUAL_FROAT_POSITION_LIFT(target_lift_left, get_lift_left_value().position)) {
		//無効時処理
		reset_pid_value(&lift_l_pos_value, &lift_l_pos_pid);
	}
	else
	{
		PID_position_control(get_lift_left_value().position, &lift_l_pos_value, &lift_l_pos_pid, &lift_l_pos_gain);
	}

	lift_l_vel_value.target = lift_l_pos_value.manipulate * lift_max_velocity;

	// 速度型pid
	if (IS_EQUAL_FROAT_VELOCITY(lift_l_vel_value.target, get_lift_left_value().velocity)) {
		//無効時処理
		reset_pid_value(&lift_l_vel_value, &lift_l_vel_pid);
	}
	else
	{
		PID_speed_control(get_lift_left_value().velocity, &lift_l_vel_value, &lift_l_vel_pid, &lift_l_vel_gain);
	}

	lift_l_vel_value.output = (int)(lift_l_vel_value.manipulate * MOTOR_MAX_OUTPUT3);

//	print("lift_l_output: %d\n\r", lift_l_vel_value.output);

	if(lift_l_vel_value.output < 0)
	{
		if(LIMIT_SW3_ON)
		{
			Motor_3(0);
			set_lift_l(0);
		}
		else
		{
			Motor_3(lift_l_vel_value.output);
		}
	}
	else
	{
		Motor_3(lift_l_vel_value.output);
	}
}

void SetPositionGain_arm(pid_gain *gain, float target, float observation_value)
{
	float diff;
	diff = ABS(target - observation_value);

	if(diff < 0.02)
	{
		gain->kp = 20.0;	// 20
	}
	else if(diff < 0.05)
	{
		gain->kp = 15.0;	// 15
	}
	else
	{
		gain->kp = 6.0;
	}
}

void SetGain_lift_right(pid_gain *pos_gain, pid_gain *vel_gain, float target, float observation_value)
{
	float diff;
	diff = target - observation_value;

	if(diff > 0)
	{
		if(diff < 0.4)
		{
			pos_gain->kp = 3.0f;
		}
		else if(diff < 0.6)
		{
			pos_gain->kp = 2.8f;
		}
		else
		{
			pos_gain->kp = 2.6f;
		}
		pos_gain->ki = 0.005f;

		vel_gain->kp = 1.2f;
		vel_gain->ki = 0.002f;
	}
	else if(diff < 0)
	{
		if(diff < 0.4)
		{
			pos_gain->kp = 2.6f;
		}
		else if(diff < 0.6)
		{
			pos_gain->kp = 2.4f;
		}
		else
		{
			pos_gain->kp = 2.2f;
		}
		pos_gain->ki = 0.01f;

		vel_gain->kp = 1.5f;
		vel_gain->ki = 0.01f;
	}
}

void SetGain_lift_left(pid_gain *pos_gain, pid_gain *vel_gain, float target, float observation_value)
{
	float diff;
	diff = target - observation_value;

	if(diff > 0)
	{
		if(diff < 0.4)
		{
			pos_gain->kp = 2.9f;
		}
		else if(diff < 0.6)
		{
			pos_gain->kp = 2.7f;
		}
		else
		{
			pos_gain->kp = 2.5f;
		}
		pos_gain->ki = 0.005f;

		vel_gain->kp = 1.2f;
		vel_gain->ki = 0.002f;
	}
	else if(diff < 0)
	{
		if(diff < 0.4)
		{
			pos_gain->kp = 2.6f;
		}
		else if(diff < 0.6)
		{
			pos_gain->kp = 2.4f;
		}
		else
		{
			pos_gain->kp = 2.2f;
		}
		pos_gain->ki = 0.01f;

		vel_gain->kp = 1.5f;
		vel_gain->ki = 0.01f;
	}
}

void set_target_arm_right(float value)
{
	target_arm_right = value;
}

void set_target_arm_left(float value)
{
	target_arm_left = value;
}

void set_target_lift_right(float value)
{
	target_lift_right = value;
}

void set_target_lift_left(float value)
{
	target_lift_left = value;
}

float get_target_arm_right(void)
{
	return target_arm_right;
}

float get_target_arm_left(void)
{
	return target_arm_left;
}

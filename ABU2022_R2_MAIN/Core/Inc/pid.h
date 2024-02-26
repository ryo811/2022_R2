#ifndef PID_H_
#define PID_H_


#include "main.h"
#define ABS(x) ((x)>0?(x):-(x))

typedef struct{
	float prev_prev_bias;
	float prev_bias;
	float bias;
	float prev_op_value;
	float op_value;
	float prev_delta_d;
	float sigma;
}pid_value;

typedef struct{
	float kp;
	float ki;
	float kd;
	float d_time;
}pid_gain;

typedef struct{
	float target;
	float manipulate;
	int output;
}control_value;

void PID_speed_control(float observation_value, control_value *control, pid_value *pid, pid_gain *gain);
void PID_position_control(float observation_value, control_value *control, pid_value *pid, pid_gain *gain);
void PID_position_control_ver2(float observation_value, control_value *control, pid_value *pid, pid_gain *gain);

#endif

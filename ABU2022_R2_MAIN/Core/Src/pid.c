#include "pid.h"
#include "usart.h"


void PID_speed_control(float observation_value, control_value *control, pid_value *pid, pid_gain *gain){
	float p, i, d;

	pid->bias = control->target - observation_value;

	p = gain->kp * (pid->bias - pid->prev_bias);
	i = gain->ki * pid->bias;
	d = (gain->kd * pid->prev_delta_d) + ((1.0 - gain->kd) * (pid->bias - (2.0 * pid->prev_bias) + pid->prev_prev_bias));

	pid->prev_prev_bias = pid->prev_bias;
	pid->prev_bias = pid->bias;

	pid->op_value = pid->prev_op_value + (p + i + d);
	pid->prev_op_value = pid->op_value;
	pid->prev_delta_d = d;

	if(ABS(pid->op_value) > 1.0){
		pid->op_value = pid->op_value > 0 ? 1.0 : -1.0;
	}
	control->manipulate = pid->op_value;

//	print("mani %f\n\r", control->manipulate);
}

void PID_position_control(float observation_value, control_value *control, pid_value *pid, pid_gain *gain){
	float p, i, d;

	pid->bias = control->target - observation_value;

	/* �ｿｽﾎ搾ｿｽ�ｿｽﾌ托ｿｽ�ｿｽa�ｿｽ�ｿｽ�ｿｽZ�ｿｽo*/
	pid->sigma += pid->bias;

	/* PID �ｿｽv�ｿｽZ*/
	p = gain->kp * pid->bias;
	i = gain->ki * pid->sigma;
	d = gain->kd * pid->prev_delta_d + (1.0 -gain->kd) * (pid->bias - pid->prev_bias);

	/* �ｿｽﾎ搾ｿｽ�ｿｽﾌ更�ｿｽV*/
	pid->prev_bias = pid->bias;

	/* �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ更�ｿｽV*/
	pid->prev_delta_d = d;

	pid->op_value = p + i + d;
	if(ABS(pid->op_value) > 1.0){
		pid->op_value = pid->op_value > 0 ? 1.0 : -1.0;
	}

//	print("op %f\n\r", pid->op_value);

	control->manipulate = pid->op_value;
//	print("%d:%d:%d\r\n",(int)(control->target * 100 - 550),(int)(observation_value * 100 - 550),(int)(control->manipulate * 100));
}

void PID_position_control_ver2(float observation_value, control_value *control, pid_value *pid, pid_gain *gain){
	float p, i, d;

	pid->bias = control->target -observation_value;
	pid->sigma += (pid->prev_bias + pid->bias) / 2.0 * gain->d_time;
	/* PID 計算*/
	p = gain->kp * pid->bias;
	i = gain->ki * pid->sigma;
	d = (gain->d_time * pid->prev_delta_d) + gain->kd * (pid->bias - pid->prev_bias) / gain->d_time;
	/* 偏差の更新*/
	pid->prev_bias = pid->bias;
	/* 微分項の更新*/
	pid->prev_delta_d = d;

	pid->op_value = p + i + d;
	if(ABS(pid->op_value) > 1.0){
		pid->op_value = pid->op_value > 0 ? 1.0 : -1.0;
	}

	control->manipulate = pid->op_value;
//	print("%d:%d:%d:%d\r\n",(int)(control->target * 100),(int)(observation_value * 100),(int)(control->manipulate * 100),(int)(pid->bias * 100));
}

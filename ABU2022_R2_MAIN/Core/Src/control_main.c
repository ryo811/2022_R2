#include "control_main.h"

static control_value partition_value;
static pid_value partition_pid;
static pid_gain partition_gain;

static control_value partition_value_pile;
static pid_value partition_pid_pile;
static pid_gain partition_gain_pile;

static float target_partition;
static uint8_t disc_counter;

static uint8_t loss_count;

static uint8_t reset_count;
static uint8_t check_count;

static uint8_t disc;

void init_partition(void){
	// 通常
	partition_gain.kp = 0.16f;
	partition_gain.ki = 0.003f;
	partition_gain.kd = 0.98f;

	partition_value.target = 0.0;
	partition_value.manipulate = 0.0;
	partition_value.output = 0;
	partition_pid.prev_prev_bias = 0.0;
	partition_pid.prev_bias = 0.0;
	partition_pid.bias = 0.0;
	partition_pid.prev_op_value = 0.0;
	partition_pid.op_value = 0.0;
	partition_pid.prev_delta_d = 0.0;
	partition_pid.sigma = 0.0;

	// 仕切りから出すとき
	partition_gain_pile.kp = 0.85f;
	partition_gain_pile.ki = 0.05f;
	partition_gain_pile.kd = 0.05f;
	partition_gain_pile.d_time = 0.025f;

	partition_value_pile.target = 0.0;
	partition_value_pile.manipulate = 0.0;
	partition_value_pile.output = 0;
	partition_pid_pile.prev_prev_bias = 0.0;
	partition_pid_pile.prev_bias = 0.0;
	partition_pid_pile.bias = 0.0;
	partition_pid_pile.prev_op_value = 0.0;
	partition_pid_pile.op_value = 0.0;
	partition_pid_pile.prev_delta_d = 0.0;
	partition_pid_pile.sigma = 0.0;
}

uint8_t partition_ready(float rad)
{
	uint8_t return_value = 0;

	if(get_partition_value() < (rad - RAD(5.0)) || get_partition_value() > (rad + RAD(5.0)))
	{
		target_partition = rad;
	}
	else
	{
		return_value = 1;
	}

	return return_value;
}

void partition_control(){
	partition_value.target = target_partition;

//	SetPositionGain_partition(&partition_gain, partition_value.target, get_partition_value());

	if (IS_EQUAL_FROAT_RAD(target_partition, get_partition_value())) {
		//辟｡蜉ｹ譎ょ�ｦ逅�
		reset_pid_value(&partition_value, &partition_pid);
	}
	else
	{
		PID_position_control(get_partition_value(), &partition_value, &partition_pid, &partition_gain);
	}

	if(partition_value.target == 0.0)
	{
		partition_value.output = (int)(partition_value.manipulate * MOTOR_MAX_OUTPUT5_LOW);
	}
	else
	{
		partition_value.output = (int)(partition_value.manipulate * MOTOR_MAX_OUTPUT5_HIGH);
	}

	Motor_5(partition_value.output);
}
void partition_control_pile(){
	partition_value_pile.target = target_partition;

	PID_position_control_ver2(get_partition_value(), &partition_value_pile, &partition_pid_pile, &partition_gain_pile);

	if(partition_value_pile.target == 0.0)
	{
		partition_value_pile.output = (int)(partition_value_pile.manipulate * MOTOR_MAX_OUTPUT5_LOW);
	}
	else
	{
		partition_value_pile.output = (int)(partition_value_pile.manipulate * MOTOR_MAX_OUTPUT5_LOW);
	}

//	print("%d:%d\r\n",partition_value_pile.output,(int)(partition_value_pile.manipulate * 100));
	Motor_5(partition_value_pile.output);
}

void SetPositionGain_partition(pid_gain *gain, float target, float observation_value)
{
	float diff;
	diff = ABS(target - observation_value);

	if(diff < RAD(25))
	{
		gain->kp = 0.2;
	}
	else if(diff < RAD(50))
	{
		gain->kp = 0.15;
	}
	else
	{
		gain->kp = 0.1;
	}
}

void set_target_partition(float value)
{
	target_partition = value;
}

void reset_value(void)
{
	reset_raspi1();
	reset_raspi1_value();
	reset_disc_count();
	reset_loss_count();
}

void lift_up_1(void)
{
	if(!get_raspi1().state_2)
	{
		loss_count++;
	}

	if(!get_raspi1().state_3)
	{
		loss_count++;
	}

	if(!get_raspi1().state_4)
	{
		loss_count++;
	}

	if(!get_raspi1().state_5)
	{
		loss_count++;
	}

	switch(loss_count)
	{
	case 0:
		while(!lift_ready(HIGHT1))
		{
			LED0_TOGGLE;
		}
		partition_mode = part_off;
		break;

	case 1:
		while(!lift_ready(HIGHT2))
		{
			LED0_TOGGLE;
		}
		partition_mode = part_off;
		break;

	case 2:
		if(camera_state == camera_on1)
		{
			while(!lift_ready(HIGHT3_CAMERA))
			{
				LED0_TOGGLE;
			}
			partition_mode = part_off;
			partition_air = air_up_on;
		}
		else
		{
			while(!lift_ready(HIGHT3))
			{
				LED0_TOGGLE;
			}
		}
		break;

	case 3:
		if(camera_state == camera_on1)
		{
			while(!lift_ready(HIGHT4_CAMERA))
			{
				LED0_TOGGLE;
			}
			partition_mode = part_off;
			partition_air = air_down_on;
		}
		else
		{
			while(!lift_ready(HIGHT4))
			{
				LED0_TOGGLE;
			}
		}
		break;

	case 4:
		while(!lift_ready(HIGHT5))
		{
			LED0_TOGGLE;
		}
		partition_mode = part_off;
		break;
	}
}

void lift_up_2(void)
{
	if(!get_raspi1().state_3)
	{
		loss_count++;
	}

	if(!get_raspi1().state_4)
	{
		loss_count++;
	}

	if(!get_raspi1().state_5)
	{
		loss_count++;
	}

	switch(loss_count)
	{
	case 0:
		if(camera_state == camera_on1)
		{
			while(!lift_ready(HIGHT2_CAMERA))
			{
				LED0_TOGGLE;
			}
			partition_mode = part_on;
		}
		else
		{
			while(!lift_ready(HIGHT2))
			{
				LED0_TOGGLE;
			}
			partition_mode = part_off;
		}
		break;

	case 1:
		if(camera_state == camera_on1)
		{
			while(!lift_ready(HIGHT3_CAMERA))
			{
				LED0_TOGGLE;
			}
			partition_air = air_up_on;
			partition_mode = part_on;
		}
		else
		{
			while(!lift_ready(HIGHT3))
			{
				LED0_TOGGLE;
			}
		}
		break;

	case 2:
		if(camera_state == camera_on1)
		{
			while(!lift_ready(HIGHT4_CAMERA))
			{
				LED0_TOGGLE;
			}
			partition_air = air_down_on;
			partition_mode = part_on;
		}
		else
		{
			while(!lift_ready(HIGHT4))
			{
				LED0_TOGGLE;
			}
		}
		break;

	case 3:
		while(!lift_ready(HIGHT5))
		{
			LED0_TOGGLE;
		}
		partition_mode = part_off;
		break;
	}
}

void lift_up_3(void)
{
	if(!get_raspi1().state_4)
	{
		loss_count++;
	}

	if(!get_raspi1().state_5)
	{
		loss_count++;
	}

	switch(loss_count)
	{
	case 0:
		if(camera_state == camera_on1)
		{
			while(!lift_ready(HIGHT3_CAMERA))
			{
				LED0_TOGGLE;
			}
			partition_air = air_up_on;
			partition_mode = part_on;
		}
		else
		{
			while(!lift_ready(HIGHT3))
			{
				LED0_TOGGLE;
			}
		}
		break;

	case 1:
		if(camera_state == camera_on1)
		{
			while(!lift_ready(HIGHT4_CAMERA))
			{
				LED0_TOGGLE;
			}
			partition_air = air_down_on;
			partition_mode = part_on;
		}
		else if(camera_state == camera_off)
		{
			while(!lift_ready(HIGHT4))
			{
				LED0_TOGGLE;
			}
		}
		break;

	case 2:
		while(!lift_ready(HIGHT5))
		{
			LED0_TOGGLE;
		}
		partition_mode = part_off;
		break;
	}
}

void reset_loss_count(void)
{
	loss_count = 0;
}

void arm_mode_change(void)
{
	if(arm_mode == mode_on)
	{
		Motor_0(30);
		Motor_2(30);

		while(1)
		{
			if(GetController().bits.Batu == 0)
			{
				print("arm_on\n\r");
				arm_mode = mode_off;
				break;
			}
		}
	}
	else if(arm_mode == mode_off)
	{
		if(LIMIT_SW0_ON)
		{
			Motor_0(0);
		}
		else
		{
			Motor_0(-30);
		}

		if(LIMIT_SW2_ON)
		{
			Motor_2(0);
		}
		else
		{
			Motor_2(-30);
		}

		while(1)
		{
			if(GetController().bits.Batu == 0)
			{
				print("arm_off\n\r");
				arm_mode = mode_on;
				break;
			}
		}
	}
}

void pile_mode_change(void)
{
	if(pile_mode == mode1)
	{
		LED0_ON;
		while(1)
		{
			if(GetController().bits.Shikaku == 0)
			{
				print("pile_mode2\n\r");
				pile_mode = mode2;
				break;
			}
		}
	}
	else if(pile_mode == mode2)
	{
		LED0_OFF;
		while(1)
		{
			if(GetController().bits.Shikaku == 0)
			{
				print("pile_mode1\n\r");
				pile_mode = mode1;
				break;
			}
		}
	}
}

void air_mode_change(void)
{
	if(GetController().bits.Up)
	{
		air_mode_change1();
	}
	else if(GetController().bits.Down)
	{
		air_mode_change2();
	}
}

void air_mode_change1(void)
{
	if(air_mode1 == air_on)
	{
		AIR2_0_ON;
		AIR2_1_ON;

		while(1)
		{
			if(!GetController().bits.Up)
			{
				air_mode1 = air_off;
				break;
			}
		}
	}
	else if(air_mode1 == air_off)
	{
		AIR2_0_OFF;
		AIR2_1_OFF;

		while(1)
		{
			if(!GetController().bits.Up)
			{
				air_mode1 = air_on;
				break;
			}
		}
	}
}

void air_mode_change2(void)
{
	if(air_mode2 == air2_on)
	{
		AIR2_2_ON;

		while(1)
		{
			if(!GetController().bits.Down)
			{
				air_mode2 = air2_off;
				break;
			}
		}
	}
	else if(air_mode2 == air2_off)
	{
		AIR2_2_OFF;

		while(1)
		{
			if(!GetController().bits.Down)
			{
				air_mode2 = air2_on;
				break;
			}
		}
	}
}

void camera_state_change(void)
{
	AIR3_0_OFF;
	AIR3_1_OFF;
	AIR3_2_OFF;
	AIR3_3_OFF;

	if(camera_state == camera_on1)
	{
		AIR3_0_ON;
	}
	else if(camera_state == camera_on2)
	{
		AIR3_1_ON;
	}
	else if(camera_state == camera_off)
	{
		AIR3_2_ON;
	}

	if(camera_state == camera_on1)
	{
		setdata(0);
		setdata_part(1);

		while(1)
		{
			if(!GetController().bits.Start)
			{
				print("camera_on2\n\r");
				camera_state = camera_on2;
				AIR3_0_OFF;
				break;
			}
		}
	}
	else if(camera_state == camera_on2)
	{
		setdata(1);
		setdata_part(0);

		while(1)
		{
			if(!GetController().bits.Start)
			{
				print("camera_on1\n\r");
				camera_state = camera_on1;
				AIR3_1_OFF;
				break;
			}
		}
	}
	else if(camera_state == camera_off)
	{
		setdata(1);
		setdata_part(0);

		while(1)
		{
			if(!GetController().bits.Start)
			{
				print("camera_on1\n\r");
				camera_state = camera_on1;
				AIR3_2_OFF;
				break;
			}
		}
	}
}

void disc_count(void)
{
	while(1)
	{
		if(GetController().bits.Shikaku == 0)
		{
			disc_counter++;
			if(disc_counter > 5)
			{
				disc_counter = 1;
			}
			print("disc: %d\n\r", disc_counter);
			break;
		}
	}
}

void reset_disc_count(void)
{
	disc_counter = 0;
}

uint8_t get_disc_count(void)
{
	return disc_counter;
}

void reset_counter(void){
	uint32_t tim_counter;
	uint8_t diff;
	static uint32_t prev_tim ;

	if(!check_count)
	{
		prev_tim = HAL_GetTick();
	}
	else
	{
		tim_counter = HAL_GetTick();
		diff = tim_counter - prev_tim;

		if(diff < 26)
		{
			reset_count++;
		}
		else
		{
			reset_count = 0;
		}

		prev_tim = tim_counter;
	}

	check_count++;
}

uint8_t get_reset_count(void)
{
	return reset_count;
}

void counter_reset(void)
{
	reset_count = 0;
	check_count = 0;
}

void slicer(void)
{
	if(GetController().bits.Right)
	{
		Motor_7(50);
	}
	else if(GetController().bits.Left)
	{
		Motor_7(-50);
	}
	else
	{
		Motor_7(0);
	}
}

void disc_led(void)
{
	if(camera_state == camera_on1)
	{
		disc = get_raspi1().disc_camera1;
	}
	else if(camera_state == camera_on2)
	{
		if((get_raspi1().disc_camera1 >= 1) && (get_raspi1().disc_camera1  <= 5))
		{
			disc = get_raspi1().disc_camera1;
		}
		else if((get_disc_count() >= 1) && (get_disc_count()  <= 5))
		{
			disc = get_disc_count();
		}
	}

	switch(disc)
	{
	case 1:
		AIR3_0_OFF;
		AIR3_1_OFF;
		AIR3_2_ON;
		break;

	case 2:
		AIR3_0_OFF;
		AIR3_1_ON;
		AIR3_2_ON;
		break;

	case 3:
		AIR3_0_OFF;
		AIR3_1_ON;
		AIR3_2_OFF;
		break;

	case 4:
		AIR3_0_ON;
		AIR3_1_ON;
		AIR3_2_OFF;
		break;

	case 5:
		AIR3_0_ON;
		AIR3_1_OFF;
		AIR3_2_OFF;
		break;
	}

	if(camera_state == camera_on1)
	{
		AIR3_3_OFF;
	}
	else
	{
		AIR3_3_ON;
	}
}

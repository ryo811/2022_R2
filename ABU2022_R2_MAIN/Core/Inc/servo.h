#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "tim.h"

#define SERVO_0(pulse)			servo_control(0, pulse)
#define SERVO_1(pulse)			servo_control(1, pulse)

void init_servo();
void stop_servo_pwm();
void servo_control(int servo_number, int percentage);

#endif /* INC_SERVO_H_ */

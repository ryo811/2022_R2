/*
 * controller_can.h
 *
 *  Created on: 2018/09/26
 *      Author: greee
 */

#ifndef CONTROLLER_CAN_H_
#define CONTROLLER_CAN_H_

#include "can.h"
#include "can_com.h"
#include "usart.h"
#include "string.h" //For memcpy

#define CONTROLLER_START            (0x01)
#define CONTROLLER_STOP             (0x02)

uint8_t controller_stats;

union ps3 {
	unsigned char Controller_data[6];

	struct {
		unsigned char Sankaku :1;
		unsigned char Maru :1;
		unsigned char Batu :1;
		unsigned char Shikaku :1;
		unsigned char L_2 :1;
		unsigned char R_2 :1;
		unsigned char L_1 :1;
		unsigned char R_1 :1;

		unsigned char Select :1;
		unsigned char Start :1;
		unsigned char unuse :2;
		unsigned char Up :1;
		unsigned char Right :1;
		unsigned char Down :1;
		unsigned char Left :1;

		signed char left_analog_xaxis :8;
		signed char left_analog_yaxis :8;
		signed char right_analog_xaxis :8;
		signed char right_analog_yaxis :8;
	} bits;
};

void StartControllerSequential(uint8_t intervalTime);
void StopControllerSequential(void);
void UpdateController();
union ps3 GetController();
uint8_t GetControllerUpdateFlag();
void PrintControllerData();

#endif /* CONTROLLER_CAN_H_ */

#ifndef CAN_COM_H_
#define CAN_COM_H_

#include "main.h"
#include "can.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"
#include "stdint.h"

#define ID_MAIN			0x00

//can1
#define ID_RASPI		0x01

//can2
#define ID_CONTROLLER 	0x02
#define ID_BOH			0x06
#define ID_F7			0x07

typedef struct {
	uint8_t state;				// ディスクの状態（0:平、1:立）
	uint8_t disc_camera1;		// カメラ1でのディスク判定
	uint8_t disc_camera2;		// カメラ2でのディスク判定
	uint8_t state_2;			// ディスク2の状態（0:フィールド外、1:フィールド内）
	uint8_t state_3;			// ディスク3の状態（0:フィールド外、1:フィールド内）
	uint8_t state_4;			// ディスク4の状態（0:フィールド外、1:フィールド内）
	uint8_t state_5;			// ディスク5の状態（0:フィールド外、1:フィールド内）
	uint8_t partition_state;	// 仕切りの状態（0:使用、1:不使用）
} raspi_t;

typedef union {
	uint8_t array[8];
	raspi_t value;
} raspi1_can_t;

typedef struct {
	uint8_t camera_data;
	uint8_t part_data;
} raspi1_txdata;

typedef union {
	uint8_t array[8];
	raspi1_txdata value;
} raspi1_can_tx;

typedef union {
	uint8_t array[8];
	uint8_t value;
} raspi2_can_t;

typedef struct {
	uint8_t motor_number;
	int8_t percent;
} boh_t;

typedef union {
	uint8_t array[8];
	boh_t value;
} boh_tx_can_t;

typedef union {
	uint8_t array[8];
	uint8_t value;
} boh_rx_can_t;

void InitCan(void);
void UpdateCan_raspi1(void);
void UpdateCan_raspi2(void);
void UpdateCan_boh(void);
//void SetData(uint8_t st, int8_t motor);
void setdata(uint8_t tsdata);
void setdata_part(uint8_t data);
void SendData(void);
void update_raspi1(void);
void init_raspi1_value(void);
void reset_raspi1_value(void);
void reset_raspi1(void);

uint8_t can_check();
uint8_t get_raspi_stats();
raspi_t get_raspi1();
uint8_t get_raspi2();
uint8_t get_boh();

#endif /* CAN_COM_H_ */

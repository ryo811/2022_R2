/*
 * controller_can.c
 *
 *  Created on: 2018/09/26
 *      Author: greee
 */

#include "controller.h"

static union ps3 _ps3;
static uint8_t _updateFlag;

/**
 * @brief �R���g���[����Ƃ̒ʐM���J�n����
 * @param intervalTime ���M����
 */
void StartControllerSequential(uint8_t intervalTime) {
	CAN_TxHeaderTypeDef txHeader;
	uint32_t mailBoxNum;
	uint8_t data[3];

	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 2;
	txHeader.StdId = ID_CONTROLLER;
	data[0] = CONTROLLER_START;
	data[1] = intervalTime;
	if(HAL_CAN_AddTxMessage(&hcan3,&txHeader,data,&mailBoxNum) == HAL_OK){
		LED6_OFF;
	}
}

/**
 * �R���g���[����Ƃ̒ʐM���I������
 */
void StopControllerSequential(void) {
	CAN_TxHeaderTypeDef txHeader;
	uint32_t mailBoxNum;
	uint8_t data[2];

	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 1;
	txHeader.StdId = ID_CONTROLLER;
	data[0] = CONTROLLER_STOP;
	HAL_CAN_AddTxMessage(&hcan3,&txHeader,data,&mailBoxNum);
}

void UpdateController(){
	uint8_t rxData[8];
	CAN_RxHeaderTypeDef rxHeader;
	if(HAL_CAN_GetRxMessage(&hcan3, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK){
		LED6_TOGGLE;
		memcpy(_ps3.Controller_data, rxData, sizeof(_ps3.Controller_data));
//		controller_stats = 1;
	}
	_updateFlag = 1;
}

/**
 * @brief �擾�����R���g���[���f�[�^�ɃA�N�Z�X����Q�b�^�[
 * @return �R���g���[���f�[�^
 */
union ps3 GetController() {
	return _ps3;
}

/**
 * @brief �R���g���[���̍X�V���������^�C�~���O��ʒm
 * @return
 */
uint8_t GetControllerUpdateFlag() {
	if (!_updateFlag) {
		return 0;
	}

	return _updateFlag = 0, 1;
}

///**
// * @brief �R���g���[���f�[�^�̏o��
// * @brief �f�o�b�O�p
// */
//void PrintControllerData() {
//	int i;
//	for (i = 0; i < 2; i++) {
//		PrintBinary(_ps3.Controller_data[i]);
//	}
//	for(; i < 6; i++){
//		print("%d ", _ps3.Controller_data[i]);
//	}
//	print("\n\r");
//}

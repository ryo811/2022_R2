#include "can_com.h"

static void SetCanFilter_MAIN();
static void SetCanFilter_BOH();
static void SetCanFilter_RASPI();

static raspi1_can_t ras1;
static raspi2_can_t ras2;
static boh_rx_can_t rx_boh;
static uint8_t raspi_stats;
static uint8_t prev_disc;
//static uint8_t can_count;
static raspi_t raspi1_value;

static raspi1_txdata ras_txdata;

static void SetCanFilter_MAIN(){
	CAN_FilterTypeDef filterConfig;

	  filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	  filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	  filterConfig.FilterIdHigh = (ID_MAIN << 5);
	  filterConfig.FilterIdLow = 0x0000;
	  filterConfig.FilterMaskIdHigh = 0x00e0;
	  filterConfig.FilterMaskIdLow = 0x0000;
	  filterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	  filterConfig.FilterActivation = ENABLE;
	  filterConfig.SlaveStartFilterBank = 14;

	  filterConfig.FilterBank = 0;
	  HAL_CAN_ConfigFilter(&hcan1, &filterConfig);

//	  filterConfig.FilterBank = 2;
//	  HAL_CAN_ConfigFilter(&hcan2, &filterConfig);

	  filterConfig.FilterBank = 3;
	  HAL_CAN_ConfigFilter(&hcan3, &filterConfig);
}

static void SetCanFilter_RASPI(){
	CAN_FilterTypeDef filterConfig;

	  filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	  filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	  filterConfig.FilterIdHigh = (ID_RASPI << 5);
	  filterConfig.FilterIdLow = 0x0000;
	  filterConfig.FilterMaskIdHigh = 0x00e0;
	  filterConfig.FilterMaskIdLow = 0x0000;
	  filterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
	  filterConfig.FilterActivation = ENABLE;
	  filterConfig.SlaveStartFilterBank = 14;

	  filterConfig.FilterBank = 1;
	  HAL_CAN_ConfigFilter(&hcan1, &filterConfig);
}

static void SetCanFilter_BOH(){
	CAN_FilterTypeDef filterConfig;

	  filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	  filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	  filterConfig.FilterIdHigh = (ID_F7 << 5);
	  filterConfig.FilterIdLow = 0x0000;
	  filterConfig.FilterMaskIdHigh = 0x00e0;
	  filterConfig.FilterMaskIdLow = 0x0000;
	  filterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
	  filterConfig.FilterActivation = ENABLE;
	  filterConfig.SlaveStartFilterBank = 14;

	  filterConfig.FilterBank = 4;
	  HAL_CAN_ConfigFilter(&hcan3, &filterConfig);
}

void InitCan(void){
	SetCanFilter_MAIN();
	SetCanFilter_RASPI();
	SetCanFilter_BOH();
	HAL_CAN_Start(&hcan1);
//	HAL_CAN_Start(&hcan2);
	HAL_CAN_Start(&hcan3);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);
//	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_ActivateNotification(&hcan3, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_ActivateNotification(&hcan3, CAN_IT_RX_FIFO1_MSG_PENDING);

	prev_disc = 0;
}

void UpdateCan_raspi1(void){
	uint8_t rxData[8];
	CAN_RxHeaderTypeDef rxHeader;
	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK){
		LED7_TOGGLE;
		memcpy(ras1.array, rxData, sizeof(ras1.array));
//		print("state: %d disc_camera1: %d disc_camera2: %d 2: %d 3: %d 4: %d 5: %d part: %d\n\r", ras1.value.state, ras1.value.disc_camera1, ras1.value.disc_camera2, ras1.value.state_2, ras1.value.state_3, ras1.value.state_4, ras1.value.state_5, ras1.value.partition_state);

		if(ras1.value.state == 6)
		{
			raspi1_value.state_2 = ras1.value.state_2;
			raspi1_value.state_3 = ras1.value.state_3;
			raspi1_value.state_4 = ras1.value.state_4;
			raspi1_value.state_5 = ras1.value.state_5;
			raspi1_value.partition_state = ras1.value.partition_state;
		}
		else
		{
			raspi1_value.state = ras1.value.state;
			raspi1_value.disc_camera1 = ras1.value.disc_camera1;
			raspi1_value.disc_camera2 = ras1.value.disc_camera2;
			raspi1_value.state_2 = ras1.value.state_2;
			raspi1_value.state_3 = ras1.value.state_3;
			raspi1_value.state_4 = ras1.value.state_4;
			raspi1_value.state_5 = ras1.value.state_5;
			raspi1_value.partition_state = ras1.value.partition_state;
		}

		if(raspi1_value.partition_state)
		{
			setdata(0);
			setdata_part(1);
			camera_state = camera_on2;
		}
		else if(!raspi1_value.partition_state)
		{
			setdata(1);
			setdata_part(0);
			camera_state = camera_on1;
		}

		print("state: %d disc_camera1: %d disc_camera2: %d 2: %d 3: %d 4: %d 5: %d part: %d\n\r", raspi1_value.state, raspi1_value.disc_camera1, raspi1_value.disc_camera2, raspi1_value.state_2, raspi1_value.state_3, raspi1_value.state_4, raspi1_value.state_5, raspi1_value.partition_state);
	}
	else
	{
		raspi_stats = 0;
	}
}

void UpdateCan_raspi2(void){
	uint8_t rxData[8];
	CAN_RxHeaderTypeDef rxHeader;
	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO1, &rxHeader, rxData) == HAL_OK){
		LED3_TOGGLE;
		memcpy(ras2.array, rxData, sizeof(ras2.array));
		print("state: %d\n\r", ras2.value);
	}
}

void setdata(uint8_t data)
{
	ras_txdata.camera_data = data;
}

void setdata_part(uint8_t data)
{
	ras_txdata.part_data = data;
}

void SendData(void){
	CAN_TxHeaderTypeDef txHeader;
	uint32_t mailBoxNum;
	raspi1_can_tx sendData;
	sendData.value = ras_txdata;

	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 8;
	txHeader.StdId = 0x00;

	if(HAL_CAN_AddTxMessage(&hcan1, &txHeader, sendData.array, &mailBoxNum) == HAL_OK){
		LED5_TOGGLE;
	}
}

void update_raspi1(void)
{
	raspi1_value.state = ras1.value.state;
	raspi1_value.disc_camera1 = ras1.value.disc_camera1;
	raspi1_value.disc_camera2 = ras1.value.disc_camera2;
}

void init_raspi1_value(void)
{
	raspi1_value.state = 0;
	raspi1_value.disc_camera1 = 0;
	raspi1_value.disc_camera2 = 0;
	raspi1_value.state_2 = 1;
	raspi1_value.state_3 = 1;
	raspi1_value.state_4 = 1;
	raspi1_value.state_5 = 1;
	raspi1_value.partition_state = 0;
}

void reset_raspi1_value(void)
{
	raspi1_value.state = 0;
	raspi1_value.disc_camera1 = 0;
	raspi1_value.disc_camera2 = 0;
}

void reset_raspi1(void)
{
	ras1.value.state = 0;
	ras1.value.disc_camera1 = 0;
	ras1.value.disc_camera2 = 0;
}

//uint8_t can_check()
//{
//	if(can_count == 5)
//	{
//		can_count = 0;
//	}
//
//	if(ras1.value.disc_camera1 == prev_disc)
//	{
//		can_count++;
//	}
//
//	prev_disc = ras1.value.disc_camera1;
//
//	HAL_Delay(500);
//
//	return can_count;
//}

uint8_t get_raspi_stats()
{
	return raspi_stats;
}

raspi_t get_raspi1()
{
	return raspi1_value;
}

uint8_t get_raspi2()
{
	return ras2.value;
}

uint8_t get_sub()
{
	return rx_boh.value;
}

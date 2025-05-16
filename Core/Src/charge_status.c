#include <stdint.h>
#include "main.h"
#include "idleTask.h"
#include <stdio.h>
#include "GopherCAN.h"


void initStatus_LEDs(){
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin, GPIO_PIN_RESET); // green 
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, GPIO_PIN_RESET); // yellow
    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin, GPIO_PIN_RESET); // red
    HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin, GPIO_PIN_RESET); // blue
}


uint8_t red_LED(void){
	if (bmsChargerOverVoltageAlert_state.data||
	bmsChargerOverCurrentAlert_state.data||
	bmsChargerVoltageMismatchAlert_state.data||
	bmsChargerCurrentMismatchAlert_state.data||
	bmsChargerHardwareFailureAlert_state.data||
	bmsChargerOverTempAlert_state.data||
	bmsChargerInputVoltageErrorAlert_state.data||
	bmsChargerBatteryNotDetectedErrorAlert_state.data||
	bmsChargerCommunicationErrorAlert_state.data){
		return 1;
	}
	else if (!(bmsChargerOverVoltageAlert_state.data&&
	bmsChargerOverCurrentAlert_state.data&&
	bmsChargerVoltageMismatchAlert_state.data&&
	bmsChargerCurrentMismatchAlert_state.data&&
	bmsChargerHardwareFailureAlert_state.data&&
	bmsChargerOverTempAlert_state.data&&
	bmsChargerInputVoltageErrorAlert_state.data&&
	bmsChargerBatteryNotDetectedErrorAlert_state.data&&
	bmsChargerCommunicationErrorAlert_state.data)){
		return 0
	}
}


uint8_t green_LED(void) {
	int SDC1 = HAL_GPIO_ReadPin(SDC1_GPIO_Port,SDC1_Pin);
    int SDC2 = HAL_GPIO_ReadPin(SDC2_GPIO_Port,SDC2_Pin);
    int SDC3 = HAL_GPIO_ReadPin(SDC3_GPIO_Port,SDC3_Pin);
    int SDC4 = HAL_GPIO_ReadPin(SDC4_GPIO_Port,SDC4_Pin);
	int CP = HAL_GPIO_ReadPin(CP_EN_GPIO_Port, CP_EN_Pin);//use different can message from bms
	if (!SDC1&&!SDC2&&!SDC3&&!SDC4&&CP) {
		return 1;
	} 
	else{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, 0);
	}
	return 0;
}

void check_LEDs(void){
	if (red_LED()) {
		
	}
	else if (green_LED()){
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, 1);
	}
	HAL_GPIO_
}

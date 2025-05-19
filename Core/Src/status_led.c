#include <stdint.h>
#include "main.h"
#include "status_led.h"
#include <stdio.h>
#include "GopherCAN.h"

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
		return 0;
	}
}


uint8_t green_LED(void) {
	int CP = HAL_GPIO_ReadPin(CP_EN_GPIO_Port, CP_EN_Pin);//use different can message from bms
	if (!sdcStatus1.data&&!sdcStatus2.data&&!sdcStatus3.data&&!sdcStatus4.data&&CP){
		return 1;
	} 
	else{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, 0);
	}
	return 0;
}

void check_LEDs(void){
	if (red_LED()) {
		HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
        HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1); // Buzzer and not BLUE LED?
	}
	else if (green_LED()){
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin, 1);
	}
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
}
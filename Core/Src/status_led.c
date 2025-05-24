#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "status_led.h"
#include "GopherCAN.h"
#include "GopherCAN_config.h"

extern TIM_HandleTypeDef htim2;

void initStatus_LEDs(void){
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin, GPIO_PIN_RESET); // green 
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, GPIO_PIN_RESET); // yellow
    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin, GPIO_PIN_RESET); // red
    HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin, GPIO_PIN_RESET); // blue
}

uint8_t red_LED(void){
	if (//bmsChargerOverVoltageAlert_state.data||
	//bmsChargerOverCurrentAlert_state.data||
	//bmsChargerVoltageMismatchAlert_state.data||
	//bmsChargerCurrentMismatchAlert_state.data||
	//bmsChargerHardwareFailureAlert_state.data||
	//bmsChargerOverTempAlert_state.data||
	//bmsChargerInputVoltageErrorAlert_state.data||
	//bmsChargerBatteryNotDetectedErrorAlert_state.data||
	//bmsChargerCommunicationErrorAlert_state.data
    0){
		return 1;
	}
	return 0;
}


uint8_t green_LED(void) {
	if (//!sdcStatus1.data&&
        //!sdcStatus2.data&&
        //!sdcStatus3.data&&
        //!sdcStatus4.data&&
        //chargerStatusByte.data
        1){
		return 1;
	} 
	return 0;
}

volatile uint8_t toggle = 0;
void buzzer(void){
    HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
    toggle = 1;
    __HAL_TIM_SET_COUNTER(&htim2,0); // reset
    HAL_TIM_Base_Start_IT(&htim2); //start interrupt
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
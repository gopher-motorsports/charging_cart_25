#include <stdint.h>
#include "main.h"
#include "idleTask.h"
#include <stdio.h>
#include "GopherCAN.h"

#define SOE_LOWER_LIM  0
#define SOE_UPPER_LIM  0

void initStatus_LEDs(){
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin, GPIO_PIN_RESET); // green 
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, GPIO_PIN_RESET); // yellow
    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin, GPIO_PIN_RESET); // red
    HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin, GPIO_PIN_RESET); // blue
}

void red_LED(int state) {
	if (state < SOE_LOWER_LIM) {
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, 1); 
	} else if (state >= SOE_LOWER_LIM) {
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin, 1);
	}
}



#include <stdint.h>
#include "main.h"
#include "idleTask.h"
#include <stdio.h>
#include "GopherCAN.h"

#define HEARTBEAT_BLINK_MS      300
#define HEARTBEAT_PERIOD_MS     2000

void initIdleTask(){
    HAL_GPIO_WritePin(Heartbeat_GPIO_Port, Heartbeat_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin, GPIO_PIN_RESET); // green led normally low

}
void runIdleTask(){
    static uint8_t hbState = 0;
    static  uint32_t lastHeartBeatUpdate = 0;
    if(hbState){
        if(HAL_GetTick() - lastHeartBeatUpdate > HEARTBEAT_BLINK_MS){
            lastHeartBeatUpdate = HAL_GetTick();
            HAL_GPIO_WritePin(Heartbeat_GPIO_Port, Heartbeat_Pin, GPIO_PIN_RESET);
            hbState = 0;
        }

    } else {
        if(HAL_GetTick() - lastHeartBeatUpdate > (HEARTBEAT_PERIOD_MS - HEARTBEAT_BLINK_MS)){
            lastHeartBeatUpdate = HAL_GetTick();            
            HAL_GPIO_WritePin(Heartbeat_GPIO_Port, Heartbeat_Pin, GPIO_PIN_SET);
            hbState = 1;
        }
    }

    // printf("soe : %lu\n", soeByOCV_percent.data);
    // printf("\e[1;1H\e[2J");
    // printf("hello world\n");
    // printf("soe: %f\n", 3.14f);

    // For debugging sdcStatus
    // printf("\e[1;1H\e[2J");
    // printf("SDC Status:\n");
    // printf("1: %u\n2: %u\n3: %u\n4: %u\n", sdcStatus1.data, sdcStatus2.data, sdcStatus3.data, sdcStatus4.data);   
    // osDelay(500);

    // For debugging J1772
    static uint32_t lastUpdate = 0;
    if((HAL_GetTick() - lastUpdate) > 500){
        printf("\e[1;1H\e[2J");
        printf("Max Ampactiy: %f\n", chargingData.maxAmpacity);
        printf("Charging Power Limit: %f\n", chargingPowerLimit.data);
        // osDelay(500);
        lastUpdate = HAL_GetTick();
    }



    // if(soeByOCV_percent.data == 100){
    //     HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET); // turn on green led
    // }

    // debugging LEDs
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET); // turn on green led
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET); // turn on red led
    HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET);
    
}

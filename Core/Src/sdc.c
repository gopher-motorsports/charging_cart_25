#include <stdint.h>
#include "main.h"
#include "sdc.h"
#include <stdio.h>
#include "GopherCAN.h"

static uint8_t statSDC1 = 0;
static uint8_t statSDC2 = 0;
static uint8_t statSDC3 = 0;
static uint8_t statSDC4 = 0;


void initSdc(){

}
void runSdc(){
    // check status of each SDC pin
    // if the pin is low, SDC status is good -> do nothing
    // if the pin is high, SDC status is bad -> act accordingly
    statSDC1 = HAL_GPIO_ReadPin(SDC1_GPIO_Port,SDC1_Pin);
    statSDC2 = HAL_GPIO_ReadPin(SDC2_GPIO_Port,SDC2_Pin);
    statSDC3 = HAL_GPIO_ReadPin(SDC3_GPIO_Port,SDC3_Pin);
    statSDC4 = HAL_GPIO_ReadPin(SDC4_GPIO_Port,SDC4_Pin);

    update_and_queue_param_u8(&sdcStatus18,statSDC1);
    update_and_queue_param_u8(&sdcStatus19,statSDC2);
    update_and_queue_param_u8(&sdcStatus20,statSDC3);


}

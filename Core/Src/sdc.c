#include <stdint.h>
#include "main.h"
#include "sdc.h"
#include <stdio.h>
#include "GopherCAN.h"

void initSdc(){

}
void runSdc(){
    // check status of each SDC pin
    // if the pin is low, SDC status is good -> do nothing
    // if the pin is high, SDC status is bad -> act accordingly
    uint8_t statSDC1 = HAL_GPIO_ReadPin(SDC1_GPIO_Port,SDC1_Pin);
    uint8_t statSDC2 = HAL_GPIO_ReadPin(SDC2_GPIO_Port,SDC2_Pin);
    uint8_t statSDC3 = HAL_GPIO_ReadPin(SDC3_GPIO_Port,SDC3_Pin);
    uint8_t statSDC4 = HAL_GPIO_ReadPin(SDC4_GPIO_Port,SDC4_Pin);


}

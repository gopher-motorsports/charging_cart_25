/* ==================================================================== */
/* ============================= INCLUDES ============================= */
/* ==================================================================== */
#include "main.h"
#include "j1772.h"

/* ==================================================================== */
/* ============================= DEFINES ============================== */
/* ==================================================================== */

// Timeout of IMD PWM signal in microseconds
#define CP_PWM_TIMOUT_MICROSEC   (100000U)

#define CP_CURRENT_PER_MICROSEC   (0.06f)  // 0.6 A per 10 us → 0.06 A per 1 us

#define CP_MIN_HIGH_TIME_MICROSEC    (100U)
#define CP_MAX_HIGH_TIME_MICROSEC    (850U)

// Standard J1772 voltage for AC level 1 and 2 charging
#define STANDARD_LVL1_VOLT (120U)
#define STANDARD_LVL2_VOLT (208U)

// Standard NEMA maximum current in Amps and voltage in Volts
#define DEFAULT_CURRENT_LIMIT   (15U)
#define DEFAULT_VOLTAGE (110U)


/* ==================================================================== */
/* ======================= EXTERNAL VARIABLES ========================= */
/* ==================================================================== */

// Voltatile variables to be updated from IC timer interrupt
extern volatile uint32_t cpFrequency;
extern volatile uint32_t cpHighTime;
extern volatile uint32_t cpDutyCycle;
extern volatile uint32_t cpLastUpdate;

/* ==================================================================== */
/* =================== GLOBAL FUNCTION DEFINITIONS ==================== */
/* ==================================================================== */

/*!
  @brief    Determine the maximum allowed current
  @param    chargingData Data struct to return J1772 and other charging info
*/

void getJ1772Status(chargingData_S *chargingData)
{

    if((HAL_GetTick() - cpLastUpdate) < CP_PWM_TIMOUT_MICROSEC)
	{
		// HAL GPIO -> ENABLE CP
        HAL_GPIO_WritePin(CP_EN_GPIO_Port, CP_EN_Pin, GPIO_PIN_SET);

        // Calculate current limit
        if (cpHighTime < CP_MIN_HIGH_TIME_MICROSEC)
            cpHighTime = CP_MIN_HIGH_TIME_MICROSEC;
        else if (cpHighTime > CP_MAX_HIGH_TIME_MICROSEC)
            cpHighTime = CP_MAX_HIGH_TIME_MICROSEC;

        chargingData->maxAmpacity = cpHighTime * CP_CURRENT_PER_MICROSEC;

        // Calculate power limit
        if(chargingData->maxAmpacity <= 16)
        {
            // Level 1 charging
            chargingData->powerLimit = STANDARD_LVL1_VOLT * chargingData->maxAmpacity;
        }
        else
        {
            // Level 2 charging
            chargingData->powerLimit = STANDARD_LVL2_VOLT * chargingData->maxAmpacity;
        }
	
    } else {
        // HAL GPIO -> DISABLE CP
        HAL_GPIO_WritePin(CP_EN_GPIO_Port, CP_EN_Pin, GPIO_PIN_RESET);

        // Set power limit to default
        chargingData->maxAmpacity = DEFAULT_CURRENT_LIMIT;
    }



}


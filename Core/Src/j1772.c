/* ==================================================================== */
/* ============================= INCLUDES ============================= */
/* ==================================================================== */
#include "main.h"
#include "j1772.h"
#include "GopherCAN.h"

/* ==================================================================== */
/* ============================= DEFINES ============================== */
/* ==================================================================== */

// J1772 charging Control Pilot (CP) signal standard values
// J1772 generates a 1 kHz full cycle CP PWM signal

// Timeout of CP PWM signal in milliseconds
#define CP_PWM_TIMOUT_MICROSEC   (10U)

// Maximum continuous ampere rating is 0.6 A per 10 us of high time for PWM signal 
#define CP_CURRENT_PER_MICROSEC   (0.06f)  // 0.6 A per 10 us = 0.06 A per 1 us

// Minimum and maximum allowed high time for formula
#define CP_MIN_HIGH_TIME_MICROSEC    (100U)
#define CP_MAX_HIGH_TIME_MICROSEC    (850U)

// Standard voltage for J1772 AC level 1 and 2 charging
#define STANDARD_LVL1_VOLT (120.0f)
#define STANDARD_LVL2_VOLT (208.0f)

// Maximum current for J1772 AC level 1 charging
#define STANDARD_LVL1_AMP (16U)

// Standard NEMA maximum current in Amps and voltage in Volts
// The charger will assume the standard power limit for NEMA unless CP_PWM is detected,
// indicating the possibility of a higher power limit
#define DEFAULT_CURRENT_LIMIT   (15U)
#define DEFAULT_VOLTAGE (110U)

// Absolute maximum current of 20 Amps to comply with FSAE comp rules
#define MAX_ALLOWED_AMP (20U)


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
  @brief    Determine the maximum power limit for charging
  @param    chargingData Data struct to return charging info
*/

void getJ1772Status(chargingData_S *chargingData)
{

    if((HAL_GetTick() - cpLastUpdate) < CP_PWM_TIMOUT_MICROSEC && cpLastUpdate != 0)
	{
		// HAL GPIO -> ENABLE CP
        HAL_GPIO_WritePin(CP_EN_GPIO_Port, CP_EN_Pin, GPIO_PIN_SET);

        // Copy local of volatile variable
        uint32_t localHighTime = cpHighTime;

        // Calculate current limit
        if (localHighTime < CP_MIN_HIGH_TIME_MICROSEC)
        {
            localHighTime = CP_MIN_HIGH_TIME_MICROSEC;
        }
        else if (localHighTime > CP_MAX_HIGH_TIME_MICROSEC)
        {
            localHighTime = CP_MAX_HIGH_TIME_MICROSEC;
        }

        // Calculate max current capacity
        chargingData->maxAmpacity = cpHighTime * CP_CURRENT_PER_MICROSEC;

        // Clamp max current to 20 A to comply with comp rules
        if(chargingData->maxAmpacity > MAX_ALLOWED_AMP)
        {
            chargingData->maxAmpacity = MAX_ALLOWED_AMP;
        }

        // Calculate power limit
        if(chargingData->maxAmpacity <= STANDARD_LVL1_AMP)
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
        // No J1772 detected, charge at default NEMA values

        // HAL GPIO -> DISABLE CP
        HAL_GPIO_WritePin(CP_EN_GPIO_Port, CP_EN_Pin, GPIO_PIN_RESET);

        // Set power limit to default
        chargingData->maxAmpacity = DEFAULT_CURRENT_LIMIT;
        chargingData->powerLimit = DEFAULT_VOLTAGE * DEFAULT_CURRENT_LIMIT;
    }

    // Send charging power limit to BMS over CAN
    update_and_queue_param_float(&chargingPowerLimit,chargingData->powerLimit);

}


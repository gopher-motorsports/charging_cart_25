/* ==================================================================== */
/* ============================= INCLUDES ============================= */
/* ==================================================================== */

#include "printTask.h"
#include "main.h"
#include <stdio.h>
#include "GopherCAN.h"
#include "gcanUtils.h"

/* ==================================================================== */
/* =================== LOCAL FUNCTION DECLARATIONS ==================== */
/* ==================================================================== */

static void printCellVoltages();
static void printCellTemps();

/* ==================================================================== */
/* =================== LOCAL FUNCTION DEFINITIONS ===================== */
/* ==================================================================== */

static void printCellVoltages()
{
    printf("Cell Voltage:\n");
    printf("|   CELL   |");
    for(int32_t i = 0; i < NUM_CELL_MON_IN_ACCUMULATOR; i++)
    {
        printf("    %02ld     |", i);
    }
    printf("\n");
    for(int32_t i = 0; i < NUM_CELLS_PER_CELL_MONITOR; i++)
    {
        printf("|    %02ld    |", i+1);
        for(int32_t j = 0; j < NUM_CELL_MON_IN_ACCUMULATOR; j++)
        {
            const FLOAT_CAN_STRUCT *cellParam = cellVoltageParams[i][j];
            if (cellParam != NULL)
            {
                printf("   %5.3f   |", cellParam->data);
            }
            else
            {
                printf("  N/A     |");
            }
        }
        printf("\n");
    }
	printf("\n");
}

static void printCellTemps()
{
    printf("Cell Temp:\n");
    printf("|   BMB    |");
    for(int32_t i = 0; i < NUM_CELL_MON_IN_ACCUMULATOR; i++)
    {
        printf("     %02ld    |", i);
    }
    printf("\n");
    for(int32_t i = 0; i < NUM_CELLS_PER_CELL_MONITOR; i++)
    {
        printf("|    %02ld    |", i+1);
        for(int32_t j = 0; j < NUM_CELL_MON_IN_ACCUMULATOR; j++)
        {
            printf("   %3.1f   |", (double)telemetryData->bmb[j].cellTemp[i]);
            printf("\n");
        }
    }
    printf("|  Board   |");
    for(int32_t j = 0; j < NUM_CELL_MON_IN_ACCUMULATOR; j++)
    {
        if((telemetryData->bmb[j].boardTempStatus == GOOD) && (telemetryData->bmbStatus[j] == GOOD))
        {
            if((telemetryData->bmb[j].boardTemp < 0.0f) || telemetryData->bmb[j].boardTemp >= 100.0f)
            {
                printf("   %3.1f   |", (double)telemetryData->bmb[j].boardTemp);
            }
            else
            {
                printf("    %3.1f   |", (double)telemetryData->bmb[j].boardTemp);
            }
        }
        else
        {
            printf(" NO SIGNAL |");
        }
    }
	printf("\n");

}
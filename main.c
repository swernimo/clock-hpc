#include "mcc_generated_files/mcc.h"

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    TMR0_StartTimer();
    while (1)
    {
        if(TMR0_HasOverflowOccured()){
            TMR0_StopTimer();
            LED_Toggle();
            PIR0bits.TMR0IF = 0;
            TMR0_StartTimer();
        }
    }
}
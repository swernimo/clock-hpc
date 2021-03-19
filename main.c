#include "mcc_generated_files/mcc.h"
#include "I2C.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"
#define EEADDR 0x64
#define RTCC_ADDR 0x6F //0x57
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    I2C_Initialize();
    I2C_Start();
    I2C_Write(RTCC_ADDR, 0x06, 0x05);
    I2C_Stop();
    __delay_ms(5);
    I2C_Start();
    uint8_t data = I2C_Read(RTCC_ADDR, 0x06);
//    uint8_t data = i2c_read1ByteRegister(RTCC_ADDR, 0x06);
    I2C_Stop();

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
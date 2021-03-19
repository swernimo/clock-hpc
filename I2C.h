#ifndef I2C
#define	I2C

#include <xc.h>
#include <stdint.h>

void I2C_Initialize(void);
void I2C_Start();
void I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
uint8_t I2C_Read(uint8_t address, uint8_t reg);
void I2C_Stop();

#endif	


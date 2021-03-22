#include "I2C.h"

void I2C_Initialize(){
    SSP1STAT = 0x80;
    SSP1CON1 = 0x08;
    SSP1CON2 = 0x00;
    SSP1ADD  = 0x06;
    SSP1CON1bits.SSPEN = 0;
}

void I2C_Start(){
    SSP1CON1bits.SSPEN = 1;
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN);
    PIR3bits.SSP1IF = 0;
}

void I2C_Write(uint8_t address, uint8_t reg, uint8_t data){
    I2C_Start();
    SSP1BUF = (address << 1);//left shift 1 bit to clear 7th bit (7th bit == 0 for write)
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
    if(SSP1CON2bits.ACKSTAT){
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN);
        return;
    }
    
    SSP1BUF = reg;
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
    if(SSP1CON2bits.ACKSTAT){
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN);
        return;
    }
    
    SSP1BUF = data;
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
    __delay_ms(5);
    I2C_Stop();
}

uint8_t I2C_Read(uint8_t address, uint8_t reg){
    I2C_Start();
    uint8_t data;
    
    SSP1BUF = (address << 1);//left shift 1 bit to clear 7th bit (7th bit == 0 for write)
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
    if(SSP1CON2bits.ACKSTAT){
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN);
        return (0xFF);
    }
    
    SSP1BUF = reg;
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
    if(SSP1CON2bits.ACKSTAT){
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN);
        return (0xFF);
    }
    
    SSP1CON2bits.RSEN = 1;
    while(SSP1CON2bits.RSEN);
    PIR3bits.SSP1IF = 0;
    
    address = (address << 1); //shift left 1 bit to clear 7th bit
    address |= 0x01; //bitwise OR to set 7th bit a 1 (read is 1))    
    SSP1BUF = address;
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
    if(SSP1CON2bits.ACKSTAT){
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN);
        return (0xFF);
    }
    SSP1CON2bits.RCEN = 1;    
    while(!SSP1STATbits.BF);
    data = SSP1BUF;
    
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while(SSP1CON2bits.ACKEN);
        
    I2C_Stop();
    
    return data;
}

void I2C_Stop(){
    SSP1CON2bits.PEN = 0;
    while(SSP1CON2bits.PEN);
    SSP1CON1bits.SSPEN = 0;
    SSP1CON2bits.RCEN = 0;
}
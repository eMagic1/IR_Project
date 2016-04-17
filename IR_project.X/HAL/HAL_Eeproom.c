#ifndef __HAL_EEPROM_C__
#define __HAL_EEPROM_C__

#include <xc.h> 
#include "HAL_Eeprom.h"

void HAL_Eeprom_Write(int i_Address, unsigned char u8_Data)
{
    eeprom_write(i_Address, u8_Data); 
}

void HAL_Eeprom_Read(int i_Address, unsigned char * p_u8_Data)
{
    *p_u8_Data = eeprom_read(i_Address);
}
unsigned char ReadEEByte(unsigned char address)
{
    EEADR = address; // load address of EEPROM to read
    EECON1bits.EEPGD = 0; // access EEPROM data memory
    EECON1bits.CFGS = 0; // do not access configuration registers
    EECON1bits.RD = 1; // initiate read 
    return EEDATA; // return EEPROM byte
}

// Write Byte to internal EEPROM
unsigned char WriteEEByte(unsigned char address, unsigned char data)
{
    EECON1bits.EEPGD = 0;    //Point to EEPROM
    EECON1bits.WREN = 1;    //EEPROM Write Enable Bit
    INTCONbits.GIE = 0;        //Disable all Interrupts
    EEADR=address; // load address of write to EEPROM
    EEDATA=data; // load data to write to EEPROM    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    while(!PIR2bits.EEIF);
    PIR2bits.EEIF = 0;    
    //Verify write operation
    if (ReadEEByte(address)==data) // read the byte we just wrote to EEPROM
    return 1; // write was successful
    else
    return 0; // write failed
}
#endif

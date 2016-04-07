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

#endif

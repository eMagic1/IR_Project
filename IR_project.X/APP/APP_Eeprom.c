#ifndef _APP_EEPROM_C__
#define _APP_EEPROM_C__

#include "../HAL/HAL_Eeprom.h"
#include "APP_Eeprom.h"
#include    "APP_LEDs.h"
void Write_State_Of_Load(LOAD_ID eLoadID, unsigned char value)
{
    WriteEEByte(STATE_ADDRESS + eLoadID, value);
}

void Read_State_Of_Load(LOAD_ID eLoadID, unsigned char * p_value)
{
     *p_value = ReadEEByte(STATE_ADDRESS + eLoadID);
}

void Write_IR_Data(LOAD_ID eLoadID, unsigned char * p_Data, unsigned char u8_Len)
{
    unsigned char u8_Index;
    //need update write len :v
    WriteEEByte(DATA_LEN_ADDRESS + eLoadID * DATA_LEN_SIZE, u8_Len);
    for(u8_Index = 0; u8_Index <= u8_Len; u8_Index ++)
    {
        WriteEEByte( IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + u8_Index , p_Data[u8_Index]);
    }
}
void Read_IR_Data_Len(LOAD_ID eLoadID, unsigned char * p_Len)
{
    *p_Len = ReadEEByte(DATA_LEN_ADDRESS + eLoadID * DATA_LEN_SIZE);
}

void Read_IR_Data_At(LOAD_ID eLoadID, unsigned char * p_Data, unsigned char Index)
{
    *p_Data = ReadEEByte(IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + Index);   
}
#endif
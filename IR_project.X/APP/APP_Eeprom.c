#ifndef _APP_EEPROM_C__
#define _APP_EEPROM_C__

#include "../HAL/HAL_Eeprom.h"
#include "APP_Eeprom.h"

void Write_State_Of_Load(LOAD_ID eLoadID, unsigned char value)
{
    HAL_Eeprom_Write(STATE_ADDRESS + eLoadID, value);
}

void Read_State_Of_Load(LOAD_ID eLoadID, unsigned char * p_value)
{
    HAL_Eeprom_Read(STATE_ADDRESS + eLoadID, p_value);
}

void Write_IR_Data(LOAD_ID eLoadID, unsigned short * p_Data, unsigned char u8_Len)
{
    unsigned char u8_Index;
    //need update write len :v
    HAL_Eeprom_Write(DATA_LEN_ADDRESS + eLoadID * DATA_LEN_SIZE, u8_Len);
    for(u8_Index = 0; u8_Index <= u8_Len; u8_Index ++)
    {
        //write first byte
        HAL_Eeprom_Write(IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + 2*u8_Index    , (unsigned char)(p_Data[u8_Index]&&0x00FF));
        //write next byte
        HAL_Eeprom_Write(IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + 2*u8_Index + 1, (unsigned char)((p_Data[u8_Index]&&0xFF00)>>8));
    }
}
void Read_IR_Data(LOAD_ID eLoadID, unsigned short * p_Data, unsigned char * p_Len)
{
    unsigned char u8_Index;
    unsigned char u8_Data_L;
    unsigned char u8_Data_H;
    unsigned char u8_Len = 0;
    
    HAL_Eeprom_Read(DATA_LEN_ADDRESS + eLoadID * DATA_LEN_SIZE, &u8_Len);
    *p_Len = u8_Len;
    for(u8_Index = 0; u8_Index <= u8_Len; u8_Index ++)
    {
        //read first byte
        HAL_Eeprom_Read(IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + 2*u8_Index    , &u8_Data_L);
        //read next byte
        HAL_Eeprom_Read(IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + 2*u8_Index + 1, &u8_Data_H);
        p_Data[u8_Index] = (unsigned short)(u8_Data_H*256 + u8_Data_L);
    }
}

void Read_IR_Data_Len(LOAD_ID eLoadID, unsigned char * p_Len)
{
    HAL_Eeprom_Read(DATA_LEN_ADDRESS + eLoadID * DATA_LEN_SIZE, p_Len);
}

void Read_IR_Data_At(LOAD_ID eLoadID, unsigned short * p_Data, unsigned char Index)
{
    unsigned char u8_Data_L;
    unsigned char u8_Data_H;
   
    //read first byte
    HAL_Eeprom_Read(IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + 2*Index    , &u8_Data_L);
    //read next byte
    HAL_Eeprom_Read(IR_ADDRESS + eLoadID*IR_DATA_WORD_SIZE + 2*Index + 1, &u8_Data_H);
    *p_Data = (unsigned short)(u8_Data_H*256 + u8_Data_L);

}
#endif
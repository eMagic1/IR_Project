/* 
 * File:   APP_Eeprom.h
 * Author: Minh
 *
 * Created on March 31, 2016, 9:00 PM
 */
#ifndef APP_EEPROM_H
#define	APP_EEPROM_H

#define STATE_ADDRESS   0
#define STATE_SIZE      3
#define NUMBER_LOAD     3
#define DATA_LEN_ADDRESS    STATE_ADDRESS + STATE_SIZE
#define DATA_LEN_SIZE   1
#define IR_ADDRESS      DATA_LEN_ADDRESS + DATA_LEN_SIZE * NUMBER_LOAD

#define IR_DATA_WORD_SIZE    100

typedef enum
{
    LOAD_1 = 0,
    LOAD_2,
    LOAD_3,
}LOAD_ID;

#ifdef	__cplusplus
extern "C" {
#endif
    
void Write_State_Of_Load(LOAD_ID eLoadID, unsigned char value);
void Read_State_Of_Load(LOAD_ID eLoadID, unsigned char * p_value);
void Read_IR_Data_Len(LOAD_ID eLoadID, unsigned char * p_Len);
void Read_IR_Data_At(LOAD_ID eLoadID, unsigned char * p_Data, unsigned char Index);
#ifdef	__cplusplus
}
#endif

#endif	/* APP_LEDS_H */


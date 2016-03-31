/* 
 * File:   APP_OPTO.h
 * Author: Minh
 *
 * Created on March 31, 2016, 9:10 PM
 */
#ifndef APP_EEPROM_H
#define	APP_EEPROM_H

#define STATE_ADDRESS   0
#define STATE_SIZE      3
#define IR_ADDRESS      STATE_ADDRESS + STATE_SIZE
#define IR_DATA_WORD_SIZE    100

typedef enum
{
    LOAD_ID_1 = 0,
    LOAD_ID_2,
    LOAD_ID_3,
}OPTO_LOAD_ID;

typedef enum
{
    LOAD_OFF = 0,
    LOAD_ON  = 1,
    LOAD_STATE_MAX = 0xff,            
}E_LOAD_STATE;
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* APP_LEDS_H */


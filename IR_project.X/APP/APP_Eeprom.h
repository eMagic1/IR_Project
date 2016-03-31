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
#define IR_ADDRESS      STATE_ADDRESS + STATE_SIZE
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




#ifdef	__cplusplus
}
#endif

#endif	/* APP_LEDS_H */


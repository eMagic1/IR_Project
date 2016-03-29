/* 
 * File:   APP_Beeper.h
 * Author: mle
 *
 * Created on March 29, 2016, 3:48 PM
 */

#ifndef APP_BEEPER_H
#define	APP_BEEPER_H

typedef struct
{
    unsigned short u16_Beeper_Frequency;
    unsigned char u8_Beeper_Volume;
    unsigned char u8_Beeper_Number;
}struct_Beeper;

typedef struct
{
    unsigned short time_on; //in ms
    unsigned short time_off;// in ms
}struct_time_beeper;

typedef enum
{
    BEEPER_STATE_OFF,
    BEEPER_STATE_ON,
}Beeper_State;
#define BEEPER_NOMAL_FREQUENCY 28400
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* APP_BEEPER_H */


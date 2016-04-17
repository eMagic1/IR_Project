/* 
 * File:   APP_Beeper.h
 * Author: mle
 *
 * Created on March 29, 2016, 3:48 PM
 */

#ifndef APP_BEEPER_H
#define	APP_BEEPER_H

#define FREQUENCY_LOW 24400
#define FREQUENCY_MED 28400
#define FREQUENCY_HI  32000

typedef enum
{
    VOLUME_LOW = 0,
    VOLUME_MED = 1,
    VOLUME_HIGH = 2,
    VOLUME_MAX = 3,
}VOLUME_LEVEL; 

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
void BEEPER_Set_Volume_Frequency(unsigned short frequency, VOLUME_LEVEL Volume);
void BEEPER_Direct_Beep(void);
void BEEPER_On_Setting(void);
void BEEPER_Setting_OK(void);
void BEEPER_Setting_Error(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_BEEPER_H */


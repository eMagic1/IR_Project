/* 
 * File:   APP_OPTO.h
 * Author: Minh
 *
 * Created on March 31, 2016, 9:10 PM
 */

#ifndef APP_OPPTO_H
#define	APP_OPPTO_H

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

#ifdef __APP_OPTO_C__
void LOAD_Change_State(OPTO_LOAD_ID e_Load_Id, E_LOAD_STATE e_Load_State);
#else 
extern void LOAD_Change_State(OPTO_LOAD_ID e_Load_Id, E_LOAD_STATE e_Load_State);
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* APP_LEDS_H */


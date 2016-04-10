/* 
 * File:   APP_LEDs.h
 * Author: mle
 *
 * Created on March 29, 2016, 2:43 PM
 */

#ifndef APP_LEDS_H
#define	APP_LEDS_H

typedef enum
{
    LED_1 = 0,
    LED_2 = 1,
    LED_3 = 2,
    LED_ID_MAX = 0xFF,
}E_LED_ID;

typedef enum
{
    LED_OFF = 0,
    LED_ON  = 1,
    LED_STATE_MAX = 0xff,            
}E_LED_STATE;

#ifdef	__cplusplus
extern "C" {
#endif

void LEDs_Change_State(E_LED_ID e_Leds_Id, E_LED_STATE e_Led_State);
void LEDs_Blink(E_LED_ID e_Leds_Id);
void LEDs_Stop_Blink(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_LEDS_H */


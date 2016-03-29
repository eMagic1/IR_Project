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
    LED_1 = 3,
    LED_2 = 4,
    LED_3 = 5,
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




#ifdef	__cplusplus
}
#endif

#endif	/* APP_LEDS_H */


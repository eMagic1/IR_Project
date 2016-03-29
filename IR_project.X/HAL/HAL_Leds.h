/* 
 * File:   HAL_Leds.h
 * Author: Minh
 *
 * Created on March 28, 2016, 9:03 PM
 */

#ifndef HAL_LEDS_H
#define	HAL_LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void GPIO_Leds_Init(void);
void GPIO_Leds_Set(unsigned char pin_number);
void GPIO_Leds_Clear(unsigned char pin_number);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_LEDS_H */


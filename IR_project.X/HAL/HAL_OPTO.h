/* 
 * File:   HAL_OPTO.h
 * Author: Minh
 *
 * Created on March 31, 2016, 8:24 PM
 */

#ifndef HAL_OPTO_H
#define	HAL_OPTO_H

#ifdef	__cplusplus
extern "C" {
#endif

void GPIO_OPTOs_Init(void);
void GPIO_OPTO_Set(unsigned char pin_number);
void GPIO_OPTO_Clear(unsigned char pin_number);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_OPTO_H */


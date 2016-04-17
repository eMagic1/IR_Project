/* 
 * File:   HAL_Buzzer.h
 * Author: Minh
 *
 * Created on March 28, 2016, 9:46 PM
 */

#ifndef HAL_BUZZER_H
#define	HAL_BUZZER_H

#ifdef	__cplusplus
extern "C" {
#endif

void HAL_Buzzer_GPIO_Init(void);
void setPWMFreq(unsigned short Fpwm, unsigned char dutyPercent);
void HAL_Buzzer_PWM_Init(unsigned short frequency_Khz, unsigned char Duty);
void HAL_Buzzer_On(void);
void HAL_Buzzer_Off(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_BUZZER_H */


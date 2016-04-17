/* 
 * File:   HAL_Timer.h
 * Author: Minh
 *
 * Created on April 2, 2016, 5:22 PM
 */

#ifndef HAL_TIMER_H
#define	HAL_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
#ifdef __HAL_TIMER_C__
void HAL_Debonce(void);
void HAL_Timer_0_Init(unsigned char Count_100ms, f_void_IRS * f_p_func);
void HAL_Timer0_Reset(void);
void HAL_Timer0_Stop(void);

void HAL_Timer1_Init(unsigned short timer_ms, f_void_IRS * f_p_func);
void HAL_Timer1_Reset(void);
void HAL_Timer1_Stop(void);

void HAL_Timer2_Init(void);
void HAL_Timer2_Get_TickCount(unsigned char * value);
void HAL_Timer2_Reset(void);
void HAL_Timer2_Stop(void);
#else
extern void HAL_Debonce(void);
extern void HAL_Timer_0_Init(unsigned char Count_100ms, f_void_IRS * f_p_func);
extern void HAL_Timer0_Reset(void);
extern void HAL_Timer0_Stop(void);

extern void HAL_Timer1_Init(unsigned short timer_ms, f_void_IRS * f_p_func);
extern void HAL_Timer1_Reset(void);
extern void HAL_Timer1_Stop(void);

extern void HAL_Timer2_Init(void);
extern void HAL_Timer2_Get_TickCount(unsigned char * value);
extern void HAL_Timer2_Reset(void);
extern void HAL_Timer2_Stop(void);
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_TIMER_H */


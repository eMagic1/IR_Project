/* 
 * File:   APP_Timer.h
 * Author: Minh
 *
 * Created on April 5, 2016, 10:00 PM
 */

#ifndef APP_TIMER_H
#define	APP_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef __APP_TIMER_C__
void Setting_Timer_Start(void);
void Setting_Timer_Stop(void);
#else
extern unsigned char Timer_15s_Is_Over ;
extern void Setting_Timer_Start(void);
extern void Setting_Timer_Stop(void);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* APP_TIMER_H */


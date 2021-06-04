/*
 * Timer_Services.h
 *
 * Created: 4/29/2021 7:02:03 PM
 *  Author: lenovo
 */ 


#ifndef TIMER_SERVICES_H_
#define TIMER_SERVICES_H_

#include "Timer.h"

void PWM_Init(void);
void PWM_Freq_KHZ(u16 freq);
void PWM_Freq_HZ(u16 freq);
void PWM_Duty(u16 duty);

void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void));
void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void));
void Timer1_SetInterruptTime_s (u16 time,void(*LocalFptr)(void));
void PWM_Measure(u32* Pfreq,u8* Pduty);
void PWM_Measure2(u32* Pfreq,u8* Pduty);
static void Func_ICU(void);




#endif /* TIMER_SERVICES_H_ */
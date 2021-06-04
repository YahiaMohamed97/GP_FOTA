

#ifndef TIMER2_H_
#define TIMER2_H_


#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "LCD.h"

typedef enum
{
	T2_NORMAL_MODE=0,
	T2_PHASE_PWM,
	T2_CTC_MODE,
	T2_FAST_PWM
}TIMER2_t;

typedef enum
{
	T2_OC2_DISCONNECTED=0,
	T2_OC2_TOGGLE,
	T2_NON_INVERTING,
	T2_INVERTING,
}T2_OC2;


#define		T2_PRESCALLER_1			1
#define		T2_PRESCALLER_8			2
#define		T2_PRESCALLER_64		3
#define		T2_PRESCALLER_256		4
#define		T2_PRESCALLER_1024		5

void	 TIM2_Init(TIMER2_t timer_mode,T2_OC2 OC_mode,u8 prescaller);
void	 TIM2_CompareMatch_Interrupt_Enable(void);
void	 TIM2_CompareMatch_Interrupt_Disable(void);
void	 TIM2_OverFlow_Interrupt_Enable(void);
void	 TIM2_OverFlow_Interrupt_Disable(void);
u32		 TIM2_Calc_FunTime(void (*local_ptr)(void));
void	 TIM2CTC_SetCallBack(void (*local_ptr)(void));
u32		 TIM2_Return_InterruptConter(void);
void	 TIM2_Write_InterruptCounter(void);
void	 TIM2_SetCallBack(void (*local_ptr)(void));




#endif /* TIMER2_H_ */
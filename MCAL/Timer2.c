
#include "Timer.h"
void TIM2_Init(TIMER2_t timer_mode,T2_OC2 OC_mode,u8 prescaller)
{
	switch(timer_mode)
	{
		case T2_NORMAL_MODE:
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		switch(OC_mode)
		{
			case T2_OC2_DISCONNECTED:
			CLR_BIT(TCCR2,COM20);
			CLR_BIT(TCCR2,COM21);
			break;
			default:
			CLR_BIT(TCCR2,COM20);
			CLR_BIT(TCCR2,COM21);
			break;
		}
		break;
		case T2_PHASE_PWM:
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		switch(OC_mode)
		{
			case T2_NON_INVERTING:
			CLR_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
			break;
			case T2_INVERTING:
			SET_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
			break;
			default:
			CLR_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
			break;
		}
		break;
		case T2_CTC_MODE:
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		switch(OC_mode)
		{
			case T2_OC2_TOGGLE:
			SET_BIT(TCCR2,COM20);
			CLR_BIT(TCCR2,COM21);
			break;
			default:
			SET_BIT(TCCR2,COM20);
			CLR_BIT(TCCR2,COM21);
			break;
		}
		break;
		case T2_FAST_PWM:
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		switch(OC_mode)
		{
			case T2_NON_INVERTING:
			CLR_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
			break;
			case T2_INVERTING:
			SET_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
			break;
			default:
			CLR_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
			break;
		}
		break;
	}
	TCCR2	&=0X78;
	TCCR2	|=prescaller;
}

void TIM2_CompareMatch_Interrupt_Enable(void)
{
	SET_BIT(TIMSK,OCIE2);
}

void TIM2_CompareMatch_Interrupt_Disable(void)
{
	CLR_BIT(TIMSK,OCIE2);
}

void TIM2_OverFlow_Interrupt_Enable(void)
{
	SET_BIT(TIMSK,TOIE2);
}

void TIM2_OverFlow_Interrupt_Disable(void)
{
	CLR_BIT(TIMSK,TOIE2);
}
volatile static u32	 counter=0;
volatile static void (*OC2_PTR)		(void)		=(void*)0;
volatile static void (*OVF2_PTR)	(void)		=(void*)0;
u32 TIM2_Calc_FunTime(void (*local_ptr)(void))
{
	TCNT2=0;
	counter=0;
	TIM2_OverFlow_Interrupt_Enable();
	OVF2_PTR=local_ptr;
	u32 time=(u32)(counter*256)+TCNT0;
	return time;
}

void TIM2_SetCallBack(void (*local_ptr)(void))
{
	OVF2_PTR=local_ptr;
}
/*
void TIM2CTC_SetCallBack(void (*local_ptr)(void))
{
	LCD_WriteInRowCol(1,0);
	LCD_WriteString("Hi");
	OC2_PTR=local_ptr;
	
}
*/
/*
ISR(TIMER2_COMP_vect)
{
	if(OC2_PTR!=(void*)0)
	{
		OC2_PTR();
	}
}
*/
void TIM2_Write_InterruptCounter(void)
{
	counter=0;
}

u32 TIM2_Return_InterruptConter(void)
{
	return counter;
}

ISR(TIMER2_OVF_vect)
{
	counter++;
	if(OVF2_PTR!=(void*)0)
	{
		OVF2_PTR();
	}
}



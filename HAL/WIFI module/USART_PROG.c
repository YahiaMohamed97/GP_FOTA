
#include <avr/io.h>
#include "TYPES.h"
#include "MACROS.h"
#include <avr/delay.h>
#include "USART_INTERFACE.h"


#define THRESHOLD_VALUE  1000
void (*MUSART1_CallBack)(void);

void __vector_19(void)        __attribute__((signal));

void MUSART_VidInit ( unsigned long BAUDRATE) {
#ifdef DOUBLE_SPEED_MODE
	UCSRA |=(1 << U2X);
#endif
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);	/* Enable USART transmitter and receiver */
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	/* Write USCRC for 8 bit data and 1 stop bit */
	UBRRL = BAUD_PRESCALE;							/* Load UBRRL with lower 8 bit of prescale value */
	UBRRH = (BAUD_PRESCALE >> 8);					/* Load UBRRH with upper 8 bit of prescale value */

}


void MUSART1_VidSendCharSync ( u8 Copy_u8Char ){

	UDR = Copy_u8Char ;

	while( GET_BIT(UCSRA, UDRE ) == 0 );

	CLR_BIT( UCSRA, UDRE ) ;

}

void MUSART1_VidSendStringSynch ( u8 * Copy_ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while ( Copy_ptrString[ LOC_u8Iterator ] != '\0' ){

		MUSART1_VidSendCharSync( Copy_ptrString[ LOC_u8Iterator ] );
		LOC_u8Iterator++ ;

	}

}

u8 MUSART1_u8RecCharSynch ( void ){

	u8  LOC_u8Data  = 0 ;
	u32 LOC_TimeOut = 0 ;
	CLR_BIT ( UCSRA , RXC);
	while( ( GET_BIT ( UCSRA , RXC) == 0 ) && ( LOC_TimeOut < THRESHOLD_VALUE ) )
	{
		LOC_TimeOut++;
	}

	if( LOC_TimeOut == THRESHOLD_VALUE )
	{
		LOC_u8Data = 255;
	}
	else
	{
		TOG_BIT(PORTA,0);
		LOC_u8Data = UDR;
	}

	return LOC_u8Data;

}

u8 String[20];
u8 * MUSART1_PtrReadStringSynch ( void ){

	u8 LOC_Iterator = 0 , LOC_u8DataCome ;

	while( ( LOC_u8DataCome = MUSART1_u8RecCharSynch() ) != 13 ){

		String[ LOC_Iterator ] = LOC_u8DataCome ;
		LOC_Iterator++;
	}

	String[LOC_Iterator] = '\0';

	return ( String );

}

void MUSART1_VidClearFlags( void ){

	/* Clear all flags */
	UCSRA = 0;

}

u8 MUSART1_u8ReadDataRegister ( void ){

	return UDR;

}


void MUSART1_VidSetCallBack( void (*ptr) (void) ){

	MUSART1_CallBack = ptr ;

}

void __vector_19(void)
{
	MUSART1_CallBack();

}



#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


#define DOUBLE_SPEED_MODE

#ifdef DOUBLE_SPEED_MODE
	#define BAUD_PRESCALE (int)round(((((double)F_CPU / ((double)BAUDRATE * 8.0))) - 1.0))	/* Define prescale value */
#else
	#define BAUD_PRESCALE (int)round(((((double)F_CPU / ((double)BAUDRATE * 16.0))) - 1.0))	/* Define prescale value */
#endif

void MUSART_VidInit ( unsigned long BAUDRATE) ;
void MUSART1_VidSendCharSync    ( u8 Copy_u8Char      ) ;
void MUSART1_VidSendStringSynch ( u8 * Copy_ptrString ) ;
u8   MUSART1_u8RecCharSynch     ( void                ) ;
u8 * MUSART1_PtrReadStringSynch ( void                ) ;
void MUSART1_VidClearFlags      ( void                ) ;
u8   MUSART1_u8ReadDataRegister ( void                ) ;

void MUSART1_VidSetCallBack     ( void (*ptr) (void)  ) ;

#endif /* USART_INTERFACE_H_ */

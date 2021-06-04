#include "UART.h"


void UART_Init(void)
{
 //9600 buad rate
 UBRRL=51;
 
 //normal speed
 CLEAR_BIT(UCSRA,U2X);
 
 //transmitter & reciever enable preph
 SET_BIT(UCSRB,TXEN);
 SET_BIT(UCSRB,RXEN);
 
 //default frame 8 data 1 stop parity
 
}

void UART_Send(u8 data)
{
	while (READ_BIT(UCSRA,UDRE)==0);
	UDR=data;
}



u8 UART_Receive()
{
	while (READ_BIT(UCSRA,RXC)==0);
	return UDR;
}

u8 UART_Receive_PeriodicCheck(u8* data)
{
	if (READ_BIT(UCSRA,RXC)==1)
	{
		*data=UDR;
		return 1;
	}
	
	return 0;
}

#include "DIO_Interface.h"
extern const DIO_PinStatus_type  PinsStatusArray[TOTAL_PINS];
void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	u8 Pin_num = pin%8;
	DIO_Port_type port =pin/8;
	
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,Pin_num);
			break;
			
			case PB:
			SET_BIT(DDRB,Pin_num);
			break;
			
			case PC:
			SET_BIT(DDRC,Pin_num);
			break;
			
			case PD:
			SET_BIT(DDRD,Pin_num);
			break;
		}

		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLEAR_BIT(DDRA,Pin_num);
			CLEAR_BIT(PORTA,Pin_num);
			break;
			
			case PB:
			CLEAR_BIT(DDRB,Pin_num);
			CLEAR_BIT(PORTB,Pin_num);
			break;
			
			case PC:
			CLEAR_BIT(DDRC,Pin_num);
			CLEAR_BIT(PORTC,Pin_num);
			break;
			
			case PD:
			CLEAR_BIT(DDRD,Pin_num);
			CLEAR_BIT(PORTD,Pin_num);
			break;
		}
		  break;
	     case INLLUP:
		 switch(port)
		 {
			 case PA:
			 CLEAR_BIT(DDRA,Pin_num);
			 SET_BIT(PORTA,Pin_num);
			 break;
			 
			 case PB:
			 CLEAR_BIT(DDRB,Pin_num);
			 SET_BIT(PORTB,Pin_num);
			 break;
			 
			 case PC:
			 CLEAR_BIT(DDRC,Pin_num);
			 SET_BIT(PORTC,Pin_num);
			 break;
			 
			 case PD:
			 CLEAR_BIT(DDRD,Pin_num);
			 SET_BIT(PORTD,Pin_num);
			 break;
		 }
		 break;
	}
}
u8 DIO_ReadPort(DIO_Port_type port)
{
	switch(port)
	{
		case PA:
		return PINA;
		break;
		
		case PB:
		return PINB;
		break;
		
		case PC:
		return PINC;
		break;
		
		case PD:
		return PIND;
		break;
	}
}
void DIO_WritePin(DIO_Pin_type pin,DIO_Voltage_type volt)
{
	u8 DIO_Pin_num = pin%8;
	DIO_Port_type port =pin/8;
	switch(volt)
	{
		case HIGH:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,DIO_Pin_num);
			SET_BIT(PORTA,DIO_Pin_num);
			break;
			
			case PB:
			SET_BIT(DDRB,DIO_Pin_num);
			SET_BIT(PORTB,DIO_Pin_num);
			break;
			
			case PC:
			SET_BIT(DDRC,DIO_Pin_num);
			SET_BIT(PORTC,DIO_Pin_num);
			break;
			
			case PD:
			SET_BIT(DDRD,DIO_Pin_num);
			SET_BIT(PORTD,DIO_Pin_num);
			break;
		}
		break;
		case LOW:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,DIO_Pin_num);
			CLEAR_BIT(PORTA,DIO_Pin_num);
			break;
			
			case PB:
			SET_BIT(DDRB,DIO_Pin_num);
			CLEAR_BIT(PORTB,DIO_Pin_num);
			break;
			
			case PC:
			SET_BIT(DDRC,DIO_Pin_num);
			CLEAR_BIT(PORTC,DIO_Pin_num);
			break;
			
			case PD:
			SET_BIT(DDRD,DIO_Pin_num);
			CLEAR_BIT(PORTD,DIO_Pin_num);
			break;
		}
		break;
	}	
}
u8 DIO_ReadPin(DIO_Pin_type pin)
{ 
	u8 volt=0;
	u8 DIO_Pin_num = pin%8;
	DIO_Port_type port =pin/8;
	switch(port)
	{
		case PA:
		volt = READ_BIT(PINA,DIO_Pin_num);
		break;
		
		case PB:
		volt = READ_BIT(PINB,DIO_Pin_num);
		break;
		
		case PC:
		volt = READ_BIT(PINC,DIO_Pin_num);
		break;
		
		case PD:
		volt = READ_BIT(PIND,DIO_Pin_num);
		break;
	}
	return volt;
}
void DIO_WritePort(DIO_Port_type port,u8 value)
{
	switch(port)
	{
		case PA:
		PORTA=value;
		break;
		
		case PB:
		PORTB=value;
		break;
		
		case PC:
		PORTC=value;
		break;
		
		case PD:
		PORTD=value;
		break;
	}
}
void DIO_Init(void)
{
	DIO_Pin_type  i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinsStatusArray[i]);
	}
}
void  DIO_TogglePin(DIO_Pin_type pin)
{
	u8 status=DIO_ReadPin(pin);
	if (status==0)
	{
		DIO_WritePin(pin,HIGH);
	} 
	else
	{
		DIO_WritePin(pin,LOW);
	}
}

/*
 * StdType.h
 *
 * Created: 9/29/2020 6:28:10 PM
 *  Author: Al Badr
 */ 


#ifndef STDTYPE_H_
#define STDTYPE_H_

typedef unsigned char        u8;
typedef unsigned int        u16;
typedef unsigned long       u32;
typedef unsigned long long  u64;

typedef signed char          s8;
typedef signed int          s16;
typedef signed long         s32;
typedef signed long long    s64;


typedef enum{FALSE=0,TRUE}Bool_type;

#endif /* STDTYPE_H_ */




/*
---------------------7seg-------------------------------------------------------
#define  SEGMENT_PORT                PORTA
#define  EN1                         6
#define  EN2                         7
void sevsegment_display (u8 n)
{  u8 x=n%10;
	u8 y=n/10;
	
	SEGMENT_PORT=SegNum[x]<<1;
	SET_BIT(PORTC,EN1);
	CLEAR_BIT(PORTC,EN2);
	_delay_ms(2);
	SEGMENT_PORT=SegNum[y]<<1;
	SET_BIT(PORTC,EN2);
	CLEAR_BIT(PORTC,EN1);
	_delay_ms(2);
	
}
int main(void)
{
	
	DDRA=0xff;
	DDRC=0xff;
	DDRD=0x00;
	PORTD=0xff;
	SET_BIT(PORTC,EN1);
	SET_BIT(PORTC,EN2);
	 u8 i=0,j;

	while(1)
	{ 
		sevsegment_display(i);
		if (READ_BIT(PIND,2)==0)
		{
			i++;
			_delay_ms(200);
		}
		if (READ_BIT(PIND,3)==0)
		{
			i--;
		_delay_ms(200);
		}
		 
	/*for (i=0;i<99;i++)
	{
		for (j=0;j<125;j++)
		{
			sevsegment_display(i);
		}
	}
			u16 x=1000;
	DDRB =0xff;
	u8 i,j;
	while(1)
	{
	    for(i=0;i<5;i++)
		{
			PORTB=0xff;
			_delay_ms(x/4);
			PORTB=0;
			_delay_ms(x/4);
			
		}
		
		for(i=0;i<5;i++)
		{
			PORTB=0xf0;
			_delay_ms(x/2);
			PORTB=0x0f;
			_delay_ms(x/2);
		}
		for(i=0;i<5;i++)
		{
			PORTB=0B11000000;
			_delay_ms(x/4);
			PORTB=0B00110000;
			_delay_ms(x/4);
			PORTB=0B00001100;
			_delay_ms(x/4);
			PORTB=0B00000011;
			_delay_ms(x/4);
			
		}
		for(i=0;i<5;i++)
		{
			for(j=0;j<8;j++)
			{
				PORTB=0;
				SET_BIT(PORTB,i);
			}
			_delay_ms(300);
		}
	}
	-------------------------------------------------------------------------7seg*/
/*
-------------------------leds ----------------
 for (u8 i=0;i<150;i++)
 {
	 SET_BIT(PORTA,x);
	 _delay_ms(2);
 }
 if (READ_BIT(PIND,2)==0)
 {
	 CLEAR_BIT(PORTA,x);
	 x++;
	 if (x==8)
	 {
		 x=0;
	 }
	 
 }
 if (READ_BIT(PIND,3)==0)
 {
	 CLEAR_BIT(PORTA,x);
	 x--;
	  if (x==-1)
	  {
		  x=8;
	  }
	  
  }*/
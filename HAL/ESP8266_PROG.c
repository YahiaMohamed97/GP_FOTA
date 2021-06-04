
#include "TYPES.h"
#include "MACROS.h"
#include <avr/io.h>
#include "USART_INTERFACE.h"

#include "ESP8266_INTERFACE.h"

#include <util/delay.h>

u8 volatile Iterator = 0  ;
u8 volatile DataCome[200] ;

void MUSART_CallBack ( void ){

	/* Receive ESP8266 Response */
	DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();
	/* ------------------ */
	Iterator++;
	MUSART1_VidClearFlags();

}

void ESP8266_VidInit ( void ){
	u8 Local_u8Result = 0;
		while(Local_u8Result == 0)
		{
			MUSART1_VidSendStringSynch( (u8 *)"AT\r\n" );
			//_delay_ms( 3000 );
			Local_u8Result = voidEspValidateCmd();

		}
		SET_BIT(PORTA,0);

		Local_u8Result = 0;
		while(Local_u8Result == 0)
		{
			MUSART1_VidSendStringSynch( (u8 *)"AT+CIPMODE=0\r\n" );
			_delay_ms( 3000 );
			Local_u8Result = voidEspValidateCmd();
		}
}

void ESP8266_VidConnectToWiFi ( u8 * SSID , u8 * Password ){

	ESP8266_VidClearBuffer();
	u8 Local_u8Result = 0;
		while(Local_u8Result == 0)
		{
			MUSART1_VidSendStringSynch( (u8 *) "AT+CWJAP=\"" );
			MUSART1_VidSendStringSynch( (u8 *) SSID );
			MUSART1_VidSendStringSynch( (u8 *) "\",\"" );
			MUSART1_VidSendStringSynch( (u8 *) Password);
			MUSART1_VidSendStringSynch( (u8 *) "\"\r\n");
			_delay_ms( 8000 );
			Local_u8Result = voidEspValidateCmd();
		}
		Local_u8Result=0;
}


void ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port ){

	ESP8266_VidClearBuffer();
	u8 Local_u8Result = 0;
		while(Local_u8Result == 0)
		{
			MUSART1_VidSendStringSynch( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
			MUSART1_VidSendStringSynch( (u8 *) Copy_u8Domain );
			MUSART1_VidSendStringSynch( (u8 *) "\"," );
			MUSART1_VidSendStringSynch( (u8 *) Copy_u8Port );
			MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
			_delay_ms( 2000 );
			Local_u8Result = voidEspValidateCmd();
		}

}

void ESP8266_VidSendHttpReq( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();
	u8 Local_u8Result = 0;
		while(Local_u8Result == 0)
		{
			MUSART1_VidSendStringSynch( (u8 *) "AT+CIPSEND=" );
			MUSART1_VidSendStringSynch( (u8 *) Copy_u8Length );
			MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
			_delay_ms( 4000 );
			Local_u8Result = voidEspValidateCmd();
		}
		Local_u8Result=0;
	ESP8266_VidClearBuffer();
	while(Local_u8Result == 0)
	{
		MUSART1_VidSendStringSynch( (u8 *) "GET /update?api_key=" );
		MUSART1_VidSendStringSynch( (u8 *) Copy_u8Key );
		MUSART1_VidSendStringSynch( (u8 *) "&field1=" );
		MUSART1_VidSendStringSynch( (u8 *) Copy_u8Data );
		MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
		_delay_ms( 20000 );
		Local_u8Result = voidEspValidateCmd();
	}
	Local_u8Result=0;
}

u8   ESP8266_u8ReceiveHttpReq( u8 * Copy_u8ChannelID , u8 * Copy_u8Length ){
	ESP8266_VidClearBuffer();
	u8 Local_u8Result = 0;
		while(Local_u8Result == 0)
		{
			MUSART1_VidSendStringSynch( (u8 *) "AT+CIPSEND=" );
			MUSART1_VidSendStringSynch( (u8 *) Copy_u8Length );
			MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
			_delay_ms( 4000 );
			Local_u8Result = voidEspValidateCmd();
		}

	ESP8266_VidClearBuffer();
	while(Local_u8Result == 0)
	{
		Local_u8Result = 0;
		MUSART1_VidSendStringSynch( (u8 *) "GET http://" );
		MUSART1_VidSendStringSynch( (u8 *) Copy_u8ChannelID );
		MUSART1_VidSendStringSynch( (u8 *) "/value.txt\r\n" );
		_delay_ms( 20000 );
		Local_u8Result = voidEspValidateCmd();
	}

	ESP8266_VidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );

	/*For yrabiot3.freevar.com ( Value Array Index )*/
	return  DataCome[82] ;


}

void ESP8266_VidClearBuffer ( void ){

	u8 LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 150 ; LOC_u8Iterator1++ ){

		DataCome[ LOC_u8Iterator1 ] = 0 ;

	}

}




u8 voidEspValidateCmd(void)
{
	u8 Local_u8Response[100] = {0};
	u8 i = 0;
	u8 Dummy = 0;
	u8 Result = 0;

	while (Dummy != 255)
	{
		Dummy = MUSART1_u8RecCharSynch();
		Local_u8Response[i] = Dummy;
		i++;
	}

	/* Check if Ok */
	if (Local_u8Response[0] == 'O' && Local_u8Response[1] == 'K')
	{
		Result = 1;

	}

	return Result;
}


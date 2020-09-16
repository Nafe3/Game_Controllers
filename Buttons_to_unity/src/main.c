#include "STD_TYPES.h"
#include "GPIO.h"
#include "RCC_interface.h"

#include "HUART_interface.h"
#include "Debug.h"
#include "Trace.h"
#include "Delay_interface.h"

int main(void)
{
	/*** Variables Declaration ***/
	u8 Up_Button_State   ; //Up    Button pressed state
	u8 Down_Button_State ; //Down  Button pressed state
	u8 Right_Button_State; //Right Button pressed state
	u8 Left_Button_State ; //Left  Button pressed state

	/*** Hardware Initialization ***/
	RCC_f32GetPLLMultiplierValue();
	RCC_voidChangeBusPrescalar(RCC_APB1_PRESCALAR_2);

	RCC_voidEnablePeripheralClock(RCC_PERIPHERALS_PORTA); //Activate clock for button port
	RCC_voidEnablePeripheralClock(RCC_PERIPHERALS_PORTC); //Activate clock for on-board led port

	HUART_u8Init(HUART_USART1, 115200, UART_STOP_BIT1, UART_PARITY_DISABLED);

	/*** OnBoard_Led Configuration ***/
	GPIO_Pin_t OnBoard_Led;
	OnBoard_Led.port = PORTC;
	OnBoard_Led.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	OnBoard_Led.pin  = 13;
	OnBoard_Led.speed= GPIO_OUTPUT_SPEED_50MHz;

	GPIO_Init(&OnBoard_Led);
	GPIO_Pin_Write(&OnBoard_Led,HIGH);

	/*** Buttons Pins Configuration ***/
	GPIO_Pin_t Up_Button;
	Up_Button.port = PORTA;
	Up_Button.mode = GPIO_MODE_INPUT_PULLUP_PULLDOWN;
	Up_Button.pin  = 4;
	Up_Button.speed= GPIO_INPUT_MODE_RESET_STATE;

	GPIO_Pin_t Down_Button;
	Down_Button.port = PORTA;
	Down_Button.mode = GPIO_MODE_INPUT_PULLUP_PULLDOWN;
	Down_Button.pin  = 6;
	Down_Button.speed= GPIO_INPUT_MODE_RESET_STATE;

	GPIO_Pin_t Right_Button;
	Right_Button.port = PORTA;
	Right_Button.mode = GPIO_MODE_INPUT_PULLUP_PULLDOWN;
	Right_Button.pin  = 7;
	Right_Button.speed= GPIO_INPUT_MODE_RESET_STATE;

	GPIO_Pin_t Left_Button;
	Left_Button.port = PORTA;
	Left_Button.mode = GPIO_MODE_INPUT_PULLUP_PULLDOWN;
	Left_Button.pin  = 5;
	Left_Button.speed= GPIO_INPUT_MODE_RESET_STATE;

	/*** Initialization & Activating pull-up resistors ***/
	GPIO_Init(&Up_Button   );
	GPIO_Init(&Down_Button );
	GPIO_Init(&Right_Button);
	GPIO_Init(&Left_Button );

	GPIO_Pin_Write(&Up_Button   ,HIGH);
	GPIO_Pin_Write(&Down_Button ,HIGH);
	GPIO_Pin_Write(&Right_Button,HIGH);
	GPIO_Pin_Write(&Left_Button ,HIGH);

	while(1)
	{
		/*** Reading Input data ***/
		//delay_ms(50);
		GPIO_Pin_Read(&Up_Button   ,&Up_Button_State   );
		GPIO_Pin_Read(&Down_Button ,&Down_Button_State );
		GPIO_Pin_Read(&Right_Button,&Right_Button_State);
		GPIO_Pin_Read(&Left_Button ,&Left_Button_State );


		/*** Actions ***/
		GPIO_Pin_Write(&OnBoard_Led,HIGH);

		if(Up_Button_State   == LOW) {printmsg1("UP\r\n")   ;GPIO_Pin_Write(&OnBoard_Led,LOW);} //if the button is pressed
		if(Down_Button_State == LOW) {printmsg1("DOWN\r\n") ;GPIO_Pin_Write(&OnBoard_Led,LOW);} //if the button is pressed
		if(Right_Button_State== LOW) {printmsg1("RIGHT\r\n");GPIO_Pin_Write(&OnBoard_Led,LOW);} //if the button is pressed
		if(Left_Button_State == LOW) {printmsg1("LEFT\r\n") ;GPIO_Pin_Write(&OnBoard_Led,LOW);} //if the button is pressed
	}

	return 0;
}

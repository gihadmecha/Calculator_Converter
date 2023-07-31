
#include "Calculator_Converter.h"

void Calculator_Converter_Init ()
{
	DIO_Init();
	LCD_Init();
}

void Calculator_Converter_welcomeMessage ()
{
	LCD_GoTo(0, 0);
	LCD_WriteString("Welcome !!");
	_delay_ms(1000);
	LCD_GoTo(0, 0);
	LCD_WriteString("Calculator");
	LCD_GoTo(1, 0);
	LCD_WriteString("made by Gihad");
	_delay_ms(1000);
}
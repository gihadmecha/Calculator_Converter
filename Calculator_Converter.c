
#include "Calculator_Converter_Private.h"
#include "Calculator_Converter.h"

extern void Calculator_Converter_Init ()
{
	DIO_Init();
	LCD_Init();
	
	Calculator_Converter_welcomeMessage ();
}

static void Calculator_Converter_welcomeMessage ()
{
	LCD_Clear();
	
	LCD_GoTo(0, 0);
	LCD_WriteString("Welcome !!");
	_delay_ms(1000);
	
	LCD_GoTo(0, 0);
	LCD_WriteString("Calculator");
	LCD_GoTo(1, 0);
	LCD_WriteString("made by Gihad");
	_delay_ms(1000);
	
	levelFlag = MAIN_LIST;
	
	LCD_Clear();
}

static void Calculator_Converter_mainList ()
{
	if (levelFlag == MAIN_LIST)
	{
		u8 key = KEYPAD_GetKey();
		while ( key != '1' && key != '2')
		{
			LCD_GoTo(0, 0);
			LCD_WriteString("1.Calculator");
			LCD_GoTo(1, 0);
			LCD_WriteString("2.Converter");
			
			key = KEYPAD_GetKey();
		}
		
		if (key == '1')
		{
			levelFlag = CALCULATE_SCREEN;
		}
		else if (key == '2')
		{
			levelFlag = CONVERT_FROM_LIST;
		}
		
		LCD_Clear();
	}
}

static void Calculator_Converter_scanCalculator ()
{
	key = KEYPAD_GetKey();
	while (key != '=' && key != 'C')
	{
		if (key != NULL)
		{
			if (converterNumberAsCharactersIndex < 13)
			{
				if (converterNumberAsCharactersIndex == 0)
				{
					LCD_GoToClear(1, 0, 13);
					LCD_GoToClear(0, 0, 13);
				}
				
				LCD_WriteChar(key);
				converterNumberAsCharacters[converterNumberAsCharactersIndex] = key;
				converterNumberAsCharactersIndex++;
				converterNumberAsCharacters[converterNumberAsCharactersIndex] = NULL;
			}
		}
		
		key = KEYPAD_GetKey();
	}
}

static void Calculator_Converter_CalculateScreen ()
{
	if (levelFlag == CALCULATE_SCREEN)
	{
		Calculator_Converter_scanCalculator ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 0);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_convertFromList ()
{
	if (levelFlag == CONVERT_FROM_LIST)
	{
		convertFromListKey = KEYPAD_GetKey();
		while (convertFromListKey != '1' && convertFromListKey != '2' && convertFromListKey != '3' && convertFromListKey != 'C')
		{
			LCD_GoTo(0, 0);
			LCD_WriteString("convert from:");
			LCD_GoTo(1, 0);
			LCD_WriteString("1.D");
			LCD_GoTo(1, 6);
			LCD_WriteString("2.H");
			LCD_GoTo(1, 12);
			LCD_WriteString("3.B");
			
			convertFromListKey = KEYPAD_GetKey();
		}
		
		if (convertFromListKey == '1' || convertFromListKey == '2' || convertFromListKey == '3')
		{
			levelFlag = CONVERT_TO_LIST;
		}
		else if (convertFromListKey == 'C')
		{
			levelFlag = MAIN_LIST;
		}
		
		LCD_Clear();
	}
}

static void Calculator_Converter_convertToList ()
{
	if (levelFlag == CONVERT_TO_LIST)
	{
		u8 key = KEYPAD_GetKey();
		while (key != '1' && key != '2' && key != '3' && key != 'C')
		{
			LCD_GoTo(0, 0);
			LCD_WriteString("convert To:");
			LCD_GoTo(1, 0);
			LCD_WriteString("1.D");
			LCD_GoTo(1, 6);
			LCD_WriteString("2.H");
			LCD_GoTo(1, 12);
			LCD_WriteString("3.B");
			
			key = KEYPAD_GetKey();
		}
		
		if (key == '1')
		{
			if (convertFromListKey == '1')
			{
				levelFlag = DEC_TO_DEC;
			}
			else if (convertFromListKey == '2')
			{
				levelFlag = HEX_TO_DEC;
			}
			else if (convertFromListKey == '3')
			{
				levelFlag = BIN_TO_DEC;
			}
		}
		else if (key == '2')
		{
			if (convertFromListKey == '1')
			{
				levelFlag = DEC_TO_HEX;
			}
			else if (convertFromListKey == '2')
			{
				levelFlag = HEX_TO_HEX;
			}
			else if (convertFromListKey == '3')
			{
				levelFlag = BIN_TO_HEX;
			}
		}
		else if (key == '3')
		{
			if (convertFromListKey == '1')
			{
				levelFlag = DEC_TO_BIN;
			}
			else if (convertFromListKey == '2')
			{
				levelFlag = HEX_TO_BIN;
			}
			else if (convertFromListKey == '3')
			{
				levelFlag = BIN_TO_BIN;
			}
		}
		else if (key == 'C')
		{
			levelFlag = MAIN_LIST;
		}
		
		LCD_Clear();
	}
}

static void Calculator_Converter_scan ()
{
	key = KEYPAD_GetKey();
	while (key != '=' && key != 'C')
	{
		if (key != NULL)
		{
			if (converterNumberAsCharactersIndex < 13)
			{
				if (converterNumberAsCharactersIndex == 0)
				{
					LCD_GoToClear(1, 4, 13);
					LCD_GoToClear(0, 4, 13);
				}
				
				LCD_WriteChar(key);
				converterNumberAsCharacters[converterNumberAsCharactersIndex] = key;
				converterNumberAsCharactersIndex++;
				converterNumberAsCharacters[converterNumberAsCharactersIndex] = NULL;
			}
		}
		
		key = KEYPAD_GetKey();
	}
}

static void Calculator_Converter_DecToDec ()
{
	if (levelFlag == DEC_TO_DEC)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("DEC:");
		LCD_GoTo(1, 0);
		LCD_WriteString("DEC:");
		
		Calculator_Converter_scan ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
		
}

static void Calculator_Converter_DecToHex ()
{
	if (levelFlag == DEC_TO_HEX)
	{
		
		LCD_GoTo(0, 0);
		LCD_WriteString("DEC:");
		LCD_GoTo(1, 0);
		LCD_WriteString("HEX:");
		
		Calculator_Converter_scan ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_DecToBin ()
{
	if (levelFlag == DEC_TO_BIN)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("DEC:");
		LCD_GoTo(1, 0);
		LCD_WriteString("BIN:");
		
		Calculator_Converter_scan ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_scanHex ()
{
	key = KEYPAD_GetKey();
	while (key != '=' && key != 'C')
	{
		if (key != NULL)
		{
			if (converterNumberAsCharactersIndex < 13)
			{
				if (converterNumberAsCharactersIndex == 0)
				{
					LCD_GoToClear(1, 4, 13);
					LCD_GoToClear(0, 4, 13);
				}
				
				if (key == '/')
				{
					LCD_WriteChar('A');
					converterNumberAsCharacters[converterNumberAsCharactersIndex] = 'A';
				}
				else if (key == '*')
				{
					LCD_WriteChar('B');
					converterNumberAsCharacters[converterNumberAsCharactersIndex] = 'B';
				}
				else if (key == '-')
				{
					LCD_WriteChar('D');
					converterNumberAsCharacters[converterNumberAsCharactersIndex] = 'D';
				}
				else if (key == '+')
				{
					LCD_WriteChar('E');
					converterNumberAsCharacters[converterNumberAsCharactersIndex] = 'E';
				}
				else
				{
					LCD_WriteChar(key);
					converterNumberAsCharacters[converterNumberAsCharactersIndex] = key;
				}
				converterNumberAsCharactersIndex++;
				converterNumberAsCharacters[converterNumberAsCharactersIndex] = NULL;
			}
		}
		
		key = KEYPAD_GetKey();
	}
}

static void Calculator_Converter_HexToDec ()
{
	if (levelFlag == HEX_TO_DEC)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("HEX:");
		LCD_GoTo(1, 0);
		LCD_WriteString("DEC:");
			
		Calculator_Converter_scanHex ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_HexToHex ()
{
	if (levelFlag == HEX_TO_HEX)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("HEX:");
		LCD_GoTo(1, 0);
		LCD_WriteString("HEX:");
	
		Calculator_Converter_scanHex ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_HexToBin ()
{
	if (levelFlag == HEX_TO_BIN)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("HEX:");
		LCD_GoTo(1, 0);
		LCD_WriteString("BIN:");
			
		Calculator_Converter_scanHex ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_BinToDec ()
{
	if (levelFlag == BIN_TO_DEC)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("BIN:");
		LCD_GoTo(1, 0);
		LCD_WriteString("DEC:");
		
		Calculator_Converter_scan ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_BinToHex ()
{
	if (levelFlag == BIN_TO_HEX)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("BIN:");
		LCD_GoTo(1, 0);
		LCD_WriteString("HEX:");
		
		Calculator_Converter_scan ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static void Calculator_Converter_BinToBin ()
{
	if (levelFlag == BIN_TO_BIN)
	{
		LCD_GoTo(0, 0);
		LCD_WriteString("BIN:");
		LCD_GoTo(1, 0);
		LCD_WriteString("BIN:");
		
		Calculator_Converter_scan ();
		
		if (key == '=')
		{
			converterNumberAsCharactersIndex = 0;
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

extern void Calculator_Converter_Run ()
{
	Calculator_Converter_mainList ();
	Calculator_Converter_CalculateScreen ();
	Calculator_Converter_convertFromList ();
	Calculator_Converter_convertToList ();
	Calculator_Converter_DecToDec ();
	Calculator_Converter_DecToHex ();
	Calculator_Converter_DecToBin ();
	Calculator_Converter_HexToDec ();
	Calculator_Converter_HexToHex ();
	Calculator_Converter_HexToBin ();
	Calculator_Converter_BinToDec ();
	Calculator_Converter_BinToHex ();
	Calculator_Converter_BinToBin ();
}
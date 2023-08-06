
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
	_delay_ms(500);
	
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
			converterNumberAsCharactersIndex = 0;
			levelFlag = CALCULATE_SCREEN;
		}
		else if (key == '2')
		{
			converterNumberAsCharactersIndex = 0;
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
			if (converterNumberAsCharactersIndex < 16)
			{
				if (converterNumberAsCharactersIndex == 0)
				{
					LCD_GoToClear(1, 0, 16);
					LCD_GoToClear(0, 0, 16);
					
					if (key == '+' || key == '-' || key == '*' || key == '/')
					{
						LCD_WriteString("Ans");
					}
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

static void Calculator_Converter_ErrorMessage ()
{
	LCD_Clear();
	LCD_GoTo(0, 0);
	LCD_WriteString("ERROR !!");
	LCD_GoTo(1, 0);
	LCD_WriteString("PRESS ANY KEY ...");
	
	key = KEYPAD_GetKey();
	while (key == NULL)
	{
		key = KEYPAD_GetKey();
	}
	
	LCD_Clear();
}

static u8 Calculator_Converter_IsDecimal ()
{
	for (u8 index = 0; converterNumberAsCharacters[index]; index++)
	{
		//if (converterNumberAsCharacters[0] == '*' || converterNumberAsCharacters[0] == '/')
		//{
			//return 0;
		//}
		if ( (converterNumberAsCharacters[index] < '0' || converterNumberAsCharacters[index] > '9') && converterNumberAsCharacters[index+1] == NULL )
		{
			return 0;
		}
		if ((converterNumberAsCharacters[index] < '0' || converterNumberAsCharacters[index] > '9') && (converterNumberAsCharacters[index+1] < '0' || converterNumberAsCharacters[index+1] > '9'))
		{
			return 0;
		}
	}
	
	return 1;
}

static u64 number1 = 0;
static u64 number2 = 0;
static u8 sign = '+';
static s64 result = 0;
static u8 Calculator_Converter_CalculatorProcess ()
{
	u8 numberFlag = 1;
	u8 digit = 0;
	
	number2 = 0;
	
	for (u8 index = 0; converterNumberAsCharacters[index]; index++)
	{
		if (index == 0)
		{
			if (converterNumberAsCharacters[0] >= '0' && converterNumberAsCharacters[0] <= '9')
			{
				number1 = 0;
			}
			else
			{
				number1 = result;
			}
		}
		
		if (converterNumberAsCharacters[index] >= '0' && converterNumberAsCharacters[index] <= '9' && numberFlag == 1)
		{
			digit = converterNumberAsCharacters[index] - '0';
			number1 = number1 * 10 + digit;
		}
		else if (converterNumberAsCharacters[index] >= '0' && converterNumberAsCharacters[index] <= '9' && numberFlag == 2)
		{
			digit = converterNumberAsCharacters[index] - '0';
			number2 = number2 * 10 + digit;
		}
		else
		{
			numberFlag = 2;
			sign = converterNumberAsCharacters[index];
		}
	}
	
	if (sign == '/' && number2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

static void Calculator_Converter_Calculate ()
{
	switch (sign)
	{
		case '+':
		result = number1 + number2;
		break;
		case '-':
		result = number1 - number2;
		break;
		case '*':
		result = number1 * number2;
		break;
		case '/':
		result = number1 / number2;
		break;
	}
}

static void Calculator_Converter_CalculateScreen ()
{
	if (levelFlag == CALCULATE_SCREEN)
	{
		Calculator_Converter_scanCalculator ();
		
		if (key == '=')
		{
			if (Calculator_Converter_IsDecimal () && Calculator_Converter_CalculatorProcess ())
			{
				Calculator_Converter_Calculate ();
				
				LCD_GoTo(1, 0);
				LCD_WriteNumber(result);
			}
			else
			{
				Calculator_Converter_ErrorMessage ();
			}
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
			LCD_Clear();
			levelFlag = MAIN_LIST;
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
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
			LCD_WriteString("convert ");
			if (convertFromListKey == '1')
			{
				LCD_WriteChar('D');
			}
			else if (convertFromListKey == '2')
			{
				LCD_WriteChar('H');
			}
			else if (convertFromListKey == '3')
			{
				LCD_WriteChar('B');
			}
			LCD_WriteString(" To:");
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

static u64 Calculator_Converter_DecStringToDec ()
{
	u64 number = 0;
	u8 digit = 0;
	for (u8 index = 0; converterNumberAsCharacters[index]; index++)
	{
		digit = converterNumberAsCharacters[index] - '0';
		number = number * 10 + digit;
	}
	return number;
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
			if (Calculator_Converter_IsDecimal ())
			{
				LCD_GoTo(1, 4);
				LCD_WriteString(converterNumberAsCharacters);
			}
			else
			{
				Calculator_Converter_ErrorMessage ();
			}
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
			if (Calculator_Converter_IsDecimal ())
			{
				LCD_GoTo(1, 4);
				LCD_WriteHex(Calculator_Converter_DecStringToDec ());
			}
			else
			{
				Calculator_Converter_ErrorMessage ();
			}
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
			if (Calculator_Converter_IsDecimal ())
			{
				LCD_GoTo(1, 4);
				LCD_WriteBinary (Calculator_Converter_DecStringToDec ());
			}
			else
			{
				Calculator_Converter_ErrorMessage ();
			}
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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

static u64 Calculator_Converter_HexStingToDec ()
{
	u64 number = 0;
	u8 digit = 0;
	for (u8 index = 0; converterNumberAsCharacters[index]; index++)
	{
		if (converterNumberAsCharacters[index] == 'A')
		{
			digit = 10;
		}
		else if (converterNumberAsCharacters[index] == 'B')
		{
			digit = 11;
		}
		else if (converterNumberAsCharacters[index] == 'C')
		{
			digit = 12;
		}
		else if (converterNumberAsCharacters[index] == 'D')
		{
			digit = 13;
		}
		else if (converterNumberAsCharacters[index] == 'E')
		{
			digit = 14;
		}
		else if (converterNumberAsCharacters[index] == 'F')
		{
			digit = 15;
		}
		else
		{
			digit = converterNumberAsCharacters[index] - '0';
		}
		
		number = number * 16 + digit;
	}
	return number;
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
			LCD_GoTo(1, 4);
			LCD_WriteNumber (Calculator_Converter_HexStingToDec ());
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
			LCD_GoTo(1, 4);
			LCD_WriteString(converterNumberAsCharacters);
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
			LCD_GoTo(1, 4);
			LCD_WriteBinary (Calculator_Converter_HexStingToDec ());
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
			levelFlag = MAIN_LIST;
			LCD_Clear();
		}
	}
}

static u8 Calculator_Converter_IsBinary ()
{
	for (u8 index = 0; converterNumberAsCharacters[index]; index++)
	{
		if (converterNumberAsCharacters[0] == '*' || converterNumberAsCharacters[0] == '/')
		{
			return 0;
		}
		if ( (converterNumberAsCharacters[index] < '0' || converterNumberAsCharacters[index] > '9') && converterNumberAsCharacters[index+1] == NULL )
		{
			return 0;
		}
		if ((converterNumberAsCharacters[index] < '0' || converterNumberAsCharacters[index] > '9') && (converterNumberAsCharacters[index+1] < '0' || converterNumberAsCharacters[index+1] > '9'))
		{
			return 0;
		}
		if ((converterNumberAsCharacters[index] >= '2' && converterNumberAsCharacters[index] <= '9'))
		{
			return 0;
		}
	}
	
	return 1;
}

static u64 Calculator_Converter_BinaryStingToDec ()
{
	u64 number = 0;
	u8 digit = 0;
	for (u8 index = 0; converterNumberAsCharacters[index]; index++)
	{
		digit = converterNumberAsCharacters[index] - '0';
		number = number * 2 + digit;
	}
	return number;
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
			if (Calculator_Converter_IsBinary ())
			{
				LCD_GoTo(1, 4);
				LCD_WriteNumber (Calculator_Converter_BinaryStingToDec ());
			}
			else
			{
				Calculator_Converter_ErrorMessage ();
			}
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
			if (Calculator_Converter_IsBinary ())
			{
				LCD_GoTo(1, 4);
				LCD_WriteHex(Calculator_Converter_BinaryStingToDec ());
			}
			else
			{
				Calculator_Converter_ErrorMessage ();
			}
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
			if (Calculator_Converter_IsBinary ())
			{
				LCD_GoTo(1, 4);
				LCD_WriteString(converterNumberAsCharacters);
			}
			else
			{
				Calculator_Converter_ErrorMessage ();
			}
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
		}
		else if (key == 'C')
		{
			converterNumberAsCharactersIndex = 0;
			converterNumberAsCharacters[0] = NULL;
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
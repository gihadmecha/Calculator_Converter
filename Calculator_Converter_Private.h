


#ifndef CALCULATOR_CONVERTER_PRIVATE_H_
#define CALCULATOR_CONVERTER_PRIVATE_H_

#include "Calculator_Converter.h"

#define		WELCOME_MESSAGE		0
#define		MAIN_LIST			1
#define		CALCULATE_SCREEN	2
#define		CONVERT_FROM_LIST	3
#define		CONVERT_TO_LIST		4
#define		DEC_TO_DEC			5
#define		DEC_TO_HEX			6
#define		DEC_TO_BIN			7
#define		HEX_TO_DEC			8
#define		HEX_TO_HEX			9
#define		HEX_TO_BIN			10
#define		BIN_TO_DEC			11
#define		BIN_TO_HEX			12
#define		BIN_TO_BIN			13

static u8 levelFlag = WELCOME_MESSAGE;

u8 convertFromListKey = NULL;

static char converterNumberAsCharacters[17] = {0};
static u8 converterNumberAsCharactersIndex = 0;
static u8 key = NULL;

static void Calculator_Converter_welcomeMessage ();
static void Calculator_Converter_mainList ();
static void Calculator_Converter_scanCalculator ();
static u8 Calculator_Converter_IsDecimal ();
static void Calculator_Converter_CalculateScreen ();
static void Calculator_Converter_convertFromList ();
static void Calculator_Converter_convertToList ();
static void Calculator_Converter_scan ();
static void Calculator_Converter_DecToDec ();
static void Calculator_Converter_DecToHex ();
static void Calculator_Converter_DecToBin ();
static void Calculator_Converter_scanHex ();
static void Calculator_Converter_HexToDec ();
static void Calculator_Converter_HexToHex ();
static void Calculator_Converter_HexToBin ();
static u8 Calculator_Converter_IsBinary ();
static void Calculator_Converter_BinToDec ();
static void Calculator_Converter_BinToHex ();
static void Calculator_Converter_BinToBin ();



#endif /* CALCULATOR_CONVERTER_PRIVATE_H_ */
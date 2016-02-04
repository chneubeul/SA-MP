/****************************************************************************************************
 *                                                                                                  *
 *                                          Bit Functions                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.4                                                                                *
 *                                                                                                  *
 * bit 0 - 31:                                                                                      *
 * (bit 31) --> 11111111000000001111010001010000 <-- (bit 0)                                        *
 *                                                                                                  *
 * Bit Functions:                                                                                   *
 * GetValueBit(value,bit);                                                                          *
 * SetValueBit(&value,bit,power);  //power 0 or 1                                                   *
 * InvertValue(value);                                                                              *
 * InvertValueEx(value,key); //default key 0xFFFFFFFF                                               *
 * bool:CheckValue(value); //even - false, uneven - true                                            *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _bit_function
	#endinput
#endif
#define _bit_function

#define GetValueBit(%0,%1)		((%0) >>> (%1) & 0x01)
#define InvertValue(%0)			((%0) ^ 0xFFFFFFFF)
#define InvertValueEx(%0,%1) 	((%0) ^ (%1))

stock bool:CheckValue(value){
	new int = 0;
	for(new i = 31; i >= 0; i--){
		if(GetValueBit(value,i)){
			int++;
		}
	}
	if(int%2 == 0) return false;
	return true;
}

stock SetValueBit(&value,bit,power){
	if((power & 0x01) == 1){
		value |= floatround(floatpower(2,bit));
	} else {
		value &= ~floatround(floatpower(2,bit));
	}
}

//EOF
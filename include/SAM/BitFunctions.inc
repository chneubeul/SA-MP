/****************************************************************************************************
 *                                                                                                  *
 *                                          Bit Functions                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.3                                                                                *
 *                                                                                                  *
 * bit 0 - 31:                                                                                      *
 * (bit 31) --> 11111111000000001111010001010000 <-- (bit 0)                                        *
 *                                                                                                  *
 * Bit Functions:                                                                                   *
 * GetValueBit(value,bit);                                                                          *
 * SetValueBit(&value,bit,power);  //power 0 or 1                                                   *
 * InvertValue(value);                                                                              *
 * InvertValueEx(value,key = 0xFFFFFFFF);                                                           *
 * bool:CheckValue(value); //even - false, uneven - true                                            *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _bit_function
	#endinput
#endif
#define _bit_function

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

stock GetValueBit(value,bit){
	if(bit < 0 || bit > 31) print("[ADM] Warring: Get bit error, the wrong bit id.");
	return (value >>> bit & 0x01);
}

stock SetValueBit(&value,bit,power){
	if(bit < 0 || bit > 31) print("[ADM] Warring: Set bit error, the wrong bit id.");
	if((power & 0x01) == 1){
		value |= floatround(floatpower(2,bit));
	} else {
		value &= ~floatround(floatpower(2,bit));
	}
}

stock InvertValue(value){
	return (value ^ 0xFFFFFFFF);
}

stock InvertValueEx(value,key = 0xFFFFFFFF){
	return (value ^ key);
}

//EOF
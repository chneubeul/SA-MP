/****************************************************************************************************
 *                                                                                                  *
 *                                          Bit Functions                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.5B                                                                               *
 *                                                                                                  *
 * bit 0 - 31:                                                                                      *
 * (bit 31) --> 11111111000000001111010001010000 <-- (bit 0)                                        *
 *                                                                                                  *
 * Bit Functions:                                                                                   *
 * GetValueBit(value, bit);                                                                         *
 * SetValueBit(&value, bit, power);  //power 0 or 1                                                 *
 * InvertValue(value);                                                                              *
 * InvertValueEx(value, key); //default key 0xFFFFFFFF                                              *
 * bool:CheckValue(value); //even - false, uneven - true                                            *
 * ExtractValue(value, &byte1, &byte2, &byte3, &byte4);                                             *
 * ExtractFloat(Float:value, &byte1, &byte2, &byte3, &byte4);                                       *
 * MergeValue(&value, byte1, byte2, byte3, byte4);                                                  *
 * MergeFloat(&Float:value, byte1, byte2, byte3, byte4);                                            *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _bit_function
	#endinput
#endif
#define _bit_function

#define GetValueBit(%0,%1)				((%0) >>> (%1) & 0x01)
#define InvertValue(%0)					((%0) ^ 0xFFFFFFFF)
#define InvertValueEx(%0,%1) 			((%0) ^ (%1))

#define ExtractValue(%0,%1,%2,%3,%4)	((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define ExtractFloat(%0,%1,%2,%3,%4)	((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define MergeValue(%0,%1,%2,%3,%4)		((%0) = (((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))
#define MergeFloat(%0,%1,%2,%3,%4)		((%0) = Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

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
	if(power){
		value |= (0x01 << bit);
	} else {
		value &= ~(0x01 << bit);
	}
}

//EOF
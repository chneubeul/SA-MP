/****************************************************************************************************
 *                                                                                                  *
 *                                          Bit Functions                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.2                                                                                *
 *                                                                                                  *
 * bit 0 - 31:                                                                                      *
 * (bit 31) --> 11111111000000001111010001010000 <-- (bit 0)                                        *
 *                                                                                                  *
 * Bit Functions:                                                                                   *
 * GetValueBit(value,bit);                                                                          *
 * SetValueBit(value,bit,power);  //power 0 or 1                                                    *
 * InvertValue(value);                                                                              *
 * InvertValueEx(value,key = 0xFFFFFFFF);                                                           *
 * bool:CheckValue(value); //even - false, uneven - true                                            *
 *                                                                                                  *
 * IF operators:                                                                                    *
 * if(AND(expression1,expression2))  // expression1 && expression2                                  *
 * if(OR(expression1,expression2))   // expression1 || expression2                                  *
 * if(NOT(expression))               // !expression1                                                *
 * if(NOR(expression1,expression2))                                                                 *
 * if(NAND(expression1,expression2))                                                                *
 * if(XOR(expression1,expression2))                                                                 *
 * if(NXOR(expression1,expression2))                                                                *
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

stock SetValueBit(value,bit,power){
	if(bit < 0 || bit > 31) print("[ADM] Warring: Set bit error, the wrong bit id.");
	new int = 0;
	power = (power & 0x01);
	for(new i = 31; i >= 0; i--){
		if(i == bit){
			if(power){
				int += floatround(floatpower(2,i));
			}
		} else {
			if(value >>> i & 0x01){
				int += floatround(floatpower(2,i));
			}
		}
	}
	return int;
}

stock InvertValue(value){
	return (value ^ 0xFFFFFFFF);
}

stock InvertValueEx(value,key = 0xFFFFFFFF){
	return (value ^ key);
}

#define AND(%1,%2)					(%1 && %2)
#define OR(%1,%2)					(%1 || %2)
#define NOT(%1)						(!%1)
#define NOR(%1,%2)					(!(%1 || %2))
#define NAND(%1,%2)					(!(%1 && %2))
#define XOR(%1,%2)					(!(%1 && %2) && (%1 || %2))
#define NXOR(%1,%2)					((%1 && %2) || !(%1 || %2))

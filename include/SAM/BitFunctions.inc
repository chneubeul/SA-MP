/****************************************************************************************************
 *                                                                                                  *
 *                                          Bit Functions                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.0                                                                                *
 *                                                                                                  *
 * bit 0 - 31:                                                                                      *
 * (bit 31) --> 11111111000000001111010001010000 <-- (bit 0)                                        *
 *                                                                                                  *
 * Bit Functions:                                                                                   *
 * GetValueBit(value,bit);                                                                          *
 * SetValueBit(value,bit,power);  //power 0 or 1                                                    *
 * InvertValue(value);                                                                              *
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

stock GetValueBit(value,bit){
	return (value >>> bit & 0x01);
}

stock SetValueBit(value,bit,power){
	new nv = 0;
	power = (power & 0x01);
	for(new i = 31; i >= 0; i--){
		if(i == bit){
			if(power){
				nv += floatround(floatpower(2, i));
			}
		} else {
			if(GetValueBit(value,i)){
				nv += floatround(floatpower(2, i));
			}
		}
	}
	return nv;
}

stock InvertValue(value){
	new nv = 0;
	for(new i = 31; i >= 0; i--){
		if(!GetValueBit(value,i)){
			nv += floatround(floatpower(2, i));
		}
	}
	return nv;
}

#define AND(%1,%2)					(%1 && %2)
#define OR(%1,%2)					(%1 || %2)
#define NOT(%1)						(!%1)
#define NOR(%1,%2)					(!(%1 || %2))
#define NAND(%1,%2)					(!(%1 && %2))
#define XOR(%1,%2)					(!(%1 && %2) && (%1 || %2))
#define NXOR(%1,%2)					((%1 && %2) || !(%1 || %2))

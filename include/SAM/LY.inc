/****************************************************************************************************
 *                                                                                                  *
 *                                       Unsigned Long 61 bit                                       *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.2                                                                                *
 *                                                                                                  *
 * Pawn Unsigned Long for 32 Bit language (precision 61-bit)                                        *
 * Available limit:                                                                                 *
 * 0 - 2 147 483 647 000 000 000                                                                    *
 * 0 - 2 000 000 000 000 000 000                                                                    *
 *                                                                                                  *
 * bool:IsValueContainLY(prefix,sufix,value);                                                       *
 * GetLYString(prefix,sufix,string[]);                                                              *
 * UpdateLY(&prefix,&sufix,value,limitprefix = DEFAULT_MAX_LY_PREFIX);                              *
 *                                                                                                  *
 ****************************************************************************************************/
 
#if defined _Long_Yoyo
	#endinput
#endif
#define _Long_Yoyo

#define MAX_LY_PREFIX	 			(2147483647)
#define DEFAULT_MAX_LY_PREFIX		(2000000000)

#if !defined strcopy
	stock strcopy(string1[],string2[]){
		for(new i = 0, j = strlen(string1); i < j; i++){
			string2[i] = string1[i];
		}
		string2[strlen(string1)] = EOS;
	}
#endif

stock bool:IsValueContainLY(prefix,sufix,value){
	if((prefix == 0) && (sufix == 0)) return false;
	if((sufix < value) && (prefix == 0)) return false;
	return true;
}

stock GetLYString(prefix,sufix,string[]){
	new buffer[20];
	if(prefix == 0){
		format(buffer,sizeof(buffer),"%d",sufix);
	} else {
		format(buffer,sizeof(buffer),"%d%09d",prefix,sufix);
	}
	strcopy(buffer,string);
}

//Unsigned Long 32 bit
stock UpdateLY(&prefix,&sufix,value,limitprefix = DEFAULT_MAX_LY_PREFIX){
	if(value == 0) return 1; //skip
	
	new tmp = value;
	
	if((tmp > 0) && (prefix >= limitprefix) && (sufix >= 0)){
		prefix = limitprefix;
		sufix = 0;
	} else if((tmp > 0) && (prefix >= limitprefix-1) && (sufix >= 999999999)){
		prefix = limitprefix;
		sufix = 0;
	} else if((tmp > 0) && (prefix >= limitprefix) && (sufix >= 999999999)){
		prefix = limitprefix;
		sufix = 0;
	} else {
		if(value >= 0){
			while(tmp >= 1000000000){
				tmp -= 1000000000;
				prefix += 1;
			}
			sufix += tmp;
			while(sufix > 999999999){
				sufix -= 1000000000;
				prefix += 1;
			}
		} else if(value < 0){
			while(tmp <= -1000000000){
				prefix -= 1;
				tmp += 1000000000;
			}
			sufix += (tmp);
			while(sufix < 0){
				sufix += 1000000000;
				prefix -= 1;
			}
			if(prefix < 0){
				prefix = 0;
				sufix = 0;
			}
		}
	}	
	if((prefix >= limitprefix) && (sufix >= 0)){
		prefix = limitprefix;
		sufix = 0;
	}
	return 1;
}


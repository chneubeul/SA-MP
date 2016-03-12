/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                       Unsigned Long 61 bit                                                                     *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * File Version: 1.4                                                                                                              *
 *                                                                                                                                *
 * Pawn Unsigned Long for 32 Bit language (precision 61-bit)                                                                      *
 * Available limit:                                                                                                               *
 * 0 - 2 147 483 647 000 000 000                                                                                                  *
 * 0 - 2 000 000 000 000 000 000                                                                                                  *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * bool:IsValueContainLY(prefix,suffix,value);                                                                                    *
 * GetLYString(prefix,suffix,string[],maxdest = sizeof(string));                                                                  *
 * UpdateLY(&prefix,&suffix,value,limitprefix = DEFAULT_MAX_LY_PREFIX);                                                           *
 * AddSeparatorLY(string[],separator[]);                                                                                          *
 * CalculatePercentLY(&prefix,&suffix,Float:percent = 0.0,increase = true,limitprefix = DEFAULT_MAX_LY_PREFIX);                   *
 *                                                                                                                                *
 **********************************************************************************************************************************/
 
#if defined _Long_Yoyo
	#endinput
#endif
#define _Long_Yoyo

#define LY_STRING_LEN					(20)
#define MAX_LY_PREFIX	 				(2147483647)
#define DEFAULT_MAX_LY_PREFIX			(2000000000)

stock bool:IsValueContainLY(prefix,suffix,value){
	if((prefix == 0) && (suffix == 0)) return false;
	if((suffix < value) && (prefix == 0)) return false;
	return true;
}

stock GetLYString(prefix,suffix,string[],maxdest = sizeof(string)){
	if(prefix == 0){
		format(string,maxdest,"%d",suffix);
	} else {
		format(string,maxdest,"%d%09d",prefix,suffix);
	}
}

//Pawn Unsigned Long for 32 Bit language (precision 61-bit)
stock UpdateLY(&prefix,&suffix,value,limitprefix = DEFAULT_MAX_LY_PREFIX){
	if(value == 0) return 1; //skip
	
	new tmp = value;
	
	if((tmp > 0) && (prefix >= limitprefix) && (suffix >= 0)){
		prefix = limitprefix;
		suffix = 0;
	} else if((tmp > 0) && (prefix >= limitprefix-1) && (suffix >= 999999999)){
		prefix = limitprefix;
		suffix = 0;
	} else if((tmp > 0) && (prefix >= limitprefix) && (suffix >= 999999999)){
		prefix = limitprefix;
		suffix = 0;
	} else {
		if(value >= 0){
			while(tmp >= 1000000000){
				tmp -= 1000000000;
				prefix += 1;
			}
			suffix += tmp;
			while(suffix > 999999999){
				suffix -= 1000000000;
				prefix += 1;
			}
		} else if(value < 0){
			while(tmp <= -1000000000){
				prefix -= 1;
				tmp += 1000000000;
			}
			suffix += (tmp);
			while(suffix < 0){
				suffix += 1000000000;
				prefix -= 1;
			}
			if(prefix < 0){
				prefix = 0;
				suffix = 0;
			}
		}
	}	
	if((prefix >= limitprefix) && (suffix >= 0)){
		prefix = limitprefix;
		suffix = 0;
	}
	return 1;
}

stock AddSeparatorLY(string[],separator[]){ 
	new tStr[32];
	format(tStr,sizeof(tStr),"%s",string); 

	if(strlen(tStr) < 4) return tStr; 
	new iPos = strlen(tStr), iCount = 1; 

	while(iPos > 0){ 
		if(iCount == 4){ 
			iCount = 0; 
			strins(tStr,separator,iPos,1); 
			iPos++; 
		}
		iCount++; 
		iPos--; 
	} 
	return tStr; 
}  

stock CalculatePercentLY(&prefix,&suffix,Float:percent = 0.0,bool:increase = true,limitprefix = DEFAULT_MAX_LY_PREFIX){
	new Float:lycut = (prefix*(percent/100.0)),
		modify_p = floatround(lycut,floatround_round),
		modify_s = floatround((lycut-modify_p)*100) * 10000000;
	
	if(increase){
		prefix += modify_p;
		UpdateLY(prefix,suffix,modify_s,limitprefix);
		modify_s = floatround(suffix*(percent/100.0));
		UpdateLY(prefix,suffix,modify_s,limitprefix);
	} else {
		prefix -= modify_p;
		UpdateLY(prefix,suffix,-modify_s,limitprefix);
		modify_s = floatround(suffix*(percent/100.0));
		UpdateLY(prefix,suffix,-modify_s,limitprefix);
	}
}


//EOF
/****************************************************************************************************
 *                                                                                                  *
 *                                           Data Convert                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.1                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * GetFileID(File:handle);                                                                          *
 * BinToInt(string[]);                                                                              *
 * BoolToInt(bool:boolean);                                                                         *
 * HexToInt(string[]);                                                                              * 
 * StringToInt(string[]);                                                                           *
 * bool:StringToBool(string[]);                                                                     *
 * strcopy(string1[],string2[]);                                                                    *
 * IntToHex(int);                                                                                   *
 *                                                                                                  *
 ****************************************************************************************************/

#define StringToInt(%0)		strval(%0)
 
stock GetFileID(File:handle){
	return (_:handle);
}

stock BinToInt(string[]){
	if(strlen(string) == 0) return -1;
	new int = 0;
	for(new i = strlen(string)-1, j = i; i >= 0; i--){
		if(string[i] == '1'){
			int += floatround(floatpower(2,j-i));
		}
	}
	return int;
}

stock BoolToInt(bool:boolean){
	if(boolean){
		return 1;
	} else {
		return 0;
	}
}

stock bool:StringToBool(string[]){
	if(string[0] == '0'){
		return false;
	} else {
		return true;
	}
}

stock strcopy(string1[],string2[]){
	for(new i = 0, j = strlen(string1); i < j; i++){
		string2[i] = string1[i];
	}
	string2[strlen(string1)] = EOS;
}

stock HexToInt(string[]){
	if(string[0] == 0) return 0;
	new cur = 1, res = 0;
	for(new i = strlen(string)-1; i >= 0; i--){
		if(string[i] < 58){
			res = res + cur * (string[i] - 48);
		} else {
			res = res + cur * (string[i] - 55);
		}
		cur = cur * 16;
	}
	return res;
}

stock IntToHex(int){
	new buffer[8], i = 0, result[8], g = 0;
	while(int > 0){
		new tmp = int % 16;

		if(tmp < 10){
			buffer[i] = tmp + 48;
		} else {
			buffer[i] = tmp + 55;
		}
		i++;
		int = int / 16;
	}
	for(i = strlen(buffer)-1; i >= 0; i--){
		result[g++] = buffer[i];
	}
	while(strlen(result) < 6){
		strins(result, "0", 0);
	}
	return result;
}

//EOF
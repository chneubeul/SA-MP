/****************************************************************************************************
 *                                                                                                  *
 *                                           Data Convert                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.2                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * GetFileHandleID(File:handle);                                                                    *
 * GetFileID(File:handle);                                                                          *
 * BinToInt(string[]);                                                                              *
 * BoolToInt(bool:boolean);                                                                         *
 * HexToInt(string[]);                                                                              * 
 * StringToInt(string[]);                                                                           *
 * bool:StringToBool(string[]);                                                                     *
 * strcopy(input[], output[], maxlength = sizeof(output));                                          *
 * IntToHex(int);                                                                                   *
 *                                                                                                  *
 ****************************************************************************************************/

#define FIRST_FILE_ADDRESS			(0x004E5A18)
#define INVALID_FILE_ID				(0xFFB1A5E7)
#define INVALID_FILE_HANDLE			(File:0)
#define GetFileHandleID(%0)			(_:%0)
#define StringToInt(%0)				strval(%0)

stock GetFileID(File:handle){
	if(handle == INVALID_FILE_HANDLE){
		return INVALID_FILE_ID;
	} else {
		return ((GetFileHandleID(handle)-FIRST_FILE_ADDRESS)/32);
	}
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

stock strcopy(input[], output[], maxlength = sizeof(output)){
	output[0] = 0;
	strcat(output,input,maxlength);
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
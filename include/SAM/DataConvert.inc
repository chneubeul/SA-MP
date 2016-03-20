/****************************************************************************************************
 *                                                                                                  *
 *                                           Data Convert                                           *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * File Version: 1.3                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * GetFileHandleID(File:handle);                                                                    *
 * GetFileID(File:handle);                                                                          *
 * BinToInt(string[]);                                                                              *
 * BoolToInt(bool:boolean);                                                                         *
 * HexToInt(string[]);                                                                              * 
 * StringToInt(string[]);                                                                           *
 * bool:StringToBool(string[]);                                                                     *
 * strcopy(input[],output[]);  //string copy for warning 224: indeterminate array size              *
 * fstrcopy(input[],output[],maxdest = sizeof(output));   //fast string copy                        *
 * IntToHex(int);                                                                                   *
 * ABCToCBA(input[],output[]);                                                                      *
 * AnyToInt(str[],type,&bool:flag);                                                                 *
 * IntToAny(value,output[],type);                                                                   *
 * rot13(string[]);                                                                                 *
 * code128(input[],output[]);                                                                       *
 *                                                                                                  *
 ****************************************************************************************************/
 
#if defined _Data_Convert
	#endinput
#endif
#define _Data_Convert

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

stock strcopy(input[],output[]){
	for(new i = 0, j = strlen(input); i < j; i++){
		output[i] = input[i];
	}
	output[strlen(input)] = EOS;
}

stock fstrcopy(input[], output[], maxdest = sizeof(output)){
	output[0] = EOS;
	strcat(output,input);
	output[strlen(input)] = EOS;
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


stock ABCToCBA(input[], output[]){
	for(new i = 0, j = strlen(input); i < j; i++){
		output[j-(i+1)] = input[i];
	}
	output[strlen(input)] = EOS;
}

stock AnyToInt(str[], type, &bool:flag){
	new k, n = strlen(str), i = 1, val;
	if(str[0] >= 0x30 && str[0] <= 0x39){
		val = str[0] - 48;
	} else {
		val = str[0] - 55;
	}
	if(val >= type){
		flag = false;
		return 0;
	}
	
	while(i < n){
		if(str[i] >= 0x30 && str[i] <= 0x39){
	    	k = str[i] - 48;
		} else {
			k = str[i] - 55;
		}
		if(k >= type){
			flag = false;
			return 0;
		}
		val = val * type + k;
		i++;
	}
	flag = true;
	return val;
}

stock IntToAny(value, output[], type){
	new tmp = value, val[256], i = 0;
	while(tmp > 1){
		val[i] = (tmp % type);
		if(val[i] < 10){
			val[i] += 0x30;
		} else {
			val[i] += 0x37;
		}
		tmp = tmp / type;
		i++;
	}
	val[i] = EOS;
	ABCToCBA(val,output);
}

stock rot13(string[]){
	for(new i = 0, j = strlen(string); i < j; i++){
		if('a' <= string[i] <= 'z'){
			string[i] = (string[i] - 'a' + 13) % 26 + 'a';
		} else if('A' <= string[i] <= 'Z'){
			string[i] = (string[i] - 'A' + 13) % 26 + 'A';
		}
	}
}

stock code128(input[],output[]){
	for(new i = 0, j = strlen(input); i < j; i++){
		output[i] = (0xFF & input[i]+128);
	}
	output[strlen(input)] = EOS;
}

//EOF
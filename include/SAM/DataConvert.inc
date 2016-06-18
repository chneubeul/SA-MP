/****************************************************************************************************
 *                                                                                                  *
 *                                           Data Convert                                           *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * File Version: 1.7                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * GetFileHandleID(File:handle);                                                                    *
 * GetFileID(File:handle);                                                                          *
 * bool:IsIdentical({AllTag,_}:variable1,{AllTag,_}:variable2);                                     *
 * BoolToInt(bool:boolean);                                                                         *
 * bool:IntToBool(value);                                                                           *
 * bool:StringToBool(string[]);                                                                     *
 * StringToInt(string[]);                                                                           *
 * BinToInt(string[]);                                                                              *
 * IntToBin(value);                                                                                 *
 * HexToInt(string[]);                                                                              *
 * IntToHex(int);                                                                                   *
 * IntToHexEx(int);                                                                                 *
 * HexToBin(string[]);                                                                              *
 * BinToHex(string[]);                                                                              *
 * BinToHexEx(string[]);                                                                            *
 * strcopy(input[],output[]);  //string copy for warning 224: indeterminate array size              *
 * fstrcopy(input[],output[],maxdest = sizeof(output));   //fast string copy                        *
 * ABCToCBA(input[],output[]);                                                                      *
 * AnyToInt(str[],type,&bool:flag);                                                                 *
 * IntToAny(value,output[],type);                                                                   *
 * rot13(string[]);                                                                                 *
 * code128(input[],output[]);                                                                       *
 * swap_int({Float,_}:int1,{Float,_}:int2);                                                         *
 * swap_string(string1[], string2[], dest1 = sizeof(string1), dest2 = sizeof(string2));             *
 * FloatToInt(Float:value); //Convert Float binary data to Integer binary data                      *
 * Float:IntToFloat(value); //Convert Integer binary data to Float binary data                      *
 *                                                                                                  *
 ****************************************************************************************************/

/*
//Check Version DataConvert.inc
#if !defined _Data_Convert
	#error You need DataConvert.inc v1.7
#elseif !defined Data_Convert_Version
	#error Update you DataConvert.inc to v1.7
#elseif (Data_Convert_Version < 10701)
	#error Update you DataConvert.inc to v1.7
#endif
*/

#if !defined sscanf
	#error Unknown sscanf version
#endif

#if defined _Data_Convert
	#endinput
#endif
#define _Data_Convert

#define Data_Convert_Version		(10701) //a.b[c] 10000*a+100*b+c

#define FIRST_FILE_ADDRESS			(0x004E5A18)
#define INVALID_FILE_ID				(0xFFB1A5E7)
#define INVALID_FILE_HANDLE			(File:0)
#define GetFileHandleID(%0)			(_:%0)
#define StringToInt(%0)				strval(%0)

#define IsIdentical(%0,%1)			((tagof(%0) == tagof(%1)) && (_:%0) == (_:%1))

//swapvars by Crayder
#define swap_int(%0,%1)				(((%0) ^= (%1)), ((%1) ^= (%0)), ((%0) ^= (%1)))

#define BoolToInt(%0)				((%0)?1:0)
#define IntToBool(%0)				((%0 == 1)?true:false)

#define FloatToInt(%0)				(_:%0)
#define IntToFloat(%0)				(Float:%0)

stock bool:swap_string(string1[], string2[], dest1 = sizeof(string1), dest2 = sizeof(string2)){
	if(dest1 < strlen(string2) || dest2 < strlen(string1)) return false;
	new swap_size = dest1;
	if(dest2 > swap_size) swap_size = dest2;
	for(new i = 0; i < swap_size; i++){
		swap_int(string1[i],string2[i]);
	}
	return true;
}

stock GetFileID(File:handle){
	if(handle == INVALID_FILE_HANDLE){
		return INVALID_FILE_ID;
	} else {
		return ((GetFileHandleID(handle)-FIRST_FILE_ADDRESS)/32);
	}
}

stock BinToInt(string[]){
	new int = 0;
	sscanf(string","b",int);
	return int;
}

stock HexToBin(string[]){
	new str[34], value = 0;
	sscanf(string,"x",value);
	format(str,sizeof(str),"%b",value);
	return str;
}

stock BinToHex(string[]){
	new str[10], value = 0;
	sscanf(string,"b",value);
	format(str,sizeof(str),"%06x",value);
	return str;
}

stock BinToHexEx(string[]){
	new str[10], value = 0;
	sscanf(string,"b",value);
	format(str,sizeof(str),"%x",value);
	return str;
}

stock IntToBin(value){
	new string[34];
	format(string,sizeof(string),"%b",value);
	return string;
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
	new int = 0;
	sscanf(string,"x",int);
	return int;
}

stock IntToHex(int){
	new result[10];
	format(result,sizeof(result),"%06x",int);
	return result;
}

stock IntToHexEx(int){
	new result[10];
	format(result,sizeof(result),"%x",int);
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
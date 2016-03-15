/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                      ADM Encryption File                                                       *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * File Version: 1.8C                                                                                                             *
 *                                                                                                                                *
 * File Functions:                                                                                                                *
 * InvertFile(const char* input, const char* output);                                                                             *
 * HexNegativeFile(const char* input, const char* output, char* key);                                                             *
 * RollXFile(const char* input, const char* output, char* key);                                                                   *
 * ADMx32(const char* input, const char* output, char* key);                                                                      *
 * ADMx64(const char* input, const char* output, char* key);                                                                      *
 * ADMx128(const char* input, const char* output, char* key);                                                                     *
 * ADMx256(const char* input, const char* output, char* key);                                                                     *
 * ADMx512(const char* input, const char* output, char* password, bool invertpassword = false);                                   *
 *                                                                                                                                *
 * String Functions:                                                                                                              *
 * InvertString(char* input, char* output, int maxdest);                                                                          *
 * HexNegativeString(char* input, char* output, char* key, int maxdest);                                                          *
 * RollXString(char* input, char* output, char* key, int maxdest);                                                                *
 * ADMx32String(char* input, char* output, char* key, int maxdest);                                                               *
 * ADMx64String(char* input, char* output, char* key, int maxdest);                                                               *
 * ADMx128String(char* input, char* output, char* key, int maxdest);                                                              *
 * ADMx256String(char* input, char* output, char* key, int maxdest);                                                              *
 * ADMx512String(char* input, char* output, char* password, bool invertpassword, int maxdest);                                    *
 *                                                                                                                                *
 * Other Functions:                                                                                                               *
 * IsValidADMKey(char* key, int type);                                                                                            *
 * GetADMKeyType(char* key, bool distorted = false);                                                                              *
 * DecodeADMKey(char* inputkey, char* outputkey, int type, int maxdest);                                                          *
 * CreateADMKey(char* key, int type, int maxdest);                                                                                *
 * StringToHexString(char* input, char* output, int maxdest);                                                                     *
 * HexStringToString(char* input, char* output, int maxdest);                                                                     *
 *                                                                                                                                *
 * Return value:                                                                                                                  *
 * ERROR_CODE_ADM_UNEXEC       //function unexecutable                                                                            *
 * ERROR_CODE_ADM_OK           //success                                                                                          *
 * ERROR_CODE_ADM_INPUT        //input file not exist                                                                             *
 * ERROR_CODE_ADM_OUTPUT       //output file exist                                                                                *
 * ERROR_CODE_ADM_KEY          //invalid key                                                                                      *
 * ERROR_CODE_ADM_SIZE         //invalid file size                                                                                *
 * ERROR_CODE_ADM_DEST         //error destination size                                                                           *
 * ERROR_CODE_ADM_OPEN_INPUT   //error open input file                                                                            *
 * ERROR_CODE_ADM_OPEN_OUTPUT  //error open output file                                                                           * 
 * ERROR_CODE_ADM_INVALID_TYPE //invalid key type                                                                                 *
 * ERROR_CODE_ADM_PASSWORD     //invalid password length                                                                          *
 * ERROR_CODE_ADM_MD5          //invalid MD5 Load                                                                                 *
 *                                                                                                                                *
 * Key Generator:                                                                                                                 *
 * http://ngc.ugu.pl/admkg                                                                                                        *
 * http://ngc.porobieni.com/admkg/                                                                                                *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
#define _LARGEFILE_SOURCE		1
#define _LARGEFILE64_SOURCE		1
#define _FILE_OFFSET_BITS		64
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include "md5.cpp"
#include <ctime>

using namespace std;
*/

#if defined _adm_encryption
	#endinput
#endif
#define _adm_encryption

#define ADM_Encryption_Version 		(10803) //a.b[c] 10000*a+100*b+c

#define MAX_FILE_SIZE				(18446744073709551615ULL)	//~16 EB

#define KEY_TYPE_UNKNOWN			(0)
#define KEY_TYPE_HEXNEGATIVE		(4)
#define KEY_TYPE_ROLLX				(8)
#define KEY_TYPE_ADMx32				(32)
#define KEY_TYPE_ADMx64				(64)
#define KEY_TYPE_ADMx128			(128)
#define KEY_TYPE_ADMx256			(256)

#define MAX_MODE_ADMx32				(4)
#define MAX_MODE_ADMx64				(8)
#define MAX_MODE_ADMx128			(16)
#define MAX_MODE_ADMx256			(32)
#define MAX_MODE_ADMx512			(64)

#define MAX_KEY_LEN_HEXNEGATIVE		(4)
#define MAX_KEY_LEN_ROLLX			(4)
#define MAX_KEY_LEN_ADMx32			(16)
#define MAX_KEY_LEN_ADMx64			(32)
#define MAX_KEY_LEN_ADMx128			(64)
#define MAX_KEY_LEN_ADMx256			(128)
#define MAX_KEY_LEN_ADMx512			(36)

#define MAX_LEN_BINARY_ADMx512		(20)

#define ERROR_CODE_ADM_UNEXEC		(0)			//function unexecutable
#define ERROR_CODE_ADM_OK			(1)			//success
#define ERROR_CODE_ADM_INPUT		(-1)		//input file not exist
#define ERROR_CODE_ADM_OUTPUT		(-2)		//output file exist
#define ERROR_CODE_ADM_KEY			(-3)		//invalid key
#define ERROR_CODE_ADM_SIZE			(-4)		//invalid file size
#define ERROR_CODE_ADM_DEST			(-5)		//error destination size
#define ERROR_CODE_ADM_OPEN_INPUT	(-6)		//error open input file
#define ERROR_CODE_ADM_OPEN_OUTPUT	(-7)		//error open output file
#define ERROR_CODE_ADM_INVALID_TYPE	(-8)		//invalid key type
#define ERROR_CODE_ADM_PASSWORD		(-9)		//invalid password len
#define ERROR_CODE_ADM_MD5			(-10)		//invalid MD5 Load

bool fexist(const char *fileName){
	ifstream infile(fileName);
	return infile.good();
}

std::ifstream::pos_type filesize(const char* filename){
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg(); 
}

char* StrToChar(string str, char* tmp){
	int size = str.length();
	for(int i = 0; i < size; i++){
		tmp[i] = str[i];
	}
	tmp[size] = '\0';
}

char* UpperCase(char* str){
    for(int i = 0, j = strlen(str); i < j; i++){
        if(str[i] >= 97 && str[i] <= 122){
            //na duze
            str[i] = str[i] - 32;
        }
    }
}

int random(int max){
	return rand()%max;
}

/********************
 * Other Functions  *
 ********************/

bool IsValidADMKey(char* key, int type){
	switch(type){
	
		case KEY_TYPE_HEXNEGATIVE: {
			int mode;
			sscanf(key,"%d",&mode);
			if(mode < 1 || mode > 15){
				return false;
			}
			break;
		}
		
		case KEY_TYPE_ROLLX: {
			int mode;
			sscanf(key,"%d",&mode);
			if(mode < 1 || mode > 255){
				return false;
			}
			break;
		}

		case KEY_TYPE_ADMx32: {
			int mode[MAX_MODE_ADMx32];
			sscanf(key,"%d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3]
			);
			for(int i = 0; i < MAX_MODE_ADMx32; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx64: {
			int mode[MAX_MODE_ADMx64];
			sscanf(key,"%d %d %d %d %d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7]
			);
			for(int i = 0; i < MAX_MODE_ADMx64; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx128: {
			int mode[MAX_MODE_ADMx128];
			sscanf(key,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
				&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15]
			);
			for(int i = 0; i < MAX_MODE_ADMx128; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx256: {
			int mode[MAX_MODE_ADMx256];
			sscanf(key,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
				&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15],
				&mode[16],&mode[17],&mode[18],&mode[19],&mode[20],&mode[21],&mode[22],&mode[23],
				&mode[24],&mode[25],&mode[26],&mode[27],&mode[28],&mode[29],&mode[30],&mode[31]
			);
			for(int i = 0; i < MAX_MODE_ADMx256; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}
			break;
		}

		default: return false;
	}
	return true;
}

int GetADMKeyType(char* key, bool distorted = false){
	int mode[MAX_MODE_ADMx256], cnt = 0;
	sscanf(key,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
		&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15],
		&mode[16],&mode[17],&mode[18],&mode[19],&mode[20],&mode[21],&mode[22],&mode[23],
		&mode[24],&mode[25],&mode[26],&mode[27],&mode[28],&mode[29],&mode[30],&mode[31]
	);
	for(int i = 0; i < MAX_MODE_ADMx256; i++){
		if(mode[i] >= 1 && mode[i] <= 255){
			cnt++;
		}
	}
	switch(cnt){
		case 1: {
			if(mode[0] >= 1 && mode[0] <= 15){
				return KEY_TYPE_HEXNEGATIVE;
			}
			if(mode[0] >= 1 && mode[0] <= 255){
				return KEY_TYPE_ROLLX;
			}
		}
		
		case MAX_MODE_ADMx32:  return KEY_TYPE_ADMx32;
		case MAX_MODE_ADMx64:  return KEY_TYPE_ADMx64;
		case MAX_MODE_ADMx128: return KEY_TYPE_ADMx128;
		case MAX_MODE_ADMx256: return KEY_TYPE_ADMx256;
	}
	if(distorted){
		return (cnt*8); //returns the number of key bits
	} else {
		return KEY_TYPE_UNKNOWN;
	}
}

int DecodeADMKey(char* inputkey, char* outputkey, int type, int maxdest){
	switch(type){
		
		case KEY_TYPE_HEXNEGATIVE: {
			if(maxdest < MAX_KEY_LEN_HEXNEGATIVE) return ERROR_CODE_ADM_DEST;
			int mode;
			sscanf(inputkey,"%d",&mode);
			if(mode < 1 || mode > 15){
				outputkey[0] = '\0';
				return ERROR_CODE_ADM_KEY;
			} else {
				snprintf(outputkey,maxdest,"%d",(0xF & (16-mode)));
			}
			break;
		}
		
		case KEY_TYPE_ROLLX: {
			if(maxdest < MAX_KEY_LEN_ROLLX) return ERROR_CODE_ADM_DEST;
			int mode;
			sscanf(inputkey,"%d",&mode);
			if(mode < 1 || mode > 255){
				outputkey[0] = '\0';
				return ERROR_CODE_ADM_KEY;
			} else {
				snprintf(outputkey,maxdest,"%d",(0xFF & (256-mode)));
			}
			break;
		}
		
		case KEY_TYPE_ADMx32: {
			if(maxdest < MAX_KEY_LEN_ADMx32) return ERROR_CODE_ADM_DEST;
			int mode[MAX_MODE_ADMx32];
			sscanf(inputkey,"%d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3]
			);
			for(int i = 0; i < MAX_MODE_ADMx32; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = '\0';
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						snprintf(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						snprintf(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx64: {
			if(maxdest < MAX_KEY_LEN_ADMx64) return ERROR_CODE_ADM_DEST;
			int mode[MAX_MODE_ADMx64];
			sscanf(inputkey,"%d %d %d %d %d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7]
			);
			for(int i = 0; i < MAX_MODE_ADMx64; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = '\0';
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						snprintf(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						snprintf(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx128: {
			if(maxdest < MAX_KEY_LEN_ADMx128) return ERROR_CODE_ADM_DEST;
			int mode[MAX_MODE_ADMx128];
			sscanf(inputkey,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
				&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15]
			);
			for(int i = 0; i < MAX_MODE_ADMx128; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = '\0';
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						snprintf(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						snprintf(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx256: {
			if(maxdest < MAX_KEY_LEN_ADMx256) return ERROR_CODE_ADM_DEST;
			int mode[MAX_MODE_ADMx256];
			sscanf(inputkey,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
				&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15],
				&mode[16],&mode[17],&mode[18],&mode[19],&mode[20],&mode[21],&mode[22],&mode[23],
				&mode[24],&mode[25],&mode[26],&mode[27],&mode[28],&mode[29],&mode[30],&mode[31]
			);
			for(int i = 0; i < MAX_MODE_ADMx256; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = '\0';
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						snprintf(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						snprintf(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}
			break;
		}

		default: return ERROR_CODE_ADM_INVALID_TYPE;
	}
	return ERROR_CODE_ADM_OK;
}

int CreateADMKey(char* key, int type, int maxdest){
	switch(type){
	
		case KEY_TYPE_HEXNEGATIVE: {
			if(maxdest < MAX_KEY_LEN_HEXNEGATIVE) return ERROR_CODE_ADM_DEST;
			snprintf(key,maxdest,"%d",random(15)+1);
			break;
		}
		
		case KEY_TYPE_ROLLX: {
			if(maxdest < MAX_KEY_LEN_ROLLX) return ERROR_CODE_ADM_DEST;
			snprintf(key,maxdest,"%d",random(255)+1);
			break;
		}
		
		case KEY_TYPE_ADMx32: {
			if(maxdest < MAX_KEY_LEN_ADMx32) return ERROR_CODE_ADM_DEST;
			for(int i = 0; i < MAX_MODE_ADMx32; i++){
				if(i == 0){
					snprintf(key,maxdest,"%d",random(255)+1);
				} else {
					snprintf(key,maxdest,"%s %d",key,random(255)+1);
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx64: {
			if(maxdest < MAX_KEY_LEN_ADMx64) return ERROR_CODE_ADM_DEST;
			for(int i = 0; i < MAX_MODE_ADMx64; i++){
				if(i == 0){
					snprintf(key,maxdest,"%d",random(255)+1);
				} else {
					snprintf(key,maxdest,"%s %d",key,random(255)+1);
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx128: {
			if(maxdest < MAX_KEY_LEN_ADMx128) return ERROR_CODE_ADM_DEST;
			for(int i = 0; i < MAX_MODE_ADMx128; i++){
				if(i == 0){
					snprintf(key,maxdest,"%d",random(255)+1);
				} else {
					snprintf(key,maxdest,"%s %d",key,random(255)+1);
				}
			}
			break;
		}
		
		case KEY_TYPE_ADMx256: {
			if(maxdest < MAX_KEY_LEN_ADMx256) return ERROR_CODE_ADM_DEST;
			for(int i = 0; i < MAX_MODE_ADMx256; i++){
				if(i == 0){
					snprintf(key,maxdest,"%d",random(255)+1);
				} else {
					snprintf(key,maxdest,"%s %d",key,random(255)+1);
				}
			}
			break;
		}

		default: return ERROR_CODE_ADM_INVALID_TYPE;
	}
	return ERROR_CODE_ADM_OK;
}

int StringToHexString(char* input, char* output, int maxdest){
	int asize = strlen(input), idx = 0, offset = 0;
	if((asize*2) > maxdest) return ERROR_CODE_ADM_DEST;
	while(idx < asize){
		output[offset] = (0xF & (input[idx] >> 4));
		if(output[offset] < 10){
			output[offset] += 48;
		} else {
			output[offset] += 55;
		}
		output[offset+1] = (0xF & input[idx]);
		if(output[offset+1] < 10){
			output[offset+1] += 48;
		} else {
			output[offset+1] += 55;
		}
		idx++;
		offset += 2;
	}
	output[asize*2] = '\0';
	return ERROR_CODE_ADM_OK;
}

int HexStringToString(char* input, char* output, int maxdest){
	int asize = (strlen(input)/2), idx = 0, offset = 0, unit[2];
	if(asize > maxdest) return ERROR_CODE_ADM_DEST;
	while(idx < asize){
		if(input[offset] >= 97){
			unit[0] = (input[offset]-87);
		} else if(input[offset] < 58){
			unit[0] = (input[offset]-48);
		} else {
			unit[0] = (input[offset]-55);
		}
		if(input[offset+1] >= 97){
			unit[1] = (input[offset+1]-87);
		} else if(input[offset+1] < 58){
			unit[1] = (input[offset+1]-48);
		} else {
			unit[1] = (input[offset+1]-55);
		}
		output[idx] = (unit[0]*16)+unit[1];
		idx++;
		offset += 2;
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

/********************
 * File Functions   *
 ********************/

int InvertFile(const char* input, const char* output){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;
	
	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = (buffer ^ 0xFF);
		outputfile << buffer;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();	
	return ERROR_CODE_ADM_OK;
}

int HexNegativeFile(const char* input, const char* output, char* key){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	int mode;
	sscanf(key,"%d",&mode);
	if(mode < 1 || mode > 15) return ERROR_CODE_ADM_KEY;
	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = (((0xF & ((buffer >> 4)+mode))*16) + (0xF & ((buffer & 0xF)+mode)));
		outputfile << buffer;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();
	return ERROR_CODE_ADM_OK;
}

int RollXFile(const char* input, const char* output, char* key){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	int mode;
	sscanf(key,"%d",&mode);
	if(mode < 1 || mode > 255) return ERROR_CODE_ADM_KEY;
	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = ((buffer+mode) & 0xFF);
		outputfile << buffer;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();
	return ERROR_CODE_ADM_OK;
}

int ADMx32(const char* input, const char* output, char* key){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	int mode[MAX_MODE_ADMx32];
	sscanf(key,"%d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3]
	);
	for(int i = 0; i < MAX_MODE_ADMx32; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	int s = 0;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = ((buffer+mode[s]) & 0xFF);
		outputfile << buffer;
		s++;
		if(s >= MAX_MODE_ADMx32) s = 0;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();
	return ERROR_CODE_ADM_OK;
}

int ADMx64(const char* input, const char* output, char* key){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	int mode[MAX_MODE_ADMx64];
	sscanf(key,"%d %d %d %d %d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7]
	);
	for(int i = 0; i < MAX_MODE_ADMx64; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	int s = 0;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = ((buffer+mode[s]) & 0xFF);
		outputfile << buffer;
		s++;
		if(s >= MAX_MODE_ADMx64) s = 0;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();
	return ERROR_CODE_ADM_OK;
}

int ADMx128(const char* input, const char* output, char* key){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	int mode[MAX_MODE_ADMx128];
	sscanf(key,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
		&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15]
	);
	for(int i = 0; i < MAX_MODE_ADMx128; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	int s = 0;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = ((buffer+mode[s]) & 0xFF);
		outputfile << buffer;
		s++;
		if(s >= MAX_MODE_ADMx128) s = 0;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();
	return ERROR_CODE_ADM_OK;
}


int ADMx256(const char* input, const char* output, char* key){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	int mode[MAX_MODE_ADMx256];
	sscanf(key,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
		&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15],
		&mode[16],&mode[17],&mode[18],&mode[19],&mode[20],&mode[21],&mode[22],&mode[23],
		&mode[24],&mode[25],&mode[26],&mode[27],&mode[28],&mode[29],&mode[30],&mode[31]
	);
	for(int i = 0; i < MAX_MODE_ADMx256; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	int s = 0;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = ((buffer+mode[s]) & 0xFF);
		outputfile << buffer;
		s++;
		if(s >= MAX_MODE_ADMx256) s = 0;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();
	return ERROR_CODE_ADM_OK;
}

int ADMx512(const char* input, const char* output, char* password, bool invertpassword = false){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	
	int psize = strlen(password);
	if(psize < 1 || psize > 255) return ERROR_CODE_ADM_PASSWORD;
	
	int	mode[MAX_MODE_ADMx512],
		BinKeyAlfa[MAX_LEN_BINARY_ADMx512],
		BinKeyBeta[MAX_LEN_BINARY_ADMx512],
		BinKeyGamma[MAX_LEN_BINARY_ADMx512],
		BinKeyDelta[MAX_LEN_BINARY_ADMx512];

	char hash[MAX_KEY_LEN_ADMx512],
		 tmpkey[MAX_LEN_BINARY_ADMx512];
	
	
	//Create Bin Key Alfa
	stringstream ss;
	string pass;
	ss << password;
	ss >> pass;
	
	pass = md5(pass);
	
	StrToChar(pass,hash);
	UpperCase(hash);
	HexStringToString(hash,tmpkey,sizeof(tmpkey));
	
	for(int i = 0, j = strlen(tmpkey); i < j; i++){
		BinKeyAlfa[i] = (0xFF & (tmpkey[i]+256));
	}
	
	//Create Bin Key Beta	
	for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
		BinKeyBeta[i] = (BinKeyAlfa[i] ^ 0xFF);
	}
	
	//Create Bin Key Gamma
	for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
		BinKeyGamma[i] = (((0xF & ((BinKeyAlfa[i] >> 4)+8))*16) + (0xF & ((BinKeyAlfa[i] & 0xF)+8)));
	}

	//Create Bin Key Delta
	for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
		BinKeyDelta[i] = (((0xF & ((BinKeyBeta[i] >> 4)+8))*16) + (0xF & ((BinKeyBeta[i] & 0xF)+8)));
	}

	//Decode password
	if(invertpassword){
		for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
			BinKeyAlfa[i] = (0xFF & (256-BinKeyAlfa[i]));
			BinKeyBeta[i] = (0xFF & (256-BinKeyBeta[i]));
			BinKeyGamma[i] = (0xFF & (256-BinKeyGamma[i]));
			BinKeyDelta[i] = (0xFF & (256-BinKeyDelta[i]));
		}
	}
	
	//Allocate key address
	int tid = 0;
	for(int i = 0; i < MAX_MODE_ADMx512; i++){
		switch(i % 8){
			case 0: mode[i] = BinKeyAlfa[tid]; break;
			case 1: mode[i] = BinKeyGamma[tid]; break;
			case 2: mode[i] = BinKeyBeta[tid]; break;
			case 3: mode[i] = BinKeyDelta[tid]; break;
			case 4: mode[i] = BinKeyGamma[tid]; break;
			case 5: mode[i] = BinKeyBeta[tid]; break;
			case 6: mode[i] = BinKeyAlfa[tid]; break;
			case 7: mode[i] = BinKeyDelta[tid]; break;
		}
		if((i+1) % 8 == 0) tid++;
	}

	unsigned long long int asize;
	asize = filesize(input);
	if(asize > MAX_FILE_SIZE) return ERROR_CODE_ADM_SIZE;
	ifstream inputfile;
	ofstream outputfile;

	inputfile.open(input, ios::binary);
	outputfile.open(output, ios::binary);
	if(!inputfile.is_open()) return ERROR_CODE_ADM_OPEN_INPUT;
	if(!outputfile.is_open()){
		inputfile.close();
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	
	unsigned long long int i = 0ULL;
	int s = 0;
	while(i < asize && inputfile.good()){
		char buffer;
		inputfile.get(buffer);
		buffer = ((buffer+mode[s]) & 0xFF);
		outputfile << buffer;
		s++;
		if(s >= MAX_MODE_ADMx512) s = 0;
		i += 1ULL;
	}
	inputfile.close();
	outputfile.close();
	return ERROR_CODE_ADM_OK;
}

/********************
 * String Functions *
 ********************/

int InvertString(char* input, char* output, int maxdest){
	int asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	while(idx < asize){
		output[idx] = (input[idx] ^ 0xFF);
		idx++;
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

int HexNegativeString(char* input, char* output, char* key, int maxdest){
	int mode;
	sscanf(key,"%d",&mode);
	if(mode < 1 || mode > 15) return ERROR_CODE_ADM_KEY;
	int asize = strlen(input);
	if(asize > maxdest) return ERROR_CODE_ADM_DEST;
	for(int i = 0; i < asize; i++){
		output[i] = (((0xF & ((input[i] >> 4)+mode))*16) + (0xF & ((input[i] & 0xF)+mode)));
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

int RollXString(char* input, char* output, char* key, int maxdest){
	int mode;
	sscanf(key,"%d",&mode);
	if(mode < 1 || mode > 255) return ERROR_CODE_ADM_KEY;
	int asize = strlen(input);
	if(asize > maxdest) return ERROR_CODE_ADM_DEST;
	for(int i = 0; i < asize; i++){
		output[i] = (0xFF & (input[i]+mode));
	}
	output[strlen(input)] = '\0';
	return ERROR_CODE_ADM_OK;
}

int ADMx32String(char* input, char* output, char* key, int maxdest){
	int asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	int mode[MAX_MODE_ADMx32];
	sscanf(key,"%d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3]
	);
	for(int i = 0; i < MAX_MODE_ADMx32; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	int s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx32) s = 0;
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

int ADMx64String(char* input, char* output, char* key, int maxdest){
	int asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	int mode[MAX_MODE_ADMx64];
	sscanf(key,"%d %d %d %d %d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7]
	);
	for(int i = 0; i < MAX_MODE_ADMx64; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	int s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx64) s = 0;
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

int ADMx128String(char* input, char* output, char* key, int maxdest){
	int asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	int mode[MAX_MODE_ADMx128];
	sscanf(key,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
		&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15]
	);
	for(int i = 0; i < MAX_MODE_ADMx128; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	int s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx128) s = 0;
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

int ADMx256String(char* input, char* output, char* key, int maxdest){
	int asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	int mode[MAX_MODE_ADMx256];
	sscanf(key,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&mode[0],&mode[1],&mode[2],&mode[3],&mode[4],&mode[5],&mode[6],&mode[7],
		&mode[8],&mode[9],&mode[10],&mode[11],&mode[12],&mode[13],&mode[14],&mode[15],
		&mode[16],&mode[17],&mode[18],&mode[19],&mode[20],&mode[21],&mode[22],&mode[23],
		&mode[24],&mode[25],&mode[26],&mode[27],&mode[28],&mode[29],&mode[30],&mode[31]
	);
	for(int i = 0; i < MAX_MODE_ADMx256; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	int s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx256) s = 0;
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

int ADMx512String(char* input, char* output, char* password, bool invertpassword, int maxdest){
	int asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;

	int psize = strlen(password);
	if(psize < 1 || psize > 255) return ERROR_CODE_ADM_PASSWORD;
	
	int	mode[MAX_MODE_ADMx512],
		BinKeyAlfa[MAX_LEN_BINARY_ADMx512],
		BinKeyBeta[MAX_LEN_BINARY_ADMx512],
		BinKeyGamma[MAX_LEN_BINARY_ADMx512],
		BinKeyDelta[MAX_LEN_BINARY_ADMx512];

	char hash[MAX_KEY_LEN_ADMx512],
		 tmpkey[MAX_LEN_BINARY_ADMx512];
	
	
	//Create Bin Key Alfa
	stringstream ss;
	string pass;
	ss << password;
	ss >> pass;
	
	pass = md5(pass);
	
	StrToChar(pass,hash);
	UpperCase(hash);
	HexStringToString(hash,tmpkey,sizeof(tmpkey));
	
	for(int i = 0, j = strlen(tmpkey); i < j; i++){
		BinKeyAlfa[i] = (0xFF & (tmpkey[i]+256));
	}
	
	//Create Bin Key Beta	
	for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
		BinKeyBeta[i] = (BinKeyAlfa[i] ^ 0xFF);
	}
	
	//Create Bin Key Gamma
	for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
		BinKeyGamma[i] = (((0xF & ((BinKeyAlfa[i] >> 4)+8))*16) + (0xF & ((BinKeyAlfa[i] & 0xF)+8)));
	}

	//Create Bin Key Delta
	for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
		BinKeyDelta[i] = (((0xF & ((BinKeyBeta[i] >> 4)+8))*16) + (0xF & ((BinKeyBeta[i] & 0xF)+8)));
	}

	//Decode password
	if(invertpassword){
		for(int i = 0; i < MAX_LEN_BINARY_ADMx512; i++){
			BinKeyAlfa[i] = (0xFF & (256-BinKeyAlfa[i]));
			BinKeyBeta[i] = (0xFF & (256-BinKeyBeta[i]));
			BinKeyGamma[i] = (0xFF & (256-BinKeyGamma[i]));
			BinKeyDelta[i] = (0xFF & (256-BinKeyDelta[i]));
		}
	}
	
	//Allocate key address
	int tid = 0;
	for(int i = 0; i < MAX_MODE_ADMx512; i++){
		switch(i % 8){
			case 0: mode[i] = BinKeyAlfa[tid]; break;
			case 1: mode[i] = BinKeyGamma[tid]; break;
			case 2: mode[i] = BinKeyBeta[tid]; break;
			case 3: mode[i] = BinKeyDelta[tid]; break;
			case 4: mode[i] = BinKeyGamma[tid]; break;
			case 5: mode[i] = BinKeyBeta[tid]; break;
			case 6: mode[i] = BinKeyAlfa[tid]; break;
			case 7: mode[i] = BinKeyDelta[tid]; break;
		}
		if((i+1) % 8 == 0) tid++;
	}	
	
	int s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx512) s = 0;
	}
	output[asize] = '\0';
	return ERROR_CODE_ADM_OK;
}

//EOF
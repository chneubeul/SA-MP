/****************************************************************************************************
 *                                                                                                  *
 *                                       ADM Encryption File                                        *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.6b                                                                               *
 *                                                                                                  *
 * File Functions:                                                                                  *
 * InvertFile(const char* input, const char* output);                                               *
 * ADMx32(const char* input, const char* output, char* key);                                        *
 * ADMx64(const char* input, const char* output, char* key);                                        *
 * ADMx128(const char* input, const char* output, char* key);                                       *
 * ADMx256(const char* input, const char* output, char* key);                                       *
 *                                                                                                  *
 * String Functions:                                                                                *
 * InvertString(char* input, char* output, int maxdest);                                            *
 * ADMx32String(char* input, char* output, char* key, int maxdest);                                 *
 * ADMx64String(char* input, char* output, char* key, int maxdest);                                 *
 * ADMx128String(char* input, char* output, char* key, int maxdest);                                *
 * ADMx256String(char* input, char* output, char* key, int maxdest);                                *
 * StringToHexString(char* input, char* output, int maxdest);                                       *
 * HexStringToString(char* input, char* output, int maxdest);                                       *
 *                                                                                                  *
 * Return value:                                                                                    *
 * ERROR_CODE_ADM_UNEXEC      //function unexecutable                                               *
 * ERROR_CODE_ADM_OK          //success                                                             *
 * ERROR_CODE_ADM_INPUT       //input file not exist                                                *
 * ERROR_CODE_ADM_OUTPUT      //output file exist                                                   *
 * ERROR_CODE_ADM_KEY         //invalid key                                                         *
 * ERROR_CODE_ADM_SIZE        //invalid file size                                                   *
 * ERROR_CODE_ADM_DEST        //error destination size                                              *
 * ERROR_CODE_ADM_OPEN_INPUT  //error open input file                                               *
 * ERROR_CODE_ADM_OPEN_OUTPUT //error open output file                                              *
 *                                                                                                  *
 * Key Generator:                                                                                   *
 * http://ngc.ugu.pl/admkg                                                                          *
 *                                                                                                  *
 ****************************************************************************************************/
 
/*
#define _LARGEFILE_SOURCE		1
#define _LARGEFILE64_SOURCE		1
#define _FILE_OFFSET_BITS		64
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
*/

#if defined _adm_encryption
	#endinput
#endif
#define _adm_encryption

#define MAX_FILE_SIZE				(18446744073709551615ULL)	//~16 EB

#define MAX_MODE_ADMx32				(4)
#define MAX_MODE_ADMx64				(8)
#define MAX_MODE_ADMx128			(16)
#define MAX_MODE_ADMx256			(32)

#define MAX_KEY_LEN_ADMx32			(16)
#define MAX_KEY_LEN_ADMx64			(32)
#define MAX_KEY_LEN_ADMx128			(64)
#define MAX_KEY_LEN_ADMx256			(128)

#define ERROR_CODE_ADM_UNEXEC		(0)			//function unexecutable
#define ERROR_CODE_ADM_OK			(1)			//success
#define ERROR_CODE_ADM_INPUT		(-1)		//input file not exist
#define ERROR_CODE_ADM_OUTPUT		(-2)		//output file exist
#define ERROR_CODE_ADM_KEY			(-3)		//invalid key
#define ERROR_CODE_ADM_SIZE			(-4)		//invalid file size
#define ERROR_CODE_ADM_DEST			(-5)		//error destination size
#define ERROR_CODE_ADM_OPEN_INPUT	(-6)		//error open input file
#define ERROR_CODE_ADM_OPEN_OUTPUT	(-7)		//error open output file
	
bool fexist(const char *fileName){
	ifstream infile(fileName);
	return infile.good();
}

std::ifstream::pos_type filesize(const char* filename){
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg(); 
}

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
		if(input[offset] < 58){
			unit[0] = (input[offset]-48);
		} else {
			unit[0] = (input[offset]-55);
		}
		if(input[offset+1] < 58){
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


//EOF
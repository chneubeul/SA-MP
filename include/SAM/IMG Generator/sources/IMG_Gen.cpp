/****************************************************************************************************
 *                                                                                                  *
 *                                   Binary Object File Converter                                   *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM/IMG%20Generator           *
 *                                                                                                  *
 * File Version: 1.0                                                                                *
 *                                                                                                  *
 ****************************************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <fstream>
#include <bitset>

#include "BINLDR_CPP.inc"

using namespace std;

void StrToChar(string input, char* output){
	for(int i = 0, j = input.length(); i < j; i++){
		output[i] = input[i];
	}
	output[input.length()] = '\0';
}

bool fexist(const char *filename){
	std::ifstream ifile(filename);
	return (bool)ifile;
}

std::ifstream::pos_type filesize(const char* filename){
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

int float_to_int(float value){
	union {
		float input;
		int   output;
	} data;
	
	data.input = value;
	bitset<sizeof(float) * CHAR_BIT> bits(data.output);
	return data.output;
}

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("IMG_Gen <input_file> <output_file>\n");
		return 0;
	}
	char input[256], output[256];
	snprintf(input,sizeof input,"%s",argv[1]);
	snprintf(output,sizeof output,"%s",argv[2]);
	if(!fexist(input)){
		printf("Input file not exist.\n");
		return 0;
	} else if(fexist(output)){
		printf("Output file exist.\n");
		return 0;
	}
	
	ifstream inpf;
	ofstream outf;

	inpf.open(input, ios::binary);
	outf.open(output, ios::binary);
	
	if(!inpf){
		printf("Cannot open input file.\n");
		return 0;
	}
	
	int read_time = GetTickCount();
	int cnt = 0, lcnt = 0, ecnt = 0;
	
	while(!inpf.eof()){
		lcnt++;
		string line;
		char buffer[256];
		getline(inpf,line);
		StrToChar(line,buffer);
		if(line[0] != '/' && line.find("CreateDynamicObject") != string::npos){
			int modelid = 0, worldid = -1, interiorid = -1, playerid = -1, RAW[MAX_RAW_DATA], tmp;
			float x, y, z, rx, ry, rz, streamdistance = 200.0, drawdistance = 0.0;
			bool erno = true;
			
			if(sscanf(buffer,"CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f,%f);",&modelid,&x,&y,&z,&rx,&ry,&rz,&worldid,&interiorid,&playerid,&streamdistance,&drawdistance)){
				erno = false;
				if(streamdistance == -1) streamdistance = CalculateObjectDistance(modelid);
			} else if(sscanf(buffer,"CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f);",&modelid,&x,&y,&z,&rx,&ry,&rz,&worldid,&interiorid,&playerid,&streamdistance)){
				erno = false;
				if(streamdistance == -1) streamdistance = CalculateObjectDistance(modelid);
			} else if(sscanf(buffer,"CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f,%d,%d,%d);",&modelid,&x,&y,&z,&rx,&ry,&rz,&worldid,&interiorid,&playerid)){
				erno = false;
				if(streamdistance == -1) streamdistance = CalculateObjectDistance(modelid);
			} else if(sscanf(buffer,"CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f,%d,%d);",&modelid,&x,&y,&z,&rx,&ry,&rz,&worldid,&interiorid)){
				erno = false;
				if(streamdistance == -1) streamdistance = CalculateObjectDistance(modelid);
			} else if(sscanf(buffer,"CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f,%d);",&modelid,&x,&y,&z,&rx,&ry,&rz,&worldid)){
				erno = false;
				if(streamdistance == -1) streamdistance = CalculateObjectDistance(modelid);
			} else if(sscanf(buffer,"CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f);",&modelid,&x,&y,&z,&rx,&ry,&rz)){
				erno = false;
				if(streamdistance == -1) streamdistance = CalculateObjectDistance(modelid);
			} else {
				printf("Parse error in line %d\n",lcnt);
				ecnt++;
			}
			
			if(!erno){
				ExtractValue(modelid,tmp,tmp,RAW[0],RAW[1]);
				ExtractValue(float_to_int(x),RAW[2],RAW[3],RAW[4],RAW[5]);
				ExtractValue(float_to_int(y),RAW[6],RAW[7],RAW[8],RAW[9]);
				ExtractValue(float_to_int(z),RAW[10],RAW[11],RAW[12],RAW[13]);
				ExtractValue(float_to_int(rx),RAW[14],RAW[15],RAW[16],RAW[17]);
				ExtractValue(float_to_int(ry),RAW[18],RAW[19],RAW[20],RAW[21]);
				ExtractValue(float_to_int(rz),RAW[22],RAW[23],RAW[24],RAW[25]);
				ExtractValue(worldid,RAW[26],RAW[27],RAW[28],RAW[29]);
				ExtractValue(interiorid,RAW[30],RAW[31],RAW[32],RAW[33]);
				ExtractValue(float_to_int(streamdistance),RAW[34],RAW[35],RAW[36],RAW[37]);
				ExtractValue(float_to_int(drawdistance),RAW[38],RAW[39],RAW[40],RAW[41]);

				for(int i = 0; i < MAX_RAW_DATA; i++){
					outf << (char)RAW[i];
				}
				cnt++;
			}
		}
	}
	
	inpf.close();
	outf.close();
	
	float ratio = ((float(filesize(output))/float(filesize(input)))*100.0);
	
	if(ecnt == 0){
		printf("Read %d line, convert %d object, into %d ms, ratio %.2f %%\n",lcnt,cnt,GetTickCount()-read_time,ratio);
	} else {
		printf("Read %d line, convert %d object, into %d ms, ratio %.2f %%, %d errors\n",lcnt,cnt,GetTickCount()-read_time,ratio,ecnt);
	}
	return 0;
}

/****************************************************************************************************
 *                                                                                                  *
 *                                       ADM Encryption File                                        *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.2                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * ADMx32(const input[], const output[], key[]);                                                    *
 * ADMx64(const input[], const output[], key[]);                                                    *
 * ADMx128(const input[], const output[], key[]);                                                   *
 * ADMx256(const input[], const output[], key[]);                                                   *
 *                                                                                                  *
 * Return value:                                                                                    *
 * ERROR_CODE_ADM_OK         //success                                                              *
 * ERROR_CODE_ADM_INPUT      //input file not exist                                                 *
 * ERROR_CODE_ADM_OUTPUT     //output file exist                                                    *
 * ERROR_CODE_ADM_KEY        //invalid key                                                          *
 * ERROR_CODE_ADM_SIZE       //invalid file size                                                    *
 *                                                                                                  *
 * Key Generator:                                                                                   *
 * http://ngc.ugu.pl/admkg                                                                          *
 *                                                                                                  *
 ****************************************************************************************************/
 
#if defined _adm_encryption
	#endinput
#endif
#define _adm_encryption

#if !defined sscanf
	#error Unknown sscanf version
#endif

#define MAX_FILE_SIZE			2147483647	//2 GB

#define MAX_MODE_ADMx32			4
#define MAX_MODE_ADMx64			8
#define MAX_MODE_ADMx128		16
#define MAX_MODE_ADMx256		32

#define MAX_KEY_LEN_ADMx32		16
#define MAX_KEY_LEN_ADMx64		32
#define MAX_KEY_LEN_ADMx128		64
#define MAX_KEY_LEN_ADMx256		128

#define ERROR_CODE_ADM_OK		1		//success
#define ERROR_CODE_ADM_INPUT	-1		//input file not exist
#define ERROR_CODE_ADM_OUTPUT	-2		//output file exist
#define ERROR_CODE_ADM_KEY		-3		//invalid key
#define ERROR_CODE_ADM_SIZE		-4		//invalid file size

stock ADMx32(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode[MAX_MODE_ADMx32];
	sscanf(key,"D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3]
	);
	for(new i = 0; i < MAX_MODE_ADMx32; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	while(idx < asize){
		fputchar(outf,((fgetchar(inpf,0,false)+mode[s]) & 0xFF),false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx32) s = 0;
	}
	fclose(inpf);
	fclose(outf);
	return ERROR_CODE_ADM_OK;
}

#define ADM ADMx32

stock ADMx64(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode[MAX_MODE_ADMx64];
	sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7]
	);
	for(new i = 0; i < MAX_MODE_ADMx64; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	while(idx < asize){
		fputchar(outf,((fgetchar(inpf,0,false)+mode[s]) & 0xFF),false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx64) s = 0;
	}
	fclose(inpf);
	fclose(outf);
	return ERROR_CODE_ADM_OK;
}

stock ADMx128(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode[MAX_MODE_ADMx128];
	sscanf(string,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
		mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15]
	);
	for(new i = 0; i < MAX_MODE_ADMx128; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	while(idx < asize){
		fputchar(outf,((fgetchar(inpf,0,false)+mode[s]) & 0xFF),false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx128) s = 0;
	}
	fclose(inpf);
	fclose(outf);
	return ERROR_CODE_ADM_OK;
}

stock ADMx256(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode[MAX_MODE_ADMx256];
	sscanf(string,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
		mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15],
		mode[16],mode[17],mode[18],mode[19],mode[20],mode[21],mode[22],mode[23],
		mode[24],mode[25],mode[26],mode[27],mode[28],mode[29],mode[30],mode[31]
	);
	for(new i = 0; i < MAX_MODE_ADMx256; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	while(idx < asize){
		fputchar(outf,((fgetchar(inpf,0,false)+mode[s]) & 0xFF),false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx256) s = 0;
	}
	fclose(inpf);
	fclose(outf);
	return ERROR_CODE_ADM_OK;
}

//EOF

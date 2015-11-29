/****************************************************************************************************
 *                                                                                                  *
 *                                       ADM Encryption File                                        *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.0                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * ADMx32(const input[], const output[], key[], &status);                                           *
 * ADMx64(const input[], const output[], key[], &status);                                           *
 * ADMx128(const input[], const output[], key[], &status);                                          *
 * ADMx256(const input[], const output[], key[], &status);                                          *
 *                                                                                                  *
 * return:                                                                                          *
 * 0 - error                                                                                        *
 * 1 - success                                                                                      *
 *                                                                                                  *
 * Status list:                                                                                     *
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

new ModeADMx32[MAX_MODE_ADMx32],
	ModeADMx64[MAX_MODE_ADMx64],
	ModeADMx128[MAX_MODE_ADMx128],
	ModeADMx256[MAX_MODE_ADMx256];

stock RootADMx32(string1,&string2,step){
	string2 = ((string1+ModeADMx32[step]) & 0xFF);
}

stock RootADMx64(string1,&string2,step){
	string2 = ((string1+ModeADMx64[step]) & 0xFF);
}

stock RootADMx128(string1,&string2,step){
	string2 = ((string1+ModeADMx128[step]) & 0xFF);
}

stock RootADMx256(string1,&string2,step){
	string2 = ((string1+ModeADMx256[step]) & 0xFF);
}

stock KeyExtractADMx32(string[],&status){
	sscanf(string,"D(0)D(0)D(0)D(0)",
		ModeADMx32[0],
		ModeADMx32[1],
		ModeADMx32[2],
		ModeADMx32[3]
	);
	for(new i = 0; i < MAX_MODE_ADMx32; i++){
		if(ModeADMx32[0] < 1 || ModeADMx32[0] > 255){
			status = ERROR_CODE_ADM_KEY;
			break;
		}
	}
}

stock KeyExtractADMx64(string[],&status){
	sscanf(string,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		ModeADMx64[0],
		ModeADMx64[1],
		ModeADMx64[2],
		ModeADMx64[3],
		ModeADMx64[4],
		ModeADMx64[5],
		ModeADMx64[6],
		ModeADMx64[7]
	);
	for(new i = 0; i < MAX_MODE_ADMx64; i++){
		if(ModeADMx64[0] < 1 || ModeADMx64[0] > 255){
			status = ERROR_CODE_ADM_KEY;
			break;
		}
	}
}

stock KeyExtractADMx128(string[],&status){
	sscanf(string,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		ModeADMx128[0],
		ModeADMx128[1],
		ModeADMx128[2],
		ModeADMx128[3],
		ModeADMx128[4],
		ModeADMx128[5],
		ModeADMx128[6],
		ModeADMx128[7],
		ModeADMx128[8],
		ModeADMx128[9],
		ModeADMx128[10],
		ModeADMx128[11],
		ModeADMx128[12],
		ModeADMx128[13],
		ModeADMx128[14],
		ModeADMx128[15]
	);
	for(new i = 0; i < MAX_MODE_ADMx128; i++){
		if(ModeADMx128[0] < 1 || ModeADMx128[0] > 255){
			status = ERROR_CODE_ADM_KEY;
			break;
		}
	}
}

stock KeyExtractADMx256(string[],&status){
	sscanf(string,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		ModeADMx256[0],
		ModeADMx256[1],
		ModeADMx256[2],
		ModeADMx256[3],
		ModeADMx256[4],
		ModeADMx256[5],
		ModeADMx256[6],
		ModeADMx256[7],
		ModeADMx256[8],
		ModeADMx256[9],
		ModeADMx256[10],
		ModeADMx256[11],
		ModeADMx256[12],
		ModeADMx256[13],
		ModeADMx256[14],
		ModeADMx256[15],
		ModeADMx256[16],
		ModeADMx256[17],
		ModeADMx256[18],
		ModeADMx256[19],
		ModeADMx256[20],
		ModeADMx256[21],
		ModeADMx256[22],
		ModeADMx256[23],
		ModeADMx256[24],
		ModeADMx256[25],
		ModeADMx256[26],
		ModeADMx256[27],
		ModeADMx256[28],
		ModeADMx256[29],
		ModeADMx256[30],
		ModeADMx256[31]
	);
	for(new i = 0; i < MAX_MODE_ADMx256; i++){
		if(ModeADMx256[0] < 1 || ModeADMx256[0] > 255){
			status = ERROR_CODE_ADM_KEY;
			break;
		}
	}
}

stock ADMx32(const input[], const output[], key[], &status){
	if(!fexist(input)){ status = ERROR_CODE_ADM_INPUT; return 0; }
	if(fexist(output)){ status = ERROR_CODE_ADM_OUTPUT; return 0; }
	KeyExtractADMx32(key,status);
	if(status == ERROR_CODE_ADM_KEY) return 0;
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){ fclose(inpf); status = ERROR_CODE_ADM_SIZE; return 0; }
	new File:outf = fopen(output,io_write), gchar;
	while(idx < asize){
		gchar = fgetchar(inpf,0,false);
		RootADMx32(gchar,gchar,s);
		fputchar(outf,gchar,false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx32) s = 0;
	}
	status = ERROR_CODE_ADM_OK;
	fclose(inpf);
	fclose(outf);
	return 1;
}

stock ADMx64(const input[], const output[], key[], &status){
	if(!fexist(input)){ status = ERROR_CODE_ADM_INPUT; return 0; }
	if(fexist(output)){ status = ERROR_CODE_ADM_OUTPUT; return 0; }
	KeyExtractADMx64(key,status);
	if(status == ERROR_CODE_ADM_KEY) return 0;
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){ fclose(inpf); status = ERROR_CODE_ADM_SIZE; return 0; }
	new File:outf = fopen(output,io_write), gchar;
	while(idx < asize){
		gchar = fgetchar(inpf,0,false);
		RootADMx64(gchar,gchar,s);
		fputchar(outf,gchar,false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx64) s = 0;
	}
	status = ERROR_CODE_ADM_OK;
	fclose(inpf);
	fclose(outf);
	return 1;
}

stock ADMx128(const input[], const output[], key[], &status){
	if(!fexist(input)){ status = ERROR_CODE_ADM_INPUT; return 0; }
	if(fexist(output)){ status = ERROR_CODE_ADM_OUTPUT; return 0; }
	KeyExtractADMx128(key,status);
	if(status == ERROR_CODE_ADM_KEY) return 0;
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){ fclose(inpf); status = ERROR_CODE_ADM_SIZE; return 0; }
	new File:outf = fopen(output,io_write), gchar;
	while(idx < asize){
		gchar = fgetchar(inpf,0,false);
		RootADMx128(gchar,gchar,s);
		fputchar(outf,gchar,false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx128) s = 0;
	}
	status = ERROR_CODE_ADM_OK;
	fclose(inpf);
	fclose(outf);
	return 1;
}

stock ADMx256(const input[], const output[], key[], &status){
	if(!fexist(input)){ status = ERROR_CODE_ADM_INPUT; return 0; }
	if(fexist(output)){ status = ERROR_CODE_ADM_OUTPUT; return 0; }
	KeyExtractADMx256(key,status);
	if(status == ERROR_CODE_ADM_KEY) return 0;
	new File:inpf = fopen(input,io_read);
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){ fclose(inpf); status = ERROR_CODE_ADM_SIZE; return 0; }
	new File:outf = fopen(output,io_write), gchar;
	while(idx < asize){
		gchar = fgetchar(inpf,0,false);
		RootADMx256(gchar,gchar,s);
		fputchar(outf,gchar,false);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx256) s = 0;
	}
	status = ERROR_CODE_ADM_OK;
	fclose(inpf);
	fclose(outf);
	return 1;
}

//EOF

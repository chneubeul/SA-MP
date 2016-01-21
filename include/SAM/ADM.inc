/****************************************************************************************************
 *                                                                                                  *
 *                                       ADM Encryption File                                        *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.6                                                                                *
 *                                                                                                  *
 * File Functions:                                                                                  *
 * ADMToInt(ADM:admvar);                                                                            *
 * ADM:InvertFile(const input[], const output[]);                                                   *
 * ADM:ADMx32(const input[], const output[], key[]);                                                *
 * ADM:ADMx64(const input[], const output[], key[]);                                                *
 * ADM:ADMx128(const input[], const output[], key[]);                                               *
 * ADM:ADMx256(const input[], const output[], key[]);                                               *
 *                                                                                                  *
 * String Functions:                                                                                *
 * ADM:InvertString(input[], output[], maxdest = sizeof(output));                                   *
 * ADM:ADMx32String(input[], output[], key[], maxdest = sizeof(output));                            *
 * ADM:ADMx64String(input[], output[], key[], maxdest = sizeof(output));                            *
 * ADM:ADMx128String(input[], output[], key[], maxdest = sizeof(output));                           *
 * ADM:ADMx256String(input[], output[], key[], maxdest = sizeof(output));                           *
 * ADM:StringToHexString(input[], output[], maxdest = sizeof(output));                              *
 * ADM:HexStringToString(input[], output[], maxdest = sizeof(output));                              *
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
 
#if defined _adm_encryption
	#endinput
#endif
#define _adm_encryption

#if !defined sscanf
	#error Unknown sscanf version
#endif

#define MAX_FILE_SIZE				(2147483647)	//~2 GB

#define MAX_MODE_ADMx32				(4)
#define MAX_MODE_ADMx64				(8)
#define MAX_MODE_ADMx128			(16)
#define MAX_MODE_ADMx256			(32)

#define MAX_KEY_LEN_ADMx32			(16)
#define MAX_KEY_LEN_ADMx64			(32)
#define MAX_KEY_LEN_ADMx128			(64)
#define MAX_KEY_LEN_ADMx256			(128)

#define ERROR_CODE_ADM_UNEXEC		(ADM:0)		//function unexecutable
#define ERROR_CODE_ADM_OK			(ADM:1)		//success
#define ERROR_CODE_ADM_INPUT		(ADM:-1)	//input file not exist
#define ERROR_CODE_ADM_OUTPUT		(ADM:-2)	//output file exist
#define ERROR_CODE_ADM_KEY			(ADM:-3)	//invalid key
#define ERROR_CODE_ADM_SIZE			(ADM:-4)	//invalid file size
#define ERROR_CODE_ADM_DEST			(ADM:-5)	//error destination size
#define ERROR_CODE_ADM_OPEN_INPUT	(ADM:-6)	//error open input file
#define ERROR_CODE_ADM_OPEN_OUTPUT	(ADM:-7)	//error open output file

//Remove ADM: tag
stock ADMToInt(ADM:admvar){
	return (_:admvar);
}

stock ADM:InvertFile(const input[], const output[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new File:inpf = fopen(input,io_read);
	if(!inpf) return ERROR_CODE_ADM_OPEN_INPUT;
	new asize = flength(inpf), idx = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	if(!outf){
		fclose(inpf);
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
	while(idx < asize){
		fputchar(outf,(fgetchar(inpf,0,false) ^ 0xFF),false);
		idx++;
	}
	fclose(inpf);
	fclose(outf);
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx32(const input[], const output[], key[]){
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
	if(!inpf) return ERROR_CODE_ADM_OPEN_INPUT;
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	if(!outf){
		fclose(inpf);
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
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

stock ADM:ADMx64(const input[], const output[], key[]){
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
	if(!inpf) return ERROR_CODE_ADM_OPEN_INPUT;
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	if(!outf){
		fclose(inpf);
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
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

stock ADM:ADMx128(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode[MAX_MODE_ADMx128];
	sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
		mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15]
	);
	for(new i = 0; i < MAX_MODE_ADMx128; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new File:inpf = fopen(input,io_read);
	if(!inpf) return ERROR_CODE_ADM_OPEN_INPUT;
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	if(!outf){
		fclose(inpf);
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
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

stock ADM:ADMx256(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode[MAX_MODE_ADMx256];
	sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
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
	if(!inpf) return ERROR_CODE_ADM_OPEN_INPUT;
	new asize = flength(inpf), idx = 0, s = 0;
	if(asize > MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return ERROR_CODE_ADM_SIZE;
	}
	new File:outf = fopen(output,io_write);
	if(!outf){
		fclose(inpf);
		return ERROR_CODE_ADM_OPEN_OUTPUT;
	}
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



stock ADM:InvertString(input[], output[], maxdest = sizeof(output)){
	new asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	while(idx < asize){
		output[idx] = (input[idx] ^ 0xFF);
		idx++;
	}
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx32String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	new mode[MAX_MODE_ADMx32];
	sscanf(key,"D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3]
	);
	for(new i = 0; i < MAX_MODE_ADMx32; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx32) s = 0;
	}
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx64String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	new mode[MAX_MODE_ADMx64];
	sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7]
	);
	for(new i = 0; i < MAX_MODE_ADMx64; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx64) s = 0;
	}
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx128String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	new mode[MAX_MODE_ADMx128];
	sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
		mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15]
	);
	for(new i = 0; i < MAX_MODE_ADMx128; i++){
		if(mode[i] < 1 || mode[i] > 255){
			return ERROR_CODE_ADM_KEY;
		}
	}
	new s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx128) s = 0;
	}
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx256String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input), idx = 0;
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	new mode[MAX_MODE_ADMx256];
	sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
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
	new s = 0;
	while(idx < asize){
		output[idx] = ((input[idx]+mode[s]) & 0xFF);
		idx++;
		s++;
		if(s >= MAX_MODE_ADMx256) s = 0;
	}
	return ERROR_CODE_ADM_OK;
}

stock ADM:StringToHexString(input[], output[], maxdest = sizeof(output)){
	new asize = strlen(input), idx = 0, offset = 0;
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
	return ERROR_CODE_ADM_OK;
}

stock ADM:HexStringToString(input[], output[], maxdest = sizeof(output)){
	new asize = (strlen(input)/2), idx = 0, offset = 0, unit[2];
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
	return ERROR_CODE_ADM_OK;
}
//EOF

/****************************************************************************************************
 *                                                                                                  *
 *                                       ADM Encryption File                                        *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 1.7                                                                                *
 *                                                                                                  *
 * File Functions:                                                                                  *
 * ADM:InvertFile(const input[], const output[]);                                                   *
 * ADM:HexNegativeFile(const input[], const output[], key[]);                                       *
 * ADM:RollXFile(const input[], const output[], key[]);                                             *
 * ADM:ADMx32(const input[], const output[], key[]);                                                *
 * ADM:ADMx64(const input[], const output[], key[]);                                                *
 * ADM:ADMx128(const input[], const output[], key[]);                                               *
 * ADM:ADMx256(const input[], const output[], key[]);                                               *
 *                                                                                                  *
 * String Functions:                                                                                *
 * ADM:InvertString(input[], output[], maxdest = sizeof(output));                                   *
 * ADM:HexNegativeString(input[], output[], key[], maxdest = sizeof(output));                       *
 * ADM:RollXString(input[], output[], key[], maxdest = sizeof(output));                             *
 * ADM:ADMx32String(input[], output[], key[], maxdest = sizeof(output));                            *
 * ADM:ADMx64String(input[], output[], key[], maxdest = sizeof(output));                            *
 * ADM:ADMx128String(input[], output[], key[], maxdest = sizeof(output));                           *
 * ADM:ADMx256String(input[], output[], key[], maxdest = sizeof(output));                           *
 * ADM:StringToHexString(input[], output[], maxdest = sizeof(output));                              *
 * ADM:HexStringToString(input[], output[], maxdest = sizeof(output));                              *
 *                                                                                                  *
 * Other Functions:                                                                                 *
 * ADMToInt(ADM:admvar);                                                                            *
 * bool:IsValidADMKey(key[], type);                                                                 *
 * GetADMKeyType(key[], bool:distorted = false);                                                    *
 * ADM:DecodeADMKey(inputkey[], outputkey[], type, maxdest = sizeof(outputkey));                    *
 * ADM:CreateADMKey(key[], type, maxdest = sizeof(key));                                            *
 *                                                                                                  *
 * Return value:                                                                                    *
 * ERROR_CODE_ADM_UNEXEC       //function unexecutable                                              *
 * ERROR_CODE_ADM_OK           //success                                                            *
 * ERROR_CODE_ADM_INPUT        //input file not exist                                               *
 * ERROR_CODE_ADM_OUTPUT       //output file exist                                                  *
 * ERROR_CODE_ADM_KEY          //invalid key                                                        *
 * ERROR_CODE_ADM_SIZE         //invalid file size                                                  *
 * ERROR_CODE_ADM_DEST         //error destination size                                             *
 * ERROR_CODE_ADM_OPEN_INPUT   //error open input file                                              *
 * ERROR_CODE_ADM_OPEN_OUTPUT  //error open output file                                             * 
 * ERROR_CODE_ADM_INVALID_TYPE //invalid key type                                                   *
 *                                                                                                  *
 * Key Generator:                                                                                   *
 * http://ngc.ugu.pl/admkg                                                                          *
 *                                                                                                  *
 ****************************************************************************************************/
 
/*
//Check Version ADM.inc
#if !defined _adm_encryption
	#error You need ADM.inc v1.7
#elseif !defined ADM_Encryption_Version
	#error Update you ADM.inc to v1.7
#elseif (ADM_Encryption_Version < 10701)
	#error Update you ADM.inc to v1.7
#endif
*/

#if defined _adm_encryption
	#endinput
#endif
#define _adm_encryption

#define ADM_Encryption_Version 		(10701) //a.b[c] 10000*a+100*b+c

#if !defined sscanf
	#error Unknown sscanf version
#endif

#define MAX_FILE_SIZE				(2147483647)	//~2 GB

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

#define MAX_KEY_LEN_HEXNEGATIVE		(4)
#define MAX_KEY_LEN_ROLLX			(4)
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
#define ERROR_CODE_ADM_INVALID_TYPE	(ADM:-8)	//invalid key type


/********************
 * Other Functions  *
 ********************/

//Remove ADM: tag
stock ADMToInt(ADM:admvar){
	return (_:admvar);
}

stock bool:IsValidADMKey(key[], type){
	switch(type){
	
		case KEY_TYPE_HEXNEGATIVE: {
			new mode;
			sscanf(key,"D(0)",mode);
			if(mode < 1 || mode > 15){
				return false;
			}
		}
		
		case KEY_TYPE_ROLLX: {
			new mode;
			sscanf(key,"D(0)",mode);
			if(mode < 1 || mode > 255){
				return false;
			}
		}

		case KEY_TYPE_ADMx32: {
			new mode[MAX_MODE_ADMx32];
			sscanf(key,"D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3]
			);
			for(new i = 0; i < MAX_MODE_ADMx32; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}
		}
		
		case KEY_TYPE_ADMx64: {
			new mode[MAX_MODE_ADMx64];
			sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7]
			);
			for(new i = 0; i < MAX_MODE_ADMx64; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}	
		}
		
		case KEY_TYPE_ADMx128: {
			new mode[MAX_MODE_ADMx128];
			sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
				mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15]
			);
			for(new i = 0; i < MAX_MODE_ADMx128; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}
		}
		
		case KEY_TYPE_ADMx256: {
			new mode[MAX_MODE_ADMx256];
			sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
				mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15],
				mode[16],mode[17],mode[18],mode[19],mode[20],mode[21],mode[22],mode[23],
				mode[24],mode[25],mode[26],mode[27],mode[28],mode[29],mode[30],mode[31]
			);
			for(new i = 0; i < MAX_MODE_ADMx256; i++){
				if(mode[i] < 1 || mode[i] > 255){
					return false;
				}
			}
		}

		default: return false;
	}
	return true;
}

stock GetADMKeyType(key[], bool:distorted = false){
	new mode[MAX_MODE_ADMx256], cnt = 0;
	sscanf(key,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
		mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
		mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15],
		mode[16],mode[17],mode[18],mode[19],mode[20],mode[21],mode[22],mode[23],
		mode[24],mode[25],mode[26],mode[27],mode[28],mode[29],mode[30],mode[31]
	);
	for(new i = 0; i < MAX_MODE_ADMx256; i++){
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

stock ADM:DecodeADMKey(inputkey[], outputkey[], type, maxdest = sizeof(outputkey)){
	switch(type){
	
		case KEY_TYPE_HEXNEGATIVE: {
			if(maxdest < MAX_KEY_LEN_HEXNEGATIVE) return ERROR_CODE_ADM_DEST;
			new mode;
			sscanf(inputkey,"D(0)",mode);
			if(mode < 1 || mode > 15){
				outputkey[0] = EOS;
				return ERROR_CODE_ADM_KEY;
			} else {
				format(outputkey,maxdest,"%d",(0xF & (16-mode)));
			}
		}
		
		case KEY_TYPE_ROLLX: {
			if(maxdest < MAX_KEY_LEN_ROLLX) return ERROR_CODE_ADM_DEST;
			new mode;
			sscanf(inputkey,"D(0)",mode);
			if(mode < 1 || mode > 255){
				outputkey[0] = EOS;
				return ERROR_CODE_ADM_KEY;
			} else {
				format(outputkey,maxdest,"%d",(0xFF & (256-mode)));
			}
		}
		
		case KEY_TYPE_ADMx32: {
			if(maxdest < MAX_KEY_LEN_ADMx32) return ERROR_CODE_ADM_DEST;
			new mode[MAX_MODE_ADMx32];
			sscanf(inputkey,"D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3]
			);
			for(new i = 0; i < MAX_MODE_ADMx32; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = EOS;
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						format(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						format(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}
		}
		
		case KEY_TYPE_ADMx64: {
			if(maxdest < MAX_KEY_LEN_ADMx64) return ERROR_CODE_ADM_DEST;
			new mode[MAX_MODE_ADMx64];
			sscanf(inputkey,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7]
			);
			for(new i = 0; i < MAX_MODE_ADMx64; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = EOS;
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						format(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						format(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}	
		}
		
		case KEY_TYPE_ADMx128: {
			if(maxdest < MAX_KEY_LEN_ADMx128) return ERROR_CODE_ADM_DEST;
			new mode[MAX_MODE_ADMx128];
			sscanf(inputkey,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
				mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15]
			);
			for(new i = 0; i < MAX_MODE_ADMx128; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = EOS;
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						format(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						format(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}
		}
		
		case KEY_TYPE_ADMx256: {
			if(maxdest < MAX_KEY_LEN_ADMx256) return ERROR_CODE_ADM_DEST;
			new mode[MAX_MODE_ADMx256];
			sscanf(inputkey,"D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)D(0)",
				mode[0],mode[1],mode[2],mode[3],mode[4],mode[5],mode[6],mode[7],
				mode[8],mode[9],mode[10],mode[11],mode[12],mode[13],mode[14],mode[15],
				mode[16],mode[17],mode[18],mode[19],mode[20],mode[21],mode[22],mode[23],
				mode[24],mode[25],mode[26],mode[27],mode[28],mode[29],mode[30],mode[31]
			);
			for(new i = 0; i < MAX_MODE_ADMx256; i++){
				if(mode[i] < 1 || mode[i] > 255){
					outputkey[0] = EOS;
					return ERROR_CODE_ADM_KEY;
				} else {
					if(i == 0){
						format(outputkey,maxdest,"%d",(0xFF & (256-mode[i])));
					} else {
						format(outputkey,maxdest,"%s %d",outputkey,(0xFF & (256-mode[i])));
					}
				}
			}
		}

		default: return ERROR_CODE_ADM_INVALID_TYPE;
	}
	return ERROR_CODE_ADM_OK;
}

stock ADM:CreateADMKey(key[], type, maxdest = sizeof(key)){
	switch(type){
	
		case KEY_TYPE_HEXNEGATIVE: {
			if(maxdest < MAX_KEY_LEN_HEXNEGATIVE) return ERROR_CODE_ADM_DEST;
			format(key,maxdest,"%d",random(15)+1);
		}
		
		case KEY_TYPE_ROLLX: {
			if(maxdest < MAX_KEY_LEN_ROLLX) return ERROR_CODE_ADM_DEST;
			format(key,maxdest,"%d",random(255)+1);
		}
		
		case KEY_TYPE_ADMx32: {
			if(maxdest < MAX_KEY_LEN_ADMx32) return ERROR_CODE_ADM_DEST;
			for(new i = 0; i < MAX_MODE_ADMx32; i++){
				if(i == 0){
					format(key,maxdest,"%d",random(255)+1);
				} else {
					format(key,maxdest,"%s %d",key,random(255)+1);
				}
			}
		}
		
		case KEY_TYPE_ADMx64: {
			if(maxdest < MAX_KEY_LEN_ADMx64) return ERROR_CODE_ADM_DEST;
			for(new i = 0; i < MAX_MODE_ADMx64; i++){
				if(i == 0){
					format(key,maxdest,"%d",random(255)+1);
				} else {
					format(key,maxdest,"%s %d",key,random(255)+1);
				}
			}	
		}
		
		case KEY_TYPE_ADMx128: {
			if(maxdest < MAX_KEY_LEN_ADMx128) return ERROR_CODE_ADM_DEST;
			for(new i = 0; i < MAX_MODE_ADMx128; i++){
				if(i == 0){
					format(key,maxdest,"%d",random(255)+1);
				} else {
					format(key,maxdest,"%s %d",key,random(255)+1);
				}
			}
		}
		
		case KEY_TYPE_ADMx256: {
			if(maxdest < MAX_KEY_LEN_ADMx256) return ERROR_CODE_ADM_DEST;
			for(new i = 0; i < MAX_MODE_ADMx256; i++){
				if(i == 0){
					format(key,maxdest,"%d",random(255)+1);
				} else {
					format(key,maxdest,"%s %d",key,random(255)+1);
				}
			}
		}

		default: return ERROR_CODE_ADM_INVALID_TYPE;
	}
	return ERROR_CODE_ADM_OK;
}


/********************
 * File Functions   *
 ********************/

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

stock ADM:HexNegativeFile(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode;
	sscanf(key,"D(0)",mode);
	if(mode < 1 || mode > 15) return ERROR_CODE_ADM_KEY;
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
		fputchar(outf,(((0xF & ((fgetchar(inpf,0,false) >> 4)+mode))*16) + (0xF & ((fgetchar(inpf,0,false) & 0xF)+mode))));
		idx++;
	}
	fclose(inpf);
	fclose(outf);
	return ERROR_CODE_ADM_OK;
}

stock ADM:RollXFile(const input[], const output[], key[]){
	if(!fexist(input)) return ERROR_CODE_ADM_INPUT;
	if(fexist(output)) return ERROR_CODE_ADM_OUTPUT;
	new mode;
	sscanf(key,"D(0)",mode);
	if(mode < 1 || mode > 255) return ERROR_CODE_ADM_KEY;
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
		fputchar(outf,((fgetchar(inpf,0,false)+mode) & 0xFF),false);
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

/********************
 * String Functions *
 ********************/

stock ADM:InvertString(input[], output[], maxdest = sizeof(output)){
	new asize = strlen(input);
	if(maxdest < asize) return ERROR_CODE_ADM_DEST;
	for(new i = 0; i < asize; i++){
		output[i] = (input[i] ^ 0xFF);
	}
	output[asize] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:HexNegativeString(input[], output[], key[], maxdest = sizeof(output)){
	new mode;
	sscanf(key,"D(0)",mode);
	if(mode < 1 || mode > 15) return ERROR_CODE_ADM_KEY;
	new asize = strlen(input);
	if(asize > maxdest) return ERROR_CODE_ADM_DEST;
	for(new i = 0; i < asize; i++){
		output[i] = (((0xF & ((input[i] >> 4)+mode))*16) + (0xF & ((input[i] & 0xF)+mode)));
	}
	output[asize] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:RollXString(input[], output[], key[], maxdest = sizeof(output)){
	new mode;
	sscanf(key,"D(0)",mode);
	if(mode < 1 || mode > 255) return ERROR_CODE_ADM_KEY;
	new asize = strlen(input);
	if(asize > maxdest) return ERROR_CODE_ADM_DEST;
	for(new i = 0; i < asize; i++){
		output[i] = (0xFF & (input[i]+mode));
	}
	output[strlen(input)] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx32String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input);
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
	for(new i = 0; i < asize; i++){
		output[i] = ((input[i]+mode[s]) & 0xFF);
		s++;
		if(s >= MAX_MODE_ADMx32) s = 0;
	}
	output[asize] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx64String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input);
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
	for(new i = 0; i < asize; i++){
		output[i] = ((input[i]+mode[s]) & 0xFF);
		s++;
		if(s >= MAX_MODE_ADMx64) s = 0;
	}
	output[asize] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx128String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input);
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
	for(new i = 0; i < asize; i++){
		output[i] = ((input[i]+mode[s]) & 0xFF);
		s++;
		if(s >= MAX_MODE_ADMx128) s = 0;
	}
	output[asize] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:ADMx256String(input[], output[], key[], maxdest = sizeof(output)){
	new asize = strlen(input);
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
	for(new i = 0; i < asize; i++){
		output[i] = ((input[i]+mode[s]) & 0xFF);
		s++;
		if(s >= MAX_MODE_ADMx256) s = 0;
	}
	output[asize] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:StringToHexString(input[], output[], maxdest = sizeof(output)){
	new asize = strlen(input), offset = 0;
	if((asize*2) > maxdest) return ERROR_CODE_ADM_DEST;
	for(new i = 0; i < asize; i++){
		output[offset] = (0xF & (input[i] >> 4));
		if(output[offset] < 10){
			output[offset] += 48;
		} else {
			output[offset] += 55;
		}
		output[offset+1] = (0xF & input[i]);
		if(output[offset+1] < 10){
			output[offset+1] += 48;
		} else {
			output[offset+1] += 55;
		}
		offset += 2;
	}
	output[asize*2] = EOS;
	return ERROR_CODE_ADM_OK;
}

stock ADM:HexStringToString(input[], output[], maxdest = sizeof(output)){
	new asize = (strlen(input)/2), offset = 0, unit[2];
	if(asize > maxdest) return ERROR_CODE_ADM_DEST;
	for(new i = 0; i < asize; i++){
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
		output[i] = (unit[0]*16)+unit[1];
		offset += 2;
	}
	output[asize] = EOS;
	return ERROR_CODE_ADM_OK;
}


//EOF
/****************************************************************************************************
 *                                                                                                  *
 * Easy IMG Creator v1.1 made by Abyss Morgan                                                       *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts                         *
 *                                                                                                  *
 ****************************************************************************************************/

/*

This file is deprecated, use IMG Generator for Windows:
https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM/IMG%20Generator

*/

#define INPUT_TXT		"MyObject.txt"
#define OUTPUT_BIN		"MyObject.bin"

#include <a_samp>
#include <sscanf2>
#include <SAM/BINLDR>

//Check Version BINLDR.inc
#if !defined _Bin_Loader
	#error You need BINLDR.inc v2.2
#elseif !defined Bin_Loader_Version
	#error Update you BINLDR.inc to v2.2
#elseif (Bin_Loader_Version < 20201)
	#error Update you BINLDR.inc to v2.2
#endif

public OnFilterScriptInit(){
	if(fexist(OUTPUT_BIN)) fremove(OUTPUT_BIN);
	if(fexist(INPUT_TXT)){
		new IMG::edi = SaveBinaryObjectIMG(INPUT_TXT,OUTPUT_BIN);
		if(edi != ERROR_CODE_BINLDR_OK){
			printf("Error Convert '%s' file, code '%d'",INPUT_TXT,IMGToInt(edi));
		}
	}
	return 1;
}

//EOF
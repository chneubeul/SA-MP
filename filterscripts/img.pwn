/****************************************************************************************************
 *                                                                                                  *
 * Easy IMG Creator by Abyss Morgan                                                                 *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts                         *
 *                                                                                                  *
 ****************************************************************************************************/

#define INPUT_TXT		"FullServer.txt"
#define OUTPUT_BIN		"FullServer.bin"

#include <a_samp>
#include <sscanf2>
#include <SAM/BINLDR>

//Check Version BINLDR.inc
#if !defined _Bin_Loader
	#error You need BINLDR.inc v2.0
#elseif !defined Bin_Loader_Version
	#error Update you BINLDR.inc to v2.0
#elseif (Bin_Loader_Version < 20001)
	#error Update you BINLDR.inc to v2.0
#endif

public OnFilterScriptInit(){
	if(fexist(INPUT_TXT)){
		SaveBinaryObjectIMG(INPUT_TXT,OUTPUT_BIN);
	}
	return 1;
}

// EOF

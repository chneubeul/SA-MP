/************************************
 * Easy IMG Creator by Abyss Morgan *
 ************************************/

#define INPUT_TXT		"FullServer.txt"
#define OUTPUT_BIN		"FullServer.bin"

#include <a_samp>
#include <sscanf2>
#include <SAM/ADM>
#include <SAM/DoT>

//Check Version ADM.inc
#if !defined _adm_encryption
	#error You need ADM.inc v1.9
#elseif !defined ADM_Encryption_Version
	#error Update you ADM.inc to v1.9
#elseif (ADM_Encryption_Version < 10901)
	#error Update you ADM.inc to v1.9
#endif

//Check Version DoT.inc
#if !defined _DoT_Loader
	#error You need DoT.inc v1.2
#elseif !defined DoT_Loader_Version
	#error Update you DoT.inc to v1.2
#elseif (DoT_Loader_Version < 10201)
	#error Update you DoT.inc to v1.2
#endif

public OnFilterScriptInit(){
	if(fexist(INPUT_TXT)){
		SaveBinaryObjectIMG(INPUT_TXT,OUTPUT_BIN);
	}
	return 1;
}

// EOF

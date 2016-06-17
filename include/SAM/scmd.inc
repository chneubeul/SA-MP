/****************************************************************************************************
 *                                                                                                  *
 *                                          SScanf Command                                          *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * File Version: 1.0                                                                                *
 *                                                                                                  *
 * Callbacks:                                                                                       *
 * OnPlayerCommandReceived(playerid, cmdtext[]);                                                    *
 * OnPlayerCommandPerformed(playerid, cmdtext[], success);                                          *
 *                                                                                                  *
 ****************************************************************************************************/

#if !defined sscanf
	#tryinclude <sscanf2>
#endif

#if !defined sscanf
	#error Unknown sscanf version
#endif

#if defined _scmd_included
	#endinput
#endif
#define _scmd_included

#define CMD_SUCCESS 		(1)
#define CMD_FAILURE 		(0)

#define MAX_FUNC_NAME 		(32)
#define MAX_CMD_NAME		(27)
#define MAX_BUFFER_LEN		(128)

#define COMMAND:%1(%2)		forward cmd_%1(%2); public cmd_%1(%2)
#define CMD:%1(%2)			COMMAND:%1(%2)
#define command(%1,%2,%3)	COMMAND:%1(%2, %3)
#define cmd(%1,%2,%3) 		COMMAND:%1(%2, %3)
#define SCMD:%1(%2)			COMMAND:%1(%2)

#if !defined isnull
	#define isnull(%1)		((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

forward OnPlayerCommandReceived(playerid, cmdtext[]);
forward OnPlayerCommandPerformed(playerid, cmdtext[], success);

static bool:scmd_g_HasOPCS = false, bool:scmd_g_HasOPCE = false;

public OnFilterScriptInit(){
	scmd_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	scmd_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
	return CallLocalFunction("scmd_OnFilterScriptInit", "");
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit scmd_OnFilterScriptInit
forward scmd_OnFilterScriptInit();

public OnGameModeInit(){
	scmd_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	scmd_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
	if(funcidx("scmd_OnGameModeInit") != -1){
		return CallLocalFunction("scmd_OnGameModeInit", "");
	}
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit scmd_OnGameModeInit
forward scmd_OnGameModeInit();



public OnPlayerCommandText(playerid, cmdtext[]){
	if(scmd_g_HasOPCS && !CallLocalFunction("OnPlayerCommandReceived", "is", playerid, cmdtext)) return 1;

	static funcname[MAX_FUNC_NAME], cmd_buffer[MAX_BUFFER_LEN];
	cmd_buffer = "";
	sscanf(cmdtext,"?<SSCANF_QUIET=1>'/'s["#MAX_CMD_NAME"] s["#MAX_BUFFER_LEN"]",funcname,cmd_buffer);
	format(funcname,sizeof(funcname),"cmd_%s",funcname);
	if(!cmd_buffer[0]){
		if(scmd_g_HasOPCE) return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid, "\1"));
		return CallLocalFunction(funcname, "is", playerid, "\1");
	}
	if(scmd_g_HasOPCE) return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid, cmd_buffer));
	return CallLocalFunction(funcname, "is", playerid, cmd_buffer);
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText scmd_OnPlayerCommandText
forward scmd_OnPlayerCommandText(playerid, cmdtext[]);

//EOF
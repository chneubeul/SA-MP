/****************************************************************************************************
 *                                                                                                  *
 *                                          SScanf Command                                          *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 * Another Author: ZeeX used scheme zcmd.inc v0.3.1                                                 *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * Plugins: SScanf                                                                                  *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.1.1                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 * SScanf Version: 2.8.2                                                                            *
 *                                                                                                  *
 * Callbacks:                                                                                       *
 * OnPlayerCommandReceived(playerid,cmdtext[]);                                                     *
 * OnPlayerCommandPerformed(playerid,cmdtext[],success);                                            *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined CMD
	#endinput
#endif

#if !defined sscanf
	#tryinclude <sscanf2>
#endif

#if !defined sscanf
	#error [ADM] Unknown SScanf Version
#endif

#if defined _scmd_included
	#endinput
#endif
#define _scmd_included

/*
#if defined CMD
	#error Detected another command system
#endif
*/

#define CMD_SUCCESS 		1
#define CMD_FAILURE 		0

#define MAX_FUNC_NAME 		32
#define MAX_CMD_NAME		28
#define MAX_BUFFER_LEN		144

#define COMMAND:%1(%2)		forward cmd_%1(%2); public cmd_%1(%2)
#define CMD:%1(%2)			COMMAND:%1(%2)
#define command(%1,%2,%3)	COMMAND:%1(%2, %3)
#define cmd(%1,%2,%3) 		COMMAND:%1(%2, %3)
#define SCMD:%1(%2)			COMMAND:%1(%2)

#if !defined isnull
	#define isnull(%1)		((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if defined OnPlayerCommandReceived
	forward OnPlayerCommandReceived(playerid,cmdtext[]);
#endif
#if defined OnPlayerCommandPerformed
	forward OnPlayerCommandPerformed(playerid,cmdtext[],success);
#endif

//Hook: OnPlayerCommandText
public OnPlayerCommandText(playerid,cmdtext[]){
	#if defined OnPlayerCommandReceived
		if(!OnPlayerCommandReceived(playerid,cmdtext)) return 1;
	#endif
	
	static funcname[MAX_FUNC_NAME], cmd_buffer[MAX_BUFFER_LEN];
	cmd_buffer = "";
	sscanf(cmdtext,"?<SSCANF_QUIET=1>'/'s["#MAX_CMD_NAME"] s["#MAX_BUFFER_LEN"]",funcname,cmd_buffer);
	format(funcname,sizeof(funcname),"cmd_%s",funcname);
	if(cmd_buffer[0]){
		#if defined OnPlayerCommandPerformed
			return OnPlayerCommandPerformed(playerid,cmdtext,CallLocalFunction(funcname,"is",playerid,cmd_buffer));
		#else
			return CallLocalFunction(funcname,"is",playerid,cmd_buffer);
		#endif
	} else {
		#if defined OnPlayerCommandPerformed
			return OnPlayerCommandPerformed(playerid,cmdtext,CallLocalFunction(funcname,"is",playerid,"\1"));
		#else
			return CallLocalFunction(funcname,"is",playerid,"\1");
		#endif
	}
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText scmd_OnPlayerCommandText
forward scmd_OnPlayerCommandText(playerid,cmdtext[]);

//EOF
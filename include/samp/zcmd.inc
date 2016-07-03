/**************************************************
 *                                                *
 *   @Author:    ZeeX                             *
 *   @Version:   0.3.3                            *
 *   @Released:  31.10.2009                       *
 *   @Updated:   03.07.2016 Abyss Morgan & Yashas *
 *                                                *
 **************************************************/

#if defined _zcmd_included
	#endinput
#endif
#define _zcmd_included

#if defined CMD
	#error Detected another command system
#endif

#define CMD_SUCCESS 		1
#define CMD_FAILURE 		0

#define MAX_FUNC_NAME 		32
#define MAX_CMD_NAME		28
#define MAX_BUFFER_LEN		144

#define COMMAND:%1(%2)		forward cmd_%1(%2); public cmd_%1(%2)
#define CMD:%1(%2)			COMMAND:%1(%2)
#define command(%1,%2,%3)	COMMAND:%1(%2, %3)
#define cmd(%1,%2,%3) 		COMMAND:%1(%2, %3)

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
	static funcname[MAX_FUNC_NAME] = "cmd_";
	
	static pos;
	if((pos = strfind(cmdtext," ",false,1)) == -1){
		if((pos = strlen(cmdtext)) > MAX_CMD_NAME) pos = 1;
		strmid(funcname[4],cmdtext,1,pos,MAX_CMD_NAME);
		#if defined OnPlayerCommandPerformed
			return OnPlayerCommandPerformed(playerid,cmdtext,CallLocalFunction(funcname,"is",playerid,"\1"));
		#else
			return CallLocalFunction(funcname,"is",playerid,"\1");
		#endif
	} else {
		if(pos > MAX_CMD_NAME) pos = 1;
		strmid(funcname[4],cmdtext,1,pos,MAX_CMD_NAME);
		while(cmdtext[pos] == ' ') pos++;
		if(cmdtext[pos]){
			#if defined OnPlayerCommandPerformed
				return OnPlayerCommandPerformed(playerid,cmdtext,CallLocalFunction(funcname,"is",playerid,cmdtext[pos]));
			#else
				return CallLocalFunction(funcname,"is",playerid,cmdtext[pos]);
			#endif
		} else {
			#if defined OnPlayerCommandPerformed
				return OnPlayerCommandPerformed(playerid,cmdtext,CallLocalFunction(funcname,"is",playerid,"\1"));
			#else
				return CallLocalFunction(funcname,"is",playerid,"\1");
			#endif
		}
	}
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText zcmd_OnPlayerCommandText
forward zcmd_OnPlayerCommandText(playerid,cmdtext[]);

//EOF
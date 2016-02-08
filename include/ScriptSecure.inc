/**************************************
 * Script Secure v2.2 by Abyss Morgan *
 **************************************/

/*
//Install

//#define DONT_ALLOW_LOCALHOST	//additional option
#define FILE_SERVERIP			"127.0.0.1"
#define FILE_SERVERPORT			(7777)			
#define FILE_LICENSEID			(20160201)		//<--- YYYYMMDD 01.02.2016 (DD.MM.YYYY)
#define FILE_MAX_PLAYERS		(500)			//max players in server.cfg
#define FILE_RCONPASS			"123"			//rcon password
#define FILE_LANGUAGE			"Polish"		//server language

public OnGameModeInit(){

	AntiDeAMX();
	ScriptSecureADM();
	
	return 1;
}

public OnFilterScriptInit(){

	AntiDeAMX();
	ScriptSecureADM();
	
	return 1;
}
*/

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if !defined FILE_SERVERIP
	#error Please #define FILE_SERVERIP "127.0.0.1"
#endif

#if !defined FILE_SERVERPORT
	#error Please #define FILE_SERVERPORT (7777)
#endif

#if !defined FILE_LICENSEID
	#error Please #define FILE_LICENSEID (20160201)
#endif

#if !defined FILE_MAX_PLAYERS
	#error Please #define FILE_MAX_PLAYERS (500)
#endif

#if !defined FILE_RCONPASS
	#error Please #define FILE_RCONPASS "123"
#endif

#if !defined FILE_LANGUAGE
	#error Please #define FILE_LANGUAGE "Polish"
#endif


AntiDeAMX(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
}


ScriptSecureADM(){
	//IP and PORT check
	new serverIP[16];
	GetServerVarAsString("bind",serverIP,sizeof(serverIP));
	
	if(!strcmp(serverIP,FILE_SERVERIP,true) && !isnull(serverIP)){
		//Server IP OK
	} else {
		if(!strcmp(serverIP,"127.0.0.1",true) || !strcmp(serverIP,"localhost",true)){
			//localhost
			#if defined DONT_ALLOW_LOCALHOST
				print("[ADM] Error: This script is stolen.");
				SendRconCommand("exit");
			#else
				print("[ADM] Info: Local server detect.");
			#endif
		} else {
			print("[ADM] Error: This script is stolen.");
			SendRconCommand("exit");
		}
	}
	if(!strcmp(serverIP,"127.0.0.1",true) || !strcmp(serverIP,"localhost",true)){
		//localhost
		#if defined DONT_ALLOW_LOCALHOST
			print("[ADM] Error: This script is stolen.");
			SendRconCommand("exit");
		#endif
	} else if(GetServerVarAsInt("port") != FILE_SERVERPORT){
		print("[ADM] Error: This script is stolen.");
		SendRconCommand("exit");
	}

	//Date Check
	new tmpdate, tmpyear, tmpmonth, tmpday;
	getdate(tmpyear,tmpmonth,tmpday);
	tmpdate = (10000*tmpyear)+(100*tmpmonth)+tmpday;
	if(tmpdate > FILE_LICENSEID){
		print("[ADM] Error: Script license has expired.");
		SendRconCommand("exit");
	}

	//Check server.cfg
	if(GetMaxPlayers() != FILE_MAX_PLAYERS){
		print("[ADM] Error: Invalid server config, check your max players.");
		SendRconCommand("exit");
	}
	
	new rtemp[32];
	GetServerVarAsString("rcon_password",rtemp,sizeof(rtemp));
	if(strcmp(rtemp,FILE_RCONPASS,false) != 0){
		print("[ADM] Error: Invalid server config, check your rcon password.");
		SendRconCommand("exit");
	}
	rtemp = "";
	
	GetServerVarAsString("language",rtemp,sizeof(rtemp));
	if(strcmp(rtemp,FILE_LANGUAGE,false) != 0 || isnull(rtemp)){
		print("[ADM] Error: Invalid server config, check your language.");
		SendRconCommand("exit");
	}
	rtemp = "";
}

#undef FILE_SERVERIP
#undef FILE_SERVERPORT
#undef FILE_LICENSEID
#undef FILE_MAX_PLAYERS
#undef FILE_RCONPASS
#undef FILE_LANGUAGE

//EOF
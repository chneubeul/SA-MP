/****************************************************************************************************
 *                                                                                                  *
 * Script Secure v2.2 made by Abyss Morgan                                                          *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include                               *
 *                                                                                                  *
 ****************************************************************************************************/

/*
//Install

//#define DONT_ALLOW_LOCALHOST	//additional option
//#define CHECK_MAX_PLAYERS		//additional option
//#define CHECK_RCON_PASSWORD	//additional option
//#define CHECK_SERVER_LANGUAGE	//additional option

#define FILE_tmpserverIP			"127.0.0.1"
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

#if !defined FILE_tmpserverIP
	#error Please #define FILE_tmpserverIP "127.0.0.1"
#endif

#if !defined FILE_SERVERPORT
	#error Please #define FILE_SERVERPORT (7777)
#endif

#if !defined FILE_LICENSEID
	#error Please #define FILE_LICENSEID (20160201)
#endif

#if defined CHECK_MAX_PLAYERS
	#if !defined FILE_MAX_PLAYERS
		#error Please #define FILE_MAX_PLAYERS (500)
	#endif
#endif

#if defined CHECK_RCON_PASSWORD
	#if !defined FILE_RCONPASS
		#error Please #define FILE_RCONPASS "123"
	#endif
#endif

#if defined CHECK_SERVER_LANGUAGE
	#if !defined FILE_LANGUAGE
		#error Please #define FILE_LANGUAGE "Polish"
	#endif
#endif

AntiDeAMX(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
}


ScriptSecureADM(){
	//IP and PORT check
	new tmpserverIP[16];
	GetServerVarAsString("bind",tmpserverIP,sizeof(tmpserverIP));
	
	if(!strcmp(tmpserverIP,FILE_tmpserverIP,true) && !isnull(tmpserverIP)){
		//Server IP OK
	} else {
		if(!strcmp(tmpserverIP,"127.0.0.1",true) || !strcmp(tmpserverIP,"localhost",true)){
			//localhost
			#if defined DONT_ALLOW_LOCALHOST
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Error: This script is stolen.");
				}
				SendRconCommand("exit");
				return 0;
			#else
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Info: Local server detect.");
				}
			#endif
		} else {
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: This script is stolen.");
			}
			SendRconCommand("exit");
			return 0;
		}
	}
	if(!strcmp(tmpserverIP,"127.0.0.1",true) || !strcmp(tmpserverIP,"localhost",true)){
		//localhost
		#if defined DONT_ALLOW_LOCALHOST
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: This script is stolen.");
			}
			SendRconCommand("exit");
			return 0;
		#endif
	} else if(GetServerVarAsInt("port") != FILE_SERVERPORT){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: This script is stolen.");
		}
		SendRconCommand("exit");
		return 0;
	}

	//Date Check
	new tmpdate, tmpyear, tmpmonth, tmpday;
	getdate(tmpyear,tmpmonth,tmpday);
	tmpdate = (10000*tmpyear)+(100*tmpmonth)+tmpday;
	if(tmpdate > FILE_LICENSEID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: Script license has expired.");
		}
		SendRconCommand("exit");
		return 0;
	}

	//Check server.cfg
	#if defined CHECK_MAX_PLAYERS
		if(GetMaxPlayers() != FILE_MAX_PLAYERS){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: Invalid server config, check your max players.");
			}
			SendRconCommand("exit");
			return 0;
		}
	#endif
	
	new rtemp[32];
	
	#if defined CHECK_RCON_PASSWORD
		GetServerVarAsString("rcon_password",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,FILE_RCONPASS,false) != 0){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: Invalid server config, check your rcon password.");
			}
			SendRconCommand("exit");
			return 0;
		}
		rtemp = "";
	#endif
	
	#if defined CHECK_SERVER_LANGUAGE
		GetServerVarAsString("language",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,FILE_LANGUAGE,false) != 0 || isnull(rtemp)){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: Invalid server config, check your language.");
			}
			SendRconCommand("exit");
			return 0;
		}
		rtemp = "";
	#endif
	
	#pragma unused rtemp
	return 1;
}

#undef FILE_tmpserverIP
#undef FILE_SERVERPORT
#undef FILE_LICENSEID

#if defined FILE_MAX_PLAYERS
	#undef FILE_MAX_PLAYERS
#endif

#if defined FILE_RCONPASS
	#undef FILE_RCONPASS
#endif

#if defined FILE_LANGUAGE
	#undef FILE_LANGUAGE
#endif

//EOF
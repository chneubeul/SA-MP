/**************************************
 * Script Secure v2.1 by Abyss Morgan *
 **************************************/

/*
//Install
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
 
#define FILE_SERVERIP			"127.0.0.1"
#define FILE_SERVERPORT			(7777)			
#define FILE_LICENSEID			(20160201)		//<--- YYYYMMDD 01.02.2016 (DD.MM.YYYY)
#define FILE_MAX_PLAYERS		(500)			//max players in server.cfg
#define FILE_RCONPASS			"123"			//rcon password
#define FILE_LANGUAGE			"Polish"		//server language

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

AntiDeAMX(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
}


ScriptSecureADM(){
	//IP and PORT check
	new serverIP[16];
	GetServerVarAsString("bind",serverIP,sizeof(serverIP));
	
	if(!strcmp(serverIP,FILE_SERVERIP,true)){
		//Server IP OK
	} else {
		if(!strcmp(serverIP,"127.0.0.1",true) || !strcmp(serverIP,"localhost",true)){
			//localhost
			print("[ADM] Info: Local Server Detect.");
		} else {
			print("[ADM] Error: This script is stolen.");
			SendRconCommand("exit");
		}
	}
	if(!strcmp(serverIP,"127.0.0.1",true) || !strcmp(serverIP,"localhost",true)){
		//localhost
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
		print("[ADM] Error: Invalid Server Config.");
		SendRconCommand("exit");
	}
	
	new rtemp[32];
	GetServerVarAsString("rcon_password",rtemp,sizeof(rtemp));
	if(strcmp(rtemp,FILE_RCONPASS,false)!=0 || isnull(rtemp)){
		print("[ADM] Error: Invalid Server Config.");
		SendRconCommand("exit");
	}
	rtemp = "";
	#undef FILE_RCONPASS
	
	GetServerVarAsString("language",rtemp,sizeof(rtemp));
	if(strcmp(rtemp,FILE_LANGUAGE,false)!=0 || isnull(rtemp)){
		print("[ADM] Error: Invalid Server Config.");
		SendRconCommand("exit");
	}
	rtemp = "";
	#undef FILE_LANGUAGE
}

//EOF
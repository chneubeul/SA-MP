/**************************************
 * Script Secure v3.0 by Abyss Morgan *
 **************************************/

/*
//Install

//#define CHECK_MAX_PLAYERS		//additional option
//#define CHECK_RCON_PASSWORD	//additional option
//#define CHECK_SERVER_LANGUAGE	//additional option

Add server information to ADMServerList

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

enum e_server_config {
	ADM_ServerIP[16],
	ADM_ServerPort,
	ADM_LicenseID,
	ADM_MaxPlayers,
	ADM_RconPassword[32],
	ADM_Language[32]
}

/*
IP - string
PORT - integer value
LicenseID - integer value //YYYYMMDD
MaxPlayers - integer value
RconPassword - string
Language - string
*/

//IP Port LicenseID MaxPlayers RconPassword Language
new ADMServerList[][e_server_config] = {
	{ "127.0.0.1", 7777, 20160201, 500, "123", "Polish" },
	{ "127.0.0.1", 7778, 20170201, 500, "123", "English" }
};


#define INVALID_SERVERID		(-1)

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

FindServerID(){
	new serverIP[16], serverPort = GetServerVarAsInt("port");
	GetServerVarAsString("bind",serverIP,sizeof(serverIP));
	for(new i = 0, j = sizeof(ADMServerList); i < j; i++){
		if(!strcmp(serverIP,ADMServerList[i][ADM_ServerIP],true) && !isnull(serverIP)){
			if(serverPort == ADMServerList[i][ADM_ServerPort]){
				return i;
			}
		}
	}
	return INVALID_SERVERID;
}

AntiDeAMX(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
}


ScriptSecureADM(){

	//IP and PORT check
	new sid = FindServerID();
	if(sid == INVALID_SERVERID){
		print("[ADM] Error: This script is stolen.");
		SendRconCommand("exit");
		return 0;
	}

	//Date Check
	new tmpdate, tmpyear, tmpmonth, tmpday;
	getdate(tmpyear,tmpmonth,tmpday);
	tmpdate = (10000*tmpyear)+(100*tmpmonth)+tmpday;
	if(tmpdate > ADMServerList[sid][ADM_LicenseID]){
		print("[ADM] Error: Script license has expired.");
		SendRconCommand("exit");
		return 0;
	}

	//Check server.cfg
	#if defined CHECK_MAX_PLAYERS
		if(GetMaxPlayers() != ADMServerList[sid][ADM_MaxPlayers]){
			print("[ADM] Error: Invalid server config, check your max players.");
			SendRconCommand("exit");
			return 0;
		}
	#endif
	
	new rtemp[32];
	
	#if defined CHECK_RCON_PASSWORD
		GetServerVarAsString("rcon_password",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,ADMServerList[sid][ADM_RconPassword],false) != 0){
			print("[ADM] Error: Invalid server config, check your rcon password.");
			SendRconCommand("exit");
			return 0;
		}
		rtemp = "";
	#endif
	
	#if defined CHECK_SERVER_LANGUAGE
		GetServerVarAsString("language",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,ADMServerList[sid][ADM_Language],false) != 0 || isnull(rtemp)){
			print("[ADM] Error: Invalid server config, check your language.");
			SendRconCommand("exit");
			return 0;
		}
		rtemp = "";
	#endif
	
	#pragma unused rtemp
	return 1;
}
//EOF
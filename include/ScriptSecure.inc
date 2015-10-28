

#define FILE_SERVERIP			"127.0.0.1"
#define FILE_SERVERPORT			(7777)			
#define FILE_LICENSEID			(20160201)		//01.02.2016
#define FILE_MAX_PLAYERS		(500)			//max players in server.cfg
#define FILE_RCONPASS			"123"			//rcon password
#define FILE_LANGUAGE			"Polish"		//server language

#if !defined isnull
	#define isnull(%1) \
				((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

AntiDeAMX(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
}


ADM(){
	//IP and PORT check
	new serverIP[16];
	GetServerVarAsString("bind",serverIP,sizeof(serverIP));
	if(strcmp(serverIP,FILE_SERVERIP,false)!=0 || isnull(serverIP)){
		if((strcmp(serverIP,"127.0.0.1",false)!=0) || (strcmp(serverIP,"localhost",false)!=0) || isnull(serverIP)){
			print("ADM: Local Server Detect !");
		} else {
			print("ADM: This script is stolen !");
			SendRconCommand("exit");
		}
	} else if(GetServerVarAsInt("port") != FILE_SERVERPORT){
		print("ADM: This script is stolen !");
		SendRconCommand("exit");
	}

	//Date Check
	new tmpdate, tmpyear, tmpmonth, tmpday;
	getdate(tmpyear,tmpmonth,tmpday);
	tmpdate = (10000*tmpyear)+(100*tmpmonth)+tmpday;
	if(tmpdate > FILE_LICENSEID){
		print("ADM: Script license has expired !");
		SendRconCommand("exit");
	}

	//Check server.cfg
	if(GetMaxPlayers() != FILE_MAX_PLAYERS){
		print("ADM: Error check server.cfg !");
		SendRconCommand("exit");
	}
	
	new rtemp[32];
	GetServerVarAsString("rcon_password",rtemp,sizeof(rtemp));
	if(strcmp(rtemp,FILE_RCONPASS,false)!=0 || isnull(rtemp)){
		print("ADM: Error check server.cfg !");
		SendRconCommand("exit");
	}
	rtemp = "";
	#undef FILE_RCONPASS
	
	GetServerVarAsString("language",rtemp,sizeof(rtemp));
	if(strcmp(rtemp,FILE_LANGUAGE,false)!=0 || isnull(rtemp)){
		print("ADM: Error check server.cfg !");
		SendRconCommand("exit");
	}
	rtemp = "";
	#undef FILE_LANGUAGE
}





public OnGameModeInit(){

	AntiDeAMX();
	ADM();
	
	return 1;
}

public OnFilterScriptInit(){

	AntiDeAMX();
	ADM();
	
	return 1;
}
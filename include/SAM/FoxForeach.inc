/****************************************************************************************************
 *                                                                                                  *
 *                                           FoX Foreach                                            *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * File Version: 1.1                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * FoxForeach(variable);                                                                            *
 * CountFoxPlayer();                                                                                *
 * FoxForeachRandomPlayer();                                                                        *
 * bool:IsPlayerInFoxPool(playerid);                                                                *
 *                                                                                                  *
 * Extended functions:                                                                              *
 * foX(variable,beginning,end);                                                                     *
 * foreach(variable);                                                                               *
 *                                                                                                  *
 * Auto functions:                                                                                  *
 * bool:FoxAddPlayer(playerid);                                                                     *
 * bool:FoxRemovePlayer(playerid);                                                                  *
 * FoxForeachInit();                                                                                *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _FoX_Foreach
	#endinput
#endif
#define _FoX_Foreach

#define FoxForeach(%0)					for(new %0 = FoxPlayers[0], i_%0 = 0; i_%0 <= FoxUpperbound; i_%0++, %0 = FoxPlayers[i_%0])
#define CountFoxPlayer()				(FoxUpperbound+1)

#define foX(%1,%2,%3)					for(new %1 = %2; %1 <= %3; %1++)

#if !defined foreach
	#define foreach(%1)					for(new %1 = 0, p_%1 = GetPlayerPoolSize(); %1 <= p_%1; %1++)
#endif

new FoxPlayers[MAX_PLAYERS],
	FoxUpperbound = -1;

stock bool:IsPlayerInFoxPool(playerid){
	for(new i = 0; i <= FoxUpperbound; i++){
		if(FoxPlayers[i] == playerid){
			return true;
		}
	}
	return false;
}

stock bool:FoxAddPlayer(playerid){
	if(IsPlayerInFoxPool(playerid)) return false;
	FoxUpperbound++;
	FoxPlayers[FoxUpperbound] = playerid;
	return true;
}

stock FoxForeachRandomPlayer(){
	if(FoxUpperbound == -1) return 0;
	new playerid = FoxPlayers[random(FoxUpperbound+1)];
	if(IsPlayerConnected(playerid)) return playerid;
	return 0;
}

stock FoxForeachInit(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i)){
			FoxAddPlayer(i);
		}
	}
	return 1;
}

stock bool:FoxRemovePlayer(playerid){
	if(!IsPlayerInFoxPool(playerid)) return false;
	for(new i = 0; i <= FoxUpperbound; i++){
		if(FoxPlayers[i] == playerid){
			if(FoxUpperbound == 0){
				FoxPlayers[i] = 0;
			} else if(i == FoxUpperbound){
				FoxPlayers[i] = 0;
			} else {
				FoxPlayers[i] = FoxPlayers[FoxUpperbound];
				FoxPlayers[FoxUpperbound] = 0;
			}
			FoxUpperbound--;
			break;
		}
	}
	return true;
}

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	FoxForeachInit();
	#if defined FoX_OnFilterScriptInit
		FoX_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit FoX_OnFilterScriptInit
#if defined FoX_OnFilterScriptInit
	forward FoX_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	FoxForeachInit();
	#if defined FoX_OnGameModeInit
		FoX_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FoX_OnGameModeInit
#if defined FoX_OnGameModeInit
	forward FoX_OnGameModeInit();
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	FoxRemovePlayer(playerid);
	#if defined FoX_OnPlayerDisconnect
		FoX_OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect FoX_OnPlayerDisconnect
#if defined FoX_OnPlayerDisconnect
	forward FoX_OnPlayerDisconnect(playerid,reason);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	FoxAddPlayer(playerid);
	#if defined FoX_OnPlayerConnect
		FoX_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect FoX_OnPlayerConnect
#if defined FoX_OnPlayerConnect
	forward FoX_OnPlayerConnect(playerid);
#endif

//EOF
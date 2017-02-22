/****************************************************************************************************
 *                                                                                                  *
 *                                        Knife Shoot Script                                        *
 *                                                                                                  *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                        *
 * Publication: http://forum.sa-mp.com/showthread.php?t=599773                                      *
 *                                                                                                  *
 * Plugins: Streamer, ColAndreas                                                                    *
 * Modules: 3DTryg                                                                                  *
 * Attributes: None                                                                                 *
 *                                                                                                  *
 * File Version: 2.5.0                                                                              *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                   *
 * Streamer Version: 2.8.2                                                                          *
 * ColAndreas Version: 1.4.0                                                                        *
 * 3DTryg Version: 4.0.2                                                                            *
 *                                                                                                  *
 * Functions:                                                                                       *
 * ToggleUseTeamKnifeShoot(bool:toggle);            //default: false                                *
 * bool:IsToggleUseTeamKnifeShoot();                                                                *
 * ToggleKnifeShootForAll(bool:toggle);             //default: true                                 *
 * bool:IsToggleKnifeShootForAll();                                                                 *
 * ToggleKnifeShootForPlayer(playerid,bool:toggle); //default: false                                *
 * bool:IsToggleKnifeShootForPlayer(playerid);                                                      *
 * Float:GetKnifeShootDamage(playerid);                                                             *
 * SetKnifeShootDamage(playerid,Float:amount);                                                      *
 * Float:GetKnifeShootSpeed(playerid);                                                              *
 * SetKnifeShootSpeed(playerid,Float:speed);                                                        *
 * Float:GetKnifeShootRange(playerid);                                                              *
 * SetKnifeShootRange(playerid,Float:range);                                                        *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _knife_shot
	#endinput
#endif
#define _knife_shot

#if (!defined GetPlayerPoolSize)
	#error [ADM] This include requires SA:MP version 0.3.7
#endif

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

#if !defined COLANDREAS
	#error [ADM] Unknown ColAndreas Version
#endif


//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v4.0.2
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#elseif (Tryg3D_Version < 40002)
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#endif

#define KNIFE_SPEED 						(12.0)
#define KNIFE_MAX_RADIUS					(15.0)
#define KNIFE_REFRESH_ACTION				(1000)	//1 sec
#define KNIFE_REFRESH_MISS					(5000)	//5 sec
#define KNIFE_DAMAGE						(10.0)

new KnifeLockTarget[MAX_PLAYERS],
	KnifeStep[MAX_PLAYERS],
	KnifeTime[MAX_PLAYERS],
	Float:KnifeShootDamage[MAX_PLAYERS],
	Float:KnifeShootSpeed[MAX_PLAYERS],
	Float:KnifeShootRange[MAX_PLAYERS],
	bool:KnifeEnabledForPlayer[MAX_PLAYERS],
	bool:KnifeEnabledForAll = true,
	bool:KnifeUsePlayerTeam = false;

#define ToggleUseTeamKnifeShoot(%0)			KnifeUsePlayerTeam = (%0)
#define IsToggleUseTeamKnifeShoot()			KnifeUsePlayerTeam
#define ToggleKnifeShootForAll(%0)			KnifeEnabledForAll = (%0)
#define IsToggleKnifeShootForAll()			KnifeEnabledForAll
#define ToggleKnifeShootForPlayer(%0,%1)	KnifeEnabledForPlayer[(%0)] = (%1)
#define IsToggleKnifeShootForPlayer(%0)		KnifeEnabledForPlayer[(%0)]
#define GetKnifeShootDamage(%0)				KnifeShootDamage[(%0)]
#define SetKnifeShootDamage(%0,%1)			KnifeShootDamage[(%0)] = (%1)
#define GetKnifeShootSpeed(%0)				KnifeShootSpeed[(%0)]
#define SetKnifeShootSpeed(%0,%1)			KnifeShootSpeed[(%0)] = (%1)
#define GetKnifeShootRange(%0)				KnifeShootRange[(%0)]
#define SetKnifeShootRange(%0,%1)			KnifeShootRange[(%0)] = (%1)

T3D:function KnifeShot(playerid){
	new Vec[LongFloat3D], mtime, pteam, Float:ldist = 20000;
	GetPlayerPos(playerid,Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z]);
	GetPlayerFacingAngle(playerid,Vec[T3D:rZ]);
	Vec[T3D:VW] = GetPlayerVirtualWorld(playerid);
	Vec[T3D:INT] = GetPlayerInterior(playerid);
	GetPointInFront2D(Vec[T3D:X],Vec[T3D:Y],Vec[T3D:rZ],GetKnifeShootRange(playerid),Vec[T3D:tX],Vec[T3D:tY]);
	KnifeLockTarget[playerid] = INVALID_PLAYER_ID;
	pteam = GetPlayerTeam(playerid);
	
	Tryg3DForeach(i){
		if(i != playerid){
			if(IsPlayerConnected(i)){
				if(!IsToggleUseTeamKnifeShoot() || (IsToggleUseTeamKnifeShoot() && (pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM))){
					if(Tryg3D_IsPlayerSpawned(i)){
						GetPlayerPos(i,Vec[T3D:VecX],Vec[T3D:VecY],Vec[T3D:VecZ]);
						if(GetPlayerVirtualWorld(i) == Vec[T3D:VW] && GetPlayerInterior(i) == Vec[T3D:INT]){
							if(IsPointInCylinder3D(Vec[T3D:VecX],Vec[T3D:VecY],Vec[T3D:VecZ],Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z],Vec[T3D:tX],Vec[T3D:tY],Vec[T3D:tZ],2.0)){
								if(!IsBetweenElementsIsWall(playerid,item_player,i,item_player)){
									new Float:dist = GetDistanceBetweenPoints3D(Vec[T3D:VecX],Vec[T3D:VecY],Vec[T3D:VecZ],Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z]);
									if(dist < ldist){
										ldist = dist;
										KnifeLockTarget[playerid] = i;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	if(KnifeLockTarget[playerid] == INVALID_PLAYER_ID){
		CompRotationFloat(Vec[T3D:rZ]+90.0,Vec[T3D:trZ]);
		new tmpobj = CreateDynamicObject(335,Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z],0.0,90.0,Vec[T3D:trZ],Vec[T3D:VW],Vec[T3D:INT],-1);
		GetPointInFront3DCol(Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z],356.7,Vec[T3D:rZ],GetKnifeShootRange(playerid),Vec[T3D:tX],Vec[T3D:tY],Vec[T3D:tZ]);		
		GetMoveTime(Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z],Vec[T3D:tX],Vec[T3D:tY],Vec[T3D:tZ],GetKnifeShootSpeed(playerid),mtime);
		MoveDynamicObject(tmpobj,Vec[T3D:tX],Vec[T3D:tY],Vec[T3D:tZ],GetKnifeShootSpeed(playerid),0.0,110.0,Vec[T3D:trZ]);
		SetTimerEx("KnifeDestroy",mtime+KNIFE_REFRESH_MISS,0,"ddd",tmpobj,INVALID_PLAYER_ID,playerid);
	} else {
		GetPlayerPos(KnifeLockTarget[playerid],Vec[T3D:VecX],Vec[T3D:VecY],Vec[T3D:VecZ]);
		GetRotationFor2Point2D(Vec[T3D:X],Vec[T3D:Y],Vec[T3D:VecX],Vec[T3D:VecY],Vec[T3D:trZ]);
		CompRotationFloat(Vec[T3D:trZ]+90.0,Vec[T3D:trZ]);
		new tmpobj = CreateDynamicObject(335,Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z],0.0,90.0,Vec[T3D:trZ],Vec[T3D:VW],Vec[T3D:INT],-1);
		GetMoveTime(Vec[T3D:X],Vec[T3D:Y],Vec[T3D:Z],Vec[T3D:VecX],Vec[T3D:VecY],Vec[T3D:VecZ],GetKnifeShootSpeed(playerid),mtime);
		MoveDynamicObject(tmpobj,Vec[T3D:VecX],Vec[T3D:VecY],Vec[T3D:VecZ],GetKnifeShootSpeed(playerid),0.0,90.0,Vec[T3D:trZ]);
		SetTimerEx("KnifeDestroy",mtime,0,"ddd",tmpobj,KnifeLockTarget[playerid],playerid);
	}
	KnifeTime[playerid] = GetTickCount();
	return 1;
}

T3D:function KnifeDestroy(objectid,targetid,playerid){
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	if(targetid != INVALID_PLAYER_ID){
		Tryg3D_GivePlayerDamage(targetid,GetKnifeShootDamage(playerid),playerid,4,3);
		ApplyAnimation(targetid,"ped","SHOT_partial",4.1,0,1,1,1,1,1);
	}
	return 1;
}

T3D:function KnifeInit(){
	for(new i = 0; i < MAX_PLAYERS; i++){
		SetKnifeShootDamage(i,KNIFE_DAMAGE);
		SetKnifeShootSpeed(i,KNIFE_SPEED);
		SetKnifeShootRange(i,KNIFE_MAX_RADIUS);
	}
}

new CRC_KnifeInit = true;

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(IsToggleKnifeShootForAll() || IsToggleKnifeShootForPlayer(playerid)){
		if(GetTickCount()-KnifeTime[playerid] >= KNIFE_REFRESH_ACTION){
			if(GetPlayerWeapon(playerid) == 4){
				if(newkeys == KEY_FIRE && KnifeStep[playerid] == 1){
					KnifeStep[playerid] = 0;
					KnifeShot(playerid);
				}
				if(newkeys == KEY_HANDBRAKE && KnifeStep[playerid] == 0){
					KnifeStep[playerid] = 1;
				}
			}
		}
	}
	#if defined Knife_OnPlayerKeyStateChange
		Knife_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange Knife_OnPlayerKeyStateChange
#if defined Knife_OnPlayerKeyStateChange
	forward Knife_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_KnifeInit){
		CRC_KnifeInit = false;
		KnifeInit();
	}
	#if defined Knife_OnFilterScriptInit
		Knife_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Knife_OnFilterScriptInit
#if defined Knife_OnFilterScriptInit
	forward Knife_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_KnifeInit){
		CRC_KnifeInit = false;
		KnifeInit();
	}
	#if defined Knife_OnGameModeInit
		Knife_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Knife_OnGameModeInit
#if defined Knife_OnGameModeInit
	forward Knife_OnGameModeInit();
#endif

//EOF
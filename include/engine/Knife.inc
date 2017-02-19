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
 * File Version: 2.4.0                                                                              *
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
	bool:KnifeEnabledForPlayer[MAX_PLAYERS],
	bool:KnifeEnabledForAll = true,
	bool:KnifeUsePlayerTeam = false;

#define ToggleUseTeamKnifeShoot(%0)			KnifeUsePlayerTeam = (%0)
#define IsToggleUseTeamKnifeShoot()			(KnifeUsePlayerTeam)
#define ToggleKnifeShootForAll(%0)			KnifeEnabledForAll = (%0)
#define IsToggleKnifeShootForAll()			(KnifeEnabledForAll)
#define ToggleKnifeShootForPlayer(%0,%1)	KnifeEnabledForPlayer[(%0)] = (%1)
#define IsToggleKnifeShootForPlayer(%0)		(KnifeEnabledForPlayer[(%0)])

forward KnifeShot(playerid);
forward KnifeDestroy(objectid,targetid,playerid);

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

public KnifeShot(playerid){
	new Float:mx, Float:my, Float:mz, Float:mrz, Float:mtx, Float:mty, Float:mtz, mvw, mint, Float:trz,
		Float:px, Float:py, Float:pz, pvw, pint, mtime, pteam;
	GetPlayerPos(playerid,mx,my,mz);
	GetPlayerFacingAngle(playerid,mrz);
	mvw = GetPlayerVirtualWorld(playerid);
	mint = GetPlayerInterior(playerid);
	GetPointInFront2D(mx,my,mrz,KNIFE_MAX_RADIUS,mtx,mty);
	KnifeLockTarget[playerid] = INVALID_PLAYER_ID;
	new Float:ldist = 20000;
	pteam = GetPlayerTeam(playerid);
	
	Tryg3DForeach(i){
		if(i != playerid){
			if(IsPlayerConnected(i)){
				if(!IsToggleUseTeamKnifeShoot() || (IsToggleUseTeamKnifeShoot() && (pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM))){
					if(Tryg3D_IsPlayerSpawned(i)){
						GetPlayerPos(i,px,py,pz);
						pvw = GetPlayerVirtualWorld(i);
						pint = GetPlayerInterior(i);
						if(pvw == mvw && pint == mint){
							if(IsPointInCylinder3D(px,py,pz, mx,my,mz, mtx,mty,mz, 2.0)){
								if(!IsBetweenElementsIsWall(playerid,item_player,i,item_player)){
									new Float:dist = GetDistanceBetweenPoints3D(px,py,pz,mx,my,mz);
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
		CompRotationFloat(mrz+90.0,trz);
		new tmpobj = CreateDynamicObject(335,mx,my,mz,0.0,90.0,trz,mvw,mint,-1);
		GetPointInFront3DCol(mx,my,mz,356.7,mrz,KNIFE_MAX_RADIUS,mtx,mty,mtz);		
		GetMoveTime(mx,my,mz,mtx,mty,mtz,KNIFE_SPEED,mtime);
		MoveDynamicObject(tmpobj,mtx,mty,mtz,KNIFE_SPEED,0.0,110.0,trz);
		SetTimerEx("KnifeDestroy",mtime+KNIFE_REFRESH_MISS,0,"ddd",tmpobj,INVALID_PLAYER_ID,playerid);
	} else {
		GetPlayerPos(KnifeLockTarget[playerid],px,py,pz);
		pvw = GetPlayerVirtualWorld(KnifeLockTarget[playerid]), pint = GetPlayerInterior(KnifeLockTarget[playerid]);
		GetRotationFor2Point2D(mx,my,px,py,trz);
		CompRotationFloat(trz+90.0,trz);
		new tmpobj = CreateDynamicObject(335,mx,my,mz,0.0,90.0,trz,mvw,mint,-1);
		GetMoveTime(mx,my,mz,px,py,pz,KNIFE_SPEED,mtime);
		MoveDynamicObject(tmpobj,px,py,pz,KNIFE_SPEED,0.0,90.0,trz);
		SetTimerEx("KnifeDestroy",mtime,0,"ddd",tmpobj,KnifeLockTarget[playerid],playerid);
	}
	KnifeTime[playerid] = GetTickCount();
	return 1;
}

public KnifeDestroy(objectid,targetid,playerid){
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	if(targetid != INVALID_PLAYER_ID){
		Tryg3D_GivePlayerDamage(targetid,KNIFE_DAMAGE,playerid,4,3);
		ApplyAnimation(targetid,"ped","SHOT_partial",4.1,0,1,1,1,1,1);
	}
	return 1;
}

//EOF
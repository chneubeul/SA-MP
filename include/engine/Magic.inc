/****************************************************************************************************
 *                                                                                                  *
 *                                        Magic Shoot Script                                        *
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
 * File Version: 1.0.0                                                                              *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                   *
 * Streamer Version: 2.8.2                                                                          *
 * ColAndreas Version: 1.4.0                                                                        *
 * 3DTryg Version: 4.0.2                                                                            *
 *                                                                                                  *
 * Functions:                                                                                       *
 * ToggleUseTeamMagicShoot(bool:toggle);            //default: false                                *
 * bool:IsToggleUseTeamMagicShoot();                                                                *
 * ToggleMagicShootForAll(bool:toggle);             //default: false                                *
 * bool:IsToggleMagicShootForAll();                                                                 *
 * ToggleMagicShootForPlayer(playerid,bool:toggle); //default: false                                *
 * bool:IsToggleMagicShootForPlayer(playerid);                                                      *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _magic_shot
	#endinput
#endif
#define _magic_shot

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

#define MAGIC_SPEED 						(12.0)
#define MAGIC_MAX_RADIUS					(15.0)
#define MAGIC_REFRESH_ACTION				(1000)	//1 sec
#define MAGIC_DAMAGE						(10.0)

new MagicLockTarget[MAX_PLAYERS],
	MagicTime[MAX_PLAYERS],
	bool:MagicEnabledForPlayer[MAX_PLAYERS],
	bool:MagicEnabledForAll = false,
	bool:MagicUsePlayerTeam = false;

#define ToggleUseTeamMagicShoot(%0)			MagicUsePlayerTeam = (%0)
#define IsToggleUseTeamMagicShoot()			(MagicUsePlayerTeam)
#define ToggleMagicShootForAll(%0)			MagicEnabledForAll = (%0)
#define IsToggleMagicShootForAll()			(MagicEnabledForAll)
#define IsToggleMagicShootForPlayer(%0)		(MagicEnabledForPlayer[(%0)])

stock ToggleMagicShootForPlayer(playerid,bool:toggle){
	MagicEnabledForPlayer[playerid] = toggle;
	if(toggle){
		ResetPlayerWeapons(playerid);
		SetPlayerAttachedObject(playerid,7,338,6,0.080000,-0.010000,0.000000,0.000000,353.134094,65.000000,0.300000,0.300000,0.300000);
	} else {
		RemovePlayerAttachedObject(playerid,7);
	}
}

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(IsToggleMagicShootForAll() || IsToggleMagicShootForPlayer(playerid)){
		if(GetTickCount()-MagicTime[playerid] >= MAGIC_REFRESH_ACTION){
			if(Tryg3D_KeyPressed(KEY_FIRE)){
				MagicShot(playerid);
			}
		}
	}
	#if defined Magic_OnPlayerKeyStateChange
		Magic_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange Magic_OnPlayerKeyStateChange
#if defined Magic_OnPlayerKeyStateChange
	forward Magic_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

T3D:function MagicShot(playerid){
	new Float:mx, Float:my, Float:mz, Float:mrz, Float:mtx, Float:mty, Float:mtz, mvw, mint,
		Float:px, Float:py, Float:pz, pvw, pint, mtime, pteam;
	GetPlayerPos(playerid,mx,my,mz);
	GetPlayerFacingAngle(playerid,mrz);
	mvw = GetPlayerVirtualWorld(playerid);
	mint = GetPlayerInterior(playerid);
	GetPointInFront2D(mx,my,mrz,MAGIC_MAX_RADIUS,mtx,mty);
	MagicLockTarget[playerid] = INVALID_PLAYER_ID;
	new Float:ldist = 20000;
	pteam = GetPlayerTeam(playerid);
	
	Tryg3DForeach(i){
		if(i != playerid){
			if(IsPlayerConnected(i)){
				if(!IsToggleUseTeamMagicShoot() || (IsToggleUseTeamMagicShoot() && (pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM))){
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
										MagicLockTarget[playerid] = i;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	ApplyAnimation(playerid,"KNIFE","knife_3",4.1,0,1,1,0,0,1);
	if(MagicLockTarget[playerid] == INVALID_PLAYER_ID){
		new tmpobj = CreateDynamicObject(18693,mx,my,mz,90.0,0.0,mrz,mvw,mint,-1,_,100.0);
		GetPointInFront3DCol(mx,my,mz,0.0,mrz,MAGIC_MAX_RADIUS,mtx,mty,mtz);		
		GetMoveTime(mx,my,mz,mtx,mty,mtz,MAGIC_SPEED,mtime);
		MoveDynamicObject(tmpobj,mtx,mty,mtz,MAGIC_SPEED,90.0,0.0,mrz);
		SetTimerEx("MagicDestroy",mtime,0,"ddd",tmpobj,INVALID_PLAYER_ID,playerid);
	} else {
		GetPlayerPos(MagicLockTarget[playerid],px,py,pz);
		pvw = GetPlayerVirtualWorld(MagicLockTarget[playerid]), pint = GetPlayerInterior(MagicLockTarget[playerid]);
		GetRotationFor2Point2D(mx,my,px,py,mrz);
		new tmpobj = CreateDynamicObject(18693,mx,my,mz,90.0,0.0,mrz,mvw,mint,-1,_,100.0);
		GetMoveTime(mx,my,mz,px,py,pz,MAGIC_SPEED,mtime);
		MoveDynamicObject(tmpobj,px,py,pz,MAGIC_SPEED,90.0,0.0,mrz);
		SetTimerEx("MagicDestroy",mtime,0,"ddd",tmpobj,MagicLockTarget[playerid],playerid);
	}
	MagicTime[playerid] = GetTickCount();
	return 1;
}

T3D:function MagicDestroy(objectid,targetid,playerid){
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	if(targetid != INVALID_PLAYER_ID){
		Tryg3D_GivePlayerDamage(targetid,MAGIC_DAMAGE,playerid,7,3);
		ApplyAnimation(targetid,"ped","SHOT_partial",4.1,0,1,1,1,1,1);
	}
	return 1;
}

//EOF
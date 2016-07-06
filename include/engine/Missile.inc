/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                        Missile Launcher                                                        *
 *                                                                                                                                *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 *                                                                                                                                *
 * Plugins: Streamer                                                                                                              *
 * Modules: 3DTryg, ATM                                                                                                           *
 *                                                                                                                                *
 * File Version: 1.6.3                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * Streamer Version: 2.8.2                                                                                                        *
 * 3DTryg Version: 2.6.2                                                                                                          *
 * ATM Version: 1.4.2                                                                                                             *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * MissileLaunch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid, *
 *               Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM);    *
 * MissileDestroy(mobid,type,playerid);                                                                                           *
 * Float:GetMissileExplodeVisibility();                                                                                           *
 * SetMissileExplodeVisibility(Float:explode_stream);                                                                             *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid);                                                                 *
 * OnMissileDetectPlayer(playerid,killerid);                                                                                      *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
//Check Version Missile.inc
#if !defined _missile_launcher
	#error [ADM] You need Missile.inc v1.6.3
#elseif !defined Missile_Version
	#error [ADM] Update you Missile.inc to v1.6.3
#elseif (Missile_Version < 10603)
	#error [ADM] Update you Missile.inc to v1.6.3
#endif
*/

#if !defined Streamer_AppendArrayData
	#error [ADM] Unknown Streamer Version
#endif

//Check Version ATM.inc
#if !defined _ATM_Core
	#error [ADM] You need ATM.inc v1.4.2
#elseif !defined ATM_Version
	#error [ADM] Update you ATM.inc to v1.4.2
#elseif (ATM_Version < 10402)
	#error [ADM] Update you ATM.inc to v1.4.2
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v2.6.2
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v2.6.2
#elseif (Tryg3D_Version < 20602)
	#error [ADM] Update you 3DTryg.inc to v2.6.2
#endif

#if defined _missile_launcher
	#endinput
#endif
#define _missile_launcher

#define Missile_Version						(10603)

#define MISSILE_OBJECT_NORMAL				(0)
#define MISSILE_OBJECT_BIG					(1)
#define MISSILE_OBJECT_HYDRA				(2)

#define MAX_MISSILE							(2048)
#define MISSILE_EXTRA_ID_OFFSET				(300001)

#define MISSILE_TYPE_EXPLODE_SMALL			(12)
#define MISSILE_TYPE_EXPLODE_NORMAL			(2)
#define MISSILE_TYPE_EXPLODE_LARGE			(6)
#define MISSILE_TYPE_EXPLODE_HUGE			(7)

#define MISSILE_DESTROY_TYPE_TARGET			(0)	//When rocket reaches its destination (always killerid=INVALID_PLAYER_ID)
#define MISSILE_DESTROY_TYPE_DETECT			(1)	//When rocket has been destroyed by detection range
#define MISSILE_DESTROY_TYPE_KILL			(2)	//When rocket has been destroyed by player

#define INVALID_MISSILE_ID					(0)

#if !defined ANY_TEAM
	#define ANY_TEAM						(0xFFFF)
#endif

enum e_missile {
	bool:missile_active,
	missile_objectid,
	missile_areaid,
	missile_type,
	Float:missile_explode,
	missile_timer,
	missile_playerid,
	missile_teamid,
	missile_vehicleid
}

new MissileComponent[MAX_MISSILE][e_missile],
	Float:MissileExplosionVisibility = 200.0;

#define GetMissileExplodeVisibility()		MissileExplosionVisibility
#define SetMissileExplodeVisibility(%0)		MissileExplosionVisibility = (%0)

stock FindFreeMissileID(){
	for(new i = 1; i < MAX_MISSILE; i++){
		if(!MissileComponent[i][missile_active]) return i;
	}
	return INVALID_MISSILE_ID;
}

forward MissileDestroy(mobid,type,playerid);
forward OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid);
forward OnMissileDetectPlayer(playerid,killerid);

stock MissileLaunch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM){
	new mobid = FindFreeMissileID();
	if(mobid == INVALID_MISSILE_ID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Failed to MissileLaunch limit %d exceeded, edit Missile.inc and change MAX_MISSILE",MAX_MISSILE);
		}
		return INVALID_MISSILE_ID;
	}
	
	new Float:rx, Float:rz;
	GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
	switch(missile_object){
		case MISSILE_OBJECT_NORMAL: {
			CompRotationFloat(rz-90.0,rz);
			MissileComponent[mobid][missile_objectid] = CreateDynamicObject(3790,x,y,z,0.0,rx,rz,worldid,interiorid,playerid,streamdistance);
		}
		case MISSILE_OBJECT_BIG: {
			CompRotationFloat(rz-90.0,rz);
			MissileComponent[mobid][missile_objectid] = CreateDynamicObject(3786,x,y,z,0.0,rx,rz,worldid,interiorid,playerid,streamdistance);
		}
		case MISSILE_OBJECT_HYDRA: {
			MissileComponent[mobid][missile_objectid] = CreateDynamicObject(345,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance);
		}
	}
	
	MissileComponent[mobid][missile_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(MissileComponent[mobid][missile_areaid],MissileComponent[mobid][missile_objectid]);
	MissileComponent[mobid][missile_explode] = explode_radius;
	MissileComponent[mobid][missile_active] = true;
	MissileComponent[mobid][missile_playerid] = byplayerid;
	MissileComponent[mobid][missile_teamid] = teamid;
	MissileComponent[mobid][missile_vehicleid] = GetPlayerVehicleID(byplayerid);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,MissileComponent[mobid][missile_areaid],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	MissileComponent[mobid][missile_type] = type;
	
	switch(missile_object){
		case MISSILE_OBJECT_HYDRA: {
			MoveDynamicObject(MissileComponent[mobid][missile_objectid],tx,ty,tz,speed,rx,0.0,rz);
		}
		
		default: {
			MoveDynamicObject(MissileComponent[mobid][missile_objectid],tx,ty,tz,speed,0.0,rx,rz);
		}
	}
	
	MissileComponent[mobid][missile_timer] = SetTimerEx("MissileDestroy",GetMoveTime(x,y,z,tx,ty,tz,speed)-10,false,"ddd",mobid,MISSILE_DESTROY_TYPE_TARGET,INVALID_PLAYER_ID);
	return mobid;
}

public MissileDestroy(mobid,type,playerid){
	if(mobid <= 0 || mobid >= MAX_MISSILE) return 0;
	KillTimer(MissileComponent[mobid][missile_timer]);
	new Float:x, Float:y, Float:z,
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_WORLD_ID),
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_INTERIOR_ID);
	
	GetDynamicObjectPos(MissileComponent[mobid][missile_objectid],x,y,z);
	CreateExplosionForRangePoint(x,y,z,worldid,interiorid,MissileComponent[mobid][missile_type],GetMissileExplodeVisibility(),MissileComponent[mobid][missile_explode]);
	if(IsAnyPlayerInDynamicArea(MissileComponent[mobid][missile_areaid],1)){
		for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
			if(IsPlayerConnected(i)){
				if(IsPlayerInDynamicArea(i,MissileComponent[mobid][missile_areaid],1)){
					SetTimerEx("OnMissileDetectPlayer",50,false,"dd",i,MissileComponent[mobid][missile_playerid]);
				}
			}
		}
	}
	DestroyDynamicObject(MissileComponent[mobid][missile_objectid]);
	DestroyDynamicArea(MissileComponent[mobid][missile_areaid]);
	MissileComponent[mobid][missile_objectid] = INVALID_STREAMER_ID;
	MissileComponent[mobid][missile_areaid] = INVALID_STREAMER_ID;
	MissileComponent[mobid][missile_active] = false;
	MissileComponent[mobid][missile_type] = 0;
	MissileComponent[mobid][missile_explode] = 0.0;
	MissileComponent[mobid][missile_playerid] = INVALID_PLAYER_ID;
	MissileComponent[mobid][missile_teamid] = ANY_TEAM;
	MissileComponent[mobid][missile_vehicleid] = 0;
	CallLocalFunction("OnMissileDestroy","dfffdd",mobid,x,y,z,type,playerid);
	return 1;
}

//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_MISSILE){
		if(MissileComponent[mobid][missile_active] && MissileComponent[mobid][missile_objectid] == objectid){
			if((MissileComponent[mobid][missile_teamid] != GetPlayerTeam(playerid)) || (MissileComponent[mobid][missile_teamid] == ANY_TEAM)){
				MissileDestroy(mobid,MISSILE_DESTROY_TYPE_KILL,playerid);
			}
		}
	}
	#if defined MISOnPlayerShootDynamicObject
		MISOnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject MISOnPlayerShootDynamicObject
#if defined MISOnPlayerShootDynamicObject
	forward MISOnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid, areaid){
	new pstate = GetPlayerState(playerid);
	if(pstate != 1 && pstate != 2 && pstate != 3) return 1;
	
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
	
	if(mobid > 0 && mobid < MAX_MISSILE){
		if(MissileComponent[mobid][missile_active] && MissileComponent[mobid][missile_playerid] != playerid && MissileComponent[mobid][missile_areaid] == areaid){
			if((MissileComponent[mobid][missile_teamid] != GetPlayerTeam(playerid)) || (MissileComponent[mobid][missile_teamid] == ANY_TEAM)){
				if((MissileComponent[mobid][missile_vehicleid] != GetPlayerVehicleID(playerid)) || (MissileComponent[mobid][missile_vehicleid] == 0)){
					MissileDestroy(mobid,MISSILE_DESTROY_TYPE_DETECT,playerid);
				}
			}
		}
	}	
	#if defined MIS_OnPlayerEnterDynamicArea
		MIS_OnPlayerEnterDynamicArea(playerid, areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea MIS_OnPlayerEnterDynamicArea
#if defined MIS_OnPlayerEnterDynamicArea
	forward MIS_OnPlayerEnterDynamicArea(playerid, areaid);
#endif

//EOF
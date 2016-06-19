/**********************************************************************************************************************************
 *                                                                                                                                *
 * Military Dynamic Mines System v1.8 made by Abyss Morgan                                                                        *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * CreateDynamicMine(type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,            *
 *                   worldid,interiorid,playerid,Float:streamdistance,mine_object = MINE_OBJECT_STANDARD,teamid = ANY_TEAM);      *
 * CreateDynamicMineEx(objectid,type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z, *
 *                     Float:rx,Float:ry,Float:rz,worldid,interiorid,playerid,Float:streamdistance,teamid = ANY_TEAM);            *
 * DestroyDynamicMine(mobid);                                                                                                     *
 * Float:GetMineExplodeVisibility();                                                                                              *
 * SetMineExplodeVisibility(Float:explode_stream);                                                                                *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid);                                                                    *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

//Check Version ATM.inc
#if !defined _ATM_Core
	#error You need ATM.inc v1.3D
#elseif !defined ATM_Version
	#error Update you ATM.inc to v1.3D
#elseif (ATM_Version < 10304)
	#error Update you ATM.inc to v1.3D
#endif

#if defined _dynamic_mine_system
	#endinput
#endif
#define _dynamic_mine_system

#define MINE_OBJECT_STANDARD		(0)
#define MINE_OBJECT_UNDERWATER		(1)
#define MINE_OBJECT_LASER			(3)
#define MINE_OBJECT_PIZZA			(4)

#define MAX_MINES					(2048)
#define MINE_EXTRA_ID_OFFSET		(200001)
#define MINE_INFINITY_HEALTH		(1000000.0)

#define MINE_STATUS_UNACTIVE		(0)
#define MINE_STATUS_ACTIVE			(1)
#define MINE_STATUS_DAMAGED			(2)

#define MINE_TYPE_EXPLODE_SMALL		(12)
#define MINE_TYPE_EXPLODE_NORMAL	(2)
#define MINE_TYPE_EXPLODE_LARGE		(6)
#define MINE_TYPE_EXPLODE_HUGE		(7)

#define INVALID_MINE_ID				(-1)

#define MINE_DESTROY_TYPE_DETECT	(0)	//When mine has been destroyed by detection range
#define MINE_DESTROY_TYPE_KILL		(1)	//When mine has been destroyed by player shoot

#if !defined ANY_TEAM
	#define ANY_TEAM				(0xFFFF)
#endif

enum e_mine {
	mine_status,
	mine_objectid,
	mine_areaid,
	mine_tickcount,
	mine_type,
	mine_respawntime,
	Float:mine_health,
	Float:mine_maxhealth,
	Float:mine_explode,
	mine_teamid
}

new MineComponent[MAX_MINES][e_mine],
	MineUpperBound = 0,
	MineTimer,
	Float:MineExplosionVisibility = 200.0;

static const Float:MDM_WeaponDamage[] = {
	1.0,	// 0 - Fist
	1.0,	// 1 - Brass knuckles
	1.0,	// 2 - Golf club
	1.0,	// 3 - Nitestick
	1.0,	// 4 - Knife
	1.0,	// 5 - Bat
	1.0,	// 6 - Shovel
	1.0,	// 7 - Pool cue
	1.0,	// 8 - Katana
	1.0,	// 9 - Chainsaw
	1.0,	// 10 - Dildo
	1.0,	// 11 - Dildo 2
	1.0,	// 12 - Vibrator
	1.0,	// 13 - Vibrator 2
	1.0,	// 14 - Flowers
	1.0,	// 15 - Cane
	82.5,	// 16 - Grenade
	0.0,	// 17 - Teargas
	1.0,	// 18 - Molotov
	9.9,	// 19 - Vehicle M4 (custom)
	46.2,	// 20 - Vehicle minigun (custom)
	0.0,	// 21
	8.25,	// 22 - Colt 45
	13.2,	// 23 - Silenced
	46.2,	// 24 - Deagle
	3.3,	// 25 - Shotgun
	3.3,	// 26 - Sawed-off
	4.95,	// 27 - Spas
	6.6,	// 28 - UZI
	8.25,	// 29 - MP5
	9.9,	// 30 - AK47
	9.9,	// 31 - M4
	6.6,	// 32 - Tec9
	24.75,	// 33 - Cuntgun
	41.25,	// 34 - Sniper
	82.5,	// 35 - Rocket launcher
	82.5,	// 36 - Heatseeker
	1.0,	// 37 - Flamethrower
	46.2,	// 38 - Minigun
	82.5,	// 39 - Satchel
	0.0,	// 40 - Detonator
	0.33,	// 41 - Spraycan
	0.33,	// 42 - Fire extinguisher
	0.0,	// 43 - Camera
	0.0,	// 44 - Night vision
	0.0,	// 45 - Infrared
	0.0,	// 46 - Parachute
	0.0,	// 47 - Fake pistol
	2.64,	// 48 - Pistol whip (custom)
	9.9,	// 49 - Vehicle
	330.0,	// 50 - Helicopter blades
	82.5,	// 51 - Explosion
	1.0,	// 52 - Car park (custom)
	1.0,	// 53 - Drowning
	165.0	// 54 - Splat
};

#define GetMineExplodeVisibility()		MineExplosionVisibility
#define SetMineExplodeVisibility(%0)	MineExplosionVisibility = (%0)

stock FindFreeMineID(){
	for(new i = 0; i < MAX_MINES; i++){
		if(MineComponent[i][mine_objectid] == 0) return i;
	}
	return INVALID_MINE_ID;
}

forward OnDynamicMineUpdate(tec);
forward DestroyDynamicMine(mobid);
forward ExplodeDynamicMine(mobid,type,playerid);
forward RespawnDynamicMine(mobid);
forward OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid);

public OnFilterScriptInit(){
	MineTimer = SetTimerEx("OnDynamicMineUpdate", 1000, true, "d", 1);
	#if defined MDM_OnFilterScriptInit
		MDM_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit MDM_OnFilterScriptInit
#if defined MDM_OnFilterScriptInit
	forward MDM_OnFilterScriptInit();
#endif

public OnFilterScriptExit(){
	KillTimer(MineTimer);
	#if defined MDM_OnFilterScriptExit
		MDM_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit MDM_OnFilterScriptExit
#if defined MDM_OnFilterScriptExit
	forward MDM_OnFilterScriptExit();
#endif

public OnGameModeInit(){
	MineTimer = SetTimerEx("OnDynamicMineUpdate", 1000, true, "d", 1);
	#if defined MDM_OnGameModeInit
		MDM_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit MDM_OnGameModeInit
#if defined MDM_OnGameModeInit
	forward MDM_OnGameModeInit();
#endif

public OnGameModeExit(){
	KillTimer(MineTimer);
	#if defined MDM_OnGameModeExit
		MDM_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit MDM_OnGameModeExit
#if defined MDM_OnGameModeExit
	forward MDM_OnGameModeExit();
#endif

public OnDynamicMineUpdate(tec){
	#pragma unused tec
	new tick = GetTickCount();
	for(new mobid = 0; mobid <= MineUpperBound; mobid++){
		if(MineComponent[mobid][mine_status] == MINE_STATUS_DAMAGED){
			if((tick >= MineComponent[mobid][mine_tickcount]) && (MineComponent[mobid][mine_tickcount] != 0)){
				MineComponent[mobid][mine_tickcount] = 0;
				RespawnDynamicMine(mobid);
			}
		}
	}
	return 1;
}

stock CreateDynamicMine(type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,mine_object = MINE_OBJECT_STANDARD,teamid = ANY_TEAM){
	new mobid = FindFreeMineID();
	if(mobid == INVALID_MINE_ID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Failed to CreateDynamicMine limit %d exceeded, edit Mines.inc and change MAX_MINES",MAX_MINES);
		}
		return INVALID_MINE_ID;
	}
	switch(mine_object){
		case MINE_OBJECT_STANDARD:		MineComponent[mobid][mine_objectid] = CreateDynamicObject(19602,x,y,z-0.93,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_UNDERWATER:	MineComponent[mobid][mine_objectid] = CreateDynamicObject(2918,x,y,z-0.10,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_LASER:			MineComponent[mobid][mine_objectid] = CreateDynamicObject(18643,x,y,z-0.09,180.0,90.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_PIZZA:			MineComponent[mobid][mine_objectid] = CreateDynamicObject(19580,x,y,z+0.05,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		
		default:						MineComponent[mobid][mine_objectid] = CreateDynamicObject(19602,x,y,z-0.93,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
	}
	MineComponent[mobid][mine_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	MineComponent[mobid][mine_health] = health;
	MineComponent[mobid][mine_maxhealth] = health;
	MineComponent[mobid][mine_explode] = explode_radius;
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_type] = type;
	MineComponent[mobid][mine_respawntime] = respawntime;
	MineComponent[mobid][mine_teamid] = teamid;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	MineComponent[mobid][mine_status] = MINE_STATUS_ACTIVE;
	if(mobid > MineUpperBound) MineUpperBound = mobid;
	return mobid;
}

stock CreateDynamicMineEx(objectid,type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,worldid,interiorid,playerid,Float:streamdistance,teamid = ANY_TEAM){
	new mobid = FindFreeMineID();
	if(mobid == INVALID_MINE_ID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Failed to CreateDynamicMine limit %d exceeded, edit Mines.inc and change MAX_MINES",MAX_MINES);
		}
		return INVALID_MINE_ID;
	}
	
	MineComponent[mobid][mine_objectid] = CreateDynamicObject(objectid,x,y,z,rx,ry,rz,worldid,interiorid,playerid,streamdistance);
	MineComponent[mobid][mine_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	MineComponent[mobid][mine_health] = health;
	MineComponent[mobid][mine_maxhealth] = health;
	MineComponent[mobid][mine_explode] = explode_radius;
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_type] = type;
	MineComponent[mobid][mine_respawntime] = respawntime;
	MineComponent[mobid][mine_teamid] = teamid;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	MineComponent[mobid][mine_status] = MINE_STATUS_ACTIVE;
	if(mobid > MineUpperBound) MineUpperBound = mobid;
	return mobid;
}

public DestroyDynamicMine(mobid){
	if(mobid < 0 || mobid >= MAX_MINES) return 0;
	if(MineComponent[mobid][mine_status] == MINE_STATUS_UNACTIVE) return 0;
	DestroyDynamicObject(MineComponent[mobid][mine_objectid]);
	DestroyDynamicArea(MineComponent[mobid][mine_areaid]);
	MineComponent[mobid][mine_objectid] = INVALID_STREAMER_ID;
	MineComponent[mobid][mine_areaid] = INVALID_STREAMER_ID;
	MineComponent[mobid][mine_health] = 0.0;
	MineComponent[mobid][mine_maxhealth] = 0.0;
	MineComponent[mobid][mine_explode] = 0.0;
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_type] = 0;
	MineComponent[mobid][mine_status] = MINE_STATUS_UNACTIVE;
	MineComponent[mobid][mine_respawntime] = 0;
	MineComponent[mobid][mine_teamid] = ANY_TEAM;
	if(mobid == MineUpperBound) MineUpperBound = (mobid-1);
	return 1;
}

public ExplodeDynamicMine(mobid,type,playerid){
	if(mobid < 0 || mobid >= MAX_MINES) return 0;
	new Float:minex, Float:miney, Float:minez,
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID),
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_INTERIOR_ID);
		
	GetDynamicObjectPos(MineComponent[mobid][mine_objectid],minex,miney,minez);
	CreateExplosionForRangePoint(minex,miney,minez,worldid,interiorid,MineComponent[mobid][mine_type],GetMineExplodeVisibility(),MineComponent[mobid][mine_explode]);
	MineComponent[mobid][mine_tickcount] = GetTickCount()+(MineComponent[mobid][mine_respawntime]*1000);
	MineComponent[mobid][mine_status] = MINE_STATUS_DAMAGED;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID,worldid+10000); //hide mine
	CallLocalFunction("OnMineDestroy","dfffdd",mobid,minex,miney,minez,type,playerid);
	return 1;
}

public RespawnDynamicMine(mobid){
	if(mobid < 0 || mobid >= MAX_MINES) return 0;
	new worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID,worldid-10000); //show mine
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_health] = MineComponent[mobid][mine_maxhealth];
	MineComponent[mobid][mine_status] = MINE_STATUS_ACTIVE;
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mobid >= 0 && mobid < MAX_MINES){
		if(MineComponent[mobid][mine_status] == MINE_STATUS_ACTIVE){
			if((MineComponent[mobid][mine_teamid] != GetPlayerTeam(playerid)) || (MineComponent[mobid][mine_teamid] == ANY_TEAM)){
				if(MineComponent[mobid][mine_health] != MINE_INFINITY_HEALTH){
					MineComponent[mobid][mine_health] -= MDM_WeaponDamage[weaponid];
					new buffer[128];
					if(MineComponent[mobid][mine_health] > 0){
						format(buffer,sizeof buffer,"Mine~n~~w~%.0f HP~n~~r~~h~~h~-%.0f HP",MineComponent[mobid][mine_health],MDM_WeaponDamage[weaponid]);
					} else {
						format(buffer,sizeof buffer,"Mine~n~~w~0 HP~n~~r~~h~~h~-%.0f HP",MDM_WeaponDamage[weaponid]);
					}
					GameTextForPlayer(playerid,buffer,500,4);
					if(MineComponent[mobid][mine_health] <= 0.0){
						ExplodeDynamicMine(mobid,MINE_DESTROY_TYPE_KILL,playerid);
					}
				}
			}
		}
	}
	#if defined MDM_OnPlayerShootDynamicObject
		MDM_OnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject MDM_OnPlayerShootDynamicObject
#if defined MDM_OnPlayerShootDynamicObject
	forward MDM_OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z);
#endif


public OnPlayerEnterDynamicArea(playerid, areaid){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mobid >= 0 && mobid < MAX_MINES){
		if(MineComponent[mobid][mine_status] == MINE_STATUS_ACTIVE){
			if((MineComponent[mobid][mine_teamid] != GetPlayerTeam(playerid)) || (MineComponent[mobid][mine_teamid] == ANY_TEAM)){
				MineComponent[mobid][mine_health] = 0.0;
				ExplodeDynamicMine(mobid,MINE_DESTROY_TYPE_DETECT,playerid);
			}
		}
	}	
	#if defined MDM_OnPlayerEnterDynamicArea
		MDM_OnPlayerEnterDynamicArea(playerid, areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea MDM_OnPlayerEnterDynamicArea
#if defined MDM_OnPlayerEnterDynamicArea
	forward MDM_OnPlayerEnterDynamicArea(playerid, areaid);
#endif

//EOF
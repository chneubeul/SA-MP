/******************************************************
 *                                                    *
 * Military Dynamic Mines System v1.3 by Abyss Morgan *
 *                                                    *
 ******************************************************/

/*
//To add/remove mines use:
CreateDynamicMine(type, Float:detection_range, Float:explode_radius, Float:health, respawntime, Float:x, Float:y, Float:z, worldid, interiorid, playerid, Float:streamdistance);
DestroyDynamicMine(mineid);
*/

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

#if defined _dynamic_mine_system
	#endinput
#endif
#define _dynamic_mine_system

#define MAX_MINES					(300)
#define MINE_EXTRA_ID_OFFSET		(200001)
#define MINE_INFINITY_HEALTH		(1000000.0)
#define MINE_Z_CORRECT				(-0.93)
#define MINE_STATUS_UNACTIVE		(0)
#define MINE_STATUS_ACTIVE			(1)
#define MINE_STATUS_DAMAGED			(2)
#define MINE_TYPE_EXPLODE_SMALL		(12)
#define MINE_TYPE_EXPLODE_NORMAL	(2)
#define MINE_TYPE_EXPLODE_LARGE		(6)
#define MINE_TYPE_EXPLODE_HUGE		(7)
#define INVALID_MINE_ID				(-1)

enum e_mine {
	mine_status,
	mine_objectid,
	mine_areaid,
	mine_tickcount,
	mine_type,
	mine_respawntime,
	Float:mine_health,
	Float:mine_maxhealth,
	Float:mine_explode
}

new MineComponent[MAX_MINES][e_mine],
	MineUpperBound = 0,
	MineTimer;

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

stock FindFreeMineID(){
	for(new i = 0; i < MAX_MINES; i++){
		if(MineComponent[i][mine_objectid] == 0) return i;
	}
	return INVALID_MINE_ID;
}

stock CreateExplosionForRangePoint(Float:x,Float:y,Float:z,worldid,interiorid,type,Float:radius,Float:expradius){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i)){
			new Float:minex, Float:miney, Float:minez;
			if(IsPlayerInAnyVehicle(i)){
				GetVehiclePos(GetPlayerVehicleID(i),minex,miney,minez);
			} else {
				GetPlayerPos(i,minex,miney,minez);
			}
			new Float:distance = VectorSize(minex-x,miney-y,minez-z);
			if((GetPlayerInterior(i) == interiorid) && (GetPlayerVirtualWorld(i) == worldid) && (distance <= radius)){
				CreateExplosionForPlayer(i,x,y,z,type,expradius);
			}
		}
	}
	return 1;
}

forward OnDynamicMineUpdate(tec);
forward CreateDynamicMine(type, Float:detection_range, Float:explode_radius, Float:health, respawntime, Float:x, Float:y, Float:z, worldid, interiorid, playerid, Float:streamdistance);
forward DestroyDynamicMine(mineid);
forward ExplodeDynamicMine(mineid);
forward RespawnDynamicMine(mineid);

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

public OnDynamicMineUpdate(tec){
	#pragma unused tec
	new tick = GetTickCount();
	for(new mineid = 0; mineid <= MineUpperBound; mineid++){
		if(MineComponent[mineid][mine_status] == MINE_STATUS_DAMAGED){
			if((tick >= MineComponent[mineid][mine_tickcount]) && (MineComponent[mineid][mine_tickcount] != 0)){
				MineComponent[mineid][mine_tickcount] = 0;
				RespawnDynamicMine(mineid);
			}
		}
	}
	return 1;
}

public CreateDynamicMine(type, Float:detection_range, Float:explode_radius, Float:health, respawntime, Float:x, Float:y, Float:z, worldid, interiorid, playerid, Float:streamdistance){
	new mineid = FindFreeMineID();
	if(mineid == INVALID_MINE_ID) return INVALID_MINE_ID;
	MineComponent[mineid][mine_objectid] = CreateDynamicObject(19602,x,y,z+MINE_Z_CORRECT,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance); //1213
	MineComponent[mineid][mine_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	MineComponent[mineid][mine_health] = health;
	MineComponent[mineid][mine_maxhealth] = health;
	MineComponent[mineid][mine_explode] = explode_radius;
	MineComponent[mineid][mine_tickcount] = 0;
	MineComponent[mineid][mine_type] = type;
	MineComponent[mineid][mine_respawntime] = respawntime;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mineid][mine_objectid],E_STREAMER_EXTRA_ID,(mineid+MINE_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,MineComponent[mineid][mine_areaid],E_STREAMER_EXTRA_ID,(mineid+MINE_EXTRA_ID_OFFSET));
	MineComponent[mineid][mine_status] = MINE_STATUS_ACTIVE;
	if(mineid > MineUpperBound) MineUpperBound = mineid;
	return mineid;
}

public DestroyDynamicMine(mineid){
	if(mineid < 0 || mineid >= MAX_MINES) return 0;
	DestroyDynamicObject(MineComponent[mineid][mine_objectid]);
	DestroyDynamicArea(MineComponent[mineid][mine_areaid]);
	#if !defined _streamer_spec
		#if !defined FIX_OBJECTS
			MineComponent[mineid][mine_objectid] = INVALID_STREAMER_ID;
			MineComponent[mineid][mine_areaid] = INVALID_STREAMER_ID;
		#endif
	#endif
	MineComponent[mineid][mine_health] = 0.0;
	MineComponent[mineid][mine_maxhealth] = 0.0;
	MineComponent[mineid][mine_explode] = 0.0;
	MineComponent[mineid][mine_tickcount] = 0;
	MineComponent[mineid][mine_type] = 0;
	MineComponent[mineid][mine_status] = MINE_STATUS_UNACTIVE;
	MineComponent[mineid][mine_respawntime] = 0;
	if(mineid == MineUpperBound) MineUpperBound = (mineid-1);
	return 1;
}

public ExplodeDynamicMine(mineid){
	if(mineid < 0 || mineid >= MAX_MINES) return 0;
	new Float:minex, Float:miney, Float:minez,
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mineid][mine_objectid],E_STREAMER_WORLD_ID),
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mineid][mine_objectid],E_STREAMER_INTERIOR_ID);
		
	GetDynamicObjectPos(MineComponent[mineid][mine_objectid],minex,miney,minez);
	if(worldid == -1 || interiorid == -1){
		CreateExplosion(minex,miney,minez,MineComponent[mineid][mine_type],MineComponent[mineid][mine_explode]);
	} else {
		CreateExplosionForRangePoint(minex,miney,minez,worldid,interiorid,MineComponent[mineid][mine_type],200.0,MineComponent[mineid][mine_explode]);
	}
	MineComponent[mineid][mine_tickcount] = GetTickCount()+(MineComponent[mineid][mine_respawntime]*1000);
	MineComponent[mineid][mine_status] = MINE_STATUS_DAMAGED;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mineid][mine_objectid],E_STREAMER_WORLD_ID,worldid+10000); //hide mine
	return 1;
}

public RespawnDynamicMine(mineid){
	if(mineid < 0 || mineid >= MAX_MINES) return 0;
	new worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mineid][mine_objectid],E_STREAMER_WORLD_ID);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mineid][mine_objectid],E_STREAMER_WORLD_ID,worldid-10000); //show mine
	MineComponent[mineid][mine_tickcount] = 0;
	MineComponent[mineid][mine_health] = MineComponent[mineid][mine_maxhealth];
	MineComponent[mineid][mine_status] = MINE_STATUS_ACTIVE;
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){
	new mineid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mineid >= 0 && mineid < MAX_MINES){
		if(MineComponent[mineid][mine_status] == MINE_STATUS_ACTIVE){
			if(MineComponent[mineid][mine_health] != MINE_INFINITY_HEALTH){
				MineComponent[mineid][mine_health] -= MDM_WeaponDamage[weaponid];
				new buffer[128];
				if(MineComponent[mineid][mine_health] > 0){
					format(buffer,sizeof buffer,"Mine~n~~w~%.0f HP~n~~r~~h~~h~-%.0f HP",MineComponent[mineid][mine_health],MDM_WeaponDamage[weaponid]);
				} else {
					format(buffer,sizeof buffer,"Mine~n~~w~0 HP~n~~r~~h~~h~-%.0f HP",MDM_WeaponDamage[weaponid]);
				}
				GameTextForPlayer(playerid,buffer,500,4);
				if(MineComponent[mineid][mine_health] <= 0.0){
					ExplodeDynamicMine(mineid);
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
	new mineid = (Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mineid >= 0 && mineid < MAX_MINES){
		if(MineComponent[mineid][mine_status] == MINE_STATUS_ACTIVE){
			MineComponent[mineid][mine_health] = 0.0;
			ExplodeDynamicMine(mineid);
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
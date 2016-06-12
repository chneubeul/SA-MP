/****************************************************************************************************
 *                                                                                                  *
 * Missile Launcher v1.0 made by Abyss Morgan                                                       *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts                         *
 *                                                                                                  *
 ****************************************************************************************************/

/*

MissileLaunch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID);
MissileDestroy(mobid);

*/

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

#if !defined _ATM_Core
	#error You need ATM.inc
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.4B
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.4B
#elseif (Tryg3D_Version < 20402)
	#error Update you 3DTryg.inc to v2.4B
#endif

#if defined _missile_launcher
	#endinput
#endif
#define _missile_launcher

#define MISSILE_OBJECT_NORMAL			(0)
#define MISSILE_OBJECT_BIG				(1)
#define MISSILE_OBJECT_HYDRA			(2)

#define MAX_MISSILE						(2048)
#define MISSILE_EXTRA_ID_OFFSET			(300001)

#define MISSILE_TYPE_EXPLODE_SMALL		(12)
#define MISSILE_TYPE_EXPLODE_NORMAL		(2)
#define MISSILE_TYPE_EXPLODE_LARGE		(6)
#define MISSILE_TYPE_EXPLODE_HUGE		(7)

#define INVALID_MISSILE_ID				(-1)

enum e_missile {
	bool:missile_active,
	missile_objectid,
	missile_areaid,
	missile_type,
	Float:missile_explode,
	missile_timer,
	missile_playerid
}

new MissileComponent[MAX_MISSILE][e_missile];

stock FindFreeMissileID(){
	for(new i = 0; i < MAX_MISSILE; i++){
		if(!MissileComponent[i][missile_active]) return i;
	}
	return INVALID_MISSILE_ID;
}

forward MissileDestroy(mobid);

stock MissileLaunch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID){
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
			MissileComponent[mobid][missile_objectid] = CreateDynamicObject(345,x,y,z,0.0,rx,rz,worldid,interiorid,playerid,streamdistance);
		}
	}
	
	MissileComponent[mobid][missile_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(MissileComponent[mobid][missile_areaid],MissileComponent[mobid][missile_objectid]);
	MissileComponent[mobid][missile_explode] = explode_radius;
	MissileComponent[mobid][missile_active] = true;
	MissileComponent[mobid][missile_playerid] = byplayerid;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,MissileComponent[mobid][missile_areaid],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	MissileComponent[mobid][missile_type] = type;
	MoveDynamicObject(MissileComponent[mobid][missile_objectid],tx,ty,tz,speed,0.0,rx,rz);
	MissileComponent[mobid][missile_timer] = SetTimerEx("MissileDestroy",GetMoveTime(x,y,z,tx,ty,tz,speed)-10,false,"d",mobid);
	return mobid;
}

public MissileDestroy(mobid){
	if(mobid < 0 || mobid >= MAX_MISSILE) return 0;
	KillTimer(MissileComponent[mobid][missile_timer]);
	new Float:x, Float:y, Float:z,
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_WORLD_ID),
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_INTERIOR_ID);
	
	GetDynamicObjectPos(MissileComponent[mobid][missile_objectid],x,y,z);
	CreateExplosionForRangePoint(x,y,z,worldid,interiorid,MissileComponent[mobid][missile_type],200.0,MissileComponent[mobid][missile_explode]);
	DestroyDynamicObject(MissileComponent[mobid][missile_objectid]);
	DestroyDynamicArea(MissileComponent[mobid][missile_areaid]);
	MissileComponent[mobid][missile_objectid] = INVALID_STREAMER_ID;
	MissileComponent[mobid][missile_areaid] = INVALID_STREAMER_ID;
	MissileComponent[mobid][missile_active] = false;
	MissileComponent[mobid][missile_type] = 0;
	MissileComponent[mobid][missile_explode] = 0.0;
	MissileComponent[mobid][missile_playerid] = INVALID_PLAYER_ID;
	return 1;
}


public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
	if(mobid >= 0 && mobid < MAX_MISSILE){
		if(MissileComponent[mobid][missile_active]){
			MissileDestroy(mobid);
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

public OnPlayerEnterDynamicArea(playerid, areaid){
	new pstate = GetPlayerState(playerid);
	if(pstate != 1 && pstate != 2 && pstate != 3) return 1;
	
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
	
	if(mobid >= 0 && mobid < MAX_MISSILE){
		if(MissileComponent[mobid][missile_active] && MissileComponent[mobid][missile_playerid] != playerid){
			MissileDestroy(mobid);
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
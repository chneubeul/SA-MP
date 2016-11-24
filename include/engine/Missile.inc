/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                        Missile Launcher                                                        *
 *                                                                                                                                *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 * Publication: http://forum.sa-mp.com/showthread.php?t=608018                                                                    *
 *                                                                                                                                *
 * Plugins: Streamer                                                                                                              *
 * Modules: 3DTryg                                                                                                                *
 *                                                                                                                                *
 * File Version: 1.7.0                                                                                                            *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                                                 *
 * Streamer Version: 2.8.2                                                                                                        *
 * 3DTryg Version: 3.0.5                                                                                                          *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * MissileLaunch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid, *
 *               Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM,     *
 *               bool:remote=false,remote_count=MAX_MISSILE_REMOTE_TARGET,remote_height=1.0);                                     *
 * MissileLaunchAimPlayer(targetid,type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,           *
 *                        worldid,interiorid,playerid,Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,             *
 *                        byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM);                                                          *
 * bool:MissileStopAimPlayer(mobid);                                                                                              *
 * MissileDestroy(mobid,type,playerid);                                                                                           *
 * MissileRemoteTarget(mobid,Float:tx,Float:ty,Float:tz,Float:speed = 0.0);                                                       *
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
	#error [ADM] You need Missile.inc v1.7.0
#elseif !defined Missile_Version
	#error [ADM] Update you Missile.inc to v1.7.0
#elseif (Missile_Version < 10700)
	#error [ADM] Update you Missile.inc to v1.7.0
#endif
*/

#if defined _missile_launcher
	#endinput
#endif
#define _missile_launcher

#if (!defined GetPlayerPoolSize)
	#error [ADM] This include requires SA:MP version 0.3.7
#endif

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v3.0.5
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v3.0.5
#elseif (Tryg3D_Version < 30005)
	#error [ADM] Update you 3DTryg.inc to v3.0.5
#endif

#define Missile_Version						(10700)

#define MISSILE_OBJECT_NORMAL				(0)
#define MISSILE_OBJECT_BIG					(1)
#define MISSILE_OBJECT_HYDRA				(2)

#define MAX_MISSILE							(2048)
#define MAX_MISSILE_REMOTE_TARGET			(32)
#define MISSILE_EXTRA_ID_OFFSET				(300001)
#define MISSILE_REMOTE_PLAYER				(999)

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
	missile_playerid,
	missile_teamid,
	missile_vehicleid,
	missile_remote_count,
	Float:missile_speed,
	Float:missile_remote_X[MAX_MISSILE_REMOTE_TARGET],
	Float:missile_remote_Y[MAX_MISSILE_REMOTE_TARGET],
	Float:missile_remote_Z[MAX_MISSILE_REMOTE_TARGET],
	player_target
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

forward OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid);
forward OnMissileDetectPlayer(playerid,killerid);

stock MissileLaunch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid, \
	Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM, \
	bool:remote=false,remote_count=MAX_MISSILE_REMOTE_TARGET,Float:remote_height=1.0){
	
	new mobid = FindFreeMissileID();
	if(mobid == INVALID_MISSILE_ID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Failed to MissileLaunch limit %d exceeded, edit Missile.inc and change MAX_MISSILE",MAX_MISSILE);
		}
		return INVALID_MISSILE_ID;
	}
	
	remote_count--;
	new Float:rx, Float:rz, Float:orgRZ;
	GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
	orgRZ = rz;
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
	MissileComponent[mobid][missile_explode] = explode_radius;
	MissileComponent[mobid][missile_active] = true;
	MissileComponent[mobid][missile_playerid] = byplayerid;
	MissileComponent[mobid][missile_teamid] = teamid;
	MissileComponent[mobid][missile_speed] = speed;
	MissileComponent[mobid][player_target] = INVALID_PLAYER_ID;
	if(remote && remote_count > -1){
		if(remote_height <= 0.0){
			remote_height = 1.0;
		}
		
		if(remote_count >= MAX_MISSILE_REMOTE_TARGET) remote_count = (MAX_MISSILE_REMOTE_TARGET-1);
		MissileComponent[mobid][missile_remote_count] = remote_count;
	
		new Float:mercury = (1.0/(remote_count+2)),
			Float:dist = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz),
			Float:jun = (dist/2.0), Float:rsize, idx = 1;
			
		//0 - primary target
		//remote_count - first remote point
		for(new i = remote_count; i >= 0; i--){
			rsize = (dist*(mercury*idx));
			GetPointInFront2D(x,y,orgRZ,rsize,MissileComponent[mobid][missile_remote_X][i],MissileComponent[mobid][missile_remote_Y][i]);
			if(rsize == jun){
				MissileComponent[mobid][missile_remote_Z][i] = (z + remote_height);
			} else if(rsize < jun){
				//upward
				MissileComponent[mobid][missile_remote_Z][i] = (z + (rsize * (remote_height / jun)));
			} else {
				//downward
				MissileComponent[mobid][missile_remote_Z][i] = (z + remote_height - ((rsize * (remote_height / jun)) - remote_height));
			}
			idx++;
		}
		Tryg3DMapAndreasFindZ(MissileComponent[mobid][missile_remote_X][0],MissileComponent[mobid][missile_remote_Y][0],MissileComponent[mobid][missile_remote_Z][0]);
		
		tx = MissileComponent[mobid][missile_remote_X][remote_count];
		ty = MissileComponent[mobid][missile_remote_Y][remote_count];
		tz = MissileComponent[mobid][missile_remote_Z][remote_count];
		GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
		switch(missile_object){
			case MISSILE_OBJECT_NORMAL: {
				CompRotationFloat(rz-90.0,rz);
				SetDynamicObjectRot(MissileComponent[mobid][missile_objectid],0.0,rx,rz);
			}
			case MISSILE_OBJECT_BIG: {
				CompRotationFloat(rz-90.0,rz);
				SetDynamicObjectRot(MissileComponent[mobid][missile_objectid],0.0,rx,rz);
			}
			case MISSILE_OBJECT_HYDRA: {
				SetDynamicObjectRot(MissileComponent[mobid][missile_objectid],rx,0.0,rz);
			}
		}
	} else {
		MissileComponent[mobid][missile_remote_count] = 0;
	}
	MissileComponent[mobid][missile_vehicleid] = GetPlayerVehicleID(byplayerid);
	
	MissileComponent[mobid][missile_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(MissileComponent[mobid][missile_areaid],MissileComponent[mobid][missile_objectid]);
	
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
	return mobid;
}

stock MissileLaunchAimPlayer(targetid,type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid, \
	Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM){
	
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
	MissileComponent[mobid][missile_explode] = explode_radius;
	MissileComponent[mobid][missile_active] = true;
	MissileComponent[mobid][missile_playerid] = byplayerid;
	MissileComponent[mobid][missile_teamid] = teamid;
	MissileComponent[mobid][missile_speed] = speed;
	MissileComponent[mobid][missile_remote_count] = MISSILE_REMOTE_PLAYER;
	MissileComponent[mobid][missile_vehicleid] = GetPlayerVehicleID(byplayerid);
	MissileComponent[mobid][player_target] = targetid;
	MissileComponent[mobid][missile_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(MissileComponent[mobid][missile_areaid],MissileComponent[mobid][missile_objectid]);
	
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
	return mobid;
}

stock bool:MissileStopAimPlayer(mobid){
	if(MissileComponent[mobid][missile_active]){
		if(MissileComponent[mobid][missile_remote_count] == MISSILE_REMOTE_PLAYER){
			if(!IsPlayerConnected(MissileComponent[mobid][player_target])){
				MissileComponent[mobid][player_target] = INVALID_PLAYER_ID;
				MissileComponent[mobid][missile_remote_count] = 0;
				return true;
			}
		}
	}
	return false;
}

stock MissileRemoteTarget(mobid,Float:tx,Float:ty,Float:tz,Float:speed = 0.0){
	if(mobid <= 0 || mobid >= MAX_MISSILE) return 0;
	if(!MissileComponent[mobid][missile_active]) return 0;
	if(speed == 0.0) speed = MissileComponent[mobid][missile_speed];
	new missile_modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_MODEL_ID),
		Float:x ,Float:y, Float:z, Float:rx, Float:rz;
	GetDynamicObjectPos(MissileComponent[mobid][missile_objectid],x,y,z);
	GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
	switch(missile_modelid){
		case 345: {
			SetDynamicObjectRot(MissileComponent[mobid][missile_objectid],rx,0.0,rz);
			MoveDynamicObject(MissileComponent[mobid][missile_objectid],tx,ty,tz,speed,rx,0.0,rz);
		}
		
		case 3790, 3786: {
			CompRotationFloat(rz-90.0,rz);
			SetDynamicObjectRot(MissileComponent[mobid][missile_objectid],0.0,rx,rz);
			MoveDynamicObject(MissileComponent[mobid][missile_objectid],tx,ty,tz,speed,0.0,rx,rz);
		}
	}
	return 1;
}

stock MissileDestroy(mobid,type,playerid){
	if(mobid <= 0 || mobid >= MAX_MISSILE) return 0;
	if(!MissileComponent[mobid][missile_active]) return 0;

	new Float:x, Float:y, Float:z,
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_WORLD_ID),
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MissileComponent[mobid][missile_objectid],E_STREAMER_INTERIOR_ID);
	
	GetDynamicObjectPos(MissileComponent[mobid][missile_objectid],x,y,z);
	CreateDynamicExplosion(x,y,z,MissileComponent[mobid][missile_type],MissileComponent[mobid][missile_explode],worldid,interiorid,-1,GetMissileExplodeVisibility());
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
	MissileComponent[mobid][missile_speed] = 0.0;
	MissileComponent[mobid][missile_remote_count] = 0;
	MissileComponent[mobid][player_target] = INVALID_PLAYER_ID;
	CallLocalFunction("OnMissileDestroy","dfffdd",mobid,x,y,z,type,playerid);
	return 1;
}

//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid,weaponid,objectid,Float:x,Float:y,Float:z){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_MISSILE){
		if(MissileComponent[mobid][missile_active] && MissileComponent[mobid][missile_objectid] == objectid){
			if((MissileComponent[mobid][missile_teamid] != GetPlayerTeam(playerid)) || (MissileComponent[mobid][missile_teamid] == ANY_TEAM)){
				MissileDestroy(mobid,MISSILE_DESTROY_TYPE_KILL,playerid);
			}
		}
	}
	#if defined MISOnPlayerShootDynamicObject
		MISOnPlayerShootDynamicObject(playerid,weaponid,objectid,x,y,z);
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
	forward MISOnPlayerShootDynamicObject(playerid,weaponid,objectid,Float:x,Float:y,Float:z);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,areaid){
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
		MIS_OnPlayerEnterDynamicArea(playerid,areaid);
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
	forward MIS_OnPlayerEnterDynamicArea(playerid,areaid);
#endif

//Hook: OnDynamicObjectMoved
public OnDynamicObjectMoved(objectid){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_MISSILE){
		if(MissileComponent[mobid][missile_active] && MissileComponent[mobid][missile_objectid] == objectid){
			if(MissileComponent[mobid][missile_remote_count] == MISSILE_REMOTE_PLAYER){
				if(!IsPlayerConnected(MissileComponent[mobid][player_target])){
					MissileComponent[mobid][player_target] = INVALID_PLAYER_ID;
					MissileComponent[mobid][missile_remote_count] = 0;
				}
			}
			if(MissileComponent[mobid][missile_remote_count] <= 0){
				MissileDestroy(mobid,MISSILE_DESTROY_TYPE_TARGET,INVALID_PLAYER_ID);
			} else if(MissileComponent[mobid][missile_remote_count] == MISSILE_REMOTE_PLAYER){
				new Float:px,Float:py,Float:pz;
				GetPlayerPos(MissileComponent[mobid][player_target],px,py,pz);
				#if defined COLANDREAS
					new Float:x, Float:y, Float:z, Float:tx, Float:ty, Float:tz;
					GetDynamicObjectPos(objectid,x,y,z);
					MovePointCol(x,y,z,px,py,pz,tx,ty,tz);
					if(tx != px || ty != py || tz != pz){
						//collision
						MissileComponent[mobid][missile_remote_count] = 0;
						MissileRemoteTarget(mobid,tx,ty,tz);
					} else {
						MissileRemoteTarget(mobid,tx,ty,tz);
					}
				#else
					MissileRemoteTarget(mobid,px,py,pz);
				#endif
			} else {
				MissileComponent[mobid][missile_remote_count]--;
				new remote_id = MissileComponent[mobid][missile_remote_count];
				#if defined COLANDREAS
					new Float:x, Float:y, Float:z, Float:tx, Float:ty, Float:tz;
					GetDynamicObjectPos(objectid,x,y,z);
					MovePointCol(x,y,z,MissileComponent[mobid][missile_remote_X][remote_id],MissileComponent[mobid][missile_remote_Y][remote_id],MissileComponent[mobid][missile_remote_Z][remote_id],tx,ty,tz);
					if(tx != MissileComponent[mobid][missile_remote_X][remote_id] || ty != MissileComponent[mobid][missile_remote_Y][remote_id] || tz != MissileComponent[mobid][missile_remote_Z][remote_id]){
						//collision
						MissileComponent[mobid][missile_remote_count] = 0;
						MissileRemoteTarget(mobid,tx,ty,tz);
					} else {
						MissileRemoteTarget(mobid,MissileComponent[mobid][missile_remote_X][remote_id],MissileComponent[mobid][missile_remote_Y][remote_id],MissileComponent[mobid][missile_remote_Z][remote_id]);
					}
				#else
					MissileRemoteTarget(mobid,MissileComponent[mobid][missile_remote_X][remote_id],MissileComponent[mobid][missile_remote_Y][remote_id],MissileComponent[mobid][missile_remote_Z][remote_id]);
				#endif
			}
		}
	}
	#if defined MIS_OnDynamicObjectMoved
		MIS_OnDynamicObjectMoved(objectid);
	#endif
	return 1;
}

#if defined _ALS_OnDynamicObjectMoved
	#undef OnDynamicObjectMoved
#else
	#define _ALS_OnDynamicObjectMoved
#endif
#define OnDynamicObjectMoved MIS_OnDynamicObjectMoved
#if defined MIS_OnDynamicObjectMoved
	forward MIS_OnDynamicObjectMoved(objectid);
#endif
//EOF

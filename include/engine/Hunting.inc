/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                         Hunting System                                                         *
 *                                                                                                                                *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 * Publication: ---                                                                                                               *
 * Website: http://8.ct8.pl                                                                                                       *
 *                                                                                                                                *
 * Plugins: Streamer, ColAndreas                                                                                                  *
 * Modules: 3DTryg                                                                                                                *
 *                                                                                                                                *
 * File Version: 1.0.0                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * Streamer Version: 2.9.1                                                                                                        *
 * 3DTryg Version: 4.4.3                                                                                                          *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * Hunting::Count();                                                                                                              *
 * Hunting::GetFreeID();                                                                                                          *
 * Hunting::Create(type,Float:x,Float:y,Float:z,Float:health,respawntime,worldid=-1,interiorid=-1,playerid=-1,                    *
 *                 Float:streamdistance=200.0,moving_area = 0);                                                                   *
 * Hunting::Respawn(mobid);                                                                                                       *
 * Hunting::Destroy(mobid);                                                                                                       *
 * Hunting::Kill(mobid,playerid);                                                                                                 *
 * Hunting::GetKey();                                                                                                             *
 * Hunting::SetKey(key);                                                                                                          *
 * Hunting::SetDrop(mobid,drop);                                                                                                  *
 * Hunting::GetDrop(mobid);                                                                                                       *
 * Hunting::GetPos(mobid,Float:x,Float:y,Float:z);                                                                                *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * OnPlayerTakeHuntDrop(playerid,mobid,drop);                                                                                     *
 * OnPlayerKillHuntAnimal(playerid,mobid);                                                                                        *
 * OnPlayerApproachingAnimal(playerid,mobid,mob_state);                                                                           *
 * OnAnimalTakeDamage(mobid,playerid,Float:amount,weaponid);                                                                      *
 * OnHuntAnimalRespawn(mobid);                                                                                                    *
 *                                                                                                                                *
 **********************************************************************************************************************************/
 
#if ((defined Streamer_AppendArrayData) && (defined INVALID_STREAMER_ID) && (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] You need Streamer v2.9.1 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined COLANDREAS
	#error [ADM] You need ColAndreas v1.4.0 (github.com/Pottus/ColAndreas/releases)
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v4.4.3 (github.com/AbyssMorgan/SA-MP/blob/master/include/SAM/3DTryg.inc)
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v4.4.3 (github.com/AbyssMorgan/SA-MP/blob/master/include/SAM/3DTryg.inc)
#elseif (Tryg3D_Version < 40403)
	#error [ADM] Update you 3DTryg.inc to v4.4.3 (github.com/AbyssMorgan/SA-MP/blob/master/include/SAM/3DTryg.inc)
#endif

#if defined _hunting_system
	#endinput
#endif
#define _hunting_system

#define Hunting::								Hunt_

#if !defined MAX_HUNTING_ANIMALS
	#define MAX_HUNTING_ANIMALS					100
#endif

#if !defined HUNTING_UPDATE_INTERVAL
	#define HUNTING_UPDATE_INTERVAL				500
#endif

#define HUNT_EXTRA_ID_OFFSET					600000

#define HUNTING_TYPE_COW						19833
#define HUNTING_TYPE_DEER						19315

#define HUNTING_STATE_DESTROYED					0
#define HUNTING_STATE_SPAWNED					1
#define HUNTING_STATE_DEAD						2

#define INVALID_HUNTING_ID						0

#define HUNTING_NO_AUTO_RESPAWN					-1

enum Hunting::enum {
	STREAMER_TAG_OBJECT Hunting::objectid,
	STREAMER_TAG_AREA Hunting::drop_area,
	STREAMER_TAG_AREA Hunting::areaid,
	Hunting::type,
	Float:Hunting::health,
	Float:Hunting::max_health,
	Hunting::state,
	Hunting::respawntime,
	Hunting::drop,
	Hunting::respawn_tick,
	Float:Hunting::X,
	Float:Hunting::Y,
	Float:Hunting::Z,
	Float:Hunting::tX,
	Float:Hunting::tY,
	Float:Hunting::rZ
}

new Hunting::Data[MAX_HUNTING_ANIMALS][Hunting::enum],
	Hunting::Upperbound = 0,
	Hunting::Key = KEY_YES,
	Hunting::Timer = -1;
	
forward OnPlayerTakeHuntDrop(playerid,mobid,drop);
forward OnPlayerKillHuntAnimal(playerid,mobid);
forward OnPlayerApproachingAnimal(playerid,mobid,mob_state);
forward OnAnimalTakeDamage(mobid,playerid,Float:amount,weaponid);
forward OnHuntAnimalRespawn(mobid);

#define Hunt_GetKey()							Hunting::Key
#define Hunt_SetKey(%0)							Hunting::Key = (%0)

#define Hunt_SetDrop(%0,%1)						Hunting::Data[(%0)][Hunting::drop] = (%1)
#define Hunt_GetDrop(%0)						Hunting::Data[(%0)][Hunting::drop]

#define Hunt_GetPos(%0,%1,%2,%3)				GetDynamicObjectPos(Hunting::Data[(%0)][Hunting::objectid],(%1),(%2),(%3))

stock Hunting::Count(){
	new cnt = 0;
	for(new mobid = 1; mobid <= Hunting::Upperbound; mobid++){
		if(Hunting::Data[mobid][Hunting::state] != HUNTING_STATE_DESTROYED) cnt++;
	}
	return cnt;
}

stock Hunting::GetFreeID(){
	for(new mobid = 1; mobid < MAX_HUNTING_ANIMALS; mobid++){
		if(Hunting::Data[mobid][Hunting::state] == HUNTING_STATE_DESTROYED) return mobid;
	}
	return INVALID_HUNTING_ID;
}

stock Hunting::Create(type,Float:x,Float:y,Float:z,Float:health,respawntime,worldid=-1,interiorid=-1,playerid=-1,Float:streamdistance=200.0,STREAMER_TAG_AREA moving_area = STREAMER_TAG_AREA INVALID_STREAMER_ID){
	new mobid = Hunting::GetFreeID();
	if(mobid == INVALID_HUNTING_ID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Failed to Hunting::Create limit %d exceeded, add #define MAX_HUNTING_ANIMALS before Hunting.inc",MAX_HUNTING_ANIMALS);
		}
		return mobid;
	}
	new Float:tmp_float,Float:target_z;
	MovePointCol(x,y,z,x,y,-100.0,tmp_float,tmp_float,target_z);
	z = target_z;
	switch(type){
		case HUNTING_TYPE_COW: {
			Hunting::Data[mobid][Hunting::objectid] = CreateDynamicObject(type,x,y,z,0.0,0.0,180.0,worldid,interiorid,playerid,streamdistance);
		}
		case HUNTING_TYPE_DEER: {
			z += 0.5;
			Hunting::Data[mobid][Hunting::objectid] = CreateDynamicObject(type,x,y,z,0.0,0.0,90.0,worldid,interiorid,playerid,streamdistance);
		}
	}
	Hunting::Data[mobid][Hunting::drop_area] = CreateDynamicSphere(x,y,z,3.0,worldid,interiorid,playerid);
	
	AttachDynamicAreaToObject(Hunting::Data[mobid][Hunting::drop_area],Hunting::Data[mobid][Hunting::objectid]);
	
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_EXTRA_ID,(mobid+HUNT_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::drop_area],E_STREAMER_EXTRA_ID,(mobid+HUNT_EXTRA_ID_OFFSET));
	
	Hunting::Data[mobid][Hunting::areaid] = moving_area;
	
	Hunting::Data[mobid][Hunting::type] = type;
	Hunting::Data[mobid][Hunting::respawntime] = respawntime;
	Hunting::Data[mobid][Hunting::health] = health;
	Hunting::Data[mobid][Hunting::max_health] = health;
	Hunting::Data[mobid][Hunting::drop] = 1;
	Hunting::Data[mobid][Hunting::respawn_tick] = 0;
	Hunting::Data[mobid][Hunting::X] = x;
	Hunting::Data[mobid][Hunting::Y] = y;
	Hunting::Data[mobid][Hunting::Z] = z;
	Hunting::Data[mobid][Hunting::tX] = x;
	Hunting::Data[mobid][Hunting::tY] = y;
	Hunting::Data[mobid][Hunting::rZ] = 0.0;
	
	if(mobid > Hunting::Upperbound) Hunting::Upperbound = mobid;
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_SPAWNED;
	
	return mobid;
}

stock Hunting::Respawn(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	Hunting::Data[mobid][Hunting::respawn_tick] = 0;
	Hunting::Data[mobid][Hunting::health] = Hunting::Data[mobid][Hunting::max_health];
	Hunting::SetDrop(mobid,1);
	SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::X],Hunting::Data[mobid][Hunting::Y],Hunting::Data[mobid][Hunting::Z]);
	
	Hunting::Data[mobid][Hunting::tX] = Hunting::Data[mobid][Hunting::X];
	Hunting::Data[mobid][Hunting::tY] = Hunting::Data[mobid][Hunting::Y];
	
	switch(Hunting::Data[mobid][Hunting::type]){
		case HUNTING_TYPE_COW: {
			SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,180.0);
		}
		case HUNTING_TYPE_DEER: {
			SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,90.0);
		}
	}
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_SPAWNED;
	CallRemoteFunction("OnHuntAnimalRespawn","d",mobid);
	return 1;
}

stock Hunting::Destroy(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(Hunting::Data[mobid][Hunting::state] == HUNTING_STATE_DESTROYED) return 0;
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_DESTROYED;
	
	if(IsValidDynamicObject(Hunting::Data[mobid][Hunting::objectid])) DestroyDynamicObject(Hunting::Data[mobid][Hunting::objectid]);
	if(IsValidDynamicArea(Hunting::Data[mobid][Hunting::drop_area])) DestroyDynamicArea(Hunting::Data[mobid][Hunting::drop_area]);
	if(IsValidDynamicArea(Hunting::Data[mobid][Hunting::areaid])) DestroyDynamicArea(Hunting::Data[mobid][Hunting::areaid]);
	
	Hunting::Data[mobid][Hunting::objectid] = STREAMER_TAG_OBJECT 0;
	Hunting::Data[mobid][Hunting::drop_area] = STREAMER_TAG_AREA 0;
	Hunting::Data[mobid][Hunting::areaid] = STREAMER_TAG_AREA 0;
	Hunting::Data[mobid][Hunting::type] = 0;
	Hunting::Data[mobid][Hunting::health] = 0.0;
	Hunting::Data[mobid][Hunting::max_health] = 0.0;
	Hunting::Data[mobid][Hunting::respawntime] = 0;
	Hunting::Data[mobid][Hunting::respawn_tick] = 0;
	Hunting::Data[mobid][Hunting::X] = 0.0;
	Hunting::Data[mobid][Hunting::Y] = 0.0;
	Hunting::Data[mobid][Hunting::Z] = 0.0;
	Hunting::Data[mobid][Hunting::tX] = 0.0;
	Hunting::Data[mobid][Hunting::tY] = 0.0;
	Hunting::Data[mobid][Hunting::rZ] = 0.0;
	
	if(mobid == Hunting::Upperbound) Hunting::Upperbound--;
	return 1;
}

stock Hunting::Kill(mobid,playerid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(Hunting::Data[mobid][Hunting::state] != HUNTING_STATE_SPAWNED) return 0;
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_DEAD;
	
	StopDynamicObject(Hunting::Data[mobid][Hunting::objectid]);
	
	
	new Float:tmp_float,Float:target_z,Float:x,Float:y,Float:z;
	Hunting::GetPos(mobid,x,y,z);
	MovePointCol(x,y,z,x,y,-100.0,tmp_float,tmp_float,target_z);
	
	switch(Hunting::Data[mobid][Hunting::type]){
		case HUNTING_TYPE_COW: {
			MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],x,y,target_z+0.3,0.5,0.0,90.0);
		}
		case HUNTING_TYPE_DEER: {
			MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],x,y,target_z+0.1,0.5,270.0);
		}
	}
	
	Hunting::Data[mobid][Hunting::respawn_tick] = GetTickCount() + (1000 * Hunting::Data[mobid][Hunting::respawntime]);
	
	CallRemoteFunction("OnPlayerKillHuntAnimal","dd",playerid,mobid);
	return 1;
}

T3D:function Hunting::OnUpdate(){
	static	Float:tmp_float,Float:target_z,
			Float:x,Float:y,Float:z,
			Float:tx,Float:ty,Float:tz,
			Float:vx,Float:vy,Float:vz;
	
	for(new mobid = 1; mobid <= Hunting::Upperbound; mobid++){
		switch(Hunting::Data[mobid][Hunting::state]){
			case HUNTING_STATE_SPAWNED: {
				Hunting::GetPos(mobid,x,y,z);
				MovePointCol(x,y,z,x,y,-100.0,tmp_float,tmp_float,target_z);
				if(GetDistanceBetweenPoints2D(Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],x,y) == 0.0){
					for(;;){
						GetRandomPointInCircle(x,y,25.0,tx,ty);
						Tryg3D::MapAndreasFindZ(tx,ty,tz);
						MovePointColCutLineEx(x,y,z,tx,ty,tz,vx,vy,vz,1.0);
						if(GetDistanceBetweenPoints2D(x,y,vx,vy) <= 2.0) continue;
						if(Hunting::Data[mobid][Hunting::areaid] != STREAMER_TAG_AREA INVALID_STREAMER_ID){
							if(!IsPointInDynamicArea(Hunting::Data[mobid][Hunting::areaid],vx,vy,vz)) continue;
						}
						Hunting::Data[mobid][Hunting::tX] = vx;
						Hunting::Data[mobid][Hunting::tY] = vy;
						GetRotationFor2Point2D(x,y,vx,vy,Hunting::Data[mobid][Hunting::rZ]);
						break;
					}
				}
				switch(Hunting::Data[mobid][Hunting::type]){
					case HUNTING_TYPE_COW: {
						SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,CompRotationFloat(Hunting::Data[mobid][Hunting::rZ]+180.0));
						MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],target_z,0.8);
					}
					case HUNTING_TYPE_DEER: {
						SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,CompRotationFloat(Hunting::Data[mobid][Hunting::rZ]+90.0));
						MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],target_z+0.5,0.8);
					}
				}
			}
			case HUNTING_STATE_DEAD: {
				if(Hunting::Data[mobid][Hunting::respawntime] != HUNTING_NO_AUTO_RESPAWN){
					if(Hunting::Data[mobid][Hunting::respawn_tick] != 0 && GetTickCount() >= Hunting::Data[mobid][Hunting::respawn_tick]){
						Hunting::Respawn(mobid);
					}
				}
			}
		}
	}
	return 1;
}


//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-HUNT_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
		if(Hunting::Data[mobid][Hunting::objectid] == objectid && Hunting::Data[mobid][Hunting::state] == HUNTING_STATE_SPAWNED){
			if(CallRemoteFunction("OnAnimalTakeDamage","ddfd",mobid,playerid,Tryg3D::GetWeaponDamage(weaponid),weaponid)){
				Hunting::Data[mobid][Hunting::health] -= Tryg3D::GetWeaponDamage(weaponid);
			}
			if(Hunting::Data[mobid][Hunting::health] <= 0.0){
				Hunting::Kill(mobid,playerid);
			}
		}
	}
	#if defined HUN_OnPlayerShootDynamicObject
		HUN_OnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject HUN_OnPlayerShootDynamicObject
#if defined HUN_OnPlayerShootDynamicObject
	forward HUN_OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA areaid){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-HUNT_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
		if(Hunting::Data[mobid][Hunting::drop_area] == areaid){
			CallRemoteFunction("OnPlayerApproachingAnimal","ddd",playerid,mobid,Hunting::Data[mobid][Hunting::state]);
		}
	}	
	#if defined HUN_OnPlayerEnterDynamicArea
		HUN_OnPlayerEnterDynamicArea(playerid, areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea HUN_OnPlayerEnterDynamicArea
#if defined HUN_OnPlayerEnterDynamicArea
	forward HUN_OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA areaid);
#endif

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(Tryg3D::KeyPressed(Hunting::Key)){
		new max_areas = GetPlayerNumberDynamicAreas(playerid);
		if(max_areas){
			new STREAMER_TAG_AREA player_areas[64], mobid;
			GetPlayerDynamicAreas(playerid,player_areas,max_areas);
			for(new k = 0; k < max_areas; k++){
				mobid = Streamer_GetIntData(STREAMER_TYPE_AREA,player_areas[k],E_STREAMER_EXTRA_ID)-HUNT_EXTRA_ID_OFFSET;
				if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
					if(player_areas[k] == Hunting::Data[mobid][Hunting::drop_area]){
						if(Hunting::Data[mobid][Hunting::state] == HUNTING_STATE_DEAD){
							CallRemoteFunction("OnPlayerTakeHuntDrop","ddd",playerid,mobid,Hunting::Data[mobid][Hunting::drop]);
						}
						break;
					}
				}
				mobid = 0;
			}
		}
	}
	#if defined HUN_OnPlayerKeyStateChange
		HUN_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange HUN_OnPlayerKeyStateChange
#if defined HUN_OnPlayerKeyStateChange
	forward HUN_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

new bool:CRC_HuntingInit = true,
	bool:CRC_HuntingExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_HuntingInit){
		CRC_HuntingInit = false;
		Hunting::Timer = SetTimerEx("Hunt_OnUpdate",HUNTING_UPDATE_INTERVAL,true,"");
	}
	#if defined HUN_OnFilterScriptInit
		HUN_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit HUN_OnFilterScriptInit
#if defined HUN_OnFilterScriptInit
	forward HUN_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_HuntingInit){
		CRC_HuntingInit = false;
		Hunting::Timer = SetTimerEx("Hunt_OnUpdate",HUNTING_UPDATE_INTERVAL,true,"");
	}
	#if defined HUN_OnGameModeInit
		HUN_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit HUN_OnGameModeInit
#if defined HUN_OnGameModeInit
	forward HUN_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_HuntingExit){
		CRC_HuntingExit = false;
		KillTimer(Hunting::Timer);
	}
	#if defined HUN_OnFilterScriptExit
		HUN_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit HUN_OnFilterScriptExit
#if defined HUN_OnFilterScriptExit
	forward HUN_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_HuntingExit){
		CRC_HuntingExit = false;
		KillTimer(Hunting::Timer);
	}
	#if defined HUN_OnGameModeExit
		HUN_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit HUN_OnGameModeExit
#if defined HUN_OnGameModeExit
	forward HUN_OnGameModeExit();
#endif

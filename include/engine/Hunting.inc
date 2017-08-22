/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                         Hunting System                                                         *
 *                                                                                                                                *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 * Publication: http://forum.sa-mp.com/showthread.php?t=639694                                                                    *
 * Website: http://8.ct8.pl                                                                                                       *
 *                                                                                                                                *
 * Plugins: Streamer, ColAndreas                                                                                                  *
 * Modules: 3DTryg                                                                                                                *
 *                                                                                                                                *
 * File Version: 1.1.0                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * Streamer Version: 2.9.1                                                                                                        *
 * ColAndreas Version: 1.4.0                                                                                                      *
 * 3DTryg Version: 4.4.3                                                                                                          *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * Hunting::Create(type,Float:x,Float:y,Float:z,Float:health,respawntime,worldid=-1,interiorid=-1,playerid=-1,                    *
 *                 Float:streamdistance=200.0,moving_area = 0);                                                                   *
 * Hunting::Destroy(mobid);                                                                                                       *
 * Hunting::Respawn(mobid);                                                                                                       *
 * Hunting::Kill(mobid,playerid);                                                                                                 *
 * Hunting::Stop(mobid);                                                                                                          *
 * Hunting::GoTo(mobid,Float:x,Float:y,bool:area_check=true,bool:disable_moving=false);                                           *
 * Hunting::GetDrop(mobid);                                                                                                       *
 * Hunting::SetDrop(mobid,drop);                                                                                                  *
 * Hunting::GetPos(mobid,Float:x,Float:y,Float:z);                                                                                *
 * Hunting::ToggleMoving(mobid,toggle);                                                                                           *
 * Hunting::IsToggledMoving(mobid);                                                                                               *
 * Hunting::GetHealth(mobid);                                                                                                     *
 * Hunting::SetHealth(mobid,Float:health);                                                                                        *
 * Hunting::GetSpawnHealth(mobid);                                                                                                *
 * Hunting::SetSpawnHealth(mobid,Float:health);                                                                                   *
 * Hunting::GetRespawnTime(mobid);                                                                                                *
 * Hunting::SetRespawnTime(mobid,respawntime);                                                                                    *
 * Hunting::GetSpawn(mobid,&Float:x,&Float:y,&Float:z);                                                                           *
 * Hunting::SetSpawn(mobid,Float:x,Float:y,Float:z);                                                                              *
 * Hunting::GetInterior(mobid);                                                                                                   *
 * Hunting::SetInterior(mobid,interiorid);                                                                                        *
 * Hunting::GetVirtualWorld(mobid);                                                                                               *
 * Hunting::SetVirtualWorld(mobid,worldid);                                                                                       *
 * Hunting::GetSpeed(mobid);                                                                                                      *
 * Hunting::SetSpeed(mobid,Float:speed);                                                                                          *
 * Hunting::IsValid(mobid);                                                                                                       *
 * Hunting::IsSpawned(mobid);                                                                                                     *
 * Hunting::IsDead(mobid);                                                                                                        *
 *                                                                                                                                *
 * Extended Functions:                                                                                                            *
 * Hunting::Count();                                                                                                              *
 * Hunting::GetKey();                                                                                                             *
 * Hunting::SetKey(key);                                                                                                          *
 * Hunting::GetFreeID();                                                                                                          *
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
	Float:Hunting::rZ,
	Float:Hunting::speed,
	Hunting::moving,
	Hunting::calm
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

#define Hunt_ToggleMoving(%0,%1)				Hunting::Data[(%0)][Hunting::moving] = (%1)
#define Hunt_IsToggledMoving(%0)				Hunting::Data[(%0)][Hunting::moving]

#define Hunt_GetPos(%0,%1,%2,%3)				GetDynamicObjectPos(Hunting::Data[(%0)][Hunting::objectid],(%1),(%2),(%3))

#define Hunt_Stop(%0)							StopDynamicObject(Hunting::Data[(%0)][Hunting::objectid])

#define Hunt_GetHealth(%0)						Hunting::Data[(%0)][Hunting::health]
#define Hunt_SetHealth(%0,%1)					Hunting::Data[(%0)][Hunting::health] = (%1)

#define Hunt_GetSpawnHealth(%0)					Hunting::Data[(%0)][Hunting::max_health]
#define Hunt_SetSpawnHealth(%0,%1)				Hunting::Data[(%0)][Hunting::max_health] = (%1)

#define Hunt_GetRespawnTime(%0)					Hunting::Data[(%0)][Hunting::respawntime]
#define Hunt_SetRespawnTime(%0,%1)				Hunting::Data[(%0)][Hunting::respawntime] = (%1)

#define Hunt_IsValid(%0)						(Hunting::Data[(%0)][Hunting::state] != HUNTING_STATE_DESTROYED)
#define Hunt_IsSpawned(%0)						(Hunting::Data[(%0)][Hunting::state] == HUNTING_STATE_SPAWNED)
#define Hunt_IsDead(%0)							(Hunting::Data[(%0)][Hunting::state] == HUNTING_STATE_DEAD)

#define Hunt_GetInterior(%0)					Streamer_GetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[(%0)][Hunting::objectid],E_STREAMER_INTERIOR_ID)
#define Hunt_GetVirtualWorld(%0)				Streamer_GetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[(%0)][Hunting::objectid],E_STREAMER_WORLD_ID)

#define Hunt_GetSpeed(%0)						Hunting::Data[(%0)][Hunting::speed]
#define Hunt_SetSpeed(%0,%1)					Hunting::Data[(%0)][Hunting::speed] = (%1)

stock Hunting::Count(){
	new cnt = 0;
	for(new mobid = 1; mobid <= Hunting::Upperbound; mobid++){
		if(Hunting::IsValid(mobid)) cnt++;
	}
	return cnt;
}

stock Hunting::GetFreeID(){
	for(new mobid = 1; mobid < MAX_HUNTING_ANIMALS; mobid++){
		if(!Hunting::IsValid(mobid)) return mobid;
	}
	return INVALID_HUNTING_ID;
}

stock Hunting::SetSpawn(mobid,Float:x,Float:y,Float:z){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	Hunting::Data[mobid][Hunting::X] = x;
	Hunting::Data[mobid][Hunting::Y] = y;
	Hunting::Data[mobid][Hunting::Z] = z;
	return 1;
}

stock Hunting::GetSpawn(mobid,&Float:x,&Float:y,&Float:z){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	x = Hunting::Data[mobid][Hunting::X];
	y = Hunting::Data[mobid][Hunting::Y];
	z = Hunting::Data[mobid][Hunting::Z];
	return 1;
}

stock Hunting::SetInterior(mobid,interiorid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_INTERIOR_ID,interiorid);
	Streamer_SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::drop_area],E_STREAMER_INTERIOR_ID,interiorid);
	return 1;
}

stock Hunting::SetVirtualWorld(mobid,worldid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_WORLD_ID,worldid);
	Streamer_SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::drop_area],E_STREAMER_WORLD_ID,worldid);
	return 1;
}

stock Hunting::GoTo(mobid,Float:x,Float:y,bool:area_check=true,bool:disable_moving=false){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsSpawned(mobid)) return 0;
	
	new Float:z;
	Tryg3D::MapAndreasFindZ(x,y,z);
	if(IsPointInWater(x,y)) return 0;
	if(area_check && Hunting::Data[mobid][Hunting::areaid] != STREAMER_TAG_AREA INVALID_STREAMER_ID){
		if(!IsPointInDynamicArea(Hunting::Data[mobid][Hunting::areaid],x,y,z)) return 0;
	}
	
	new Float:vx,Float:vy,Float:vz,
		tmp_moving = Hunting::IsToggledMoving(mobid);
	
	Hunting::ToggleMoving(mobid,0);
	Hunting::Stop(mobid);
	Hunting::GetPos(mobid,vx,vy,vz);
	
	Hunting::Data[mobid][Hunting::tX] = x;
	Hunting::Data[mobid][Hunting::tY] = y;
	GetRotationFor2Point2D(vx,vy,x,y,Hunting::Data[mobid][Hunting::rZ]);
	
	if(!disable_moving){
		Hunting::ToggleMoving(mobid,1);
	} else {
		Hunting::ToggleMoving(mobid,tmp_moving);
	}
	return 1;
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
			Hunting::Data[mobid][Hunting::objectid] = CreateDynamicObject(type,x,y,z,0.0,0.0,184.0,worldid,interiorid,playerid,streamdistance);
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
	Hunting::Data[mobid][Hunting::tX] = x;
	Hunting::Data[mobid][Hunting::tY] = y;
	Hunting::Data[mobid][Hunting::rZ] = 0.0;
	Hunting::Data[mobid][Hunting::moving] = 1;
	Hunting::Data[mobid][Hunting::speed] = 0.8;
	Hunting::Data[mobid][Hunting::calm] = 0;
	
	Hunting::SetSpawn(mobid,x,y,z);
	
	if(mobid > Hunting::Upperbound) Hunting::Upperbound = mobid;
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_SPAWNED;
	
	return mobid;
}

stock Hunting::Destroy(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(Hunting::Data[mobid][Hunting::state] == HUNTING_STATE_DESTROYED) return 0;
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_DESTROYED;
	
	if(IsValidDynamicObject(Hunting::Data[mobid][Hunting::objectid])) DestroyDynamicObject(Hunting::Data[mobid][Hunting::objectid]);
	if(IsValidDynamicArea(Hunting::Data[mobid][Hunting::drop_area])) DestroyDynamicArea(Hunting::Data[mobid][Hunting::drop_area]);
	
	Hunting::Data[mobid][Hunting::objectid] = STREAMER_TAG_OBJECT 0;
	Hunting::Data[mobid][Hunting::drop_area] = STREAMER_TAG_AREA 0;
	Hunting::Data[mobid][Hunting::areaid] = STREAMER_TAG_AREA 0;
	Hunting::Data[mobid][Hunting::type] = 0;
	Hunting::Data[mobid][Hunting::health] = 0.0;
	Hunting::Data[mobid][Hunting::max_health] = 0.0;
	Hunting::Data[mobid][Hunting::respawntime] = 0;
	Hunting::Data[mobid][Hunting::respawn_tick] = 0;
	Hunting::Data[mobid][Hunting::tX] = 0.0;
	Hunting::Data[mobid][Hunting::tY] = 0.0;
	Hunting::Data[mobid][Hunting::rZ] = 0.0;
	Hunting::Data[mobid][Hunting::moving] = 0;
	Hunting::Data[mobid][Hunting::speed] = 0.8;
	Hunting::Data[mobid][Hunting::calm] = 0;
	
	Hunting::SetSpawn(mobid,0.0,0.0,0.0);
	
	if(mobid == Hunting::Upperbound) Hunting::Upperbound--;
	return 1;
}

stock Hunting::Respawn(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	Hunting::Data[mobid][Hunting::respawn_tick] = 0;
	Hunting::Data[mobid][Hunting::health] = Hunting::Data[mobid][Hunting::max_health];
	Hunting::SetDrop(mobid,1);
	
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],0,0,"","",0);
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],1,0,"","",0);
	new modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_MODEL_ID);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_MODEL_ID,modelid);

	SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::X],Hunting::Data[mobid][Hunting::Y],Hunting::Data[mobid][Hunting::Z]);
	
	Hunting::Data[mobid][Hunting::tX] = Hunting::Data[mobid][Hunting::X];
	Hunting::Data[mobid][Hunting::tY] = Hunting::Data[mobid][Hunting::Y];
	
	switch(Hunting::Data[mobid][Hunting::type]){
		case HUNTING_TYPE_COW: {
			SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,184.0);
		}
		case HUNTING_TYPE_DEER: {
			SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,90.0);
		}
	}
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_SPAWNED;
	CallRemoteFunction("OnHuntAnimalRespawn","d",mobid);
	return 1;
}

stock Hunting::Kill(mobid,playerid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsSpawned(mobid)) return 0;
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_DEAD;
	Hunting::Data[mobid][Hunting::health] = 0.0;
	
	Hunting::Stop(mobid);
	
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],0,2806,"CJ_MEATY","CJ_FLESH_1",0);
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],1,2806,"CJ_MEATY","CJ_FLESH_1",0);
	
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
			Float:tx,Float:ty,
			Float:vx,Float:vy,Float:vz;
	
	for(new mobid = 1; mobid <= Hunting::Upperbound; mobid++){
		switch(Hunting::Data[mobid][Hunting::state]){
			case HUNTING_STATE_SPAWNED: {
				target_z = 0.0;
				Hunting::GetPos(mobid,x,y,z);
				MovePointCol(x,y,z+1.0,x,y,-100.0,tmp_float,tmp_float,target_z);
				if(Hunting::IsToggledMoving(mobid)){
					if(GetDistanceBetweenPoints2D(Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],x,y) == 0.0){
						for(;;){
							vx = vy = vz = 0.0;
							GetRandomPointInCircle(x,y,25.0,tx,ty);
							MovePointColCutLineEx(x,y,z+1.0,tx,ty,z+1.0,vx,vy,vz,3.0);
							if(GetDistanceBetweenPoints2D(x,y,vx,vy) <= 2.0) continue;
							if(IsPointInWater(vx,vy)) continue;
							if(Hunting::Data[mobid][Hunting::areaid] != STREAMER_TAG_AREA INVALID_STREAMER_ID){
								if(!IsPointInDynamicArea(Hunting::Data[mobid][Hunting::areaid],vx,vy,vz)) continue;
							}
							Hunting::Data[mobid][Hunting::tX] = vx;
							Hunting::Data[mobid][Hunting::tY] = vy;
							GetRotationFor2Point2D(x,y,vx,vy,Hunting::Data[mobid][Hunting::rZ]);
							break;
						}
					}
				}
				if(GetTickCount() >= Hunting::Data[mobid][Hunting::calm]){
					Hunting::SetSpeed(mobid,0.8);
				}
				switch(Hunting::Data[mobid][Hunting::type]){
					case HUNTING_TYPE_COW: {
						SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],x,y,target_z);
						SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,CompRotationFloat(Hunting::Data[mobid][Hunting::rZ]+184.0));
						MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],target_z,Hunting::GetSpeed(mobid));
					}
					case HUNTING_TYPE_DEER: {
						SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],x,y,target_z+0.5);
						SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,CompRotationFloat(Hunting::Data[mobid][Hunting::rZ]+90.0));
						MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],target_z+0.5,Hunting::GetSpeed(mobid));
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
		if(Hunting::Data[mobid][Hunting::objectid] == objectid && Hunting::IsSpawned(mobid)){
			Hunting::SetSpeed(mobid,8.0);
			if(CallRemoteFunction("OnAnimalTakeDamage","ddfd",mobid,playerid,Tryg3D::GetWeaponDamage(weaponid),weaponid)){
				Hunting::Data[mobid][Hunting::health] -= Tryg3D::GetWeaponDamage(weaponid);
			}
			Hunting::Data[mobid][Hunting::calm] = GetTickCount() + 30000;
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
						if(Hunting::IsDead(mobid)){
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

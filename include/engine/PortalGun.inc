/****************************************************************************************************
 *                                                                                                  *
 *                                        Portal Gun Script                                         *
 *                                                                                                  *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                        *
 * Publication: http://forum.sa-mp.com/showthread.php?p=3862804                                     *
 *                                                                                                  *
 * Plugins: Streamer, ColAndreas                                                                    *
 * Modules: 3DTryg                                                                                  *
 * Attributes: None                                                                                 *
 *                                                                                                  *
 * File Version: 1.0.0                                                                              *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                   *
 * Streamer Version: 2.9.0                                                                          *
 * ColAndreas Version: 1.4.0                                                                        *
 * 3DTryg Version: 4.0.4                                                                            *
 *                                                                                                  *
 * Functions:                                                                                       *
 * TogglePrivatePortalGun(bool:toggle);            //default: false                                 *
 * bool:IsTogglePrivatePortalGun();                                                                 *
 * TogglePortalGunForAll(bool:toggle);             //default: true                                  *
 * bool:IsTogglePortalGunForAll();                                                                  *
 * TogglePortalGunForPlayer(playerid,bool:toggle); //default: false                                 *
 * bool:IsTogglePortalGunForPlayer(playerid);                                                       *
 * Float:GetPortalGunSpeed(playerid);                                                               *
 * SetPortalGunSpeed(playerid,Float:speed);                                                         *
 * ForceClosePortalGunRing(playerid);                                                               *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _portal_gun
	#endinput
#endif
#define _portal_gun

#if (!defined GetPlayerPoolSize)
	#error [ADM] This include requires SA:MP version 0.3.7
#endif

#if ((defined Streamer_AppendArrayData) && (defined INVALID_STREAMER_ID) && (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] You need Streamer v2.9.0
#endif

#if !defined COLANDREAS
	#error [ADM] You need ColAndreas v1.4.0
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v4.0.4
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v4.0.4
#elseif (Tryg3D_Version < 40004)
	#error [ADM] Update you 3DTryg.inc to v4.0.4
#endif

#define PG_GetValueBit(%0,%1)					((%0) >>> (%1) & 0x01)
#define PG_SetValueBit(%0,%1,%2)				((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define PG_GetConfigAddress(%0)					(floatround((%0)/32))
#define PG_GetConfigBit(%0)						((%0) % 32)
#define PG_GetConfigSize(%0)					(((%0) / 32)+1)

#define PG_IsToggleConfigInformation(%0,%1)		PG_GetValueBit(%0[PG_GetConfigAddress(%1)],PG_GetConfigBit(%1))
#define PG_ToggleConfigInformation(%0,%1,%2)	PG_SetValueBit(%0[PG_GetConfigAddress(%1)],PG_GetConfigBit(%1),((%2) & 0x1))

#define PORTAL_EXTRA_ID_OFFSET					(400000)
#define PORTAL_GUN_SPEED 						(25.0)
#define PORTAL_GUN_BLUE							(0)
#define PORTAL_GUN_ORANGE						(1)

new PortalGunRing[MAX_PLAYERS][2],
	PortalGunZone[MAX_PLAYERS][2],
	PortalGunTick[MAX_PLAYERS][2],
	PlayerInPortal[MAX_PLAYERS],
	Float:PortalGunSpeed[MAX_PLAYERS],
	PortalEnabledForPlayer[PG_GetConfigSize(MAX_PLAYERS)],
	PlayerPortalType[PG_GetConfigSize(MAX_PLAYERS)],
	bool:PortalEnabledForAll = true,
	bool:PrivatePortalGun = false;

#define TogglePrivatePortalGun(%0)			PrivatePortalGun = (%0)
#define IsTogglePrivatePortalGun()			PrivatePortalGun
#define TogglePortalGunForAll(%0)			PortalEnabledForAll = (%0)
#define IsTogglePortalGunForAll()			PortalEnabledForAll
#define TogglePortalGunForPlayer(%0,%1)		PG_ToggleConfigInformation(PortalEnabledForPlayer,(%0),(%1))
#define IsTogglePortalGunForPlayer(%0)		PG_IsToggleConfigInformation(PortalEnabledForPlayer,(%0))
#define SetPortalGunType(%0,%1)				PG_ToggleConfigInformation(PlayerPortalType,(%0),(%1))
#define GetPortalGunType(%0)				PG_IsToggleConfigInformation(PlayerPortalType,(%0))
#define GetPortalGunSpeed(%0)				PortalGunSpeed[(%0)]
#define SetPortalGunSpeed(%0,%1)			PortalGunSpeed[(%0)] = (%1)

T3D:function ForceClosePortalGunRing(playerid){
	if(IsValidDynamicObject(PortalGunRing[playerid][0])) DestroyDynamicObject(PortalGunRing[playerid][0]);
	if(IsValidDynamicObject(PortalGunRing[playerid][1])) DestroyDynamicObject(PortalGunRing[playerid][1]);
	PortalGunRing[playerid][0] = PortalGunRing[playerid][1] = INVALID_STREAMER_ID;
	
	if(IsValidDynamicArea(PortalGunZone[playerid][0])) DestroyDynamicArea(PortalGunZone[playerid][0]);
	if(IsValidDynamicArea(PortalGunZone[playerid][1])) DestroyDynamicArea(PortalGunZone[playerid][1]);
	PortalGunZone[playerid][0] = PortalGunZone[playerid][1] = INVALID_STREAMER_ID;
	return 1;
}

T3D:function PortalGunInit(){
	for(new i = 0; i < MAX_PLAYERS; i++){
		SetPortalGunSpeed(i,PORTAL_GUN_SPEED);
	}
}

new CRC_PortalInit = true;

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(IsTogglePortalGunForAll() || IsTogglePortalGunForPlayer(playerid)){
		if(GetPlayerWeapon(playerid) == 33 && !IsPlayerInAnyVehicle(playerid)){
			if(Tryg3D_KeyPressed(KEY_YES)){
				if(GetPortalGunType(playerid)){
					SetPortalGunType(playerid,PORTAL_GUN_BLUE);
					GameTextForPlayer(playerid,"~b~Portal Gun Ring",1500,4);
				} else {
					SetPortalGunType(playerid,PORTAL_GUN_ORANGE);
					GameTextForPlayer(playerid,"~r~~h~~h~Portal Gun Ring",1500,4);
				}
			}
		}
	}
	#if defined PG_OnPlayerKeyStateChange
		PG_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange PG_OnPlayerKeyStateChange
#if defined PG_OnPlayerKeyStateChange
	forward PG_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: OnPlayerWeaponShot
public OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,Float:fX,Float:fY,Float:fZ){
	if(IsTogglePortalGunForAll() || IsTogglePortalGunForPlayer(playerid)){
		if(weaponid == 33){
			new portal_id, F4[Float3D];
			if(!(fX == 0.0 || fY == 0.0 || fZ == 0.0)){
				switch(hittype){
					case BULLET_HIT_TYPE_VEHICLE, BULLET_HIT_TYPE_OBJECT, BULLET_HIT_TYPE_PLAYER_OBJECT, BULLET_HIT_TYPE_PLAYER: {
						GetPlayerLastShotVectors(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
					}
					default: {
						GetPlayerLastShotVectors(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
						F4[T3D:tX] = fX, F4[T3D:tY] = fY, F4[T3D:tZ] = fZ;
					}
				}
			}
			if(!(F4[T3D:X] == 0.0 || F4[T3D:Y] == 0.0 || F4[T3D:Z] == 0.0)){
				if(GetPortalGunType(playerid)){
					portal_id = PORTAL_GUN_ORANGE;
				} else {
					portal_id = PORTAL_GUN_BLUE;
				}
				F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
				F4[T3D:INT] = GetPlayerInterior(playerid);
				
				MovePointColCutLine(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],0.1);
				
				PortalGunTick[playerid][portal_id] = GetTickCount();
				if(IsValidDynamicObject(PortalGunRing[playerid][portal_id])) DestroyDynamicObject(PortalGunRing[playerid][portal_id]);
				if(IsValidDynamicArea(PortalGunZone[playerid][portal_id])) DestroyDynamicArea(PortalGunZone[playerid][portal_id]);

				if(IsPointInGround(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],(F4[T3D:INT] != 0),2.2)){
					GetGroundRotation(F4[T3D:tX],F4[T3D:tY],1.0,F4[T3D:rX],F4[T3D:rZ]);
					F4[T3D:rZ] = CompRotationFloat(F4[T3D:rZ]+180.0);
				} else {
					GetRotationFor2Point3D(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],F4[T3D:rX],F4[T3D:rZ]);
					F4[T3D:rX] = CompRotationFloat(F4[T3D:rX]+90.0);
				}
				
				PortalGunRing[playerid][portal_id] = CreateDynamicObject(1316,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rX],0.0,F4[T3D:rZ],F4[T3D:VW],F4[T3D:INT],-1,100.0);
				if(portal_id == PORTAL_GUN_ORANGE){
					SetDynamicObjectMaterial(PortalGunRing[playerid][portal_id],0,1316,"ingame","CJ_W_GRAD",0xFFFF6600);
				} else {
					SetDynamicObjectMaterial(PortalGunRing[playerid][portal_id],0,1316,"ingame","CJ_W_GRAD",0xFF00FFFF);
				}
				PortalGunZone[playerid][portal_id] = CreateDynamicSphere(0.0,0.0,-6000.0,1.5,F4[T3D:VW],F4[T3D:INT],-1);
				AttachDynamicAreaToObject(PortalGunZone[playerid][portal_id],PortalGunRing[playerid][portal_id]);
				Streamer_SetIntData(STREAMER_TYPE_AREA,PortalGunZone[playerid][portal_id],E_STREAMER_EXTRA_ID,playerid+PORTAL_EXTRA_ID_OFFSET);
				MoveDynamicObject(PortalGunRing[playerid][portal_id],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],GetPortalGunSpeed(playerid));
			}
		}
	}
	#if defined PG_OnPlayerWeaponShot
		PG_OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,fX,fY,fZ);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot PG_OnPlayerWeaponShot
#if defined PG_OnPlayerWeaponShot
	forward PG_OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,fX,fY,fZ);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,areaid){
	new pstate = GetPlayerState(playerid);
	if(pstate != 1 && pstate != 2 && pstate != 3) return 1;
	
	new targetid = (Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-PORTAL_EXTRA_ID_OFFSET);
	if(targetid >= 0 && targetid < MAX_PLAYERS){
		if((PrivatePortalGun && playerid == targetid) || !PrivatePortalGun){
			new portal_id = -1;
			if(PortalGunZone[targetid][PORTAL_GUN_ORANGE] == areaid){
				portal_id = PORTAL_GUN_BLUE;
			} else if(PortalGunZone[targetid][PORTAL_GUN_BLUE] == areaid){
				portal_id = PORTAL_GUN_ORANGE;
			}
			if(portal_id != -1 && IsValidDynamicObject(PortalGunRing[targetid][portal_id]) && !IsDynamicObjectMoving(PortalGunRing[targetid][portal_id])){
				if((GetTickCount()-PortalGunTick[targetid][portal_id] >= 10000) && (GetTickCount()-PlayerInPortal[playerid] >= 2000)){
					PlayerInPortal[playerid] = GetTickCount();
					new F4[Float3D];
					GetDynamicObjectPos(PortalGunRing[targetid][portal_id],F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
					GetDynamicObjectRot(PortalGunRing[targetid][portal_id],F4[T3D:rX],F4[T3D:rY],F4[T3D:rZ]);
					F4[T3D:VW] = Streamer_GetIntData(STREAMER_TYPE_OBJECT,PortalGunRing[targetid][portal_id],E_STREAMER_WORLD_ID);
					F4[T3D:INT] = Streamer_GetIntData(STREAMER_TYPE_OBJECT,PortalGunRing[targetid][portal_id],E_STREAMER_INTERIOR_ID);
					
					F4[T3D:rX] = CompRotationFloat(F4[T3D:rX]+90.0);
					
					if(IsPlayerInAnyVehicle(playerid)){
						new Float:T3D:x,Float:T3D:y,Float:T3D:z;
						GetVehicleModelInfo(GetVehicleModel(GetPlayerVehicleID(playerid)),VEHICLE_MODEL_INFO_SIZE,T3D:x,T3D:y,T3D:z);
						GetPointInFront3D(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rX],F4[T3D:rZ],((T3D:y+1.0)/2.0),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
						GetRotationFor2Point2D(F4[T3D:X],F4[T3D:Y],F4[T3D:tX],F4[T3D:tY],F4[T3D:rZ]);
						SetPlayerAbsolutePositionVeh(playerid,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],F4[T3D:rZ],F4[T3D:VW],F4[T3D:INT],500);
					} else {
						GetPointInFront3D(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rX],F4[T3D:rZ],2.0,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
						GetRotationFor2Point2D(F4[T3D:X],F4[T3D:Y],F4[T3D:tX],F4[T3D:tY],F4[T3D:rZ]);
						SetPlayerAbsolutePosition(playerid,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],F4[T3D:rZ],F4[T3D:VW],F4[T3D:INT],500);
					}
				}
			}
		}
	}	
	#if defined PG_OnPlayerEnterDynamicArea
		PG_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_PortalInit){
		CRC_PortalInit = false;
		PortalGunInit();
	}
	#if defined PG_OnFilterScriptInit
		PG_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit PG_OnFilterScriptInit
#if defined PG_OnFilterScriptInit
	forward PG_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_PortalInit){
		CRC_PortalInit = false;
		PortalGunInit();
	}
	#if defined PG_OnGameModeInit
		PG_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit PG_OnGameModeInit
#if defined PG_OnGameModeInit
	forward PG_OnGameModeInit();
#endif

//EOF
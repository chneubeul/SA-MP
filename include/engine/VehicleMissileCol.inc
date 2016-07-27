/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                         Vehicle Missile Launcher (ColAndreas Version)                                          *
 *                                                                                                                                *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 *                                                                                                                                *
 * Plugins: Streamer, ColAndreas                                                                                                  *
 * Modules: 3DTryg, Missile                                                                                                       *
 *                                                                                                                                *
 * File Version: 1.5.2                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * Streamer Version: 2.8.2                                                                                                        *
 * ColAndreas Version: 1.4.0                                                                                                      *
 * 3DTryg Version: 2.7.3                                                                                                          *
 * Missile Version: 1.6.4                                                                                                         *
 *                                                                                                                                *
 * Vehicle Weapons:                                                                                                               *
 * - Mini Missile (Dual rocket)                                                                                                   *
 * - Heavy Missile (Six rocket of high firepower)                                                                                 *
 * - Rhino Missile (Rhino explosion)                                                                                              *
 * - Bomber Missile (Quadruple-ground missiles)                                                                                   *
 * - Mortar Missile (Marica mortar)                                                                                               *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * ToggleVehicleMiniMissile(vehicleid,toggle);                                                                                    *
 * ToggleVehicleHeavyMissile(vehicleid,toggle);                                                                                   *
 * ToggleVehicleRhinoMissile(vehicleid,toggle);                                                                                   *
 * ToggleVehicleBomberMissile(vehicleid,toggle);                                                                                  *
 * ToggleVehicleMortarMissile(vehicleid,toggle);                                                                                  *
 * IsToggleVehicleMiniMissile(vehicleid);                                                                                         *
 * IsToggleVehicleHeavyMissile(vehicleid);                                                                                        *
 * IsToggleVehicleRhinoMissile(vehicleid);                                                                                        *
 * IsToggleVehicleBomberMissile(vehicleid);                                                                                       *
 * IsToggleVehicleMortarMissile(vehicleid);                                                                                       *
 *                                                                                                                                *
 * Float:GetVehicleMiniMissileSpeed(vehicleid);                                                                                   *
 * Float:GetVehicleHeavyMissileSpeed(vehicleid);                                                                                  *
 * Float:GetVehicleBomberMissileSpeed(vehicleid);                                                                                 *
 * Float:GetVehicleMortarMissileSpeed(vehicleid);                                                                                 *
 * SetVehicleMiniMissileSpeed(vehicleid,Float:speed);                                                                             *
 * SetVehicleHeavyMissileSpeed(vehicleid,Float:speed);                                                                            *
 * SetVehicleBomberMissileSpeed(vehicleid,Float:speed);                                                                           *
 * SetVehicleMortarMissileSpeed(vehicleid,Float:speed);                                                                           *
 *                                                                                                                                *
 * GetVehicleMiniMissileReload(vehicleid);                                                                                        *
 * GetVehicleHeavyMissileReload(vehicleid);                                                                                       *
 * GetVehicleBomberMissileReload(vehicleid);                                                                                      *
 * GetVehicleRhinoMissileReload(vehicleid);                                                                                       *
 * GetVehicleMortarMissileReload(vehicleid);                                                                                      *
 * SetVehicleMiniMissileReload(vehicleid,time);                                                                                   *
 * SetVehicleHeavyMissileReload(vehicleid,time);                                                                                  *
 * SetVehicleBomberMissileReload(vehicleid,time);                                                                                 *
 * SetVehicleRhinoMissileReload(vehicleid,time);                                                                                  *
 * SetVehicleMortarMissileReload(vehicleid,time);                                                                                 *
 *                                                                                                                                *
 * Float:GetVehicleMiniMissileDistance(vehicleid);                                                                                *
 * Float:GetVehicleHeavyMissileDistance(vehicleid);                                                                               *
 * Float:GetVehicleBomberMissileDistance(vehicleid);                                                                              *
 * Float:GetVehicleRhinoMissileDistance(vehicleid);                                                                               *
 * Float:GetVehicleMortarMissileDistance(vehicleid);                                                                              *
 * SetVehicleMiniMissileDistance(vehicleid,Float:distance);                                                                       *
 * SetVehicleHeavyMissileDistance(vehicleid,Float:distance);                                                                      *
 * SetVehicleBomberMissileDistance(vehicleid,Float:distance);                                                                     *
 * SetVehicleRhinoMissileDistance(vehicleid,Float:distance);                                                                      *
 * SetVehicleMortarMissileDistance(vehicleid,Float:distance);                                                                     *
 *                                                                                                                                *
 * GetVehicleMiniMissileKey(vehicleid);                                                                                           *
 * GetVehicleHeavyMissileKey(vehicleid);                                                                                          *
 * GetVehicleBomberMissileKey(vehicleid);                                                                                         *
 * GetVehicleRhinoMissileKey(vehicleid);                                                                                          *
 * GetVehicleMortarMissileKey(vehicleid);                                                                                         *
 * SetVehicleMiniMissileKey(vehicleid,key);                                                                                       *
 * SetVehicleHeavyMissileKey(vehicleid,key);                                                                                      *
 * SetVehicleBomberMissileKey(vehicleid,key);                                                                                     *
 * SetVehicleRhinoMissileKey(vehicleid,key);                                                                                      *
 * SetVehicleMortarMissileKey(vehicleid,key);                                                                                     *
 *                                                                                                                                *
 * Float:GetVehicleMortarMissileHeight(vehicleid);                                                                                *
 * SetVehicleMortarMissileHeight(vehicleid,Float:height);                                                                         *
 *                                                                                                                                *
 * Float:GetMissileStreamDistance();                                                                                              *
 * SetMissileStreamDistance(Float:streamdistance);                                                                                *
 * DisarmVehicleMissile(vehicleid);                                                                                               *
 *                                                                                                                                *
 * OnVehicleShot(playerid,type);                                                                                                  *
 * OnVehicleMissileInit();                                                                                                        *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if !defined Streamer_AppendArrayData
	#error [ADM] Unknown Streamer Version
#endif

#if !defined COLANDREAS
	#error [ADM] Unknown ColAndreas Version
#endif

//Check Version Missile.inc
#if !defined _missile_launcher
	#error [ADM] You need Missile.inc v1.6.4
#elseif !defined Missile_Version
	#error [ADM] Update you Missile.inc to v1.6.4
#elseif (Missile_Version < 10604)
	#error [ADM] Update you Missile.inc to v1.6.4
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v2.7.3
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v2.7.3
#elseif (Tryg3D_Version < 20703)
	#error [ADM] Update you 3DTryg.inc to v2.7.3
#endif

#if defined _veh_missile_launcher
	#endinput
#endif
#define _veh_missile_launcher

#define MAX_VEHICLE_MISSILE_TYPE				(5)
#define VEHICLE_MISSILE_TYPE_MINI				(0)
#define VEHICLE_MISSILE_TYPE_HEAVY				(1)
#define VEHICLE_MISSILE_TYPE_BOMBER				(2)
#define VEHICLE_MISSILE_TYPE_RHINO				(3)
#define VEHICLE_MISSILE_TYPE_MORTAR				(4)

#define VEHICLE_MISSILE_SPEED_MINI				(40.0)
#define VEHICLE_MISSILE_SPEED_HEAVY				(40.0)
#define VEHICLE_MISSILE_SPEED_BOMBER			(40.0)
#define VEHICLE_MISSILE_SPEED_MORTAR			(40.0)

#define VEHICLE_MISSILE_RELOAD_MINI				(500) //500 ms
#define VEHICLE_MISSILE_RELOAD_HEAVY			(3000)
#define VEHICLE_MISSILE_RELOAD_BOMBER			(1000)
#define VEHICLE_MISSILE_RELOAD_RHINO			(250)
#define VEHICLE_MISSILE_RELOAD_MORTAR			(500)

#define VEHICLE_MISSILE_DISTANCE_MINI			(1200.0)
#define VEHICLE_MISSILE_DISTANCE_HEAVY			(2000.0)
#define VEHICLE_MISSILE_DISTANCE_BOMBER			(1200.0)
#define VEHICLE_MISSILE_DISTANCE_RHINO			(12.0)
#define VEHICLE_MISSILE_DISTANCE_MORTAR			(250.0)

#define VEHICLE_MISSILE_KEY_MINI				(KEY_FIRE)
#define VEHICLE_MISSILE_KEY_HEAVY				(KEY_ACTION)
#define VEHICLE_MISSILE_KEY_BOMBER				(KEY_YES)
#define VEHICLE_MISSILE_KEY_RHINO				(KEY_FIRE)
#define VEHICLE_MISSILE_KEY_MORTAR				(KEY_YES)

#define VEHICLE_MISSILE_HEIGHT_MORTAR			(50.0)

//Get Compress Adress
#define GetVehicleConfigAddress(%0)				(floatround((%0)/32))
#define GetVehicleConfigBit(%0)					((%0) % 32)

//BitFunctions.inc
#define VM_GetValueBit(%0,%1)					((%0) >>> (%1) & 0x01)
#define VM_SetValueBit(%0,%1,%2)				((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

new VehicleConfigMiniMissile[64],
	VehicleConfigHeavyMissile[64],
	VehicleConfigRhinoMissile[64],
	VehicleConfigBomberMissile[64],
	VehicleConfigMortarMissile[64],
	VehicleWeaponTick[MAX_PLAYERS][MAX_VEHICLE_MISSILE_TYPE],
	VehicleWeaponReload[MAX_VEHICLES+1][MAX_VEHICLE_MISSILE_TYPE],
	VehicleWeaponKey[MAX_VEHICLES+1][MAX_VEHICLE_MISSILE_TYPE],
	Float:VehicleWeaponSpeed[MAX_VEHICLES+1][MAX_VEHICLE_MISSILE_TYPE],
	Float:VehicleWeaponDistance[MAX_VEHICLES+1][MAX_VEHICLE_MISSILE_TYPE],
	Float:VehicleMortarHeight[MAX_VEHICLES+1],
	Float:MissileStreamDistance = 200.0;

#define IsToggleVehicleMiniMissile(%0)			VM_GetValueBit(VehicleConfigMiniMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define IsToggleVehicleHeavyMissile(%0)			VM_GetValueBit(VehicleConfigHeavyMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define IsToggleVehicleRhinoMissile(%0)			VM_GetValueBit(VehicleConfigRhinoMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define IsToggleVehicleBomberMissile(%0)		VM_GetValueBit(VehicleConfigBomberMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define IsToggleVehicleMortarMissile(%0)		VM_GetValueBit(VehicleConfigMortarMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))

#define ToggleVehicleMiniMissile(%0,%1)			VM_SetValueBit(VehicleConfigMiniMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define ToggleVehicleHeavyMissile(%0,%1)		VM_SetValueBit(VehicleConfigHeavyMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define ToggleVehicleRhinoMissile(%0,%1)		VM_SetValueBit(VehicleConfigRhinoMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define ToggleVehicleBomberMissile(%0,%1)		VM_SetValueBit(VehicleConfigBomberMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define ToggleVehicleMortarMissile(%0,%1)		VM_SetValueBit(VehicleConfigMortarMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))

#define GetVehicleMiniMissileSpeed(%0)			VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define GetVehicleHeavyMissileSpeed(%0)			VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define GetVehicleBomberMissileSpeed(%0)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define GetVehicleMortarMissileSpeed(%0)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]

#define SetVehicleMiniMissileSpeed(%0,%1)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define SetVehicleHeavyMissileSpeed(%0,%1)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define SetVehicleBomberMissileSpeed(%0,%1)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define SetVehicleMortarMissileSpeed(%0,%1)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)

#define GetVehicleMiniMissileReload(%0)			VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define GetVehicleHeavyMissileReload(%0)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define GetVehicleBomberMissileReload(%0)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define GetVehicleRhinoMissileReload(%0)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define GetVehicleMortarMissileReload(%0)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]

#define SetVehicleMiniMissileReload(%0,%1)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define SetVehicleHeavyMissileReload(%0,%1)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define SetVehicleBomberMissileReload(%0,%1)	VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define SetVehicleRhinoMissileReload(%0,%1)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define SetVehicleMortarMissileReload(%0,%1)	VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)

#define GetVehicleMiniMissileDistance(%0)		VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define GetVehicleHeavyMissileDistance(%0)		VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define GetVehicleBomberMissileDistance(%0)		VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define GetVehicleRhinoMissileDistance(%0)		VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define GetVehicleMortarMissileDistance(%0)		VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]

#define SetVehicleMiniMissileDistance(%0,%1)	VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define SetVehicleHeavyMissileDistance(%0,%1)	VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define SetVehicleBomberMissileDistance(%0,%1)	VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define SetVehicleRhinoMissileDistance(%0,%1)	VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define SetVehicleMortarMissileDistance(%0,%1)	VehicleWeaponDistance[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)

#define GetVehicleMiniMissileKey(%0)			VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define GetVehicleHeavyMissileKey(%0)			VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define GetVehicleBomberMissileKey(%0)			VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define GetVehicleRhinoMissileKey(%0)			VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define GetVehicleMortarMissileKey(%0)			VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]

#define SetVehicleMiniMissileKey(%0,%1)			VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define SetVehicleHeavyMissileKey(%0,%1)		VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define SetVehicleBomberMissileKey(%0,%1)		VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define SetVehicleRhinoMissileKey(%0,%1)		VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define SetVehicleMortarMissileKey(%0,%1)		VehicleWeaponKey[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)

#define GetVehicleMortarMissileHeight(%0)		VehicleMortarHeight[(%0)]
#define SetVehicleMortarMissileHeight(%0,%1)	VehicleMortarHeight[(%0)] = (%1)

#define GetMissileStreamDistance()				MissileStreamDistance
#define SetMissileStreamDistance(%0)			MissileStreamDistance = (%0)

stock DisarmVehicleMissile(vehicleid){
	ToggleVehicleMiniMissile(vehicleid,0);
	ToggleVehicleHeavyMissile(vehicleid,0);
	ToggleVehicleRhinoMissile(vehicleid,0);
	ToggleVehicleBomberMissile(vehicleid,0);
	ToggleVehicleMortarMissile(vehicleid,0);
}

forward OnVehicleShot(playerid,type);
forward OnVehicleMissileInit();

public OnVehicleShot(playerid,type){
	new vid = GetPlayerVehicleID(playerid);

	switch(type){
		case VEHICLE_MISSILE_TYPE_MINI: {
			if(IsToggleVehicleMiniMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleMiniMissileReload(vid)) return 1;

				new F4[Float3D], F5[Float3D];
				GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rY]-180.0,F5[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleMiniMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleMiniMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rY],F5[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleMiniMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleMiniMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}

		case VEHICLE_MISSILE_TYPE_HEAVY: {
			if(IsToggleVehicleHeavyMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleHeavyMissileReload(vid)) return 1;

				new F4[Float3D], F5[Float3D];
				GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],CompRotationFloat(F5[T3D:rY]+15.0),F5[T3D:rZ]+90.0,6.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleHeavyMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],CompRotationFloat(F5[T3D:rY]+45.0),F5[T3D:rZ]+90.0,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleHeavyMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],CompRotationFloat(F5[T3D:rY]+75.0),F5[T3D:rZ]+90.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleHeavyMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],CompRotationFloat(F5[T3D:rY]+105.0),F5[T3D:rZ]+90.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleHeavyMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],CompRotationFloat(F5[T3D:rY]+135.0),F5[T3D:rZ]+90.0,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleHeavyMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],CompRotationFloat(F5[T3D:rY]+165.0),F5[T3D:rZ]+90.0,6.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleHeavyMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);
				
				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}

		case VEHICLE_MISSILE_TYPE_BOMBER: {
			if(IsToggleVehicleBomberMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleBomberMissileReload(vid)) return 1;

				new F4[Float3D], F5[Float3D];
				GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				CompRotationFloat(F5[T3D:rX]-45.0,F5[T3D:rX]);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleBomberMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]-90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleBomberMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]+45.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleBomberMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);

				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]-45.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],GetVehicleBomberMissileDistance(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);


				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}

		case VEHICLE_MISSILE_TYPE_RHINO: {
			if(IsToggleVehicleRhinoMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleRhinoMissileReload(vid)) return 1;

				new F5[Float3D];
				GetPointInFrontOfVehicle3DCol(vid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],GetVehicleRhinoMissileDistance(vid));

				CreateDynamicExplosion(F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],MISSILE_TYPE_EXPLODE_NORMAL,5.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance());
				
				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}
		
		case VEHICLE_MISSILE_TYPE_MORTAR: {
			if(IsToggleVehicleMortarMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleMortarMissileReload(vid)) return 1;
				
				new F4[Float3D], F5[Float3D];
				GetPlayerCameraZAngle(playerid,F4[T3D:rZ]);
				GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F4[T3D:rZ]-90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],GetVehicleMortarMissileDistance(vid),F4[T3D:tX],F4[T3D:tY]);
				Tryg3DMapAndreasFindZ(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleMortarMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,MAX_MISSILE_REMOTE_TARGET,GetVehicleMortarMissileHeight(vid));
	
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F4[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],GetVehicleMortarMissileDistance(vid),F4[T3D:tX],F4[T3D:tY]);
				Tryg3DMapAndreasFindZ(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleMortarMissileSpeed(vid),F4[T3D:X],F4[T3D:Y],F4[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,MAX_MISSILE_REMOTE_TARGET,GetVehicleMortarMissileHeight(vid));
	
				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}
	}

	return 1;
}

public OnVehicleMissileInit(){
	for(new i = 0; i <= MAX_VEHICLES; i++){
		SetVehicleMiniMissileSpeed(i,VEHICLE_MISSILE_SPEED_MINI);
		SetVehicleHeavyMissileSpeed(i,VEHICLE_MISSILE_SPEED_HEAVY);
		SetVehicleBomberMissileSpeed(i,VEHICLE_MISSILE_SPEED_BOMBER);
		SetVehicleMortarMissileSpeed(i,VEHICLE_MISSILE_SPEED_MORTAR);

		SetVehicleMiniMissileReload(i,VEHICLE_MISSILE_RELOAD_MINI);
		SetVehicleHeavyMissileReload(i,VEHICLE_MISSILE_RELOAD_HEAVY);
		SetVehicleBomberMissileReload(i,VEHICLE_MISSILE_RELOAD_BOMBER);
		SetVehicleRhinoMissileReload(i,VEHICLE_MISSILE_RELOAD_RHINO);
		SetVehicleMortarMissileReload(i,VEHICLE_MISSILE_RELOAD_MORTAR);
		
		SetVehicleMiniMissileDistance(i,VEHICLE_MISSILE_DISTANCE_MINI);
		SetVehicleHeavyMissileDistance(i,VEHICLE_MISSILE_DISTANCE_HEAVY);
		SetVehicleBomberMissileDistance(i,VEHICLE_MISSILE_DISTANCE_BOMBER);
		SetVehicleRhinoMissileDistance(i,VEHICLE_MISSILE_DISTANCE_RHINO);
		SetVehicleMortarMissileDistance(i,VEHICLE_MISSILE_DISTANCE_MORTAR);
		
		SetVehicleMiniMissileKey(i,VEHICLE_MISSILE_KEY_MINI);
		SetVehicleHeavyMissileKey(i,VEHICLE_MISSILE_KEY_HEAVY);
		SetVehicleBomberMissileKey(i,VEHICLE_MISSILE_KEY_BOMBER);
		SetVehicleRhinoMissileKey(i,VEHICLE_MISSILE_KEY_RHINO);
		SetVehicleMortarMissileKey(i,VEHICLE_MISSILE_KEY_MORTAR);
		
		SetVehicleMortarMissileHeight(i,VEHICLE_MISSILE_HEIGHT_MORTAR);
	}
	return 1;
}

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0){
		new vid = GetPlayerVehicleID(playerid);
		if(Tryg3DKeyPressed(GetVehicleMiniMissileKey(vid))){
			if(IsToggleVehicleMiniMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_MINI);
			}
		}
		if(Tryg3DKeyPressed(GetVehicleHeavyMissileKey(vid))){
			if(IsToggleVehicleHeavyMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_HEAVY);
			}
		}
		if(Tryg3DKeyPressed(GetVehicleBomberMissileKey(vid))){
			if(IsToggleVehicleBomberMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_BOMBER);
			}
		}
		if(Tryg3DKeyPressed(GetVehicleRhinoMissileKey(vid))){
			if(IsToggleVehicleRhinoMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_RHINO);
			}
		}
		if(Tryg3DKeyPressed(GetVehicleMortarMissileKey(vid))){
			if(IsToggleVehicleMortarMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_MORTAR);
			}
		}
	}
	#if defined VM_OnPlayerKeyStateChange
		VM_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange VM_OnPlayerKeyStateChange
#if defined VM_OnPlayerKeyStateChange
	forward VM_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

new bool:CRC_VehicleMissileCol = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_VehicleMissileCol){ CRC_VehicleMissileCol = false; } else return 1; //Init Engine
	OnVehicleMissileInit();
	#if defined VM_OnFilterScriptInit
		VM_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit VM_OnFilterScriptInit
#if defined VM_OnFilterScriptInit
	forward VM_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_VehicleMissileCol){ CRC_VehicleMissileCol = false; } else return 1; //Init Engine
	OnVehicleMissileInit();
	#if defined VM_OnGameModeInit
		VM_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit VM_OnGameModeInit
#if defined VM_OnGameModeInit
	forward VM_OnGameModeInit();
#endif

//EOF
/****************************************************************************************************
 *                                                                                                  *
 * Vehicle Missile Launcher v1.0 made by Abyss Morgan                                               *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts                         *
 *                                                                                                  *
 * Functions:                                                                                       *
 * ToggleVehicleMiniMissile(vehicleid,toggle);                                                      *
 * ToggleVehicleHeavyMissile(vehicleid,toggle);                                                     *
 * ToggleVehicleRhinoMissile(vehicleid,toggle);                                                     *
 * ToggleVehicleBomberMissile(vehicleid,toggle);                                                    *
 * IsToggleVehicleMiniMissile(vehicleid);                                                           *
 * IsToggleVehicleHeavyMissile(vehicleid);                                                          *
 * IsToggleVehicleRhinoMissile(vehicleid);                                                          *
 * IsToggleVehicleBomberMissile(vehicleid);                                                         *
 *                                                                                                  *
 * SetVehicleMiniMissileSpeed(vehicleid,Float:speed);                                               *
 * SetVehicleHeavyMissileSpeed(vehicleid,Float:speed);                                              *
 * SetVehicleBomberMissileSpeed(vehicleid,Float:speed);                                             *
 * GetVehicleMiniMissileSpeed(vehicleid);                                                           *
 * GetVehicleHeavyMissileSpeed(vehicleid);                                                          *
 * GetVehicleBomberMissileSpeed(vehicleid);                                                         *
 *                                                                                                  *
 * GetVehicleMiniMissileReload(vehicleid);                                                          *
 * GetVehicleHeavyMissileReload(vehicleid);                                                         *
 * GetVehicleBomberMissileReload(vehicleid);                                                        *
 * GetVehicleRhinoMissileReload(vehicleid);                                                         *
 * SetVehicleMiniMissileReload(vehicleid,time);                                                     *
 * SetVehicleHeavyMissileReload(vehicleid,time);                                                    *
 * SetVehicleBomberMissileReload(vehicleid,time);                                                   *
 * SetVehicleRhinoMissileReload(vehicleid,time);                                                    *
 *                                                                                                  *
 * OnVehicleShot(playerid,type);                                                                    *
 *                                                                                                  *
 ****************************************************************************************************/

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

#if !defined MapAndreas_FindZ_For2DCoord
	#error Unknown MapAndreas Version
#endif

#if !defined _ATM_Core
	#error You need ATM.inc
#endif

#if !defined _missile_launcher
	#error You need Missile.inc
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.5C
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.5C
#elseif (Tryg3D_Version < 20503)
	#error Update you 3DTryg.inc to v2.5C
#endif

#if defined _veh_missile_launcher
	#endinput
#endif
#define _veh_missile_launcher

#define MAX_VEHICLE_MISSILE_TYPE			(4)
#define VEHICLE_MISSILE_TYPE_MINI			(0)
#define VEHICLE_MISSILE_TYPE_HEAVY			(1)
#define VEHICLE_MISSILE_TYPE_BOMBER			(2)
#define VEHICLE_MISSILE_TYPE_RHINO			(3)

#define VEHICLE_MISSILE_SPEED_MINI			(40.0)
#define VEHICLE_MISSILE_SPEED_HEAVY			(40.0)
#define VEHICLE_MISSILE_SPEED_BOMBER		(40.0)

#define VEHICLE_MISSILE_RELOAD_MINI			(500) //500 ms
#define VEHICLE_MISSILE_RELOAD_HEAVY		(3000)
#define VEHICLE_MISSILE_RELOAD_BOMBER		(1000)
#define VEHICLE_MISSILE_RELOAD_RHINO		(250)

//Get Compress Adress
#define GetVehicleConfigAddress(%0)			(floatround((%0)/32))
#define GetVehicleConfigBit(%0)				((%0) % 32)

//BitFunctions.inc
#define VM_GetValueBit(%0,%1)				((%0) >>> (%1) & 0x01)
#define VM_SetValueBit(%0,%1,%2)			((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

new VehicleConfigMiniMissile[64],
	VehicleConfigHeavyMissile[64],
	VehicleConfigRhinoMissile[64],
	VehicleConfigBomberMissile[64],
	VehicleWeaponTick[MAX_PLAYERS][MAX_VEHICLE_MISSILE_TYPE],
	Float:VehicleWeaponSpeed[MAX_VEHICLES+1][MAX_VEHICLE_MISSILE_TYPE-1],
	VehicleWeaponReload[MAX_VEHICLES+1][MAX_VEHICLE_MISSILE_TYPE];

#define IsToggleVehicleMiniMissile(%0)			VM_GetValueBit(VehicleConfigMiniMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define IsToggleVehicleHeavyMissile(%0)			VM_GetValueBit(VehicleConfigHeavyMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define IsToggleVehicleRhinoMissile(%0)			VM_GetValueBit(VehicleConfigRhinoMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define IsToggleVehicleBomberMissile(%0)		VM_GetValueBit(VehicleConfigBomberMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))

#define ToggleVehicleMiniMissile(%0,%1)			VM_SetValueBit(VehicleConfigMiniMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define ToggleVehicleHeavyMissile(%0,%1)		VM_SetValueBit(VehicleConfigHeavyMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define ToggleVehicleRhinoMissile(%0,%1)		VM_SetValueBit(VehicleConfigRhinoMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define ToggleVehicleBomberMissile(%0,%1)		VM_SetValueBit(VehicleConfigBomberMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))

#define GetVehicleMiniMissileSpeed(%0)			VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define GetVehicleHeavyMissileSpeed(%0)			VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define GetVehicleBomberMissileSpeed(%0)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]

#define SetVehicleMiniMissileSpeed(%0,%1)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define SetVehicleHeavyMissileSpeed(%0,%1)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define SetVehicleBomberMissileSpeed(%0,%1)		VehicleWeaponSpeed[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)

#define GetVehicleMiniMissileReload(%0)			VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define GetVehicleHeavyMissileReload(%0)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define GetVehicleBomberMissileReload(%0)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define GetVehicleRhinoMissileReload(%0)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_RHINO]

#define SetVehicleMiniMissileReload(%0,%1)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define SetVehicleHeavyMissileReload(%0,%1)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define SetVehicleBomberMissileReload(%0,%1)	VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define SetVehicleRhinoMissileReload(%0,%1)		VehicleWeaponReload[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)

forward OnVehicleShot(playerid,type);
forward OnVehicleMissileInit();

public OnVehicleShot(playerid,type){
	new vid = GetPlayerVehicleID(playerid);

	switch(type){
		case VEHICLE_MISSILE_TYPE_MINI: {
			if(IsToggleVehicleMiniMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleMiniMissileReload(vid)) return 1;

				new F4[e_float], F5[e_float];
				GetVehiclePos(vid,F5[X],F5[Y],F5[Z]);
				GetVehicleRotation(vid,F5[rX],F5[rY],F5[rZ]);

				GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ]+90.0,3.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],1200.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleMiniMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_HYDRA,F4[tX],F4[tY],F4[tZ],playerid);

				GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ]-90.0,3.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],1200.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleMiniMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_HYDRA,F4[tX],F4[tY],F4[tZ],playerid);

				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}

		case VEHICLE_MISSILE_TYPE_HEAVY: {
			if(IsToggleVehicleHeavyMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleHeavyMissileReload(vid)) return 1;

				new F4[e_float], F5[e_float];
				GetVehiclePos(vid,F5[X],F5[Y],F5[Z]);
				GetVehicleRotation(vid,F5[rX],F5[rY],F5[rZ]);

				GetPointInFront3D(F5[X],F5[Y],F5[Z]-2.0,F5[rX],F5[rZ]+90.0,6.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],2000.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_BIG,F4[tX],F4[tY],F4[tZ],playerid);

				GetPointInFront3D(F5[X],F5[Y],F5[Z]-2.0,F5[rX],F5[rZ]-90.0,6.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],2000.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_BIG,F4[tX],F4[tY],F4[tZ],playerid);


				GetPointInFront3D(F5[X],F5[Y],F5[Z]+0.0,F5[rX],F5[rZ]+90.0,5.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],2000.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_BIG,F4[tX],F4[tY],F4[tZ],playerid);

				GetPointInFront3D(F5[X],F5[Y],F5[Z]+0.0,F5[rX],F5[rZ]-90.0,5.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],2000.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_BIG,F4[tX],F4[tY],F4[tZ],playerid);


				GetPointInFront3D(F5[X],F5[Y],F5[Z]-4.0,F5[rX],F5[rZ]+90.0,5.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],2000.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_BIG,F4[tX],F4[tY],F4[tZ],playerid);

				GetPointInFront3D(F5[X],F5[Y],F5[Z]-4.0,F5[rX],F5[rZ]-90.0,5.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],2000.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,8.0,25.0,GetVehicleHeavyMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_BIG,F4[tX],F4[tY],F4[tZ],playerid);

				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}

		case VEHICLE_MISSILE_TYPE_BOMBER: {
			if(IsToggleVehicleBomberMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleBomberMissileReload(vid)) return 1;

				new F4[e_float], F5[e_float];
				GetVehiclePos(vid,F5[X],F5[Y],F5[Z]);
				GetVehicleRotation(vid,F5[rX],F5[rY],F5[rZ]);
				CompRotationFloat(F5[rX]-45.0,F5[rX]);

				GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ]+90.0,3.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],1200.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_NORMAL,F4[tX],F4[tY],F4[tZ],playerid);

				GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ]-90.0,3.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],1200.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_NORMAL,F4[tX],F4[tY],F4[tZ],playerid);

				GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ]+45.0,4.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],1200.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_NORMAL,F4[tX],F4[tY],F4[tZ],playerid);

				GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ]-45.0,4.0,F4[X],F4[Y],F4[Z]);
				GetPointInFrontOnGround(F4[X],F4[Y],F4[Z],F5[rX],F5[rZ],F4[tX],F4[tY],F4[tZ],1200.0);
				MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,25.0,GetVehicleBomberMissileSpeed(vid),F4[X],F4[Y],F4[Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0,MISSILE_OBJECT_NORMAL,F4[tX],F4[tY],F4[tZ],playerid);


				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}

		case VEHICLE_MISSILE_TYPE_RHINO: {
			if(IsToggleVehicleRhinoMissile(vid)){
				if(GetTickCount()-VehicleWeaponTick[playerid][type] < GetVehicleRhinoMissileReload(vid)) return 1;

				new F5[e_float];
				GetPointInFrontOfVehicle3D(vid,F5[tX],F5[tY],F5[tZ],12.0);

				CreateExplosionForRangePoint(F5[tX],F5[tY],F5[tZ],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),MISSILE_TYPE_EXPLODE_NORMAL,200.0,5.0);

				VehicleWeaponTick[playerid][type] = GetTickCount();
			}
		}
	}

	return 1;
}

public OnVehicleMissileInit(){
	for(new i = 0; i < MAX_VEHICLES+1; i++){
		SetVehicleMiniMissileSpeed(i,VEHICLE_MISSILE_SPEED_MINI);
		SetVehicleHeavyMissileSpeed(i,VEHICLE_MISSILE_SPEED_HEAVY);
		SetVehicleBomberMissileSpeed(i,VEHICLE_MISSILE_SPEED_BOMBER);

		SetVehicleMiniMissileReload(i,VEHICLE_MISSILE_RELOAD_MINI);
		SetVehicleHeavyMissileReload(i,VEHICLE_MISSILE_RELOAD_HEAVY);
		SetVehicleBomberMissileReload(i,VEHICLE_MISSILE_RELOAD_BOMBER);
		SetVehicleRhinoMissileReload(i,VEHICLE_MISSILE_RELOAD_RHINO);
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
	if(IsPlayerInAnyVehicle(playerid)){
		new vid = GetPlayerVehicleID(playerid);
		if(KEY_PRESSED(KEY_FIRE)){
			if(IsToggleVehicleMiniMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_MINI);
			}
			if(IsToggleVehicleRhinoMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_RHINO);
			}
		}
		if(KEY_PRESSED(KEY_ACTION)){
			if(IsToggleVehicleHeavyMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_HEAVY);
			}
		}
		if(KEY_PRESSED(KEY_YES)){
			if(IsToggleVehicleBomberMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_BOMBER);
			}
		}
	}
	#if defined VM_OnPlayerKeyStateChange
		VM_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
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
	forward VM_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnFilterScriptInit(){
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

public OnGameModeInit(){
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
/****************************************************************************************************
 *                                                                                                  *
 *                                   GangZone Extended Functions                                    *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * Plugins: Streamer                                                                                *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.2.1                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 * Streamer Version: 2.8.2                                                                          *
 *                                                                                                  *
 * Notice:                                                                                          *
 * - Fit with YSF.inc when it is before GangZoneEx.inc                                              *
 *                                                                                                  *
 * Functions:                                                                                       *
 * IsValidGangZone(zoneid);                                                                         *
 * IsPlayerInGangZone(playerid,zoneid);                                                             *
 * IsPlayerInAnyGangZone(playerid);                                                                 *
 * GangZoneCreateEx(Float:minx,Float:miny,Float:maxx,Float:maxy,worldid = -1,interiorid = -1);      *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _Gang_Zone_Ex
	#endinput
#endif
#define _Gang_Zone_Ex

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

new GangZoneArea[MAX_GANG_ZONES];

stock GangZoneCreateEx(Float:minx,Float:miny,Float:maxx,Float:maxy,worldid = -1,interiorid = -1){
	new tid = GangZoneCreate(minx,miny,maxx,maxy);
	if(tid == INVALID_GANG_ZONE){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: GangZoneCreate returned INVALID_GANG_ZONE");
		}
		return INVALID_GANG_ZONE;
	}
	GangZoneArea[tid] = CreateDynamicRectangle(minx,miny,maxx,maxy,worldid,interiorid,-1);
	return tid;
}

//Hook: GangZoneCreate
stock GZ_GangZoneCreate(Float:minx,Float:miny,Float:maxx,Float:maxy){
	new tid;
	if((tid = GangZoneCreate(minx,miny,maxx,maxy)) == INVALID_GANG_ZONE) return INVALID_GANG_ZONE;
	GangZoneArea[tid] = CreateDynamicRectangle(minx,miny,maxx,maxy,-1,-1,-1);
	return tid;
}

#if defined _ALS_GangZoneCreate
	#undef GangZoneCreate
#else
	#define _ALS_GangZoneCreate
#endif
#define GangZoneCreate GZ_GangZoneCreate

//Hook: GangZoneDestroy
stock GZ_GangZoneDestroy(zoneid){
	if(zoneid < 0 || zoneid > MAX_GANG_ZONES) return 0;
	if(IsValidDynamicArea(GangZoneArea[zoneid])) DestroyDynamicArea(GangZoneArea[zoneid]);
	return GangZoneDestroy(zoneid);
}

#if defined _ALS_GangZoneDestroy
	#undef GangZoneDestroy
#else
	#define _ALS_GangZoneDestroy
#endif
#define GangZoneDestroy GZ_GangZoneDestroy

//fix colision YSF.inc
#if !defined _YSF_included
	stock bool:IsPlayerInGangZone(playerid,zoneid){
		if(zoneid < 0 || zoneid > MAX_GANG_ZONES){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				printf("[ADM] Warring: Invalid zoneid, range 0 - %d",MAX_GANG_ZONES-1);
			}
			return false;
		}
		if(IsPlayerInDynamicArea(playerid,GangZoneArea[zoneid])) return true;
		return false;
	}
	
	stock bool:IsValidGangZone(zoneid){
		if(zoneid < 0 || zoneid > MAX_GANG_ZONES){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				printf("[ADM] Warring: Invalid zoneid, range 0 - %d",MAX_GANG_ZONES-1);
				return false;
			}
		}
		if(IsValidDynamicArea(GangZoneArea[zoneid]) && GangZoneArea[zoneid] != 0) return true
		return false;
	}
#endif

stock bool:IsPlayerInAnyGangZone(playerid){
	for(new i = 0; i < MAX_GANG_ZONES; i++){
		if(IsPlayerInGangZone(playerid,i)) return true;
	}
	return false;
}

//EOF
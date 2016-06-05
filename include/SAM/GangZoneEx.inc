/****************************************************************************************************
 *                                                                                                  *
 * GangZone Update v1.2 made by Abyss Morgan                                                        *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * Notice:                                                                                          *
 * Fit with YSF.inc when it is before GangZoneEx.inc                                                *
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

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

new GangZoneArea[MAX_GANG_ZONES];

stock GangZoneCreateEx(Float:minx,Float:miny,Float:maxx,Float:maxy,worldid = -1,interiorid = -1){
	new tid = GangZoneCreate(minx,miny,maxx,maxy);
	if(tid == INVALID_GANG_ZONE) return print("[ADM] Warring: GangZoneCreate returned INVALID_GANG_ZONE");
	GangZoneArea[tid] = CreateDynamicRectangle(minx,miny,maxx,maxy,worldid,interiorid,-1);
	return tid;
}

stock AC_GangZoneCreate(Float:minx,Float:miny,Float:maxx,Float:maxy){
	new tid = GangZoneCreate(minx,miny,maxx,maxy);
	if(tid == INVALID_GANG_ZONE) return print("[ADM] Warring: GangZoneCreate returned INVALID_GANG_ZONE");
	GangZoneArea[tid] = CreateDynamicRectangle(minx,miny,maxx,maxy,-1,-1,-1);
	return tid;
}

#if defined _ALS_GangZoneCreate
	#undef GangZoneCreate
#else
	#define _ALS_GangZoneCreate
#endif
#define GangZoneCreate AC_GangZoneCreate

stock AC_GangZoneDestroy(zoneid){
	if(zoneid < 0 || zoneid > MAX_GANG_ZONES) return printf("[ADM] Warring: Invalid zoneid, range 0 - %d",MAX_GANG_ZONES);
	if(IsValidDynamicArea(GangZoneArea[zoneid])) DestroyDynamicArea(GangZoneArea[zoneid]);
	return GangZoneDestroy(zoneid);
}

#if defined _ALS_GangZoneDestroy
	#undef GangZoneDestroy
#else
	#define _ALS_GangZoneDestroy
#endif
#define GangZoneDestroy AC_GangZoneDestroy

//fix colision YSF.inc
#if !defined _YSF_included
	stock bool:IsPlayerInGangZone(playerid,zoneid){
		if(zoneid < 0 || zoneid > MAX_GANG_ZONES) return printf("[ADM] Warring: Invalid zoneid, range 0 - %d",MAX_GANG_ZONES);
		if(IsPlayerInDynamicArea(playerid,GangZoneArea[zoneid])) return true;
		return false;
	}
	
	stock bool:IsValidGangZone(zoneid){
		if(zoneid < 0 || zoneid > MAX_GANG_ZONES) return printf("[ADM] Warring: Invalid zoneid, range 0 - %d",MAX_GANG_ZONES);
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
/****************************************************************************************************
 *                                                                                                  *
 * GangZone Update v1.1 by Abyss Morgan                                                             *
 *                                                                                                  *
 * IsPlayerInGangZone(playerid,zone);                                                               *
 * IsPlayerInAnyGangZone(playerid);                                                                 *
 * GangZoneCreateEx(Float:minx,Float:miny,Float:maxx,Float:maxy,worldid = -1,interiorid = -1);      *
 *                                                                                                  *
 ****************************************************************************************************/

new GangZoneArea[MAX_GANG_ZONES];

stock GangZoneCreateEx(Float:minx,Float:miny,Float:maxx,Float:maxy,worldid = -1,interiorid = -1){
	new tid = GangZoneCreate(minx,miny,maxx,maxy);
	GangZoneArea[tid] = CreateDynamicRectangle(minx,miny,maxx,maxy,worldid,interiorid,-1);
	return tid;
}

stock AC_GangZoneCreate(Float:minx,Float:miny,Float:maxx,Float:maxy){
	new tid = GangZoneCreate(minx,miny,maxx,maxy);
	GangZoneArea[tid] = CreateDynamicRectangle(minx,miny,maxx,maxy,-1,-1,-1);
	return tid;
}

#if defined _ALS_GangZoneCreate
	#undef GangZoneCreate
#else
	#define _ALS_GangZoneCreate
#endif
#define GangZoneCreate AC_GangZoneCreate

stock AC_GangZoneDestroy(zone){
	if(IsValidDynamicArea(GangZoneArea[zone])) DestroyDynamicArea(GangZoneArea[zone]);
	GangZoneDestroy(zone);
}

#if defined _ALS_GangZoneDestroy
	#undef GangZoneDestroy
#else
	#define _ALS_GangZoneDestroy
#endif
#define GangZoneDestroy AC_GangZoneDestroy

stock bool:IsPlayerInGangZone(playerid,zone){
	if(IsPlayerInDynamicArea(playerid,GangZoneArea[zone])) return true;
	return false;
}

stock bool:IsPlayerInAnyGangZone(playerid){
	for(new i = 0; i < MAX_GANG_ZONES; i++){
		if(IsPlayerInGangZone(playerid,i)) return true;
	}
	return false;
}
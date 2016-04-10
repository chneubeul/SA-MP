/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                            ATM Core                                                            *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                         *
 *                                                                                                                                *
 * File Version: 1.0B                                                                                                             *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * SecToTimeDay(second);      //Use: %d:%02d:%02d:%02d                                                                            *
 * MSToTimeDay(millisecond);  //Use: %d:%02d:%02d:%02d                                                                            *
 * SecToTime(second);         //Use: %02d:%02d:%02d                                                                               *
 * MSToTime(millisecond);     //Use: %02d:%02d:%02d                                                                               *
 * SecToTimeMini(second);     //Use: %02d:%02d                                                                                    *
 * MSToTimeMini(millisecond); //Use: %02d:%02d                                                                                    *
 * foX(variable,beginning,end);                                                                                                   *
 * foreach(variable);                                                                                                             *
 * KEY_PRESSED(key);                                                                                                              *
 * KEY_RELEASED(key);                                                                                                             *
 * KEY_HOLDING(key);                                                                                                              *
 * CreateExplosionForRangePoint(Float:x,Float:y,Float:z,worldid,interiorid,type,Float:radius,Float:expradius);                    *
 * Float:CalculatePercent(Float:value,Float:maxvalue);                                                                            *
 * GetSAMIncludeVersion(value,name[],maxdest = sizeof(name));                                                                     *
 * SetPlayerWorldBoundsEx(playerid,Float:minx,Float:miny,Float:maxx,Float:maxy);                                                  *
 * GetPlayerNick(playerid);                                                                                                       *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if defined _ATM_Core
	#endinput
#endif
#define _ATM_Core

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if !defined SecToTimeDay
	//%d:%02d:%02d:%02d
	#define SecToTimeDay(%0)			((%0) / 86400),(((%0) % 86400) / 3600),((((%0) % 86400) % 3600) / 60),((((%0) % 86400) % 3600) % 60)
	#define MSToTimeDay(%0)				SecToTimeDay((%0)/1000)
	//%02d:%02d:%02d
	#define SecToTime(%0)				((%0) / 3600),(((%0) % 3600) / 60),(((%0) % 3600) % 60)
	#define MSToTime(%0)				SecToTime((%0)/1000)
	//%02d:%02d
	#define SecToTimeMini(%0)			((%0) / 60),((%0) % 60)
	#define MSToTimeMini(%0)			SecToTimeMini((%0)/1000)
#endif

//value bigger than possible
#if !defined VBTP
	#define VBTP 						(0x7FFFFFFF)
#endif

#if !defined FLOAT_NAN
	#define FLOAT_NAN 					(Float:0xFFFFFFFF)
#endif

#define SD_TINY						(5.0)
#define SD_VERYLOW					(20.0)
#define SD_LOW						(200.0)
#define SD_MEDIUM					(500.0)
#define SD_HIGH						(800.0)
#define SD_VERYHIGH					(999.0)

#define ALL_PLAYERS					(-1)
#define ALL_VW						(-1)
#define ALL_INT						(-1)
#define ATM_INT						(1)
#define ATM_VW						(1)
#define REAL_INT					(0)
#define REAL_VW						(0)

#define foX(%1,%2,%3)				for(new %1 = %2; %1 <= %3; %1++)
#define foreach(%1)					for(new %1 = 0, p_%1 = GetPlayerPoolSize(); %1 <= p_%1; %1++)

#define KEY_PRESSED(%0) 			(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define KEY_RELEASED(%0)			(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define KEY_HOLDING(%0) 			((newkeys & (%0)) == (%0))

enum e_float {
	Float:X, Float:Y, Float:Z,
	Float:rX, Float:rY, Float:rZ,
	Float:tX, Float:tY, Float:tZ,
	VW, INT, Float:SPEED
}

stock CreateExplosionForRangePoint(Float:x,Float:y,Float:z,worldid,interiorid,type,Float:radius,Float:expradius){
	foreach(i){
		if(IsPlayerConnected(i)){
			new F4[e_float];
			if(IsPlayerInAnyVehicle(i)){
				GetVehiclePos(GetPlayerVehicleID(i),F4[X],F4[Y],F4[Z]);
			} else {
				GetPlayerPos(i,F4[X],F4[Y],F4[Z]);
			}
			new Float:distance = GetDistanceBetweenPoints3D(F4[X],F4[Y],F4[Z],x,y,z);
			if((GetPlayerInterior(i) == interiorid) && (GetPlayerVirtualWorld(i) == worldid) && (distance <= radius)){
				CreateExplosionForPlayer(i,x,y,z,type,expradius);
			}
		}
	}
	return 1;
}

stock Float:CalculatePercent(Float:value,Float:maxvalue){ 
    return ((value/maxvalue)*100.0); 
}

stock GetSAMIncludeVersion(value,name[],maxdest = sizeof(name)){
	format(name,maxdest,"%d.%d%c",(value / 10000),((value % 10000) / 100),(((value % 10000) % 100) + 0x40));
}

stock SetPlayerWorldBoundsEx(playerid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	new Float:Tminx,Float:Tminy,Float:Tmaxx,Float:Tmaxy;
	if(minx < maxx){
		Tminx = minx, Tmaxx = maxx;
	} else {
		Tminx = maxx, Tmaxx = minx;
	}
	if(miny < maxy){
		Tminy = miny, Tmaxy = maxy;
	} else {
		Tminy = maxy, Tmaxy = miny;
	}
	SetPlayerWorldBounds(playerid,Tminx,Tminy,Tmaxx,Tmaxy);
}

stock GetPlayerNick(playerid){
	new pnick[24];
	GetPlayerName(playerid,pnick,sizeof (pnick));
	return pnick;
}

//EOF
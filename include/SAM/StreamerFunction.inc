/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                  Streamer Special Functions                                                    *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * File Version: 1.6                                                                                                              *
 *                                                                                                                                *
 * Objects Functions:                                                                                                             *
 * GetDynamicObjectModel(objectid);                                                                                               *
 * SetDynamicObjectModel(objectid,modelid);                                                                                       *
 * SetDynamicObjectVW(objectid,worldid);                                                                                          *
 * SetDynamicObjectINT(objectid,interiorid);                                                                                      *
 * SetDynamicObjectSD(objectid,Float:streamdistance);                                                                             *
 * SetDynamicObjectDD(objectid,Float:drawdistance);                                                                               *
 * GetDynamicObjectVW(objectid);                                                                                                  *
 * GetDynamicObjectINT(objectid);                                                                                                 *
 * GetDynamicObjectSD(objectid,&Float:streamdistance);                                                                            *
 * GetDynamicObjectDD(objectid,&Float:drawdistance);                                                                              *
 * SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);                                        *
 * GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);                                  *
 * RebuildDynamicObject(objectid,...);                                                                                            *
 * SetDynamicObjectMoveSpeed(objectid,Float:speed);                                                                               *
 *                                                                                                                                *
 * SAMP Object Functions:                                                                                                         * 
 * SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);                                               *
 * GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);                                         *
 * DestroyObjects();                                                                                                              *
 * CountObjects();                                                                                                                *
 *                                                                                                                                *
 * Cube Functions:                                                                                                                *
 * DestroyDynamicObjectsInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1);   *
 * DestroyDynamicObjectsInCubeFM(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1); *
 * IsPointInArea(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                      *
 * IsPointInAreaEx(...,pointworldid,pointinteriorid,areaworldid,areainteriorid);                                                  *
 *                                                                                                                                *
 * Vehicle Functions:                                                                                                             *
 * DestroyVehicleDynamicObject(vehicleid);                                                                                        *
 * DeattachVehicleDynamicObject(vehicleid);                                                                                       *
 *                                                                                                                                *
 * Pickup Functions:                                                                                                              *
 * SetDynamicCPSize(checkpointid,Float:size);                                                                                     *
 * SetDynamicRaceCPSize(checkpointid,Float:size);                                                                                 *
 *                                                                                                                                *
 * Player Functions:                                                                                                              *
 * DestroyPlayerDynamicObject(playerid);                                                                                          *
 * DeattachPlayerDynamicObject(playerid);                                                                                         *
 *                                                                                                                                *
 * MapIcon Functions:                                                                                                             *
 * SetDynamicMapIconColor(iconid,color);                                                                                          *
 *                                                                                                                                *
 **********************************************************************************************************************************/
 
#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

#if defined _streamer_spec
	#endinput
#endif
#define _streamer_spec

#define GetDynamicObjectModel(%1)			Streamer_GetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_MODEL_ID)
#define SetDynamicObjectModel(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_MODEL_ID,%2)
#define SetDynamicObjectVW(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_WORLD_ID,%2)
#define SetDynamicObjectINT(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_INTERIOR_ID,%2)
#define GetDynamicObjectVW(%1)				Streamer_GetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_WORLD_ID)
#define GetDynamicObjectINT(%1)				Streamer_GetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_INTERIOR_ID)
#define SetDynamicObjectSD(%1,%2)			Streamer_SetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_STREAM_DISTANCE,%2)
#define SetDynamicObjectDD(%1,%2)			Streamer_SetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_DRAW_DISTANCE,%2)
#define SetDynamicObjectMoveSpeed(%1,%2)	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_MOVE_SPEED,%2)
#define SetDynamicCPSize(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_CP,%1,E_STREAMER_SIZE,%2)
#define SetDynamicRaceCPSize(%1,%2)			Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,%1,E_STREAMER_SIZE,%2)
#define SetDynamicMapIconColor(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,%1,E_STREAMER_COLOR,%2)
 
stock GetDynamicObjectSD(objectid,&Float:streamdistance){
	return Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_STREAM_DISTANCE,streamdistance);
}

stock GetDynamicObjectDD(objectid,&Float:drawdistance){
	return Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_DRAW_DISTANCE,drawdistance);
}

stock SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	if(IsValidDynamicObject(objectid)) SetDynamicObjectPos(objectid,x,y,z);
	if(IsValidDynamicObject(objectid)) SetDynamicObjectRot(objectid,rx,ry,rz);
}

stock GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	if(IsValidDynamicObject(objectid)) GetDynamicObjectPos(objectid,x,y,z);
	if(IsValidDynamicObject(objectid)) GetDynamicObjectRot(objectid,rx,ry,rz);
}

stock SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	if(IsValidObject(objectid)) SetObjectPos(objectid,x,y,z);
	if(IsValidObject(objectid)) SetObjectRot(objectid,rx,ry,rz);
}

stock GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	if(IsValidObject(objectid)) GetObjectPos(objectid,x,y,z);
	if(IsValidObject(objectid)) GetObjectRot(objectid,rx,ry,rz);
}

stock CountObjects(){
	new count = 0;
	for(new i=0; i <= MAX_OBJECTS; i++){
		if(IsValidObject(i)) count += 1;
	}
	return count;
}

stock DestroyObjects(){
	for(new i=0; i <= MAX_OBJECTS; i++){
		if(IsValidObject(i)) DestroyObject(i);
	}
}

stock RebuildDynamicObject(objectid,modelid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,worldid,interiorid,playerid,Float:streamdistance,Float:drawdistance){
	if(!IsValidDynamicObject(objectid)) return 0;
	if(IsDynamicObjectMoving(objectid)) StopDynamicObject(objectid);
	SetDynamicObjectPosAndRot(objectid,x,y,z,rx,ry,rz); 
	SetDynamicObjectModel(objectid,modelid);
	SetDynamicObjectVW(objectid,worldid);
	SetDynamicObjectINT(objectid,interiorid);
	SetDynamicObjectSD(objectid,streamdistance);
	SetDynamicObjectDD(objectid,drawdistance);
	return 1;
}

stock IsPointInArea(Float:x, Float:y, Float:z, Float:minx = -FLOAT_INFINITY, Float:miny = -FLOAT_INFINITY, Float:minz = -FLOAT_INFINITY, Float:maxx = FLOAT_INFINITY, Float:maxy = FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy) && (z >= minz && z <= maxz)) return true;
	return false;
}

stock IsPointInAreaEx(Float:x, Float:y, Float:z, Float:minx = -FLOAT_INFINITY, Float:miny = -FLOAT_INFINITY, Float:minz = -FLOAT_INFINITY, Float:maxx = FLOAT_INFINITY, Float:maxy = FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, pointworldid = -1, pointinteriorid = -1, areaworldid = -1, areainteriorid = -1){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy) && (z >= minz && z <= maxz) && (pointworldid == areaworldid) && (pointinteriorid == areainteriorid)) return true;
	return false;
}

stock DestroyDynamicObjectsInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1){
	new Float:piox, Float:pioy, Float:pioz, pioVW, pioINT, max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
	for(new i = 0; i < max_dobj; i++){
		if(IsValidDynamicObject(i)){
			GetDynamicObjectPos(i,piox,pioy,pioz);
			pioVW = GetDynamicObjectVW(i);
			pioINT = GetDynamicObjectINT(i);
			if(IsPointInArea(piox,pioy,pioz,minx,miny,minz,maxx,maxy,maxz)){
				if(((worldid == pioVW) || (worldid == -1)) && (interiorid == pioINT) || (interiorid == -1)){
					if(IsDynamicObjectMoving(i)) StopDynamicObject(i);
					DestroyDynamicObject(i);
				}
			}
		}
	}
}

stock DestroyDynamicObjectsInCubeFM(modelid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1){
	new Float:piox, Float:pioy, Float:pioz, pioVW, pioINT, max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
	for(new i = 0; i < max_dobj; i++){
		if(IsValidDynamicObject(i)){
			GetDynamicObjectPos(i,piox,pioy,pioz);
			pioVW = GetDynamicObjectVW(i);
			pioINT = GetDynamicObjectINT(i);
			if(IsPointInArea(piox,pioy,pioz,minx,miny,minz,maxx,maxy,maxz)){
				if(((worldid == pioVW) || (worldid == -1)) && ((interiorid == pioINT) || (interiorid == -1)) && (modelid == GetDynamicObjectModel(i))){
					if(IsDynamicObjectMoving(i)) StopDynamicObject(i);
					DestroyDynamicObject(i);
				}
			}
		}
	}
}

stock DestroyVehicleDynamicObject(vehicleid){
	new max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
	for(new i = 0; i < max_dobj; i++){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				DestroyDynamicObject(i);
			}
		}
	}
}

stock DeattachVehicleDynamicObject(vehicleid){
	new max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
	for(new i = 0; i < max_dobj; i++){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE,INVALID_VEHICLE_ID);
			}
		}
	}
}

stock DeattachPlayerDynamicObject(playerid){
	new max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
	for(new i = 0; i < max_dobj; i++){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER) == playerid){
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER,INVALID_PLAYER_ID);
			}
		}
	}
}

stock DestroyPlayerDynamicObject(playerid){
	new max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
	for(new i = 0; i < max_dobj; i++){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER) == playerid){
				DestroyDynamicObject(i);
			}
		}
	}
}

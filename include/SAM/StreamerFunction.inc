/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                  Streamer Special Functions                                                    *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * File Version: 1.9                                                                                                              *
 * Streamer Version: 2.7.8                                                                                                        *
 *                                                                                                                                *
 * Objects Functions:                                                                                                             *
 * GetDynamicObjectModel(objectid);                                                                                               *
 * SetDynamicObjectModel(objectid,modelid);                                                                                       *
 * GetDynamicObjectVW(objectid);                                                                                                  *
 * SetDynamicObjectVW(objectid,worldid);                                                                                          *
 * GetDynamicObjectINT(objectid);                                                                                                 *
 * SetDynamicObjectINT(objectid,interiorid);                                                                                      *
 * GetDynamicObjectSD(objectid,&Float:streamdistance);                                                                            *
 * SetDynamicObjectSD(objectid,Float:streamdistance);                                                                             *
 * GetDynamicObjectDD(objectid,&Float:drawdistance);                                                                              *
 * SetDynamicObjectDD(objectid,Float:drawdistance);                                                                               *
 * GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);                                  *
 * SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);                                        *
 * GetDynamicObjectMoveSpeed(objectid,&Float:speed);                                                                              *
 * SetDynamicObjectMoveSpeed(objectid,Float:speed);                                                                               *
 * GetDynamicObjectMovePos(objectid,&Float:x,&Float:y,&Float:z);                                                                  *
 * SetDynamicObjectMovePos(objectid,Float:x,Float:y,Float:z);                                                                     *
 * GetDynamicObjectMoveRot(objectid,&Float:rx,&Float:ry,&Float:rz);                                                               *
 * SetDynamicObjectMoveRot(objectid,Float:rx = -1000.0,Float:ry = -1000.0,Float:rz = -1000.0);                                    *
 * GetDynamicObjectMoveTime(objectid,&objstate,&rtime);                                                                           *
 * SetDynamicObjectAttachSync(objectid,syncrotation);                                                                             *
 * DeattachObjectDynamicObject(objectid);                                                                                         *
 * DeattachDynamicObjectComponent(objectid,type);                                                                                 *
 * DestroyDynamicObjectComponent(objectid,type);                                                                                  *
 * RebuildDynamicObject(objectid,...);                                                                                            *
 *                                                                                                                                *
 * SAMP Object Functions:                                                                                                         *
 * GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);                                         *
 * SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);                                               *
 * DestroyObjects();                                                                                                              *
 * CountObjects();                                                                                                                *
 *                                                                                                                                *
 * Cube Functions:                                                                                                                *
 * DestroyDynamicObjectsInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1);   *
 * DestroyDynamicObjectsInCubeFM(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1); *
 * IsPointInArea(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                      *
 * IsPointInAreaEx(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,vw1,int1,vw2,int2);  *
 *                                                                                                                                *
 * Vehicle Functions:                                                                                                             *
 * DestroyVehicleDynamicObject(vehicleid);                                                                                        *
 * DeattachVehicleDynamicObject(vehicleid);                                                                                       *
 *                                                                                                                                *
 * Check Point Functions:                                                                                                         *
 * SetDynamicCPSize(checkpointid,Float:size);                                                                                     *
 * GetDynamicCPPos(checkpointid,&Float:x,&Float:y,&Float:z);                                                                      *
 * SetDynamicCPPos(checkpointid,Float:x,Float:y,Float:z);                                                                         *
 *                                                                                                                                *
 * Race Check Point Functions:                                                                                                    *
 * SetDynamicRaceCPSize(checkpointid,Float:size);                                                                                 *
 * GetDynamicRaceCPPos(checkpointid,&Float:x,&Float:y,&Float:z);                                                                  *
 * SetDynamicRaceCPPos(checkpointid,Float:x,Float:y,Float:z);                                                                     *
 *                                                                                                                                *
 * Player Functions:                                                                                                              *
 * DestroyPlayerDynamicObject(playerid);                                                                                          *
 * DeattachPlayerDynamicObject(playerid);                                                                                         *
 *                                                                                                                                *
 * MapIcon Functions:                                                                                                             *
 * SetDynamicMapIconColor(iconid,color);                                                                                          *
 * GetDynamicMapIconPos(iconid,&Float:x,&Float:y,&Float:z);                                                                       *
 * SetDynamicMapIconPos(iconid,Float:x,Float:y,Float:z);                                                                          *
 *                                                                                                                                *
 * Pickup Functions:                                                                                                              *
 * GetDynamicPickupPos(pickupid,&Float:x,&Float:y,&Float:z);                                                                      *
 * SetDynamicPickupPos(pickupid,Float:x,Float:y,Float:z);                                                                         *
 * GetDynamicPickupModel(pickupid);                                                                                               *
 * SetDynamicPickupModel(pickupid,modelid);                                                                                       *
 *                                                                                                                                *
 * 3DText Functions:                                                                                                              *
 * GetDynamic3DTextPos(Text3D:id,&Float:x,&Float:y,&Float:z);                                                                     *
 * SetDynamic3DTextPos(Text3D:id,Float:x,Float:y,Float:z);                                                                        *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

#if defined _streamer_spec
	#endinput
#endif
#define _streamer_spec

#if !defined INVALID_STREAMER_ID
	#define INVALID_STREAMER_ID 0
#endif

#if !defined IsValidVehicle
	native IsValidVehicle(vehicleid);
#endif

//#define FIX_OBJECTS

#define MOVE_OBJECT_STATE_STOP		(0)
#define MOVE_OBJECT_STATE_MOVED		(1)
#define MOVE_OBJECT_STATE_INVALID	(2)

#define GetDynamicObjectModel(%1)			Streamer_GetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_MODEL_ID)
#define SetDynamicObjectModel(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_MODEL_ID,%2)
#define SetDynamicObjectVW(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_WORLD_ID,%2)
#define SetDynamicObjectINT(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_INTERIOR_ID,%2)
#define GetDynamicObjectVW(%1)				Streamer_GetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_WORLD_ID)
#define GetDynamicObjectINT(%1)				Streamer_GetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_INTERIOR_ID)
#define SetDynamicObjectSD(%1,%2)			Streamer_SetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_STREAM_DISTANCE,%2)
#define SetDynamicObjectDD(%1,%2)			Streamer_SetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_DRAW_DISTANCE,%2)
#define SetDynamicObjectMoveSpeed(%1,%2)	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_MOVE_SPEED,%2)
#define GetDynamicObjectMoveSpeed(%1,%2)	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_MOVE_SPEED,%2)
#define GetDynamicObjectSD(%1,%2)			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_STREAM_DISTANCE,%2)
#define GetDynamicObjectDD(%1,%2)			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_DRAW_DISTANCE,%2)
#define DeattachObjectDynamicObject(%1)		Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_ATTACHED_OBJECT,INVALID_STREAMER_ID)
#define SetDynamicObjectAttachSync(%1,%2)	Streamer_SetIntData(STREAMER_TYPE_OBJECT,%1,E_STREAMER_SYNC_ROTATION,%2)
#define SetDynamicCPSize(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_CP,%1,E_STREAMER_SIZE,%2)
#define SetDynamicRaceCPSize(%1,%2)			Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,%1,E_STREAMER_SIZE,%2)
#define SetDynamicMapIconColor(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,%1,E_STREAMER_COLOR,%2)
#define GetDynamicPickupModel(%1)			Streamer_GetIntData(STREAMER_TYPE_PICKUP,%1,E_STREAMER_MODEL_ID)
#define SetDynamicPickupModel(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_PICKUP,%1,E_STREAMER_MODEL_ID,%2)


stock SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	if(IsValidDynamicObject(objectid)){
		SetDynamicObjectPos(objectid,x,y,z);
		SetDynamicObjectRot(objectid,rx,ry,rz);
	}
}

stock GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	if(IsValidDynamicObject(objectid)){
		GetDynamicObjectPos(objectid,x,y,z);
		GetDynamicObjectRot(objectid,rx,ry,rz);
	}
}

stock SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	if(IsValidObject(objectid)){
		SetObjectPos(objectid,x,y,z);
		SetObjectRot(objectid,rx,ry,rz);
	}
}

stock GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	if(IsValidObject(objectid)){
		GetObjectPos(objectid,x,y,z);
		GetObjectRot(objectid,rx,ry,rz);
	}
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

stock RebuildDynamicObject(objectid,modelid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,worldid = -1,interiorid = -1,playerid = -1,Float:streamdistance = STREAMER_OBJECT_SD,Float:drawdistance = STREAMER_OBJECT_DD){
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

stock IsPointInArea(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy) && (z >= minz && z <= maxz)) return true;
	return false;
}

stock IsPointInAreaEx(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,vw1 = -1,int1 = -1,vw2 = -1,int2 = -1){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy) && (z >= minz && z <= maxz) && (vw1 == vw2) && (int1 == int2)) return true;
	return false;
}

stock DestroyDynamicObjectsInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1){
	new Float:piox,Float:pioy,Float:pioz,pioVW,pioINT,max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
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
	new Float:piox,Float:pioy,Float:pioz,pioVW,pioINT,max_dobj = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
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

stock GetDynamicCPPos(checkpointid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Z,z);
}

stock SetDynamicCPPos(checkpointid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Z,z);
}

stock GetDynamicRaceCPPos(checkpointid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Z,z);
}

stock SetDynamicRaceCPPos(checkpointid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Z,z);
}

stock GetDynamicObjectMovePos(objectid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Z,z);
}

stock GetDynamicObjectMoveRot(objectid,&Float:rx,&Float:ry,&Float:rz){
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_X,rx);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Y,ry);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Z,rz);
}

stock SetDynamicObjectMovePos(objectid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Z,z);
}

stock SetDynamicObjectMoveRot(objectid,Float:rx = -1000.0,Float:ry = -1000.0,Float:rz = -1000.0){
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_X,rx);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Y,ry);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Z,rz);
}

stock GetDynamicPickupPos(pickupid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Z,z);
}

stock SetDynamicPickupPos(pickupid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Z,z);
}

stock GetDynamicMapIconPos(iconid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Z,z);
}

stock SetDynamicMapIconPos(iconid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Z,z);
}

stock GetDynamic3DTextPos(Text3D:id,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Z,z);
}

stock SetDynamic3DTextPos(Text3D:id,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Z,z);
}

stock DestroyDynamicObjectComponent(objectid,type){
	new max_dobj = Streamer_GetUpperBound(type);
	for(new i = 0; i < max_dobj; i++){
		if(Streamer_GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == objectid){
			switch(type){
				case STREAMER_TYPE_OBJECT:	if(IsValidDynamicObject(i)) DestroyDynamicObject(i);
				case STREAMER_TYPE_AREA:	if(IsValidDynamicArea(i)) DestroyDynamicArea(i);
			}
		}
	}
}

stock DeattachDynamicObjectComponent(objectid,type){
	new max_dobj = Streamer_GetUpperBound(type);
	for(new i = 0; i < max_dobj; i++){
		if(Streamer_GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == objectid){
			switch(type){
				case STREAMER_TYPE_OBJECT:	Streamer_SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_STREAMER_ID);
				case STREAMER_TYPE_AREA:	Streamer_SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_VEHICLE_ID);
			}
		}
	}
}

stock GetDynamicObjectMoveTime(objectid,&objstate,&rtime){
	if(IsValidDynamicObject(objectid)){
		if(IsDynamicObjectMoving(objectid)){
			new Float:piox,Float:pioy,Float:pioz,Float:piotx,Float:pioty,Float:piotz,Float:dist,Float:objspeed;
			GetDynamicObjectPos(objectid,piox,pioy,pioz);
			GetDynamicObjectMovePos(objectid,piotx,pioty,piotz);
			GetDynamicObjectMoveSpeed(objectid,objspeed);
			dist = VectorSize(piox-piotx,pioy-pioty,pioz-piotz);
			rtime = floatround((dist/objspeed)*1000.0);
			objstate =  MOVE_OBJECT_STATE_MOVED;
		} else {
			objstate = MOVE_OBJECT_STATE_STOP;
			rtime = 0;
		}
	} else {
		objstate = MOVE_OBJECT_STATE_INVALID;
		rtime = 0;
	}
}


//Fix Destroy Objects
#if defined FIX_OBJECTS
	//DestroyDynamicObject
	stock AC_DestroyDynamicObject(&objectid){
		new dobj = DestroyDynamicObject(objectid);
		objectid = INVALID_STREAMER_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicObject
		#undef DestroyDynamicObject
	#else
		#define _ALS_DestroyDynamicObject
	#endif
	#define DestroyDynamicObject AC_DestroyDynamicObject

	//DestroyObject
	stock AC_DestroyObject(&objectid){
		new dobj = DestroyObject(objectid);
		objectid = INVALID_OBJECT_ID;
		return dobj;
	}

	#if defined _ALS_DestroyObject
		#undef DestroyObject
	#else
		#define _ALS_DestroyObject
	#endif
	#define DestroyObject AC_DestroyObject

	//DestroyPlayerObject
	stock AC_DestroyPlayerObject(playerid,&objectid){
		new dobj = DestroyPlayerObject(playerid,objectid);
		objectid = INVALID_OBJECT_ID;
		return dobj;
	}

	#if defined _ALS_DestroyPlayerObject
		#undef DestroyPlayerObject
	#else
		#define _ALS_DestroyPlayerObject
	#endif
	#define DestroyPlayerObject AC_DestroyPlayerObject

	//DestroyDynamicPickup
	stock AC_DestroyDynamicPickup(&pickupid){
		new dobj = DestroyDynamicPickup(pickupid);
		pickupid = INVALID_STREAMER_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicPickup
		#undef DestroyDynamicPickup
	#else
		#define _ALS_DestroyDynamicPickup
	#endif
	#define DestroyDynamicPickup AC_DestroyDynamicPickup

	//DestroyDynamicCP
	stock AC_DestroyDynamicCP(&checkpointid){
		new dobj = DestroyDynamicCP(checkpointid);
		checkpointid = INVALID_STREAMER_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicCP
		#undef DestroyDynamicCP
	#else
		#define _ALS_DestroyDynamicCP
	#endif
	#define DestroyDynamicCP AC_DestroyDynamicCP

	//DestroyDynamicRaceCP
	stock AC_DestroyDynamicRaceCP(&checkpointid){
		new dobj = DestroyDynamicRaceCP(checkpointid);
		checkpointid = INVALID_STREAMER_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicRaceCP
		#undef DestroyDynamicRaceCP
	#else
		#define _ALS_DestroyDynamicRaceCP
	#endif
	#define DestroyDynamicRaceCP AC_DestroyDynamicRaceCP

	//DestroyDynamicMapIcon
	stock AC_DestroyDynamicMapIcon(&iconid){
		new dobj = DestroyDynamicMapIcon(iconid);
		iconid = INVALID_STREAMER_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicMapIcon
		#undef DestroyDynamicMapIcon
	#else
		#define _ALS_DestroyDynamicMapIcon
	#endif
	#define DestroyDynamicMapIcon AC_DestroyDynamicMapIcon

	//DestroyDynamic3DTextLabel
	stock AC_DestroyDynamic3DTextLabel(&Text3D:id){
		new dobj = DestroyDynamic3DTextLabel(id);
		id = Text3D:INVALID_STREAMER_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamic3DTextLabel
		#undef DestroyDynamic3DTextLabel
	#else
		#define _ALS_DestroyDynamic3DTextLabel
	#endif
	#define DestroyDynamic3DTextLabel AC_DestroyDynamic3DTextLabel

	//DestroyDynamicArea
	stock AC_DestroyDynamicArea(&areaid){
		new dobj = DestroyDynamicArea(areaid);
		areaid = INVALID_STREAMER_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicArea
		#undef DestroyDynamicArea
	#else
		#define _ALS_DestroyDynamicArea
	#endif
	#define DestroyDynamicArea AC_DestroyDynamicArea

#endif
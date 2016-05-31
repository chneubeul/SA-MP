/*******************************************************************************************************************************************
 *                                                                                                                                         *
 *                                                       Streamer Special Functions                                                        *
 *                                                                                                                                         *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                                     *
 *                                                                                                                                         *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                                  *
 *                                                                                                                                         *
 * File Version: 2.3C                                                                                                                      *
 * Streamer Version: 2.8.2                                                                                                                 *
 *                                                                                                                                         *
 * Objects Functions:                                                                                                                      *
 * GetDynamicObjectModel(objectid);                                                                                                        *
 * SetDynamicObjectModel(objectid,modelid);                                                                                                *
 * GetDynamicObjectVW(objectid);                                                                                                           *
 * SetDynamicObjectVW(objectid,worldid);                                                                                                   *
 * GetDynamicObjectINT(objectid);                                                                                                          *
 * SetDynamicObjectINT(objectid,interiorid);                                                                                               *
 * GetDynamicObjectSD(objectid,&Float:streamdistance);                                                                                     *
 * SetDynamicObjectSD(objectid,Float:streamdistance);                                                                                      *
 * GetDynamicObjectDD(objectid,&Float:drawdistance);                                                                                       *
 * SetDynamicObjectDD(objectid,Float:drawdistance);                                                                                        *
 * GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);                                           *
 * SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);                                                 *
 * GetDynamicObjectMoveSpeed(objectid,&Float:speed);                                                                                       *
 * SetDynamicObjectMoveSpeed(objectid,Float:speed);                                                                                        *
 * GetDynamicObjectMovePos(objectid,&Float:x,&Float:y,&Float:z);                                                                           *
 * SetDynamicObjectMovePos(objectid,Float:x,Float:y,Float:z);                                                                              *
 * GetDynamicObjectMoveRot(objectid,&Float:rx,&Float:ry,&Float:rz);                                                                        *
 * SetDynamicObjectMoveRot(objectid,Float:rx = -1000.0,Float:ry = -1000.0,Float:rz = -1000.0);                                             *
 * GetDynamicObjectMoveTime(objectid,&objstate,&rtime);                                                                                    *
 * SetDynamicObjectAttachSync(objectid,syncrotation);                                                                                      *
 * ResetDynamicObjectMaterial(objectid,materialindex);                                                                                     *
 * ResetDynamicObjectMaterialAll(objectid);                                                                                                *
 * DeattachObjectDynamicObject(objectid);                                                                                                  *
 * DeattachDynamicObjectComponent(objectid,type);                                                                                          *
 * DestroyDynamicObjectComponent(objectid,type);                                                                                           *
 * RebuildDynamicObject(objectid,...);                                                                                                     *
 * GetDynamicObjectArea(objectid);                                                                                                         *
 * SetDynamicObjectArea(objectid,areaid);                                                                                                  *
 * GetDynamicObjectPriority(objectid);                                                                                                     *
 * SetDynamicObjectPriority(objectid,priority);                                                                                            *
 *                                                                                                                                         *
 * SAMP Functions:                                                                                                                         *
 * GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);                                                  *
 * SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);                                                        *
 * CountObjects();                                                                                                                         *
 * CountVehicles();                                                                                                                        *
 * CountPlayerObjects(playerid,bool:streamer = false);                                                                                     *
 * DestroyObjects();                                                                                                                       *
 * DestroyVehicles();                                                                                                                      *
 * DestroyPlayerObjects(playerid,bool:streamer = false);                                                                                   *
 * GangZoneDestroyAll();                                                                                                                   *
 *                                                                                                                                         *
 * Cube Functions:                                                                                                                         *
 * DestroyDynamicObjectsInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1);            *
 * DestroyDynamicObjectsInCubeFM(modelid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1);  *
 * IsPointInArea(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                               *
 * IsPointInAreaEx(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,vw1,int1,vw2,int2);           *
 *                                                                                                                                         *
 * Vehicle Functions:                                                                                                                      *
 * DestroyVehicleDynamicObject(vehicleid);                                                                                                 *
 * DeattachVehicleDynamicObject(vehicleid);                                                                                                *
 *                                                                                                                                         *
 * Check Point Functions:                                                                                                                  *
 * GetDynamicCPPos(checkpointid,&Float:x,&Float:y,&Float:z);                                                                               *
 * SetDynamicCPPos(checkpointid,Float:x,Float:y,Float:z);                                                                                  *
 * GetDynamicCPSize(checkpointid,&Float:size);                                                                                             *
 * SetDynamicCPSize(checkpointid,Float:size);                                                                                              *
 * GetDynamicCPVW(checkpointid);                                                                                                           *
 * SetDynamicCPVW(checkpointid,worldid);                                                                                                   *
 * GetDynamicCPINT(checkpointid);                                                                                                          *
 * SetDynamicCPINT(checkpointid,interiorid);                                                                                               *
 * GetDynamicCPSD(checkpointid,&Float:streamdistance);                                                                                     *
 * SetDynamicCPSD(checkpointid,Float:streamdistance);                                                                                      *
 * GetDynamicCPArea(checkpointid);                                                                                                         *
 * SetDynamicCPArea(checkpointid,areaid);                                                                                                  *
 * GetDynamicCPPriority(checkpointid);                                                                                                     *
 * SetDynamicCPPriority(checkpointid,priority);                                                                                            *
 *                                                                                                                                         *
 * Race Check Point Functions:                                                                                                             *
 * GetDynamicRaceCPPos(checkpointid,&Float:x,&Float:y,&Float:z);                                                                           *
 * SetDynamicRaceCPPos(checkpointid,Float:x,Float:y,Float:z);                                                                              *
 * GetDynamicRaceCPNext(checkpointid,&Float:nextx,&Float:nexty,&Float:nextz);                                                              *
 * SetDynamicRaceCPNext(checkpointid,Float:nextx,Float:nexty,Float:nextz);                                                                 *
 * GetDynamicRaceCPType(checkpointid);                                                                                                     *
 * SetDynamicRaceCPType(checkpointid,type);                                                                                                *
 * GetDynamicRaceCPSize(checkpointid,&Float:size);                                                                                         *
 * SetDynamicRaceCPSize(checkpointid,Float:size);                                                                                          *
 * GetDynamicRaceCPVW(checkpointid);                                                                                                       *
 * SetDynamicRaceCPVW(checkpointid,worldid);                                                                                               *
 * GetDynamicRaceCPINT(checkpointid);                                                                                                      *
 * SetDynamicRaceCPINT(checkpointid,interiorid);                                                                                           *
 * GetDynamicRaceCPSD(checkpointid,&Float:streamdistance);                                                                                 *
 * SetDynamicRaceCPSD(checkpointid,Float:streamdistance);                                                                                  *
 * GetDynamicRaceCPArea(checkpointid);                                                                                                     *
 * SetDynamicRaceCPArea(checkpointid,areaid);                                                                                              *
 * GetDynamicRaceCPPriority(checkpointid);                                                                                                 *
 * SetDynamicRaceCPPriority(checkpointid,priority);                                                                                        *
 *                                                                                                                                         *
 * Player Functions:                                                                                                                       *
 * DestroyPlayerDynamicObject(playerid);                                                                                                   *
 * DeattachPlayerDynamicObject(playerid);                                                                                                  *
 *                                                                                                                                         *
 * MapIcon Functions:                                                                                                                      *
 * GetDynamicMapIconPos(iconid,&Float:x,&Float:y,&Float:z);                                                                                *
 * SetDynamicMapIconPos(iconid,Float:x,Float:y,Float:z);                                                                                   *
 * GetDynamicMapIconType(iconid);                                                                                                          *
 * SetDynamicMapIconType(iconid,type);                                                                                                     *
 * GetDynamicMapIconStyle(iconid);                                                                                                         *
 * SetDynamicMapIconStyle(iconid,style);                                                                                                   *
 * GetDynamicMapIconVW(iconid);                                                                                                            *
 * SetDynamicMapIconVW(iconid,worldid);                                                                                                    *
 * GetDynamicMapIconINT(iconid);                                                                                                           *
 * SetDynamicMapIconINT(iconid,interiorid);                                                                                                *
 * GetDynamicMapIconSD(iconid,&Float:streamdistance);                                                                                      *
 * SetDynamicMapIconSD(iconid,Float:streamdistance);                                                                                       *
 * SetDynamicMapIconColor(iconid,color);                                                                                                   *
 * GetDynamicMapIconColor(iconid);                                                                                                         *
 * GetDynamicMapIconArea(iconid);                                                                                                          *
 * SetDynamicMapIconArea(iconid,areaid);                                                                                                   *
 * GetDynamicMapIconPriority(iconid);                                                                                                      *
 * SetDynamicMapIconPriority(iconid,priority);                                                                                             *
 *                                                                                                                                         *
 * Pickup Functions:                                                                                                                       *
 * GetDynamicPickupPos(pickupid,&Float:x,&Float:y,&Float:z);                                                                               *
 * SetDynamicPickupPos(pickupid,Float:x,Float:y,Float:z);                                                                                  *
 * GetDynamicPickupModel(pickupid);                                                                                                        *
 * SetDynamicPickupModel(pickupid,modelid);                                                                                                *
 * GetDynamicPickupVW(pickupid);                                                                                                           *
 * SetDynamicPickupVW(pickupid,worldid);                                                                                                   *
 * GetDynamicPickupINT(pickupid);                                                                                                          *
 * SetDynamicPickupINT(pickupid,interiorid);                                                                                               *
 * GetDynamicPickupSD(pickupid,&Float:streamdistance);                                                                                     *
 * SetDynamicPickupSD(pickupid,Float:streamdistance);                                                                                      *
 * GetDynamicPickupType(pickupid);                                                                                                         *
 * SetDynamicPickupType(pickupid,type);                                                                                                    *
 * GetDynamicPickupArea(pickupid);                                                                                                         *
 * SetDynamicPickupArea(pickupid,areaid);                                                                                                  *
 * GetDynamicPickupPriority(pickupid);                                                                                                     *
 * SetDynamicPickupPriority(pickupid,priority);                                                                                            *
 *                                                                                                                                         *
 * 3DText Functions:                                                                                                                       *
 * GetDynamic3DTextPos(Text3D:id,&Float:x,&Float:y,&Float:z);                                                                              *
 * SetDynamic3DTextPos(Text3D:id,Float:x,Float:y,Float:z);                                                                                 *
 * GetDynamic3DTextDD(Text3D:id,Float:drawdistance);                                                                                       *
 * SetDynamic3DTextDD(Text3D:id,Float:drawdistance);                                                                                       *
 * GetDynamic3DTextSD(Text3D:id,&Float:streamdistance);                                                                                    *
 * SetDynamic3DTextSD(Text3D:id,Float:streamdistance);                                                                                     *
 * GetDynamic3DTextVW(Text3D:id);                                                                                                          *
 * SetDynamic3DTextVW(Text3D:id,worldid);                                                                                                  *
 * GetDynamic3DTextINT(Text3D:id);                                                                                                         *
 * SetDynamic3DTextINT(Text3D:id,interiorid);                                                                                              *
 * GetDynamic3DTextColor(Text3D:id);                                                                                                       *
 * SetDynamic3DTextColor(Text3D:id,color);                                                                                                 *
 * GetDynamic3DTextArea(Text3D:id);                                                                                                        *
 * SetDynamic3DTextArea(Text3D:id,areaid);                                                                                                 *
 * GetDynamic3DTextPriority(Text3D:id);                                                                                                    *
 * SetDynamic3DTextPriority(Text3D:id,priority);                                                                                           *
 * SetDynamic3DTextTestLos(Text3D:id,testlos);                                                                                             *
 * SetDynamic3DTextAttachPlayer(Text3D:id,attachedplayer);                                                                                 *
 * SetDynamic3DTextAttachVehicle(Text3D:id,attachedvehicle);                                                                               *
 *                                                                                                                                         *
 * Area Functions:                                                                                                                         *
 * GetDynamicCirclePos(areaid,&Float:x,&Float:y);                                                                                          *
 * SetDynamicCirclePos(areaid,Float:x,Float:y);                                                                                            *
 * GetDynamicCylinderPos(areaid,&Float:x,&Float:y,&Float:minz,&Float:maxz);                                                                *
 * SetDynamicCylinderPos(areaid,Float:x,Float:y,Float:minz,Float:maxz);                                                                    *
 * GetDynamicSpherePos(areaid,&Float:x,&Float:y,&Float:z);                                                                                 *
 * SetDynamicSpherePos(areaid,Float:x,Float:y,Float:z);                                                                                    *
 * GetDynamicRectanglePos(areaid,&Float:minx,&Float:miny,&Float:maxx,&Float:maxy);                                                         *
 * SetDynamicRectanglePos(areaid,Float:minx,Float:miny,Float:maxx,Float:maxy);                                                             *
 * GetDynamicCubePos(areaid,&Float:minx,&Float:miny,&Float:minz,&Float:maxx,&Float:maxy,&Float:maxz);                                      *
 * SetDynamicCubePos(areaid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                                            *
 * GetDynamicCuboidPos(areaid,&Float:minx,&Float:miny,&Float:minz,&Float:maxx,&Float:maxy,&Float:maxz);                                    *
 * SetDynamicCuboidPos(areaid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                                          *
 * GetDynamicAreaVW(areaid);                                                                                                               *
 * SetDynamicAreaVW(areaid,worldid);                                                                                                       *
 * GetDynamicAreaINT(areaid);                                                                                                              *
 * SetDynamicAreaINT(areaid,interiorid);                                                                                                   *
 * GetDynamicAreaSize(areaid,Float:size);                                                                                                  *
 * SetDynamicAreaSize(areaid,Float:size);                                                                                                  *
 *                                                                                                                                         *
 * Anti Area Functions:                                                                                                                    *
 * IsPointInAntiArea(areaid,Float:x,Float:y,Float:z);                                                                                      *
 * IsPlayerInAntiArea(playerid,areaid,recheck = 0);                                                                                        *
 * IsPlayerInAnyAntiArea(playerid,recheck = 0);                                                                                            *
 * IsAnyPlayerInAntiArea(areaid,recheck = 0);                                                                                              *
 * IsAnyPlayerInAnyAntiArea(recheck = 0);                                                                                                  *
 *                                                                                                                                         *
 * Anti Area Callbacks:                                                                                                                    *
 * OnPlayerEnterAntiArea(playerid,areaid);                                                                                                 *
 * OnPlayerLeaveAntiArea(playerid,areaid);                                                                                                 *
 *                                                                                                                                         *
 * Pool Size Functions:                                                                                                                    *
 * GetDynamicObjectPoolSize();                                                                                                             *
 * GetDynamicPickupPoolSize();                                                                                                             *
 * GetDynamicCPPoolSize();                                                                                                                 *
 * GetDynamicRaceCPPoolSize();                                                                                                             *
 * GetDynamicMapIconPoolSize();                                                                                                            *
 * GetDynamic3DTextPoolSize();                                                                                                             *
 * GetDynamicAreaPoolSize();                                                                                                               *
 *                                                                                                                                         *
 * Update Functions:                                                                                                                       *
 * UpdateAllDynamicElements();                                                                                                             *
 * UpdateAllDynamicObjects();                                                                                                              *
 * UpdateAllDynamicPickups();                                                                                                              *
 * UpdateAllDynamicCPs();                                                                                                                  *
 * UpdateAllDynamicRaceCPs();                                                                                                              *
 * UpdateAllDynamicMapIcons();                                                                                                             *
 * UpdateAllDynamic3DTextLabels();                                                                                                         *
 * UpdateAllDynamicAreas();                                                                                                                *
 *                                                                                                                                         *
 * Foreach Functions:                                                                                                                      *
 * ForDynamicObjects(variable);                                                                                                            *
 * ForDynamicPickups(variable);                                                                                                            *
 * ForDynamicCPs(variable);                                                                                                                *
 * ForDynamicRaceCPs(variable);                                                                                                            *
 * ForDynamicMapIcons(variable);                                                                                                           *
 * ForDynamic3DTextLabels(variable);                                                                                                       *
 * ForDynamicAreas(variable);                                                                                                              *
 *                                                                                                                                         *
 * Extended Functions:                                                                                                                     *
 * bool:IsValidStreamer(version);                                                                                                          *
 * GetStreamerVersion();                                                                                                                   *
 * GetValidStreamerVersion();                                                                                                              *
 * GetStreamerVersionName(name[], value = GET_STREAMER_VERSION, maxdest = sizeof name);                                                    *
 *                                                                                                                                         *
 *******************************************************************************************************************************************/

/*
//Check Version StreamerFunction.inc
#if !defined _streamer_spec
	#error You need StreamerFunction.inc v2.3C
#elseif !defined Streamer_Spec_Version
	#error Update you StreamerFunction.inc to v2.3C
#elseif (Streamer_Spec_Version < 20303)
	#error Update you StreamerFunction.inc to v2.3C
#endif
*/

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

#if defined _streamer_spec
	#endinput
#endif
#define _streamer_spec

#define Streamer_Spec_Version 					(20303) //a.b[c] 10000*a+100*b+c
#define Valid_Streamer_Version 					(0x282001)

#if !defined INVALID_STREAMER_ID
	#define INVALID_STREAMER_ID 0
#endif

#if defined INVALID_DYNAMIC_OBJECT_ID
	#if (INVALID_DYNAMIC_OBJECT_ID != INVALID_STREAMER_ID)
		#error Invalid DestroyDynamicObject Hook version. Invalid definition INVALID_DYNAMIC_OBJECT_ID
	#endif
	#undef INVALID_DYNAMIC_OBJECT_ID
#endif
#define INVALID_DYNAMIC_OBJECT_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_PICKUP_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_CP_ID					INVALID_STREAMER_ID
#define INVALID_DYNAMIC_RACE_CP_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_MAP_ICON_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_3D_TEXT_LABEL_ID		INVALID_STREAMER_ID
#define INVALID_DYNAMIC_AREA_ID					INVALID_STREAMER_ID

#if !defined IsValidVehicle
	native IsValidVehicle(vehicleid);
#endif

//Force Fix Objects
#if !defined FIX_OBJECTS
	#define FIX_OBJECTS
#endif

#define GET_STREAMER_VERSION					(0xFFFFFFFF)

#define MOVE_OBJECT_STATE_STOP					(0)
#define MOVE_OBJECT_STATE_MOVED					(1)
#define MOVE_OBJECT_STATE_INVALID				(2)

#define GetStreamerVersion()					(Streamer_IncludeFileVersion)
#define GetValidStreamerVersion()				(Valid_Streamer_Version)

//DynamicObject
#define GetDynamicObjectModel(%1)				Streamer_GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MODEL_ID)
#define SetDynamicObjectModel(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MODEL_ID,(%2))
#define GetDynamicObjectINT(%1)					Streamer_GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicObjectINT(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicObjectVW(%1)					Streamer_GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicObjectVW(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicObjectSD(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicObjectSD(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicObjectDD(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define SetDynamicObjectDD(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define GetDynamicObjectMoveSpeed(%1,%2) 		Streamer_GetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MOVE_SPEED,(%2))
#define SetDynamicObjectMoveSpeed(%1,%2) 		Streamer_SetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MOVE_SPEED,(%2))
#define DeattachObjectDynamicObject(%1)			Streamer_SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_ATTACHED_OBJECT,INVALID_STREAMER_ID)
#define SetDynamicObjectAttachSync(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_SYNC_ROTATION,(%2))
#define GetDynamicObjectArea(%1)				Streamer_GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_AREA_ID)
#define SetDynamicObjectArea(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_AREA_ID,(%2))
#define GetDynamicObjectPriority(%1)			Streamer_GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_PRIORITY)
#define SetDynamicObjectPriority(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_PRIORITY,(%2))

//DynamicPickup
#define GetDynamicPickupModel(%1)				Streamer_GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_MODEL_ID)
#define SetDynamicPickupModel(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_MODEL_ID,(%2))
#define GetDynamicPickupSD(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicPickupSD(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicPickupVW(%1)					Streamer_GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicPickupVW(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicPickupINT(%1)					Streamer_GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicPickupINT(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicPickupType(%1)				Streamer_GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_TYPE)
#define SetDynamicPickupType(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_TYPE,(%2))
#define GetDynamicPickupArea(%1)				Streamer_GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_AREA_ID)
#define SetDynamicPickupArea(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_AREA_ID,(%2))
#define GetDynamicPickupPriority(%1)			Streamer_GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_PRIORITY)
#define SetDynamicPickupPriority(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_PRIORITY,(%2))

//DynamicCP
#define GetDynamicCPSize(%1,%2)					Streamer_GetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_SIZE,(%2))
#define SetDynamicCPSize(%1,%2)					Streamer_SetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_SIZE,(%2))
#define GetDynamicCPArea(%1)					Streamer_GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_AREA_ID)
#define SetDynamicCPArea(%1,%2)					Streamer_SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_AREA_ID,(%2))
#define GetDynamicCPPriority(%1)				Streamer_GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_PRIORITY)
#define SetDynamicCPPriority(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicCPSD(%1,%2)					Streamer_GetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicCPSD(%1,%2)					Streamer_SetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicCPVW(%1)						Streamer_GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicCPVW(%1,%2)					Streamer_SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicCPINT(%1)						Streamer_GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicCPINT(%1,%2)					Streamer_SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_INTERIOR_ID,(%2))

//DynamicRaceCP
#define GetDynamicRaceCPSize(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_SIZE,(%2))
#define SetDynamicRaceCPSize(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_SIZE,(%2))
#define GetDynamicRaceCPArea(%1)				Streamer_GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_AREA_ID)
#define SetDynamicRaceCPArea(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_AREA_ID,(%2))
#define GetDynamicRaceCPPriority(%1)			Streamer_GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_PRIORITY)
#define SetDynamicRaceCPPriority(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicRaceCPSD(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicRaceCPSD(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicRaceCPType(%1)				Streamer_GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_TYPE)
#define SetDynamicRaceCPType(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_TYPE,(%2))
#define GetDynamicRaceCPVW(%1)					Streamer_GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicRaceCPVW(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicRaceCPINT(%1)					Streamer_GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicRaceCPINT(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_INTERIOR_ID,(%2))

//DynamicMapIcon
#define GetDynamicMapIconColor(%1)				Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_COLOR)
#define SetDynamicMapIconColor(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_COLOR,(%2))
#define GetDynamicMapIconArea(%1)				Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_AREA_ID)
#define SetDynamicMapIconArea(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_AREA_ID,(%2))
#define GetDynamicMapIconPriority(%1)			Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_PRIORITY)
#define SetDynamicMapIconPriority(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicMapIconSD(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicMapIconSD(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicMapIconType(%1)				Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_TYPE)
#define SetDynamicMapIconType(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_TYPE,(%2))
#define GetDynamicMapIconVW(%1)					Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicMapIconVW(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicMapIconINT(%1)				Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicMapIconINT(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicMapIconStyle(%1)				Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STYLE)
#define SetDynamicMapIconStyle(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STYLE,(%2))

//3DText
#define GetDynamic3DTextDD(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define SetDynamic3DTextDD(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define GetDynamic3DTextSD(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamic3DTextSD(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamic3DTextVW(%1)					Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_WORLD_ID)
#define SetDynamic3DTextVW(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamic3DTextINT(%1)					Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamic3DTextINT(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamic3DTextColor(%1)				Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_COLOR)
#define SetDynamic3DTextColor(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_COLOR,(%2))
#define SetDynamic3DTextTestLos(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_TEST_LOS,(%2))
#define SetDynamic3DTextAttachPlayer(%1,%2)		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_ATTACHED_PLAYER,(%2))
#define SetDynamic3DTextAttachVehicle(%1,%2)	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_ATTACHED_VEHICLE,(%2))
#define GetDynamic3DTextArea(%1)				Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_AREA_ID)
#define SetDynamic3DTextArea(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_AREA_ID,(%2))
#define GetDynamic3DTextPriority(%1)			Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_PRIORITY)
#define SetDynamic3DTextPriority(%1,%2)			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_PRIORITY,(%2))

//DynamicArea
#define GetDynamicAreaVW(%1)					Streamer_GetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicAreaVW(%1,%2)					Streamer_SetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicAreaINT(%1)					Streamer_GetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicAreaINT(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicAreaSize(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_AREA,(%1),E_STREAMER_SIZE,(%2))
#define SetDynamicAreaSize(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_AREA,(%1),E_STREAMER_SIZE,(%2))


//DynamicAntiArea
#define IsPlayerInAntiArea(%0,%1,%2)			(!IsPlayerInDynamicArea(%0,%1,%2))
#define IsPlayerInAnyAntiArea(%0,%1)			(!IsPlayerInAnyDynamicArea(%0,%1))
#define IsAnyPlayerInAntiArea(%0,%1)			(!IsAnyPlayerInDynamicArea(%0,%1))
#define IsAnyPlayerInAnyAntiArea(%0)			(!IsAnyPlayerInAnyDynamicArea(%0))
#define IsPointInAntiArea(%0,%1,%2,%3)			(!IsPointInDynamicArea(%0,%1,%2,%3))

//PoolSize
#define GetDynamicObjectPoolSize()				Streamer_GetUpperBound(STREAMER_TYPE_OBJECT)
#define GetDynamicPickupPoolSize()				Streamer_GetUpperBound(STREAMER_TYPE_PICKUP)
#define GetDynamicCPPoolSize()					Streamer_GetUpperBound(STREAMER_TYPE_CP)
#define GetDynamicRaceCPPoolSize()				Streamer_GetUpperBound(STREAMER_TYPE_RACE_CP)
#define GetDynamicMapIconPoolSize()				Streamer_GetUpperBound(STREAMER_TYPE_MAP_ICON)
#define GetDynamic3DTextPoolSize()				Streamer_GetUpperBound(STREAMER_TYPE_3D_TEXT_LABEL)
#define GetDynamicAreaPoolSize()				Streamer_GetUpperBound(STREAMER_TYPE_AREA)

//Foreach
#define ForDynamicObjects(%1)					for(new %1 = 1, p_%1 = GetDynamicObjectPoolSize(); %1 <= p_%1; %1++)
#define ForDynamicPickups(%1)					for(new %1 = 1, p_%1 = GetDynamicPickupPoolSize(); %1 <= p_%1; %1++)
#define ForDynamicCPs(%1)						for(new %1 = 1, p_%1 = GetDynamicCPPoolSize(); %1 <= p_%1; %1++)
#define ForDynamicRaceCPs(%1)					for(new %1 = 1, p_%1 = GetDynamicRaceCPPoolSize(); %1 <= p_%1; %1++)
#define ForDynamicMapIcons(%1)					for(new %1 = 1, p_%1 = GetDynamicMapIconPoolSize(); %1 <= p_%1; %1++)
#define ForDynamic3DTextLabels(%1)				for(new %1 = 1, p_%1 = GetDynamic3DTextPoolSize(); %1 <= p_%1; %1++)
#define ForDynamicAreas(%1)						for(new %1 = 1, p_%1 = GetDynamicAreaPoolSize(); %1 <= p_%1; %1++)

stock bool:IsValidStreamer(version){
	if(GetStreamerVersion() < version) return false;
	return true;
}

stock GetStreamerVersionName(name[], value = GET_STREAMER_VERSION, maxdest = sizeof name){
	if(value == GET_STREAMER_VERSION) value = GetStreamerVersion();
	new str[10];
	format(str,sizeof(str),"%06x",value);
	format(name,maxdest,"%d.%d.%dr%d",(str[0]-48),(str[1]-48),(str[2]-48),(((str[3]-48)*100) + ((str[4]-48)*10) + (str[5]-48)));
}

stock SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	SetDynamicObjectPos(objectid,x,y,z);
	SetDynamicObjectRot(objectid,rx,ry,rz);
}

stock GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	GetDynamicObjectPos(objectid,x,y,z);
	GetDynamicObjectRot(objectid,rx,ry,rz);
}

stock SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	SetObjectPos(objectid,x,y,z);
	SetObjectRot(objectid,rx,ry,rz);
}

stock GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	GetObjectPos(objectid,x,y,z);
	GetObjectRot(objectid,rx,ry,rz);
}

stock CountObjects(){
	new count = 0;
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(IsValidObject(i)) count += 1;
	}
	return count;
}

stock DestroyObjects(){
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(IsValidObject(i)) DestroyObject(i);
	}
}

stock CountVehicles(){
	new count = 0;
	for(new i = 0; i <= MAX_VEHICLES; i++){
		if(IsValidVehicle(i)) count += 1;
	}
	return count;
}

stock DestroyVehicles(){
	for(new i = 0; i <= MAX_VEHICLES; i++){
		if(IsValidVehicle(i)) DestroyVehicle(i);
	}
}

stock GangZoneDestroyAll(){
	for(new i = 0; i <= MAX_GANG_ZONES; i++){
		GangZoneDestroy(i);
	}
}

stock CountPlayerObjects(playerid,bool:streamer = false){
	new count = 0;
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(streamer){
			if(IsValidPlayerObject(playerid,i)){
				count += 1;
			}
		} else {
			if(Streamer_GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID){
				if(IsValidPlayerObject(playerid,i)){
					count += 1;
				}
			}
		}
	}
	return count;
}

stock DestroyPlayerObjects(playerid,bool:streamer = false){
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(streamer){
			if(IsValidPlayerObject(playerid,i)){
				DestroyPlayerObject(playerid,i);
			}
		} else {
			if(Streamer_GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID){
				if(IsValidPlayerObject(playerid,i)){
					DestroyPlayerObject(playerid,i);
				}
			}
		}
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
	new Float:piox,Float:pioy,Float:pioz,pioVW,pioINT;
	ForDynamicObjects(i){
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
	new Float:piox,Float:pioy,Float:pioz,pioVW,pioINT;
	ForDynamicObjects(i){
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
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				DestroyDynamicObject(i);
			}
		}
	}
}

stock DeattachVehicleDynamicObject(vehicleid){
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE,INVALID_VEHICLE_ID);
			}
		}
	}
}

stock DeattachPlayerDynamicObject(playerid){
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER) == playerid){
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER,INVALID_PLAYER_ID);
			}
		}
	}
}

stock DestroyPlayerDynamicObject(playerid){
	ForDynamicObjects(i){
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

stock GetDynamicRaceCPNext(checkpointid,&Float:nextx,&Float:nexty,&Float:nextz){
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_X,nextx);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Y,nexty);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Z,nextz);
}

stock SetDynamicRaceCPNext(checkpointid,Float:nextx,Float:nexty,Float:nextz){
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_X,nextx);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Y,nexty);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Z,nextz);
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

stock GetDynamicCirclePos(areaid,&Float:x,&Float:y){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
}

stock SetDynamicCirclePos(areaid,Float:x,Float:y){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
}

stock GetDynamicCylinderPos(areaid,&Float:x,&Float:y,&Float:minz,&Float:maxz){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock SetDynamicCylinderPos(areaid,Float:x,Float:y,Float:minz,Float:maxz){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock GetDynamicSpherePos(areaid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Z,z);
}

stock SetDynamicSpherePos(areaid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Z,z);
}

stock GetDynamicCubePos(areaid,&Float:minx,&Float:miny,&Float:minz,&Float:maxx,&Float:maxy,&Float:maxz){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock SetDynamicCubePos(areaid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock GetDynamicRectanglePos(areaid,&Float:minx,&Float:miny,&Float:maxx,&Float:maxy){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
}

stock SetDynamicRectanglePos(areaid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
}

stock DestroyDynamicObjectComponent(objectid,type){
	new max_dobj = Streamer_GetUpperBound(type);
	for(new i = 1; i < max_dobj; i++){
		if(Streamer_GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == objectid){
			switch(type){
				case STREAMER_TYPE_OBJECT:	if(IsValidDynamicObject(i)) DestroyDynamicObject(i);
				case STREAMER_TYPE_AREA:	if(IsValidDynamicArea(i)) DestroyDynamicArea(i);
				default: print("[ADM] Warring: Invalid Object Component type.");
			}
		}
	}
}

stock DeattachDynamicObjectComponent(objectid,type){
	new max_dobj = Streamer_GetUpperBound(type);
	for(new i = 1; i < max_dobj; i++){
		if(Streamer_GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == objectid){
			switch(type){
				case STREAMER_TYPE_OBJECT:	Streamer_SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_STREAMER_ID);
				case STREAMER_TYPE_AREA:	Streamer_SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_VEHICLE_ID);
				default: print("[ADM] Warring: Invalid Object Component type.");
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

stock UpdateAllDynamicObjects(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_OBJECT);
	}
}

stock UpdateAllDynamicPickups(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_PICKUP);
	}
}

stock UpdateAllDynamicCPs(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_CP);
	}
}

stock UpdateAllDynamicRaceCPs(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_RACE_CP);
	}
}

stock UpdateAllDynamicMapIcons(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_MAP_ICON);
	}
}

stock UpdateAllDynamic3DTextLabels(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_3D_TEXT_LABEL);
	}
}

stock UpdateAllDynamicAreas(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i, STREAMER_TYPE_AREA);
	}
}

stock UpdateAllDynamicElements(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i);
	}
}

stock ResetDynamicObjectMaterial(objectid,materialindex){
	SetDynamicObjectMaterial(objectid,materialindex,-1,"none","none",0);
	SetDynamicObjectModel(objectid,GetDynamicObjectModel(objectid));
}

stock ResetDynamicObjectMaterialAll(objectid){
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialUsed(objectid,i)){
			SetDynamicObjectMaterial(objectid,i,-1,"none","none",0);
		}
	}
	SetDynamicObjectModel(objectid,GetDynamicObjectModel(objectid));
}


#define GetDynamicCuboidPos 					GetDynamicCubePos
#define SetDynamicCuboidPos						SetDynamicCubePos


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
	
	//AttachDynamicObjectToObject
	stock AC_AttachDynamicObjectToObject(objectid,attachtoid,Float:offsetx,Float:offsety,Float:offsetz,Float:rx,Float:ry,Float:rz,syncrotation = 1){
		new dobj = AttachDynamicObjectToObject(objectid,attachtoid,offsetx,offsety,offsetz,rx,ry,rz,syncrotation);
		if(GetDynamicObjectPriority(attachtoid) <= GetDynamicObjectPriority(objectid)){
			SetDynamicObjectPriority(attachtoid,GetDynamicObjectPriority(objectid)+1);
		}
		return dobj;
	}

	#if defined _LS_AttachDynamicObjectToObject
		#undef AttachDynamicObjectToObject
	#else
		#define _LS_AttachDynamicObjectToObject
	#endif
	#define AttachDynamicObjectToObject AC_AttachDynamicObjectToObject

#endif



//DynamicAntiArea Hook
forward OnPlayerEnterAntiArea(playerid,areaid);
forward OnPlayerLeaveAntiArea(playerid,areaid);

public OnPlayerEnterDynamicArea(playerid,areaid){
	CallLocalFunction("OnPlayerLeaveAntiArea","dd",playerid,areaid);
	#if defined SSpec_OnPlayerEnterDynamicArea
		SSpec_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea SSpec_OnPlayerEnterDynamicArea
#if defined SSpec_OnPlayerEnterDynamicArea
	forward SSpec_OnPlayerEnterDynamicArea(playerid,areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid,areaid){
	CallLocalFunction("OnPlayerEnterAntiArea","dd",playerid,areaid);
	#if defined SSpec_OnPlayerLeaveDynamicArea
		SSpec_OnPlayerLeaveDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea SSpec_OnPlayerLeaveDynamicArea
#if defined SSpec_OnPlayerLeaveDynamicArea
	forward SSpec_OnPlayerLeaveDynamicArea(playerid,areaid);
#endif

stock CheckStreamerVersion(){
	if(!IsValidStreamer(GetValidStreamerVersion())){
		new str1[32], str2[32];
		GetStreamerVersionName(str1,GetStreamerVersion());
		GetStreamerVersionName(str2,GetValidStreamerVersion());
		printf("[ADM] Warring: Your Streamer %s It is not compatible with this version Streamer Functions, update your streamer to %s",str1,str2);
	}
}

//Hook Init
public OnFilterScriptInit(){
	CheckStreamerVersion();
	#if defined SSpec_OnFilterScriptInit
		SSpec_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SSpec_OnFilterScriptInit
#if defined SSpec_OnFilterScriptInit
	forward SSpec_OnFilterScriptInit();
#endif

public OnGameModeInit(){
	CheckStreamerVersion();
	#if defined SSpec_OnGameModeInit
		SSpec_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SSpec_OnGameModeInit
#if defined SSpec_OnGameModeInit
	forward SSpec_OnGameModeInit();
#endif

//EOF
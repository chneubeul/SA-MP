/*******************************************************************************************************************************************
 *                                                                                                                                         *
 *                                                       )(   Streamer Functions   )(                                                      *
 *                                                                                                                                         *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                                     *
 *                                                                                                                                         *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                                  *
 * Publication: http://forum.sa-mp.com/showthread.php?t=590918                                                                             *
 *                                                                                                                                         *
 * Plugins: Streamer                                                                                                                       *
 * Modules: None                                                                                                                           *
 *                                                                                                                                         *
 * File Version: 2.5.7                                                                                                                     *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                                                          *
 * Streamer Version: 2.8.2                                                                                                                 *
 *                                                                                                                                         *
 * Compiler Options:                                                                                                                       *
 * DISABLE_STREAMER_SPEC_CHECK  //Turn off check streamer version                                                                          *
 * ENABLE_BULLET_DYNAMIC_OBJECT //Turn on call OnPlayerWeaponShot when we shoot in a dynamic object                                        *
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
 * GetDynamicObjectMoveTime(objectid,&objstate,&rtime=0);                                                                                  *
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
 * GetDynamicObjectDatagram(objectid,data[]);                                                                                              *
 * SetDynamicObjectDatagram(objectid,data[]);                                                                                              *
 * RemoveDynamicObjectDatagram(objectid,data[]);                                                                                           *
 * bool:IsSetDynamicObjectDatagram(objectid);                                                                                              *
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
 * bool:IsPointInArea(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                          *
 * bool:IsPointInAreaEx(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,vw1,int1,vw2,int2);      *
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
 * GetDynamicCPDatagram(checkpointid,data[]);                                                                                              *
 * SetDynamicCPDatagram(checkpointid,data[]);                                                                                              *
 * RemoveDynamicCPDatagram(checkpointid,data[]);                                                                                           *
 * bool:IsSetDynamicCPDatagram(checkpointid);                                                                                              *
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
 * GetDynamicRaceCPDatagram(checkpointid,data[]);                                                                                          *
 * SetDynamicRaceCPDatagram(checkpointid,data[]);                                                                                          *
 * RemoveDynamicRaceCPDatagram(checkpointid,data[]);                                                                                       *
 * bool:IsSetDynamicRaceCPDatagram(checkpointid);                                                                                          *
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
 * GetDynamicMapIconDatagram(iconid,data[]);                                                                                               *
 * SetDynamicMapIconDatagram(iconid,data[]);                                                                                               *
 * RemoveDynamicMapIconDatagram(iconid,data[]);                                                                                            *
 * bool:IsSetDynamicMapIconDatagram(iconid);                                                                                               *
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
 * GetDynamicPickupDatagram(pickupid,data[]);                                                                                              *
 * SetDynamicPickupDatagram(pickupid,data[]);                                                                                              *
 * RemoveDynamicPickupDatagram(pickupid,data[]);                                                                                           *
 * bool:IsSetDynamicPickupDatagram(pickupid);                                                                                              *
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
 * GetDynamic3DTextDatagram(Text3D:id,data[]);                                                                                             *
 * SetDynamic3DTextDatagram(Text3D:id,data[]);                                                                                             *
 * RemoveDynamic3DTextDatagram(Text3D:id,data[]);                                                                                          *
 * bool:IsSetDynamic3DTextDatagram(Text3D:id);                                                                                             *
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
 * GetDynamicAreaDatagram(areaid,data[]);                                                                                                  *
 * SetDynamicAreaDatagram(areaid,data[]);                                                                                                  *
 * RemoveDynamicAreaDatagram(areaid,data[]);                                                                                               *
 * bool:IsSetDynamicAreaDatagram(areaid);                                                                                                  *
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
 * Nearest Item Functions:                                                                                                                 *
 * GetNearestVisibleItem(playerid,type);                                                                                                   *
 * GetNearestVisibleObject(playerid);                                                                                                      *
 * GetNearestVisiblePickup(playerid);                                                                                                      *
 * GetNearestVisibleCP(playerid);                                                                                                          *
 * GetNearestVisibleRaceCP(playerid);                                                                                                      *
 * GetNearestVisibleMapIcon(playerid);                                                                                                     *
 * GetNearestVisible3DText(playerid);                                                                                                      *
 * GetNearestVisibleArea(playerid);                                                                                                        *
 *                                                                                                                                         *
 * Extended Functions:                                                                                                                     *
 * bool:IsValidStreamer(version);                                                                                                          *
 * GetStreamerVersion();                                                                                                                   *
 * GetValidStreamerVersion();                                                                                                              *
 * GetStreamerVersionName(name[], value = GET_STREAMER_VERSION, maxdest = sizeof name);                                                    *
 * CheckStreamerVersion();                                                                                                                 *
 * GetStreamDatagram(type,id,data[]);                                                                                                      *
 * SetStreamDatagram(type,id,data[]);                                                                                                      *
 * RemoveStreamDatagram(type,id);                                                                                                          *
 * bool:IsSetStreamDatagram(type,id);                                                                                                      *
 * GetStreamerSpecActiveCount();                                                                                                           *
 *                                                                                                                                         *
 * Definitions:                                                                                                                            *
 * INVALID_DYNAMIC_OBJECT_ID                                                                                                               *
 * INVALID_DYNAMIC_PICKUP_ID                                                                                                               *
 * INVALID_DYNAMIC_CP_ID                                                                                                                   *
 * INVALID_DYNAMIC_RACE_CP_ID                                                                                                              *
 * INVALID_DYNAMIC_MAP_ICON_ID                                                                                                             *
 * INVALID_DYNAMIC_3D_TEXT_ID                                                                                                              *
 * INVALID_DYNAMIC_AREA_ID                                                                                                                 *
 * INVALID_PICKUP_ID                                                                                                                       *
 * MAX_STREAM_SIZE                                                                                                                         *
 * INVALID_STREAMER_COMPONENT                                                                                                              *
 *                                                                                                                                         *
 * Fixes:                                                                                                                                  *
 * DestroyDynamicObject         -> Resets the variable after the destruction of the DynamicObject.                                         *
 * DestroyDynamicPickup         -> Resets the variable after the destruction of the DynamicPickup.                                         *
 * DestroyDynamicCP             -> Resets the variable after the destruction of the DynamicCP.                                             *
 * DestroyDynamicRaceCP         -> Resets the variable after the destruction of the DynamicRaceCP.                                         *
 * DestroyDynamicMapIcon        -> Resets the variable after the destruction of the DynamicMapIcon.                                        *
 * DestroyDynamic3DTextLabel    -> Resets the variable after the destruction of the Dynamic3DTextLabel.                                    *
 * DestroyDynamicArea           -> Resets the variable after the destruction of the DynamicArea.                                           *
 * DestroyObject                -> Resets the variable after the destruction of the Object.                                                *
 * DestroyPlayerObject          -> Resets the variable after the destruction of the PlayerObject.                                          *
 * DestroyPickup                -> Resets the variable after the destruction of the Pickup.                                                *
 * Delete3DTextLabel            -> Resets the variable after the destruction of the 3DTextLabel.                                           *
 * DeletePlayer3DTextLabel      -> Resets the variable after the destruction of the Player3DTextLabel.                                     *
 * AttachDynamicObjectToObject  -> Changes the priority of the parent to be greater than the priority of sub-objects.                      *
 *                                                                                                                                         *
 *******************************************************************************************************************************************/

/*
//Check Version StreamerFunction.inc
#if !defined _streamer_spec
	#error [ADM] You need StreamerFunction.inc v2.5.7
#elseif !defined Streamer_Spec_Version
	#error [ADM] Update you StreamerFunction.inc to v2.5.7
#elseif (Streamer_Spec_Version < 20507)
	#error [ADM] Update you StreamerFunction.inc to v2.5.7
#endif
*/

#if defined _streamer_spec
	#endinput
#endif
#define _streamer_spec

#if (!defined GetPlayerPoolSize)
	#error [ADM] This include requires SA:MP version 0.3.7
#endif

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

#define Streamer_Spec_Version 					(20507) //a.b.c 10000*a+100*b+c
#define Streamer_Spec_SAMP_Version				"0.3.7"
#define Valid_Streamer_Version 					(0x282001)

#if !defined INVALID_STREAMER_ID
	#define INVALID_STREAMER_ID 0
#endif

#if defined INVALID_DYNAMIC_OBJECT_ID
	#if (INVALID_DYNAMIC_OBJECT_ID != INVALID_STREAMER_ID)
		#error [ADM] Invalid DestroyDynamicObject Hook version. Invalid definition INVALID_DYNAMIC_OBJECT_ID
	#endif
	#undef INVALID_DYNAMIC_OBJECT_ID
#endif
#define INVALID_DYNAMIC_OBJECT_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_PICKUP_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_CP_ID					INVALID_STREAMER_ID
#define INVALID_DYNAMIC_RACE_CP_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_MAP_ICON_ID				INVALID_STREAMER_ID
#define INVALID_DYNAMIC_3D_TEXT_ID				Text3D:INVALID_STREAMER_ID
#define INVALID_DYNAMIC_AREA_ID					INVALID_STREAMER_ID

#if !defined INVALID_PICKUP_ID
	#define INVALID_PICKUP_ID					-1
#endif

#if !defined MAX_STREAM_SIZE
	#define MAX_STREAM_SIZE						256
#endif

#if !defined INVALID_STREAMER_COMPONENT
	#define INVALID_STREAMER_COMPONENT			-1
#endif

#define StreamerSpecProt::						stock

#if !defined isnull
	#define isnull(%1) 							((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define GET_STREAMER_VERSION					(0xFFFFFFFF)

#define MOVE_OBJECT_STATE_STOP					(0)
#define MOVE_OBJECT_STATE_MOVED					(1)
#define MOVE_OBJECT_STATE_INVALID				(2)

#define BULLET_HIT_TYPE_DYNAMIC_OBJECT			(15)

#define GetStreamerVersion()					(Streamer_IncludeFileVersion)
#define GetValidStreamerVersion()				(Valid_Streamer_Version)

//Global
#define GetStreamDatagram(%0,%1,%2)				GetSVarString("Stream:"#%0":"#%1"",(%2),MAX_STREAM_SIZE)
#define SetStreamDatagram(%0,%1,%2)				SetSVarString("Stream:"#%0":"#%1"",(%2))
#define RemoveStreamDatagram(%0,%1) 			DeleteSVar("Stream:"#%0":"#%1"")

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
#define GetDynamicObjectDatagram(%1,%2)			GetStreamDatagram(STREAMER_TYPE_OBJECT,(%1),(%2))
#define SetDynamicObjectDatagram(%1,%2)			SetStreamDatagram(STREAMER_TYPE_OBJECT,(%1),(%2))
#define RemoveDynamicObjectDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_OBJECT,(%1))
#define IsSetDynamicObjectDatagram(%1)			IsSetStreamDatagram(STREAMER_TYPE_OBJECT,(%1))

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
#define GetDynamicPickupDatagram(%1,%2)			GetStreamDatagram(STREAMER_TYPE_PICKUP,(%1),(%2))
#define SetDynamicPickupDatagram(%1,%2)			SetStreamDatagram(STREAMER_TYPE_PICKUP,(%1),(%2))
#define RemoveDynamicPickupDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_PICKUP,(%1))
#define IsSetDynamicPickupDatagram(%1)			IsSetStreamDatagram(STREAMER_TYPE_PICKUP,(%1))

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
#define GetDynamicCPDatagram(%1,%2)				GetStreamDatagram(STREAMER_TYPE_CP,(%1),(%2))
#define SetDynamicCPDatagram(%1,%2)				SetStreamDatagram(STREAMER_TYPE_CP,(%1),(%2))
#define RemoveDynamicCPDatagram(%1)				RemoveStreamDatagram(STREAMER_TYPE_CP,(%1))
#define IsSetDynamicCPDatagram(%1)				IsSetStreamDatagram(STREAMER_TYPE_CP,(%1))

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
#define GetDynamicRaceCPDatagram(%1,%2)			GetStreamDatagram(STREAMER_TYPE_RACE_CP,(%1),(%2))
#define SetDynamicRaceCPDatagram(%1,%2)			SetStreamDatagram(STREAMER_TYPE_RACE_CP,(%1),(%2))
#define RemoveDynamicRaceCPDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_RACE_CP,(%1))
#define IsSetDynamicRaceCPDatagram(%1)			IsSetStreamDatagram(STREAMER_TYPE_RACE_CP,(%1))

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
#define GetDynamicMapIconDatagram(%1,%2)		GetStreamDatagram(STREAMER_TYPE_MAP_ICON,(%1),(%2))
#define SetDynamicMapIconDatagram(%1,%2)		SetStreamDatagram(STREAMER_TYPE_MAP_ICON,(%1),(%2))
#define RemoveDynamicMapIconDatagram(%1)		RemoveStreamDatagram(STREAMER_TYPE_MAP_ICON,(%1))
#define IsSetDynamicMapIconDatagram(%1)			IsSetStreamDatagram(STREAMER_TYPE_MAP_ICON,(%1))

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
#define GetDynamic3DTextDatagram(%1,%2)			GetStreamDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1),(%2))
#define SetDynamic3DTextDatagram(%1,%2)			SetStreamDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1),(%2))
#define RemoveDynamic3DTextDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1))
#define IsSetDynamic3DTextDatagram(%1)			IsSetStreamDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1))

//DynamicArea
#define GetDynamicAreaVW(%1)					Streamer_GetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicAreaVW(%1,%2)					Streamer_SetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicAreaINT(%1)					Streamer_GetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicAreaINT(%1,%2)				Streamer_SetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicAreaSize(%1,%2)				Streamer_GetFloatData(STREAMER_TYPE_AREA,(%1),E_STREAMER_SIZE,(%2))
#define SetDynamicAreaSize(%1,%2)				Streamer_SetFloatData(STREAMER_TYPE_AREA,(%1),E_STREAMER_SIZE,(%2))
#define GetDynamicAreaDatagram(%1,%2)			GetStreamDatagram(STREAMER_TYPE_AREA,(%1),(%2))
#define SetDynamicAreaDatagram(%1,%2)			SetStreamDatagram(STREAMER_TYPE_AREA,(%1),(%2))
#define RemoveDynamicAreaDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_AREA,(%1))
#define IsSetDynamicAreaDatagram(%1)			IsSetStreamDatagram(STREAMER_TYPE_AREA,(%1))

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

//GetNearestVisibleItem
#define GetNearestVisibleObject(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_OBJECT)
#define GetNearestVisiblePickup(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_PICKUP)
#define GetNearestVisibleCP(%0)					GetNearestVisibleItem((%0),STREAMER_TYPE_CP)
#define GetNearestVisibleRaceCP(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_RACE_CP)
#define GetNearestVisibleMapIcon(%0)			GetNearestVisibleItem((%0),STREAMER_TYPE_MAP_ICON)
#define GetNearestVisible3DText(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_3D_TEXT_LABEL)
#define GetNearestVisibleArea(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_AREA)

#define GetStreamerSpecActiveCount() 			GetSVarInt("ADM:StreamerSpec:ACTIVE")

StreamerSpecProt:: bool:IsValidStreamer(version){
	if(GetStreamerVersion() < version) return false;
	return true;
}

StreamerSpecProt:: GetStreamerVersionName(name[], value = GET_STREAMER_VERSION, maxdest = sizeof name){
	if(value == GET_STREAMER_VERSION) value = GetStreamerVersion();
	new ver_str[10];
	format(ver_str,sizeof(ver_str),"%06x",value);
	format(name,maxdest,"%d.%d.%dr%d",(ver_str[0]-48),(ver_str[1]-48),(ver_str[2]-48),(((ver_str[3]-48)*100) + ((ver_str[4]-48)*10) + (ver_str[5]-48)));
}

StreamerSpecProt:: SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	SetDynamicObjectPos(objectid,x,y,z);
	SetDynamicObjectRot(objectid,rx,ry,rz);
}

StreamerSpecProt:: GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	GetDynamicObjectPos(objectid,x,y,z);
	GetDynamicObjectRot(objectid,rx,ry,rz);
}

StreamerSpecProt:: SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	SetObjectPos(objectid,x,y,z);
	SetObjectRot(objectid,rx,ry,rz);
}

StreamerSpecProt:: GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	GetObjectPos(objectid,x,y,z);
	GetObjectRot(objectid,rx,ry,rz);
}

StreamerSpecProt:: CountObjects(){
	new count = 0;
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(IsValidObject(i)) count++;
	}
	return count;
}

StreamerSpecProt:: DestroyObjects(){
	new count = 0;
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(IsValidObject(i)){
			DestroyObject(i);
			count++;
		}
	}
	return count;
}

StreamerSpecProt:: CountVehicles(){
	new count = 0;
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		if(IsValidVehicle(i)) count++;
	}
	return count;
}

StreamerSpecProt:: DestroyVehicles(){
	new count = 0;
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		if(IsValidVehicle(i)){
			DestroyVehicle(i);
			count++;
		}
	}
	return count;
}

StreamerSpecProt:: GangZoneDestroyAll(){
	for(new i = 0; i <= MAX_GANG_ZONES; i++){
		GangZoneDestroy(i);
	}
}

StreamerSpecProt:: CountPlayerObjects(playerid,bool:streamer = false){
	new count = 0;
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(streamer){
			if(IsValidPlayerObject(playerid,i)){
				count++;
			}
		} else {
			if(Streamer_GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID){
				if(IsValidPlayerObject(playerid,i)){
					count++;
				}
			}
		}
	}
	return count;
}

StreamerSpecProt:: DestroyPlayerObjects(playerid,bool:streamer = false){
	new count = 0;
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(streamer){
			if(IsValidPlayerObject(playerid,i)){
				DestroyPlayerObject(playerid,i);
				count++;
			}
		} else {
			if(Streamer_GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID){
				if(IsValidPlayerObject(playerid,i)){
					DestroyPlayerObject(playerid,i);
					count++;
				}
			}
		}
	}
	return count;
}

StreamerSpecProt:: RebuildDynamicObject(objectid,modelid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,worldid = -1,interiorid = -1,playerid = -1,Float:streamdistance = STREAMER_OBJECT_SD,Float:drawdistance = STREAMER_OBJECT_DD,areaid = -1,priority = 0){
	if(!IsValidDynamicObject(objectid)) return 0;
	if(IsDynamicObjectMoving(objectid)) StopDynamicObject(objectid);
	SetDynamicObjectPosAndRot(objectid,x,y,z,rx,ry,rz);
	SetDynamicObjectModel(objectid,modelid);
	SetDynamicObjectVW(objectid,worldid);
	SetDynamicObjectINT(objectid,interiorid);
	SetDynamicObjectSD(objectid,streamdistance);
	SetDynamicObjectDD(objectid,drawdistance);
	SetDynamicObjectArea(objectid,areaid);
	SetDynamicObjectPriority(objectid,priority);
	return 1;
}

StreamerSpecProt:: bool:IsPointInArea(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy) && (z >= minz && z <= maxz)) return true;
	return false;
}

StreamerSpecProt:: bool:IsPointInAreaEx(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,vw1 = -1,int1 = -1,vw2 = -1,int2 = -1){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy) && (z >= minz && z <= maxz) && (vw1 == vw2) && (int1 == int2)) return true;
	return false;
}

StreamerSpecProt:: DestroyDynamicObjectsInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1){
	new count = 0,Float:piox,Float:pioy,Float:pioz,pioVW,pioINT;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			GetDynamicObjectPos(i,piox,pioy,pioz);
			pioVW = GetDynamicObjectVW(i);
			pioINT = GetDynamicObjectINT(i);
			if(IsPointInArea(piox,pioy,pioz,minx,miny,minz,maxx,maxy,maxz)){
				if(((worldid == pioVW) || (worldid == -1)) && (interiorid == pioINT) || (interiorid == -1)){
					if(IsDynamicObjectMoving(i)) StopDynamicObject(i);
					DestroyDynamicObject(i);
					count++;
				}
			}
		}
	}
	return count;
}

StreamerSpecProt:: DestroyDynamicObjectsInCubeFM(modelid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,worldid = -1,interiorid = -1){
	new count = 0,Float:piox,Float:pioy,Float:pioz,pioVW,pioINT;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			GetDynamicObjectPos(i,piox,pioy,pioz);
			pioVW = GetDynamicObjectVW(i);
			pioINT = GetDynamicObjectINT(i);
			if(IsPointInArea(piox,pioy,pioz,minx,miny,minz,maxx,maxy,maxz)){
				if(((worldid == pioVW) || (worldid == -1)) && ((interiorid == pioINT) || (interiorid == -1)) && (modelid == GetDynamicObjectModel(i))){
					if(IsDynamicObjectMoving(i)) StopDynamicObject(i);
					DestroyDynamicObject(i);
					count++;
				}
			}
		}
	}
	return count;
}

StreamerSpecProt:: DestroyVehicleDynamicObject(vehicleid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				DestroyDynamicObject(i);
				count++;
			}
		}
	}
	return count;
}

StreamerSpecProt:: DeattachVehicleDynamicObject(vehicleid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE,INVALID_VEHICLE_ID);
				count++;
			}
		}
	}
	return count;
}

StreamerSpecProt:: DeattachPlayerDynamicObject(playerid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER) == playerid){
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER,INVALID_PLAYER_ID);
				count++;
			}
		}
	}
	return count;
}

StreamerSpecProt:: DestroyPlayerDynamicObject(playerid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER) == playerid){
				DestroyDynamicObject(i);
				count++;
			}
		}
	}
	return count;
}

StreamerSpecProt:: GetDynamicCPPos(checkpointid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Z,z);
}

StreamerSpecProt:: SetDynamicCPPos(checkpointid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_CP,checkpointid,E_STREAMER_Z,z);
}

StreamerSpecProt:: GetDynamicRaceCPPos(checkpointid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Z,z);
}

StreamerSpecProt:: SetDynamicRaceCPPos(checkpointid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_Z,z);
}

StreamerSpecProt:: GetDynamicRaceCPNext(checkpointid,&Float:nextx,&Float:nexty,&Float:nextz){
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_X,nextx);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Y,nexty);
	Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Z,nextz);
}

StreamerSpecProt:: SetDynamicRaceCPNext(checkpointid,Float:nextx,Float:nexty,Float:nextz){
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_X,nextx);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Y,nexty);
	Streamer_SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Z,nextz);
}

StreamerSpecProt:: GetDynamicObjectMovePos(objectid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Z,z);
}

StreamerSpecProt:: GetDynamicObjectMoveRot(objectid,&Float:rx,&Float:ry,&Float:rz){
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_X,rx);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Y,ry);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Z,rz);
}

StreamerSpecProt:: SetDynamicObjectMovePos(objectid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Z,z);
}

StreamerSpecProt:: SetDynamicObjectMoveRot(objectid,Float:rx = -1000.0,Float:ry = -1000.0,Float:rz = -1000.0){
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_X,rx);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Y,ry);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Z,rz);
}

StreamerSpecProt:: GetDynamicPickupPos(pickupid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Z,z);
}

StreamerSpecProt:: SetDynamicPickupPos(pickupid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Z,z);
}

StreamerSpecProt:: GetDynamicMapIconPos(iconid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Z,z);
}

StreamerSpecProt:: SetDynamicMapIconPos(iconid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Z,z);
}

StreamerSpecProt:: GetDynamic3DTextPos(Text3D:id,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Z,z);
}

StreamerSpecProt:: SetDynamic3DTextPos(Text3D:id,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Z,z);
}

StreamerSpecProt:: GetDynamicCirclePos(areaid,&Float:x,&Float:y){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
}

StreamerSpecProt:: SetDynamicCirclePos(areaid,Float:x,Float:y){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
}

StreamerSpecProt:: GetDynamicCylinderPos(areaid,&Float:x,&Float:y,&Float:minz,&Float:maxz){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

StreamerSpecProt:: SetDynamicCylinderPos(areaid,Float:x,Float:y,Float:minz,Float:maxz){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

StreamerSpecProt:: GetDynamicSpherePos(areaid,&Float:x,&Float:y,&Float:z){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Z,z);
}

StreamerSpecProt:: SetDynamicSpherePos(areaid,Float:x,Float:y,Float:z){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Z,z);
}

StreamerSpecProt:: GetDynamicCubePos(areaid,&Float:minx,&Float:miny,&Float:minz,&Float:maxx,&Float:maxy,&Float:maxz){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

StreamerSpecProt:: SetDynamicCubePos(areaid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

StreamerSpecProt:: GetDynamicRectanglePos(areaid,&Float:minx,&Float:miny,&Float:maxx,&Float:maxy){
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
}

StreamerSpecProt:: SetDynamicRectanglePos(areaid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
}

StreamerSpecProt:: DestroyDynamicObjectComponent(objectid,type){
	new count = 0, max_dobj = Streamer_GetUpperBound(type);
	for(new i = 1; i < max_dobj; i++){
		if((IsValidDynamicObject(i) && type == STREAMER_TYPE_OBJECT) || (IsValidDynamicArea(i) && type == STREAMER_TYPE_AREA)){
			if(Streamer_GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == objectid){
				switch(type){
					case STREAMER_TYPE_OBJECT: {
						DestroyDynamicObject(i);
						count++;
					}
					case STREAMER_TYPE_AREA: {
						DestroyDynamicArea(i);
						count++;
					}
					default: return INVALID_STREAMER_COMPONENT;
				}
			}
		}
	}
	return count;
}

StreamerSpecProt:: DeattachDynamicObjectComponent(objectid,type){
	new count = 0, max_dobj = Streamer_GetUpperBound(type);
	for(new i = 1; i < max_dobj; i++){
		if((IsValidDynamicObject(i) && type == STREAMER_TYPE_OBJECT) || (IsValidDynamicArea(i) && type == STREAMER_TYPE_AREA)){
			if(Streamer_GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == objectid){
				switch(type){
					case STREAMER_TYPE_OBJECT: {
						Streamer_SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_STREAMER_ID);
						count++;
					}
					case STREAMER_TYPE_AREA: {
						Streamer_SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_VEHICLE_ID);
						count++;
					}
					default: return INVALID_STREAMER_COMPONENT;
				}
			}
		}
	}
	return count;
}

StreamerSpecProt:: GetDynamicObjectMoveTime(objectid,&objstate,&rtime=0){
	if(!IsValidDynamicObject(objectid)){
		objstate = MOVE_OBJECT_STATE_INVALID;
		rtime = 0;
		return rtime;
	} else if(IsDynamicObjectMoving(objectid)){
		new Float:piox,Float:pioy,Float:pioz,Float:piotx,Float:pioty,Float:piotz,Float:dist,Float:objspeed;
		GetDynamicObjectPos(objectid,piox,pioy,pioz);
		GetDynamicObjectMovePos(objectid,piotx,pioty,piotz);
		GetDynamicObjectMoveSpeed(objectid,objspeed);
		dist = VectorSize(piox-piotx,pioy-pioty,pioz-piotz);
		rtime = floatround((dist/objspeed)*1000.0);
		objstate = MOVE_OBJECT_STATE_MOVED;
		return rtime;
	} else {
		objstate = MOVE_OBJECT_STATE_STOP;
		rtime = 0;
		return rtime;
	}
	return rtime;
}

StreamerSpecProt:: UpdateAllDynamicObjects(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_OBJECT);
	}
}

StreamerSpecProt:: UpdateAllDynamicPickups(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_PICKUP);
	}
}

StreamerSpecProt:: UpdateAllDynamicCPs(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_CP);
	}
}

StreamerSpecProt:: UpdateAllDynamicRaceCPs(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_RACE_CP);
	}
}

StreamerSpecProt:: UpdateAllDynamicMapIcons(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_MAP_ICON);
	}
}

StreamerSpecProt:: UpdateAllDynamic3DTextLabels(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_3D_TEXT_LABEL);
	}
}

StreamerSpecProt:: UpdateAllDynamicAreas(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i,STREAMER_TYPE_AREA);
	}
}

StreamerSpecProt:: UpdateAllDynamicElements(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		Streamer_Update(i);
	}
}

StreamerSpecProt:: ResetDynamicObjectMaterial(objectid,materialindex){
	SetDynamicObjectMaterial(objectid,materialindex,0,"","",0);
	SetDynamicObjectModel(objectid,GetDynamicObjectModel(objectid));
}

StreamerSpecProt:: ResetDynamicObjectMaterialAll(objectid){
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialUsed(objectid,i)){
			SetDynamicObjectMaterial(objectid,i,0,"","",0);
		}
	}
	SetDynamicObjectModel(objectid,GetDynamicObjectModel(objectid));
}

StreamerSpecProt:: CheckStreamerVersion(){
	if(!IsValidStreamer(GetValidStreamerVersion())){
		new str1[32], str2[32];
		GetStreamerVersionName(str1,GetStreamerVersion());
		GetStreamerVersionName(str2,GetValidStreamerVersion());
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Your Streamer %s It is not compatible with this version Streamer Functions, update your Streamer to %s",str1,str2);
		}
	}
}

StreamerSpecProt:: bool:IsSetStreamDatagram(type,id){
	new stream_data[MAX_STREAM_SIZE];
	GetStreamDatagram(type,id,stream_data);
	if(isnull(stream_data)) return false;
	return true;
}

StreamerSpecProt:: GetNearestVisibleItem(playerid,type){
	new Float:x, Float:y, Float:z, max_element, tmp_item, itemid = INVALID_STREAMER_ID,
		Float:min_radius = 20000.0, Float:distance, idx_max = 0, idx = 0;
	
	GetPlayerPos(playerid,x,y,z);
	idx_max = Streamer_CountVisibleItems(playerid,type,1);
	switch(type){
		case STREAMER_TYPE_OBJECT, STREAMER_TYPE_PICKUP, STREAMER_TYPE_MAP_ICON, STREAMER_TYPE_3D_TEXT_LABEL: {
			max_element = Streamer_GetVisibleItems(type,playerid);
			while(idx <= max_element && idx_max > 0){
				if((tmp_item = Streamer_GetItemStreamerID(playerid,type,idx)) != INVALID_STREAMER_ID){
					idx_max--;
					Streamer_GetDistanceToItem(x,y,z,type,tmp_item,distance,3);
					if(distance < min_radius){
						itemid = tmp_item;
						min_radius = distance;
					}
				}
				idx++;
			}
		}

		case STREAMER_TYPE_CP: {
			max_element = GetDynamicCPPoolSize(), idx = 1;
			while(idx <= max_element && idx_max > 0){
				if(IsValidDynamicCP(idx)){
					if(Streamer_IsItemVisible(playerid,type,i)){
						idx_max--;
						Streamer_GetDistanceToItem(x,y,z,type,tmp_item,distance,3);
						if(distance < min_radius){
							itemid = tmp_item;
							min_radius = distance;
						}
					}
				}
				idx++;
			}
		}
		
		case STREAMER_TYPE_RACE_CP: {
			max_element = GetDynamicRaceCPPoolSize(), idx = 1;
			while(idx <= max_element && idx_max > 0){
				if(IsValidDynamicRaceCP(idx)){
					if(Streamer_IsItemVisible(playerid,type,i)){
						idx_max--;
						Streamer_GetDistanceToItem(x,y,z,type,tmp_item,distance,3);
						if(distance < min_radius){
							itemid = tmp_item;
							min_radius = distance;
						}
					}
				}
				idx++;
			}
		}
		
		case STREAMER_TYPE_AREA: {
			max_element = GetDynamicAreaPoolSize(), idx = 1;
			while(idx <= max_element && idx_max > 0){
				if(IsValidDynamicArea(idx)){
					if(Streamer_IsItemVisible(playerid,type,i)){
						idx_max--;
						Streamer_GetDistanceToItem(x,y,z,type,tmp_item,distance,3);
						if(distance < min_radius){
							itemid = tmp_item;
							min_radius = distance;
						}
					}
				}
				idx++;
			}
		}
		
		default: return INVALID_STREAMER_ID;
	}
	return itemid;
}

#define GetDynamicCuboidPos 					GetDynamicCubePos
#define SetDynamicCuboidPos						SetDynamicCubePos

/****************************************************************************************************
 *                                                                                                  *
 * Fix Destroy Object Hook                                                                          *
 *                                                                                                  *
 ****************************************************************************************************/

//Hook: DestroyDynamicObject
StreamerSpecProt:: SF_DestroyDynamicObject(&objectid){
	new dobj = DestroyDynamicObject(objectid);
	objectid = INVALID_STREAMER_ID;
	return dobj;
}

#if defined _ALS_DestroyDynamicObject
	#undef DestroyDynamicObject
#else
	#define _ALS_DestroyDynamicObject
#endif
#define DestroyDynamicObject SF_DestroyDynamicObject

//Hook: DestroyDynamicPickup
StreamerSpecProt:: SF_DestroyDynamicPickup(&pickupid){
	new dobj = DestroyDynamicPickup(pickupid);
	pickupid = INVALID_STREAMER_ID;
	return dobj;
}

#if defined _ALS_DestroyDynamicPickup
	#undef DestroyDynamicPickup
#else
	#define _ALS_DestroyDynamicPickup
#endif
#define DestroyDynamicPickup SF_DestroyDynamicPickup

//Hook: DestroyDynamicCP
StreamerSpecProt:: SF_DestroyDynamicCP(&checkpointid){
	new dobj = DestroyDynamicCP(checkpointid);
	checkpointid = INVALID_STREAMER_ID;
	return dobj;
}

#if defined _ALS_DestroyDynamicCP
	#undef DestroyDynamicCP
#else
	#define _ALS_DestroyDynamicCP
#endif
#define DestroyDynamicCP SF_DestroyDynamicCP

//Hook: DestroyDynamicRaceCP
StreamerSpecProt:: SF_DestroyDynamicRaceCP(&checkpointid){
	new dobj = DestroyDynamicRaceCP(checkpointid);
	checkpointid = INVALID_STREAMER_ID;
	return dobj;
}

#if defined _ALS_DestroyDynamicRaceCP
	#undef DestroyDynamicRaceCP
#else
	#define _ALS_DestroyDynamicRaceCP
#endif
#define DestroyDynamicRaceCP SF_DestroyDynamicRaceCP

//Hook: DestroyDynamicMapIcon
StreamerSpecProt:: SF_DestroyDynamicMapIcon(&iconid){
	new dobj = DestroyDynamicMapIcon(iconid);
	iconid = INVALID_STREAMER_ID;
	return dobj;
}

#if defined _ALS_DestroyDynamicMapIcon
	#undef DestroyDynamicMapIcon
#else
	#define _ALS_DestroyDynamicMapIcon
#endif
#define DestroyDynamicMapIcon SF_DestroyDynamicMapIcon

//Hook: DestroyDynamic3DTextLabel
StreamerSpecProt:: SF_DestroyDynamic3DTextLabel(&Text3D:id){
	new dobj = DestroyDynamic3DTextLabel(id);
	id = Text3D:INVALID_STREAMER_ID;
	return dobj;
}

#if defined _ALS_DestroyDynamic3DTextLabel
	#undef DestroyDynamic3DTextLabel
#else
	#define _ALS_DestroyDynamic3DTextLabel
#endif
#define DestroyDynamic3DTextLabel SF_DestroyDynamic3DTextLabel

//Hook: DestroyDynamicArea
StreamerSpecProt:: SF_DestroyDynamicArea(&areaid){
	new dobj = DestroyDynamicArea(areaid);
	areaid = INVALID_STREAMER_ID;
	return dobj;
}

#if defined _ALS_DestroyDynamicArea
	#undef DestroyDynamicArea
#else
	#define _ALS_DestroyDynamicArea
#endif
#define DestroyDynamicArea SF_DestroyDynamicArea

//Hook: AttachDynamicObjectToObject
StreamerSpecProt:: SF_AttachDynamicObjectToObject(objectid,attachtoid,Float:offsetx,Float:offsety,Float:offsetz,Float:rx,Float:ry,Float:rz,syncrotation = 1){
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
#define AttachDynamicObjectToObject SF_AttachDynamicObjectToObject

//Hook: DestroyObject
StreamerSpecProt:: SF_DestroyObject(&objectid){
	new dobj = DestroyObject(objectid);
	objectid = INVALID_OBJECT_ID;
	return dobj;
}

#if defined _ALS_DestroyObject
	#undef DestroyObject
#else
	#define _ALS_DestroyObject
#endif
#define DestroyObject SF_DestroyObject

//Hook: DestroyPlayerObject
StreamerSpecProt:: SF_DestroyPlayerObject(playerid,&objectid){
	new dobj = DestroyPlayerObject(playerid,objectid);
	objectid = INVALID_OBJECT_ID;
	return dobj;
}

#if defined _ALS_DestroyPlayerObject
	#undef DestroyPlayerObject
#else
	#define _ALS_DestroyPlayerObject
#endif
#define DestroyPlayerObject SF_DestroyPlayerObject

//Hook: DestroyPickup
StreamerSpecProt:: SF_DestroyPickup(&pickupid){
	new dobj = DestroyPickup(pickupid);
	pickupid = INVALID_PICKUP_ID;
	return dobj;
}

#if defined _ALS_DestroyPickup
	#undef DestroyPickup
#else
	#define _ALS_DestroyPickup
#endif
#define DestroyPickup SF_DestroyPickup

//Hook: Delete3DTextLabel
StreamerSpecProt:: SF_Delete3DTextLabel(&Text3D:id){
	new dobj = Delete3DTextLabel(id);
	id = Text3D:INVALID_3DTEXT_ID;
	return dobj;
}

#if defined _ALS_Delete3DTextLabel
	#undef Delete3DTextLabel
#else
	#define _ALS_Delete3DTextLabel
#endif
#define Delete3DTextLabel SF_Delete3DTextLabel

//Hook: DeletePlayer3DTextLabel
StreamerSpecProt:: SF_DeletePlayer3DTextLabel(playerid,&PlayerText3D:id){
	new dobj = DeletePlayer3DTextLabel(playerid,id);
	id = PlayerText3D:INVALID_3DTEXT_ID;
	return dobj;
}

#if defined _ALS_DeletePlayer3DTextLabel
	#undef DeletePlayer3DTextLabel
#else
	#define _ALS_DeletePlayer3DTextLabel
#endif
#define DeletePlayer3DTextLabel SF_DeletePlayer3DTextLabel

/****************************************************************************************************
 *                                                                                                  *
 * DynamicAntiArea Hook                                                                             *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined OnPlayerEnterAntiArea
	forward OnPlayerEnterAntiArea(playerid,areaid);
#endif
#if defined OnPlayerLeaveAntiArea
	forward OnPlayerLeaveAntiArea(playerid,areaid);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,areaid){
	#if defined OnPlayerLeaveAntiArea
		OnPlayerLeaveAntiArea(playerid,areaid);
	#endif
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

//Hook: OnPlayerLeaveDynamicArea
public OnPlayerLeaveDynamicArea(playerid,areaid){
	#if defined OnPlayerEnterAntiArea
		OnPlayerEnterAntiArea(playerid,areaid);
	#endif
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

/****************************************************************************************************
 *                                                                                                  *
 * OnPlayerWeaponShot for Streamer Object                                                           *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined ENABLE_BULLET_DYNAMIC_OBJECT

	//Hook: OnPlayerShootDynamicObject
	public OnPlayerShootDynamicObject(playerid,weaponid,objectid,Float:x,Float:y,Float:z){
		new Float:ox, Float:oy, Float:oz, Float:tx, Float:ty, Float:tz;
		GetPlayerLastShotVectors(playerid,ox,oy,oz,tx,ty,tz);
		#if defined OnPlayerWeaponShot
			OnPlayerWeaponShot(playerid,weaponid,BULLET_HIT_TYPE_DYNAMIC_OBJECT,0,tx,ty,tz);
		#endif
		#if defined SSpec_OnShootDynamicObject
			SSpec_OnShootDynamicObject(playerid,weaponid,objectid,x,y,z);
		#endif
		return 1;
	}

	#if defined _ALS_OnPlayerShootDynamicObject
		#undef OnPlayerShootDynamicObject
	#else
		#define _ALS_OnPlayerShootDynamicObject
	#endif
	#define OnPlayerShootDynamicObject SSpec_OnShootDynamicObject
	#if defined SSpec_OnShootDynamicObject
		forward SSpec_OnShootDynamicObject(playerid,weaponid,objectid,Float:x,Float:y,Float:z);
	#endif
	
#endif

/****************************************************************************************************
 *                                                                                                  *
 * FilterScript/GameMode Init Hook                                                                  *
 *                                                                                                  *
 ****************************************************************************************************/

new bool:CRC_StreamerFunctionInit = true,
	bool:CRC_StreamerFunctionExit = true;

StreamerSpecProt:: StreamerSpecInit(){
	SetSVarInt("ADM:StreamerSpec:ACTIVE",GetStreamerSpecActiveCount()+1);
	
	//Welcome to StreamerFunction
	new ver_name[16];
	format(ver_name,sizeof(ver_name),"%d.%d.%d",(Streamer_Spec_Version / 10000),((Streamer_Spec_Version % 10000) / 100),((Streamer_Spec_Version % 10000) % 100));
	if(GetSVarInt("ADM:StreamerSpec:INIT") == 0){
		SetSVarInt("ADM:StreamerSpec:INIT",1);
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Info: Load Streamer Functions v%s for SA:MP %s by Abyss Morgan",ver_name,Streamer_Spec_SAMP_Version);
		}
	}
	#if !defined DISABLE_STREAMER_SPEC_CHECK
		CheckStreamerVersion();
	#endif
}

StreamerSpecProt:: StreamerSpecExit(){
	SetSVarInt("ADM:StreamerSpec:ACTIVE",GetStreamerSpecActiveCount()-1);
	
	//Goodbye StreamerSpec
	new ver_name[16];
	format(ver_name,sizeof(ver_name),"%d.%d.%d",(Streamer_Spec_Version / 10000),((Streamer_Spec_Version % 10000) / 100),((Streamer_Spec_Version % 10000) % 100));
	if(GetStreamerSpecActiveCount() == 0){
		SetSVarInt("ADM:StreamerSpec:INIT",0);
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Info: Unload Streamer Functions v%s for SA:MP %s by Abyss Morgan",ver_name,Streamer_Spec_SAMP_Version);
		}
	}
}

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_StreamerFunctionInit){
		CRC_StreamerFunctionInit = false;
		StreamerSpecInit();
	}
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

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_StreamerFunctionInit){
		CRC_StreamerFunctionInit = false;
		StreamerSpecInit();
	}
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

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_StreamerFunctionExit){
		CRC_StreamerFunctionExit = false;
		StreamerSpecExit();
	}
	#if defined SSpec_OnFilterScriptExit
		SSpec_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit SSpec_OnFilterScriptExit
#if defined SSpec_OnFilterScriptExit
	forward SSpec_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_StreamerFunctionExit){
		CRC_StreamerFunctionExit = false;
		StreamerSpecExit();
	}
	#if defined SSpec_OnGameModeExit
		SSpec_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit SSpec_OnGameModeExit
#if defined SSpec_OnGameModeExit
	forward SSpec_OnGameModeExit();
#endif

//EOF
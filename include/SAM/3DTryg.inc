/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                       3D Tryg Functions                                                        *
 *                                                                                                                                *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                         *
 *                                                                                                                                *
 * Plugins: MapAndreas, ColAndreas, YSF, Streamer                                                                                 *
 * Modules: None                                                                                                                  *
 *                                                                                                                                *
 * File Version: 2.7.6                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * MapAndreas Version: 1.2.1                                                                                                      *
 * ColAndreas Version: 1.4.0                                                                                                      *
 * YSF Version: 2.2.0 (IS4)                                                                                                       *
 * Streamer Version: 2.8.2                                                                                                        *
 *                                                                                                                                *
 * 3DTryg FindZ Precision:                                                                                                        *
 * 1. ColAndreas   - The most accurate precision with ColAndreas plugin.                                                          *
 * 2. MapAndreasEx - Average precision MapAndreas plugin + MapAndreasEx Module.                                                   *
 * 3. MapAndreas   - Average precision MapAndreas plugin.                                                                         *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * Float:sqrtN(Float:value,Float:exponent);                                                                                       *
 * abs(value);                                                                                                                    *
 * Float:fabs(Float:value);                                                                                                       *
 * power(value,Float:exponent);                                                                                                   *
 * Float:ctg(Float:value,anglemode:mode=radian);                                                                                  *
 * Float:secans(Float:value,anglemode:mode=radian);                                                                               *
 * Float:cosecans(Float:value,anglemode:mode=radian);                                                                             *
 * single_clock(max,id);                                                                                                          *
 * even_clock(max,id);                                                                                                            *
 * uneven_clock(max,id);                                                                                                          *
 * IsEven(value);                                                                                                                 *
 * Float:RandomFloat(Float:min,Float:max,accuracy = 4);                                                                           *
 * GetRandomHit(Float:x,Float:y,Float:z,range,&Float:tx,&Float:ty,&Float:tz);                                                     *
 * Float:GetDistanceBetweenPoints1D(Float:x1,Float:x2);                                                                           *
 * Float:GetDistanceBetweenPoints2D(Float:x1,Float:y1,Float:x2,Float:y2);                                                         *
 * Float:GetDistanceBetweenPoints3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);                                       *
 * NLTZ(value);              //NotLessThanZero                                                                                    *
 * NMTZ(value);              //NotMoreThanZero                                                                                    *
 * Float:NLTZF(Float:value); //NotLessThanZeroFloat                                                                               *
 * Float:NMTZF(Float:value); //NotMoreThanZeroFloat                                                                               *
 * CompRotation(rotation,&crotation=0); //CompressRotation                                                                        *
 * Float:CompRotationFloat(Float:rotation,&Float:crotation=0.0); //CompressRotationFloat                                          *
 * GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty);                                                  *
 * GetPointInFront3D(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                       *
 * Float:GetPointInFrontOfPlayer(playerid,&Float:tx,&Float:ty,Float:radius);                                                      *
 * Float:GetPointInFrontOfCamera2D(playerid,&Float:tx,&Float:ty,Float:radius);                                                    *
 * GetPointInFrontOfCamera3D(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);                    *
 * GetRotationFor2Point2D(Float:x,Float:y,Float:tx,Float:ty,&Float:rz);                                                           *
 * GetRotationFor2Point3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:rx,&Float:rz);                                *
 * GetRandomClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0);           *
 * GetRandomPointInCircle(Float:x,Float:y,Float:size,&Float:tx,&Float:ty);                                                        *
 * GetRandomPointInCylinderEx(Float:x,Float:y,Float:minz,Float:maxz,Float:size,&Float:tx,&Float:ty,&Float:tz);                    *
 * GetRandomPointInSphere(Float:x,Float:y,Float:z,Float:size,&Float:tx,&Float:ty,&Float:tz);                                      *
 * GetRandomPointInRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,&Float:tx,&Float:ty);                                    *
 * GetRandomPointInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:tx,&Float:ty,&Float:tz);         *
 * Float:ShiftDegreeToRadian(Float:deg);                                                                                          *
 * Float:ShiftDegreeToRadianEx(Float:deg);                                                                                        *
 * Float:ShiftDegreeToGrades(Float:deg);                                                                                          *
 * Float:ShiftRadianToDegree(Float:rad);                                                                                          *
 * Float:ShiftRadianToDegreeEx(Float:rad);                                                                                        *
 * Float:ShiftRadianToGrades(Float:rad);                                                                                          *
 * Float:ShiftGradesToDegree(Float:grad);                                                                                         *
 * Float:ShiftGradesToRadian(Float:grad);                                                                                         *
 * ConvertMTARaceRotation(Float:rotation1,Float:rotation2,Float:rotation3,&Float:rx,&Float:ry,&Float:rz);                         *
 * ConvertToMTARaceRotation(Float:rx,Float:ry,Float:rz,&Float:rotation1,&Float:rotation2,&Float:rotation3);                       *
 * GetMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:speed,&rtime);                                            *
 * Float:GetSpeedForMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:speed,rtime);                              *
 * GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz);                                                                   *
 * Float:GetPointInFrontOfVehicle2D(vehicleid,&Float:tx,&Float:ty,Float:radius);                                                  *
 * GetPointInFrontOfVehicle3D(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);                  *
 * GetPlayerCameraRotation(playerid,&Float:rx,&Float:rz);                                                                         *
 * Float:GetPlayerCameraZAngle(playerid,&Float:rz=0.0);                                                                           *
 * GetPointFor2Point2D(Float:x1,Float:y1,Float:x2,Float:y2,Float:percent_size,&Float:tx,&Float:ty);                               *
 * GetPointFor2Point3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:percent_size,&Float:tx,&Float:ty,&Float:tz);   *
 * ShiftVectorToRotation(Float:vx,Float:vy,Float:vz,&Float:rx,&Float:rz);                                                         *
 * ShiftRotationToVector(Float:rx,Float:rz,&Float:vx,&Float:vy,&Float:vz);                                                        *
 * bool:IsPointBetween2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB);                                           *
 * bool:IsPointBetween2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB);                *
 * bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist);                              *
 * bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist);   *
 * bool:IsPointInCircle(Float:px,Float:py,Float:x,Float:y,Float:size);                                                            *
 * bool:IsPointInCylinder(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:size);           *
 * bool:IsPlayerInCylinderEx(playerid,Float:x,Float:y,Float:minz,Float:maxz,Float:size);                                          *
 * bool:IsPointInSphere(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:size);                                           *
 * bool:IsPointInRectangle(Float:x,Float:y,Float:minx,Float:miny,Float:maxx,Float:maxy);                                          *
 * bool:IsPointInCube(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                 *
 * bool:IsPointInPolygon(Float:x,Float:y,Float:points[],maxpoints = sizeof(points));                                              *
 * bool:IsPlayerInCircle(playerid,Float:x,Float:y,Float:size);                                                                    *
 * bool:IsPlayerInCylinder(playerid,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:size);                            *
 * bool:IsPointInCylinderEx(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:minz,Float:maxz,Float:size);                         *
 * bool:IsPlayerInSphere(playerid,Float:x,Float:y,Float:z,Float:size);                                                            *
 * bool:IsPlayerInRectangle(playerid,Float:minx,Float:miny,Float:maxx,Float:maxy);                                                *
 * bool:IsPlayerInCube(playerid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                               *
 * bool:IsPlayerInPolygon(playerid,Float:points[],maxpoints = sizeof(points));                                                    *
 * bool:IsProbable(chance);                                                                                                       *
 * Float:CalculatePercent(Float:value,Float:maxvalue);                                                                            *
 * Float:GetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0);                                                            *
 * Float:SetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0);                                                            *
 * Float:GetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0);                                                             *
 * Float:SetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0);                                                             *
 * Float:GetVehicleSpeed(vehicleid);                                                                                              *
 * Float:GetPlayerSpeed(playerid);                                                                                                *
 * CreateDynamicExplosion(Float:x,Float:y,Float:z,type,Float:radius,worldid=-1,interiorid=-1,playerid=-1,Float:distance=200.0);   *
 * bool:IsPlayerSkydiving(playerid);                                                                                              *
 * bool:IsPlayerUsingParachute(playerid);                                                                                         *
 * bool:IsPlayerAiming(playerid);                                                                                                 *
 * GetVehicleFlags(vehicleid);                                                                                                    *
 * GetVehicleFlagsByModel(modelid);                                                                                               *
 * bool:IsVehicleFlag(value,flag);                                                                                                *
 * CountPlayers();                                                                                                                *
 * CountActors();                                                                                                                 *
 * GetPlayerOrientationPos(playerid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);                *
 * GetVehicleOrientationPos(vehicleid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);              *
 * GetObjectOrientationPos(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);                *
 * GetWeaponShotPos(playerid,hittype,&Float:fx,&Float:fy,&Float:fz);                                                              *
 * Float:GetActorDistanceFromPoint(actorid,Float:x,Float:y,Float:z);                                                              *
 * Float:GetPlayersDistance(playerid_a,playerid_b);                                                                               *
 * Float:GetVehiclesDistance(vehicleid_a,vehicleid_b);                                                                            *
 * Float:GetObjectsDistance(objectid_a,objectid_b);                                                                               *
 * Float:GetPlayerActorDistance(playerid,actorid);                                                                                *
 * Float:GetPlayerVehicleDistance(playerid,vehicleid);                                                                            *
 * Float:GetPlayerObjectDistance(playerid,objectid);                                                                              *
 * SetPlayerLookAtPlayer(playerid,targetid,cut = CAMERA_CUT);                                                                     *
 * bool:IsPlayerLookAtSky(playerid);                                                                                              *
 * GetVehicleUpVector(vehicleid,&Float:vx,&Float:vy,&Float:vz);                                                                   *
 * GetVehicleUpPos(vehicleid,Float:radius,&Float:x,&Float:y,&Float:z);                                                            *
 * GetVehicleDownPos(vehicleid,Float:radius,&Float:x,&Float:y,&Float:z);                                                          *
 *                                                                                                                                *
 * Extended Functions:                                                                                                            *
 * Get3DTrygModules(&modules_count=0);                                                                                            *
 * bool:IsTryg3DModuleLoaded(Tryg3DModule:moduleid);                                                                              *
 * Get3DTrygErrorCount();                                                                                                         *
 * Get3DTrygWarringCount();                                                                                                       *
 * Reset3DTrygErrorCount();                                                                                                       *
 * Reset3DTrygWarringCount();                                                                                                     *
 *                                                                                                                                *
 * ATM Module Functions:                                                                                                          *
 * randomex(min,max);                                                                                                             *
 * Tryg3DKeyPressed(key);                                                                                                         *
 * Tryg3DKeyReleased(key);                                                                                                        *
 * Tryg3DKeyHolding(key);                                                                                                         *
 * isnull(string);                                                                                                                *
 *                                                                                                                                *
 * Streamer Functions:                                                                                                            *
 * GetDynamicObjectOrientationPos(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);         *
 * GetDynamicObjectOrientPosCol(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);           *
 * Float:GetDynamicObjectsDistance(objectid_a,objectid_b);                                                                        *
 * Float:GetPlayerDynamicObjectDistance(playerid,objectid);                                                                       *
 *                                                                                                                                *
 * MapAndreas Functions:                                                                                                          *
 * Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0);                                                                           *
 * GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry);                                                             *
 * GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance);           *
 * bool:IsPointInWaterFrontOfPlayer(playerid,Float:radius);                                                                       *
 * bool:IsPointInWater(Float:x,Float:y,Float:z=0.0);                                                                              *
 *                                                                                                                                *
 * MapAndreas Extended Functions:                                                                                                 *
 * bool:IsMapAndreasInit();                                                                                                       *
 * SafeMapAndreasInit(mode = MAP_ANDREAS_MODE_FULL, name[]="", len=sizeof(name));                                                 *
 *                                                                                                                                *
 * ColAndreas Functions:                                                                                                          *
 * MovePointCol(Float:StartX,Float:StartY,Float:StartZ,Float:EndX,Float:EndY,Float:EndZ,&Float:x,&Float:y,&Float:z);              *
 * MovePointColCutLine(Float:SX,Float:SY,Float:SZ,Float:EX,Float:EY,Float:EZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0);      *
 * MovePointColCutLineEx(Float:SX,Float:SY,Float:SZ,Float:EX,Float:EY,Float:EZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0);    *
 * GetPointInFront3DCol(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                    *
 * Float:GetPointInFrontOfPlayerCol(playerid,&Float:tx,&Float:ty,Float:radius);                                                   *
 * Float:GetPointInFrontOfCamera2DCol(playerid,&Float:tx,&Float:ty,Float:radius);                                                 *
 * GetPointInFrontOfCamera3DCol(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);                 *
 * Float:GetPointInFrontOfVehicle2DCol(vehicleid,&Float:tx,&Float:ty,Float:radius);                                               *
 * GetPointInFrontOfVehicle3DCol(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);               *
 * GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry);                                                             *
 * GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance);           *
 * GetPlayerCollisionFlags(playerid);                                                                                             *
 * bool:IsCollisionFlag(value,flag);                                                                                              *
 * Float:UndergroundFindZ(Float:x,Float:y,&Float:z=0.0);                                                                          *
 * Float:InteriorFindZ(Float:px,Float:py,Float:pz=1000.0,Float:size=2.0,&Float:z=0.0);                                            *
 * bool:IsPointInWater(Float:x,Float:y,Float:z=0.0);                                                                              *
 * bool:IsPointInUnderwater(Float:x,Float:y,Float:z);                                                                             *
 * bool:IsPointInUnderground(Float:x,Float:y,Float:z);                                                                            *
 * bool:IsPointInAir(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2);                                         *
 * bool:IsPointInGround(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2);                                      *
 * bool:IsPointInWaterFrontOfPlayer(playerid,Float:radius);                                                                       *
 * Float:ColAndreasFindZ(Float:x,Float:y,&Float:z=0.0);                                                                           *
 * GetPlayerOrientationPosCol(playerid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);             *
 * GetVehicleOrientationPosCol(vehicleid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);           *
 * GetObjectOrientationPosCol(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz);             *
 * bool:IsBetweenPlayersIsWall(playerid,targetid);                                                                                *
 * bool:IsBetweenPlayerToPointIsWall(playerid,Float:x,Float:y,Float:z);                                                           *
 *                                                                                                                                *
 * ColAndreas Extended Functions:                                                                                                 *
 * bool:IsColAndreasInit();                                                                                                       *
 * SafeColAndreasInit();                                                                                                          *
 * GetColAndreasVersion();                                                                                                        *
 * GetValidColAndreasVersion();                                                                                                   *
 * bool:IsValidColAndreas(version);                                                                                               *
 * GetColAndreasVersionName(name[], value = GET_COLANDREAS_VERSION, maxdest = sizeof name);                                       *
 * CheckColAndreasVersion();                                                                                                      *
 *                                                                                                                                *
 * YSF Functions:                                                                                                                 *
 * Float:GetPlayerHydraReactorRX(playerid);                                                                                       *
 * bool:IsPlayerHydraReactorBoost(playerid);                                                                                      *
 * GetPlayerRotation(playerid,&Float:rx,&Float:ry,&Float:rz);                                                                     *
 * GetPlayerTimeline(playerid);                                                                                                   *
 * SetPlayerTimeline(playerid,timeline);                                                                                          *
 * GetPlayerPos4D(playerid,&Float:x,&Float:y,&Float:z,&timeline);                                                                 *
 * SetPlayerPos4D(playerid,Float:x,Float:y,Float:z,timeline=0);                                                                   *
 * CreateDynamicExplosion4D(Float:x,Float:y,Float:z,type,Float:radius,worldid = -1,interiorid = -1,timeline=-1,                   *
 *                          playerid = -1,Float:distance = 200.0);                                                                *
 *                                                                                                                                *
 * YSF Extended Functions:                                                                                                        *
 * UpdatePlayerTimeline(playerid);                                                                                                *
 *                                                                                                                                *
 * Symbols:                                                                                                                       *
 * FLOAT_PI    - pi constant value                                                                                                *
 * FLOAT_EULER - Euler number                                                                                                     *
 * FLOAT_NAN   - Float NaN                                                                                                        *
 * VBTP        - Value Bigger Than Possible                                                                                       *
 *                                                                                                                                *
 * Functions extra names:                                                                                                         *
 * GetXYInFrontOfPlayer       -> GetPointInFrontOfPlayer                                                                          *
 * GetPointInFront            -> GetPointInFront3D                                                                                *
 * GetPointInFrontOfCamera    -> GetPointInFrontOfCamera3D                                                                        *
 * GetDistanceBetweenPoints   -> GetDistanceBetweenPoints3D                                                                       *
 * CompressRotation           -> CompRotation                                                                                     *
 * CompressRotationFloat      -> CompRotationFloat                                                                                *
 * GetXYInFrontOfPlayerCol    -> GetPointInFrontOfPlayerCol                                                                       *
 * GetPointInFrontCol         -> GetPointInFront3DCol                                                                             *
 * GetPointInFrontOfCameraCol -> GetPointInFrontOfCamera3DCol                                                                     *
 * GetXYZInFrontOfVehicle     -> GetPointInFrontOfVehicle3D (Attention, different syntax)                                         *
 * GetVehicleAngle            -> GetVehicleRotation                                                                               *
 * Tryg3DMapAndreasFindZ      -> CA_FindZ_For2DCoord / MapAndreasFindZ / MapAndreas_FindZ_For2DCoord                              *
 *                                                                                                                                *
 * Old prototype:                                                                                                                 *
 * GetAngle                   -> GetPlayerTargetAngle / SetPlayerTargetAngle / GetRotationFor2Point2D                             *
 *                                                                                                                                *
 * Deprecated functions:                                                                                                          *
 * GetXYZInFrontOfVehicle(vehicleid,Float:distance,&Float:x,&Float:y,&Float:z);                                                   *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v2.7.6
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v2.7.6
#elseif (Tryg3D_Version < 20706)
	#error [ADM] Update you 3DTryg.inc to v2.7.6
#endif
*/

#if defined _3D_Tryg
	#endinput
#endif
#define _3D_Tryg

#define Tryg3D_Version									(20706) //a.b.c 10000*a+100*b+c


//Tryg3D Plugin Module List
#define TRYG3D_MODULEID_MAPANDREAS						(Tryg3DModule:1)
#define TRYG3D_MODULEID_COLANDREAS						(Tryg3DModule:2)
#define TRYG3D_MODULEID_YSF								(Tryg3DModule:3)
#define TRYG3D_MODULEID_STREAMER						(Tryg3DModule:4)

//Detect ColAndreas
#if defined COLANDREAS
	#define Tryg3D_ColAndreas
	#define Tryg3D_ColAndreasVersion					(10400) //a.b.c 10000*a+100*b+c
	#define Tryg3D_Module_ColAndreas					(true)
#else
	#define Tryg3D_Module_ColAndreas					(false)
#endif

#if !defined COLANDREAS_VERSION
	#define COLANDREAS_VERSION							(0)
#endif

//Detect YSF
#if defined _YSF_included
	#define Tryg3D_YSF
	#define Tryg3D_Module_YSF							(true)
#else
	#define Tryg3D_Module_YSF							(false)
#endif

//Detect Streamer
#if ((defined Streamer_AppendArrayData) && (defined INVALID_STREAMER_ID))
	#define Tryg3D_Streamer
	#define Tryg3D_StreamerVersion						(0x282001)
	#define Tryg3D_Module_Streamer						(true)
#else
	#define Tryg3D_Module_Streamer						(false)
#endif

//Detect MapAndreas
#if defined MapAndreas_FindZ_For2DCoord
	#define Tryg3D_MapAndreas
	#define Tryg3D_MapAndreasVersion					(10201) //a.b.c 10000*a+100*b+c
	#define Tryg3D_Module_MapAndreas					(true)
#else
	#define Tryg3D_Module_MapAndreas					(false)
#endif

//Detect MapAndreasEx
#if defined _Map_Andreas_Ex
	#define Tryg3D_MapAndreasEx
#endif

//Auto Create MapAndreasEx
#if (!defined Tryg3D_MapAndreasEx && defined Tryg3D_MapAndreas)

	#define IsMapAndreasInit							Tryg3D_IsMapAndreasInit
	#define SafeMapAndreasInit							Tryg3D_SafeMapAndreasInit
	
	stock Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0){
		if(x <= -3000.0 || x >= 3000.0 || y <= -3000.0 || y >= 3000.0){
			z = 0.0;
		} else {
			MapAndreas_FindZ_For2DCoord(x,y,z);
		}
		return z;
	}
	
	#define Tryg3D_MapAndreasEx
	
#elseif (!defined Tryg3D_MapAndreasEx && defined Tryg3D_ColAndreas)
	
	#define IsMapAndreasInit							Tryg3D_IsColAndreasInit
	#define SafeMapAndreasInit							Tryg3D_SafeColAndreasInit
	
	stock Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0){
		if(x <= -3000.0 || x >= 3000.0 || y <= -3000.0 || y >= 3000.0){
			z = 0.0;
		} else {
			CA_FindZ_For2DCoord(x,y,z);
		}
		return z;
	}
	
	#define ColAndreasFindZ 							MapAndreasFindZ
	
	#define Tryg3D_MapAndreasEx
	
#endif

//Define FindZ Precision
#if defined Tryg3D_ColAndreas
	#define Tryg3DMapAndreasFindZ						CA_FindZ_For2DCoord
#elseif defined Tryg3D_MapAndreasEx
	#define Tryg3DMapAndreasFindZ						MapAndreasFindZ
#elseif defined Tryg3D_MapAndreas
	#define Tryg3DMapAndreasFindZ						MapAndreas_FindZ_For2DCoord
#endif

#if !defined FLOAT_PI
	#define FLOAT_PI		 							(3.14159265358979323846)
#endif

#if !defined FLOAT_EULER
	#define FLOAT_EULER									(2.718281828459)
#endif

#if !defined FLOAT_NAN
	#define FLOAT_NAN 									(Float:0xFFFFFFFF)
#endif

#if !defined VBTP
	#define VBTP 										(0x7FFFFFFF)
#endif

#if !defined MAX_POLYGON_POINTS
	#define MAX_POLYGON_POINTS 							(256)
#endif

#if !defined VEHICLE_SPEED_MULTIPLIER
	#define VEHICLE_SPEED_MULTIPLIER 					(170.00)
#endif

#if defined Tryg3D_ColAndreas
	#define POSITION_FLAG_WORLD							(0b00000001)
	#define POSITION_FLAG_INTERIOR						(0b00000010)
	#define POSITION_FLAG_AIR							(0b00000100)
	#define POSITION_FLAG_GROUND						(0b00001000)
	#define POSITION_FLAG_WATER							(0b00010000)
	#define POSITION_FLAG_UNDERWATER					(0b00100000)
	#define POSITION_FLAG_UNDERGROUND					(0b01000000)
#endif

#define VF_STREET										(1)
#define VF_AIRBORNE										(2)
#define VF_NATATORIAL									(4)
#define VF_MILITARY										(8)
#define VF_RAILROAD										(16)
#define VF_RC		 									(32)
#define VF_ROAD											(64)
#define VF_AIRPLANE										(128)
#define VF_HELICOPTER 									(256)
#define VF_BIKES	 									(512)
#define VF_TRAILER										(1024)
#define VF_TOWABLE										(2048)
#define VF_POLICE		 								(4096)

#define ctg(%0,%1)										(1.0/floattan((%0),(%1)))
#define secans(%0,%1)									(1.0/floatcos((%0),(%1)))
#define cosecans(%0,%1)									(1.0/floatsin((%0),(%1)))
#define abs(%0)											(((%0) < 0)?(-(%0)):((%0)))
#define fabs(%0)										(((%0) < 0.0)?(-(%0)):((%0)))

#define single_clock(%1,%2)								((360.0/(%1))*(%2))
#define even_clock(%1,%2)								((360.0/(%1))*(2*(%2)))
#define uneven_clock(%1,%2)								((360.0/(%1))*((2*(%2))-1))

#define	sqrtN(%0,%1)									floatpower((%0),(1.0/(%1)))

#define GetDistanceBetweenPoints1D(%1,%2)				VectorSize((%1)-(%2),0.0,0.0)
#define GetDistanceBetweenPoints2D(%1,%2,%3,%4)			VectorSize((%1)-(%3),(%2)-(%4),0.0)
#define GetDistanceBetweenPoints3D(%1,%2,%3,%4,%5,%6)	VectorSize((%1)-(%4),(%2)-(%5),(%3)-(%6))

#define NLTZ(%0)										(((%0) < 0)?(0):(%0))
#define NMTZ(%0)										(((%0) > 0)?(0):(%0))
#define NLTZF(%0)										(((%0) < 0.0)?(0.0):(%0))
#define NMTZF(%0)										(((%0) > 0.0)?(0.0):(%0))

#define IsEven(%0)										((((%0) % 2) == 0)?(true):(false))
#define power(%0,%1)									(floatround(floatpower((%0),(%1))))
#define CalculatePercent(%0,%1)							(((%0)/(%1))*100.0)

#define ShiftDegreeToRadian(%0)							((%0)*((FLOAT_PI*2)/360.0))
#define ShiftDegreeToRadianEx(%0)						((360.0-CompRotationFloat(%0))*(-((FLOAT_PI*2)/360.0)))
#define ShiftDegreeToGrades(%0)							((%0)*(10.0/9.0))
#define ShiftRadianToDegree(%0)							((%0)/((FLOAT_PI*2)/360.0))
#define ShiftRadianToDegreeEx(%0) 						(CompRotationFloat(floatabs(((%0)/((FLOAT_PI*2)/360.0))+360.0)))
#define ShiftRadianToGrades(%0)							(ShiftDegreeToGrades(ShiftRadianToDegree(%0)))
#define ShiftGradesToDegree(%0)							((%0)*0.9)
#define ShiftGradesToRadian(%0)							(ShiftDegreeToRadian(ShiftGradesToDegree(%0)))

#define ShiftRotationToVector(%0,%1,%2,%3,%4)			(GetPointInFront3D(0.0,0.0,0.0,(%0),(%1),1.0,(%2),(%3),(%4)))

//old code version made by Zoutdaxv (modified version)
#define GetRotationFor2Point2D(%0,%1,%2,%3,%4)			(CompRotationFloat((atan2((%3)-(%1),(%2)-(%0))-90.0),(%4)))
#define IsPointInCylinderEx(%0,%1,%2,%3,%4,%5,%6,%7)	IsPointInCylinder((%0),(%1),(%2),(%3),(%4),(%5),(%3),(%4),(%6),(%7))

#define GetVehicleFlags(%0)								GetVehicleFlagsByModel(GetVehicleModel(%0))
#define IsVehicleFlag(%0,%1)							((%0) & (%1))

#define T3D:											v3D

//ATM Module
#if !defined randomex
	#define randomex(%0,%1) 							(random((%1)-(%0)+1)+(%0))
#endif

#define Tryg3DKeyPressed(%0) 							(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define Tryg3DKeyReleased(%0)							(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define Tryg3DKeyHolding(%0) 							((newkeys & (%0)) == (%0))

#if !defined isnull
	#define isnull(%1) 									((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define Get3DTrygErrorCount() 							GetSVarInt("ADM:3DTryg:Error")
#define Get3DTrygWarringCount() 						GetSVarInt("ADM:3DTryg:Warring")

#define Reset3DTrygErrorCount() 						SetSVarInt("ADM:3DTryg:Error",0)
#define Reset3DTrygWarringCount() 						SetSVarInt("ADM:3DTryg:Warring",0)

//Only available for 3DTryg
#define Update3DTrygErrorCount() 						SetSVarInt("ADM:3DTryg:Error",Get3DTrygErrorCount()+1)
#define Update3DTrygWarringCount() 						SetSVarInt("ADM:3DTryg:Warring",Get3DTrygWarringCount()+1)
//-------------------------

enum element_orientation {
	o_left,
	o_right,
	o_up,
	o_down,
	o_front,
	o_back
}

enum Vectors3D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z, Float:T3D:A
}

enum Float3D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	
	T3D:VW, T3D:INT, Float:T3D:SPEED
}

enum Float4D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	
	T3D:VW, T3D:INT, T3D:TL, Float:T3D:SPEED
}

enum LongFloat3D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	Float:T3D:trX, Float:T3D:trY, Float:T3D:trZ,
	
	Float:T3D:VecX, Float:T3D:VecY, Float:T3D:VecZ,
	
	T3D:VW, T3D:INT, Float:T3D:SPEED
}

enum LongFloat4D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	Float:T3D:trX, Float:T3D:trY, Float:T3D:trZ,
	
	Float:T3D:VecX, Float:T3D:VecY, Float:T3D:VecZ,
	
	T3D:VW, T3D:INT, T3D:TL, Float:T3D:SPEED
}

stock Get3DTrygModules(&modules_count=0){
	modules_count = 0;
	new tryg_str[128];
	format(tryg_str,sizeof(tryg_str),"3D");
	
	#if defined Tryg3D_MapAndreas
		format(tryg_str,sizeof(tryg_str),"%s:MapAndreas",tryg_str);
		modules_count++;
	#endif
	
	#if defined Tryg3D_ColAndreas
		format(tryg_str,sizeof(tryg_str),"%s:ColAndreas",tryg_str);
		modules_count++;
	#endif
	
	#if defined Tryg3D_YSF
		format(tryg_str,sizeof(tryg_str),"%s:YSF",tryg_str);
		modules_count++;
	#endif
	
	#if defined Tryg3D_Streamer
		format(tryg_str,sizeof(tryg_str),"%s:Streamer",tryg_str);
		modules_count++;
	#endif
	
	return tryg_str;
}

stock Float:GetActorDistanceFromPoint(actorid,Float:x,Float:y,Float:z){
	new Float:px,Float:py,Float:pz;
	GetActorPos(actorid,px,py,pz);
	return GetDistanceBetweenPoints3D(x,y,z,px,py,pz);
}

stock Float:GetPlayersDistance(playerid_a,playerid_b){
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid_b,x,y,z);
	return GetPlayerDistanceFromPoint(playerid_a,x,y,z);
}

stock Float:GetVehiclesDistance(vehicleid_a,vehicleid_b){
	new Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid_b,x,y,z);
	return GetVehicleDistanceFromPoint(vehicleid_a,x,y,z);
}

stock Float:GetObjectsDistance(objectid_a,objectid_b){
	new Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB;
	GetObjectPos(objectid_a,xA,yA,zA);
	GetObjectPos(objectid_b,xB,yB,zB);
	return GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
}

stock Float:GetPlayerActorDistance(playerid,actorid){
	new Float:x,Float:y,Float:z;
	GetActorPos(actorid,x,y,z);
	return GetPlayerDistanceFromPoint(playerid,x,y,z);
}

stock Float:GetPlayerVehicleDistance(playerid,vehicleid){
	new Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid,x,y,z);
	return GetPlayerDistanceFromPoint(playerid,x,y,z);
}

stock Float:GetPlayerObjectDistance(playerid,objectid){
	new Float:x,Float:y,Float:z;
	GetObjectPos(objectid,x,y,z);
	return GetPlayerDistanceFromPoint(playerid,x,y,z);
}

stock SetPlayerLookAtPlayer(playerid,targetid,cut = CAMERA_CUT){
	new Float:x,Float:y,Float:z;
	GetPlayerPos(targetid,x,y,z);
	SetPlayerCameraLookAt(playerid,x,y,z,cut);
}

stock bool:IsTryg3DModuleLoaded(Tryg3DModule:moduleid){
	switch(moduleid){
		case TRYG3D_MODULEID_MAPANDREAS:	return Tryg3D_Module_MapAndreas;
		case TRYG3D_MODULEID_COLANDREAS:	return Tryg3D_Module_ColAndreas;
		case TRYG3D_MODULEID_YSF:			return Tryg3D_Module_YSF;
		case TRYG3D_MODULEID_STREAMER:		return Tryg3D_Module_Streamer;
	}
	return false;
}

//Author: hesambia random.inc
stock Float:RandomFloat(Float:min,Float:max,accuracy = 4){
	if(min >= max) return 0.0;
	if(min < 0.0 || max < 0.0) return 0.0;
	if(accuracy < 1 || accuracy > 6) return 0.0;
	new divValue; 
	switch(accuracy){
		case 1: divValue = 10;
		case 2: divValue = 100;
		case 3: divValue = 1000;
		case 4: divValue = 10000;
		case 5: divValue = 100000;
		case 6: divValue = 1000000;
	}
	return random(floatround(max)-floatround(min))+min+(random(divValue)/divValue);
}

stock Float:GetVehicleSpeed(vehicleid){
	new Float:x,Float:y,Float:z;
	GetVehicleVelocity(vehicleid,x,y,z);
	return floatmul(VectorSize(x,y,z),VEHICLE_SPEED_MULTIPLIER);
}

//Prototype function
stock Float:GetPlayerSpeed(playerid){
	new Float:x,Float:y,Float:z;
	GetPlayerVelocity(playerid,x,y,z);
	return VectorSize(x,y,z);
}

stock bool:IsPlayerSkydiving(playerid){
	new index = GetPlayerAnimationIndex(playerid);
	return bool:(index >= 958 && index <= 962);
}

stock bool:IsPlayerUsingParachute(playerid){
	new index = GetPlayerAnimationIndex(playerid);
	return bool:(index >= 963 && index <= 979);
}

stock bool:IsPlayerAiming(playerid){
	switch(GetPlayerAnimationIndex(playerid)){
		case 1167,1365,1643,1453,220: return true;
	}
	return false;
}

stock GetVehicleFlagsByModel(modelid){
	new flag_value = 0;
	switch(modelid){
		case 425,548,417,487,497,563,469,447,488: flag_value += VF_AIRBORNE + VF_HELICOPTER;
		case 460,476,511,512,520,593,592,553,519,513,577: flag_value += VF_AIRBORNE + VF_AIRPLANE;
		case 539: flag_value += VF_AIRBORNE;
	}
	switch(modelid){
		case 425,520,432: flag_value += VF_MILITARY;
	}
	switch(modelid){
		case 472,473,493,595,484,430,453,452,446,454,539,447,460: flag_value += VF_NATATORIAL;
	}
	switch(modelid){
		case 441,464,465,501,564,594: flag_value += VF_RC;
	}
	switch(modelid){
		case 471,468,586,463,523,521,461,522,581,448,462,510,481,509: flag_value += VF_BIKES;
	}
	if(modelid == 539 || ((flag_value & VF_NATATORIAL != VF_NATATORIAL) && (flag_value & VF_AIRBORNE != VF_AIRBORNE))) flag_value += VF_STREET;
	switch(modelid){
		case 437,544,431,407,408,570,569,538,537,449,532,524,403,514,515,443,435,433,432,406: {	}

		default: {
			if(flag_value&VF_NATATORIAL!=VF_NATATORIAL && flag_value&VF_AIRBORNE!=VF_AIRBORNE && flag_value&VF_RC!=VF_RC && flag_value&VF_BIKES!=VF_BIKES){
				flag_value += VF_TOWABLE;
			}
		}

	}
	switch(modelid){
		case 416,523,427,490,407,544,596,598,597,599: flag_value += VF_POLICE;
	}
	return flag_value;
}

stock CountPlayers(){
	new cnt = 0;
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i)){
			cnt++;
		}
	}
	return cnt;
}

stock CountActors(){
	new cnt = 0;
	for(new i = 0; i < MAX_ACTORS; i++){
		if(IsValidActor(i)){
			cnt++;
		}
	}
	return cnt;
}

stock GetRandomHit(Float:x,Float:y,Float:z,range,&Float:tx,&Float:ty,&Float:tz){
	tx = x + (random(range * 2 + 1)-range);
	ty = y + (random(range * 2 + 1)-range);
	tz = z + (random(range * 2 + 1)-range);
}

stock CompRotation(rotation,&crotation=0){
	crotation = rotation;
	while(crotation < 0) crotation += 360;
	while(crotation >= 360) crotation -= 360;
	return crotation;
}

stock Float:CompRotationFloat(Float:rotation,&Float:crotation=0.0){
	crotation = rotation;
	while(crotation < 0.0) crotation += 360.0;
	while(crotation >= 360.0) crotation -= 360.0;
	return crotation;
}

//Old code version, Updated by Shiska
stock GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty){
	tx = x - (radius*floatsin(rz,degrees));
	ty = y + (radius*floatcos(rz,degrees));
}

//new code version support 3D made by Abyss Morgan
stock GetPointInFront3D(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	tx = x + (radius * floatsin(rx+90.0,degrees) * floatcos(rz+90.0,degrees));
	ty = y + (radius * floatsin(rx+90.0,degrees) * floatsin(rz+90.0,degrees));
	tz = z + (radius * floatcos(-rx+90.0,degrees));
}

//GetXYInFrontOfPlayer
stock Float:GetPointInFrontOfPlayer(playerid,&Float:tx,&Float:ty,Float:radius){
	new Float:rz;
	GetPlayerPos(playerid,tx,ty,rz);
	GetPlayerFacingAngle(playerid,rz);
	if(IsPlayerInAnyVehicle(playerid)){
		GetVehicleZAngle(GetPlayerVehicleID(playerid),rz);
	}
	GetPointInFront2D(tx,ty,rz,radius,tx,ty);
	return rz;
}

stock Float:GetPlayerCameraZAngle(playerid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:mz;
	GetPlayerCameraFrontVector(playerid,mx,my,mz);
	CompRotationFloat((atan2(my,mx)-90.0),rz);
	return rz;
}

stock Float:GetPointInFrontOfCamera2D(playerid,&Float:tx,&Float:ty,Float:radius){
	new Float:x,Float:y,Float:rz;
	GetPlayerCameraPos(playerid,x,y,rz);
	GetPlayerCameraZAngle(playerid,rz);
	GetPointInFront2D(x,y,rz,radius,tx,ty);
	return rz;
}

//new code version support 3D made by Abyss Morgan
stock GetRotationFor2Point3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:rx,&Float:rz){
	new Float:radius = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
	if(radius > 0.0){
		CompRotationFloat(-(acos((tz-z)/radius)-90.0),rx);
		CompRotationFloat((atan2(ty-y,tx-x)-90.0),rz);
	} else {
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Warring: Get the rotation wrong, identical points.");
		}
		Update3DTrygWarringCount();
	}
}

//random clock pos
stock GetRandomClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0){
	new rand = random(360);
	if(rz == -1000.0) rz = rand;
	GetPointInFront3D(x,y,z,0.0,rz,radius,tx,ty,tz);
	CompRotationFloat(rz-180.0,trz);
}

stock GetRandomPointInCircle(Float:x,Float:y,Float:size,&Float:tx,&Float:ty){
	tx = x + (random(floatround(size * 2)+1)-size);
	ty = y + (random(floatround(size * 2)+1)-size);
}

/*
//temporarily removed, doesn't work
stock GetRandomPointInCylinder(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:size,&Float:tx,&Float:ty,&Float:tz){
	new Float:dist = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB), rand_line = random(floatround(dist)),
		Float:line_x, Float:line_y, Float:line_z, Float:line_rx, Float:line_rz;
	GetPointFor2Point3D(xA,yA,zA,xB,yB,zB,((float(rand_line)/dist)*100.0),line_x,line_y,line_z);
	GetRotationFor2Point3D(xA,yA,zA,xB,yB,zB,line_rx,line_rz);
	GetPointInFront3D(line_x,line_y,line_z,float(random(360)),CompRotationFloat(line_rz+90.0),float(random(floatround(size))+1),tx,ty,tz);
}
*/

stock GetRandomPointInCylinderEx(Float:x,Float:y,Float:minz,Float:maxz,Float:size,&Float:tx,&Float:ty,&Float:tz){
	tx = x + (random(floatround(size * 2)+1)-size);
	ty = y + (random(floatround(size * 2)+1)-size);
	tz = random(floatround(floatsqroot(floatpower(minz-maxz,2)))+1)+minz;
}

stock GetRandomPointInSphere(Float:x,Float:y,Float:z,Float:size,&Float:tx,&Float:ty,&Float:tz){
	tx = x + (random(floatround(size * 2)+1)-size);
	ty = y + (random(floatround(size * 2)+1)-size);
	tz = z + (random(floatround(size * 2)+1)-size);
}

stock GetRandomPointInRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,&Float:tx,&Float:ty){
	tx = random(floatround(floatsqroot(floatpower(minx-maxx,2)))+1)+minx;
	ty = random(floatround(floatsqroot(floatpower(miny-maxy,2)))+1)+miny;
}

stock GetRandomPointInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:tx,&Float:ty,&Float:tz){
	tx = random(floatround(floatsqroot(floatpower(minx-maxx,2)))+1)+minx;
	ty = random(floatround(floatsqroot(floatpower(miny-maxy,2)))+1)+miny;
	tz = random(floatround(floatsqroot(floatpower(minz-maxz,2)))+1)+minz;
}

stock ConvertMTARaceRotation(Float:rotation1,Float:rotation2,Float:rotation3,&Float:rx,&Float:ry,&Float:rz){
	rx = ShiftRadianToDegreeEx(rotation3);
	ry = ShiftRadianToDegreeEx(rotation2);
	rz = ShiftRadianToDegreeEx(rotation1);
}

stock ConvertToMTARaceRotation(Float:rx,Float:ry,Float:rz,&Float:rotation1,&Float:rotation2,&Float:rotation3){
	rotation3 = ShiftDegreeToRadianEx(rx);
	rotation2 = ShiftDegreeToRadianEx(ry);
	rotation1 = ShiftDegreeToRadianEx(rz);
}

stock GetMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:speed,&rtime=0){
	if(speed <= 0.0){
		rtime = 0x7F800000;
	} else {
		new Float:dist = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
		rtime = floatround((dist/speed)*1000.0);
	}
	return rtime;
}

stock Float:GetSpeedForMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:speed,rtime){
	if(rtime/1000.0 <= 0.0){
		speed = Float:0x7F800000;
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Warring: Get speed error, the wrong time.");
		}
		Update3DTrygWarringCount();
	} else {
		speed = (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz)/(rtime/1000.0));
	}
	return speed;
}

//GetVehicleRotation Created by IllidanS4
stock GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz){
	new Float:qw,Float:qx,Float:qy,Float:qz;
	GetVehicleRotationQuat(vehicleid,qw,qx,qy,qz);
	CompRotationFloat(asin(2*qy*qz-2*qx*qw),rx);
	CompRotationFloat(-atan2(qx*qz+qy*qw,0.5-qx*qx-qy*qy),ry);
	CompRotationFloat(-atan2(qx*qy+qz*qw,0.5-qx*qx-qz*qz),rz);
}

//GetVehicleUpVector by Shiska
stock GetVehicleUpVector(vehicleid,&Float:vx,&Float:vy,&Float:vz){
	new Float:qw,Float:qx,Float:qy,Float:qz;
	GetVehicleRotationQuat(vehicleid,qw,qx,qy,qz);
	qx *= -1, qy *= -1, qz *= -1;
	vx = 2.0*(qy*qw+qz*qx);
	vy = 2.0*(qz*qy-qx*qw);
	vz = 1.0-(2.0*(qx*qx+qy*qy));
}

stock GetVehicleUpPos(vehicleid,Float:radius,&Float:x,&Float:y,&Float:z){
	new Float:rx,Float:rz;
	GetVehicleUpVector(vehicleid,x,y,z);
	ShiftVectorToRotation(x,y,z,rx,rz);
	GetVehiclePos(vehicleid,x,y,z);
	GetPointInFront3D(x,y,z,rx,rz,radius,x,y,z);
}

stock GetVehicleDownPos(vehicleid,Float:radius,&Float:x,&Float:y,&Float:z){
	new Float:rx,Float:rz;
	GetVehicleUpVector(vehicleid,x,y,z);
	ShiftVectorToRotation(x,y,z,rx,rz);
	GetVehiclePos(vehicleid,x,y,z);
	GetPointInFront3D(x,y,z,CompRotationFloat(rx-180.0),rz,radius,x,y,z);
}

stock Float:GetPointInFrontOfVehicle2D(vehicleid,&Float:tx,&Float:ty,Float:radius){
	new Float:rx,Float:ry,Float:rz,Float:x,Float:y;
	GetVehiclePos(vehicleid,x,y,rz);
	GetVehicleRotation(vehicleid,rx,ry,rz);
	GetPointInFront2D(x,y,rz,radius,tx,ty);
	return rz;
}

stock GetPointInFrontOfVehicle3D(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
	new Float:ry,Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid,x,y,z);
	GetVehicleRotation(vehicleid,rx,ry,rz);
	GetPointInFront3D(x,y,z,rx,rz,radius,tx,ty,tz);
}

stock ShiftVectorToRotation(Float:vx,Float:vy,Float:vz,&Float:rx,&Float:rz){
	CompRotationFloat(-(acos(vz)-90.0),rx);
	CompRotationFloat((atan2(vy,vx)-90.0),rz);
}

stock GetPlayerCameraRotation(playerid,&Float:rx,&Float:rz){
	new Float:mx,Float:my,Float:mz;
	GetPlayerCameraFrontVector(playerid,mx,my,mz);
	CompRotationFloat(-(acos(mz)-90.0),rx);
	CompRotationFloat((atan2(my,mx)-90.0),rz);
}

stock GetPointInFrontOfCamera3D(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
	new Float:x,Float:y,Float:z;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPlayerCameraRotation(playerid,rx,rz);
	GetPointInFront3D(x,y,z,rx,rz,radius,tx,ty,tz);
}

stock bool:IsPlayerLookAtSky(playerid){
	new Float:rx,Float:rz;
	GetPlayerCameraRotation(playerid,rx,rz);
	if(rx > 0.0 && rx <= 90.0) return true;
	return false;
}

stock GetPointFor2Point2D(Float:x1,Float:y1,Float:x2,Float:y2,Float:percent_size,&Float:tx,&Float:ty){
	new Float:dist,Float:dest_dist,Float:rz;
	dist = GetDistanceBetweenPoints2D(x1,y1,x2,y2);
	dest_dist = (dist*(percent_size/100.0));
	GetRotationFor2Point2D(x1,y1,x2,y2,rz);
	GetPointInFront2D(x1,y1,rz,dest_dist,tx,ty);
}

stock GetPointFor2Point3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:percent_size,&Float:tx,&Float:ty,&Float:tz){
	new Float:dist,Float:dest_dist,Float:rx,Float:rz;
	dist = GetDistanceBetweenPoints3D(x1,y1,z1,x2,y2,z2);
	dest_dist = (dist*(percent_size/100.0));
	GetRotationFor2Point3D(x1,y1,z1,x2,y2,z2,rx,rz);
	GetPointInFront3D(x1,y1,z1,rx,rz,dest_dist,tx,ty,tz);
}

stock bool:IsPointBetween2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB){
	new Float:dAP = GetDistanceBetweenPoints2D(xA,yA,px,py),
		Float:dBP = GetDistanceBetweenPoints2D(xB,yB,px,py),
		Float:dAB = GetDistanceBetweenPoints2D(xA,yA,xB,yB);
	if(dAB == (dAP + dBP)) return true;
	return false;
}

stock bool:IsPointBetween2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB){
	new Float:dAP = GetDistanceBetweenPoints3D(xA,yA,zA,px,py,pz),
		Float:dBP = GetDistanceBetweenPoints3D(xB,yB,zB,px,py,pz),
		Float:dAB = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	if(dAB == (dAP + dBP)) return true;
	return false;
}

//Orig: Greg James - gjames@NVIDIA.com SRC:http://www.flipcode.com/archives/Fast_Point-In-Cylinder_Test.shtml
stock bool:IsPointInCylinder(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:size){
	new Float:pdx,Float:pdy,Float:pdz,Float:dot,Float:dsq,Float:lengthsq;
	
	pdx = px-xA;
	pdy = py-yA;
	pdz = pz-zA;
	
	dot = pdx*(xB-xA) + pdy*(yB-yA) + pdz*(zB-zA);
	
	lengthsq = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	lengthsq = lengthsq*lengthsq;
	if(lengthsq <= 0.0){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Warring: Invalid cylinder posision, identical points.");
		}
		Update3DTrygWarringCount();
		return false;
	} else if(size <= 0.0){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Warring: Invalid cylinder size.");
		}
		Update3DTrygWarringCount();
		return false;
	}
	if(dot < 0.0 || dot > lengthsq){
		return false;
	} else {
		dsq = (pdx*pdx + pdy*pdy + pdz*pdz) - dot*dot/lengthsq;
		if(dsq <= (size*size)){
			return true;
		}
	}
	return false;
}

stock bool:IsPointInCube(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy) && (z >= minz && z <= maxz)) return true;
	return false;
}

stock bool:IsPointInRectangle(Float:x,Float:y,Float:minx,Float:miny,Float:maxx,Float:maxy){
	if((x >= minx && x <= maxx) && (y >= miny && y <= maxy)) return true;
	return false;
}

//Polygon Test by RyDeR SRC:http://forum.sa-mp.com/showpost.php?p=1154971&postcount=1871 (Updated)
stock bool:IsPointInPolygon(Float:x,Float:y,Float:points[],maxpoints = sizeof(points)){
	new polygon_Sides = ((maxpoints - 2) / 2);
	if((maxpoints - 2) & 0b1 || polygon_Sides < 3) return false;
	
	new Float:polygon_Data[2][MAX_POLYGON_POINTS], cross_Total;
	
	for(new i = 0, j; i < maxpoints; i += 2, j++){
		polygon_Data[0][j] = points[i];
		polygon_Data[1][j] = points[i+1];
	}
	for(new i, j = polygon_Sides - 1; i < polygon_Sides; j = i, i++){
		if(polygon_Data[1][i] < y && polygon_Data[1][j] >= y || polygon_Data[1][j] < y && polygon_Data[1][i] >= y){
			if(polygon_Data[0][i] + (y - polygon_Data[1][i]) / (polygon_Data[1][j] - polygon_Data[1][i]) * (polygon_Data[0][j] - polygon_Data[0][i]) < x){
				cross_Total++;
			}
		}
	}
	return bool:(cross_Total & 0x1);
}

stock bool:IsPointInCircle(Float:px,Float:py,Float:x,Float:y,Float:size){
	if(GetDistanceBetweenPoints2D(x,y,px,py) <= size) return true;
	return false;
}

stock bool:IsPointInSphere(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:size){
	if(GetDistanceBetweenPoints3D(x,y,z,px,py,pz) <= size) return true;
	return false;
}

//Abyss Morgan Algorithm (False Ellipse Test 2D)
stock bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist){
	new Float:dAP = GetDistanceBetweenPoints2D(xA,yA,px,py),
		Float:dBP = GetDistanceBetweenPoints2D(xB,yB,px,py),
		Float:dAB = GetDistanceBetweenPoints2D(xA,yA,xB,yB);
	if(dAB <= (dAP + dBP) <= (dAB+(maxdist))) return true;
	return false;
}

//Abyss Morgan Algorithm (False Ellipse Test 3D)
stock bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist){
	new Float:dAP = GetDistanceBetweenPoints3D(xA,yA,zA,px,py,pz),
		Float:dBP = GetDistanceBetweenPoints3D(xB,yB,zB,px,py,pz),
		Float:dAB = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	if(dAB <= (dAP + dBP) <= (dAB+(maxdist))) return true;
	return false;
}

stock bool:IsPlayerInCircle(playerid,Float:x,Float:y,Float:size){
	new Float:px,Float:py,Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	return IsPointInCircle(px,py,x,y,size);
}

stock bool:IsPlayerInCylinder(playerid,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:size){
	new Float:px,Float:py,Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	return IsPointInCylinder(px,py,pz,xA,yA,zA,xB,yB,zB,size);
}

stock bool:IsPlayerInCylinderEx(playerid,Float:x,Float:y,Float:minz,Float:maxz,Float:size){
	new Float:px,Float:py,Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	return IsPointInCylinderEx(px,py,pz,x,y,minz,maxz,size);
}

stock bool:IsPlayerInSphere(playerid,Float:x,Float:y,Float:z,Float:size){
	new Float:px,Float:py,Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	return IsPointInSphere(px,py,pz,x,y,z,size);
}

stock bool:IsPlayerInRectangle(playerid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	new Float:px,Float:py,Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	return IsPointInRectangle(px,py,minx,miny,maxx,maxy);
}

stock bool:IsPlayerInCube(playerid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	new Float:px,Float:py,Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	return IsPointInCube(px,py,pz,minx,miny,minz,maxx,maxy,maxz);
}

stock bool:IsPlayerInPolygon(playerid,Float:points[],maxpoints = sizeof(points)){
	new Float:px,Float:py,Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	IsPointInPolygon(px,py,points,maxpoints);
}

stock bool:IsProbable(chance){
	if(chance <= 0) return false;
	if(chance >= 100) return true;
	if((random(100)+1) <= chance) return true;
	return false;
}

stock Float:GetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx,Float:my;
	GetPlayerPos(playerid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	return rz;
}

stock Float:SetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx,Float:my;
	GetPlayerPos(playerid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	SetPlayerFacingAngle(playerid,rz);
	return rz;
}

stock Float:GetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:x,Float:y;
	GetPlayerPos(playerid,mx,my,rz);
	GetPlayerPos(targetid,x,y,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	return rz;
}

stock Float:SetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:x,Float:y;
	GetPlayerPos(playerid,mx,my,rz);
	GetPlayerPos(targetid,x,y,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	SetPlayerFacingAngle(playerid,rz);
	return rz;
}

stock CreateDynamicExplosion(Float:x,Float:y,Float:z,type,Float:radius,worldid = -1,interiorid = -1,playerid = -1,Float:distance = 200.0){
	if(playerid == -1){
		for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
			if(IsPlayerConnected(i)){
				new Float:px, Float:py, Float:pz;
				if(IsPlayerInAnyVehicle(i)){
					GetVehiclePos(GetPlayerVehicleID(i),px,py,pz);
				} else {
					GetPlayerPos(i,px,py,pz);
				}
				if((GetPlayerInterior(i) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(i) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
					CreateExplosionForPlayer(i,x,y,z,type,radius);
				}
			}
		}
	} else {
		if(IsPlayerConnected(playerid)){
			new Float:px, Float:py, Float:pz;
			if(IsPlayerInAnyVehicle(playerid)){
				GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			} else {
				GetPlayerPos(playerid,px,py,pz);
			}
			if((GetPlayerInterior(playerid) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(playerid) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
				CreateExplosionForPlayer(playerid,x,y,z,type,radius);
			}
		}
	}
}

stock GetPlayerOrientationPos(playerid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
	new Float:x, Float:y, Float:z, Float:rz;
	GetPlayerPos(playerid,x,y,z);
	GetPlayerFacingAngle(playerid,rz);
	switch(orientation){
		case o_left: {
			GetPointInFront3D(x,y,z,0.0,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
		}
		case o_right: {
			GetPointInFront3D(x,y,z,0.0,CompRotationFloat(rz-90.0),distance,tx,ty,tz);
		}
		case o_up: {
			tx = x, ty = y, tz = z+distance;
		}
		case o_down: {
			tx = x, ty = y, tz = z-distance;
		}
		case o_front: {
			GetPointInFront3D(x,y,z,0.0,rz,distance,tx,ty,tz);
		}
		case o_back: {
			GetPointInFront3D(x,y,z,0.0,CompRotationFloat(rz+180.0),distance,tx,ty,tz);
		}
	}
}

stock GetVehicleOrientationPos(vehicleid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
	new Float:x, Float:y, Float:z,
		Float:rx, Float:ry, Float:rz;
	GetVehiclePos(vehicleid,x,y,z);
	GetVehicleRotation(vehicleid,rx,ry,rz); 
	switch(orientation){
		case o_left: {
			GetPointInFront3D(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
		}
		case o_right: {
			GetPointInFront3D(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
		}
		case o_up: {
			GetVehicleUpPos(vehicleid,distance,tx,ty,tz);
		}
		case o_down: {
			GetVehicleDownPos(vehicleid,distance,tx,ty,tz);
		}
		case o_front: {
			GetPointInFront3D(x,y,z,rx,rz,distance,tx,ty,tz);
		}
		case o_back: {
			GetPointInFront3D(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
		}
	}
}

stock GetObjectOrientationPos(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
	new Float:x, Float:y, Float:z,
		Float:rx, Float:ry, Float:rz;
	GetObjectPos(objectid,x,y,z);
	GetObjectRot(objectid,rx,ry,rz); 
	switch(orientation){
		case o_left: {
			GetPointInFront3D(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
		}
		case o_right: {
			GetPointInFront3D(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
		}
		case o_up: {
			GetPointInFront3D(x,y,z,CompRotationFloat(ry+90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
		}
		case o_down: {
			GetPointInFront3D(x,y,z,CompRotationFloat(ry-90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
		}
		case o_front: {
			GetPointInFront3D(x,y,z,rx,rz,distance,tx,ty,tz);
		}
		case o_back: {
			GetPointInFront3D(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
		}
	}
}

stock GetWeaponShotPos(playerid,hittype,&Float:fx,&Float:fy,&Float:fz){
	new Float:ox,Float:oy,Float:oz;
	switch(hittype){
		case BULLET_HIT_TYPE_VEHICLE, BULLET_HIT_TYPE_OBJECT, BULLET_HIT_TYPE_PLAYER_OBJECT, BULLET_HIT_TYPE_PLAYER: {
			GetPlayerLastShotVectors(playerid,ox,oy,oz,fx,fy,fz);
		}
	}
}

//Streamer Functions
#if defined Tryg3D_Streamer

	#define TRYG3D_GET_STREAMER_VERSION					(0xFFFFFFFF)
	
	#define Tryg3D_GetStreamerVersion()					(Streamer_IncludeFileVersion)
	#define Tryg3D_GetValidStreamerVersion()			(Tryg3D_StreamerVersion)
	
	stock bool:Tryg3D_IsValidStreamer(version){
		if(Tryg3D_GetStreamerVersion() < version) return false;
		return true;
	}

	stock Tryg3D_GetStreamerVersionName(name[], value = TRYG3D_GET_STREAMER_VERSION, maxdest = sizeof name){
		if(value == TRYG3D_GET_STREAMER_VERSION) value = Tryg3D_GetStreamerVersion();
		new ver_str[10];
		format(ver_str,sizeof(ver_str),"%06x",value);
		format(name,maxdest,"%d.%d.%dr%d",(ver_str[0]-48),(ver_str[1]-48),(ver_str[2]-48),(((ver_str[3]-48)*100) + ((ver_str[4]-48)*10) + (ver_str[5]-48)));
	}

	stock Tryg3D_CheckStreamerVersion(){
		if(!Tryg3D_IsValidStreamer(Tryg3D_GetValidStreamerVersion())){
			new str1[32], str2[32];
			Tryg3D_GetStreamerVersionName(str1,Tryg3D_GetStreamerVersion());
			Tryg3D_GetStreamerVersionName(str2,Tryg3D_GetValidStreamerVersion());
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				printf("[ADM] Warring: Your Streamer %s It is not compatible with this version 3DTryg, update your streamer to %s",str1,str2);
			}
			Update3DTrygWarringCount();
		}
	}

	stock GetDynamicObjectOrientationPos(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
		new Float:x, Float:y, Float:z,
			Float:rx, Float:ry, Float:rz;
		GetDynamicObjectPos(objectid,x,y,z);
		GetDynamicObjectRot(objectid,rx,ry,rz); 
		switch(orientation){
			case o_left: {
				GetPointInFront3D(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_right: {
				GetPointInFront3D(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_up: {
				GetPointInFront3D(x,y,z,CompRotationFloat(ry+90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_down: {
				GetPointInFront3D(x,y,z,CompRotationFloat(ry-90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_front: {
				GetPointInFront3D(x,y,z,rx,rz,distance,tx,ty,tz);
			}
			case o_back: {
				GetPointInFront3D(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
			}
		}
	}
	
	stock Float:GetDynamicObjectsDistance(objectid_a,objectid_b){
		new Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB;
		GetDynamicObjectPos(objectid_a,xA,yA,zA);
		GetDynamicObjectPos(objectid_b,xB,yB,zB);
		return GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	}
	
	stock Float:GetPlayerDynamicObjectDistance(playerid,objectid){
		new Float:x,Float:y,Float:z;
		GetDynamicObjectPos(objectid,x,y,z);
		return GetPlayerDistanceFromPoint(playerid,x,y,z);
	}

#endif

//MapAndreas Functions
#if (defined Tryg3D_MapAndreas || defined Tryg3D_ColAndreas)
	stock GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry){
		new Float:tpx1,Float:tpy1,Float:tpz1,
			Float:tpx2,Float:tpy2,Float:tpz2,
			Float:tmp;
		GetPointInFront2D(x,y,0.0,size,tpx1,tpy1);
		GetPointInFront2D(x,y,180.0,size,tpx2,tpy2);
		Tryg3DMapAndreasFindZ(tpx1,tpy1,tpz1);
		Tryg3DMapAndreasFindZ(tpx2,tpy2,tpz2);
		GetRotationFor2Point3D(tpx1,tpy1,tpz1,tpx2,tpy2,tpz2,rx,tmp);
		
		GetPointInFront2D(x,y,90.0,size,tpx1,tpy1);
		GetPointInFront2D(x,y,270.0,size,tpx2,tpy2);
		Tryg3DMapAndreasFindZ(tpx1,tpy1,tpz1);
		Tryg3DMapAndreasFindZ(tpx2,tpy2,tpz2);
		GetRotationFor2Point3D(tpx1,tpy1,tpz1,tpx2,tpy2,tpz2,ry,tmp);
	}
#endif

//ColAndreas Functions
#if defined Tryg3D_ColAndreas

	#define GET_COLANDREAS_VERSION						(0xFFFFFFFF)
	
	#define GetColAndreasVersion()						(COLANDREAS_VERSION)
	#define GetValidColAndreasVersion()					(Tryg3D_ColAndreasVersion)
	
	#define IsCollisionFlag(%0,%1)						((%0) & (%1))

	stock bool:IsValidColAndreas(version){
		if(GetColAndreasVersion() < version) return false;
		return true;
	}

	stock GetColAndreasVersionName(name[], value = GET_COLANDREAS_VERSION, maxdest = sizeof name){
		if(value == GET_COLANDREAS_VERSION) value = GetColAndreasVersion();
		format(name,maxdest,"%d.%d.%d",(value / 10000),((value % 10000) / 100),((value % 10000) % 100));
	}

	stock CheckColAndreasVersion(){
		if(!IsValidColAndreas(GetValidColAndreasVersion())){
			new str1[32], str2[32];
			GetColAndreasVersionName(str1,GetColAndreasVersion());
			GetColAndreasVersionName(str2,GetValidColAndreasVersion());
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				printf("[ADM] Warring: Your ColAndreas %s It is not compatible with this version 3DTryg, update your ColAndreas to %s",str1,str2);
			}
			Update3DTrygWarringCount();
		}
	}
	
	stock MovePointCol(Float:StartX,Float:StartY,Float:StartZ,Float:EndX,Float:EndY,Float:EndZ,&Float:x,&Float:y,&Float:z){
		CA_RayCastLine(StartX,StartY,StartZ,EndX,EndY,EndZ,x,y,z);
		if(x == 0.0) x = EndX;
		if(y == 0.0) y = EndY;
		if(z == 0.0) z = EndZ;
	}
	
	stock MovePointColCutLine(Float:SX,Float:SY,Float:SZ,Float:EX,Float:EY,Float:EZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0){
		new Float:radius, Float:rx, Float:rz;
		CA_RayCastLine(SX,SY,SZ,EX,EY,EZ,x,y,z);
		if(x == 0.0) x = EX;
		if(y == 0.0) y = EY;
		if(z == 0.0) z = EZ;
		radius = GetDistanceBetweenPoints3D(SX,SY,SZ,x,y,z);
		if(radius > 0.0){
			CompRotationFloat(-(acos((z-SZ)/radius)-90.0),rx);
			CompRotationFloat((atan2(y-SY,x-SX)-90.0),rz);
			if(radius-cut_size > 0.0) radius -= cut_size;
			GetPointInFront3D(SX,SY,SZ,rx,rz,radius,x,y,z);
		} else {
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Warring: Invalid resize line, identical points.");
			}
			Update3DTrygWarringCount();
		}
	}

	stock MovePointColCutLineEx(Float:SX,Float:SY,Float:SZ,Float:EX,Float:EY,Float:EZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0){
		new Float:radius, Float:rx, Float:rz;
		CA_RayCastLine(SX,SY,SZ,EX,EY,EZ,x,y,z);
		if(x == 0.0) x = EX;
		if(y == 0.0) y = EY;
		if(z == 0.0) z = EZ;
		radius = GetDistanceBetweenPoints3D(SX,SY,SZ,x,y,z);
		if(radius > 0.0){
			CompRotationFloat(-(acos((z-SZ)/radius)-90.0),rx);
			CompRotationFloat((atan2(y-SY,x-SX)-90.0),rz);
			if((radius-cut_size > cut_size) && (radius-cut_size > 0.0)){
				radius -= cut_size;
			} else {
				radius = 0.0001;
			}
			GetPointInFront3D(SX,SY,SZ,rx,rz,radius,x,y,z);
		} else {
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Warring: Invalid resize line, identical points.");
			}
			Update3DTrygWarringCount();
		}
	}
	
	//GetPointInFront3D (ColAndreas)
	stock GetPointInFront3DCol(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
		tx = x + (radius * floatsin(rx+90.0,degrees) * floatcos(rz+90.0,degrees));
		ty = y + (radius * floatsin(rx+90.0,degrees) * floatsin(rz+90.0,degrees));
		tz = z + (radius * floatcos(-rx+90.0,degrees));
		MovePointCol(x,y,z,tx,ty,tz,tx,ty,tz);
	}
	
	//GetPointInFrontOfPlayer (ColAndreas)
	stock Float:GetPointInFrontOfPlayerCol(playerid,&Float:tx,&Float:ty,Float:radius){
		new Float:rz,Float:z;
		GetPlayerPos(playerid,tx,ty,z);
		GetPlayerFacingAngle(playerid,rz);
		if(IsPlayerInAnyVehicle(playerid)){
			GetVehicleZAngle(GetPlayerVehicleID(playerid),rz);
		}
		GetPointInFront3DCol(tx,ty,z,0.0,rz,radius,tx,ty,z);
		return rz;
	}

	//GetPointInFrontOfCamera2D (ColAndreas)
	stock Float:GetPointInFrontOfCamera2DCol(playerid,&Float:tx,&Float:ty,Float:radius){
		new Float:x,Float:y,Float:z,Float:rz;
		GetPlayerCameraPos(playerid,x,y,z);
		GetPlayerCameraZAngle(playerid,rz);
		GetPointInFront3DCol(x,y,z,0.0,rz,radius,tx,ty,z);
		return rz;
	}

	//GetPointInFrontOfCamera3D (ColAndreas)
	stock GetPointInFrontOfCamera3DCol(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
		new Float:x,Float:y,Float:z;
		GetPlayerCameraPos(playerid,x,y,z);
		GetPlayerCameraRotation(playerid,rx,rz);
		GetPointInFront3DCol(x,y,z,rx,rz,radius,tx,ty,tz);
	}
	
	
	//GetPointInFrontOfVehicle2D (ColAndreas)
	stock Float:GetPointInFrontOfVehicle2DCol(vehicleid,&Float:tx,&Float:ty,Float:radius){
		new Float:rx,Float:ry,Float:rz,Float:x,Float:y,Float:z;
		GetVehiclePos(vehicleid,x,y,z);
		GetVehicleRotation(vehicleid,rx,ry,rz);
		GetPointInFront3DCol(x,y,z,0.0,rz,radius,tx,ty,z);
		return rz;
	}

	//GetPointInFrontOfVehicle3D (ColAndreas)
	stock GetPointInFrontOfVehicle3DCol(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
		new Float:ry,Float:x,Float:y,Float:z;
		GetVehiclePos(vehicleid,x,y,z);
		GetVehicleRotation(vehicleid,rx,ry,rz);
		GetPointInFront3DCol(x,y,z,rx,rz,radius,tx,ty,tz);
	}

	stock Float:UndergroundFindZ(Float:x,Float:y,&Float:z=0.0){
		z = 0.0;
		CA_RayCastLine(x,y,-0.002,x,y,-100.0,x,y,z);
		return z;
	}

	stock Float:InteriorFindZ(Float:px,Float:py,Float:pz=1000.0,Float:size=2.0,&Float:z=0.0){
		z = 0.0;
		CA_RayCastLine(px,py,pz+size,px,py,pz-100.0,px,py,z);
		return z;
	}

	stock bool:IsPointInWater(Float:x,Float:y,Float:z=0.0){
		if(z > 0.0) return false;
		new Float:tmpzA, Float:tmpzB;
		Tryg3DMapAndreasFindZ(x,y,tmpzA);
		UndergroundFindZ(x,y,tmpzB);
		if((z >= tmpzB) && (tmpzB < 0.0) && (tmpzA > -0.001 && tmpzA < 0.001)) return true;
		return false;
	}

	stock bool:IsPointInUnderwater(Float:x,Float:y,Float:z){
		if(IsPointInWater(x,y,z) && (z < -1.0)) return true;
		return false;
	}
	
	stock bool:IsPointInUnderground(Float:x,Float:y,Float:z){
		new Float:tmpzA;
		Tryg3DMapAndreasFindZ(x,y,tmpzA);
		if(z < tmpzA && !IsPointInWater(x,y,z)) return true;
		return false;
	}

	stock bool:IsPointInAir(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2){
		new Float:tmpzA;
		if(interior){
			InteriorFindZ(x,y,z,2.0,tmpzA);
		} else {
			Tryg3DMapAndreasFindZ(x,y,tmpzA);
		}
		if(z >= tmpzA+max_distance) return true;
		return false;
	}

	stock bool:IsPointInGround(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2){
		if(z <= 0.0) return false;
		new Float:tmpzA;
		if(interior){
			InteriorFindZ(x,y,z,2.0,tmpzA);
		} else {
			Tryg3DMapAndreasFindZ(x,y,tmpzA);
		}
		if(z <= tmpzA+max_distance) return true;
		return false;
	}
	
	stock GetPlayerOrientationPosCol(playerid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
		new Float:x, Float:y, Float:z, Float:rz;
		GetPlayerPos(playerid,x,y,z);
		GetPlayerFacingAngle(playerid,rz);
		switch(orientation){
			case o_left: {
				GetPointInFront3DCol(x,y,z,0.0,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_right: {
				GetPointInFront3DCol(x,y,z,0.0,CompRotationFloat(rz-90.0),distance,tx,ty,tz);
			}
			case o_up: {
				GetPointInFront3DCol(x,y,z,90.0,0.0,distance,tx,ty,tz);
			}
			case o_down: {
				GetPointInFront3DCol(x,y,z,270.0,0.0,distance,tx,ty,tz);
			}
			case o_front: {
				GetPointInFront3DCol(x,y,z,0.0,rz,distance,tx,ty,tz);
			}
			case o_back: {
				GetPointInFront3DCol(x,y,z,0.0,CompRotationFloat(rz+180.0),distance,tx,ty,tz);
			}
		}
	}

	stock GetVehicleOrientationPosCol(vehicleid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
		new Float:x, Float:y, Float:z,
			Float:rx, Float:ry, Float:rz;
		GetVehiclePos(vehicleid,x,y,z);
		GetVehicleRotation(vehicleid,rx,ry,rz); 
		switch(orientation){
			case o_left: {
				GetPointInFront3DCol(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_right: {
				GetPointInFront3DCol(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_up: {
				GetVehicleUpPos(vehicleid,distance,tx,ty,tz);
				MovePointCol(x,y,z,tx,ty,tz,tx,ty,tz);
			}
			case o_down: {
				GetVehicleDownPos(vehicleid,distance,tx,ty,tz);
				MovePointCol(x,y,z,tx,ty,tz,tx,ty,tz);
			}
			case o_front: {
				GetPointInFront3DCol(x,y,z,rx,rz,distance,tx,ty,tz);
			}
			case o_back: {
				GetPointInFront3DCol(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
			}
		}
	}
	
	stock GetObjectOrientationPosCol(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
		new Float:x, Float:y, Float:z,
			Float:rx, Float:ry, Float:rz;
		GetObjectPos(objectid,x,y,z);
		GetObjectRot(objectid,rx,ry,rz); 
		switch(orientation){
			case o_left: {
				GetPointInFront3DCol(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_right: {
				GetPointInFront3DCol(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_up: {
				GetPointInFront3DCol(x,y,z,CompRotationFloat(ry+90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_down: {
				GetPointInFront3DCol(x,y,z,CompRotationFloat(ry-90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
			}
			case o_front: {
				GetPointInFront3DCol(x,y,z,rx,rz,distance,tx,ty,tz);
			}
			case o_back: {
				GetPointInFront3DCol(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
			}
		}
	}

	//Streamer + Colandreas Functions
	#if defined Tryg3D_Streamer
		stock GetDynamicObjectOrientPosCol(objectid,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
			new Float:x, Float:y, Float:z,
				Float:rx, Float:ry, Float:rz;
			GetDynamicObjectPos(objectid,x,y,z);
			GetDynamicObjectRot(objectid,rx,ry,rz); 
			switch(orientation){
				case o_left: {
					GetPointInFront3DCol(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				}
				case o_right: {
					GetPointInFront3DCol(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				}
				case o_up: {
					GetPointInFront3DCol(x,y,z,CompRotationFloat(ry+90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				}
				case o_down: {
					GetPointInFront3DCol(x,y,z,CompRotationFloat(ry-90.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				}
				case o_front: {
					GetPointInFront3DCol(x,y,z,rx,rz,distance,tx,ty,tz);
				}
				case o_back: {
					GetPointInFront3DCol(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
				}
			}
		}
	#endif
	
	stock GetPlayerCollisionFlags(playerid){
		new Float:x, Float:y, Float:z, bool:isinterior = false, flag_value;
		GetPlayerPos(playerid,x,y,z);
		if(GetPlayerInterior(playerid) != 0){
			flag_value |= POSITION_FLAG_INTERIOR;
			isinterior = true;
		} else {
			flag_value |= POSITION_FLAG_WORLD;
		}
		if(IsPointInUnderwater(x,y,z)){
			flag_value |= POSITION_FLAG_WATER;
			flag_value |= POSITION_FLAG_UNDERWATER;
		} else if(IsPointInWater(x,y,z)){
			flag_value |= POSITION_FLAG_WATER;
		} else if(IsPointInAir(x,y,z,isinterior,2.2)){
			flag_value |= POSITION_FLAG_AIR;
		} else if(IsPointInUnderground(x,y,z)){
			flag_value |= POSITION_FLAG_UNDERGROUND;
		} else {
			flag_value |= POSITION_FLAG_GROUND;
		}
		return flag_value;
	}
	
	stock bool:IsBetweenPlayersIsWall(playerid,targetid){
		new Float:xA,Float:yA,Float:zA,
			Float:xB,Float:yB,Float:zB,
			Float:xC,Float:yC,Float:zC;
		GetPlayerPos(playerid,xA,yA,zA);
		GetPlayerPos(targetid,xB,yB,zB);
		MovePointCol(xA,yA,zA,xB,yB,zB,xC,yC,zC);
		if(xB != xC || yB != yC || zB != zC) return true;
		return false;
	}
	
	stock bool:IsBetweenPlayerToPointIsWall(playerid,Float:x,Float:y,Float:z){
		new Float:xA,Float:yA,Float:zA,
			Float:xC,Float:yC,Float:zC;
		GetPlayerPos(playerid,xA,yA,zA);
		MovePointCol(xA,yA,zA,x,y,z,xC,yC,zC);
		if(x != xC || y != yC || z != zC) return true;
		return false;
	}
	
	#define GetXYInFrontOfPlayerCol						GetPointInFrontOfPlayerCol
	#define GetPointInFrontCol							GetPointInFront3DCol
	#define GetPointInFrontOfCameraCol					GetPointInFrontOfCamera3DCol
	
	#define GetPointInFrontOnGround(%0,%1,%2,%3,%4,%5,%6,%7,%8) GetPointInFront3DCol((%0),(%1),(%2),(%3),(%4),(%8),(%5),(%6),(%7))

#elseif defined Tryg3D_MapAndreas
	stock GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance){
		new Float:tmpz;
		Tryg3DMapAndreasFindZ(x,y,tmpz);
		new Float:radius = GetDistanceBetweenPoints3D(x,y,z,x,y,tmpz),
			Float:cos = floatcos(rx+90.0,degrees),
			Float:dist;
		if(cos == 0.0){
			dist = radius;
		} else {
			dist = floatabs(radius/cos);
		}
		if((dist > max_distance) || (rx >= 0.0 && rx <= 180.0)){
			dist = max_distance;
		}
		GetPointInFront3D(x,y,z,rx,rz,dist,tx,ty,tz);
		if((dist > max_distance) || (rx >= 0.0 && rx <= 180.0)){

		} else {
			Tryg3DMapAndreasFindZ(tx,ty,tz);
		}
	}
	
	stock bool:IsPointInWater(Float:x,Float:y,Float:z=0.0){
		if(z > 0.0) return false;
		new Float:tmpz;
		Tryg3DMapAndreasFindZ(x,y,tmpz);
		if(tmpz == 0.0) return true;
		return false;
	}
	
#endif

//YSF Functions
#if defined Tryg3D_YSF

	#define GetPlayerHydraReactorRX(%0) 				CompRotationFloat((GetPlayerHydraReactorAngle(%0)/55.5555555))
	
	stock bool:IsPlayerHydraReactorBoost(playerid){
		if(GetPlayerHydraReactorAngle(playerid) == 0) return true;
		return false;
	}
	
	stock GetPlayerRotation(playerid,&Float:rx,&Float:ry,&Float:rz){
		new Float:qw,Float:qx,Float:qy,Float:qz;
		GetPlayerRotationQuat(playerid,qw,qx,qy,qz);
		CompRotationFloat(asin(2*qy*qz-2*qx*qw),rx);
		CompRotationFloat(-atan2(qx*qz+qy*qw,0.5-qx*qx-qy*qy),ry);
		CompRotationFloat(-atan2(qx*qy+qz*qw,0.5-qx*qx-qz*qz),rz);
	}
	
	//YSF Timeline Sync (Beta Version)
	#if defined ENABLE_3D_TRYG_TIMELINE_SYNC
		#define GetPlayerTimeline(%0)					GetPVarInt((%0),"PlayerTimeline")

		stock UpdatePlayerTimeline(playerid){
			new tline = GetPlayerTimeline(playerid), pskin = GetPlayerSkin(playerid), pcolor = GetPlayerColor(playerid),
				Float:px, Float:py, Float:pz;
			GetPlayerPos(playerid,px,py,pz);
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
				if(i != playerid){
					if(tline == GetPlayerTimeline(i)){
						SetPlayerSkinForPlayer(i,playerid,pskin);
						SetPlayerSkinForPlayer(playerid,i,GetPlayerSkin(i));
						
						ShowPlayerForPlayer(i,playerid);
						ShowPlayerForPlayer(playerid,i);
						
						if(GetPlayerDistanceFromPoint(i,px,py,pz) <= 300.0){
							SetPlayerMarkerForPlayer(i,playerid,pcolor);
							SetPlayerMarkerForPlayer(playerid,i,GetPlayerColor(i));
						}
					} else {
						HidePlayerForPlayer(i,playerid);
						HidePlayerForPlayer(playerid,i);
						
						SetPlayerMarkerForPlayer(i,playerid,(pcolor & 0xFFFFFF00));
						SetPlayerMarkerForPlayer(playerid,i,(GetPlayerColor(i) & 0xFFFFFF00));
					}
				}
			}
		}

		stock SetPlayerTimeline(playerid,timeline){
			SetPVarInt(playerid,"PlayerTimeline",timeline);
			UpdatePlayerTimeline(playerid);
		}

		stock GetPlayerPos4D(playerid,&Float:x,&Float:y,&Float:z,&timeline){
			GetPlayerPos(playerid,x,y,z);
			timeline = GetPlayerTimeline(playerid);
		}

		stock SetPlayerPos4D(playerid,Float:x,Float:y,Float:z,timeline=0){
			SetPlayerPos(playerid,x,y,z);
			if(GetPlayerTimeline(playerid) != timeline) SetPlayerTimeline(playerid,timeline);
		}
		
		stock CreateDynamicExplosion4D(Float:x,Float:y,Float:z,type,Float:radius,worldid = -1,interiorid = -1,timeline = -1,playerid = -1,Float:distance = 200.0){
			if(playerid == -1){
				for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
					if(IsPlayerConnected(i)){
						new Float:px, Float:py, Float:pz;
						if(IsPlayerInAnyVehicle(i)){
							GetVehiclePos(GetPlayerVehicleID(i),px,py,pz);
						} else {
							GetPlayerPos(i,px,py,pz);
						}
						if(GetPlayerTimeline(i) == timeline || timeline == -1){
							if((GetPlayerInterior(i) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(i) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
								CreateExplosionForPlayer(i,x,y,z,type,radius);
							}
						}
					}
				}
			} else {
				if(IsPlayerConnected(playerid)){
					new Float:px, Float:py, Float:pz;
					if(IsPlayerInAnyVehicle(playerid)){
						GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
					} else {
						GetPlayerPos(playerid,px,py,pz);
					}
					if((GetPlayerInterior(playerid) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(playerid) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
						CreateExplosionForPlayer(playerid,x,y,z,type,radius);
					}
				}
			}
		}
	
		//Hook: OnPlayerStreamIn
		public OnPlayerStreamIn(playerid,forplayerid){
			if(GetPlayerTimeline(playerid) == GetPlayerTimeline(forplayerid)){
				ShowPlayerForPlayer(forplayerid,playerid);
				ShowPlayerForPlayer(playerid,forplayerid);
				
				SetPlayerSkinForPlayer(forplayerid,playerid,GetPlayerSkin(playerid));
				SetPlayerSkinForPlayer(playerid,forplayerid,GetPlayerSkin(forplayerid));
				
				SetPlayerMarkerForPlayer(forplayerid,playerid,GetPlayerColor(playerid));
				SetPlayerMarkerForPlayer(playerid,forplayerid,GetPlayerColor(forplayerid));
			} else {
				HidePlayerForPlayer(forplayerid,playerid);
				HidePlayerForPlayer(playerid,forplayerid);
				
				SetPlayerMarkerForPlayer(forplayerid,playerid,(GetPlayerColor(playerid) & 0xFFFFFF00));
				SetPlayerMarkerForPlayer(playerid,forplayerid,(GetPlayerColor(forplayerid) & 0xFFFFFF00));
			}
			#if defined _3DTryg_OnPlayerStreamIn
				_3DTryg_OnPlayerStreamIn(playerid,forplayerid);
			#endif
			return 1;
		}
	
		#if defined _ALS_OnPlayerStreamIn
			#undef OnPlayerStreamIn
		#else
			#define _ALS_OnPlayerStreamIn
		#endif
		#define OnPlayerStreamIn _3DTryg_OnPlayerStreamIn
		#if defined _3DTryg_OnPlayerStreamIn
			forward _3DTryg_OnPlayerStreamIn(playerid,forplayerid);
		#endif


		//Hook: OnPlayerConnect
		public OnPlayerConnect(playerid){
			SetPVarInt(playerid,"PlayerTimeline",0);
			#if defined _3DTryg_OnPlayerConnect
				_3DTryg_OnPlayerConnect(playerid);
			#endif
			return 1;
		}

		#if defined _ALS_OnPlayerConnect
			#undef OnPlayerConnect
		#else
			#define _ALS_OnPlayerConnect
		#endif
		#define OnPlayerConnect _3DTryg_OnPlayerConnect
		#if defined _3DTryg_OnPlayerConnect
			forward _3DTryg_OnPlayerConnect(playerid);
		#endif

		//Hook: OnPlayerSpawn
		public OnPlayerSpawn(playerid){
			UpdatePlayerTimeline(playerid);
			#if defined _3DTryg_OnPlayerSpawn
				_3DTryg_OnPlayerSpawn(playerid);
			#endif
			return 1;
		}

		#if defined _ALS_OnPlayerSpawn
			#undef OnPlayerSpawn
		#else
			#define _ALS_OnPlayerSpawn
		#endif
		#define OnPlayerSpawn _3DTryg_OnPlayerSpawn
		#if defined _3DTryg_OnPlayerSpawn
			forward _3DTryg_OnPlayerSpawn(playerid);
		#endif
		
	#endif
#endif

#if (defined Tryg3D_MapAndreas || defined Tryg3D_ColAndreas)
	stock bool:IsPointInWaterFrontOfPlayer(playerid,Float:radius){
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid,x,y,z);
		GetPointInFrontOfPlayer(playerid,x,y,radius);
		#if defined Tryg3D_ColAndreas
			return IsPointInWater(x,y,0.0);
		#else
			new Float:tmpz;
			Tryg3DMapAndreasFindZ(x,y,tmpz);
			if(tmpz <= 0.0) return true;
			return false;
		#endif
	}
#endif

#define GetXYInFrontOfPlayer							GetPointInFrontOfPlayer
#define GetPointInFront									GetPointInFront3D
#define GetPointInFrontOfCamera							GetPointInFrontOfCamera3D
#define GetDistanceBetweenPoints						GetDistanceBetweenPoints3D
#define CompressRotation								CompRotation
#define CompressRotationFloat							CompRotationFloat
#define GetXYZInFrontOfVehicle(%0,%1,%2,%3,%4) 			GetPointInFrontOfVehicle3D((%0),(%2),(%3),(%4),(%1))
#define GetVehicleAngle									GetVehicleRotation
#define Get3DTrygPrecision								Get3DTrygModules

#if !defined USE_OLD_PROTOTYPE_FUNCTION
	
	#if defined GetAngle
		#error [ADM] GetAngle is old prototype. Use GetPlayerTargetAngle / SetPlayerTargetAngle / GetRotationFor2Point2D
	#endif
	
#endif

/****************************************************************************************************
 *                                                                                                  *
 * FilterScript/GameMode Init Hook                                                                  *
 *                                                                                                  *
 ****************************************************************************************************/

new bool:CRC_3DTryg = true;

#if defined Tryg3D_ColAndreas
	
	stock bool:Tryg3D_IsColAndreasInit(){
		new Float:mapunit;
		CA_FindZ_For2DCoord(0.0,0.0,mapunit);
		if(mapunit <= 0.0) return false;
		return true;
	}

	stock Tryg3D_SafeColAndreasInit(){
		//check ColAndreas Init
		new bool:ColAndreasLastStat = false;
		if(!Tryg3D_IsColAndreasInit()){
			CA_Init();
			ColAndreasLastStat = true;
		}
		if(!Tryg3D_IsColAndreasInit()){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: ColAndreas failed to initiated.");
				print("[ADM] Error: Cannot load /scriptfiles/colandreas/ColAndreas.cadb");
				Update3DTrygErrorCount();
			}
		} else {
			if(ColAndreasLastStat){
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Info: ColAndreas successfully init.");
				}
			}
		}
	}
	
	#define IsColAndreasInit							Tryg3D_IsColAndreasInit
	#define SafeColAndreasInit 							Tryg3D_SafeColAndreasInit
	
#endif

#if defined Tryg3D_MapAndreas

	stock bool:Tryg3D_IsMapAndreasInit(){
		new Float:mapunit;
		MapAndreas_FindZ_For2DCoord(0.0,0.0,mapunit);
		if(mapunit <= 0.0) return false;
		return true;
	}

	stock Tryg3D_SafeMapAndreasInit(mode = MAP_ANDREAS_MODE_FULL, name[]="", len=sizeof(name)){
		//check MapAndreas Init
		new bool:MapAndreasLastStat = false;
		if(!Tryg3D_IsMapAndreasInit()){
			MapAndreas_Init(mode,name,len);
			MapAndreasLastStat = true;
		}
		if(!Tryg3D_IsMapAndreasInit()){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: MapAndreas failed to initiated.");
				print("[ADM] Error: Cannot load /scriptfiles/SAfull.hmap");
				Update3DTrygErrorCount();
			}
		} else {
			if(MapAndreasLastStat){
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Info: MapAndreas successfully init.");
				}
			}
		}
	}
	
#endif

stock Tryg3DInit(){
	#if defined Tryg3D_ColAndreas
		Tryg3D_SafeColAndreasInit();
	#elseif defined Tryg3D_MapAndreasEx
		Tryg3D_SafeMapAndreasInit(MAP_ANDREAS_MODE_FULL);
	#elseif defined Tryg3D_MapAndreas
		Tryg3D_SafeMapAndreasInit(MAP_ANDREAS_MODE_FULL);
	#else
		
	#endif
}

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_3DTryg){ CRC_3DTryg = false; } else return 1; //Init Engine
	#if ((!defined DISABLE_3D_TRYG_CHECK) && (defined Tryg3D_ColAndreas) && (COLANDREAS_VERSION != 0))
		CheckColAndreasVersion();
	#endif
	#if !defined DISABLE_3D_TRYG_INIT
		Tryg3DInit();
	#endif
	#if ((defined Tryg3D_YSF) && (defined ENABLE_3D_TRYG_TIMELINE_SYNC))
		if(GetSVarInt("ADM:3DTryg:YSF:TIMELINE") == 0){
			SetSVarInt("ADM:3DTryg:YSF:TIMELINE",1);
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Info: YSF Timeline Sync successfully init.");
			}
		}
	#endif
	#if (!defined DISABLE_3D_TRYG_CHECK && defined Tryg3D_Streamer)
		Tryg3D_CheckStreamerVersion();
	#endif
	#if defined _3DTryg_OnFilterScriptInit
		_3DTryg_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit _3DTryg_OnFilterScriptInit
#if defined _3DTryg_OnFilterScriptInit
	forward _3DTryg_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_3DTryg){ CRC_3DTryg = false; } else return 1; //Init Engine
	#if ((!defined DISABLE_3D_TRYG_CHECK) && (defined Tryg3D_ColAndreas) && (COLANDREAS_VERSION != 0))
		CheckColAndreasVersion();
	#endif
	#if !defined DISABLE_3D_TRYG_INIT
		Tryg3DInit();
	#endif
	#if ((defined Tryg3D_YSF) && (defined ENABLE_3D_TRYG_TIMELINE_SYNC))
		if(GetSVarInt("ADM:3DTryg:YSF:TIMELINE") == 0){
			SetSVarInt("ADM:3DTryg:YSF:TIMELINE",1);
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Info: YSF Timeline Sync successfully init.");
			}
		}
	#endif
	#if (!defined DISABLE_3D_TRYG_CHECK && defined Tryg3D_Streamer)
		Tryg3D_CheckStreamerVersion();
	#endif
	#if defined _3DTryg_OnGameModeInit
		_3DTryg_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit _3DTryg_OnGameModeInit
#if defined _3DTryg_OnGameModeInit
	forward _3DTryg_OnGameModeInit();
#endif


#undef Update3DTrygErrorCount
#undef Update3DTrygWarringCount

//EOF
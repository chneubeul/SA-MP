/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                       3D Tryg Functions                                                        *
 *                                                                                                                                *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                         *
 *                                                                                                                                *
 * Plugins: MapAndreas, ColAndreas                                                                                                *
 * Modules: None                                                                                                                  *
 *                                                                                                                                *
 * File Version: 2.6.6                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * MapAndreas Version: 1.2.1                                                                                                      *
 * ColAndreas Version: 1.4.0                                                                                                      *
 *                                                                                                                                *
 * 3DTryg Precision List:                                                                                                         *
 * 1. 3D:ColAndreas   - The most accurate precision with ColAndreas plugin.                                                       *
 * 2. 3D:MapAndreasEx - Average precision MapAndreas plugin + MapAndreasEx Module.                                                *
 * 3. 3D:MapAndreas   - Average precision MapAndreas plugin.                                                                      *
 * 4. 3D:Standard     - The default precision, lack of special functions.                                                         *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * Get3DTrygPrecision();                                                                                                          *
 * Float:sqrtN(Float:value,Float:exponent);                                                                                       *
 * abs(value);                                                                                                                    *
 * power(value,Float:exponent);                                                                                                   *
 * Float:ctg(Float:value,anglemode:mode=radian);                                                                                  *
 * Float:secans(Float:value,anglemode:mode=radian);                                                                               *
 * Float:cosecans(Float:value,anglemode:mode=radian);                                                                             *
 * single_clock(max,id);                                                                                                          *
 * even_clock(max,id);                                                                                                            *
 * uneven_clock(max,id);                                                                                                          *
 * IsEven(value);                                                                                                                 *
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
 * GetRandomPointInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:x,&Float:y,&Float:z);            *
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
 * bool:IsPointInSphere(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:size);                                           *
 * bool:IsPointInRectangle(Float:x,Float:y,Float:minx,Float:miny,Float:maxx,Float:maxy);                                          *
 * bool:IsPointInCube(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                 *
 * bool:IsPointInPolygon(Float:x,Float:y,{Float,_}:...);                                                                          *
 * bool:IsProbable(chance);                                                                                                       *
 * Float:CalculatePercent(Float:value,Float:maxvalue);                                                                            *
 * Float:GetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0);                                                            *
 * Float:SetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0);                                                            *
 *                                                                                                                                *
 * Symbols:                                                                                                                       *
 * FLOAT_PI - pi constant value                                                                                                   *
 *                                                                                                                                *
 * MapAndreas Functions:                                                                                                          *
 * Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0);                                                                           *
 * GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry);                                                             *
 * GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance);           *
 * bool:IsPointInWaterFrontOfPlayer(playerid,Float:radius);                                                                       *
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
 * Tryg3DMapAndreasFindZ      -> CA_FindZ_For2DCoord / MapAndreasFindZ / MapAndreas_FindZ_For2DCoord                              *
 *                                                                                                                                *
 * Old prototype:                                                                                                                 *
 * GetAngle                   -> GetPlayerTargetAngle / SetPlayerTargetAngle / GetRotationFor2Point2D                             *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v2.6.6
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v2.6.6
#elseif (Tryg3D_Version < 20606)
	#error [ADM] Update you 3DTryg.inc to v2.6.6
#endif
*/

#if defined _3D_Tryg
	#endinput
#endif
#define _3D_Tryg

#define Tryg3D_Version									(20606) //a.b.c 10000*a+100*b+c



//Detect ColAndreas
#if defined COLANDREAS
	#define Tryg3D_ColAndreas
	#define Tryg3D_ColAndreasVersion					(10400) //a.b.c 10000*a+100*b+c
#endif

#if !defined COLANDREAS_VERSION
	#define COLANDREAS_VERSION							(0)
#endif

//Detect MapAndreas
#if defined MapAndreas_FindZ_For2DCoord
	#define Tryg3D_MapAndreas
	#define Tryg3D_MapAndreasVersion					(10201) //a.b.c 10000*a+100*b+c
#endif

//Detect MapAndreasEx
#if defined _Map_Andreas_Ex
	#define Tryg3D_MapAndreasEx
#endif

#if (!defined Tryg3D_MapAndreasEx && defined Tryg3D_MapAndreas)
	//Auto Create MapAndreasEx
	#define IsMapAndreasInit			Tryg3D_IsMapAndreasInit
	#define SafeMapAndreasInit			Tryg3D_SafeMapAndreasInit
	
	stock Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0){
		if(x <= -3000.0 || x >= 3000.0 || y <= -3000.0 || y >= 3000.0){
			z = 0.0;
		} else {
			MapAndreas_FindZ_For2DCoord(x,y,z);
		}
		return z;
	}
	
	#define Tryg3D_MapAndreasEx
	
#endif

//Define Precision
#if defined Tryg3D_ColAndreas
	#define Tryg3DMapAndreasFindZ						CA_FindZ_For2DCoord
	#define Tryg3DPrecision								"3D:ColAndreas"
#elseif defined Tryg3D_MapAndreasEx
	#define Tryg3DMapAndreasFindZ						MapAndreasFindZ
	#define Tryg3DPrecision								"3D:MapAndreasEx"
#elseif defined Tryg3D_MapAndreas
	#define Tryg3DMapAndreasFindZ						MapAndreas_FindZ_For2DCoord
	#define Tryg3DPrecision								"3D:MapAndreas"
#else
	#define Tryg3DPrecision								"3D:Standard"
#endif

#define Get3DTrygPrecision()							(Tryg3DPrecision)

#if !defined FLOAT_PI
	#define FLOAT_PI		 							(3.14159265358979323846)
#endif

#define MAX_POLYGON_POINTS 								(32)

#if defined Tryg3D_ColAndreas
	#define POSITION_FLAG_WORLD							(0b00000001)
	#define POSITION_FLAG_INTERIOR						(0b00000010)
	#define POSITION_FLAG_AIR							(0b00000100)
	#define POSITION_FLAG_GROUND						(0b00001000)
	#define POSITION_FLAG_WATER							(0b00010000)
	#define POSITION_FLAG_UNDERWATER					(0b00100000)
	#define POSITION_FLAG_UNDERGROUND					(0b01000000)
#endif

#define ctg(%0,%1)										(1.0/floattan((%0),(%1)))
#define secans(%0,%1)									(1.0/floatcos((%0),(%1)))
#define cosecans(%0,%1)									(1.0/floatsin((%0),(%1)))
#define abs(%0)											(((%0) < 0)?(-(%0)):((%0)))

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

//old code version
stock GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty){
	tx = x + (radius*floatsin(-rz,degrees));
	ty = y + (radius*floatcos(-rz,degrees));
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

stock GetPointInFrontOfCamera3D(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
	new Float:x,Float:y,Float:z;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPlayerCameraRotation(playerid,rx,rz);
	GetPointInFront3D(x,y,z,rx,rz,radius,tx,ty,tz);
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
	}
}

//random clock pos
stock GetRandomClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0){
	new rand = random(360);
	if(rz == -1000.0) rz = rand;
	GetPointInFront3D(x,y,z,0.0,rz,radius,tx,ty,tz);
	CompRotationFloat(rz-180,trz);
}

stock GetRandomPointInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:x,&Float:y,&Float:z){
	x = random(floatround(floatsqroot(floatpower(minx-maxx,2)))+1)+minx;
	y = random(floatround(floatsqroot(floatpower(miny-maxy,2)))+1)+miny;
	z = random(floatround(floatsqroot(floatpower(minz-maxz,2)))+1)+minz;
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
	} else {
		speed = (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz)/(rtime/1000.0));
	}
	return speed;
}

//GetVehicleRotation Created by IllidanS4
stock GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz){
	new Float:qw,Float:qx,Float:qy,Float:qz;
	GetVehicleRotationQuat(vehicleid,qw,qx,qy,qz);
	rx = asin(2*qy*qz-2*qx*qw);
	ry = -atan2(qx*qz+qy*qw,0.5-qx*qx-qy*qy);
	rz = -atan2(qx*qy+qz*qw,0.5-qx*qx-qz*qz);
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
	new Float:dx,Float:dy,Float:dz,Float:pdx,Float:pdy,Float:pdz,Float:dot,Float:dsq,Float:lengthsq;
	
	dx = xB - xA;
	dy = yB - yA; 
	dz = zB - zA;
	
	pdx = px - xA;
	pdy = py - yA;
	pdz = pz - zA;
	
	dot = pdx * dx + pdy * dy + pdz * dz;
	
	lengthsq = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	lengthsq = lengthsq*lengthsq;
	if(lengthsq <= 0.0){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Warring: Invalid cylinder posision, identical points.");
		}
		return false;
	} else if(size <= 0.0){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Warring: Invalid cylinder size.");
		}
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

//Polygon Test by RyDeR SRC:http://forum.sa-mp.com/showpost.php?p=1154971&postcount=1871
stock bool:IsPointInPolygon(Float:x,Float:y,{Float,_}:...){
	
	new args_Total = numargs(), polygon_Sides = (args_Total - 2) / 2;
	if((args_Total - 2) & 0b1 || MAX_POLYGON_POINTS <= polygon_Sides || polygon_Sides < 3) return false;

	new Float:polygon_Data[2][MAX_POLYGON_POINTS], cross_Total;
	
	for(new i = 2, j; i < args_Total; i += 2, j++){
		polygon_Data[0][j] = Float:getarg(i);
		polygon_Data[1][j] = Float:getarg(i+1);
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
	if(GetDistanceBetweenPoints2D(px-x,py-y) <= size) return true;
	return false;
}

stock bool:IsPointInSphere(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:size){
	if(GetDistanceBetweenPoints3D(px-x,py-y,pz-z) <= size) return true;
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

stock bool:IsProbable(chance){
	if(chance <= 0) return false;
	if(chance >= 100) return true;
	if((random(100)+1) <= chance) return true;
	return false;
}

stock Float:GetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx, Float:my;
	GetPlayerPos(playerid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	return rz;
}

stock Float:SetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx, Float:my;
	GetPlayerPos(playerid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	SetPlayerFacingAngle(playerid,rz);
	return rz;
}

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

	#define GET_COLANDREAS_VERSION					(0xFFFFFFFF)
	
	#define GetColAndreasVersion()					(COLANDREAS_VERSION)
	#define GetValidColAndreasVersion()				(Tryg3D_ColAndreasVersion)
	
	#define IsCollisionFlag(%0,%1)					((%0) & (%1))

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
			}
		} else {
			if(ColAndreasLastStat){
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Info: ColAndreas successfully init.");
				}
			}
		}
	}
	
	#define IsColAndreasInit			Tryg3D_IsColAndreasInit
	#define SafeColAndreasInit 			Tryg3D_SafeColAndreasInit
	
#endif

#if (defined Tryg3D_MapAndreasEx || defined Tryg3D_MapAndreas)

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

#if (!defined Tryg3D_MapAndreasEx && defined Tryg3D_MapAndreas)

	#define IsMapAndreasInit			Tryg3D_IsMapAndreasInit
	#define SafeMapAndreasInit			Tryg3D_SafeMapAndreasInit
	
	stock Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0){
		if(x <= -3000.0 || x >= 3000.0 || y <= -3000.0 || y >= 3000.0){
			z = 0.0;
		} else {
			MapAndreas_FindZ_For2DCoord(x,y,z);
		}
		return z;
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

//EOF
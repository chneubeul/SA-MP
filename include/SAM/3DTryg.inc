/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                       3D Tryg Functions                                                        *
 *                                                                                                                                *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                         *
 *                                                                                                                                *
 * File Version: 2.4B                                                                                                             *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
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
 * NLTZ(value);                                                                                                                   *
 * NMTZ(value);                                                                                                                   *
 * Float:NLTZF(Float:value);                                                                                                      *
 * Float:NMTZF(Float:value);                                                                                                      *
 * CompRotation(rotation,&cr=0);                                                                                                  *
 * Float:CompRotationFloat(Float:rotation,&Float:cr=Float:0);                                                                     *
 * GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty);                                                  *
 * Float:GetPointInFrontOfPlayer(playerid,&Float:x,&Float:y,Float:radius);                                                        *
 * Float:GetPointInFrontOfCamera2D(playerid,&Float:tx,&Float:ty,Float:radius);                                                    *
 * GetPointInFrontOfCamera3D(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=Float:0,&Float:rz=Float:0);            *
 * GetPointInFront3D(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                       *
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
 * GetPlayerCameraRotation(playerid,&Float:rx,&Float:rz);                                                                         *
 * Float:GetPlayerCameraZAngle(playerid,&Float:rz=Float:0);                                                                       *
 * QuatToEuler(Float:qx,Float:qy,Float:qz,Float:qw,&Float:rx,&Float:ry,&Float:rz);                                                *
 * GetPointFor2Point2D(Float:x1,Float:y1,Float:x2,Float:y2,Float:percent_size,&Float:tx,&Float:ty);                               *
 * GetPointFor2Point3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:percent_size,&Float:tx,&Float:ty,&Float:tz);   *
 * ShiftVectorToRotation(Float:vx,Float:vy,Float:vz,&Float:rx,&Float:rz);                                                         *
 * ShiftRotationToVector(Float:rx,Float:rz,&Float:vx,&Float:vy,&Float:vz);                                                        *
 * bool:IsPointBetween2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB);                                           *
 * bool:IsPointBetween2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB);                *
 * bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist);                              *
 * bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist);   *
 * bool:IsPointInCylinder(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist);        *
 * bool:IsProbable(chance);                                                                                                       *
 * GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry);                                                             *
 * GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance);           *
 *                                                                                                                                *
 * Deprecated Functions:                                                                                                          *
 * GetXYInFrontOfPlayer       -> GetPointInFrontOfPlayer                                                                          *
 * GetPointInFront            -> GetPointInFront3D                                                                                *
 * GetPointInFrontOfCamera    -> GetPointInFrontOfCamera3D                                                                        *
 * GetDistanceBetweenPoints   -> GetDistanceBetweenPoints3D                                                                       *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.4B
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.4B
#elseif (Tryg3D_Version < 20402)
	#error Update you 3DTryg.inc to v2.4B
#endif
*/

#if defined _3D_Tryg
	#endinput
#endif
#define _3D_Tryg

#define Tryg3D_Version									(20402) //a.b[c] 10000*a+100*b+c

#if !defined FLOAT_PI
	#define FLOAT_PI		 							(3.14159265358979323846)
#endif

#define ctg(%0,%1)										(1.0/floattan((%0),(%1)))
#define secans(%0,%1)									(1.0/floatcos((%0),(%1)))
#define cosecans(%0,%1)									(1.0/floatsin((%0),(%1)))
#define abs(%0)											(((%0) < 0)?(-(%0)):((%0)))

#define single_clock(%1,%2)								((360.0/%1)*(%2))
#define even_clock(%1,%2)								((360.0/%1)*(2*%2))
#define uneven_clock(%1,%2)								((360.0/%1)*((2*%2)-1))

#define	sqrtN(%0,%1)									floatpower((%0),(1.0/(%1)))

#define GetDistanceBetweenPoints1D(%1,%2)				VectorSize((%1)-(%2),0.0,0.0)
#define GetDistanceBetweenPoints2D(%1,%2,%3,%4)			VectorSize((%1)-(%3),(%2)-(%4),0.0)
#define GetDistanceBetweenPoints3D(%1,%2,%3,%4,%5,%6)	VectorSize((%1)-(%4),(%2)-(%5),(%3)-(%6))

//NotLessThanZero
#define NLTZ(%0)										(((%0) < 0)?(0):(%0))

//NotMoreThanZero
#define NMTZ(%0)										(((%0) > 0)?(0):(%0))

//NotLessThanZeroFloat
#define NLTZF(%0)										(((%0) < 0.0)?(0.0):(%0))

//NotMoreThanZeroFloat
#define NMTZF(%0)										(((%0) > 0.0)?(0.0):(%0))

#define IsEven(%0)										((((%0) % 2) == 0)?(true):(false))
#define power(%0,%1)									(floatround(floatpower((%0),(%1))))

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

stock CompRotation(rotation,&cr=0){
	cr = rotation;
	while(cr < 0) cr += 360;
	while(cr >= 360) cr -= 360;
	return cr;
}

stock Float:CompRotationFloat(Float:rotation,&Float:cr=Float:0){
	cr = rotation;
	while(cr < 0.0) cr += 360.0;
	while(cr >= 360.0) cr -= 360.0;
	return cr;
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
stock Float:GetPointInFrontOfPlayer(playerid,&Float:x,&Float:y,Float:radius){
	new Float:rz;
	GetPlayerPos(playerid,x,y,rz);
	GetPlayerFacingAngle(playerid,rz);
	if(IsPlayerInAnyVehicle(playerid)){
		GetVehicleZAngle(GetPlayerVehicleID(playerid),rz);
	}
	GetPointInFront2D(x,y,rz,radius,x,y);
	return rz;
}

stock Float:GetPlayerCameraZAngle(playerid,&Float:rz=Float:0){
	new Float:mx,Float:my,Float:mz;
	GetPlayerCameraFrontVector(playerid,mx,my,mz);
	CompRotationFloat((atan2(my,mx)-90.0),rz);
	return rz;
}

stock Float:GetPointInFrontOfCamera2D(playerid,&Float:tx,&Float:ty,Float:radius){
	new Float:x,Float:y,Float:rz;
	GetPlayerCameraPos(playerid,x,y,rz);
	GetPlayerCameraZAngle(playerid,rz);
	GetPointInFront2D(tx,ty,rz,radius,x,y);
	return rz;
}

stock GetPointInFrontOfCamera3D(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=Float:0,&Float:rz=Float:0){
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
		CompRotationFloat((atan2(ty-y,tx-x)-90),rz);
	} else {
		print("[ADM] Warring: Get the rotation wrong, identical points.");
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
		print("[ADM] Warring: Get speed error, the wrong time.");
	} else {
		speed = (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz)/(rtime/1000.0));
	}
	return speed;
}

//Prototype function v2.0
stock GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz){
	new Float:q0,Float:q1,Float:q2,Float:q3;
	GetVehicleRotationQuat(vehicleid,q0,q1,q2,q3);
	GetVehicleZAngle(vehicleid,rz);
	if((rz >= 0.0 && rz <= 90.0) || (rz >= 270.0 && rz <= 360.0)){
		CompRotationFloat(-atan2(2*(q0*q1+q2*q3),1-2*((q1*q1)+(q2*q2))),rx);
		CompRotationFloat(-asin(2*(q0*q2-q3*q1)),ry);
	} else {
		CompRotationFloat(atan2(2*(q0*q1+q2*q3),1-2*((q1*q1)+(q2*q2))),rx);
		CompRotationFloat(asin(2*(q0*q2-q3*q1)),ry);
	}
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

//Orig: Greg James - gjames@NVIDIA.com SRC: http://www.flipcode.com/archives/Fast_Point-In-Cylinder_Test.shtml
stock bool:IsPointInCylinder(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist){
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
	if(lengthsq <= 0.0 || maxdist <= 0.0){
		print("[ADM] Warring: Invalid lengthsq OR maxdist");
		return false;
	}
	if(dot < 0.0 || dot > lengthsq){
		return false;
	} else {
		dsq = (pdx*pdx + pdy*pdy + pdz*pdz) - dot*dot/lengthsq;
		if(dsq <= (maxdist*maxdist)){
			return true;
		}
	}
	return false;
}

//Prototype function
stock bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist){
	new Float:dAP = GetDistanceBetweenPoints2D(xA,yA,px,py),
		Float:dBP = GetDistanceBetweenPoints2D(xB,yB,px,py),
		Float:dAB = GetDistanceBetweenPoints2D(xA,yA,xB,yB);
	if(dAB <= (dAP + dBP) <= (dAB+(maxdist))) return true;
	return false;
}

//Prototype function
stock bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist){
	new Float:dAP = GetDistanceBetweenPoints3D(xA,yA,zA,px,py,pz),
		Float:dBP = GetDistanceBetweenPoints3D(xB,yB,zB,px,py,pz),
		Float:dAB = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	if(dAB <= (dAP + dBP) <= (dAB+(maxdist))) return true;
	return false;
}

//Prototype function
stock QuatToEuler(Float:qx,Float:qy,Float:qz,Float:qw,&Float:rx,&Float:ry,&Float:rz){
	CompRotationFloat(atan2(2*(qx*qy+qz*qw),1-2*((qy*qy)+(qz*qz))),rx);
	CompRotationFloat(asin(2*(qx*qz-qw*qy)),ry);
	CompRotationFloat(atan2(2*(qx*qw+qy*qz),1-2*(qz*qz+qw*qw)),rz);
}

stock bool:IsProbable(chance){
	if(chance <= 0) return false;
	if(chance >= 100) return true;
	if((random(100)+1) <= chance) return true;
	return false;
}

stock GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry){
	new Float:tpx1,Float:tpy1,Float:tpz1,
		Float:tpx2,Float:tpy2,Float:tpz2,
		Float:tmp;
	GetPointInFront2D(x,y,0.0,size,tpx1,tpy1);
	GetPointInFront2D(x,y,180.0,size,tpx2,tpy2);
	MapAndreas_FindZ_For2DCoord(tpx1,tpy1,tpz1);
	MapAndreas_FindZ_For2DCoord(tpx2,tpy2,tpz2);
	GetRotationFor2Point3D(tpx1,tpy1,tpz1,tpx2,tpy2,tpz2,rx,tmp);
	
	GetPointInFront2D(x,y,90.0,size,tpx1,tpy1);
	GetPointInFront2D(x,y,270.0,size,tpx2,tpy2);
	MapAndreas_FindZ_For2DCoord(tpx1,tpy1,tpz1);
	MapAndreas_FindZ_For2DCoord(tpx2,tpy2,tpz2);
	GetRotationFor2Point3D(tpx1,tpy1,tpz1,tpx2,tpy2,tpz2,ry,tmp);
	#pragma unused tmp
}

stock GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance){
	new Float:tmpz;
	MapAndreas_FindZ_For2DCoord(x,y,tmpz);
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
		MapAndreas_FindZ_For2DCoord(tx,ty,tz);
	}
}

#define GetXYInFrontOfPlayer							GetPointInFrontOfPlayer
#define GetPointInFront									GetPointInFront3D
#define GetPointInFrontOfCamera							GetPointInFrontOfCamera3D
#define GetDistanceBetweenPoints						GetDistanceBetweenPoints3D

//EOF

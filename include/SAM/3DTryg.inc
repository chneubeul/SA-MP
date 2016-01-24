/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                       3D Tryg Functions                                                        *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * File Version: 2.1e                                                                                                             *
 *                                                                                                                                *
 * Float:sqrtN(Float:value,Float:exponent);                                                                                       *
 * abs(value);                                                                                                                    *
 * power(value,Float:exponent);                                                                                                   *
 * Float:ctg(Float:value,anglemode:mode=radian);                                                                                  *
 * Float:secans(Float:value,anglemode:mode=radian);                                                                               *
 * Float:cosecans(Float:value,anglemode:mode=radian);                                                                             *
 * GetRandomHit(Float:x,Float:y,Float:z,range,&Float:tx,&Float:ty,&Float:tz);                                                     *
 * GetDistanceBetweenPoints1D(Float:x1,Float:x2);                                                                                 *
 * GetDistanceBetweenPoints2D(Float:x1,Float:y1,Float:x2,Float:y2);                                                               *
 * GetDistanceBetweenPoints3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);                                             *
 * NLTZ(value);                                                                                                                   *
 * NMTZ(value);                                                                                                                   *
 * Float:NLTZF(Float:value);                                                                                                      *
 * Float:NMTZF(Float:value);                                                                                                      *
 * CompRotation(rotation,&cr);                                                                                                    *
 * CompRotationFloat(Float:rotation,&Float:cr);                                                                                   *
 * GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty);                                                  *
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
 * GetSpeedForMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:speed,rtime);                                    *
 * GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz);                                                                   *
 * GetPlayerCameraRotation(playerid,&Float:rx,&Float:rz);                                                                         *
 * GetPlayerCameraZAngle(playerid,&Float:rz);                                                                                     *
 * QuatToEuler(Float:qx,Float:qy,Float:qz,Float:qw,&Float:rx,&Float:ry,&Float:rz);                                                *
 * GetPointFor2Point2D(Float:x1,Float:y1,Float:x2,Float:y2,Float:percent_size,&Float:tx,&Float:ty);                               *
 * GetPointFor2Point3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:percent_size,&Float:tx,&Float:ty,&Float:tz);   *
 * ShiftVectorToRotation(Float:vx,Float:vy,Float:vz,&Float:rx,&Float:rz);                                                         *
 * ShiftRotationToVector(Float:rx,Float:rz,&Float:vx,&Float:vy,&Float:vz);                                                        *
 * bool:IsPointBetween2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB);                                           *
 * bool:IsPointBetween2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB);                *
 * bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist);                              *
 * bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist);   *
 * bool:IsProbable(chance);                                                                                                       *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.1e
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.1e
#elseif (Tryg3D_Version < 0x20105)
	#error Update you 3DTryg.inc to v2.1e
#endif
*/

#if defined _3D_Tryg
	#endinput
#endif
#define _3D_Tryg

#define Tryg3D_Version 	(0x20105) //a.b[c] 10000*a+100*b+c

#if !defined PI
	#define PI (22/7)
#endif

#define ctg(%0,%1)			1/floattan(%0,%1)
#define secans(%0,%1)		1/floatcos(%0,%1)
#define cosecans(%0,%1)		1/floatsin(%0,%1)
#define abs(%0)				(((%0) < 0)?(-(%0)):((%0)))

stock Float:sqrtN(Float:value,Float:exponent){
	return floatpower(value,(1.0/exponent));
}

stock power(value,Float:exponent){
	return floatround(floatpower(value,exponent));
}

stock GetRandomHit(Float:x,Float:y,Float:z,range,&Float:tx,&Float:ty,&Float:tz){
	new rand = range * 2;
	tx = x + (random(rand)-range);
	ty = y + (random(rand)-range);
	tz = z + (random(rand)-range);
}

stock Float:GetDistanceBetweenPoints1D(Float:x1,Float:x2){
	return VectorSize(x1-x2,0.0,0.0);
}

stock Float:GetDistanceBetweenPoints2D(Float:x1,Float:y1,Float:x2,Float:y2){
	return VectorSize(x1-x2,y1-y2,0.0);
}

stock Float:GetDistanceBetweenPoints3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2){
	return VectorSize(x1-x2,y1-y2,z1-z2);
}

//NotLessThanZero
stock NLTZ(value){
	if(value < 0) value = 0;
	return value;
}

//NotMoreThanZero
stock NMTZ(value){
	if(value > 0) value = 0;
	return value;
}

//NotLessThanZeroFloat
stock Float:NLTZF(Float:value){
	if(value < 0.0) value = 0.0;
	return value;
}

//NotMoreThanZeroFloat
stock Float:NMTZF(Float:value){
	if(value > 0.0) value = 0.0;
	return value;
}

stock CompRotation(rotation,&cr){
	cr = rotation;
	while(cr < 0) cr += 360;
	while(cr >= 360) cr -= 360;
}

stock CompRotationFloat(Float:rotation,&Float:cr){
	cr = rotation;
	while(cr < 0.0) cr += 360.0;
	while(cr >= 360.0) cr -= 360.0;
}

//the old version of the code
stock GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty){
	tx = x + (radius*floatsin(-rz,degrees));
	ty = y + (radius*floatcos(-rz,degrees));
}

//a new version of the code,support 3D made by Abyss Morgan
stock GetPointInFront3D(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	tx = x + (radius * floatsin(rx+90.0,degrees) * floatcos(rz+90.0,degrees));
	ty = y + (radius * floatsin(rx+90.0,degrees) * floatsin(rz+90.0,degrees));
	tz = z + (radius * floatcos(-rx+90.0,degrees));
}

#define GetPointInFront GetPointInFront3D

//old code version made by Zoutdaxv (modified version)
stock GetRotationFor2Point2D(Float:x,Float:y,Float:tx,Float:ty,&Float:rz){
	CompRotationFloat((atan2(ty-y,tx-x)-90),rz);
}

//new code version support 3D made by Abyss Morgan
stock GetRotationFor2Point3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:rx,&Float:rz){
	new Float:radius = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
	if(radius > 0.0){
		CompRotationFloat(-(acos((tz-z)/radius)-90.0),rx);
		CompRotationFloat((atan2(ty-y,tx-x)-90),rz);
	} else {
		rx = 0.0, rz = 0.0;
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
	new cx,cy,cz;
	cx = floatround(floatsqroot(floatpower(minx-maxx,2)))+1;
	cy = floatround(floatsqroot(floatpower(miny-maxy,2)))+1;
	cz = floatround(floatsqroot(floatpower(minz-maxz,2)))+1;
	x = random(cx)+minx;
	y = random(cy)+miny;
	z = random(cz)+minz;
}

stock Float:ShiftDegreeToRadian(Float:deg){
	return (deg*((PI*2)/360));
}

stock Float:ShiftDegreeToRadianEx(Float:deg){
	CompRotationFloat(deg,deg);
	return ((360-deg)*(-((PI*2)/360)));
}

stock Float:ShiftDegreeToGrades(Float:deg){
	return (deg*(10/9));
}

stock Float:ShiftRadianToDegree(Float:rad){
	return (rad/((PI*2)/360));
}

stock Float:ShiftRadianToDegreeEx(Float:rad){
	new Float:deg;
	CompRotationFloat(floatabs((rad/((PI*2)/360))+360),deg);
	return deg;
}

stock Float:ShiftRadianToGrades(Float:rad){
	new Float:deg = ShiftRadianToDegree(rad);
	return ShiftDegreeToGrades(deg);
}

stock Float:ShiftGradesToDegree(Float:grad){
	return (grad*0.9);
}

stock Float:ShiftGradesToRadian(Float:grad){
	new Float:deg = ShiftGradesToDegree(grad);
	return ShiftDegreeToRadian(deg);
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

stock GetMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:speed,&rtime){
	if(speed <= 0.0){
		rtime = _:FLOAT_INFINITY;
	} else {
		new Float:dist = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
		rtime = floatround((dist/speed)*1000.0);
	}
}

stock GetSpeedForMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:speed,rtime){
	if(rtime/1000.0 <= 0.0){
		speed = FLOAT_INFINITY;
		print("[ADM] Warring: Get speed error, the wrong time.");
	} else {
		new Float:dist = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
		speed = (dist/(rtime/1000.0));
	}
}

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

stock ShiftRotationToVector(Float:rx,Float:rz,&Float:vx,&Float:vy,&Float:vz){
	GetPointInFront3D(0.0,0.0,0.0,rx,rz,1.0,vx,vy,vz);
}

stock GetPlayerCameraRotation(playerid,&Float:rx,&Float:rz){
	new Float:mx,Float:my,Float:mz;
	GetPlayerCameraFrontVector(playerid,mx,my,mz);
	ShiftVectorToRotation(mx,my,mz,rx,rz);
}

stock GetPlayerCameraZAngle(playerid,&Float:rz){
	new Float:mx,Float:my,Float:mz;
	GetPlayerCameraFrontVector(playerid,mx,my,mz);
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

stock bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist){
	new Float:dAP = GetDistanceBetweenPoints2D(xA,yA,px,py),
		Float:dBP = GetDistanceBetweenPoints2D(xB,yB,px,py),
		Float:dAB = GetDistanceBetweenPoints2D(xA,yA,xB,yB);
	if(dAB <= (dAP + dBP) <= dAB+(maxdist*2)) return true;
	return false;
}

stock bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist){
	new Float:dAP = GetDistanceBetweenPoints3D(xA,yA,zA,px,py,pz),
		Float:dBP = GetDistanceBetweenPoints3D(xB,yB,zB,px,py,pz),
		Float:dAB = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	if(dAB <= (dAP + dBP) <= dAB+(maxdist*2)) return true;
	return false;
}

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

//EOF
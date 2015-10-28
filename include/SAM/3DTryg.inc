/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                       3D Tryg Functions                                                        *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * File Version: 1.1                                                                                                              *
 *                                                                                                                                *
 * abs(value);                                                                                                                    *
 * power(value,exponent);                                                                                                         *
 * GetRandomHit(Float:x,Float:y,Float:z,range,&Float:tx,&Float:ty,&Float:tz);                                                     *
 * GetDistanceBetweenPoints1D(Float:x1,Float:x2);                                                                                 *
 * GetDistanceBetweenPoints2D(Float:x1,Float:y1,Float:x2,Float:y2);                                                               *
 * GetDistanceBetweenPoints3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);                                             *
 * Center(Float:value1,Float:value2);                                                                                             *
 * Intake(Float:value1,Float:value2);                                                                                             *
 * NLTZ(value);                                                                                                                   *
 * NMTZ(value);                                                                                                                   *
 * Float:NLTZF(Float:value);                                                                                                      *
 * Float:NMTZF(Float:value);                                                                                                      *
 * CompRotation(rotation,&cr);                                                                                                    *
 * CompRotationFloat(Float:rotation,&Float:cr);                                                                                   *
 * GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty);                                                  *
 * GetPointInFront(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                         *
 * GetRotationFor2Point2D(Float:x,Float:y,Float:tx,Float:ty,&Float:rz);                                                           *
 * GetRotationFor2Point3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:rx,&Float:rz);                                *
 * GetClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0,mapz = 0);        *
 * GetRandomPointInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:x,&Float:y,&Float:z);            *
 *                                                                                                                                *
 **********************************************************************************************************************************/

stock abs(value){
	if(value < 0) value *= (-1);
	return value;
}

stock power(value,exponent){
	return floatround(floatpower(value,exponent));
}

stock GetRandomHit(Float:x, Float:y, Float:z, range, &Float:tx, &Float:ty, &Float:tz){
	new rand = range * 2;
	tx = x + (random(rand)-range);
	ty = y + (random(rand)-range);
	tz = z + (random(rand)-range);
}

stock Float:GetDistanceBetweenPoints1D(Float:x1,Float:x2){
    return VectorSize(x1-x2, 0.0, 0.0);
}

stock Float:GetDistanceBetweenPoints2D(Float:x1,Float:y1,Float:x2,Float:y2){
    return VectorSize(x1-x2, y1-y2, 0.0);
}

stock Float:GetDistanceBetweenPoints3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2){
    return VectorSize(x1-x2, y1-y2, z1-z2);
}

stock Float:Center(Float:value1,Float:value2){
	return ((value1+value2)/2);
}

stock Float:Intake(Float:value1,Float:value2){
	return Center(Center(value2,value1),value1);
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
stock GetPointInFront2D(Float:x, Float:y, Float:rz, Float:radius, &Float:tx, &Float:ty){
	tx = x + (radius*floatsin(-rz,degrees));
	ty = y + (radius*floatcos(-rz,degrees));
}

//a new version of the code, support 3D made by Abyss Morgan
stock GetPointInFront(Float:x, Float:y, Float:z, Float:rx, Float:rz, Float:radius, &Float:tx, &Float:ty, &Float:tz){
	tx = x + (radius * floatsin(rx+90.0,degrees) * floatcos(rz+90.0,degrees));
	ty = y + (radius * floatsin(rx+90.0,degrees) * floatsin(rz+90.0,degrees));
	tz = z + (radius * floatcos(-rx+90.0,degrees));
}

//old code version made by Zoutdaxv (modified version) 
stock GetRotationFor2Point2D(Float:x, Float:y, Float:tx, Float:ty, &Float:rz){
	CompRotationFloat((atan2(ty-y,tx-x)-90),rz);
}

//new code version support 3D made by Abyss Morgan 
stock GetRotationFor2Point3D(Float:x, Float:y, Float:z, Float:tx, Float:ty, Float:tz, &Float:rx, &Float:rz){
	new Float:radius = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
	if(radius > 0.0){
		CompRotationFloat(-(acos((tz-z)/radius)-90.0),rx);
		CompRotationFloat((atan2(ty-y,tx-x)-90),rz);
	} else {
		rx = 0.0, rz = 0.0;
	}
}

//random clock pos
stock GetRandomClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0,mapz = 0){
	new Float:tmpz, rand = random(360);
	if(rz == -1000.0) rz = rand;
	GetPointInFront(x,y,z,0.0,rz,radius,tx,ty,tz);
	CompRotationFloat(rz-180,trz);
	#if defined MapAndreas_FindZ_For2DCoord
		if(mapz == 1){
			MapAndreas_FindZ_For2DCoord(tx,ty,tmpz);
			if(tz < tmpz+50){
				tz += (50);
			}
		}
	#else
		#pragma unused mapz
	#endif
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
/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                            NGCM Mob Move Engine System 5.0 Delta X                                             *
 *                                                                                                                                *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                                                     *
 *                                                                                                                                *
 * File Version: 5.0X                                                                                                             *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * bool:IsPointInWaterEx(Float:x,Float:y,Float:z);                                                                                *
 * GetClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0);                 *
 * EngineX(objectid,areaid,engineid,minradius,maxradius,Float:minz,Float:speed);                                                  *
 * DeltaEngineRotation(objectid,engineid,Float:speed = 0.05);                                                                     *
 * DeltaEngineX(objectid,areaid,engineid,minradius,maxradius,Float:minz,Float:speed);                                             *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if defined NGCM_KERNEL
	#error Fatal error incompatible NOX
#endif

#if defined _NOX_ENGINE_X
	#endinput
#endif
#define _NOX_ENGINE_X


//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.1F
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.1F
#elseif (Tryg3D_Version < 20106)
	#error Update you 3DTryg.inc to v2.1F
#endif

//MapAndreasEx.inc
#if !defined MapAndreasFindZ
	#error You need MapAndreasEx.inc
#endif

#define NOX_ENGINE_X_Version		(50024)

#define NOX_VERSION					"5.0 Delta X"

#if defined USE_NEW_PROTOTYPE_NT
	#define NT_VERSION				"2.0"
#else
	#define NT_VERSION				"1.0"
#endif

new InvalidPolygon[2];

enum e_nox_float {
	Float:X,
	Float:Y,
	Float:Z,
	Float:rX,
	Float:rY,
	Float:rZ,
	Float:tX,
	Float:tY,
	Float:tZ
}

public OnFilterScriptInit(){
	SafeMapAndreasInit();
	InvalidPolygon[0] = CreateDynamicRectangle(398.0,689.0,808.0,1031.0,-1,-1,-1);		//Kanion blokada
	InvalidPolygon[1] = CreateDynamicRectangle(-1407.0,1979.0,-445.0,2843.0,-1,-1,-1);	//Tama Blokada
	printf("[ADM] Info: NGCM Mob Move Engine System %s loaded",NOX_VERSION);
	#if defined NOX_OnFilterScriptInit
		NOX_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit NOX_OnFilterScriptInit
#if defined NOX_OnFilterScriptInit
	forward NOX_OnFilterScriptInit();
#endif

public OnFilterScriptExit(){
	if(IsValidDynamicArea(InvalidPolygon[0])) DestroyDynamicArea(InvalidPolygon[0]);
	if(IsValidDynamicArea(InvalidPolygon[1])) DestroyDynamicArea(InvalidPolygon[1]);
	printf("[ADM] Info: NGCM Mob Move Engine System %s unloaded",NOX_VERSION);
	#if defined NOX_OnFilterScriptExit
		NOX_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit NOX_OnFilterScriptExit
#if defined NOX_OnFilterScriptExit
	forward NOX_OnFilterScriptExit();
#endif

public OnGameModeInit(){
	SafeMapAndreasInit();
	InvalidPolygon[0] = CreateDynamicRectangle(398.0,689.0,808.0,1031.0,-1,-1,-1);		//Kanion blokada
	InvalidPolygon[1] = CreateDynamicRectangle(-1407.0,1979.0,-445.0,2843.0,-1,-1,-1);	//Tama Blokada
	printf("[ADM] Info: NGCM Mob Move Engine System %s loaded",NOX_VERSION);
	#if defined NOX_OnGameModeInit
		NOX_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit NOX_OnGameModeInit
#if defined NOX_OnGameModeInit
	forward NOX_OnGameModeInit();
#endif

public OnGameModeExit(){
	if(IsValidDynamicArea(InvalidPolygon[0])) DestroyDynamicArea(InvalidPolygon[0]);
	if(IsValidDynamicArea(InvalidPolygon[1])) DestroyDynamicArea(InvalidPolygon[1]);
	printf("[ADM] Info: NGCM Mob Move Engine System %s unloaded",NOX_VERSION);
	#if defined NOX_OnGameModeExit
		NOX_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit NOX_OnGameModeExit
#if defined NOX_OnGameModeExit
	forward NOX_OnGameModeExit();
#endif

#define ENGINE_NORMAL 		0	//[Object: 1681, 18846 OR ANY] 	|| 5.0 Delta X
#define ENGINE_FIGHTER		1	//[Object: 10757]				|| 5.0 Delta X
#define ENGINE_SUPPLY		2	//[Object: 1683]				|| 5.0 Delta X
//#define ENGINE_NGCMS		3	//[] (Only NGCM)				|| 4.0 X
//#define ENGINE_ARCMS		4	//[] (Only NGCM)				|| 4.0 X
//#define ENGINE_COMMANDER	5	//[] (Only NGCM)				|| 4.0 X
#define ENGINE_ELITE		6	//[Object: 14553] 				|| 5.0 Delta X
#define ENGINE_UBOOT		7	//[Object: 9958]				|| 5.0 Delta X
#define ENGINE_SHIP			8	//[Object: 8493]				|| 4.0 X
#define ENGINE_MINI			9	//[Object: 2510]				|| 5.0 Delta X
								//[Object: 18248]				|| Not Supported
					
stock bool:IsPointInWaterEx(Float:x,Float:y,Float:z){
	if(IsPointInDynamicArea(InvalidPolygon[0],x,y,z)) return false;
	if(IsPointInDynamicArea(InvalidPolygon[1],x,y,z)) return false;
	return true;
}

stock GetClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0){
	GetRandomClockPos(x,y,z,radius,tx,ty,tz,trz,rz);
	new Float:tmpz;
	MapAndreasFindZ(tx,ty,tmpz);
	if(tz < tmpz+50.0){
		tz += 50.0;
	}
}

stock EngineX(objectid,areaid,engineid,minradius,maxradius,Float:minz,Float:speed){
	new rad = maxradius-minradius, F5[e_nox_float];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
		case ENGINE_NORMAL: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(90)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],randRX,randRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		case ENGINE_FIGHTER: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(90)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX+8),tmpRX);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX+8,12.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(90)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX),tmpRX);
				CompRotation(randRZ-90,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,randRX,randRZ);
					}
				}
			}
		}
		
		case ENGINE_ELITE: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(90)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX+14),tmpRX);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX+14,12.0,randRZ);
					}
				}
			}
		}
		case ENGINE_UBOOT: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz == 0.0){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SHIP: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,randRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if((tmpz == 0.0) && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
	
		case ENGINE_MINI: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(90)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX),tmpRX);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
	}
}

stock DeltaEngineRotation(objectid,engineid,Float:speed = 0.05){
	new F5[e_nox_float];
	
	GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
	F5[rX] = random(90)-45;
	F5[rY] = random(20)-10;
	F5[rZ] = random(360);
	
	if(engineid == ENGINE_SHIP || engineid == ENGINE_UBOOT){
		if(F5[Z] > 0.0){
			F5[Z]-=0.05;
		} else {
			F5[Z]+=0.05;
		}
	} else {
		F5[Z]+=0.05;
	}
	
	switch(engineid){
		case ENGINE_NORMAL: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX],F5[rY],F5[rZ]);
		}
		case ENGINE_FIGHTER: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX]+8.0,F5[rY]+12.0,F5[rZ]);
		}
		case ENGINE_SUPPLY: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rY],F5[rX],F5[rZ]);
		}
		case ENGINE_ELITE: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX]+14.0,F5[rY]+12.0,F5[rZ]);
		}
		case ENGINE_UBOOT: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,0.0,0.0,F5[rZ]);
		}
		case ENGINE_SHIP: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,0.0,0.0,F5[rZ]);
		}
		case ENGINE_MINI: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX],F5[rY],F5[rZ]);
		}
	}
}

stock DeltaEngineX(objectid,areaid,engineid,minradius,maxradius,Float:minz,Float:speed){
	new rad = maxradius-minradius, F5[e_nox_float];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
		case ENGINE_NORMAL: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ],randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		case ENGINE_FIGHTER: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rX]+8),tmpRX);
			CompRotationFloat(F5[rZ]-180,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX]+8,F5[rY]+12.0,F5[rZ]);
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rY]),tmpRX);
			CompRotationFloat(F5[rZ]-90,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		
		case ENGINE_ELITE: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rX]+14.0),tmpRX);
			CompRotationFloat(F5[rZ]-180.0,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX]+14.0,F5[rY]+12.0,F5[rZ]);
				}
			}
		}
		
		case ENGINE_UBOOT: {
			new randR = random(rad)+minradius, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat(F5[rZ]-180.0,tmpRZ);
			GetPointInFront2D(F5[X],F5[Y],tmpRZ,randR,F5[tX],F5[tY]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz == 0.0){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,F5[rZ]);
				}
			}
		}
		
		case ENGINE_SHIP: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,F5[rZ],randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if((tmpz == 0.0) && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,F5[rZ]);
				}
			}
		}
	
		case ENGINE_MINI: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rX]),tmpRX);
			CompRotationFloat(F5[rZ]-180.0,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
	}
}



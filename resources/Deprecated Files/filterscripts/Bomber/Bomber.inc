/****************************************************************************************************
 *                                                                                                  *
 * Bomber NGC v1.0.1 made by Abyss Morgan                                                           *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts/Bomber                  *
 *                                                                                                  *
 ****************************************************************************************************/

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v4.0.2
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#elseif (Tryg3D_Version < 40002)
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#endif

//Check Version StreamerFunction.inc
#if !defined _streamer_spec
	#error [ADM] You need StreamerFunction.inc v2.6.0
#elseif !defined Streamer_Spec_Version
	#error [ADM] Update you StreamerFunction.inc to v2.6.0
#elseif (Streamer_Spec_Version < 20600)
	#error [ADM] Update you StreamerFunction.inc to v2.6.0
#endif

//Check Version EngineX.inc
#if !defined _NOX_ENGINE_X
	#error [ADM] You need EngineX.inc v5.1.24
#elseif !defined NOX_ENGINE_X_Version
	#error [ADM] Update you EngineX.inc to v5.1.24
#elseif (NOX_ENGINE_X_Version < 50124)
	#error [ADM] Update you EngineX.inc to v5.1.24
#endif

//Check Version ATM.inc
#if !defined _ATM_Core
	#error [ADM] You need ATM.inc v1.4.2
#elseif !defined ATM_Version
	#error [ADM] Update you ATM.inc to v1.4.2
#elseif (ATM_Version < 10402)
	#error [ADM] Update you ATM.inc to v1.4.2
#endif

//#define CHANGE_DIRECTION_OF_FLIGHT
//#define CHANGE_COLOR_AIRCRAFT

#define MAX_NGC_NPC					(10)
#define BOMBER_DISTANCE				(500.0)
#define PACK_SPEED					(5.0)

#define MOB_SPEED_SLOW				(5.0)
#define MOB_SPEED_NORMAL			(10.0)
#define MOB_SPEED_FAST				(25.0)

#define NGC_NPC_STAT_STANDBY		(0)
#define NGC_NPC_STAT_AUTO			(1)
#define NGC_NPC_STAT_MANUAL			(2)

enum e_bomber {
	e_name[64],
	Float:X,
	Float:Y
}

new Float:BomberTarget[][e_bomber] = {
	{"Las Venturas",	2148.0,1016.0}
};


new BomberTimer,
	NGCBomber[MAX_NGC_NPC][7],
	//Text3D:NGCBomberText[MAX_NGC_NPC],
	NGCBomberCords[MAX_NGC_NPC][e_float],
	NGCBomberPool,
	NGCBomberStat[MAX_NGC_NPC] = NGC_NPC_STAT_STANDBY,
	bool:BomberUsed[MAX_NGC_NPC] = false;
	
forward Bomber_OnFilterScriptInit();
forward Bomber_OnFilterScriptExit();
forward OnMobUpdate(tec);

forward NGCBomberUpdate(mobid);
forward CreateNGCBomber(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid);
forward DestroyNGCBomber(mobid);
forward SetNGCBomberStat(mobid,statid);
forward NGCBomberGoTo(mobid,Float:x,Float:y,Float:z,Float:speed);
forward OnBomberActive(mobid,Float:x,Float:y,Float:z);
forward OnPackageLanded(mobid,objectid);

new bool:CRC_Bomber = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_Bomber){ CRC_Bomber = false; } else return 1; //Init Engine
	Bomber_OnFilterScriptInit();
	#if defined BMB_OnFilterScriptInit
		BMB_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit BMB_OnFilterScriptInit
#if defined BMB_OnFilterScriptInit
	forward BMB_OnFilterScriptInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	Bomber_OnFilterScriptExit();
	#if defined BMB_OnFilterScriptExit
		BMB_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit BMB_OnFilterScriptExit
#if defined BMB_OnFilterScriptExit
	forward BMB_OnFilterScriptExit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_Bomber){ CRC_Bomber = false; } else return 1; //Init Engine
	Bomber_OnFilterScriptInit();
	#if defined BMB_OnGameModeInit
		BMB_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit BMB_OnGameModeInit
#if defined BMB_OnGameModeInit
	forward BMB_OnGameModeInit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	Bomber_OnFilterScriptExit();
	#if defined BMB_OnGameModeExit
		BMB_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit BMB_OnGameModeExit
#if defined BMB_OnGameModeExit
	forward BMB_OnGameModeExit();
#endif


public Bomber_OnFilterScriptInit(){
	
	BomberTimer = SetTimerEx("OnMobUpdate", 500, true, "d", 1);
	
	new myarea = CreateDynamicCube(-3000.0,-3000.0,200.0,3000.0,3000.0,600.0); //the entire map, height from 200 to 600 meters
	
	CreateNGCBomber(1,20000.0,21000.0,300.0,0,0,myarea);
	
	return 1;
}

public Bomber_OnFilterScriptExit(){
	KillTimer(BomberTimer);
	return 1;
}

public OnMobUpdate(tec){
	new hour, minute, second;
	gettime(hour,minute,second);
	#pragma unused tec
	
	for(new mobid = 0; mobid <= NGCBomberPool; mobid++){
		if(NGCBomber[mobid][2] == 1){
			if(minute >= 0 && minute <= 59){
				if(!BomberUsed[mobid]){
					BomberUsed[mobid] = true;
					new F4[e_float];
					new rand = random(sizeof(BomberTarget));
					NGCBomber[mobid][6] = rand;
					MapAndreasFindZ(BomberTarget[rand][X],BomberTarget[rand][Y],F4[Z]);
					F4[Z] += 150.0;
					GetRandomPointOnClock(BomberTarget[rand][X],BomberTarget[rand][Y],BOMBER_DISTANCE,F4[X],F4[Y],F4[rZ]);
					SetDynamicObjectVW(NGCBomber[mobid][0],0);
					SetDynamicObjectPos(NGCBomber[mobid][0],F4[X],F4[Y],F4[Z]);
					CompRotationFloat(F4[rZ]+90.0,F4[rZ]);
					SetDynamicObjectRot(NGCBomber[mobid][0],0.0,0.0,F4[rZ]);
					NGCBomberGoTo(mobid,BomberTarget[rand][X],BomberTarget[rand][Y],F4[Z],MOB_SPEED_NORMAL);
				}
			} else {
				BomberUsed[mobid] = false; //I have not been recently used
			}
			NGCBomberUpdate(mobid);
		}
	}

	return 1;
}

/*
0 objectid
1 areaid
2 status
3 step
4 active count
5 mapicon
6 last location
*/

public NGCBomberUpdate(mobid){
	if(NGCBomber[mobid][2] == 1){
		new F4[e_float];
		GetDynamicObjectPos(NGCBomber[mobid][0],F4[X],F4[Y],F4[Z]);
		SetDynamicMapIconPos(NGCBomber[mobid][5],F4[X],F4[Y],F4[Z]);
		//SetDynamic3DTextPos(NGCBomberText[mobid],F4[X],F4[Y],F4[Z]+2.0);
		
		if(!IsDynamicObjectMoving(NGCBomber[mobid][0])){
			switch(NGCBomberStat[mobid]){
				case NGC_NPC_STAT_STANDBY: {
					//stoimy w miejscu i czekamy na zbawienie
				}
				
				case NGC_NPC_STAT_AUTO: {
					if(NGCBomber[mobid][3] == 0){
						DeltaEngineRotation(NGCBomber[mobid][0],ENGINE_SUPPLY,DELTA_ENGINE_SPEED_SUPPLY);
						NGCBomber[mobid][3] = 1;
					} else {
						DeltaEngineX(NGCBomber[mobid][0],NGCBomber[mobid][1],ENGINE_SUPPLY,50,100,5,MOB_SPEED_NORMAL);
						NGCBomber[mobid][3] = 0;
					}
				}
				
				case NGC_NPC_STAT_MANUAL: {
					new F5[e_float];
					F5[X] = NGCBomberCords[mobid][X];
					F5[Y] = NGCBomberCords[mobid][Y];
					F5[Z] = NGCBomberCords[mobid][Z];
					new Float:distance = GetDistanceBetweenPoints3D(F4[X],F4[Y],F4[Z],F5[X],F5[Y],F5[Z]);
					if(distance > 0.0){
						if(NGCBomber[mobid][3] == 0){
							GetRotationFor2Point3D(F5[X],F5[Y],F5[Z],F4[X],F4[Y],F4[Z],F5[rX],F5[rZ]);
							MoveDynamicObject(NGCBomber[mobid][0],F4[X],F4[Y],F4[Z]+0.10,DELTA_ENGINE_SPEED_SUPPLY,0.0,0.0,F5[rZ]-90.0);
							NGCBomber[mobid][3] = 1;
						} else {
							GetRotationFor2Point3D(F5[X],F5[Y],F5[Z],F4[X],F4[Y],F4[Z],F5[rX],F5[rZ]);
							MoveDynamicObject(NGCBomber[mobid][0],F5[X],F5[Y],F5[Z],NGCBomberCords[mobid][SPEED],0.0,0.0,F5[rZ]-90.0);
							NGCBomber[mobid][3] = 0;
						}
					} else {
						OnBomberActive(mobid,F4[X],F4[Y],F4[Z]);
					}
				}
			}
		}
	}
	return 1;
}

public CreateNGCBomber(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid){
	
	NGCBomber[mobid][5] = CreateDynamicMapIcon(x,y,z,0,0x0000FFFF,worldid,interiorid,-1,500.0);
	NGCBomber[mobid][0] = CreateDynamicObject(1683,x,y,z+3.0,0.0,0.0,270.0,worldid,interiorid,-1,500.0,500.0);
	SetDynamicObjectMaterial(NGCBomber[mobid][0],0,2707,"Shopping","white",0x00FFFFFF); //kasujemy napisy
	SetDynamicObjectMaterial(NGCBomber[mobid][0],1,2707,"Shopping","white",0x00FFFFFF); //kasujemy cieñ
	#if defined CHANGE_COLOR_AIRCRAFT
		SetDynamicObjectMaterial(NGCBomber[mobid][0],2,1676,"wshxrefpump","metalic128",0xFF0000FF);
		SetDynamicObjectMaterial(NGCBomber[mobid][0],3,2707,"Shopping","white",0xFF0000FF);
		SetDynamicObjectMaterial(NGCBomber[mobid][0],4,2707,"Shopping","white",0xFF0000FF);
	#endif

	NGCBomber[mobid][1] = areaid;
	NGCBomber[mobid][3] = 0;
	NGCBomber[mobid][4] = 0;
	
	SetDynamicObjectVW(NGCBomber[mobid][0],200000);
	
	if(NGCBomberPool < mobid) NGCBomberPool = mobid;
	
	NGCBomber[mobid][2] = 1;
	
	NGCBomberStat[mobid] = NGC_NPC_STAT_STANDBY;
	
	return 1;
}

public DestroyNGCBomber(mobid){
	NGCBomber[mobid][2] = 0;
	if(IsValidDynamicObject(NGCBomber[mobid][0])) DestroyDynamicObject(NGCBomber[mobid][0]);
	if(IsValidDynamicMapIcon(NGCBomber[mobid][5])) DestroyDynamicMapIcon(NGCBomber[mobid][5]);
	//if(IsValidDynamic3DTextLabel(NGCBomberText[mobid])) DestroyDynamic3DTextLabel(NGCBomberText[mobid]);
	return 1;
}

public SetNGCBomberStat(mobid,statid){
	NGCBomberStat[mobid] = statid;
	NGCBomber[mobid][3] = 0;
	return 1;
}

public NGCBomberGoTo(mobid,Float:x,Float:y,Float:z,Float:speed){
	NGCBomberCords[mobid][X] = x;
	NGCBomberCords[mobid][Y] = y;
	NGCBomberCords[mobid][Z] = z;
	NGCBomberCords[mobid][SPEED] = speed;
	SetNGCBomberStat(mobid,NGC_NPC_STAT_MANUAL);
	return 1;
}

public OnBomberActive(mobid,Float:x,Float:y,Float:z){
	NGCBomber[mobid][4]++;
	switch(NGCBomber[mobid][4]){
		case 1: {
			new F4[e_float], Float:tmpz, tmptime, buffer[256], b_id = NGCBomber[mobid][6];
			MapAndreasFindZ(x,y,tmpz);
			tmpz += 7.4;
			
			//throw parcel
			format(buffer,sizeof buffer,"Pack dropped at the location %s",BomberTarget[b_id][e_name]);
			SendClientMessageToAll(-1,buffer);

			new pack = CreateDynamicObject(2903,x,y,z,0.0,0.0,0.0,0,0,-1,300.0); //18849
			GetMoveTime(x,y,z,x,y,tmpz,PACK_SPEED,tmptime);
			SetTimerEx("OnPackageLanded",tmptime,false,"dd",mobid,pack);
			MoveDynamicObject(pack,x,y,tmpz,PACK_SPEED,0.0,0.0,0.0);
			
			#if defined CHANGE_DIRECTION_OF_FLIGHT
				GetRandomClockPos(NGCBomberCords[mobid][X],NGCBomberCords[mobid][Y],z,BOMBER_DISTANCE,F4[X],F4[Y],F4[Z],F4[rZ]);
			#else
				GetDynamicObjectRot(NGCBomber[mobid][0],F4[rX],F4[rY],F4[rZ]);
				GetPointInFront3D(NGCBomberCords[mobid][X],NGCBomberCords[mobid][Y],z,0.0,F4[rZ]-90.0,BOMBER_DISTANCE,F4[X],F4[Y],F4[Z]);
			#endif
			NGCBomberGoTo(mobid,F4[X],F4[Y],F4[Z],MOB_SPEED_NORMAL);
		}
		
		case 2: {
			new F4[e_float];
			GetDynamicObjectPos(NGCBomber[mobid][0],F4[X],F4[Y],F4[Z]);
			GetDynamicObjectRot(NGCBomber[mobid][0],F4[rX],F4[rY],F4[rZ]);
			GetPointInFront3D(F4[X],F4[Y],F4[Z],0.0,F4[rZ]-90.0,20000.0,F4[X],F4[Y],F4[Z]);
			
			MoveDynamicObject(NGCBomber[mobid][0],F4[X],F4[Y],F4[Z],100.0,0.0,0.0,F4[rZ]);
			
			SetNGCBomberStat(mobid,NGC_NPC_STAT_STANDBY);
			NGCBomber[mobid][4] = 0;
		}
	}
	return 1;
}

public OnPackageLanded(mobid,objectid){
	//a few seconds ago landed pack
	new F4[e_float];
	GetDynamicObjectPos(objectid,F4[X],F4[Y],F4[Z]);
	MapAndreasFindZ(F4[X],F4[Y],F4[Z]);
	
	//We delete temporary pack
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	F4[Z] += 1.0;
	
	
	//edit this
	//F4[X],F4[Y],F4[Z]
	CreateDynamicCP(F4[X],F4[Y],F4[Z],10.0,0,0,-1,STREAMER_CP_SD);
	
	return 1;
}

//EOF
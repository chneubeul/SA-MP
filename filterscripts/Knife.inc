/******************************************
 * Knife Script v1.3 made by Abyss Morgan *
 ******************************************/
 
 
/*

//to hook functions
Knife_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);

*/

#if !defined Streamer_AppendArrayData
	#error Unknown streamer version
#endif

//3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.1b
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.1b
#elseif (Tryg3D_Version < 0x20102)
	#error Update you 3DTryg.inc to v2.1b
#endif

#define KNIFE_SPEED 		12.0
#define KNIFE_MAX_RADIUS	15.0

new KnifeLockTarget[MAX_PLAYERS],
	KnifeStep[MAX_PLAYERS];

stock GivePlayerDamage(playerid,Float:damage){
	new Float:thp, Float:tarm;
	GetPlayerArmour(playerid,tarm);
	GetPlayerHealth(playerid,thp);
	if(tarm >= damage){
		SetPlayerArmour(playerid,tarm-damage);
	} else if(tarm < damage){
		damage-=tarm;
		SetPlayerArmour(playerid,0.0);
		SetPlayerHealth(playerid,thp-damage);
	} else {
		SetPlayerHealth(playerid,thp-damage);
	}
}

forward KnifeShot(playerid);
forward KnifeDestroy(objectid,targetid);
forward Knife_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);

public Knife_OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(GetPlayerWeapon(playerid) == 4){
		if(newkeys == KEY_FIRE && KnifeStep[playerid] == 1){
			KnifeStep[playerid] = 0;
			KnifeShot(playerid);
		}
		if(newkeys == KEY_HANDBRAKE && KnifeStep[playerid] == 0){
			KnifeStep[playerid] = 1;
		}
	}
	return 1;
}

public KnifeShot(playerid){
	new Float:mx, Float:my, Float:mz, Float:mrz, Float:mtx, Float:mty, Float:mtz, mvw, mint, Float:trz,
		Float:px, Float:py, Float:pz, pvw, pint, mtime;
	GetPlayerPos(playerid,mx,my,mz);
	GetPlayerFacingAngle(playerid,mrz);
	mvw = GetPlayerVirtualWorld(playerid);
	mint = GetPlayerInterior(playerid);
	GetPointInFront2D(mx,my,mrz,KNIFE_MAX_RADIUS,mtx,mty);
	KnifeLockTarget[playerid] = INVALID_PLAYER_ID;
	new Float:ldist = 9000;

	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(i != playerid){
			if(IsPlayerConnected(i)){
				GetPlayerPos(i,px,py,pz);
				pvw = GetPlayerVirtualWorld(i);
				pint = GetPlayerInterior(i);
				if(pvw == mvw && pint == mint){
					if(IsPointNearly2Points3D(px,py,pz, mx,my,mz, mtx,mty,mz, 1.0)){
						new Float:dist = GetDistanceBetweenPoints3D(px,py,pz,mx,my,mz);
						if(dist < ldist){
							ldist = dist;
							KnifeLockTarget[playerid] = i;
						}
					}
				}
			}
		}
	}
	
	CompRotationFloat(mrz+90.0,trz);
	new tmpobj = CreateDynamicObject(335,mx,my,mz,0.0,90.0,trz,mvw,mint,-1);
	
	if(KnifeLockTarget[playerid] == INVALID_PLAYER_ID){
		GetPointInFront3D(mx,my,mz,356.7,mrz,KNIFE_MAX_RADIUS,mtx,mty,mtz);
		GetMoveTime(mx,my,mz,mtx,mty,mtz,KNIFE_SPEED,mtime);
		MoveDynamicObject(tmpobj,mtx,mty,mtz,KNIFE_SPEED,0.0,90.0+20.0,trz);
		SetTimerEx("KnifeDestroy",mtime+1000,0,"dd",tmpobj,INVALID_PLAYER_ID);
	} else {
		GetMoveTime(mx,my,mz,px,py,pz,KNIFE_SPEED,mtime);
		MoveDynamicObject(tmpobj,px,py,pz,KNIFE_SPEED,0.0,90.0,trz);
		SetTimerEx("KnifeDestroy",mtime+250,0,"dd",tmpobj,KnifeLockTarget[playerid]);
	}
	return 1;
}

public KnifeDestroy(objectid,targetid){
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	if(targetid != INVALID_PLAYER_ID){
		GivePlayerDamage(targetid,10.0);
	}
	return 1;
}
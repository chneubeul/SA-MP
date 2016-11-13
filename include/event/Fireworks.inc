/****************************************************************************************************
 *                                                                                                  *
 *                                          Rcon Fireworks                                          *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/event                         *
 * Publication: None                                                                                *
 *                                                                                                  *
 * Plugins: Streamer                                                                                *
 * Modules: 3DTryg                                                                                  *
 *                                                                                                  *
 * File Version: 2.1.0                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 * Streamer Version: 2.8.2                                                                          *
 * 3DTryg Version: 3.0.5                                                                            *
 *                                                                                                  *
 ****************************************************************************************************/

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v3.0.5
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v3.0.5
#elseif (Tryg3D_Version < 30005)
	#error [ADM] Update you 3DTryg.inc to v3.0.5
#endif

#define FIREWORK_ELEMENT			(256)
#define FIREWORKS_SPEED				(5.0)
#define FIREWORKS_RADIUS			(300.0)

new FireworkObj[FIREWORK_ELEMENT], bool:FireworkActive = false;

forward CreateFireworks(Float:x,Float:y,Float:z);
forward DestroyFireworks(tec);

public CreateFireworks(Float:x,Float:y,Float:z){
	FireworkActive = true;
	z+=25.0;
	for(new i = 0; i < FIREWORK_ELEMENT; i++){
		FireworkObj[i] = CreateDynamicObject(354,x,y,z,0.0,0.0,0.0,0,0,-1,200.0);
	}
	new F4[Float3D], tit;
	for(new i = 0; i < 64; i++){
		GetPointInFront3D(x,y,z,0.0,(i*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	for(new i = 64; i < 128; i++){
		GetPointInFront3D(x,y,z,5.0,((i-64)*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	for(new i = 128; i < 192; i++){
		GetPointInFront3D(x,y,z,10.0,((i-128)*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	for(new i = 192; i < 256; i++){
		GetPointInFront3D(x,y,z,15.0,((i-128)*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	GetPointInFront3D(x,y,z,0.0,0.0,FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
	GetMoveTime(x,y,z,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED,tit);
	SetTimerEx("DestroyFireworks",tit,0,"d",1);
	return 1;
}


public DestroyFireworks(tec){
	for(new i = 0; i < FIREWORK_ELEMENT; i++){
		if(IsValidDynamicObject(FireworkObj[i])) DestroyDynamicObject(FireworkObj[i]);
	}
	FireworkActive = false;
	return 1;
}

CMD:xbumm(playerid){
	if(!IsPlayerAdmin(playerid)) return 0;
	if(FireworkActive) return SendClientMessage(playerid,0xFFFFFFFF,"››› Function active");
	new F4[Float3D];
	GetPlayerPos(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
	CreateFireworks(F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
	SendClientMessageToAll(0xFFFFFFFF,"{9E3DFF}››› Fired fireworks");
	return 1;
}

//EOF
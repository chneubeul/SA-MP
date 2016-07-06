/****************************************************************************************************
 *                                                                                                  *
 *                                          Rcon Fireworks                                          *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/event                         *
 *                                                                                                  *
 * Plugins: Streamer                                                                                *
 * Modules: 3DTryg, ATM                                                                             *
 *                                                                                                  *
 * File Version: 2.0.1                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 * Streamer Version: 2.8.2                                                                          *
 * 3DTryg Version: 2.6.2                                                                            *
 * ATM Version: 1.4.2                                                                               *
 *                                                                                                  *
 ****************************************************************************************************/

#if !defined Streamer_AppendArrayData
	#error [ADM] Unknown Streamer Version
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v2.6.2
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v2.6.2
#elseif (Tryg3D_Version < 20602)
	#error [ADM] Update you 3DTryg.inc to v2.6.2
#endif

//Check Version ATM.inc
#if !defined _ATM_Core
	#error [ADM] You need ATM.inc v1.4.2
#elseif !defined ATM_Version
	#error [ADM] Update you ATM.inc to v1.4.2
#elseif (ATM_Version < 10402)
	#error [ADM] Update you ATM.inc to v1.4.2
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
	new F4[e_float], tit;
	for(new i = 0; i < 64; i++){
		GetPointInFront3D(x,y,z,0.0,(i*5.625),FIREWORKS_RADIUS,F4[tX],F4[tY],F4[tZ]);
		MoveDynamicObject(FireworkObj[i],F4[tX],F4[tY],F4[tZ],FIREWORKS_SPEED);
	}
	for(new i = 64; i < 128; i++){
		GetPointInFront3D(x,y,z,5.0,((i-64)*5.625),FIREWORKS_RADIUS,F4[tX],F4[tY],F4[tZ]);
		MoveDynamicObject(FireworkObj[i],F4[tX],F4[tY],F4[tZ],FIREWORKS_SPEED);
	}
	for(new i = 128; i < 192; i++){
		GetPointInFront3D(x,y,z,10.0,((i-128)*5.625),FIREWORKS_RADIUS,F4[tX],F4[tY],F4[tZ]);
		MoveDynamicObject(FireworkObj[i],F4[tX],F4[tY],F4[tZ],FIREWORKS_SPEED);
	}
	for(new i = 192; i < 256; i++){
		GetPointInFront3D(x,y,z,15.0,((i-128)*5.625),FIREWORKS_RADIUS,F4[tX],F4[tY],F4[tZ]);
		MoveDynamicObject(FireworkObj[i],F4[tX],F4[tY],F4[tZ],FIREWORKS_SPEED);
	}
	GetPointInFront3D(x,y,z,0.0,0.0,FIREWORKS_RADIUS,F4[tX],F4[tY],F4[tZ]);
	GetMoveTime(x,y,z,F4[tX],F4[tY],F4[tZ],FIREWORKS_SPEED,tit);
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
	new F4[e_float];
	GetPlayerPos(playerid,F4[X],F4[Y],F4[Z]);
	CreateFireworks(F4[X],F4[Y],F4[Z]);
	SendClientMessageToAll(0xFFFFFFFF,"{9E3DFF}››› Fired fireworks");
	return 1;
}

//EOF
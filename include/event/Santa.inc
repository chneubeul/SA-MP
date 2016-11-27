/****************************************************************************************************
 *                                                                                                  *
 *                                           Santa Gifts                                            *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/event                         *
 * Publication: http://forum.sa-mp.com/showthread.php?t=595265                                      *
 *                                                                                                  *
 * Plugins: Streamer, ColAndreas/MapAndreas                                                         *
 * Modules: 3DTryg, StreamerFunction                                                                *
 *                                                                                                  *
 * File Version: 1.4.2                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 * Streamer Version: 2.8.2                                                                          *
 * MapAndreas Version: 1.2.1                                                                        *
 * ColAndreas Version: 1.4.0                                                                        *
 * 3DTryg Version: 3.0.5                                                                            *
 * StreamerFunction Version: 2.5.4                                                                  *
 *                                                                                                  *
 * Callbacks:                                                                                       *
 * OnSantaPickupReward(playerid);                                                                   *
 *                                                                                                  *
 ****************************************************************************************************/

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

#if !defined Tryg3DMapAndreasFindZ
	#error [ADM] Unknown ColAndreas/MapAndreas Version
#endif

//Check Version StreamerFunction.inc
#if !defined _streamer_spec
	#error [ADM] You need StreamerFunction.inc v2.5.4
#elseif !defined Streamer_Spec_Version
	#error [ADM] Update you StreamerFunction.inc to v2.5.4
#elseif (Streamer_Spec_Version < 20504)
	#error [ADM] Update you StreamerFunction.inc to v2.5.4
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v3.0.5
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v3.0.5
#elseif (Tryg3D_Version < 30005)
	#error [ADM] Update you 3DTryg.inc to v3.0.5
#endif

#if defined _santa_gifts
	#endinput
#endif
#define _santa_gifts

#define	MAX_SANTAGIFTS			(100)
#define REFRESH_SANTAGIFTS		(2*60*60*1000)	//2 hour

new SantaGift[MAX_SANTAGIFTS],
	SantaTimer[1];

#if defined SANTA_IS_EASTER_EVENT
	//Easter
	new SantaPickupModel[][1] = {
		{19341},
		{19342},
		{19343},
		{19344},
		{19345}
	};
#elseif defined SANTA_IS_EASTER_HALLOWEEN
	//Halloween
	new SantaPickupModel[][1] = {
		{19320},	//pumpkin
		{19527},	//cauldron
		{19339}		//coffin
	};
#else
	//Christmas
	new SantaPickupModel[][1] = {
		{19054},
		{19055},
		{19056},
		{19057},
		{19058}
	};
#endif

stock SantaInit(){
	if(!IsMapAndreasInit()){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: Invalid MapAndreas Memory.");
		}
	} else {
		for(new i = 0; i < MAX_SANTAGIFTS; i++){
			SantaGiftCreate(i);
		}
		SantaTimer[0] = SetTimerEx("SantaReset",REFRESH_SANTAGIFTS,true,"d",1);
	}
}

forward SantaPickUp(playerid,pickupid);
forward SantaReset(tec);
forward SantaGiftCreate(giftid);
forward SantaGiftReset(giftid);

new bool:CRC_SantaInit = true,
	bool:CRC_SantaExit = true;

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_SantaInit){
		CRC_SantaInit = false;
		SantaInit();
	}
	#if defined SantaOnGameModeInit
		SantaOnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SantaOnGameModeInit
#if defined SantaOnGameModeInit
	forward SantaOnGameModeInit();
#endif

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_SantaInit){
		CRC_SantaInit = false;
		SantaInit();
	}
	#if defined SantaOnFilterScriptInit
		SantaOnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SantaOnFilterScriptInit
#if defined SantaOnFilterScriptInit
	forward SantaOnFilterScriptInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_SantaExit){
		CRC_SantaExit = false;
		KillTimer(SantaTimer[0]);
	}
	#if defined SantaOnFilterScriptExit
		SantaOnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit SantaOnFilterScriptExit
#if defined SantaOnFilterScriptExit
	forward SantaOnFilterScriptExit();
#endif

forward OnSantaPickupReward(playerid);

public SantaPickUp(playerid,pickupid){
	for(new i = 0; i < MAX_SANTAGIFTS; i++){
		if(pickupid == SantaGift[i]){
			SantaGiftReset(i);
			CallLocalFunction("OnSantaPickupReward","d",playerid);
			return 1;
		}
	}
	return 1;
}

//OnPlayerPickUpDynamicPickup
public OnPlayerPickUpDynamicPickup(playerid,pickupid){
	SantaPickUp(playerid,pickupid);
	#if defined Santa_OnPlayerPickUpPickup
		Santa_OnPlayerPickUpPickup(playerid,pickupid);
	#endif
	return 1;
}

#if defined _LS_OnPlayerPickUpDynamicPickup
	#undef OnPlayerPickUpDynamicPickup
#else
	#define _LS_OnPlayerPickUpDynamicPickup
#endif
#define OnPlayerPickUpDynamicPickup Santa_OnPlayerPickUpPickup
#if defined Santa_OnPlayerPickUpPickup
	forward Santa_OnPlayerPickUpPickup(playerid,pickupid);
#endif

public SantaReset(tec){
	for(new i = 0; i < MAX_SANTAGIFTS; i++){
		SantaGiftReset(i);
	}
	return 1;
}

public SantaGiftCreate(giftid){
	new smodel = random(sizeof(SantaPickupModel)), Float:piox, Float:pioy, Float:pioz;
	
	SantaErrorPos:
	GetRandomPointInCube(-3000.0,-3000.0,0.0,3000.0,3000.0,1.0,piox,pioy,pioz);
	Tryg3DMapAndreasFindZ(piox,pioy,pioz);
	if(pioz <= 0.0) goto SantaErrorPos; //water
	
	pioz+=1.0;
	SantaGift[giftid] = CreateDynamicPickup(SantaPickupModel[smodel][0],2,piox,pioy,pioz,0,0);
	return 1;
}

public SantaGiftReset(giftid){
	new smodel = random(sizeof(SantaPickupModel)), Float:piox, Float:pioy, Float:pioz;
	
	SantaErrorPos:
	GetRandomPointInCube(-3000.0,-3000.0,0.0,3000.0,3000.0,1.0,piox,pioy,pioz);
	Tryg3DMapAndreasFindZ(piox,pioy,pioz);
	if(pioz <= 0.0) goto SantaErrorPos; //water
	
	pioz+=1.0;
	SetDynamicPickupPos(SantaGift[giftid],piox,pioy,pioz);
	SetDynamicPickupModel(SantaGift[giftid],SantaPickupModel[smodel][0]);
	return 1;
}

//EOF
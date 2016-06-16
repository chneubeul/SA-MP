/****************************************************************************************************
 *                                                                                                  *
 * Santa Gifts v1.3 made by Abyss Morgan                                                            *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/event                         *
 *                                                                                                  *
 ****************************************************************************************************/

/*
//to hook function
SantaPickUpDynamicPickup(playerid,pickupid);	//OnPlayerPickUpDynamicPickup

//edit your reward in 'SantaPickUpDynamicPickup'

*/


//Check Version StreamerFunction.inc
#if !defined _streamer_spec
	#error You need StreamerFunction.inc v2.3D
#elseif !defined Streamer_Spec_Version
	#error Update you StreamerFunction.inc to v2.3D
#elseif (Streamer_Spec_Version < 20304)
	#error Update you StreamerFunction.inc to v2.3D
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.5C
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.5C
#elseif (Tryg3D_Version < 20503)
	#error Update you 3DTryg.inc to v2.5C
#endif

//MapAndreasEx.inc
#if !defined MapAndreasFindZ
	#error You need MapAndreasEx.inc
#endif

#define	MAX_SANTAGIFTS			(100)
#define REFRESH_SANTAGIFTS		(2*60*60*1000)	//2 hour

new SantaGift[MAX_SANTAGIFTS],
	SantaTimer[1];

//Christmas
new SantaPickupModel[][1] = {
	{19054},
	{19055},
	{19056},
	{19057},
	{19058}
};

/*
//Easter
new SantaPickupModel[][1] = {
	{19341},
	{19342},
	{19343},
	{19344},
	{19345}
};


//Halloween
new SantaPickupModel[][1] = {
	{19320},	//pumpkin
	{19527},	//cauldron
	{19339}		//coffin
};
*/

forward SantaPickUpDynamicPickup(playerid,pickupid);
forward SantaReset(tec);
forward SantaGiftCreate(giftid);
forward SantaGiftReset(giftid);

public OnGameModeInit(){
	SafeMapAndreasInit();
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

public OnFilterScriptInit(){
	SafeMapAndreasInit();
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


public OnFilterScriptExit(){
	KillTimer(SantaTimer[0]);
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

public SantaPickUpDynamicPickup(playerid,pickupid){
	for(new i = 0; i < MAX_SANTAGIFTS; i++){
		if(pickupid == SantaGift[i]){
			SantaGiftReset(i);
			
			
			//your reward
		}
	}
	return 1;
}


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
	MapAndreasFindZ(piox,pioy,pioz);
	if(pioz == 0) goto SantaErrorPos; //water
	
	pioz+=1.0;
	SantaGift[giftid] = CreateDynamicPickup(SantaPickupModel[smodel][0],2,piox,pioy,pioz,0,0);
	return 1;
}

public SantaGiftReset(giftid){
	new smodel = random(sizeof(SantaPickupModel)), Float:piox, Float:pioy, Float:pioz;
	
	SantaErrorPos:
	GetRandomPointInCube(-3000.0,-3000.0,0.0,3000.0,3000.0,1.0,piox,pioy,pioz);
	MapAndreasFindZ(piox,pioy,pioz);
	if(pioz == 0) goto SantaErrorPos; //water
	
	pioz+=1.0;
	SetDynamicPickupPos(SantaGift[giftid],piox,pioy,pioz);
	SetDynamicPickupModel(SantaGift[giftid],SantaPickupModel[smodel][0]);
	return 1;
}

//EOF
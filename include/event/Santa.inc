/*****************************************
 * Santa Gifts v1.2 made by Abyss Morgan *
 *****************************************/

/*

//to hook functions
Santa_GameModeInit();
Santa_FilterScriptInit();
Santa_FilterScriptExit();
Santa_PickUpDynamicPickup(playerid,pickupid);	//OnPlayerPickUpDynamicPickup

//edit your reward in 'Santa_PickUpDynamicPickup'
*/


//StreamerFunction.inc
#if !defined _streamer_spec
	#error You need StreamerFunction.inc v2.0d
#elseif !defined Streamer_Spec_Version
	#error Update you StreamerFunction.inc to v2.0d
#elseif (Streamer_Spec_Version < 20004)
	#error Update you StreamerFunction.inc to v2.0d
#endif

//3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.1b
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.1b
#elseif (Tryg3D_Version < 20102)
	#error Update you 3DTryg.inc to v2.1b
#endif

//MapAndreasEx.inc
#if !defined MapAndreasFindZ
	#error You need MapAndreasEx.inc
#endif

#define	MAX_SANTA_GIFTS			(100)
#define REFRESH_SANTA_GIFTS		(2*60*60*1000)	//2 hour

new SantaGift[MAX_SANTA_GIFTS],
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

forward Santa_GameModeInit();
forward Santa_FilterScriptInit();
forward Santa_FilterScriptExit();
forward Santa_PickUpDynamicPickup(playerid,pickupid);
forward Santa_Reset(tec);
forward Santa_GiftCreate(giftid);
forward Santa_GiftReset(giftid);

public Santa_GameModeInit(){
	if(!IsMapAndreasInit()){
		print("[ADM] Error: Invalid MapAndreas Memory.");
	} else {
		for(new i = 0; i < MAX_SANTA_GIFTS; i++){
			Santa_GiftCreate(i);
		}
		SantaTimer[0] = SetTimerEx("Santa_Reset",REFRESH_SANTA_GIFTS,true,"d",1);
	}
	return 1;
}

public Santa_FilterScriptInit(){
	Santa_GameModeInit();
	return 1;
}

public Santa_FilterScriptExit(){
	KillTimer(SantaTimer[0]);
	return 1;
}

public Santa_PickUpDynamicPickup(playerid,pickupid){
	for(new i = 0; i < MAX_SANTA_GIFTS; i++){
		if(pickupid == SantaGift[i]){
			Santa_GiftReset(i);
			
			
			//your reward
		}
	}
	return 1;
}


public Santa_Reset(tec){
	for(new i = 0; i < MAX_SANTA_GIFTS; i++){
		Santa_GiftReset(i);
	}
	return 1;
}

public Santa_GiftCreate(giftid){
	new smodel = random(sizeof(SantaPickupModel)), Float:piox, Float:pioy, Float:pioz;
	
	SantaErrorPos:
	GetRandomPointInCube(-3000.0,-3000.0,0.0,3000.0,3000.0,1.0,piox,pioy,pioz);
	MapAndreasFindZ(piox,pioy,pioz);
	if(pioz == 0) goto SantaErrorPos; //water
	
	pioz+=1.0;
	SantaGift[giftid] = CreateDynamicPickup(SantaPickupModel[smodel][0],2,piox,pioy,pioz,0,0);
	return 1;
}

public Santa_GiftReset(giftid){
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
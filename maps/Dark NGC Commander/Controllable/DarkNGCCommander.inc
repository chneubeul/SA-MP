/****************************************************************************************************
 *                                                                                                  *
 * Controllable Dark NGC Commander v1.0 by Abyss Morgan                                             *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/maps                                  *
 *                                                                                                  *
 ****************************************************************************************************/

#define DARK_NGC_SPAWN_X		(-93.976776) // 3701.969482 -49.696922
#define DARK_NGC_SPAWN_Y		(3701.969482)
#define DARK_NGC_SPAWN_Z		(-130.0)
#define DARK_NGC_SPAWN_A		(180.0)

new DarkNGC[150],
	bool:IsDarkNGC[MAX_PLAYERS],
	Float:DarkNGCSpeed = 5.0,
	bool:DarkNGCMoveType = false,
	DarkNGCDrive[11] = INVALID_PLAYER_ID,
	DarkNGCLaunchA[MAX_PLAYERS],
	DarkNGCLaunchB[MAX_PLAYERS];

stock FindDarkNGCSlot(playerid){
	for(new i = 0, j = sizeof(DarkNGCDrive); i < j; i++){
		if(DarkNGCDrive[i] == playerid) return i;
	}
	return -1;
}

stock FindDarkNGCFreeSlot(){
	for(new i = 1, j = sizeof(DarkNGCDrive); i < j; i++){
		if(DarkNGCDrive[i] == INVALID_PLAYER_ID) return i;
	}
	return -1;
}

stock ExitPlayerDarkNGC(playerid){
	if(playerid == INVALID_PLAYER_ID) return 0;
	if(!IsDarkNGC[playerid]) return 0;
	new k = FindDarkNGCSlot(playerid);
	if(k == -1) return 0;
	TogglePlayerSpectating(playerid,0);
	//SpawnPlayer(playerid);
	SetCameraBehindPlayer(playerid);
	IsDarkNGC[playerid] = false;
	DarkNGCDrive[k] = INVALID_PLAYER_ID;
	return 1;
}

stock SetDarkNGCShipColor(color){
	foX(i,2,17){
		SetObjectMaterial(DarkNGC[i],0,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],1,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],2,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],3,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],4,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],5,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],6,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],7,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],8,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],9,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],10,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],11,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],12,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],13,10817,"airportgnd_sfse","black64",0x00000000); 
	}
	foX(i,18,29){
		SetObjectMaterial(DarkNGC[i],0,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],1,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],2,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],5,10817,"airportgnd_sfse","black64",0x00000000); 
	}
	foX(i,30,45){
		SetObjectMaterial(DarkNGC[i],0,5150,"wiresetc_las2","metpat64",0xFF909090); 
		SetObjectMaterial(DarkNGC[i],1,5150,"wiresetc_las2","metpat64",0xFF909090); 
		SetObjectMaterial(DarkNGC[i],2,5150,"wiresetc_las2","metpat64",0xFF909090); 
		SetObjectMaterial(DarkNGC[i],4,5150,"wiresetc_las2","metpat64",0xFF909090); 
		SetObjectMaterial(DarkNGC[i],5,5150,"wiresetc_las2","metpat64",0xFF909090); 
	}
	foX(i,46,65){
		SetObjectMaterial(DarkNGC[i],0,8463,"vgseland","triadcarpet2",0xFF909090); 
	}
	foX(i,66,105){
		SetObjectMaterial(DarkNGC[i],0,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],1,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],2,2707,"Shopping","white",color); 
	}
	foX(i,106,115){
		SetObjectMaterial(DarkNGC[i],0,5150,"wiresetc_las2","metpat64",0xFF3B3B3B); 
		SetObjectMaterial(DarkNGC[i],1,5150,"wiresetc_las2","metpat64",0xFF3B3B3B); 
		SetObjectMaterial(DarkNGC[i],3,5150,"wiresetc_las2","metpat64",0xFF3B3B3B); 
	}
	foX(i,116,149){
		SetObjectMaterial(DarkNGC[i],0,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],1,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],2,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],3,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],4,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],5,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],6,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],7,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],8,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],9,2707,"Shopping","white",color); 
		SetObjectMaterial(DarkNGC[i],10,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],11,10817,"airportgnd_sfse","black64",0x00000000); 
		SetObjectMaterial(DarkNGC[i],12,10817,"airportgnd_sfse","black64",0x00000000); 
	}
}


stock DarkNGCInit(){
	for(new i = 0, j = sizeof(DarkNGCDrive); i < j; i++){
		DarkNGCDrive[i] = INVALID_PLAYER_ID;
	}
	//ship
	new idx = 0;
	DarkNGC[idx++] = CreateObject(1489,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(10381,180.000000,365.000000,45.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,180.000000,365.000000,45.000000,315.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-180.000000,365.000000,45.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-180.000000,365.000000,45.000000,315.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,180.000000,345.000000,45.000000,45.000000,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-180.000000,345.000000,45.000000,315.000000,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,180.000000,345.000000,45.000000,315.000000,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-180.000000,345.000000,45.000000,45.000000,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-280.000000,-155.000000,45.000000,44.994998,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-280.000000,-135.000000,45.000000,314.994995,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-280.000000,-155.000000,45.000000,314.994995,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,-280.000000,-135.000000,45.000000,44.994998,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,280.000000,-135.000000,45.000000,314.994995,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,280.000000,-135.000000,45.000000,44.994998,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,280.000000,-155.000000,45.000000,314.994995,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10381,280.000000,-155.000000,45.000000,44.994998,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,-205.000000,400.000000,75.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,200.000000,300.000000,75.000000,45.000000,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,-205.000000,300.000000,75.000000,45.000000,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,200.000000,400.000000,75.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,75.000000,400.000000,0.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,-75.000000,400.000000,0.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,275.000000,400.000000,0.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,-275.000000,400.000000,0.000000,45.000000,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,310.000000,-100.000000,75.000000,44.994998,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,310.000000,-200.000000,75.000000,45.000000,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,-310.000000,-100.000000,75.000000,44.994998,90.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4602,-310.000000,-200.000000,75.000000,44.994998,90.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,70.000000,-140.000000,0.000000,90.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-274.000000,-170.000000,0.000000,90.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,274.000000,-170.000000,0.000000,0.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,70.000000,85.000000,0.000000,90.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-70.000000,85.000000,0.000000,0.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,274.000000,55.000000,0.000000,0.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-274.000000,55.000000,0.000000,90.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,274.000000,280.000000,0.000000,0.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,70.000000,305.000000,0.000000,90.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-70.000000,305.000000,0.000000,0.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-274.000000,280.000000,0.000000,90.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-70.000000,-140.000000,0.000000,0.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,70.000000,-365.000000,0.000000,90.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-70.000000,-365.000000,0.000000,0.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,130.000000,365.000000,0.000000,0.000000,270.000000,180.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4563,-130.000000,365.000000,0.000000,90.000000,270.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,215.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,215.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,165.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,115.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,65.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,115.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,165.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,65.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,-35.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,15.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,-35.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,15.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,-85.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,-85.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,-135.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,-185.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,-60.000000,-235.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,-185.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,-135.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(8397,60.000000,-235.000000,27.000000,0.000000,45.000000,270.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-180.000000,450.000000,75.000000,270.000000,0.000000,315.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-230.000000,450.000000,75.000000,270.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,200.000000,485.000000,75.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,175.000000,450.000000,75.000000,270.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-205.000000,485.000000,75.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,225.000000,450.000000,75.000000,270.000000,0.000000,315.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,200.000000,450.000000,100.000000,315.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-205.000000,450.000000,50.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,200.000000,450.000000,50.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-205.000000,450.000000,100.000000,315.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-75.000000,485.000000,0.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-50.000000,450.000000,0.000000,270.000000,0.000000,315.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,75.000000,485.000000,0.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-100.000000,450.000000,0.000000,270.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,100.000000,450.000000,0.000000,270.000000,0.000000,315.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,50.000000,450.000000,0.000000,270.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,75.000000,450.000000,25.000000,315.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,75.000000,450.000000,-25.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-75.000000,450.000000,-25.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-75.000000,450.000000,25.000000,315.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-300.000000,450.000000,0.000000,270.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-250.000000,450.000000,0.000000,270.000000,0.000000,315.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-275.000000,485.000000,0.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-275.000000,450.000000,25.000000,315.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-275.000000,450.000000,-25.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,275.000000,485.000000,0.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,300.000000,450.000000,0.000000,270.000000,0.000000,315.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,250.000000,450.000000,0.000000,270.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,275.000000,450.000000,25.000000,315.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,275.000000,450.000000,-25.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-310.000000,-15.000000,75.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,335.000000,-50.000000,75.000000,270.000000,0.000000,314.994995,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-335.000000,-50.000000,75.000000,270.000000,0.000000,44.994998,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-310.000000,-50.000000,50.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-310.000000,-50.000000,100.000000,314.994995,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,310.000000,-15.000000,75.000000,270.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,-285.000000,-50.000000,75.000000,270.000000,0.000000,314.994995,1300.0);
	DarkNGC[idx++] = CreateObject(7236,285.000000,-50.000000,75.000000,270.000000,0.000000,44.994998,1300.0);
	DarkNGC[idx++] = CreateObject(7236,310.000000,-50.000000,100.000000,314.994995,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(7236,310.000000,-50.000000,50.000000,225.000000,0.000000,0.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,330.000000,-390.000000,5.000000,180.000000,270.000000,135.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,-330.000000,-390.000000,5.000000,180.000000,90.000000,225.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,240.000000,-390.000000,5.000000,180.000000,270.000000,65.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,-240.000000,-390.000000,5.000000,180.000000,90.000000,295.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,-120.000000,-585.000000,5.000000,180.000000,90.000000,235.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,120.000000,-585.000000,5.000000,180.000000,270.000000,125.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,70.000000,-585.000000,5.000000,180.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,-70.000000,-585.000000,5.000000,180.000000,270.000000,90.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,-20.000000,-585.000000,5.000000,180.000000,270.000000,125.000000,1300.0);
	DarkNGC[idx++] = CreateObject(4585,20.000000,-585.000000,5.000000,180.000000,270.000000,55.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,167.500000,37.500000,0.000000,0.000000,325.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,167.500000,37.500000,0.000000,0.000000,125.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,167.500000,20.000000,180.000000,0.000000,215.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,167.500000,20.000000,0.000000,180.000000,235.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,325.000000,37.500000,0.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,325.000000,20.000000,180.000000,0.000000,135.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,-275.000000,37.500000,0.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,-275.000000,20.000000,180.000000,0.000000,135.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,-432.500000,37.500000,0.000000,0.000000,325.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,-432.500000,20.000000,0.000000,180.000000,235.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,-432.500000,20.000000,180.000000,0.000000,215.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,-432.500000,37.500000,0.000000,0.000000,125.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,325.000000,-22.500000,0.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,325.000000,-40.000000,180.000000,0.000000,135.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,167.500000,-22.500000,0.000000,0.000000,125.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,167.500000,-22.500000,0.000000,0.000000,325.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,167.500000,-40.000000,0.000000,180.000000,235.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,167.500000,-40.000000,180.000000,0.000000,215.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,-275.000000,-40.000000,180.000000,0.000000,135.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,0.000000,-275.000000,-22.500000,0.000000,0.000000,45.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,-432.500000,-22.500000,0.000000,0.000000,125.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,-432.500000,-22.500000,0.000000,0.000000,325.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,187.299804,-432.500000,-40.000000,0.000000,180.000000,235.000000,1300.0);
	DarkNGC[idx++] = CreateObject(10755,-187.000000,-432.500000,-40.000000,180.000000,0.000000,215.000000,1300.0);
	
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	DarkNGC[idx++] = CreateObject(1489,0.000000,-200.000000,100.000000,0.000000,0.000000,0.000000,1300.0); //camera
	foX(i,1,149){
		new F4[e_float];
		GetObjectPosAndRot(DarkNGC[i],F4[X],F4[Y],F4[Z],F4[rX],F4[rY],F4[rZ]);
		AttachObjectToObject(DarkNGC[i],DarkNGC[0],F4[X],F4[Y],F4[Z],F4[rX],F4[rY],F4[rZ],1);
	}

	SetDarkNGCShipColor(0xFFFF0000);
	
	SetObjectPosAndRot(DarkNGC[0],DARK_NGC_SPAWN_X,DARK_NGC_SPAWN_Y,DARK_NGC_SPAWN_Z,0.0,0.0,DARK_NGC_SPAWN_A-180.0);
}

stock DarkNGCExit(){
	for(new i = 0, j = sizeof(DarkNGCDrive); i < j; i++){
		if(DarkNGCDrive[i] != INVALID_PLAYER_ID){
			ExitPlayerDarkNGC(DarkNGCDrive[i]);
		}
	}
	foX(i,0,149){
		if(IsValidObject(DarkNGC[i])) DestroyObject(DarkNGC[i]);
	}
}

CMD:darkngc(playerid,params[]){
	if(isnull(params)) return SendClientMessage(playerid,0xFFFFFFFF,"Usage: /darkngc <0/1> 0 - driver, 1 - passenger");
	new pass_id = -1;
	sscanf(params,"d",pass_id);
	if(pass_id == 0 && DarkNGCDrive[0] != INVALID_PLAYER_ID) return SendClientMessage(playerid,0xFFFFFFFF,"Ship already it has driver");
	if(pass_id == 1) pass_id = FindDarkNGCFreeSlot();
	if(pass_id == -1) return SendClientMessage(playerid,0xFFFFFFFF,"Ship is full");
	
	DarkNGCDrive[pass_id] = playerid;
	TogglePlayerSpectating(playerid,1);
	IsDarkNGC[playerid] = true;
	switch(pass_id){
		case 0: AttachCameraToObject(playerid,DarkNGC[1]);
		case 1..10: AttachCameraToObject(playerid,DarkNGC[pass_id+139]);
	}
	return 1;
}

CMD:darkngccamera(playerid,params[]){
	if(!IsDarkNGC[playerid]) return SendClientMessage(playerid,0xFFFFFFFF,"You're not in the ship!");
	new cm_x = -1, cm_y = -1, cm_z = -1,
		Float:mod_x, Float:mod_y, Float:mod_z;
	sscanf(params,"ddd",cm_y,cm_x,cm_z);
	if(isnull(params)) return SendClientMessage(playerid,0xFFFFFFFF,"Usage: /darkngccamera <front: 1 - 5> <side: 1 - 5> <height: 1 - 3>");
	if(cm_x < 1 || cm_x > 5) return SendClientMessage(playerid,0xFFFFFFFF,"Side camera ID: 1 - 5");
	if(cm_y < 1 || cm_y > 5) return SendClientMessage(playerid,0xFFFFFFFF,"Front camera ID: 1 - 5");
	if(cm_z < 1 || cm_z > 3) return SendClientMessage(playerid,0xFFFFFFFF,"Height camera ID: 1 - 3");
	
	switch(cm_x){
		case 1: mod_x = -200.0;
		case 2: mod_x = -100.0;
		case 3: mod_x = 0.0;
		case 4: mod_x = 100.0;
		case 5: mod_x = 200.0;
	}
	switch(cm_y){
		case 1: mod_y = -400.0;
		case 2: mod_y = -200.0;
		case 3: mod_y = 0.0;
		case 4: mod_y = 200.0;
		case 5: mod_y = 400.0;
	}
	switch(cm_z){
		case 1: mod_z = 100.0;
		case 2: mod_z = 0.0;
		case 3: mod_z = -100.0;
	}
	
	new k = FindDarkNGCSlot(playerid);
	switch(k){
		case 0: {
			AttachObjectToObject(DarkNGC[1],DarkNGC[0],mod_x,mod_y,mod_z,0.000000,0.000000,0.000000,1);
			AttachCameraToObject(playerid,DarkNGC[1]);
		}
		case 1..10:{
			AttachObjectToObject(DarkNGC[k+139],DarkNGC[0],mod_x,mod_y,mod_z,0.000000,0.000000,0.000000,1);
			AttachCameraToObject(playerid,DarkNGC[k+139]);
		}
	}
	return 1;
}

stock OnDarkNGCControl(playerid){
	new Keys, ud, lr;
	GetPlayerKeys(playerid,Keys,ud,lr);
	
	new F4[e_float];
	GetObjectPosAndRot(DarkNGC[0],F4[X],F4[Y],F4[Z],F4[rX],F4[rY],F4[rZ]);
	
	if(DarkNGCMoveType){
		if(ud == KEY_UP){
			//up move
			GetObjectPosAndRot(DarkNGC[0],F4[X],F4[Y],F4[Z],F4[rX],F4[rY],F4[rZ]);
			if(F4[Z]+DarkNGCSpeed < 1000.0){
				MoveObject(DarkNGC[0],F4[X],F4[Y],F4[Z]+DarkNGCSpeed,DarkNGCSpeed,F4[rX],F4[rY],F4[rZ]);
			}
		} else if(ud == KEY_DOWN){
			//down move
			GetObjectPosAndRot(DarkNGC[0],F4[X],F4[Y],F4[Z],F4[rX],F4[rY],F4[rZ]);
			if(F4[Z]-DarkNGCSpeed > -80.0){
				MoveObject(DarkNGC[0],F4[X],F4[Y],F4[Z]-DarkNGCSpeed,DarkNGCSpeed,F4[rX],F4[rY],F4[rZ]);
			}
		}
	} else {
		if(ud == KEY_UP){
			GetPointInFront2D(F4[X],F4[Y],CompRotationFloat(F4[rZ]-180.0),DarkNGCSpeed,F4[tX],F4[tY]);
			MoveObject(DarkNGC[0],F4[tX],F4[tY],F4[Z],DarkNGCSpeed,F4[rX],F4[rY],F4[rZ]);
		} else if(ud == KEY_DOWN){
			GetPointInFront2D(F4[X],F4[Y],CompRotationFloat(F4[rZ]),DarkNGCSpeed,F4[tX],F4[tY]);
			MoveObject(DarkNGC[0],F4[tX],F4[tY],F4[Z],DarkNGCSpeed,F4[rX],F4[rY],F4[rZ]);
		}
	}
	if(lr == KEY_LEFT){
		MoveObject(DarkNGC[0],F4[X],F4[Y],F4[Z]+0.05,0.05,F4[rX],F4[rY],F4[rZ]+1.0);
	} else if(lr == KEY_RIGHT){
		MoveObject(DarkNGC[0],F4[X],F4[Y],F4[Z]+0.05,0.05,F4[rX],F4[rY],F4[rZ]-1.0);
	}
 
}

stock DarkNGCKeyUpdate(playerid,newkeys,oldkeys){
	new k = FindDarkNGCSlot(playerid);
	if(k == -1) return 0;
	
	if(KEY_PRESSED(KEY_SECONDARY_ATTACK)){
		ExitPlayerDarkNGC(playerid);
	} else if(KEY_PRESSED(KEY_FIRE)){
		if(GetTickCount()-DarkNGCLaunchA[playerid] < 200){
			
		} else {
			new Float:rx, Float:rz,
				Float:x, Float:y, Float:z,
				Float:tx, Float:ty, Float:tz;
			
			GetPlayerCameraPos(playerid,x,y,z);
			GetPlayerCameraRotation(playerid,rx,rz);

			GetPointInFrontOnGround(x,y,z,rx,rz,tx,ty,tz,1500.0);
			DarkNGCLaunchA[playerid] = GetTickCount();
			MissileLaunch(MISSILE_TYPE_EXPLODE_NORMAL,8.0,25.0,35.0,x,y,z,0,0,-1,500.0,MISSILE_OBJECT_NORMAL,tx,ty,tz);
			
			GameTextForPlayer(playerid,"Missile Launch",1000,4);
		}
	}

	if(DarkNGCDrive[0] == playerid){
		if(KEY_PRESSED(KEY_JUMP)){
			if(GetTickCount()-DarkNGCLaunchB[playerid] < 30000){
				GameTextForPlayer(playerid,"Heavy Missile Overheating",1000,4);
			} else {
				new Float:rx, Float:rz,
					Float:x, Float:y, Float:z,
					Float:tx, Float:ty, Float:tz,
					Float:nrx, Float:nrz;
				
				GetPlayerCameraPos(playerid,x,y,z);
				GetPlayerCameraRotation(playerid,rx,rz);
				
				DarkNGCLaunchB[playerid] = GetTickCount();
				
				CompRotationFloat(rx-10.0,nrx);
				for(new i = 1; i <= 30; i++){
					CompRotationFloat(rz+(75-(i*3))+1,nrz);
					GetPointInFrontOnGround(x,y,z,nrx,nrz,tx,ty,tz,3000.0);
					MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,10.0,25.0,45.0,x,y,z,0,0,-1,500.0,MISSILE_OBJECT_BIG,tx,ty,tz);
				}
				
				for(new i = 1; i <= 30; i++){
					CompRotationFloat(rz+(75-(i*3))+1,nrz);
					GetPointInFrontOnGround(x,y,z,rx,nrz,tx,ty,tz,3000.0);
					MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,10.0,25.0,45.0,x,y,z,0,0,-1,500.0,MISSILE_OBJECT_BIG,tx,ty,tz);
				}
				
				CompRotationFloat(rx+10.0,nrx);
				for(new i = 1; i <= 30; i++){
					CompRotationFloat(rz+(75-(i*3))+1,nrz);
					GetPointInFrontOnGround(x,y,z,nrx,nrz,tx,ty,tz,3000.0);
					MissileLaunch(MISSILE_TYPE_EXPLODE_HUGE,10.0,25.0,45.0,x,y,z,0,0,-1,500.0,MISSILE_OBJECT_BIG,tx,ty,tz);
				}
				GameTextForPlayer(playerid,"Heavy Missile Launch",2000,4);
			}
		} else if(KEY_PRESSED(KEY_WALK)){
			DarkNGCMoveType = (!DarkNGCMoveType);
			if(DarkNGCMoveType){
				GameTextForPlayer(playerid,"Move Type Height",1000,4);
			} else {
				GameTextForPlayer(playerid,"Move Type Forward",1000,4);
			}
		} else if(KEY_PRESSED(KEY_CTRL_BACK)){
			//stop
			StopObject(DarkNGC[0]);
		} else if(KEY_PRESSED(KEY_ANALOG_RIGHT)){
			//speed increase
			DarkNGCSpeed += 5.0;
			if(DarkNGCSpeed > 200.0){
				DarkNGCSpeed = 200.0;
			} else {
				new buffer[128];
				format(buffer,sizeof buffer,"Speed: %.1f",DarkNGCSpeed);
				GameTextForPlayer(playerid,buffer,500,4);
			}
		} else if(KEY_PRESSED(KEY_ANALOG_LEFT)){
			//speed decrease
			DarkNGCSpeed -= 5.0;
			if(DarkNGCSpeed < 0.0){
				DarkNGCSpeed = 0.0;
			} else {
				new buffer[128];
				format(buffer,sizeof buffer,"Speed: %.1f",DarkNGCSpeed);
				GameTextForPlayer(playerid,buffer,500,4);
			}
		}
	}
	return 1;
}
//EOF
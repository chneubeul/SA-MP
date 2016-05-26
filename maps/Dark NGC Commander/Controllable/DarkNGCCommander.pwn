#include <a_samp>
#include <sscanf2>
#include <streamer>
#include <mapandreas>
#include <zcmd>

#include <SAM/3DTryg>
#include <SAM/StreamerFunction>
#include <SAM/ATM>

#include <Missile.inc>
#include "DarkNGCCommander.inc"

public OnFilterScriptInit(){

	DarkNGCInit();
	
	return 1;
}

public OnFilterScriptExit(){
	
	DarkNGCExit();
	
	return 1;
}

public OnPlayerUpdate(playerid){
	if(IsDarkNGC[playerid] && DarkNGCDrive[0] == playerid){
		OnDarkNGCControl(playerid);
	}
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){

	if(IsDarkNGC[playerid]){
		DarkNGCKeyUpdate(playerid,newkeys,oldkeys);
	}
	return 1;
}

//EOF
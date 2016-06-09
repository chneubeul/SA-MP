/****************************************************************************************************
 *                                                                                                  *
 * MapAndreas Update v1.2 made by Abyss Morgan                                                      *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * MapAndreas Version: 1.2.1                                                                        *
 *                                                                                                  *
 * Functions:                                                                                       *
 * bool:IsMapAndreasInit();                                                                         *
 * SafeMapAndreasInit(mode = MAP_ANDREAS_MODE_FULL, name[]="", len=sizeof(name));                   *
 * Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0);                                             *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _Map_Andreas_Ex
	#endinput
#endif
#define _Map_Andreas_Ex

#if !defined MapAndreas_FindZ_For2DCoord
	#error Unknown MapAndreas Version
#endif

stock Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0){
	if(x <= -3000.0 || x >= 3000.0 || y <= -3000.0 || y >= 3000.0){
		z = 0.0;
	} else {
		MapAndreas_FindZ_For2DCoord(x,y,z);
	}
	return z;
}

stock bool:IsMapAndreasInit(){
	new Float:mapunit;
	MapAndreasFindZ(0.0,0.0,mapunit);
	if(mapunit <= 0.0) return false;
	return true;
}

stock SafeMapAndreasInit(mode = MAP_ANDREAS_MODE_FULL, name[]="", len=sizeof(name)){
	//check MapAndreas Init
	new bool:MapAndreasLastStat = false;
	if(!IsMapAndreasInit()){
		MapAndreas_Init(mode,name,len);
		MapAndreasLastStat = true;
	}
	if(!IsMapAndreasInit()){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: MapAndreas failed to initiated.");
		}
	} else {
		if(MapAndreasLastStat){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Info: MapAndreas successfully init.");
			}
		}
	}
}

//EOF
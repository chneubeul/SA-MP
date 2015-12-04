/**********************************************
 *                                            *
 * Update for MapAndreas 1.2.1                *
 *                                            *
 * Functions:                                 *
 * bool:IsMapAndreasInit();                   *
 * SafeMapAndreasInit();                      *
 * MapAndreasFindZ(Float:x,Float:y,&Float:z); *
 *                                            *
 **********************************************/

#if !defined MapAndreas_FindZ_For2DCoord
	#error Unknown MapAndreas Version
#endif

stock bool:IsMapAndreasInit(){
	new Float:mapunit;
	MapAndreas_FindZ_For2DCoord(0.0,0.0,mapunit);
	if(mapunit <= 0.0) return false;
	return true;
}

stock SafeMapAndreasInit(){
	//check MapAndreas Init
	if(!IsMapAndreasInit()){
		MapAndreas_Init(MAP_ANDREAS_MODE_FULL);
	}
	if(!IsMapAndreasInit()){
		print("[ADM] Error: MapAndreas failed to initiated");
	}
}

stock MapAndreasFindZ(Float:x,Float:y,&Float:z){
	if(x <= -3000 || x >= 3000 || y <= -3000 || y >= 3000){
		z = 0.0;
	} else {
		MapAndreas_FindZ_For2DCoord(x,y,z);
	}
}

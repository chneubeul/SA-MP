#define FILTERSCRIPT

#include <a_samp>
#include <foreach>

public OnFilterScriptInit(){	
	
	for(new i = 0; i < 500; i++){
		CallLocalFunction("OnPlayerConnect","d",i); //connect 500 fake players
	}
	
	new a, b, c;
	
	c = 0;
	a = GetTickCount();
	foreach(new playerid : Player){
		for(new k = 0; k < 1000; k++){
			new Float:hp, Float:x, Float:y, Float:z;
			GetPlayerHealth(playerid,hp);
			SetPlayerHealth(playerid,hp);
			GetPlayerPos(playerid,x,y,z);
			x = x*x;
			y = y*y;
			z = z*z;
			SetPlayerPos(playerid,x,y,z);
			c++;
		}
		//printf("iter: %d value: %d",c-1,playerid);
	}
	b = GetTickCount();
	printf("#1 Foreach for %d iteration in %d ms",c,b-a);
	
	for(new i = 0; i < 100; i++){
		CallLocalFunction("OnPlayerDisconnect","dd",i,0); //disconnect 100 fake players
	}
	
	c = 0;
	a = GetTickCount();
	foreach(new playerid : Player){
		for(new k = 0; k < 1000; k++){
			new Float:hp, Float:x, Float:y, Float:z;
			GetPlayerHealth(playerid,hp);
			SetPlayerHealth(playerid,hp);
			GetPlayerPos(playerid,x,y,z);
			x = x*x;
			y = y*y;
			z = z*z;
			SetPlayerPos(playerid,x,y,z);
			c++;
		}
		//printf("iter: %d value: %d",c-1,playerid);
	}
	b = GetTickCount();
	printf("#2 Foreach for %d iteration in %d ms",c,b-a);
	
	
	return 1;
}

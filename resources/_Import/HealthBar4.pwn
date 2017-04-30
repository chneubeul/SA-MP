#include <a_samp>
#define COLOR_HPBAR_BG 0x000000FF
#define COLOR_HPBAR_75100BG 0x128200AA
#define COLOR_HPBAR_75100 0x1ED500FF
#define COLOR_HPBAR_5075BG 0xB8BA00AA
#define COLOR_HPBAR_5075 0xFCFF00FF
#define COLOR_HPBAR_2550BG 0xB17103AA
#define COLOR_HPBAR_2550 0xFFA200FF
																				// Colored Health Bar v 4.0
																				// Idea: Baked-Banana (backwardsman97) & DJDeegu
                                                                                // Made by O.K.Style™ (ICQ: 402747399)
                                                                                // www.gta-news.org | www.acf.clan.su
new Text:HealthBar[19];
public OnFilterScriptInit()
{
	HealthBar[0] = TextDrawCreate(611.0,68.5,"_");                              // BBG
	TextDrawLetterSize(HealthBar[0],0.5,0.449999);
	TextDrawUseBox(HealthBar[0],1);
	TextDrawBoxColor(HealthBar[0],COLOR_HPBAR_BG);
	TextDrawTextSize(HealthBar[0],543.0,0.0);
	HealthBar[1] = TextDrawCreate(608.5,71.0,"_");                              // BG (75-100)
	TextDrawLetterSize(HealthBar[1],0.5,0.0);
	TextDrawUseBox(HealthBar[1],1);
	TextDrawBoxColor(HealthBar[1],COLOR_HPBAR_75100BG);
	TextDrawTextSize(HealthBar[1],545.0,0.0);
	HealthBar[2] = TextDrawCreate(609.0,71.0,"_");                              // >= 95
	TextDrawLetterSize(HealthBar[2],0.5,0.0);
	TextDrawUseBox(HealthBar[2],1);
	TextDrawBoxColor(HealthBar[2],COLOR_HPBAR_75100);
	TextDrawTextSize(HealthBar[2],545.0,0.0);
	HealthBar[3] = TextDrawCreate(604.0,71.0,"_");                              // >= 90
	TextDrawLetterSize(HealthBar[3],0.5,0.0);
	TextDrawUseBox(HealthBar[3],1);
	TextDrawBoxColor(HealthBar[3],COLOR_HPBAR_75100);
	TextDrawTextSize(HealthBar[3],545.0,0.0);
	HealthBar[4] = TextDrawCreate(601.0,71.0,"_");                              // >= 85
	TextDrawLetterSize(HealthBar[4],0.5,0.0);
	TextDrawUseBox(HealthBar[4],1);
	TextDrawBoxColor(HealthBar[4],COLOR_HPBAR_75100);
	TextDrawTextSize(HealthBar[4],545.0,0.0);
	HealthBar[5] = TextDrawCreate(598.0,71.0,"_");                              // >= 80
	TextDrawLetterSize(HealthBar[5],0.5,0.0);
	TextDrawUseBox(HealthBar[5],1);
	TextDrawBoxColor(HealthBar[5],COLOR_HPBAR_75100);
	TextDrawTextSize(HealthBar[5],545.0,0.0);
	HealthBar[6] = TextDrawCreate(595.0,71.0,"_");                              // >= 75
	TextDrawLetterSize(HealthBar[6],0.5,0.0);
	TextDrawUseBox(HealthBar[6],1);
	TextDrawBoxColor(HealthBar[6],COLOR_HPBAR_75100);
	TextDrawTextSize(HealthBar[6],545.0,0.0);
	HealthBar[7] = TextDrawCreate(608.5,71.0,"_");                              // Çàäíèé ôîí (50-75)
	TextDrawLetterSize(HealthBar[7],0.5,0.0);
	TextDrawUseBox(HealthBar[7],1);
	TextDrawBoxColor(HealthBar[7],COLOR_HPBAR_5075BG);
	TextDrawTextSize(HealthBar[7],545.0,0.0);
	HealthBar[8] = TextDrawCreate(591.5,71.0,"_");                              // >= 70
	TextDrawLetterSize(HealthBar[8],0.5,0.0);
	TextDrawUseBox(HealthBar[8],1);
	TextDrawBoxColor(HealthBar[8],COLOR_HPBAR_5075);
	TextDrawTextSize(HealthBar[8],545.0,0.0);
	HealthBar[9] = TextDrawCreate(588.5,71.0,"_");                              // >= 65
	TextDrawLetterSize(HealthBar[9],0.5,0.0);
	TextDrawUseBox(HealthBar[9],1);
	TextDrawBoxColor(HealthBar[9],COLOR_HPBAR_5075);
	TextDrawTextSize(HealthBar[9],545.0,0.0);
	HealthBar[10] = TextDrawCreate(585.5,71.0,"_");                             // >= 60
	TextDrawLetterSize(HealthBar[10],0.5,0.0);
	TextDrawUseBox(HealthBar[10],1);
	TextDrawBoxColor(HealthBar[10],COLOR_HPBAR_5075);
	TextDrawTextSize(HealthBar[10],545.0,0.0);
	HealthBar[11] = TextDrawCreate(582.5,71.0,"_");                             // >= 55
	TextDrawLetterSize(HealthBar[11],0.5,0.0);
	TextDrawUseBox(HealthBar[11],1);
	TextDrawBoxColor(HealthBar[11],COLOR_HPBAR_5075);
	TextDrawTextSize(HealthBar[11],545.0,0.0);
	HealthBar[12] = TextDrawCreate(579.0,71.0,"_");                             // >= 50
	TextDrawLetterSize(HealthBar[12],0.5,0.0);
	TextDrawUseBox(HealthBar[12],1);
	TextDrawBoxColor(HealthBar[12],COLOR_HPBAR_5075);
	TextDrawTextSize(HealthBar[12],545.0,0.0);
	HealthBar[13] = TextDrawCreate(608.5,71.0,"_");                             // BG (25-50)
	TextDrawLetterSize(HealthBar[13],0.5,0.0);
	TextDrawUseBox(HealthBar[13],1);
	TextDrawBoxColor(HealthBar[13],COLOR_HPBAR_2550BG);
	TextDrawTextSize(HealthBar[13],545.0,0.0);
	HealthBar[14] = TextDrawCreate(576.0,71.0,"_");                             // >= 45
	TextDrawLetterSize(HealthBar[14],0.5,0.0);
	TextDrawUseBox(HealthBar[14],1);
	TextDrawBoxColor(HealthBar[14],COLOR_HPBAR_2550);
	TextDrawTextSize(HealthBar[14],545.0,0.0);
	HealthBar[15] = TextDrawCreate(573.0,71.0,"_");                             // >= 40
	TextDrawLetterSize(HealthBar[15],0.5,0.0);
	TextDrawUseBox(HealthBar[15],1);
	TextDrawBoxColor(HealthBar[15],COLOR_HPBAR_2550);
	TextDrawTextSize(HealthBar[15],545.0,0.0);
	HealthBar[16] = TextDrawCreate(570.5,71.0, "_");                            // >= 35
	TextDrawLetterSize(HealthBar[16],0.5,0.0);
	TextDrawUseBox(HealthBar[16],1);
	TextDrawBoxColor(HealthBar[16],COLOR_HPBAR_2550);
	TextDrawTextSize(HealthBar[16],545.0,0.0);
	HealthBar[17] = TextDrawCreate(567.5,71.0,"_");                             // >= 30
	TextDrawLetterSize(HealthBar[17],0.5,0.0);
	TextDrawUseBox(HealthBar[17],1);
	TextDrawBoxColor(HealthBar[17],COLOR_HPBAR_2550);
	TextDrawTextSize(HealthBar[17],545.0,0.0);
	HealthBar[18] = TextDrawCreate(564.0,71.0,"_");                             // >= 25
	TextDrawLetterSize(HealthBar[18],0.5,0.0);
	TextDrawUseBox(HealthBar[18],1);
	TextDrawBoxColor(HealthBar[18],COLOR_HPBAR_2550);
	TextDrawTextSize(HealthBar[18],545.0,0.0);
	return 1;
}
public OnFilterScriptExit()
{
	for(new i=0; i<19; i++)
	{
	    TextDrawHideForAll(HealthBar[i]);
	    TextDrawDestroy(HealthBar[i]);
	}
	return 1;
}
public OnPlayerSpawn(playerid)
{
	TextDrawShowForPlayer(playerid,HealthBar[0]);
	return 1;
}
public OnPlayerDeath(playerid,killerid,reason)
{
	for(new i=0; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
	return 1;
}
public OnPlayerUpdate(playerid)
{
	new Float:Health;
	GetPlayerHealth(playerid,Health);
	if(Health >= 95)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[1]);
		TextDrawShowForPlayer(playerid,HealthBar[2]);
	}
	else if(Health >= 90 && Health < 95)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[1]);
		TextDrawShowForPlayer(playerid,HealthBar[3]);
	}
	else if(Health >= 85 && Health < 90)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[1]);
		TextDrawShowForPlayer(playerid,HealthBar[4]);
	}
	else if(Health >= 80 && Health < 85)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[1]);
		TextDrawShowForPlayer(playerid,HealthBar[5]);
	}
	else if(Health >= 75 && Health < 80)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[1]);
		TextDrawShowForPlayer(playerid,HealthBar[6]);
	}
	else if(Health >= 70 && Health < 75)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[7]);
		TextDrawShowForPlayer(playerid,HealthBar[8]);
	}
	else if(Health >= 65 && Health < 70)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[7]);
		TextDrawShowForPlayer(playerid,HealthBar[9]);
	}
	else if(Health >= 60 && Health < 65)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[7]);
		TextDrawShowForPlayer(playerid,HealthBar[10]);
	}
	else if(Health >= 55 && Health < 60)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[7]);
		TextDrawShowForPlayer(playerid,HealthBar[11]);
	}
	else if(Health >= 50 && Health < 55)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[7]);
		TextDrawShowForPlayer(playerid,HealthBar[12]);
	}
	else if(Health >= 45 && Health < 50)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[13]);
		TextDrawShowForPlayer(playerid,HealthBar[14]);
	}
	else if(Health >= 40 && Health < 45)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[13]);
		TextDrawShowForPlayer(playerid,HealthBar[15]);
	}
	else if(Health >= 35 && Health < 40)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[13]);
		TextDrawShowForPlayer(playerid,HealthBar[16]);
	}
	else if(Health >= 30 && Health < 35)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[13]);
		TextDrawShowForPlayer(playerid,HealthBar[17]);
	}
	else if(Health >= 25 && Health < 30)
	{
		for(new i=1; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
		TextDrawShowForPlayer(playerid,HealthBar[13]);
		TextDrawShowForPlayer(playerid,HealthBar[18]);
	}
	else
	{
		for(new i=0; i<19; i++) TextDrawHideForPlayer(playerid,HealthBar[i]);
	}
	return 1;
}

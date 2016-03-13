/****************************************************************************************************
 *                                                                                                  *
 *                                           Glitch Area                                            *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts/Glitch%20Area%202.4     *
 *                                                                                                  *
 * File Version: 2.4B                                                                               *
 *                                                                                                  *
 * Install information:                                                                             *
 *                                                                                                  *
 * Variable:                                                                                        *
 * glTemp[playerid][gltime]      //starter tick                                                     *
 * glTemp[playerid][glrecord]    //record player                                                    *
 * glTemp[playerid][glstatus]    //the status of the aren                                           *
 * glTemp[playerid][glshoot]     //shot in the Arena                                                *
 *                                                                                                  *
 * Attach Functions:                                                                                *
 * gl_OnPlayerSpawn(playerid);                                                                      *
 * gl_OnPlayerConnect(playerid);                                                                    *
 * gl_OnPlayerDeath(playerid,killerid,reason);                                                      *
 * gl_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);         *
 *                                                                                                  *
 * Special Functions:                                                                               *
 * ExitGlitchArea(playerid);                                                                        *
 *                                                                                                  *
 * SQL:                                                                                             *
 * CREATE TABLE IF NOT EXISTS `glitch` (                                                            *
 *  `id` int(11) NOT NULL,                                                                          *
 *  `time` int(11) NOT NULL DEFAULT '999999',                                                       *
 *  PRIMARY KEY (`id`)                                                                              *
 * ) ENGINE=MyISAM DEFAULT CHARSET=latin1;                                                          *
 *                                                                                                  *
 * Command:                                                                                         *
 * /gl - Entrance to the arena glitch                                                               *
 * /glexit - Emergency exit of the arena glitch                                                     *
 *                                                                                                  *
 ****************************************************************************************************/

#define ACCOUNT_ID_VARIABLE		(pData[playerid][accountID]) //you accountid variable

enum e_glTemp {
	gltime,
	glrecord,
	glstatus,
	glshoot
}

new glTemp[MAX_PLAYERS][e_glTemp];

stock ExitGlitchArea(playerid){
	if(glTemp[playerid][glstatus] == 1){
		glTemp[playerid][glstatus] = 0;
		glTemp[playerid][glshoot] = 0;
		glTemp[playerid][gltime] = 0;
		SetPlayerInterior(playerid,0);
		SetPlayerVirtualWorld(playerid,0);
		SpawnPlayer(playerid);
	}
}

CMD:gl(playerid){	
	if(glTemp[playerid][glstatus] == 1) return SendClientMessage(playerid,0x00B300FF,"Already you are on area /gl");
	
	glTemp[playerid][glstatus] = 1;
	glTemp[playerid][glshoot] = 0;	//wykonal 0 strzalow
	glTemp[playerid][gltime] = 0;	//czas na 0, stan gotowosci
	
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid,24,999);
	SetPlayerPos(playerid,1410.8875,0.1127,1000.9235);
	SetPlayerFacingAngle(playerid,132.9270);
	SetPlayerInterior(playerid,1);
	SetPlayerVirtualWorld(playerid,playerid+9000); //VW 9000 - 9999
	GameTextForPlayer(playerid,"Glitch Area",2500,1);
	
	if(glTemp[playerid][glrecord] == 999999){
		SendClientMessage(playerid,0x00B300FF,"Welcome to the arena for the first time Glitch, the time is elapsed from 1 shot.");
	}
	return 1;
}

CMD:glexit(playerid){
	if(glTemp[playerid][glstatus] == 0) return SendClientMessage(playerid,0x00B300FF,"You are not on area /gl");
	ExitGlitchArea(playerid);
	return 1;
}

forward gl_OnPlayerSpawn(playerid);
forward gl_OnPlayerConnect(playerid);
forward gl_OnPlayerDeath(playerid,killerid,reason);
forward gl_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);

public gl_OnPlayerSpawn(playerid){
	glTemp[playerid][glstatus] = 0;
	glTemp[playerid][glshoot] = 0;
	glTemp[playerid][gltime] = 0;
	return 1;
}

public gl_OnPlayerConnect(playerid){
	new buffer[256];
	glTemp[playerid][glrecord] = 999999;
	glTemp[playerid][glstatus] = 0;
	glTemp[playerid][glshoot] = 0;
	glTemp[playerid][gltime] = 0;
	
	if(ACCOUNT_ID_VARIABLE != 0){
		format(buffer,sizeof buffer,"INSERT IGNORE glitch (`id`, `time`) VALUES ('%d', '999999')",ACCOUNT_ID_VARIABLE);
		mysql_query(buffer);
		
		format(buffer,sizeof buffer,"SELECT time FROM glitch WHERE id='%d' LIMIT 1",ACCOUNT_ID_VARIABLE);
		mysql_query(buffer);
		mysql_store_result();
		if(mysql_num_rows()>0){
			mysql_fetch_row(buffer);
			sscanf(buffer,"p<|>d",glTemp[playerid][glrecord]);
		}
		mysql_free_result();
	}
	if(glTemp[playerid][glrecord] <= 0) glTemp[playerid][glrecord] = 999999;	//wczytano niepoprawne dane lub ktos dal 0
	return 1;
}

public gl_OnPlayerDeath(playerid,killerid,reason){
	glTemp[playerid][glstatus] = 0;
	glTemp[playerid][glshoot] = 0;
	glTemp[playerid][gltime] = 0;
	return 1;
}

public gl_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ){
	if(glTemp[playerid][glstatus] == 1){
		if(weaponid == 24){
			if(glTemp[playerid][glshoot] == 0){ //start
				glTemp[playerid][gltime] = GetTickCount();
				glTemp[playerid][glshoot] += 1;
			} else if(glTemp[playerid][glshoot] >= 6){ //koniec zabawy
				new tgltime = GetTickCount()-glTemp[playerid][gltime], tglmsg = 0, buffer[256];
				if(tgltime < glTemp[playerid][glrecord] && tgltime > 0){
					tglmsg = 1;
					glTemp[playerid][glrecord] = tgltime;
					if(ACCOUNT_ID_VARIABLE != 0){
						format(buffer,sizeof buffer,"UPDATE glitch SET time='%d' WHERE id='%d'",glTemp[playerid][glrecord],ACCOUNT_ID_VARIABLE);
						mysql_query(buffer);
					}
				}
				ExitGlitchArea(playerid);
				if(tglmsg == 1){
					format(buffer,sizeof buffer,"Area Glitch new record, time {00FF00}%d {00B300}ms",glTemp[playerid][glrecord]);
				} else if(glTemp[playerid][glrecord] == 999999){
					format(buffer,sizeof buffer,"Area Glitch time {00FF00}%d {00B300}ms",tgltime);
				} else {
					format(buffer,sizeof buffer,"Area Glitch time {00FF00}%d {00B300}ms, current record {00FF00}%d {00B300}ms",tgltime,glTemp[playerid][glrecord]);
				}
				SendClientMessage(playerid,0x00B300FF,buffer);
			} else {
				glTemp[playerid][glshoot] += 1;
			}
		}
	}
	return 1;
}

//EOF
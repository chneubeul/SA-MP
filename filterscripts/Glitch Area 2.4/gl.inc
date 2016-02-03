/****************************************************************************************************
 *                                                                                                  *
 *                                           Glitch Area                                            *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 2.4                                                                                *
 *                                                                                                  *
 * Install information:                                                                             *
 *                                                                                                  *
 * Variable:                                                                                        *
 * pTemp[playerid][gltime]      //starter tick                                                      *
 * pTemp[playerid][glrecord]    //record player                                                     *
 * pTemp[playerid][glstatus]    //the status of the arena                                           *
 * pTemp[playerid][glshoot]     //shot in the Arena                                                 *
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

stock ExitGlitchArea(playerid){
	if(pTemp[playerid][glstatus] == 1){
		pTemp[playerid][glstatus] = 0;
		pTemp[playerid][glshoot] = 0;
		pTemp[playerid][gltime] = 0;
		SetPlayerInterior(playerid,0);
		SetPlayerVirtualWorld(playerid,0);
		SpawnPlayer(playerid);
	}
}

CMD:gl(playerid){
	//
	
	if(pTemp[playerid][glstatus] == 1) return SendClientMessage(playerid,0x00B300FF,"Already you are on area /gl");
	
	pTemp[playerid][glstatus] = 1;
	pTemp[playerid][glshoot] = 0;	//wykonal 0 strzalow
	pTemp[playerid][gltime] = 0;	//czas na 0, stan gotowosci
	
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid,24,999);
	SetPlayerPos(playerid,1410.8875,0.1127,1000.9235);
	SetPlayerFacingAngle(playerid,132.9270);
	SetPlayerInterior(playerid,1);
	SetPlayerVirtualWorld(playerid,playerid+9000); //VW 9000 - 9999
	GameTextForPlayer(playerid,"Glitch Area",2500,1);
	
	if(pTemp[playerid][glrecord] == 999999){
		SendClientMessage(playerid,0x00B300FF,"Welcome to the arena for the first time Glitch, the time is elapsed from 1 shot.");
	}
	return 1;
}

CMD:glexit(playerid){
	if(pTemp[playerid][glstatus] == 0) return SendClientMessage(playerid,0x00B300FF,"You are not on area /gl");
	ExitGlitchArea(playerid);
	return 1;
}

forward gl_OnPlayerSpawn(playerid);
forward gl_OnPlayerConnect(playerid);
forward gl_OnPlayerDeath(playerid,killerid,reason);
forward gl_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);

public gl_OnPlayerSpawn(playerid){
	pTemp[playerid][glstatus] = 0;
	pTemp[playerid][glshoot] = 0;
	pTemp[playerid][gltime] = 0;
	return 1;
}

public gl_OnPlayerConnect(playerid){
	new buffer[256];
	pTemp[playerid][glrecord] = 999999;
	pTemp[playerid][glstatus] = 0;
	pTemp[playerid][glshoot] = 0;
	pTemp[playerid][gltime] = 0;
	
	if(pData[playerid][accountID] != 0){
		format(buffer,sizeof buffer,"INSERT IGNORE glitch (`id`, `time`) VALUES ('%d', '999999')",pData[playerid][accountID]);
		mysql_query(buffer);
		
		format(buffer,sizeof buffer,"SELECT time FROM glitch WHERE id='%d' LIMIT 1",pData[playerid][accountID]);
		mysql_query(buffer);
		mysql_store_result();
		if(mysql_num_rows()>0){
			mysql_fetch_row(buffer);
			sscanf(buffer,"p<|>d",pTemp[playerid][glrecord]);
		}
		mysql_free_result();
	}
	if(pTemp[playerid][glrecord] <= 0) pTemp[playerid][glrecord] = 999999;	//wczytano niepoprawne dane lub ktos dal 0
	return 1;
}

public gl_OnPlayerDeath(playerid,killerid,reason){
	pTemp[playerid][glstatus] = 0;
	pTemp[playerid][glshoot] = 0;
	pTemp[playerid][gltime] = 0;
	return 1;
}

public gl_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ){
	if(pTemp[playerid][glstatus] == 1){
		if(weaponid == 24){
			if(pTemp[playerid][glshoot] == 0){ //start
				pTemp[playerid][gltime] = GetTickCount();
				pTemp[playerid][glshoot] += 1;
			} else if(pTemp[playerid][glshoot] >= 6){ //koniec zabawy
				new tgltime = GetTickCount()-pTemp[playerid][gltime], tglmsg = 0, buffer[256];
				if(tgltime < pTemp[playerid][glrecord] && tgltime > 0){
					tglmsg = 1;
					pTemp[playerid][glrecord] = tgltime;
					if(pData[playerid][accountID] != 0){
						format(buffer,sizeof buffer,"UPDATE glitch SET time='%d' WHERE id='%d'",pTemp[playerid][glrecord],pData[playerid][accountID]);
						mysql_query(buffer);
					}
				}
				ExitGlitchArea(playerid);
				if(tglmsg == 1){
					format(buffer,sizeof buffer,"Area Glitch new record, time {00FF00}%d {00B300}ms",pTemp[playerid][glrecord]);
				} else if(pTemp[playerid][glrecord] == 999999){
					format(buffer,sizeof buffer,"Area Glitch time {00FF00}%d {00B300}ms",tgltime);
				} else {
					format(buffer,sizeof buffer,"Area Glitch time {00FF00}%d {00B300}ms, current record {00FF00}%d {00B300}ms",tgltime,pTemp[playerid][glrecord]);
				}
				SendClientMessage(playerid,0x00B300FF,buffer);
			} else {
				pTemp[playerid][glshoot] += 1;
			}
		}
	}
	return 1;
}

//EOF
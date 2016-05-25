/****************************************************************************************************
 *                                                                                                  *
 *                                           Glitch Area                                            *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts/Glitch%20Area%202.4     *
 *                                                                                                  *
 * File Version: 2.4                                                                                *
 *                                                                                                  *
 * Compatible with FullServer                                                                       *
 *                                                                                                  *
 * Install information:                                                                             *
 *                                                                                                  *
 * Variable:                                                                                        *
 * pTemp[playerid][gltime]		//startowy tick                                                     *
 * pTemp[playerid][glrecord]	//rekord gracza                                                     *
 * pTemp[playerid][glstatus]	//status na arenie                                                  *
 * pTemp[playerid][glshoot]		//strza³ na arenie                                                  *
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
 * CREATE TABLE IF NOT EXISTS `fs_gl` (                                                             *
 *	`id` int(11) NOT NULL,                                                                          *
 *	`time` int(11) NOT NULL DEFAULT '999999',                                                       *
 *	PRIMARY KEY (`id`)                                                                              *
 * ) ENGINE=MyISAM DEFAULT CHARSET=latin1;                                                          *
 *                                                                                                  *
 * Command:                                                                                         *
 * /gl - wejœcie na arene glitch                                                                    *
 * /glexit - awaryjne wychodzenie z areny glitch                                                    *
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
	//czy moze dolaczyc, ewentualne blokady komend
	
	if(pTemp[playerid][glstatus] == 1) return SendClientMessage(playerid,0x00B300FF,"Ju¿ znajdujesz siê na arenie /gl");
	
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
		SendClientMessage(playerid,0x00B300FF,"Witamy pierwszy raz na arenie Glitch, czas zostanie odmierzony od 1 strza³u.");
	}
	return 1;
}

CMD:glexit(playerid){
	if(pTemp[playerid][glstatus] == 0) return SendClientMessage(playerid,0x00B300FF,"Nie znajdujesz siê na arenie /gl");
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
		format(buffer,sizeof buffer,"INSERT IGNORE fs_gl (`id`, `time`) VALUES ('%d', '999999')",pData[playerid][accountID]);
		mysql_query(buffer);
		
		format(buffer,sizeof buffer,"SELECT time FROM fs_gl WHERE id='%d' LIMIT 1",pData[playerid][accountID]);
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
						format(buffer,sizeof buffer,"UPDATE fs_gl SET time='%d' WHERE id='%d'",pTemp[playerid][glrecord],pData[playerid][accountID]);
						mysql_query(buffer);
					}
				}
				ExitGlitchArea(playerid);
				if(tglmsg == 1){
					format(buffer,sizeof buffer,"Arena Glitch nowy rekord, czas {00FF00}%d {00B300}ms",pTemp[playerid][glrecord]);
				} else if(pTemp[playerid][glrecord] == 999999){
					format(buffer,sizeof buffer,"Arena Glitch czas {00FF00}%d {00B300}ms",tgltime);
				} else {
					format(buffer,sizeof buffer,"Arena Glitch czas {00FF00}%d {00B300}ms, obecny rekord {00FF00}%d {00B300}ms",tgltime,pTemp[playerid][glrecord]);
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
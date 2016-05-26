/****************************************************************************************************
 *                                                                                                  *
 * Anti Supreme Troll + Object Finder Detect                                                        *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include                               *
 *                                                                                                  *
 * File Version: 1.2                                                                                *
 *                                                                                                  *
 * Cheat Info:                                                                                      *
 * http://www.mpgh.net/forum/showthread.php?t=883161                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * CheckPlayerObject(playerid);                                                                     *
 * DestroyIllegalPlayerObject(playerid);                                                            *
 *                                                                                                  *
 * Command:                                                                                         *
 * /checkplayer <id>                                                                                *
 * /cleanillegalobj <id / all>                                                                      *
 *                                                                                                  *
 * Block Command:                                                                                   *
 * /trollinfo, /pos, /dpos, /r2, /fw, /ccars, /hp, /hpu, /tp, /sm, /showid, /showcarid, /s1, /s2,   *
 * /s3, /s4, /s5, /s6, /s7, /s8, /s9, /sswitch, /lag, /col, /fwh, /bm, /reu, /tpall, /hpall, /thr,  *
 * /small, /smallc, /safe, /objectid, /oy, /or, /ob, /ov, /og, /ow, /oreset, /otog                  *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _anti_supreme_troll
	#endinput
#endif
#define _anti_supreme_troll

//Get Compress Adress
#define GetPlayerObjAddress(%0)			(floatround((%0)/32))
#define GetPlayerObjBit(%0)				((%0) % 32)

//BitFunctions.inc
#define AST_GetValueBit(%0,%1)			((%0) >>> (%1) & 0x01)
#define AST_SetValueBit(%0,%1,%2)		((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

//StreamerFunction.inc
stock AST_CountPlayerObjects(playerid,bool:streamer = false){
	new count = 0;
	for(new i = 0; i <= MAX_OBJECTS; i++){
		if(streamer){
			if(IsValidPlayerObject(playerid,i)){
				count += 1;
			}
		} else {
			if(Streamer_GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID){
				if(IsValidPlayerObject(playerid,i)){
					count += 1;
				}
			}
		}
	}
	return count;
}

new PlayerObj[MAX_PLAYERS][32]; // Compressed Data 1000*1000 -> 1000*32

stock SendClientMessageToAdmin(color,message[]){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i) && IsPlayerAdmin(i)){
			SendClientMessage(i,color,message);
		}
	}
}

stock CheckPlayerObject(playerid){
	new cnt = 0;
	for(new i = 0; i < MAX_OBJECTS; i++){
		if(Streamer_GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID && AST_GetValueBit(PlayerObj[playerid][GetPlayerObjAddress(i)],GetPlayerObjBit(i)) == 0){
			if(IsValidPlayerObject(playerid,i)){
				cnt++;
			}
		}
	}
	return cnt;
}

stock DestroyIllegalPlayerObject(playerid){
	for(new i = 0; i < MAX_OBJECTS; i++){
		if(Streamer_GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID && AST_GetValueBit(PlayerObj[playerid][GetPlayerObjAddress(i)],GetPlayerObjBit(i)) == 0){
			if(IsValidPlayerObject(playerid,i)){
				DestroyPlayerObject(playerid,i);
			}
		}
	}
}

stock OnSupremeTrollCMD(playerid,cmdtext[],params[]){
	new buffer[200], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,sizeof(name));
	format(buffer,sizeof(buffer),"[HACK DETECT] (%d)%s used the command '%s' params '%s'",playerid,name,cmdtext,params);
	SendClientMessageToAdmin(0xFF0000FF,buffer);
	printf(buffer);
	GameTextForPlayer(playerid, "~yw~~~~/~al that ~shit", 1000, 1);
	Kick(playerid); //This is sparta !!
	return 1;
}

CMD:checkplayer(playerid,params[]){
	if(!IsPlayerAdmin(playerid)) return 0;
	new userid;
	if(sscanf(params,"d",userid)){
		return SendClientMessage(playerid,0xFF0000FF,"››› Use /checkplayer <id>");
	} else if(!IsPlayerConnected(userid)){
		return SendClientMessage(playerid,0xFF0000FF,"››› Player not found");
	}
	new name[MAX_PLAYER_NAME], cnt = 0, cnt2 = 0, buffer[256];
	GetPlayerName(userid,name,sizeof(name));
	cnt = CheckPlayerObject(userid);
	cnt2 = Streamer_CountVisibleItems(userid,STREAMER_TYPE_OBJECT,1)+AST_CountPlayerObjects(userid,false);
	
	format(buffer,sizeof(buffer),"(%d)%s PlayerObject: %d / %d illegal: %d",userid,name,cnt+cnt2,cnt2,cnt);
	if(cnt == 0){
		SendClientMessage(playerid,0xFFFFFFFF,buffer);
	} else {
		SendClientMessage(playerid,0xFF0000FF,buffer);
	}
	return 1;
}

CMD:cleanillegalobj(playerid,params[]){
	if(!IsPlayerAdmin(playerid)) return 0;
	new tmp_userid[16], userid;
	if(sscanf(params,"s[16]",tmp_userid)) return SendClientMessage(playerid,0xFF0000FF,"››› Use /cleanillegalobj <id / all>");
	if(!strcmp(tmp_userid,"all",true)){
		for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
			if(IsPlayerConnected(i)){
				DestroyIllegalPlayerObject(i);
			}
		}
	} else {
		userid = strval(tmp_userid);
		if(!IsPlayerConnected(userid)){
			return SendClientMessage(playerid,0xFF0000FF,"››› Player not found");
		}
		DestroyIllegalPlayerObject(userid);
	}
	return 1;
}

CMD:trollinfo(playerid,params[])	return OnSupremeTrollCMD(playerid,"trollinfo",params);
CMD:pos(playerid,params[])			return OnSupremeTrollCMD(playerid,"pos",params);
CMD:dpos(playerid,params[])			return OnSupremeTrollCMD(playerid,"dpos",params);
CMD:r2(playerid,params[])			return OnSupremeTrollCMD(playerid,"r2",params);
CMD:fw(playerid,params[])			return OnSupremeTrollCMD(playerid,"fw",params);
CMD:ccars(playerid,params[])		return OnSupremeTrollCMD(playerid,"ccars",params);
CMD:hp(playerid,params[])			return OnSupremeTrollCMD(playerid,"hp",params);
CMD:hpu(playerid,params[])			return OnSupremeTrollCMD(playerid,"hpu",params);
CMD:tp(playerid,params[])			return OnSupremeTrollCMD(playerid,"tp",params);
CMD:sm(playerid,params[])			return OnSupremeTrollCMD(playerid,"sm",params);
CMD:showid(playerid,params[])		return OnSupremeTrollCMD(playerid,"showid",params);
CMD:showcarid(playerid,params[])	return OnSupremeTrollCMD(playerid,"showcarid",params);
CMD:s1(playerid,params[])			return OnSupremeTrollCMD(playerid,"s1",params);
CMD:s2(playerid,params[])			return OnSupremeTrollCMD(playerid,"s2",params);
CMD:s3(playerid,params[])			return OnSupremeTrollCMD(playerid,"s3",params);
CMD:s4(playerid,params[])			return OnSupremeTrollCMD(playerid,"s4",params);
CMD:s5(playerid,params[])			return OnSupremeTrollCMD(playerid,"s5",params);
CMD:s6(playerid,params[])			return OnSupremeTrollCMD(playerid,"s6",params);
CMD:s7(playerid,params[])			return OnSupremeTrollCMD(playerid,"s7",params);
CMD:s8(playerid,params[])			return OnSupremeTrollCMD(playerid,"s8",params);
CMD:s9(playerid,params[])			return OnSupremeTrollCMD(playerid,"s9",params);
CMD:sswitch(playerid,params[])		return OnSupremeTrollCMD(playerid,"sswitch",params);
CMD:lag(playerid,params[])			return OnSupremeTrollCMD(playerid,"lag",params);
CMD:col(playerid,params[])			return OnSupremeTrollCMD(playerid,"col",params);
CMD:fwh(playerid,params[])			return OnSupremeTrollCMD(playerid,"fwh",params);
CMD:bm(playerid,params[])			return OnSupremeTrollCMD(playerid,"bm",params);
CMD:reu(playerid,params[])			return OnSupremeTrollCMD(playerid,"reu",params);
CMD:tpall(playerid,params[])		return OnSupremeTrollCMD(playerid,"tpall",params);
CMD:hpall(playerid,params[])		return OnSupremeTrollCMD(playerid,"hpall",params);
CMD:thr(playerid,params[])			return OnSupremeTrollCMD(playerid,"thr",params);
CMD:small(playerid,params[])		return OnSupremeTrollCMD(playerid,"small",params);
CMD:smallc(playerid,params[])		return OnSupremeTrollCMD(playerid,"smallc",params);
CMD:safe(playerid,params[])			return OnSupremeTrollCMD(playerid,"safe",params);

CMD:objectid(playerid,params[])		return OnSupremeTrollCMD(playerid,"objectid",params);
CMD:oy(playerid,params[])			return OnSupremeTrollCMD(playerid,"oy",params);
CMD:or(playerid,params[])			return OnSupremeTrollCMD(playerid,"or",params);
CMD:ob(playerid,params[])			return OnSupremeTrollCMD(playerid,"ob",params);
CMD:ov(playerid,params[])			return OnSupremeTrollCMD(playerid,"ov",params);
CMD:og(playerid,params[])			return OnSupremeTrollCMD(playerid,"og",params);
CMD:ow(playerid,params[])			return OnSupremeTrollCMD(playerid,"ow",params);
CMD:oreset(playerid,params[])		return OnSupremeTrollCMD(playerid,"oreset",params);
CMD:otog(playerid,params[])			return OnSupremeTrollCMD(playerid,"otog",params);


//DestroyPlayerObject
stock AST_DestroyPlayerObject(playerid,&objectid){
	AST_SetValueBit(PlayerObj[playerid][GetPlayerObjAddress(objectid)],GetPlayerObjBit(objectid),0);
	new dobj = DestroyPlayerObject(playerid,objectid);
	objectid = INVALID_OBJECT_ID;
	return dobj;
}

#if defined _ALS_DestroyPlayerObject
	#undef DestroyPlayerObject
#else
	#define _ALS_DestroyPlayerObject
#endif
#define DestroyPlayerObject AST_DestroyPlayerObject

//CreatePlayerObject
stock AST_CreatePlayerObject(playerid,modelid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:DrawDistance = 0.0){
	new dobj = CreatePlayerObject(playerid,modelid,x,y,z,rx,ry,rz,DrawDistance);
	AST_SetValueBit(PlayerObj[playerid][GetPlayerObjAddress(dobj)],GetPlayerObjBit(dobj),1);
	return dobj;
}

#if defined _ALS_CreatePlayerObject
	#undef CreatePlayerObject
#else
	#define _ALS_CreatePlayerObject
#endif
#define CreatePlayerObject AST_CreatePlayerObject

//EOF

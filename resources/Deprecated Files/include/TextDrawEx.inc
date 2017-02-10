/****************************************************************************************************
 *                                                                                                  *
 *                                   TextDraw Extended Functions                                    *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.2.1                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 *                                                                                                  *
 * Functions:                                                                                       *
 * CountTextDraw();                                                                                 *
 * CountPlayerTextDraw(playerid);                                                                   *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _Text_Draw_Ex
	#endinput
#endif
#define _Text_Draw_Ex

new TextDrawCount = 0,
	PlayerTextDrawCount[MAX_PLAYERS];

#define CountTextDraw()				(TextDrawCount)
#define CountPlayerTextDraw(%0)		(PlayerTextDrawCount[(%0)])

//Hook: TextDrawCreate
stock Text:TD_TextDrawCreate(Float:x,Float:y,text[]){
	TextDrawCount++;
	return TextDrawCreate(x,y,text);
}

#if defined _ALS_TextDrawCreate
    #undef TextDrawCreate
#else
    #define _ALS_TextDrawCreate
#endif
#define TextDrawCreate TD_TextDrawCreate

//Hook: CreatePlayerTextDraw
stock PlayerText:TD_CreatePlayerTextDraw(playerid,Float:x,Float:y,text[]){
	PlayerTextDrawCount[playerid]++;
	return CreatePlayerTextDraw(playerid,x,y,text);
}

#if defined _ALS_CreatePlayerTextDraw
    #undef CreatePlayerTextDraw
#else
    #define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw TD_CreatePlayerTextDraw

//Hook: TextDrawDestroy
stock TD_TextDrawDestroy(Text:text){
	TextDrawCount--;
	return TextDrawDestroy(text);
}

#if defined _ALS_TextDrawDestroy
    #undef TextDrawDestroy
#else
    #define _ALS_TextDrawDestroy
#endif
#define TextDrawDestroy TD_TextDrawDestroy

//Hook: DestroyPlayerTextDraw
stock TD_DestroyPlayerTextDraw(playerid,PlayerText:text){
	PlayerTextDrawCount[playerid]--;
	return DestroyPlayerTextDraw(playerid,text);
}

#if defined _ALS_DestroyPlayerTextDraw
    #undef DestroyPlayerTextDraw
#else
    #define _ALS_DestroyPlayerTextDraw
#endif
#define DestroyPlayerTextDraw TD_DestroyPlayerTextDraw

//EOF
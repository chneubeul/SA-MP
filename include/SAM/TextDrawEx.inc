/****************************************************************************************************
 *                                                                                                  *
 * TextDraw Update v1.0 by Abyss Morgan                                                             *
 *                                                                                                  *
 * Functions:                                                                                       *
 * CountTextDraw();                                                                                 *
 * CountPlayerTextDraw();                                                                           *
 *                                                                                                  *
 ****************************************************************************************************/

new TextDrawCount = 0, PlayerTextDrawCount = 0;

stock CountTextDraw(){
	return TextDrawCount;
}
	
stock CountPlayerTextDraw(){
	return PlayerTextDrawCount;
}

//TextDrawCreate
stock Text:AC_TextDrawCreate(Float:x,Float:y,text[]){
	TextDrawCount++;
	return TextDrawCreate(x,y,text);
}

#if defined _ALS_TextDrawCreate
    #undef TextDrawCreate
#else
    #define _ALS_TextDrawCreate
#endif
#define TextDrawCreate AC_TextDrawCreate

//CreatePlayerTextDraw
stock PlayerText:AC_CreatePlayerTextDraw(playerid,Float:x,Float:y,text[]){
	PlayerTextDrawCount++;
	return CreatePlayerTextDraw(playerid,x,y,text);
}

#if defined _ALS_CreatePlayerTextDraw
    #undef CreatePlayerTextDraw
#else
    #define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw AC_CreatePlayerTextDraw

//TextDrawDestroy
stock AC_TextDrawDestroy(Text:text){
	TextDrawCount--;
	return TextDrawDestroy(text);
}

#if defined _ALS_TextDrawDestroy
    #undef TextDrawDestroy
#else
    #define _ALS_TextDrawDestroy
#endif
#define TextDrawDestroy AC_TextDrawDestroy

//DestroyPlayerTextDraw
stock AC_DestroyPlayerTextDraw(playerid,PlayerText:text){
	PlayerTextDrawCount--;
	return DestroyPlayerTextDraw(playerid,text);
}

#if defined _ALS_DestroyPlayerTextDraw
    #undef DestroyPlayerTextDraw
#else
    #define _ALS_DestroyPlayerTextDraw
#endif
#define DestroyPlayerTextDraw AC_DestroyPlayerTextDraw


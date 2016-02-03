/****************************************************************************************************
 *                                                                                                  *
 *                                        R G B A Conversion                                        *
 *                                                                                                  *
 * Copyright © 2014 - 2017 Abyss Morgan. All rights reserved.                                       *
 *                                                                                                  *
 * File Version: 2.0                                                                                *
 *                                                                                                  *
 * ShiftRGBAToHex(color,&red,&green,&blue,&alpha);                                                  *
 * ShiftHexToRGBA(&color,red,green,blue,alpha);                                                     *
 * ShiftRGBAToRGB(color);                                                                           *
 * ShiftRGBToRGBA(color,alpha);                                                                     *
 * ShiftRGBToARGB(color,alpha);                                                                     *
 * ShiftRGBAToARGB(color);                                                                          *
 * ShiftARGBToRGBA(color);                                                                          *
 * GetRFromRGBA(color);    //RGBA:0xFAB0A0FF R:0xFA000000                                           *
 * GetGFromRGBA(color);    //RGBA:0xFAB0A0FF G:0x00B00000                                           *
 * GetBFromRGBA(color);    //RGBA:0xFAB0A0FF B:0x0000A000                                           *
 * GetAFromRGBA(color);    //RGBA:0xFAB0A0FF A:0x000000FF                                           *
 * GetRHexFromRGBA(color); //RGBA:0xFAB0A0FF R:0xFA                                                 *
 * GetGHexFromRGBA(color); //RGBA:0xFAB0A0FF G:0xB0                                                 *
 * GetBHexFromRGBA(color); //RGBA:0xFAB0A0FF B:0xA0                                                 *
 * GetAHexFromRGBA(color); //RGBA:0xFAB0A0FF A:0xFF                                                 *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _rgb_function
	#endinput
#endif
#define _rgb_function

#define ShiftRGBAToHex(%0,%1,%2,%3,%4)	(((%1) = ((%0) >>> 24)), ((%2) = (((%0) >>> 16) & 0xFF)),((%3) = (((%0) >>> 8) & 0xFF)),((%4) = ((%0) & 0xFF)))
#define ShiftHexToRGBA(%0,%1,%2,%3,%4)	((%0) = ((%4) & 0xFF) | (((%3) & 0xFF) << 8) | (((%2) & 0xFF) << 16) | ((%1) << 24))
#define ShiftRGBAToRGB(%0)				((((%0) >>> 8) & 0xFF) | ((((%0) >>> 16) & 0xFF) << 8) | (((%0) >>> 24) << 16))
#define ShiftRGBToRGBA(%0,%1)			(((%1) & 0xFF) | (((%0) & 0xFF) << 8) | ((((%0) >>> 8) & 0xFF) << 16) | ((((%0) >>> 16) & 0xFF) << 24))
#define ShiftRGBToARGB(%0,%1)			(((%0) & 0xFF) | ((((%0) >>> 8) & 0xFF) << 8) | ((((%0) >>> 16) & 0xFF) << 16) | ((%1) << 24))
#define ShiftRGBAToARGB(%0)				((((%0) >>> 8) & 0xFF) | ((((%0) >>> 16) & 0xFF) << 8) | ((((%0) >>> 24) & 0xFF) << 16) | (((%0) & 0xFF) << 24))
#define ShiftARGBToRGBA(%0)				((((%0) >>> 24) & 0xFF) | (((%0) & 0xFF) << 8) | ((((%0) >>> 8) & 0xFF) << 16) | ((((%0) >>> 16) & 0xFF) << 24))
#define GetRFromRGBA(%0)				((%0) & 0xFF000000)
#define GetGFromRGBA(%0)				((%0) & 0x00FF0000)
#define GetBFromRGBA(%0)				((%0) & 0x0000FF00)
#define GetAFromRGBA(%0)				((%0) & 0x000000FF)
#define GetRHexFromRGBA(%0)				(((%0) >>> 24) & 0xFF)
#define GetGHexFromRGBA(%0)				(((%0) >>> 16) & 0xFF)
#define GetBHexFromRGBA(%0)				(((%0) >>> 8) & 0xFF)
#define GetAHexFromRGBA(%0)				((%0) & 0xFF)

//EOF
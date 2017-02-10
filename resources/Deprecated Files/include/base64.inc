/****************************************************************************************************
 *                                                                                                  *
 *                                              base64                                              *
 *                                                                                                  *
 * Copyright © 2013 Shiny. All rights reserved.                                                     *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/samp                          *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.0.0                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 *                                                                                                  *
 * Functions:                                                                                       *
 * base64_decode(input[],output[]);                                                                 *
 * base64_encode(input[],output[]);                                                                 *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _base64_included
	#endinput
#endif
#define _base64_included

#define e:base64 		base64_encode
#define d:base64 		base64_decode

new const LettersTable[] = {
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
};
	
new const Decoder[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  62, 0,  0,  0,  63, 52, 53,
	54, 55, 56, 57, 58, 59, 60, 61, 0,  0,
	0,  0,  0,  0,  0,  0,  1,  2,  3,  4,
	5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 0,  0,  0,  0,  0,  0,  26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0
};

stock base64_decode(input[],output[]){
	new SpaceReplacer = '=', len = strlen(input), Position;
	
	for(new i = 0; i < len; i++){
		new char_[2];
		char_[0] = Decoder[input[i++]];
		char_[1] = Decoder[input[i]];
		char_[0] = (char_[0] << 2) | ((char_[1] >> 4) & 3);
		Position += format(output[Position], len, "%c", char_[0]);
		
		if(++i < len){
			char_[0] = input[i];
			if(char_[0] == SpaceReplacer) break;
			char_[0] = Decoder[input[i]];
			char_[1] = ((char_[1] << 4) & 240) | ((char_[0] >> 2) & 15);
			Position += format(output[Position], len, "%c", char_[1]);
		}
		
		if(++i < len){
			char_[1] = input[i];
			if(char_[1] == SpaceReplacer) break;
			char_[1] = Decoder[input[i]];
			char_[0] = ((char_[0] << 6) & 192) | char_[1];
			Position += format(output[Position], len, "%c", char_[0]);
		}
	}
}

stock base64_encode(input[],output[]){
	new SpaceReplacer = '=', len = strlen(input), Position;
	
	for(new i = 0 ; i < len ; i++){
		new Character;
		Character = (input[i] >> 2) & 63;
		Position += format(output[Position], len, "%c", LettersTable[Character]);
		Character = (input[i] << 4) & 63;
		
		if(++i < len){
			Character |= (input[i] >> 4) & 15;
		}
		Position += format(output[Position], len, "%c", LettersTable[Character]);

		if(i < len){
			Character = (input[i] << 2) & 63;
			
			if(++i < len){
				Character |= (input[i] >> 6) & 3;
			}
			Position += format(output[Position], len, "%c", LettersTable[Character]);
		} else {
			i++;
			Position += format(output[Position], len, "%c", SpaceReplacer);
		}

		if(i < len){
			Character = input[i] & 63;
			Position += format(output[Position], len, "%c", LettersTable[Character]);
		} else {
			Position += format(output[Position], len, "%c", SpaceReplacer);
		}
	}
}

//EOF
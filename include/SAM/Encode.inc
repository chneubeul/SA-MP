/****************************************************************************************************
 *                                                                                                  *
 * Encode Include                                                                                   *
 *                                                                                                  *
 * File Version: 1.3                                                                                *
 *                                                                                                  *
 * rot13(string[]);                                                                                 *
 * code128(string1[],string2[]);                                                                    *
 * RollX(string1[],roll,string2[]);                                                                 *
 * GetRollDecode(roll);                                                                             *
 * HexNegative(string1[],mode,string2[],maxdest = sizeof(string2));                                 *
 *                                                                                                  *
 * Hex Negative Mode:                                                                               *
 * Encrypt: A -> B, B -> A                                                                          *
 * Decrypt: A -> B, B -> A                                                                          *
 * A       B                                                                                        *
 * 1       15                                                                                       *
 * 2       14                                                                                       *
 * 3       13                                                                                       *
 * 4       12                                                                                       *
 * 5       11                                                                                       *
 * 6       10                                                                                       *
 * 7       9                                                                                        *
 * 8       8                                                                                        *
 *                                                                                                  *
 ****************************************************************************************************/

stock rot13(string[]){
	for(new i = 0, j = strlen(string); i < j; i++){
		if('a' <= string[i] <= 'z'){
			string[i] = (string[i] - 'a' + 13) % 26 + 'a';
		} else if('A' <= string[i] <= 'Z'){
			string[i] = (string[i] - 'A' + 13) % 26 + 'A';
		}
	}
	return string;
}

stock HexNegative(string1[],mode,string2[],maxdest = sizeof(string2)){
	if(mode < 1 || mode > 15){
		format(string2,maxdest,"%s","#NAN");
		print("[ADM] Warring: Invalid HexNegative mode.");
	} else {
		for(new i = 0, j = strlen(string1); i < j; i++){
			string2[i] = (((0xF & ((string1[i] >> 4)+mode))*16) + (0xF & ((string1[i] & 0xF)+mode)));
		}
		string2[strlen(string1)] = EOS;
	}
}

stock code128(string1[],string2[]){
	for(new i = 0, j = strlen(string1); i < j; i++){
		string2[i] = (0xFF & string1[i]+128);
	}
	string2[strlen(string1)] = EOS;
}

stock GetRollDecode(roll){
	return (0xFF & (256-roll));
}

stock RollX(string1[],roll,string2[]){
	if(roll < 0 || roll > 255) print("[ADM] Warring: Invalid RollX mode.");
	for(new i = 0, j = strlen(string1); i < j; i++){
		string2[i] = (0xFF & (string1[i]+roll));
	}
	string2[strlen(string1)] = EOS;
}

/***********************
 * Encode Include v1.0 *
 ***********************/

stock rot13(string[]){
	for(new index = 0; index < strlen(string); index++){
		if('a' <= string[index] <= 'z'){
			string[index] = (string[index] - 'a' + 13) % 26 + 'a';
		} else if('A' <= string[index] <= 'Z'){
			string[index] = (string[index] - 'A' + 13) % 26 + 'A';
		}
	}
	return string;
}

stock code128(string1[],string2[]){
	for(new i = 0;i < strlen(string1);i++){
		string2[i] = (0xFF & string1[i]+128);
	}
	string2[strlen(string1)] = EOS;
}

stock HexNegative(string1[],mode,string2[],maxdest = sizeof(string2)){
	if(mode < 1 || mode > 15){
		format(string2,maxdest,"%s","#NAN");
	} else {
		for(new i = 0;i < strlen(string1);i++){
			string2[i] = (0xFF & (string1[i]+(mode*15)));
		}
		string2[strlen(string1)] = EOS;
	}
}

stock GetRollDecode(roll){
	return (0xFF & (256-roll));
}

stock RollX(string1[],roll,string2[]){
	for(new i = 0;i < strlen(string1);i++){
		string2[i] = (0xFF & (string1[i]+roll));
	}
	string2[strlen(string1)] = EOS;
}

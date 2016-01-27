/****************************************************************************************************
 *                                                                                                  *
 * Encode Include                                                                                   *
 *                                                                                                  *
 * File Version: 1.3b                                                                               *
 *                                                                                                  *
 * rot13(string[]);                                                                                 *
 * code128(input[],output[]);                                                                       *
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
}

stock code128(input[],output[]){
	for(new i = 0, j = strlen(input); i < j; i++){
		output[i] = (0xFF & input[i]+128);
	}
	output[strlen(input)] = EOS;
}

//EOF
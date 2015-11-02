/****************************************************************************************************
 *                                                                                                  *
 * Encode Include v1.1                                                                              *
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

#include <SAM/BitFunctions>
 
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

stock ExtractHex(value,&excerpt1,&excerpt2){
	excerpt1 = 0, excerpt2 = 0;
	for(new i = 4; i <= 7; i++){
		excerpt1 = SetValueBit(excerpt1,i-4,GetValueBit(value,i));
	}
	for(new i = 0; i <= 3; i++){	
		excerpt2 = SetValueBit(excerpt2,i,GetValueBit(value,i));
	}
}

stock HexNegative(string1[],mode,string2[],maxdest = sizeof(string2)){
	if(mode < 1 || mode > 15){
		format(string2,maxdest,"%s","#NAN");
	} else {
		new va1, va2;
		for(new i = 0;i < strlen(string1);i++){
			ExtractHex(string1[i],va1,va2);
			string2[i] = (((0xF & (va1+mode))*16) + (0xF & (va2+mode)));
		}
		string2[strlen(string1)] = EOS;
	}
}

stock code128(string1[],string2[]){
	for(new i = 0;i < strlen(string1);i++){
		string2[i] = (0xFF & string1[i]+128);
	}
	string2[strlen(string1)] = EOS;
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

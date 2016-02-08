SA:MP ADM Projects


Readme Version: 1.0.0



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\StreamerFunction.inc

Published: http://forum.sa-mp.com/showthread.php?t=590918

Description: This expands include an additional function to the Streamer Incognito



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\BitFunctions.inc

Published: http://forum.sa-mp.com/showthread.php?t=591223

Description: This include allows us to operate on bits.



How to use function:



new bool:PlayerConfig[MAX_PLAYERS][32]; //create variables bool store player information



//Extract the value which will be stored in a database

//now we loaded with 32 values to variables bool from Which We can use

stock ExtractPlayerConfig(playerid,value){ 

	for(new i=31; i >= 0; i--){ 

		PlayerConfig[playerid][i] = bool:GetValueBit(value,i); 

	} 

} 



//To receive a number of these values, we use

stock PackPlayerConfig(playerid,&value){ 

	for(new i=31; i >= 0; i--){ 

		SetValueBit(value,i,PlayerConfig[playerid][i]); 

	} 

}

//Now a value is written to the database :D



Additional features is:

ExtractValue(value, &byte1, &byte2, &byte3, &byte4);

ExtractFloat(Float:value, &byte1, &byte2, &byte3, &byte4);

MergeValue(&value, byte1, byte2, byte3, byte4);

MergeFloat(&Float:value, byte1, byte2, byte3, byte4);



Example:

new val = 0x89ABCDEF; //input value

new a, b, c, d; //output values



ExtractValue(val,a,b,c,d); //Extracted value



printf("%x %x %x %x",a,b,c,d); //prints 89 AB CD EF 



new tmp = 0; 

MergeValue(tmp,a,b,c,d); 



printf("%x",tmp); //prints 89ABCDE



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\RGB.inc

Published: http://forum.sa-mp.com/showthread.php?t=590770

Description: This include contains a very fast function to conversion color.



How to use function:



new col = ShiftRGBAToARGB(0xFF6600FF); //returned 0xFFFF6600; 



new red, green, blue, alpha; 

ShiftRGBAToHex(0xFF6600AA,red,green,blue,alpha); 



//returned red = 0xFF, green = 0x66, blue = 0x00, alpha = 0xAA;



new r = GetRHexFromRGBA(0xFF6600AA); //returned r = 0xFF; 



new r = GetRFromRGBA(0xFF6600AA); //returned r = 0xFF000000;  



new buffer[256];

format(buffer,sizeof buffer,"bla bla %s second part",GetColor(0xFF6600FF);

//the second part of the inscription will be orange FF6600



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\3DTryg.inc

Published: http://forum.sa-mp.com/showthread.php?t=591010

Description: This includes contain advanced functions 2D/3D manipulation.



How to use:



GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty);

and

GetPointInFront3D(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);



They allow you to get point ahead GetXYInFrontOf...



The inverse of this function is. By to two points we can get the rotation.

GetRotationFor2Point2D(Float:x,Float:y,Float:tx,Float:ty,&Float:rz);

GetRotationFor2Point3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:rx,&Float:rz);



We can also get the point between the two points.

GetPointFor2Point2D(Float:x1,Float:y1,Float:x2,Float:y2,Float:percent_size,&Float:tx,&Float:ty);

GetPointFor2Point3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:percent_size,&Float:tx,&Float:ty,&Float:tz);



Checked whether the point is located between two points

bool:IsPointBetween2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB);

bool:IsPointBetween2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB);



Or check whether the point is close to two points

bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist);

bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist);



Notice: These functions have a more accurate version, When we add the include 

\#define USE_NEW_PROTOTYPE_NT

\#include \<SAM/3DTryg\>



A very useful feature is.

bool:IsProbable(chance); //Enter chance in the range 0 - 100



Include also includes a low-level function:

NLTZ, NMTZ, NLTZF, NMTZF, CompRotation, CompRotationFloat, sqrtN



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\GangZoneEx.inc

Published: N/A

Description: This include extends the standard functions SA:MP.



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\ADM.inc

Published: http://forum.sa-mp.com/showthread.php?t=595203

Description: This includes contain a function by which we can encrypt files/data.



How to use:



Example (ADMx32):

Encrypt Key: 191 12 239 86

Decrypt Key: 65 244 17 170



a - encrypt argument

b - decrypt argument



b = 256-a



256 - 191 = 65

256 - 12 = 244

256 - 239 = 17

256 - 86 = 170



Pawn Code for File:

new ADM:edi; 



edi = ADMx32("test.txt","test.adm","191 12 239 86"); 



printf("ADM return code %d",ADMToInt(edi)); 

switch(edi){ 

	case ERROR_CODE_ADM_UNEXEC: print("Error: function unexecutable"); 

	case ERROR_CODE_ADM_OK: { 

		print("Encryption successfully completed"); 

		ADMx32("test.adm","test2.txt","65 244 17 170"); 

	} 

	case ERROR_CODE_ADM_INPUT: print("Error input file not exist"); 

	case ERROR_CODE_ADM_OUTPUT: print("Error output file exist"); 

	case ERROR_CODE_ADM_KEY: print("Error invalid key"); 

	case ERROR_CODE_ADM_SIZE: print("Error invalid file size"); 

	case ERROR_CODE_ADM_OPEN_INPUT: print("Error open input file"); 

	case ERROR_CODE_ADM_OPEN_OUTPUT: print("Error open output file"); 

}  



Screens:

http://i.imgur.com/UoIa31S.png

http://i.imgur.com/D2AoUeI.png

http://i.imgur.com/WUh3D37.png



Pawn Code for String:

new buffer[256]; 



ADMx32String("This is test string", buffer, "191 12 239 86"); 

printf("Binary data: '%s'",buffer); // 'tXÉßubv3qbĘßcČ(zV' 



new buffer2[512]; //2 * sizeof(buffer) 

StringToHexString(buffer,buffer2); 

printf("Hex data: '%s'",buffer2); // '137458C9DF756276337162CADF7F63C8287A56'





Pawn Code for Dump File:

\#define SCRIPT_DUMP_KEY	"191 12 239 86" 



new GameModeDumpFile = INVALID_DUMP_FILE, 

	GameModeDumpFileName[80]; 



forward WriteGameModeError(string[]); 



public WriteGameModeError(string[]){ 

	if(!IsDumpFileOpen(GameModeDumpFile)){ 

		GameModeDumpFile = DumpFileCreate(GameModeDumpFileName,SCRIPT_DUMP_KEY,KEY_TYPE_ADMx32); //create new dump file 

		DumpFileWrite(GameModeDumpFile,"\n"); 

	} 

	new ADM:edi = DumpFileWrite(GameModeDumpFile,string); 

	DumpFileWrite(GameModeDumpFile,"\n"); 

	if(edi == ERROR_CODE_ADM_OK) return 1; 

	switch(edi){ 

		case ERROR_CODE_ADM_DMP_IDX: print("Error invalid dump file index"); 

		case ERROR_CODE_ADM_DMP_NAME: print("Error invalid dump file name"); 

		case ERROR_CODE_ADM_KEY: print("Error invalid key"); 

		case ERROR_CODE_ADM_OPEN_OUTPUT: print("Error open output file"); 

	} 

	return 0;	 

} 



public OnGameModeInit(){ //OnFilterScriptInit 

	

	new wl_date[3], wl_time[3]; 

	getdate(wl_date[0],wl_date[1],wl_date[2]); 

	gettime(wl_time[0],wl_time[1],wl_time[2]); 

	format(GameModeDumpFileName,sizeof(GameModeDumpFileName),"GM_%02d.%02d.%02d_%02d%02d%02d.dmp",wl_date[0],wl_date[1],wl_date[2],wl_time[0],wl_time[1],wl_time[2]); 

	

	return 1; 

}



Comments:

a) Max file size:

- 2 GB for SA:MP

- 16 EB for Windows application

b) File coding

- ASCII/ANSI (8 bit) for SA:MP

- Any for Windows application



Windows Application:

https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM/ADM%20Include



Dump File Open:

https://github.com/AbyssMorgan/SA-MP/blob/master/include/SAM/ADM%20Include/SAMP%20Dump%20File.zip



Key Generator:

http://ngc.ugu.pl/admkg/index.php



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\MapAndreasEx.inc

Published: N/A

Description: This expands include an additional function to the MapAndreas



How to use:

SafeMapAndreasInit() - Initiates mapandreas, if it isn't already initialized

MapAndreasFindZ(Float:x,Float:y,&Float:z) - Find Z by X Y, prevents crash mapandreas



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\HTMLColor.inc

Published: N/A

Description: It contains color html.



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\DataConvert.inc

Published: N/A

Description: Include contains standard function for data conversion



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\TextDrawEx.inc

Published: N/A

Description: This include extends the standard functions SA:MP.



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\LY.inc

Published: http://forum.sa-mp.com/showthread.php?t=598933

Description: This include allows to use large numbers over the limit pawn.





Example:

new a = 0, b = 0, c[LY_STRING_LEN]; 



//a - prefix value 

//b - sufix value 



//plus test 

UpdateLY(a,b,5000); 

GetLYString(a,b,c); 

printf("VAL: %s",c); 



a = 1999999900; 

GetLYString(a,b,c); 

printf("VAL: %s",c); 



while(a < 2000000000){ 

	UpdateLY(a,b,2104567893); 

	GetLYString(a,b,c); 

	printf("VAL: %s",c); 

} 



//minus test 

a = b = 0; 



UpdateLY(a,b,2104567893); 

GetLYString(a,b,c); 

printf("VAL: %s",c); 





while(a != 0 || b != 0){ 

	UpdateLY(a,b,-2004567893); 

	GetLYString(a,b,c); 

	printf("VAL: %s",c); 

}



Results:



//0 -> 2000000000000000000 

VAL: 5000 

VAL: 1999999900000005000 

..

VAL: 1999999998914695971 

VAL: 2000000000000000000 



//2104567893 -> 0 

VAL: 2104567893 

VAL: 100000000 

VAL: 0  



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


Include: SAM\DoT.inc

Published: N/A

Description: N/A


$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



Include: SAM\BINLDR.inc

Published: http://forum.sa-mp.com/showthread.php?p=3653547

Description: This include allows us to load objects in a compressed binary file or encrypted file.



To do this we need:



1. Download and install this include

\#include \<SAM/BINLDR\>


2. Make sure that the input file contains objects

CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);

CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid);

CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid);

CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, playerid);

CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, playerid, Float:streamdistance);

CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, playerid, Float:streamdistance, Float:drawdistance);



3. Compress objects (remember to keep the original file), preferably using a simple script https://github.com/AbyssMorgan/SA-MP/blob/master/filterscripts/img.pwn

new edi = SaveBinaryObjectIMG("obiekty-world.txt","obiekty-world.bin");

if(edi != ERROR_CODE_BINLDR_OK){

	printf("Error Save Binary Object Code: %d",edi);

}



4. Load compress object

new edi = LoadBinaryObjectIMG("obiekty-world.bin");

if(edi != ERROR_CODE_BINLDR_OK){

	printf("Error Load Binary Object Code: %d",edi);

}





5. Enjoy the results

Standard object loader:

obiekty-world.txt objects: 100597 load time 3541 ms file size: 10.30 MB (Byte: 10'875'043)



BIN object loader:

obiekty-world.bin objects: 100597 load time 1981 ms file size: 4.02 MB (Byte: 4'225'074)



Notice: This include is recommended for experienced users.



$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$




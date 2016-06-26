/****************************************************************************************************
 *                                                                                                  *
 *                                     San Andreas Object Image                                     *
 *                                                                                                  *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/core                          *
 *                                                                                                  *
 * This is beta include!                                                                            *
 *                                                                                                  *
 * File Version: 1.1                                                                                *
 *                                                                                                  *
 * Functions:                                                                                       *
 * SAOI:CreateSAOIFile(const name[],author[],version[],description[] = "");                         *
 * SAOI:SaveDynamicObject(objectid,const name[]);                                                   *
 * SAOI:LoadObjectImage(const name[],&count=0,&load_time=0);                                        *
 * bool:UnloadObjectImage(SAOI:index);                                                              *
 * CountObjectsForIndex(SAOI:index);                                                                *
 *                                                                                                  *
 * Extended Functions:                                                                              *
 * SAOI:FindFreeSAOIID();                                                                           *
 * string_mod(input[],output[]);                                                                    *
 *                                                                                                  *
 ****************************************************************************************************/

/*
//Check Version SAOI.inc
#if !defined _SAOI_VERSION
	#error You need SAOI.inc v1.1
#elseif !defined SAOI_LOADER_VERSION
	#error Update you SAOI.inc to v1.1
#elseif (SAOI_LOADER_VERSION < 10101)
	#error Update you SAOI.inc to v1.1
#endif
*/

#if defined _SAOI_VERSION
	#endinput
#endif
#define _SAOI_VERSION

#define SAOI_LOADER_VERSION 				(10101)			//a.b[c] 10000*a+100*b+c

#define SAOI_HEADER_KEY						"SAOI 1.0 ADM"	//You can never change !!!

#define INVALID_SAOI_FILE					(SAOI:0)		//You can never change !!!
#define SAOI_EXTRA_ID_OFFSET				(1000000)		//You can never change !!!

#define MAX_SAOI_FILE_SIZE					(2147483647)	//~2 GB
#define MAX_SAOI_FILE						(SAOI:1024)		//more ? why not

#define MAX_AUTHOR_SIZE 					(32)			//Max 255 (auto resize header, compatible with all version) 
#define MAX_VERSION_SIZE 					(32)			//Max 255 (auto resize header, compatible with all version)
#define MAX_DESCRIPTION_SIZE 				(128)			//Max 255 (auto resize header, compatible with all version)

#define MAX_FONT_NAME 						(32)			//These limits can be changed according to the San Andreas 
#define MAX_TXD_NAME						(32)			//These limits can be changed according to the San Andreas 
#define MAX_TEXTURE_NAME					(32)			//These limits can be changed according to the San Andreas 
#define MAX_TEXT_NAME						(1024)			//(Max 65535 for c++) These limits can be changed according to the San Andreas

#define SAOI_ERROR_UNEXEC					(SAOI:0)		//function unexecutable
#define SAOI_ERROR_SUCCESS					(SAOI:-1)		//success
#define SAOI_ERROR_INPUT_NOT_EXIST			(SAOI:-2)		//input file not exist
#define SAOI_ERROR_OUTPUT_NOT_EXIST			(SAOI:-3)		//output file not exist
#define SAOI_ERROR_INPUT_EXIST				(SAOI:-4)		//input file exist
#define SAOI_ERROR_OUTPUT_EXIST				(SAOI:-5)		//output file exist
#define SAOI_ERROR_INPUT_NOT_OPEN			(SAOI:-6)		//error open input file
#define SAOI_ERROR_OUTPUT_NOT_OPEN			(SAOI:-7)		//error open output file
#define SAOI_ERROR_FILE_SIZE				(SAOI:-8)		//invalid file size
#define SAOI_ERROR_INVALID_OBJECTID			(SAOI:-9)		//invalid objectid
#define SAOI_ERROR_AUTHOR_SIZE				(SAOI:-10)		//invalid author size
#define SAOI_ERROR_VERSION_SIZE				(SAOI:-11)		//invalid version size
#define SAOI_ERROR_DESCRIPTION_SIZE			(SAOI:-12)		//invalid description size
#define SAOI_ERROR_INVALID_HEADER			(SAOI:-13)		//invalid header

//BitFunctions.inc
#define SAOI_GetValueBit(%0,%1)				((%0) >>> (%1) & 0x01)
#define SAOI_SetValueBit(%0,%1,%2)			((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define SAOI_ExtractValue(%0,%1,%2,%3,%4)	((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define SAOI_ExtractFloat(%0,%1,%2,%3,%4)	((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define SAOI_MergeValue(%0,%1,%2,%3,%4)		((%0) = (((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))
#define SAOI_MergeFloat(%0,%1,%2,%3,%4)		((%0) = Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#define SAOI_MergeValueEx(%1,%2,%3,%4)		(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4))
#define SAOI_MergeFloatEx(%1,%2,%3,%4)		(Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

new bool:SAOIFileStatus[SAOI:MAX_SAOI_FILE];

stock string_mod(input[],output[]){
	for(new i = 0, j = strlen(input); i < j; i++){
		output[i] = (0xFF & input[i]+128);
	}
	output[strlen(input)] = EOS;
}

stock SAOI:FindFreeSAOIID(){
	for(new SAOI:i = SAOI:1; i < MAX_SAOI_FILE; i = SAOI:(_:i+1)){
		if(!SAOIFileStatus[i]) return i;
	}
	return INVALID_SAOI_FILE;
}

stock SAOI:CreateSAOIFile(const name[],author[],version[],description[] = ""){
	if(fexist(name)) return SAOI_ERROR_OUTPUT_EXIST;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	fwrite(outf,SAOI_HEADER_KEY);
	//Create Header
	new author_size = strlen(author),
		version_size = strlen(version),
		description_size = strlen(description);
	
	if(author_size > MAX_AUTHOR_SIZE){
		fclose(outf);
		return SAOI_ERROR_AUTHOR_SIZE;
	}
	if(version_size > MAX_VERSION_SIZE){
		fclose(outf);
		return SAOI_ERROR_VERSION_SIZE;
	}
	if(description_size > MAX_DESCRIPTION_SIZE){
		fclose(outf);
		return SAOI_ERROR_DESCRIPTION_SIZE;
	}
	
	new key[32];
	for(new i = 0; i < 32; i++){
		key[i] = random(255)+1;
	}
	
	new s;

	s = 0;
	for(new i = 0; i < author_size; i++){
		author[i] = ((author[i]+key[s]) & 0xFF);
		s++;
		if(s >= 32) s = 0;
	}
	fputchar(outf,author_size,false);
	for(new i = 0; i < author_size; i++){
		fputchar(outf,author[i],false);
	}
	
	s = 0;
	for(new i = 0; i < version_size; i++){
		version[i] = ((version[i]+key[s]) & 0xFF);
		s++;
		if(s >= 32) s = 0;
	}
	fputchar(outf,version_size,false);
	for(new i = 0; i < version_size; i++){
		fputchar(outf,version[i],false);
	}
	
	s = 0;
	for(new i = 0; i < description_size; i++){
		description[i] = ((description[i]+key[s]) & 0xFF);
		s++;
		if(s >= 32) s = 0;
	}
	fputchar(outf,description_size,false);
	for(new i = 0; i < description_size; i++){
		fputchar(outf,description[i],false);
	}
	
	for(new i = 0; i < 32; i++){
		fputchar(outf,((256-key[i]) & 0xFF),false);
	}
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

stock SAOI:SaveDynamicObject(objectid,const name[]){
	if(!IsValidDynamicObject(objectid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, Float:streamdistance, Float:drawdistance, areaid, priority,
		arg_count = 13, material_used = 0, material_text_used = 0;
	
	//Get Object Info
	modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MODEL_ID);
	GetDynamicObjectPos(objectid,x,y,z);
	GetDynamicObjectRot(objectid,rx,ry,rz);
	worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_WORLD_ID);
	interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_INTERIOR_ID);
	
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_DRAW_DISTANCE,drawdistance);
	
	areaid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_AREA_ID);
	priority = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_PRIORITY);
	
	//Count Arg
	for(new i = 13; i > 7; i--){
		switch(i){
			case 13: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 12: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(drawdistance == 0.0){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(streamdistance == 300.0){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,arg_count,false);
	
	//Save Object Info
	SAOI_ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI_ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI_ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI_ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI_ExtractFloat(rx,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI_ExtractFloat(ry,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI_ExtractFloat(rz,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 8){
		SAOI_ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI_ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI_ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI_ExtractFloat(drawdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI_ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 13){
		SAOI_ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	//Get and Save Object Material
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialUsed(objectid,i)){
			SAOI_SetValueBit(material_used,i,1);
		}
	}
	
	SAOI_ExtractValue(material_used,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	for(new i = 0; i < 16; i++){
		if(SAOI_GetValueBit(material_used,i) == 1){
			new mid, txdname[MAX_TXD_NAME], texturename[MAX_TEXTURE_NAME], materialcolor;
			GetDynamicObjectMaterial(objectid,i,mid,txdname,texturename,materialcolor);
			
			SAOI_ExtractValue(mid,int1,int2,int3,int4);
			fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			fputchar(outf,strlen(txdname),false);
			string_mod(txdname,txdname);
			for(new k = 0, l = strlen(txdname); k < l; k++){
				fputchar(outf,txdname[k],false);
			}
			
			string_mod(texturename,texturename);
			fputchar(outf,strlen(texturename),false);
			for(new k = 0, l = strlen(texturename); k < l; k++){
				fputchar(outf,texturename[k],false);
			}
			
			SAOI_ExtractValue(materialcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
		}
	}
	
	//Get and Save Object Material Text
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialTextUsed(objectid,i)){
			SAOI_SetValueBit(material_text_used,i,1);
		}
	}
	
	SAOI_ExtractValue(material_text_used,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	for(new i = 0; i < 16; i++){
		if(SAOI_GetValueBit(material_text_used,i) == 1){
			new text[MAX_TEXT_NAME], materialsize, fontface[MAX_FONT_NAME], fontsize, bold, fontcolor, backcolor, textalignment;
			GetDynamicObjectMaterialText(objectid,i,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
			
			new len = strlen(text);
			SAOI_ExtractValue(len,int1,int2,int3,int4);
			fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			string_mod(text,text);
			for(new k = 0, l = strlen(text); k < l; k++){
				fputchar(outf,text[k],false);
			}
			
			fputchar(outf,materialsize,false);
			
			fputchar(outf,strlen(fontface),false);
			string_mod(fontface,fontface);
			for(new k = 0, l = strlen(fontface); k < l; k++){
				fputchar(outf,fontface[k],false);
			}
			
			fputchar(outf,fontsize,false);
			
			fputchar(outf,bold,false);
			
			SAOI_ExtractValue(fontcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI_ExtractValue(backcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			fputchar(outf,textalignment,false);
			
			
		}
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

stock SAOI:LoadObjectImage(const name[],&count=0,&load_time=0){
	count = 0;
	new NTTime = GetTickCount();
	if(!fexist(name)) return SAOI_ERROR_INPUT_NOT_EXIST;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return SAOI_ERROR_INPUT_NOT_OPEN;
	new asize = flength(inpf), idx = 0, cnt = 0;
	if(asize > MAX_SAOI_FILE_SIZE || asize < 0){
		fclose(inpf);
		return SAOI_ERROR_FILE_SIZE;
	}
	new SAOI:SAOI_ID = FindFreeSAOIID(), parse_step, bool:parse_header,
		author[MAX_AUTHOR_SIZE], version[MAX_VERSION_SIZE], description[MAX_DESCRIPTION_SIZE];
		
	SAOIFileStatus[SAOI_ID] = true;
	
	new modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, Float:streamdistance = 300.0, Float:drawdistance = 0.0, areaid = -1, priority = 0,
		arg_count = 0, material_used = 0, material_text_used = 0, objectid;
	
	while(idx < asize){
		if(!parse_header){
			new h_len = strlen(SAOI_HEADER_KEY), h_key[32];
			for(new i = 0; i < h_len; i++){
				h_key[i] = fgetchar(inpf,0,false), idx++;
			}
			h_key[h_len] = EOS;
			#if defined DEBUG_SAOI
				printf("|%s| == |%s|",h_key,SAOI_HEADER_KEY);
			#endif
			if(!strcmp(h_key,SAOI_HEADER_KEY,true)){
				new author_size, version_size, description_size, key[32];
				
				author_size = fgetchar(inpf,0,false), idx++;
				for(new i = 0; i < author_size; i++){
					author[i] = fgetchar(inpf,0,false), idx++;
				}
				
				version_size = fgetchar(inpf,0,false), idx++;
				for(new i = 0; i < version_size; i++){
					version[i] = fgetchar(inpf,0,false), idx++;
				}
				
				description_size = fgetchar(inpf,0,false), idx++;
				for(new i = 0; i < description_size; i++){
					description[i] = fgetchar(inpf,0,false), idx++;
				}
				
				for(new i = 0; i < 32; i++){
					key[i] = fgetchar(inpf,0,false), idx++;
				}
				
				
				new s;
				
				s = 0;
				for(new i = 0; i < author_size; i++){
					author[i] = ((author[i]+key[s]) & 0xFF);
					s++;
					if(s >= 32) s = 0;
				}
				
				s = 0;
				for(new i = 0; i < version_size; i++){
					version[i] = ((version[i]+key[s]) & 0xFF);
					s++;
					if(s >= 32) s = 0;
				}
				
				s = 0;
				for(new i = 0; i < description_size; i++){
					description[i] = ((description[i]+key[s]) & 0xFF);
					s++;
					if(s >= 32) s = 0;
				}
				
				parse_header = true;
			} else {
				fclose(inpf);
				return SAOI_ERROR_INVALID_HEADER;
			}
		} else {
			if(parse_step == 0){
				//Get Arg Count
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				objectid = 0, material_used = 0, material_text_used = 0, worldid = -1, interiorid = -1, streamdistance = 300.0,
				drawdistance = 0.0, areaid = -1, priority = 0;
			} else if(parse_step >= 1 && parse_step <= arg_count){
				switch(parse_step){
					case 1: {
						SAOI_MergeValue(modelid,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 2;
					}
					case 2: {
						SAOI_MergeFloat(x,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 3: {
						SAOI_MergeFloat(y,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 4: {
						SAOI_MergeFloat(z,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 5: {
						SAOI_MergeFloat(rx,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 6: {
						SAOI_MergeFloat(ry,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 7: {
						SAOI_MergeFloat(rz,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 8: {
						SAOI_MergeValue(worldid,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 9: {
						SAOI_MergeValue(interiorid,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 10: {
						SAOI_MergeFloat(streamdistance,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 11: {
						SAOI_MergeFloat(drawdistance,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 12: {
						SAOI_MergeValue(areaid,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 4;
					}
					case 13: {
						SAOI_MergeValue(areaid,0,0,0,fgetchar(inpf,0,false));
						idx += 1;
					}
				}
			} else if(parse_step == 14){
				SAOI_MergeValue(material_used,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				idx += 2;
				#if defined DEBUG_SAOI
					printf("material_used: %b",material_used);
				#endif
			} else if(parse_step >= 15 && parse_step <= 30){
				if(SAOI_GetValueBit(material_used,(parse_step-15)) == 1){
					new txdname[MAX_TXD_NAME], texturename[MAX_TEXTURE_NAME], materialcolor, txdsize, texturenamesize;
					
					SAOI_MergeValue(modelid,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
					idx += 2;
					
					txdsize = fgetchar(inpf,0,false), idx++;
					#if defined DEBUG_SAOI
						printf("TXD Size: %d",txdsize);
					#endif
					for(new i = 0; i < txdsize; i++){
						txdname[i] = fgetchar(inpf,0,false), idx++;
					}
					txdname[txdsize] = EOS;
					string_mod(txdname,txdname);
					
					texturenamesize = fgetchar(inpf,0,false), idx++;
					
					for(new i = 0; i < texturenamesize; i++){
						texturename[i] = fgetchar(inpf,0,false), idx++;
					}
					texturename[texturenamesize] = EOS;
					string_mod(texturename,texturename);
					
					SAOI_MergeValue(materialcolor,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
					idx += 4;
					
					SetDynamicObjectMaterial(objectid,(parse_step-15),modelid,txdname,texturename,materialcolor);
					
					#if defined DEBUG_SAOI
						printf("%d %d %d %s %s %08x",objectid,(parse_step-15),modelid,txdname,texturename,materialcolor);
					#endif
				}
			} else if(parse_step == 31){
				SAOI_MergeValue(material_text_used,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				idx += 2;
				#if defined DEBUG_SAOI
					printf("material_text_used: %b",material_text_used);
				#endif
			} else if(parse_step >= 32 && parse_step <= 47){
				if(SAOI_GetValueBit(material_text_used,(parse_step-32)) == 1){
					new text[MAX_TEXT_NAME], fontface[MAX_FONT_NAME], textsize, materialsize, fontfacesize, bold, fontcolor, backcolor,
						textalignment, fontsize;
					
					SAOI_MergeValue(textsize,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
					idx += 2;
					
					for(new i = 0; i < textsize; i++){
						text[i] = fgetchar(inpf,0,false), idx++;
					}
					text[textsize] = EOS;
					string_mod(text,text);
					
					materialsize = fgetchar(inpf,0,false), idx++;
					
					fontfacesize = fgetchar(inpf,0,false), idx++;
					
					for(new i = 0; i < fontfacesize; i++){
						fontface[i] = fgetchar(inpf,0,false), idx++;
					}
					fontface[fontfacesize] = EOS;
					string_mod(fontface,fontface);
					
					fontsize = fgetchar(inpf,0,false), idx++;
					
					bold = fgetchar(inpf,0,false), idx++;
					
					SAOI_MergeValue(fontcolor,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
					idx += 4;
					
					SAOI_MergeValue(backcolor,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
					idx += 4;
					
					textalignment = fgetchar(inpf,0,false), idx++;
					
					SetDynamicObjectMaterialText(objectid,(parse_step-32),text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
					#if defined DEBUG_SAOI
						printf("%d %d %s %d %s %d %d %08x %08x %d",objectid,(parse_step-32),text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
					#endif
				}
			}
			
			
			if(parse_step == arg_count){
				objectid = CreateDynamicObject(modelid,x,y,z,rx,ry,rz,worldid,interiorid,-1,streamdistance,drawdistance,areaid,priority);
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+_:SAOI_ID); //identify objects
				parse_step = 13;
				
				#if defined DEBUG_SAOI
					printf("%d %f %f %f %f %f %f %d %d -1 %f %f %d %d ex: %d",modelid,x,y,z,rx,ry,rz,worldid,interiorid,streamdistance,drawdistance,areaid,priority,SAOI_EXTRA_ID_OFFSET+_:SAOI_ID);
				#endif
				cnt++;
			} else if(parse_step == 47){
				parse_step = -1;
			}
			parse_step++;
		}
	}
	fclose(inpf);
	
	load_time = GetTickCount()-NTTime;
	count += cnt;
	
	new buffer[256];
	format(buffer,sizeof buffer,"File %s has been loaded in %d ms",name,load_time);
	printf(buffer);
	format(buffer,sizeof buffer,"Author: %s Version: %s Objects: %d",author,version,cnt);
	printf(buffer);
	if(!isnull(description)){
		format(buffer,sizeof buffer,"Description: %s",description);
		printf(buffer);
	}
	return SAOI_ID;
}

stock bool:UnloadObjectImage(SAOI:index){
	if(!SAOIFileStatus[index]) return false;
	for(new i = 1, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i <= j; i++){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_EXTRA_ID) == _:index-SAOI_EXTRA_ID_OFFSET){
				DestroyDynamicObject(i);
			}
		}
	}
	SAOIFileStatus[index] = false;
	return true;
}

stock CountObjectsForIndex(SAOI:index){
	if(!SAOIFileStatus[index]) return 0;
	new cnt = 0;
	for(new i = 1, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i <= j; i++){
		if(IsValidDynamicObject(i)){
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_EXTRA_ID) == _:index-SAOI_EXTRA_ID_OFFSET){
				cnt++;
			}
		}
	}
	return cnt;
}

//EOF
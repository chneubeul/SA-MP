/*************************************************************************************************************************************
 *                                                                                                                                   *
 *                                                        )(   SWAP File   )(                                                        *
 *                                                                                                                                   *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                                                               *
 *                                                                                                                                   *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                            *
 * Publication: ---                                                                                                                  *
 * Website: http://8.ct8.pl                                                                                                          *
 *                                                                                                                                   *
 * Plugins: None                                                                                                                     *
 * Modules: None                                                                                                                     *
 *                                                                                                                                   *
 * File Version: 1.0.0                                                                                                               *
 * SA:MP Version: 0.3.7                                                                                                              *
 *                                                                                                                                   *
 * Data types:                                                                                                                       *
 * String - X bytes string                                                                                                           *
 * Block - the same as string but don't check EOS on R/W functions                                                                   *
 * Array - 4 bytes array cells                                                                                                       *
 * Float - 4 bytes flaot value                                                                                                       *
 * Integer - 4 bytes integer value                                                                                                   *
 *                                                                                                                                   *
 * Functions:                                                                                                                        *
 * SWAP::create_empty(const file_name[]);                   //create new empty file (not recommended)                                *
 * SWAP::create_block(const file_name[],size);              //create block for empty file (not recommended, big fragmentation)       *
 * SWAP::reserve(const file_name[],size);                   //reserve new SWAP file size (recommended)                               *
 * SWAP::format(const file_name[],key[],k_len=sizeof(key)); //format new SWAP file (use after SWAP::reserve, not recommended)        *
 * SWAP::format_random(const file_name[]);                  //format new SWAP file (use after SWAP::reserve, recommended)            *
 * SWAP::decrypt_file(const input[],const output[],key[],k_len=sizeof(key));                                                         *
 * SWAP::read_string(const file_name[],key[],position,text[],len,k_len=sizeof(key));                                                 *
 * SWAP::write_string(const file_name[],key[],position,text[],max_dest=sizeof(text),k_len=sizeof(key));                              *
 * SWAP::read_array(const file_name[],key[],position,array[],len,k_len=sizeof(key));                                                 *
 * SWAP::write_array(const file_name[],key[],position,array[],max_dest=sizeof(array),k_len=sizeof(key));                             *
 * SWAP::write_block(const file_name[],key[],position,text[],max_dest=sizeof(text),k_len=sizeof(key));                               *
 * SWAP::read_int(const file_name[],key[],position,k_len=sizeof(key));                                                               *
 * SWAP::write_int(const file_name[],key[],position,value,k_len=sizeof(key));                                                        *
 * Float:SWAP::read_float(const file_name[],key[],position,k_len=sizeof(key));                                                       *
 * SWAP::write_float(const file_name[],key[],position,Float:value,k_len=sizeof(key));                                                *
 * SWAP::read_byte(const file_name[],key[],position,k_len=sizeof(key));                                                              *
 * SWAP::write_byte(const file_name[],key[],position,value,k_len=sizeof(key));                                                       *
 *                                                                                                                                   *
 *************************************************************************************************************************************/

#if defined _SWAP_include
	#endinput
#endif
#define _SWAP_include

#define SWAP::									SWAP_

#define SWAP_WRITE								0
#define SWAP_READ								1

#define SWAP_ExtractValue(%0,%1,%2,%3,%4)		((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define SWAP_ExtractFloat(%0,%1,%2,%3,%4)		((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define SWAP_MergeValueEx(%1,%2,%3,%4)			(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4))
#define SWAP_MergeFloatEx(%1,%2,%3,%4)			(Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

stock SWAP::create_empty(const file_name[]){
	if(fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	fwrite(outf,"");
	fclose(outf);
	return 1;
}

stock SWAP::create_block(const file_name[],size){
	if(size <= 0 || !fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_append);
	if(!outf) return 0;
	new asize = flength(outf);
	for(new i = 0; i < size; i++){
		fputchar(outf,random(256),false);
	}
	fclose(outf);
	return asize;
}

stock SWAP::reserve(const file_name[],size){
	if(fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	fseek(outf,size-1,seek_start);
	fputchar(outf,0,false);
	fclose(outf);
	return 1;
}

stock SWAP::format(const file_name[],key[],k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite), step, len = flength(outf);
	for(new i = 0; i < len; i++){
		fputchar(outf,((key[step++ % k_len]) & 0xFF),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::format_random(const file_name[]){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite), len = flength(outf);
	for(new i = 0; i < len; i++){
		fputchar(outf,random(256),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::decrypt_file(const input[],const output[],key[],k_len=sizeof(key)){
	if(!fexist(input)) return 0;
	if(fexist(output)) return 0;
	new File:inpf = fopen(input,io_read), step, len = flength(inpf);
	SWAP::reserve(output,len);
	new File:outf = fopen(output,io_readwrite);
	if(!outf) return 0;
	for(new i = 0; i < len; i++){
		fputchar(outf,((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),false);
	}
	fclose(inpf);
	fclose(outf);
	return 1;
}

stock SWAP::read_string(const file_name[],key[],position,text[],len,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:inpf = fopen(file_name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len);
	for(new i = 0; i < len; i++){
		text[i] = (fgetchar(inpf,0,false) + key[step++ % k_len]) & 0xFF;
	}
	fclose(inpf);
	return 1;
}

stock SWAP::write_string(const file_name[],key[],position,text[],max_dest=sizeof(text),k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), len = strlen(text);
	for(new i = 0; i < len; i++){
		fputchar(outf,((text[i]+key[step++ % k_len]) & 0xFF),false);
	}
	if(len < max_dest){
		fputchar(outf,(key[step++ % k_len]),false);
	}
	for(new i = len+1; i < max_dest; i++){
		fputchar(outf,((random(256) + key[step++ % k_len]) & 0xFF),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::write_block(const file_name[],key[],position,text[],max_dest=sizeof(text),k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len);
	for(new i = 0; i < max_dest; i++){
		fputchar(outf,((text[i]+key[step++ % k_len]) & 0xFF),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::read_array(const file_name[],key[],position,array[],len,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:inpf = fopen(file_name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len);
	for(new i = 0; i < len; i++){
		array[i] = SWAP::MergeValueEx(((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF));
	}
	fclose(inpf);
	return 1;
}

stock SWAP::write_array(const file_name[],key[],position,array[],max_dest=sizeof(array),k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), int1, int2, int3, int4;
	for(new i = 0; i < max_dest; i++){
		SWAP::ExtractValue(array[i],int1,int2,int3,int4);
		fputchar(outf,((int1+key[step++ % k_len]) & 0xFF),false);
		fputchar(outf,((int2+key[step++ % k_len]) & 0xFF),false);
		fputchar(outf,((int3+key[step++ % k_len]) & 0xFF),false);
		fputchar(outf,((int4+key[step++ % k_len]) & 0xFF),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::read_int(const file_name[],key[],position,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:inpf = fopen(file_name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len), value = SWAP::MergeValueEx(((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF));
	fclose(inpf);
	return value;
}

stock SWAP::write_int(const file_name[],key[],position,value,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), int1, int2, int3, int4;
	SWAP::ExtractValue(value,int1,int2,int3,int4);
	fputchar(outf,((int1+key[step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int2+key[step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int3+key[step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int4+key[step++ % k_len]) & 0xFF),false);
	fclose(outf);
	return 1;
}

stock SWAP::read_byte(const file_name[],key[],position,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:inpf = fopen(file_name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len), value = ((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF);
	fclose(inpf);
	return value;
}

stock SWAP::write_byte(const file_name[],key[],position,value,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len);
	fputchar(outf,((value+key[step++ % k_len]) & 0xFF),false);
	fclose(outf);
	return 1;
}

stock Float:SWAP::read_float(const file_name[],key[],position,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0.0;
	new File:inpf = fopen(file_name,io_read);
	if(!inpf) return 0.0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len), Float:value = SWAP::MergeFloatEx(((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[step++ % k_len]) & 0xFF));
	fclose(inpf);
	return value;
}

stock SWAP::write_float(const file_name[],key[],position,Float:value,k_len=sizeof(key)){
	if(!fexist(file_name)) return 0;
	new File:outf = fopen(file_name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), int1, int2, int3, int4;
	SWAP::ExtractFloat(value,int1,int2,int3,int4);
	fputchar(outf,((int1+key[step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int2+key[step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int3+key[step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int4+key[step++ % k_len]) & 0xFF),false);
	fclose(outf);
	return 1;
}
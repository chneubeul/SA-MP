/*********************
 * Chunk System v1.0 *
 *********************/

#define INVALID_CHUNK_ID -1

enum e_chunks {
	Float:sW,
	Float:sC
}

new Chunk[e_chunks];

//sizeW 40000.0 => point minx = -20000.0, maxx = 20000.0 and miny = -20000.0, maxy = 20000.0
stock SetChunkPolygon(Float:sizeW = 40000.0,Float:sizeC = 1000.0){
	Chunk[sW] = sizeW;
	Chunk[sC] = sizeC;
}

stock GetChunkID(Float:x,Float:y){
	if(Chunk[sW] == 0.0 || Chunk[sC] == 0.0) SetChunkPolygon();
	if((x+(Chunk[sW]/2)) < 0 || (y+(Chunk[sW]/2)) < 0) return INVALID_CHUNK_ID;
	return floatround((((x+(Chunk[sW]/2))/Chunk[sC])+((Chunk[sW]/Chunk[sC])*((y+(Chunk[sW]/2))/Chunk[sC]))));
}

stock IsPointInChunk(chunkid,Float:x,Float:y){
	if(Chunk[sW] == 0.0 || Chunk[sC] == 0.0) SetChunkPolygon();
	if((GetChunkID(x,y) == chunkid) && (GetChunkID(x,y) != INVALID_CHUNK_ID)) return true;
	return false;
}
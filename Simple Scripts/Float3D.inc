/*
#include <a_samp>
#include <SAM/3DTryg>
*/

main(){
	new tmp[Vectors3D];
	
	tmp[T3D:X] = 0.0;
	tmp[T3D:Y] = 0.0;
	tmp[T3D:Z] = 0.0;
	tmp[T3D:A] = 0.0;

	GetPlayerPos(0,tmp[T3D:X],tmp[T3D:Y],tmp[T3D:Z]);
	
	new var[Float3D];
	
	var[T3D:X] = 0.0;
	var[T3D:Y] = 0.0;
	var[T3D:Z] = 0.0;
	var[T3D:rX] = 0.0;
	var[T3D:rY] = 0.0;
	var[T3D:rZ] = 0.0;

	var[T3D:tX] = 0.0;
	var[T3D:tY] = 0.0;
	var[T3D:tZ] = 0.0;

	var[T3D:VW] = 0;
	var[T3D:INT] = 0;
	var[T3D:SPEED] = 0.0;
}
/*
#include <a_samp>
#include <SAM/3DTryg>
*/

main(){
	new tmp[Vectors3D];
	
	GetPlayerPos(0,tmp[T3D:X],tmp[T3D:Y],tmp[T3D:Z]);
	tmp[T3D:A] = 45.0;
	
	new var[Float3D];
	
	var[T3D:X] = 54.0;
	var[T3D:Y] = -5.0;
	var[T3D:Z] = -109.0;
	var[T3D:rX] = 97.0;
	var[T3D:rY] = 46.0;
	var[T3D:rZ] = 15.0;

	var[T3D:tX] = 97.0;
	var[T3D:tY] = 15.0;
	var[T3D:tZ] = 1.0;

	var[T3D:VW] = 9;
	var[T3D:INT] = 0;
	var[T3D:SPEED] = 70.0;
}
/*
#include <SAM/3DTryg>
*/

//you need vx,vy,vz (weapon offset) 
CreateActorWeapon(actorid,objectid,Float:vx,Float:vy,Float:vz){ 
    new Float:x,Float:y,Float:z, 
        Float:tx,Float:ty,Float:tz 
        Float:rx,Float:rz,Float:angle; 

    GetActorPos(actorid,x,y,z); 
    GetActorFacingAngle(actorid,angle); 
     
    ShiftVectorToRotation(vx,vy,vz,rx,rz); 
    GetPointInFront3D(x,y,z,rx,CompRotationFloat(angle+rz),VectorSize(vx,vy,vz),tx,ty,tz); 

    CreateDynamicObject(objectid,tx,ty,tz,80.0,0.0,0.0,-1); 
}  
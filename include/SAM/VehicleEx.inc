/****************************************************************************************************
 *                                                                                                  *
 * Vehicle Update v1.0 made by Abyss Morgan                                                         *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 *                                                                                                  *
 * Functions:                                                                                       *
 * GetVehiclePanels(vehicleid,&front_bumper,&rear_bumper);                                          *
 * SetVehiclePanels(vehicleid,flp,frp,rlp,rrp,windshield,front_bumper,rear_bumper);                 *
 * GetVehicleLights(vehicleid,&light1,&light2,&light3,&light4);                                     *
 * SetVehicleLights(vehicleid,light1,light2,light3,light4);                                         *
 * GetVehicleDoors(vehicleid,&bonnet,&boot,&driver_door,&passenger_door);                           *
 * SetVehicleDoors(vehicleid,bonnet,boot,driver_door,passenger_door);                               *
 * GetVehicleTires(vehicleid,&tire1,&tire2,&tire3,&tire4);                                          *
 * SetVehicleTires(vehicleid,tire1,tire2,tire3,tire4);                                              *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _Vehicle_Ex
	#endinput
#endif
#define _Vehicle_Ex

stock GetVehiclePanels(vehicleid, &front_bumper, &rear_bumper){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	front_bumper = (panels >> 20) & 0xF;
	rear_bumper = (panels >> 24) & 0xF;
}

stock SetVehiclePanels(vehicleid, flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	panels = (flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24));
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

stock GetVehicleLights(vehicleid, &light1, &light2, &light3, &light4){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	light1 = lights & 0x1;
	light2 = lights >> 1 & 0x1;
	light3 = lights >> 2 & 0x1;
	light4 = lights >> 3 & 0x1;
}

stock SetVehicleLights(vehicleid, light1, light2, light3, light4){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	lights = (light1 | (light2 << 1) | (light3 << 2) | (light4 << 3));
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

stock GetVehicleDoors(vehicleid, &bonnet, &boot, &driver_door, &passenger_door){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	bonnet = (doors & 0x7);
	boot = ((doors >> 8) & 0x7);
	driver_door = ((doors >> 16) & 0x7);
	passenger_door = ((doors >> 24) & 0x7);
}

stock SetVehicleDoors(vehicleid, bonnet, boot, driver_door, passenger_door){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	doors = (bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24));
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

stock GetVehicleTires(vehicleid, &tire1, &tire2, &tire3, &tire4){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	tire1 = tires & 1;
	tire2 = tires >> 1 & 1;
	tire3 = tires >> 2 & 1;
	tire4 = tires >> 3 & 1;
}

stock SetVehicleTires(vehicleid, tire1, tire2, tire3, tire4){
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	tires = (tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3));
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
}

//EOF
/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                   Vehicle Extended Functions                                                   *
 *                                                                                                                                *
 * Copyright © 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                         *
 *                                                                                                                                *
 * Plugins: None                                                                                                                  *
 * Modules: None                                                                                                                  *
 *                                                                                                                                *
 * File Version: 1.1                                                                                                              *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * GetVehiclePanels(vehicleid,&front_left,&front_right,&rear_left,&rear_right,&windshield,&front_bumper,&rear_bumper);            *
 * SetVehiclePanels(vehicleid,front_left,front_right,rear_left,rear_right,windshield,front_bumper,rear_bumper);                   *
 * GetVehicleLights(vehicleid,&light1,&light2,&light3,&light4);                                                                   *
 * SetVehicleLights(vehicleid,light1,light2,light3,light4);                                                                       *
 * GetVehicleDoors(vehicleid,&bonnet,&boot,&driver_door,&passenger_door);                                                         *
 * SetVehicleDoors(vehicleid,bonnet,boot,driver_door,passenger_door);                                                             *
 * GetVehicleTires(vehicleid,&front_left,&front_right,&rear_left,&rear_right);                                                    *
 * SetVehicleTires(vehicleid,front_left,front_right,rear_left,rear_right);                                                        *
 * SwitchVehicleLight(vehicleid,bool:light);                                                                                      *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if defined _Vehicle_Ex
	#endinput
#endif
#define _Vehicle_Ex

#define BONNET_HEALTHY_CLOSED		0
#define BONNET_HEALTHY_OPENED		1
#define BONNET_DAMAGED_CLOSED		2
#define BONNET_DAMAGED_OPENED		3
#define BONNET_MISSING				4

#define BOOT_HEALTHY_CLOSED			0
#define BOOT_HEALTHY_OPENED			1
#define BOOT_DAMAGED_CLOSED			2
#define BOOT_DAMAGED_OPENED			3
#define BOOT_MISSING				4

#define DOOR_HEALTHY_CLOSED			0
#define DOOR_HEALTHY_OPENED			1
#define DOOR_DAMAGED_CLOSED			2
#define DOOR_DAMAGED_OPENED			3
#define DOOR_MISSING				4

#define BUMPER_HEALTHY				0
#define BUMPER_CRUSHED				1
#define BUMPER_HANGING				2
#define BUMPER_MISSING				3

#define WINDSHIELD_HEALTHY			0
#define WINDSHIELD_DAMAGED			1
#define WINDSHIELD_MISSING			2

#define LIGHT_ENABLE				0
#define LIGHT_DISABLE				1

#define TIRE_HEALTHY				0
#define TIRE_DAMAGED				1

stock GetVehiclePanels(vehicleid,&front_left,&front_right,&rear_left,&rear_right,&windshield,&front_bumper,&rear_bumper){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	front_left = (panels & 0xF);
	front_right = (panels >> 4) & 0xF;
	rear_left = (panels >> 8) & 0xF;
	rear_right = (panels >> 12) & 0xF;
	windshield = (panels >> 16) & 0xF;
	front_bumper = (panels >> 20) & 0xF;
	rear_bumper = (panels >> 24) & 0xF;
}

stock SetVehiclePanels(vehicleid,front_left,front_right,rear_left,rear_right,windshield,front_bumper,rear_bumper){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	panels = (front_left | (front_right << 4) | (rear_left << 8) | (rear_right << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24));
	UpdateVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
}

stock GetVehicleLights(vehicleid,&light1,&light2,&light3,&light4){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	light1 = (lights & 0x1);
	light2 = (lights >> 1 & 0x1);
	light3 = (lights >> 2 & 0x1);
	light4 = (lights >> 3 & 0x1);
}

stock SetVehicleLights(vehicleid,light1,light2,light3,light4){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	lights = (light1 | (light2 << 1) | (light3 << 2) | (light4 << 3));
	UpdateVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
}

stock GetVehicleDoors(vehicleid,&bonnet,&boot,&driver_door,&passenger_door){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	bonnet = (doors & 0x7);
	boot = ((doors >> 8) & 0x7);
	driver_door = ((doors >> 16) & 0x7);
	passenger_door = ((doors >> 24) & 0x7);
}

stock SetVehicleDoors(vehicleid,bonnet,boot,driver_door,passenger_door){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	doors = (bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24));
	UpdateVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
}

stock GetVehicleTires(vehicleid,&front_left,&front_right,&rear_left,&rear_right){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	rear_right = (tires & 0x1);
	front_right = (tires >> 1 & 0x1);
	rear_left = (tires >> 2 & 0x1);
	front_left = (tires >> 3 & 0x1);
}

stock SetVehicleTires(vehicleid,front_left,front_right,rear_left,rear_right){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	tires = (rear_right | (front_right << 1) | (rear_left << 2) | (front_left << 3));
	UpdateVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
}

stock SwitchVehicleLight(vehicleid,bool:light){
	new panels,doors,lights,tires;
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
	if(light){
		lights = 0x0;
	} else {
		lights = 0xF;
	}
	UpdateVehicleDamageStatus(vehicleid,panels,doors,lights,tires);
}

//EOF
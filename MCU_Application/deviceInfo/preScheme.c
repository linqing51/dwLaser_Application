#include "preScheme.h"
/*****************************************************************************/	
void mySchemeInit(void){
	myScheme_t *p;
	/***************************************************************************/
	//Phlebology
	//1470nm, CW 8w 80J/cm
	p = &schemePhlebology[0];
	p->name = Phlebology_0;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm, CW 6w 60J/cm
	p = &schemePhlebology[1];
	p->name = Phlebology_1;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 60;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm, CW 3w 30J/cm
	p = &schemePhlebology[2];
	p->name = Phlebology_2;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 60;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	/***************************************************************************/
	//
	//1470nm, CW 6w, 250 Joules per hemorrhoid
	p = &schemeProctology[0];
	p->name = Proctology_0;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 60;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm, CW 7w, 350 Joules per hemorrhoid
	p = &schemeProctology[1];
	p->name = Proctology_1;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 70;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 8w, 350 Joules per hemorrhoid
	p = &schemeProctology[2];
	p->name = Proctology_2;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	//1470nm, CW 10w 100J/cm
	p = &schemeProctology[3];
	p->name = Proctology_3;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 

	//1470nm, CW 10w 100J/cm
	p = &schemeProctology[4];
	p->name = Proctology_4;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	//1470nm, CW 7w 100J/cm
	p = &schemeProctology[5];
	p->name = Proctology_5;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 70;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	//1470nm, Pulse 6w 500ms Ton, 500ms Toff
	p = &schemeCosmoGynecology[0]
	p->name = CosmoGynecology_0;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 60;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 500;
	p->negwidth = 500; 	
	
	//1470nm, Pulse 7w 500ms Ton, 500ms Toff
	p = &schemeCosmoGynecology[1]
	p->name = CosmoGynecology_1;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 70;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	p = &schemeCosmoGynecology[2]
	p->name = CosmoGynecology_2;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	p = &schemeCosmoGynecology[3]
	p->name = CosmoGynecology_3;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	//1470nm, CW 6w 15s Ton
	p = &schemeCosmoGynecology[4]
	p->name = CosmoGynecology_4;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 60;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 10w 15s Ton
	p = &schemeCosmoGynecology[5]
	p->name = CosmoGynecology_5;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 15000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 5w
	p = &schemeCosmoGynecology[6]
	p->name = CosmoGynecology_6;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	//1470nm, CW 5w
	p = &schemeCosmoGynecology[7]
	p->name = CosmoGynecology_7;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 50;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 8w
	p = &schemeCosmoGynecology[8]
	p->name = CosmoGynecology_8;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	//1470nm 12w CW
	p = &schemeGynecologyHysteroscopy[0]
	p->name = GynecologyHysteroscopy_0;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 120;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 8w CW
	p = &schemeGynecologyHysteroscopy[1]
	p->name = GynecologyHysteroscopy_1;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	//1470nm 10w CW
	p = &schemeGynecologyHysteroscopy[2]
	p->name = GynecologyHysteroscopy_2;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 10w CW
	p = &schemeGynecologyHysteroscopy[3]
	p->name = GynecologyHysteroscopy_3;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &schemeGynecologyHysteroscopy[4]
	p->name = GynecologyHysteroscopy_4;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 120;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &schemeGynecologyHysteroscopy[5]
	p->name = GynecologyHysteroscopy_5;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 120;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &schemeGynecologyHysteroscopy[6]
	p->name = GynecologyHysteroscopy_6;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 120;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &schemeGynecologyLaparoscopy[0]
	p->name = GynecologyLaparoscopy_0;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 120;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//1470nm 10w CW
	p = &schemeGynecologyLaparoscopy[1]
	p->name = GynecologyLaparoscopy_1;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &schemeGynecologyLaparoscopy[2]
	p->name = GynecologyLaparoscopy_2;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &schemeGynecologyLaparoscopy[3]
	p->name = GynecologyLaparoscopy_3;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &schemeGynecologyLaparoscopy[4]
	p->name = GynecologyLaparoscopy_4;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	//1470nm 10w CW
	p = &schemeGynecologyLaparoscopy[5]
	p->name = GynecologyLaparoscopy_5;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//1470nm, Pulse 7w 1s Ton, 5s Toff
	p = &schemeNeurosurgery[0]
	p->name = Neurosurgery_0;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 70;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 7000;

	//1470nm, Pulse 7w 1s Ton, 5s Toff
	p = &schemeNeurosurgery[1]
	p->name = Neurosurgery_1;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 70;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	//1470nm, Pulse 7w, 1s Ton, 5s Toff
	p = &schemeNeurosurgery[2]
	p->name = Neurosurgery_2;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 70;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;	

	//980m, Pulse 8w 1s Ton, 5s Toff
	p = &schemeNeurosurgery[3]
	p->name = Neurosurgery_3;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 1;
	p->power_980 = 80;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	//980nm 13w CW
	p = &schemeENT[0]
	p->name = ENT_0;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 130;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//980nm 12w CW
	p = &schemeENT[1]
	p->name = ENT_1;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 120;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &schemeENT[2]
	p->name = ENT_2;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 140;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &schemeENT[3]
	p->name = ENT_3;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 140;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &schemeENT[4]
	p->name = ENT_4;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 140;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &schemeENT[5]
	p->name = ENT_5;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 140;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &schemeENT[6]
	p->name = ENT_6;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 130;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &schemeENT[7]
	p->name = ENT_7;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 130;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 10w CW
	p = &schemeENT[8]
	p->name = ENT_8;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 100;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &schemeENT[9]
	p->name = ENT_9;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 130;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &schemeENT[10]
	p->name = ENT_10;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 130;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 10w CW
	p = &schemeENT[11]
	p->name = ENT_11;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 100;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &schemeENT[12]
	p->name = ENT_12;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 130;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 10w Pulse, 50ms Ton, 90ms Toff 
	p = &schemeENT[13]
	p->name = ENT_13;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 1;
	p->power_980 = 100;
	p->power_635 = 1;
	p->poswidth = 50;
	p->negwidth = 90;
	
	//980nm 10w CW
	p = &schemeENT[14]
	p->name = ENT_14;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 100;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 12w CW
	p = &schemeENT[15]
	p->name = ENT_15;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 120;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	//980nm, CW 10W
	p = &schemeDermatology[0]
	p->name = Dermatology_0;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 100;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm, CW 6w
	p = &schemeDermatology[1]
	p->name = Dermatology_1;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 60;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	//980nm, CW 8w
	p = &schemeDermatology[2]
	p->name = Dermatology_2;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 80;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm, CW 10w
	p = &schemeDermatology[3]
	p->name = Dermatology_3;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 1;
	p->power_980 = 100;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

//980nm, Pulse, 6w, 1s Ton, 1s Toff
	p = &schemeDermatology[4]
	p->name = Dermatology_4;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 1;
	p->power_980 = 60;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	p = &schemeDermatology[5]
	p->name = Dermatology_5;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 1;
	p->power_980 = 80;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	p = &schemeDermatology[6]
	p->name = Dermatology_6;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 1;
	p->power_980 = 80;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;

	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	p = &schemeDermatology[7]
	p->name = Dermatology_7;
	p->channel = LASER_CHANNEL_980;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_1480 = 1;
	p->power_980 = 80;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;

	//1470nm, 3w CW
	p = &schemeLiposuction[0]
	p->name = Liposuction_0;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 30;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//1470nm 6w CW
	p = &schemeLiposuction[1]
	p->name = Liposuction_1;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 60;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 8w CW
	p = &schemeLiposuction[2]
	p->name = Liposuction_2;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 12 CW
	p = &schemeLiposuction[3]
	p->name = Liposuction_3;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 120;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &schemeLiposuction[4]
	p->name = Liposuction_4;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 100;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 8w CW
	p = &schemeLiposuction[5]
	p->name = Liposuction_5;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 8w CW
	p = &schemeLiposuction[6]
	p->name = Liposuction_6;
	p->channel = LASER_CHANNEL_1470;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_1480 = 80;
	p->power_980 = 1;
	p->power_635 = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
//980nm 8w pulse, 50ms on, 50ms off
//980nm 8w pulse 50ms on, 50ms off
//980nm 10w pulse 50ms on, 50ms off
//980nm 6w pulse 50ms on, 50ms off
//980nm 6w pulse 50ms on, 50ms off
//635nm CW
//635nm CW
//635nm CW







}

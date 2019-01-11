// MakeRelations.cpp: implementation of the MakeRelations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "MakeRelations.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void MakeRelations::build()
{
	Rels = new FzyRelation *[20];
//
//
//------------------------------------------------------------
//	Maximum Vehicle speed
	Rels[0] = new FzyRelation(-10,75,"Maxspeed");
	Rels[0]->MakeMemb(-5,-5,0,"BACK");
	Rels[0]->MakeMemb(-5,0,5,"STOP");
	Rels[0]->MakeMemb(0,5,10,"Vslow");//SPEEDlow			0
	Rels[0]->MakeMemb(5,10,20,"slow");//SPEEDmedium			1
	Rels[0]->MakeMemb(10,20,50,"med");//SPEEDhigh			2
	Rels[0]->MakeMemb(20,50,75,"fast");
	Rels[0]->MakeMemb(50,75,75,"vfast");
	//
	Rels[0]->MakeHedge(-5,0,5,"HALT");//HEDGE
//------------------------------------------------------------
//	Final Vehicle speed
	Rels[1] = new FzyRelation(-10,75,"speed");
	Rels[1]->MakeMemb(-5,-5,0,"BACK");
	Rels[1]->MakeMemb(-5,0,5,"STOP");
	Rels[1]->MakeMemb(0,5,10,"Vslow");//SPEEDlow			0
	Rels[1]->MakeMemb(5,10,20,"slow");//SPEEDmedium			1
	Rels[1]->MakeMemb(10,20,50,"med");//SPEEDhigh			2
	Rels[1]->MakeMemb(20,50,75,"fast");
	Rels[1]->MakeMemb(50,75,75,"vfast");
	//
	Rels[1]->MakeHedge(-5,0,5,"HALT");//HEDGE
//------------------------------------------------------------
//
//	Rels[2] = new FzyRelation(-100,100,"BrakeRate");
//	Rels[2]->MakeMemb(-50,-25,0,"Slight");//BRAKINGslight	0
//	Rels[2]->MakeMemb(0,25,75,"Gentle");//BRAKINGgentle		1
//	Rels[2]->MakeMemb(50,75,100,"Hard");//BRAKINGhard		2
//	//
//	Rels[2]->MakeHedge(-1,0,1,"Zeroing");//HEDGE
//------------------------------------------------------------
//	Left wheel speed
	Rels[3] = new FzyRelation(-20,100,"L_Drive");
	Rels[3]->MakeMemb(-20,-5,0,"Back");
	Rels[3]->MakeMemb(-5,0,5,"Stop");
	Rels[3]->MakeMemb(0,5,10,"VSlow");
	Rels[3]->MakeMemb(5,10,25,"Slow");
	Rels[3]->MakeMemb(10,25,50,"Med");
	Rels[3]->MakeMemb(25,50,100,"fast");
	Rels[3]->MakeMemb(50,100,100,"Vfast");

	//
	Rels[3]->MakeHedge(-5,0,5,"HALT");
//------------------------------------------------------------
//	Right wheel speed
	Rels[4] = new FzyRelation(-20,100,"R_Drive");
	Rels[4]->MakeMemb(-20,-5,0,"Back");
	Rels[4]->MakeMemb(-5,0,5,"Stop");
	Rels[4]->MakeMemb(0,5,10,"VSlow");
	Rels[4]->MakeMemb(5,10,25,"Slow");
	Rels[4]->MakeMemb(10,25,50,"Med");
	Rels[4]->MakeMemb(25,50,100,"fast");
	Rels[4]->MakeMemb(50,100,100,"Vfast");
	//
	Rels[4]->MakeHedge(-5,0,5,"HALT");
//------------------------------------------------------------
//	Direction error
	Rels[5] = new FzyRelation(-50,50,"Dir_error");
	Rels[5]->MakeMemb(10,50,50,"LeftMax");
	Rels[5]->MakeMemb(0,10,50,"Left");
	Rels[5]->MakeMemb(-10,0,10,"Streight");
	Rels[5]->MakeMemb(-50,-10,0,"Right");
	Rels[5]->MakeMemb(-50,-50,-10,"RightMax");
	//
//INPUT	Rels[5]->MakeHedge(-1,0,1,"NONE");
//------------------------------------------------------------
//	Target follow
	Rels[6] = new FzyRelation(-50,50,"Target follow");
	Rels[6]->MakeMemb(15,50,50,"Left");
	Rels[6]->MakeMemb(0,15,50,"Leftish");
	Rels[6]->MakeMemb(-15,0,15,"Streight");
	Rels[6]->MakeMemb(-50,-15,0,"Rightish");
	Rels[6]->MakeMemb(-50,-50,-15,"Right");
	//
	Rels[6]->MakeHedge(-5,0,5,"STREIGHT");
//------------------------------------------------------------
//	Distance to target
	Rels[7] = new FzyRelation(0,100,"Dist_targ");
	Rels[7]->MakeMemb(0,0,5,"close");
	Rels[7]->MakeMemb(0,5,15,"near");
	Rels[7]->MakeMemb(5,15,50,"distant");
	Rels[7]->MakeMemb(25,50,100,"far");
	Rels[7]->MakeMemb(50,100,100,"Vfar");
	//
//INPUT
//------------------------------------------------------------
//	Forward Obstacle proximity
	Rels[8] = new FzyRelation(0,100,"ObsDist");
	Rels[8]->MakeMemb(0,0,10,"Vclose");
	Rels[8]->MakeMemb(0,10,20,"close");
	Rels[8]->MakeMemb(10,20,60,"med");
	Rels[8]->MakeMemb(20,60,100,"far");
	Rels[8]->MakeMemb(60,100,100,"Vfar");
	//
//INPUT	Rels[8]->MakeHedge(0,5,10,"NOobst");	//HEDGE indicates no obstacle detected
//------------------------------------------------------------
//	Belief from fuzzy map in presence of a clear space
	Rels[9] = new FzyRelation(0,100,"BelieveC");
	Rels[9]->MakeMemb(0,0,50,"No");
	Rels[9]->MakeMemb(0,50,100,"Mid");
	Rels[9]->MakeMemb(50,100,100,"Yes");
	//
//INPUT	Rels[9]->MakeHedge(0,1,2,"???");	//HEDGE 
//------------------------------------------------------------
//	Belief from fuzzy map in the presence of a wall
	Rels[10] = new FzyRelation(0,100,"BelieveW");
	Rels[10]->MakeMemb(0,0,50,"No");
	Rels[10]->MakeMemb(0,50,100,"Mid");
	Rels[10]->MakeMemb(50,100,100,"Yes");
	//
//INPUT	Rels[10]->MakeHedge(0,1,2,"???");	//HEDGE 
//------------------------------------------------------------
//	Gray scale change in respose to fuzzy map evaluation
	Rels[11] = new FzyRelation(-10,+10,"GrayChange");
	Rels[11]->MakeMemb(-10,-10,0,"No");
	Rels[11]->MakeMemb(-10,0,10,"Mid");
	Rels[11]->MakeMemb(0,10,10,"Yes");
	//
	Rels[11]->MakeHedge(-1,0,1,"???");	//HEDGE 
//------------------------------------------------------------
//	Left obstacle proximity
	Rels[12] = new FzyRelation(0,100,"LeftDis");
	Rels[12]->MakeMemb(0,0,5,"Lclose");
	Rels[12]->MakeMemb(0,5,10,"Lnear");
	Rels[12]->MakeMemb(5,10,60,"Ldist");
	Rels[12]->MakeMemb(10,60,100,"Lfar");
	Rels[12]->MakeMemb(60,100,100,"LVfar");
	//Input only No Hedge
	//Rels[12]->MakeHedge(90,95,100,"???");	//HEDGE 
//------------------------------------------------------------
//	Right obstacle proximity
	Rels[13] = new FzyRelation(0,100,"RightDis");
	Rels[13]->MakeMemb(0,0,5,"Rclose");
	Rels[13]->MakeMemb(0,5,10,"Rnear");
	Rels[13]->MakeMemb(5,10,60,"Rdist");
	Rels[13]->MakeMemb(10,60,100,"Rfar");
	Rels[13]->MakeMemb(60,100,100,"RVfar");
	//Input only no hedge
	//Rels[13]->MakeHedge(90,95,100,"???");	//HEDGE 
//------------------------------------------------------------
//	Min distance Avoidance behaviour
	Rels[14] = new FzyRelation(-50,50,"Obst_Min");
	Rels[14]->MakeMemb(15,50,50,"Left");
	Rels[14]->MakeMemb(0,15,50,"Leftish");
	Rels[14]->MakeMemb(-15,0,15,"Streight");
	Rels[14]->MakeMemb(-50,-15,0,"Rightish");
	Rels[14]->MakeMemb(-50,-50,-15,"Right");
	//
	Rels[14]->MakeHedge(-5,0,5,"STREIGHT");
//------------------------------------------------------------
//	Stearing angle
	Rels[15] = new FzyRelation(-50,50,"Stearing angle");
	Rels[15]->MakeMemb(15,50,50,"Left");
	Rels[15]->MakeMemb(0,15,50,"Leftish");
	Rels[15]->MakeMemb(-15,0,15,"Streight");
	Rels[15]->MakeMemb(-50,-15,0,"Rightish");
	Rels[15]->MakeMemb(-50,-50,-15,"Right");
	//
	Rels[15]->MakeHedge(-5,0,5,"STREIGHT");
//------------------------------------------------------------
//	Averaging Obstacle Avoidance behaviour
	Rels[16] = new FzyRelation(-50,50,"Obst_Ave");
	Rels[16]->MakeMemb(25,50,50,"Left");
	Rels[16]->MakeMemb(0,25,50,"Leftish");
	Rels[16]->MakeMemb(-25,0,25,"Streight");
	Rels[16]->MakeMemb(-50,-25,0,"Rightish");
	Rels[16]->MakeMemb(-50,-50,-25,"Right");
	//
	Rels[16]->MakeHedge(-5,0,5,"STREIGHT");
//------------------------------------------------------------
//	Obstacle Avoidance behaviour
	Rels[17] = new FzyRelation(-50,50,"Obst_Avod");
	Rels[17]->MakeMemb(15,50,50,"Left");
	Rels[17]->MakeMemb(0,15,50,"Leftish");
	Rels[17]->MakeMemb(-15,0,15,"Streight");
	Rels[17]->MakeMemb(-50,-15,0,"Rightish");
	Rels[17]->MakeMemb(-50,-50,-15,"Right");
	//
	Rels[17]->MakeHedge(-5,0,5,"STREIGHT");
//------------------------------------------------------------
//	Speed restriction due to error in target direction
	Rels[18] = new FzyRelation(-10,75,"Fin_speed");
	Rels[18]->MakeMemb(-5,-5,0,"BACK");
	Rels[18]->MakeMemb(-5,0,5,"STOP");
	Rels[18]->MakeMemb(0,5,10,"Vslow");//SPEEDlow			0
	Rels[18]->MakeMemb(5,10,20,"slow");//SPEEDmedium			1
	Rels[18]->MakeMemb(10,20,50,"med");//SPEEDhigh			2
	Rels[18]->MakeMemb(20,50,75,"fast");
	Rels[18]->MakeMemb(50,75,75,"vfast");
	//
	Rels[18]->MakeHedge(-5,0,5,"HALT");//HEDGE
//------------------------------------------------------------
//
/*	Rels[] = new FzyRelation(,,"");
	Rels[]->MakeMemb(,,,"");
	Rels[]->MakeMemb(,,,"");
	Rels[]->MakeMemb(,,,"");
	//
	Rels[]->MakeHedge(,,,"");	//HEDGE 
//------------------------------------------------------------
*/
}

MakeRelations::MakeRelations()
{

}



MakeRelations::~MakeRelations()
{

}

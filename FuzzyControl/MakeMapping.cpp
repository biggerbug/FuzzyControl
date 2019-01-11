// MakeMapping.cpp: implementation of the MakeMapping class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "MakeMapping.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SPEED_DISTANCE_braking	0
#define TRACK_STEAR_reaction	1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void MakeMappings::build()
{
	Mats = new Matrix *[10];
//------------------------------------------------------------//
//	Output	'Steering control'
//	0		1		2			3			4			5
//	NULL	LEFT	LEFTish		Streight	RIGHTish	RIGHT
//
	int LocA[] =
	{	1,1,1,2,2,
		1,1,2,4,4,
		1,2,3,4,5,
		2,2,4,5,5,
		4,4,5,5,5	};
//													TURNleft	Relation'1'
//													TURNleftish	`Obstacle avoid`
//													EVEN
//													TURNrightish
//													TURNright
//	Tleft	Tleftish	Tstreight	Trightish	Tright
//	`Target direction`
//	Relation '0'
	Mats[0] = new Matrix;
	Mats[0]->Build(5,5,LocA);
//------------------------------------------------------------//
//	Output	'Vehicle speed'
//	0		1		2		3		4		5		6		7
//	NULL	BACK	STOP	vslow	slow	med		fast	vfast
//
	int LocB[]=
	{	1,1,1,1,1,
		2,2,2,2,2,
		3,3,3,3,3,
		3,4,4,4,4,
		3,4,5,5,5,
		3,4,5,6,6,
		3,4,5,7,7	};
//												BACK	Relation'1'
//												STOP	Maximum vehicle speed
//												vslow
//												slow
//												med
//												fast
//												Vfast
//	close	near	distant		far		Vfar
//	Target distance
//	Relation '0'
	Mats[1] = new Matrix;
	Mats[1]->Build(5,7,LocB);
//------------------------------------------------------------//
//	Output	'Target following behaviour'
//	0		1			2			3		4			5
//	NULL	Left	leftish		streight	Rightish	right

	int LocC[]=
	{	1,1,3,5,5,
		1,2,3,4,5,
		1,2,3,4,5,
		1,2,3,4,5,
		1,2,3,4,5	};
//												close	Relation'1'
//												near	Distance to target
//												distant
//												far
//												Vfar
//	leftmax	left	streight	right	rightmax
//	direction error
//	Relation '0'
	Mats[2] = new Matrix;
	Mats[2]->Build(5,5,LocC);
//------------------------------------------------------------//
//	Output	'Left wheel speed'
//	0		1		2		3		4		5		6		7
//	NULL	Back	stop	Vslow	slow	Med		fast	Vfast

	int LocD[]=
	{	1,	1,	1,	2,	2,
		1,	1,	3,	3,	3,
		1,	2,	3,	3,	3,
		2,	3,	4,	4,	4,
		3,	4,	5,	5,	5,
		4,	5,	6,	6,	6,
		5,	6,	7,	7,	7	};
//												BACK
//												STOP
//												vslow	Relation'1'
//												slow	vehicle speed
//												med
//												fast
//												Vfast
//	leftmax	left	streight	right	rightmax
//	stearing direction

//	Relation '0'
	Mats[3] = new Matrix;
	Mats[3]->Build(5,7,LocD);
//------------------------------------------------------------//

//	Output	'Right wheel speed'
//	0		1		2		3		4		5		6		7
//	NULL	Back	stop	Vslow	slow	Med		fast	Vfast
//
	int LocE[]=
	{	2,	2,	1,	1,	1,
		3,	3,	3,	1,	1,
		3,	3,	3,	2,	1,
		4,	4,	4,	3,	2,
		5,	5,	5,	4,	3,
		6,	6,	6,	5,	4,
		7,	7,	7,	6,	5	};
//												BACK
//												STOP
//												vslow	Relation'1'
//												slow	vehicle speed
//												med
//												fast
//												Vfast
//	leftmax	left	streight	right	rightmax
//	stearing direction
//	Relation '0'
	Mats[4] = new Matrix;
	Mats[4]->Build(5,7,LocE);
//------------------------------------------------------------//

//	Output	'Maximum Vehicle speed'
//	0		1		2		3		4		5		6		7
//	NULL	BACK	STOP	vslow	slow	med		fast	vfast
//
	int LocF[]=
	{	1,1,1,1,1,
		2,3,3,3,2,	//4
		3,4,4,4,3,	//5
		4,5,6,5,4,
		4,5,7,5,4	};
//												vclose	Relation'1'
//												close	obstacle proximity
//												med
//												far
//												Vfar
//	leftmax	left	streight	right	rightmax
//	stearing angle
//	Relation '0'
	Mats[5] = new Matrix;
	Mats[5]->Build(5,5,LocF);
//------------------------------------------------------------//
//	Output	'Gray scale change'
//	0		1			2		3	
//	NULL	negative	none	positive	
//
	int LocG[]=
	{	2,1,1,
		3,2,1,
		3,3,2	};
//								No		Relation'1'
//								Mid		bELIEF IN cLEAR
//								Yes
//	No		Mid		Yes
//	Belief in Wall
//	Relation '0'
	Mats[6] = new Matrix;
	Mats[6]->Build(3,3,LocG);
//------------------------------------------------------------//
//	Output	'Left Vs Right obstacle avoidance'
//	0		1		2			3			4			5
//	NULL	LEFT	LEFTish		Streight	RIGHTish	RIGHT
//
	int LocH[] =
	{	3,2,1,1,1,
		4,3,2,2,2,
		5,4,3,2,2,
		5,4,4,3,2,
		5,4,4,4,3	};
//				
//											Rclose		Relation'1'
//											Rnear		'Right DISTANCE'
//											Rdist
//											Rfar
//											RVfar
//	Lclose	Lnear	Ldist	Lfar	LVfar
//	'Left Distance'
//	Relation '0'
	Mats[7] = new Matrix;
	Mats[7]->Build(5,5,LocH);
//------------------------------------------------------------//
//	Output	'Min Vs average obstacle avoidance'
//	0		1		2			3			4			5
//	NULL	LEFT	LEFTish		Streight	RIGHTish	RIGHT
//
	int LocI[] =
	{	1,1,2,4,5,
		1,2,2,4,5,
		1,2,3,4,5,
		1,2,4,4,5,
		1,2,4,5,5	};
//				
//											LMax		Relation'1'
//											Lish		'average distance'
//											Center
//											Rish
//											RMax
//	LMax	Lish	Center	Rish	Rmax
//	'Minamum distance obstace avoidance'
//	Relation '0'
	Mats[8] = new Matrix;
	Mats[8]->Build(5,5,LocI);
//------------------------------------------------------------//
//	Output	'Vehicle speed'
//	0		1		2		3		4		5		6		7
//	NULL	BACK	STOP	vslow	slow	med		fast	vfast
//
	int LocJ[]=
	{	1,1,1,1,1,
		2,2,2,2,2,
		3,3,4,3,3,
		3,4,4,4,3,
		3,4,5,4,3,
		4,5,6,5,4,
		4,5,7,5,4	};
//												BACK	Relation'1'
//												STOP	 vehicle speed
//												vslow
//												slow
//												med
//												fast
//												Vfast
//	Left	Lish	streight	Rish	Right
//	Target direction error
//	Relation '0'
	Mats[9] = new Matrix;
	Mats[9]->Build(5,7,LocJ);
//------------------------------------------------------------//

}

MakeMappings::MakeMappings()
{

}

MakeMappings::~MakeMappings()
{

}

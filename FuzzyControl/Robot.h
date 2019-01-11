// Robot.h: interface for the Robot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOT_H__0460E8C0_2DEC_11D6_909D_444553540001__INCLUDED_)
#define AFX_ROBOT_H__0460E8C0_2DEC_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Laser.h"	// includes graymap
#include "MakeInferences.h" // includes membfunc, matrix
#include "FuzzyMap.h"
#include "versionone.h"
#include "GrayMap.h"
#include "BoolMap.h"
#include "NodeMap.h"	// Added by ClassView
#include "MapController.h"

class Robot  
{
	double pi;
	float real_Orient;
	float real_y;
	float real_x;

	int MaxSpeed;
	int WheelBase;

public:
	int route_node;
	int Cur_node;	// Implicitly 0 to begin! Master Node.
	int Cur_dir;
	int endAt;
	int startAt;
	bool ROUTE;
	bool GOAL;
	int behave;
	int doing;
	int possible;

	void Robot::route();
	void Robot::Gogoal();
	void explore();
	Robot::Notpossible();

	void propogate(int from);

	bool planRoute(int Node);
	bool planRoute();
	bool planRoute(float x, float y);	

	void buildNodes();
	void FtoGMap();

	BoolMap *bMap;

	NodeMap *NMap;

	float Orient;
	float pos_y;
	float pos_x;

	coord goal;
	coord target;
	MakeInferences Infer;

	FuzzyMap FMap;
	GrayMap GMap;
	Laser *Laz;
	MapController *NMapControl;

	void Drive(float Left ,float Right);
	void Build(int x, int y, float Orientation);
	void runinfer();
	void implement();
	
	void MakeScan();	
	void updateMap();
	void moveFuzzyMap(int x,int y);
	
	Robot();
	Robot(BoolMap *BM);
	virtual ~Robot();
};

#endif // !defined(AFX_ROBOT_H__0460E8C0_2DEC_11D6_909D_444553540001__INCLUDED_)

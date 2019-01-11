// Laser.h: interface for the Laser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LASER_H__FCD713E1_2C83_11D6_909D_444553540001__INCLUDED_)
#define AFX_LASER_H__FCD713E1_2C83_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BoolMap.h"

class Laser  
{
	double pi;
	BoolMap *BMap;

public:
	float average;
	float furthest;
	float Exclude;
	float scan(int x, int y, float dir);
	int rot_inc;
	int *distances;
	int MaxRange;

	void scan(int x, int y);
	int measure(float x, float y, float angle);
	Laser();
	Laser(BoolMap *BooleanMap);
	virtual ~Laser();

};

#endif // !defined(AFX_LASER_H__FCD713E1_2C83_11D6_909D_444553540001__INCLUDED_)

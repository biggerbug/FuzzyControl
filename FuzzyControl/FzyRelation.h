// FzyRelation.h: interface for the FzyRelation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FZYRELATION_H__4408D738_2497_11D6_909D_444553540001__INCLUDED_)
#define AFX_FZYRELATION_H__4408D738_2497_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MembFunc.h"

class FzyRelation  
{
private:
	float Rmin, Rmax;

	MembFunc MembList[10];
	MembFunc Hedge;
	bool HasHedge;
	
public:
	char name[15];

	bool MakeHedge(float Min, float Mid, float Max, char Name[]);
	float GetCval(int);
	void Clip(int,float);
	float GetRMax();
	float GetRMin();
	int members;

	float Eval(int M, float In);
	float Defuz();
	bool MakeMemb(float Min, float Mid, float Max, char Name[]);
	FzyRelation(float RMin, float RMax, char Name[]);
	virtual ~FzyRelation();

};

#endif // !defined(AFX_FZYRELATION_H__4408D738_2497_11D6_909D_444553540001__INCLUDED_)

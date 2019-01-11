// MembFunc.h: interface for the MembFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBFUNC_H__4408D73C_2497_11D6_909D_444553540001__INCLUDED_)
#define AFX_MEMBFUNC_H__4408D73C_2497_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MembFunc  
{
private:
	char name[15];
	float min;
	float mid;
	float max;
	float clipvalue;

public:
	float Hval(float);

	float GetMid();
	float GetMax();
	float GetMin();
	float GetClip();

	void SetClip(float Value);
	void CreateMembFunc(float Min, float Med, float Max, char Name[]);
	MembFunc();
	virtual ~MembFunc();


};

#endif // !defined(AFX_MEMBFUNC_H__4408D73C_2497_11D6_909D_444553540001__INCLUDED_)

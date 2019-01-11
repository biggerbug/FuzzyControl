// MembFunc.cpp: implementation of the MembFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "MembFunc.h"
#include "FzyRelation.h"//

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;    


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MembFunc::MembFunc()
{
	clipvalue=0;
}

MembFunc::~MembFunc()
{

}

void MembFunc::CreateMembFunc(float Min, float Mid, float Max, char Name[])
{
	min=Min;
	mid=Mid;
	max=Max;
strcpy (name,Name);
}

void MembFunc::SetClip(float Value)
{
	clipvalue=Value;
}

float MembFunc::GetClip()
{
	return clipvalue;
}

float MembFunc::GetMin()
{
	return min;
}

float MembFunc::GetMax()
{
	return max;
}

float MembFunc::GetMid()
{
	return mid;
}

float MembFunc::Hval(float In)
{
	int temp;

	if(In==GetMid())
	{
		temp= 1;
//		printf("\nID`d as MidPoint.");
	}
	//Or Y=MX+c
	if(In<GetMid())
	{
		temp= (In-GetMin())*(1/(GetMid()-GetMin()));
//		printf("\nCalculated between Min and Mid");
	}
	if(In>GetMid()) 
	{
		temp= 1+(In-GetMid())*(-1/(GetMax()-GetMid()));
//		printf("\nCalculated between Mid and Max");
	}
	return temp;
}

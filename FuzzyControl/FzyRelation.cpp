// FzyRelation.cpp: implementation of the FzyRelation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "MembFunc.h"
#include "FzyRelation.h"
#include "conio.h"

using namespace std;    

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FzyRelation::FzyRelation(float RMin, float RMax, char Name[])
{
//
	members=0;
//	
	Rmin=RMin;
	Rmax=RMax;
	strcpy(name,Name);
	HasHedge =0;
}

FzyRelation::~FzyRelation()
{

}


bool FzyRelation::MakeMemb(float Min, float Mid, float Max, char Name[])
{
	if((Min<=Mid)&&(Mid<=Max)&&(Rmin<=Min)&&(Max<=Rmax))
	{
		MembList[members].CreateMembFunc(Min,Mid,Max,Name);
		members++;

		return 1;
	}
	else
		return 0;
}

bool FzyRelation::MakeHedge(float Min, float Mid, float Max, char Name[])
{
	if((Min<=Mid)&&(Mid<=Max)&&(Rmin<=Min)&&(Max<=Rmax))
	{
		Hedge.CreateMembFunc(Min,Mid,Max,Name);
		HasHedge = 1;

		return 1;
	}
	else
		return 0;
}

float FzyRelation::Defuz()
{
//	int i;
//	for(i=0;i<members;i++)
//		printf("\nMember %d, Min=%f Mid=%f Max=%f Clipped at %f",i,MembList[i].GetMin(),MembList[i].GetMid(),MembList[i].GetMax(),MembList[i].GetClip());
	int R,M;
	float val=0, WSum=0, SigVal=0;
	for(R=int(GetRMin());R<int(GetRMax());R++)
	{
		val = 0;
		for(M=0;M<members;M++)
		{
			if((Eval(M,float(R))>val) && (GetCval(M)>val))
			{
				if(Eval(M,float(R))>GetCval(M))
					val = GetCval(M);
				else
					val = Eval(M,float(R));

			}
			//Extract ALL membership values here
		}
		// Implement hedge function...
		if(HasHedge)
		{
			if( (R>Hedge.GetMin()) && (R<Hedge.GetMax()) && (Hedge.Hval(float(R))>val) )
			{
				val = Hedge.Hval(float(R));
//					printf("\nHedgevalue is set at %f",val);
			}
		}
		//
		WSum += val*R;
		SigVal += val;
//		printf("\nWsum = %f, SigVal = %f, Wsum/SigVal = %f",WSum,SigVal,WSum/SigVal);
//		getch();
	}
	FzyRelation *local = this;
	float temp = WSum / SigVal;
//		printf("\nFuzzyRelation %s defuziz to %f",local->name,temp);
	if((WSum)&&(SigVal))
		return(temp);
	else
		return(0);
}

float FzyRelation::Eval(int M, float In)
{
//	printf("\nEval working on membership %d at value %f,\nRange %f to %f and centered at %f.",M,In,MembList[M].GetMin(),MembList[M].GetMax(),MembList[M].GetMid() );

	float temp= 0;
	//If outside members range = 0
	if(In<MembList[M].GetMin()||In>MembList[M].GetMax())
	{
//		printf("\nReturnde as out of range.");
		return 0;
	}
	//If hedge & is AT Mid = 1
	if( (MembList[M].GetMin()==MembList[M].GetMid()) || 
		(MembList[M].GetMax()==MembList[M].GetMid()) )
		if(In==MembList[M].GetMid())
		{
			temp = 1;
//		printf("\nID`d as a HedgeMax");
		}
	//Else if AT Min or Max = 0
	else if( (In==MembList[M].GetMin()) || (In==MembList[M].GetMax()) )
	{
//		printf("\nReturned as Limit.");
		return 0;
	}
	//Otherwise if at Mid = 1
	if(In==MembList[M].GetMid())
	{
		temp= 1;
//		printf("\nID`d as MidPoint.");
	}
	//Or Y=MX+c
	if(In<MembList[M].GetMid())
	{
		temp= (In-MembList[M].GetMin())*(1/(MembList[M].GetMid()-MembList[M].GetMin()));
//		printf("\nCalculated between Min and Mid");
		
	}
	if(In>MembList[M].GetMid()) 
	{
		temp= 1+(In-MembList[M].GetMid())*(-1/(MembList[M].GetMax()-MembList[M].GetMid()));
//		printf("\nCalculated between Mid and Max");
		
	}

	return temp;
}

float FzyRelation::GetRMin()
{
	return(Rmin);
}

float FzyRelation::GetRMax()
{
	return(Rmax);
}

void FzyRelation::Clip(int Member, float ClipValue)
{
	MembList[Member].SetClip(ClipValue);
}

float FzyRelation::GetCval(int Rel)
{
	return(MembList[Rel].GetClip());
}

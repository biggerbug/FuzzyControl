// InFer.cpp: implementation of the InFer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "InFer.h"
#include "FzyRelation.h"
#include "MembFunc.h"
#include "Matrix.h"
#include "conio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SPEEDlow	0
#define	SPEEDmedium	1
#define	SPEEDhigh	2

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


InFer::InFer()
{

}

void InFer::Build(FzyRelation *RelA, FzyRelation *RelB, FzyRelation *Out, Matrix *Mx)
{

	Rels[0] = RelA;
	Rels[1] = RelB;
	Output = Out;
	Mat = Mx;

}

float InFer::Exe(float A, float B)
{
	if(A<Rels[0]->GetRMin())
	{
//printf("\nRelation %s input %f minn`d to %f",Rels[0]->name,A,Rels[0]->GetRMin());
		A=Rels[0]->GetRMin();
	}
	if(A>Rels[0]->GetRMax())
	{
//printf("\nRelation %s input %f maxed to %f",Rels[0]->name,A,Rels[0]->GetRMax());
		A=Rels[0]->GetRMax();
	}
	if(B<Rels[1]->GetRMin())
	{
//printf("\nRelation %s input %f minn`d to %f",Rels[1]->name,B,Rels[1]->GetRMin());
		B=Rels[1]->GetRMin();
	}
	if(B>Rels[1]->GetRMax())
	{
//printf("\nRelation %s input %f maxed to %f",Rels[1]->name,B,Rels[1]->GetRMax());
		B=Rels[1]->GetRMax();
	}

	int i,row,colum;

	for(i=0;i<Rels[0]->members;i++)
		Rels[0]->Clip(i,1);
	for(i=0;i<Rels[1]->members;i++)
		Rels[1]->Clip(i,1);
	for(i=0;i<Output->members;i++)
		Output->Clip(i,0);
//printf("\n");
	for(row=0;row<Rels[1]->members;row++)
	{
		for(colum=0;colum<Rels[0]->members;colum++)
		{
			if(Mat->M[row][colum])
			{
				Output->Clip(Mat->M[row][colum]-1,MaX(Output->GetCval(Mat->M[row][colum]-1),MiN(Rels[0],colum,A,Rels[1],row,B)));
			}
//printf("%d ",Mat->M[row][colum]);
		}
//printf("\n");
	}
	float temp= Output->Defuz();
	return(temp);
}

InFer::~InFer()
{

}

float InFer::MaX(FzyRelation *RiA, int i, float A, FzyRelation *RjB, int j, float B)
{
	if(RiA->Eval(i,A)>RjB->Eval(j,B))
		return RiA->Eval(i,A);
	return RjB->Eval(j,B);
}

float InFer::MaX(float a, float b)
{
	if(a>b)
		return(a);
	return(b);
}

float InFer::MiN(FzyRelation *RiA, int i, float A, FzyRelation *RjB, int j, float B)
{
//	printf("\nMiN... RiA->Eval(i,A) = %f // RjB->Eval(j,B) = %f",RiA->Eval(i,A),RjB->Eval(j,B));
	if(RiA->Eval(i,A)>=RjB->Eval(j,B))
		return RjB->Eval(j,B);
	return RiA->Eval(i,A);
}

float InFer::MiN(float a, float b)
{
	if(a>b)
		return(b);
	return(a);
}



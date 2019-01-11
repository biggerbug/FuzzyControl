// GrayMap.cpp: implementation of the GrayMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "GrayMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void GrayMap::Build(int x, int y)
{
	int i,j;

	x_size = x;
	y_size = y;

	data = new int *[x];
	for(i=0;i<x;i++)
	{
		data[i] = new int[y];
		for(j=0;j<y;j++)
			data[i][j]=0;
	}

//	SetPos(5,6,20);
//	SetPos(5,7,40);
//	SetPos(5,8,60);
//	SetPos(5,9,80);
//	SetPos(6,6,100);
//	SetPos(7,7,100);
//	SetPos(8,8,100);
//	SetPos(9,9,100);

}

void GrayMap::SetPos(int X, int Y, int Value)
{
	if((X<0) || (Y<0) || (X>x_size-1) || (Y>y_size-1))
	{
		;
	}
	else
	{
		data[X][Y] = Value;
	}
}

int GrayMap::GetPos(int X, int Y)
{
	if((X<0) || (Y<0) || (X>x_size-1) || (Y>y_size-1))
		return(1);		// All area outside range are occupied
	return(data[X][Y]);
}

GrayMap::GrayMap()
{

}

GrayMap::~GrayMap()
{

}

int GrayMap::size_x()
{
	return(x_size);
}

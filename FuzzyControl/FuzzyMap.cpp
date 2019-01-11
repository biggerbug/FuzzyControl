// FuzzyMap.cpp: implementation of the FuzzyMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FuzzyMap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void FuzzyMap::Build(int x, int y)
{
	int i,j;

	x_size = x;
	y_size = y;

	x_pos = 0;
	y_pos = 0;

	BClear = new int *[x];
	for(i=0;i<x;i++)
	{
		BClear[i] = new int[y];
		for(j=0;j<y;j++)
			BClear[i][j]=0;
	}

	BWall = new int *[x];
	for(i=0;i<x;i++)
	{
		BWall[i] = new int[y];
		for(j=0;j<y;j++)
			BWall[i][j]=0;
	}
}

void FuzzyMap::SetWall(int X, int Y, int Value)
{
	BWall[X][Y] = Value;
}

int FuzzyMap::GetWall(int X, int Y)
{
	return(BWall[X][Y]);
}

void FuzzyMap::SetClear(int X, int Y, int Value)
{
	BClear[X][Y] = Value;
}

int FuzzyMap::GetClear(int X, int Y)
{
	return(BClear[X][Y]);
}

FuzzyMap::FuzzyMap()
{

}

FuzzyMap::~FuzzyMap()
{

}

void FuzzyMap::clearMap()
{
	int i,j;
//
	for(i=0;i<x_size;i++)
	{
		for(j=0;j<y_size;j++)
		{
			BClear[i][j]=0;
			BWall[i][j]=0;
		}
	}
}

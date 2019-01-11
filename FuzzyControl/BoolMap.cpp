// BoolMap.cpp: implementation of the BoolMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BoolMap.h"
#include "math.h"
#include "conio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void BoolMap::Build(int x, int y)
{
	int i,j;

	x_size = x;
	y_size = y;

	data = new bool *[x];
	for(i=0;i<x;i++)
	{
		data[i] = new bool[y];
		for(j=0;j<y;j++)
			data[i][j]=0;
	}
	
	int wall;
	const int walls = 4+4+4+4;

	int wallmap[walls][4] =	{
		{	0,0,x-1,0	},
		{	x-1,0,x-1,y-1	},
		{	x-1,y-1,0,y-1	},
		{	0,y-1,0,0	},
//
		{	10,10,20,10	},
		{	20,10,20,20	},
		{	20,20,10,20	},
		{	10,20,10,10	},
//
		{	50,50,60,60	},
		{	60,60,50,60	},
		{	50,60,70,60	},
		{	70,60,70,70	},
//
		{	20,70,10,50	},
		{	10,50,35,25	},
		{	35,25,50,25	},
		{	50,25,70,40	},
//
	};

	for(wall=0;wall<walls;wall++)
	{
		drawWall(wallmap[wall][0],wallmap[wall][1],wallmap[wall][2],wallmap[wall][3], 1);
	}	
}

void BoolMap::drawWall(int ax, int ay, int bx, int by, bool color)
{
	if(	(ax<0) || (ay<0) || (ax>x_size-1) || (ay>y_size-1) ||
		(bx<0) || (by<0) || (bx>x_size-1) || (by>y_size-1) )
	{
		;
	}
	else
	{
		int i;
		int x_dist = bx-ax;
		int y_dist = by-ay;
		int index = int(pow(pow(x_dist,2)+pow(y_dist,2),0.5));
		for(i=0;i<index;i++)
		{
			data[ax+int(i*x_dist/index)][ay+int(i*y_dist/index)]=color;
			if(!color)
			{
				data[ax-1+int(i*x_dist/index)][ay-1+int(i*y_dist/index)]=0;
				data[ax-1+int(i*x_dist/index)][ay+1+int(i*y_dist/index)]=0;
				data[ax+1+int(i*x_dist/index)][ay-1+int(i*y_dist/index)]=0;
				data[ax+1+int(i*x_dist/index)][ay+1+int(i*y_dist/index)]=0;
			}
		}
	}
}

void BoolMap::SetPos(int X, int Y, bool Value)
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

bool BoolMap::GetPos(int X, int Y)
{
	if((X<0) || (Y<0) || (X>x_size-1) || (Y>y_size-1))
		return(1);		// All area outside range are occupied
	return(data[X][Y]);
}

BoolMap::BoolMap()
{

}

BoolMap::~BoolMap()
{

}

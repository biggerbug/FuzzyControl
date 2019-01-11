// Laser.cpp: implementation of the Laser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Laser.h"
#include "math.h"
#include "BoolMap.h"

#include "conio.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

float Laser::scan(int x, int y, float dir)
{
	float fur=0,av=0;
	int count=0;
	float closest=MaxRange;
	float range;
	float ii;
	for(ii=-(1.0/8.0);ii<=(1.0/8.0);ii+=(1.0/32.0))
	{
		range = measure(x,y,dir+ii);
//		printf("\nScan at %f = range of %f",dir+ii,range);
		if((range)&&(range < closest))
			closest = range;
		if((range)&&(range>fur))
			fur = range;
		if(range)
			av+=range;
		else
			av+=MaxRange;
		count++;
	}
	av /= count;
	furthest=float(float(fur)-Exclude)/float(float(MaxRange)-float(Exclude))*100;
	average=float(float(av)-Exclude)/float(float(MaxRange)-float(Exclude))*100;
//printf("\n\nObstacle range is %f\n\n",closest);
	if(closest>MaxRange)
		closest=MaxRange;
	return(float(float(closest)-float(Exclude+2))/float(float(MaxRange)-float(Exclude+2))*100);
}

void Laser::scan(int x, int y)
{
	float angle;
	int i;
	for(i=0;i<rot_inc;i++)
	{
		angle = -0.5+float(i)/float(rot_inc);		// Scans start at -0.5,South and move East full circle.
		distances[i]=measure(x,y,angle);
	}
}

int Laser::measure(float x, float y, float angle)
{
	int range=0;
	int hit = 0;
	float new_x, new_y, last_x, last_y;
	last_x = x;
	last_y = y;
	while(range<MaxRange && hit == 0)
	{
		new_x = x-sin(2*pi*angle)*range;
		new_y = y+cos(2*pi*angle)*range;

		if(new_x<0 || new_x>BMap->x_size || new_y<0 || new_y>BMap->y_size)
			break;
		else if(	BMap->GetPos( int(new_x),int(new_y) ) !=0 ||
					BMap->GetPos( int(last_x),int(new_y) ) !=0 ||
					BMap->GetPos( int(new_x),int(last_y) ) !=0 )
		{
			hit = 1;
		}

//	printf("\nScanning at BoolMap(%f,%f) angle=%f",new_x,new_y,angle);

		range++;
		
		last_x = new_x;
		last_y = new_y;
	}

	if(hit)
		return(range);
	return(0);
}

Laser::Laser(BoolMap *BooleanMap)
{
	BMap = BooleanMap;
	pi = 3.1415926535;
	rot_inc = 32;
	distances = new int[rot_inc];
	MaxRange = 17;		//Keep to odd numbers as range dictates size of Fuzzy map and robot lives at center point x/2,y/2
}

Laser::Laser()
{

}

Laser::~Laser()
{

}


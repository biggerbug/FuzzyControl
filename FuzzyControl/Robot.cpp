// Robot.cpp: implementation of the Robot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Robot.h"
#include "Math.h"
#include "conio.h"	//getch()
#include "NodeMap.h"
#include "MapController.h"
#include "BoolMap.h"
#include "Laser.h"

// Behaviour constants
#define EXPLORE	0
#define TARGET	1
#define STOP	2
#define START	3

// Explore behaviour constants
#define NODE	0
#define EXPAND	1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void Robot::Build(int x, int y, float Orientation)
{
	int Bx,By;
	Bx= bMap->x_size;
	By= bMap->y_size;
	GMap.Build(Bx,By);
	FMap.Build(2*Laz->MaxRange,2*Laz->MaxRange);	//Robot lives at center point x/2,y/2
	Infer.Build();

	pos_x= x;
	pos_y= y;
	real_x= x;
	real_y= y;

	Orient = Orientation;
	real_Orient= Orientation;

	MaxSpeed = 16;
	WheelBase = 4;
	Laz->Exclude = pow((pow((WheelBase/2),2)*2),0.5);
	//
	NMap = new NodeMap(NMapControl);
	NMap->MakeMasterNode(pos_x,pos_y);
	//
	behave = START;		// Initial starting behaviour for robot
	GOAL = 0;				// NOT going for the goal just yet eh!
	ROUTE=0;
	possible=10;
	doing=0;		// 0 to begin! NODE
	//
	route_node=0;
}

void Robot::Drive(float Left, float Right)
{
	int backup_x = int(pos_x);
	int backup_y = int(pos_y);
	//
	float Rx,Ry,Lx,Ly;
	float Rdis,Ldis;
	int i,diff;
	if(Left>Right)
		diff=Left-Right;
	else
		diff=Right-Left;
	float x_temp,y_temp,ori_temp;
	x_temp = pos_x;
	y_temp = pos_y;
	ori_temp = Orient;
	
//	printf("\nFreds origional location and orientation is (%f,%f) at %f",x_temp,y_temp,Orient);
	
	//calc drive potentials of each wheel
	Rdis= Right/100*MaxSpeed;
	Ldis= Left/100*MaxSpeed;
	if(diff)
	{
		Rdis/=diff;
		Ldis/=diff;
	}
//	printf("\n\nLeft dis inc %f , Right dis inc %f",Ldis,Rdis);
	
	for(i=0;i<=diff;i++)
	{
		//calc wheel positions from orientation and position
		Rx= x_temp+(WheelBase/2)*cos(2*pi*ori_temp);
		Ry= y_temp+(WheelBase/2)*sin(2*pi*ori_temp);
		Lx= x_temp-(WheelBase/2)*cos(2*pi*ori_temp);
		Ly= y_temp-(WheelBase/2)*sin(2*pi*ori_temp);

//		printf("\ncos(2*pi*Orient) = %f",cos(2*pi*Orient));
//		printf("\nsin(2*pi*Orient) = %f",sin(2*pi*Orient));
		
//		printf("\nx displacement = %f",(WheelBase/2)*cos(2*pi*Orient));
//		printf("\ny displacement = %f",(WheelBase/2)*sin(2*pi*Orient));

//		printf("\nWheelBase = %d",WheelBase);

//		printf("\nFreds left wheel is at (%f,%f)",Lx,Ly);
//		printf("\nFreds right wheel is at (%f,%f)",Rx,Ry);
	
		//calc new wheel position from old and drive potential
		Rx= Rx+Rdis*cos(2*pi*(ori_temp+0.25));
		Ry= Ry+Rdis*sin(2*pi*(ori_temp+0.25));
		Lx= Lx-Ldis*cos(2*pi*(ori_temp-0.25));
		Ly= Ly-Ldis*sin(2*pi*(ori_temp-0.25));

//		printf("\n\nNow left wheel is at (%f,%f)",Lx,Ly);
//		printf("\nNow right wheel is at (%f,%f)",Rx,Ry);

		//recalc new x,y and orientation of robot, Keepint within +-0.5
//		
		if(Ly<Ry)											//East
		{
			if(Lx<Rx)		
				ori_temp= atan((Ry-Ly)/(Rx-Lx))/(2*pi);				//North
			else
				ori_temp= 0.5+(-(atan((Ry-Ly)/(Lx-Rx))/(2*pi)));	//South	
		}
//
		else												//West
		{
			if(Lx<Rx)
				ori_temp= atan((Ry-Ly)/(Rx-Lx))/(2*pi);				//North
			else
				ori_temp= -0.5+(-(atan((Ry-Ly)/(Lx-Rx))/(2*pi)));	//South
		}
//
		x_temp= (Rx+Lx)/2;
		y_temp= (Ry+Ly)/2;

//		printf("\nFreds new orientation is %f",ori_temp);
//		getch();
	}

	pos_x = x_temp;
	pos_y = y_temp;
	Orient = ori_temp;

	moveFuzzyMap(int(pos_x)-backup_x,int(pos_y)-backup_y);
}

Robot::Robot()
{

}

Robot::Robot( BoolMap *BM)
{
	bMap = BM;
	//
	Robot *ref = this;
	NMapControl = new MapController(ref);
	Laz = new Laser(BM);
	pi = 3.1415926535;
}

Robot::~Robot()
{

}

void Robot::implement()
{
	Drive(Infer.Lwheel,Infer.Rwheel);
//	printf("\nDRive(%f,%f)",Infer.Lwheel,Infer.Rwheel);
}

void Robot::MakeScan()
{
	Laz->scan(pos_x,pos_y);
//	printf("\nMakescan compleated successfully");
}

void Robot::updateMap()
{
	float angle,range;
	int i,j,x,y,current;
	for(i=0;i<Laz->rot_inc;i++)
	{
		angle = -0.5+float(i)/float(Laz->rot_inc);		// Scans start at -0.5,South and move East full circle.
		range = Laz->distances[i];
		if(range)
		{	// Set wall point
			x = int( -sin(2*pi*angle)*range )+int(FMap.x_size/2);
			y = int( cos(2*pi*angle)*range )+int(FMap.y_size/2);
		
			if((x>=0)&&(x<FMap.x_size)&&(y>=0)&&(y,FMap.y_size))
			{
				current = FMap.GetWall(x,y);
				FMap.SetWall(x,y,int(float(current)+((100.0-float(current))/5.0)) );		//!!// Insufficient
			}
	//printf("\nbelief level = %d",FMap.GetWall(x,y));
		}
		else
			range = Laz->MaxRange;
//
		for(j=int(range-2);j>0;j--)
		{	// Set clear from NEAR wall to robot
			x = int( -sin(2*pi*angle)*j )+int(FMap.x_size/2);
			y = int( cos(2*pi*angle)*j )+int(FMap.y_size/2);

			if((x>=0)&&(x<FMap.x_size)&&(y>=0)&&(y,FMap.y_size))
			{
				current = FMap.GetClear(x,y);
				FMap.SetClear(x,y,int(float(current)+((100.0-float(current))/5.0)) );		//!!// Insufficient
			}
		// Potential for setting clear if transitional points.		
		}
	}
//	printf("\nUpdateMape compleated successfully");
	FtoGMap();
}

void Robot::moveFuzzyMap(int x, int y)
{
	//First relocate map on X axis
	int i,j;
	if(x<0)//Robot moves left//West
	{
		for(i=FMap.x_size-1;i>=-x;i--)	//Working from right to left
		{
			for(j=0;j<FMap.y_size;j++)	//and on each element of each colum
			{
				FMap.SetClear(i,j,FMap.GetClear(i+x,j));
				FMap.SetWall(i,j,FMap.GetWall(i+x,j));
			}
		}
		for(i=-x;i>=0;i--)
		{
			for(j=0;j<FMap.y_size;j++)
			{
				FMap.SetClear(i,j,0);
				FMap.SetWall(i,j,0);
			}
		}
	}
	else
	{
		for(i=0;i<FMap.x_size-x;i++)	//Working from left to right
		{
			for(j=0;j<FMap.y_size;j++)	//and on each element of each colum
			{
				FMap.SetClear(i,j,FMap.GetClear(i+x,j));
				FMap.SetWall(i,j,FMap.GetWall(i+x,j));
			}
		}
		for(i=x;i>0;i--)
		{
			for(j=0;j<FMap.y_size;j++)
			{
				FMap.SetClear(FMap.x_size-i,j,0);
				FMap.SetWall(FMap.x_size-i,j,0);
			}
		}
	}
//nOW RELOCATE MAP ON Y AXIS
// Fuzzymap y axis 0 is at the south
	int iy,ix;
	if(y<0)		//then robot is heading south
	{
		for(iy=FMap.y_size-1;iy>=-y;iy--)	// starting at top working down
		{
			for(ix=0;ix<FMap.x_size;ix++)	// for each element in row
			{
				FMap.SetClear(ix,iy,FMap.GetClear(ix,iy+y));
				FMap.SetWall(ix,iy,FMap.GetWall(ix,iy+y));
			}
		}
		for(iy=-y;iy>=0;iy--)
		{
			for(ix=0;ix<FMap.x_size;ix++)
			{
				FMap.SetClear(ix,iy,0);		//Possibly consider data from Gray scale map
				FMap.SetWall(ix,iy,0);
			}
		}
	}
	else
	{
		for(iy=0;iy<FMap.y_size-y;iy++)
		{
			for(ix=0;ix<FMap.x_size;ix++)
			{
				FMap.SetClear(ix,iy,FMap.GetClear(ix,iy+y));
				FMap.SetWall(ix,iy,FMap.GetWall(ix,iy+y));
			}
		}
		for(iy=FMap.y_size-y;iy<FMap.y_size;iy++)
		{
			for(ix=0;ix<FMap.x_size;ix++)
			{
				FMap.SetClear(ix,iy,0);
				FMap.SetWall(ix,iy,0);
			}
		}
	}
}

void Robot::FtoGMap()
{
//	Fuzzy Map to Gray Map inference
	int ix,iy,Rx,Ry,FClear,FWall;
	float dGray,cGray;
	Rx= pos_x - FMap.x_size/2;
	Ry= pos_y - FMap.y_size/2;
	for(iy=0; iy<FMap.y_size; iy++)
	{
		for(ix=0; ix<FMap.x_size; ix++)
		{
			if( (Rx+ix>=0) && (Rx+ix<GMap.x_size) && (Ry+iy>=0) && (Ry+iy<GMap.y_size) )
			{
				FClear=FMap.GetClear(ix,iy);
				FWall=FMap.GetWall(ix,iy);
				cGray = float(GMap.GetPos(Rx+ix,Ry+iy));
				//- - - - - - - - - - - - - - - - -
				dGray = Infer.rules[6]->Exe(FClear,FWall);
				//- - - - - - - - - - - - - - - - -
				if(cGray+dGray > 100)
					GMap.SetPos(Rx+ix,Ry+iy,100);
				else if(cGray+dGray <0)
					GMap.SetPos(Rx+ix,Ry+iy,0);
				else
					GMap.SetPos(Rx+ix,Ry+iy,cGray+dGray);
			}
		}
	}
//	printf("\nFtoGMap compleated successfully");
}

void Robot::buildNodes()
{
	NMapControl->NodeRules();
}

void Robot::runinfer()
{
	if(behave == START)
	{
		target.x=NMap->Nodes[0]->x_x+NMap->off_x;	//To start with ...
		target.y=NMap->Nodes[0]->y_y+NMap->off_y;	//
		behave = EXPLORE;
	}
//
	if(	(!GOAL)				&&	// Quicker that checking visability
		(behave == TARGET)	&&	// only when target is valid!
		(NMapControl->isvisable(goal.x, goal.y)) )	// And visable
	{
		Gogoal();	// Then go directly to the goal
	}
//
	if((GOAL)||(ROUTE))
	{
		if(GOAL)
		{
			Gogoal();
		}
//
		if(ROUTE)
		{
			route();
		}
	}
//
	else
	{
		if(behave == TARGET)
		{
			explore();
		}
	//
		if(behave == EXPLORE)
		{
			explore();
		}
	}
//
	Robot *ref = this;
	possible += Infer.Exe(ref);	// Flag for frustration leeding to impossible goal
	if(possible<=0)
	{
		possible=3;
		Notpossible();
	}
}

void Robot::route()
{
//printf("\nROUTE");
//
	if(		(NMapControl->isvisable(NMap->Nodes[endAt]))	&&
			(route_node != endAt)	)
	{
		route_node = endAt;
		startAt= route_node;
		Cur_node = route_node;
		target.x= NMap->Nodes[route_node]->x_x + NMap->off_x;
		target.y= NMap->Nodes[route_node]->y_y + NMap->off_y;
	}
//
	float dist = NMap->distance(pos_x, pos_y, float(target.x), float(target.y) );
	if(dist <= 2.0)
	{
		if(route_node != startAt)		// Washy way but identifies the first node
		{
			route_node = startAt;		// in the route plan
			Cur_node = startAt;
			doing = NODE;
		}
		//
		if(route_node == endAt)
		{
//printf("\nEnded route");
			ROUTE=0;
			Cur_node = endAt;//??
			//
			target.x = NMap->Nodes[Cur_node]->x_x + NMap->off_x;
			target.y = NMap->Nodes[Cur_node]->y_y + NMap->off_y;
//			target.x = NMap->Nodes[Cur_node]->x_x + NMap->off_x;
//			target.y = NMap->Nodes[Cur_node]->y_y + NMap->off_y;
		}
		else
		{
//printf("\nPreceding to next node in route");
//printf("\nFINDNEXT called from ROUTE");
			route_node = NMap->findnext(route_node);
			startAt= route_node;
			Cur_node = route_node;
			target.x= NMap->Nodes[route_node]->x_x + NMap->off_x;
			target.y= NMap->Nodes[route_node]->y_y + NMap->off_y;
		}
	}
}

void Robot::Gogoal()	// If sighted goal
{
//printf("\nGOAL");
//
	int clear=0;
	if(!GOAL)
	{
		GOAL=1;
		ROUTE=0;	//	???**???	.,;;,.
		target.x=goal.x;
		target.y=goal.y;
	}
//
	if( (target.x != goal.x) ||		// Goal has moved!
		(target.y != goal.y) )
	{
		GOAL=0;
		clear=1;
	}
//
	if( NMap->distance(	pos_x,	pos_y,				// If arived at GOAL
						goal.x,	goal.y ) <= 2)// Why 2? To Big? or Small? Maby Fuzzy?
	{
		GOAL = 0;			// No longer seeking the goal.
		behave = EXPLORE;
		clear=1;
	}
	//
	if(clear)	// Find next node...
	{
		Cur_node = NMap->findnext(Cur_node);// Then look for new node
		//
		int count =0;
		while((!planRoute(Cur_node)) && (count < NMap->NumNodes))
		{
//printf("\nFINDNEXT called from EXPLORE NODE loop");
			Cur_node = NMap->findnext(Cur_node);// Then look for new one
			count++;
		}
				if(count==NMap->NumNodes)
				{
//					printf("\n\n\tDroped out without finding route a");
//					getch();
				}
	}
}

void Robot::explore()
{
	if(doing == NODE)	// Traveling to a node
	{
//printf("\nNODE");
		if( NMap->distance(	pos_x,pos_y,				// If arived at node
							target.x,target.y) <= 2)// Why 2? To Big? or Small? Maby Fuzzy?
		{
//printf("\n distance close");
			Cur_dir = NMap->assessNode(Cur_node);	// target is set within assessNode!
//
			if(Cur_dir<8)					// If node incompleate
			{
				doing = EXPAND;
//printf("\nassesed node and now expanding it");
			}
			else						// find a new node
			{						
				NMap->setExploredBit(Cur_node);
//
//printf("\nFINDNEXT called from EXPLORE NODE");
				Cur_node = NMap->findnext(Cur_node);// Then look for new node
				//
				int count =0;
				while((!planRoute(Cur_node)) && (count < NMap->NumNodes))
				{
//printf("\nFINDNEXT called from EXPLORE NODE loop");
					Cur_node = NMap->findnext(Cur_node);// Then look for new one
					count++;
				}
				if(count==NMap->NumNodes)
				{
//printf("\n\n\tDroped out without finding route b");
//					getch();
				}
			}
//
			possible = 3;
		}
	}
//
	if(	(doing == EXPAND))// &&	// Trying to expand node map
//		(behave == EXPLORE)	)	// But only if not tracking a target!
	{
//printf("\nEXPAND");
		if( NMap->Nodes[Cur_node]->DirFlag[Cur_dir] == 1) // Link has been created in NMap Update stage
		{
//printf("\nDirflag is set!");
//printf("\nFINDNEXT called from EXPLORE EXPAND");
			Cur_node = NMap->findnext(Cur_node);// Then look for new node
			int count =0;
			while((!planRoute(Cur_node)) && (count < NMap->NumNodes))
			{
//printf("\nFINDNEXT called from EXPLORE EXPAND loop");
				Cur_node = NMap->findnext(Cur_node);// Then look for new one
				count++;
			}
				if(count==NMap->NumNodes)
				{
//					printf("\n\n\tDroped out without finding route c");
//					getch();
				}
			possible = 3;
			doing = NODE;
		}
	//
		float dist = NMap->distance(pos_x, pos_y, float(target.x), float(target.y) );
//
		if(	(doing != NODE)	&&	//	check status has not already changed
			(dist <= 1.0) )		// 
		{
//printf("\nArived at expand target");
			NMap->Nodes[Cur_node]->DirFlag[Cur_dir] = -1;	//Indicate failure to form link but success in getting to position
//
//printf("\nFINDNEXT called from EXPLORE Distance");
			Cur_node = NMap->findnext(Cur_node);// Then look for new one
			int count =0;
			while((!planRoute(Cur_node)) && (count < NMap->NumNodes))
			{
//printf("\nFINDNEXT called from EXPLORE Distance loop");
				Cur_node = NMap->findnext(Cur_node);// Then look for new one
				count++;
			}
			if(count==NMap->NumNodes)
			{
//				printf("\n\n\tDroped out without finding route d");
//				getch();
			}
//printf("\nnow doing NODE");
			possible = 3;
			doing = NODE;
		}
	}
//
/*	if(	(doing == EXPAND)	&&	// Trying to expand node map
		(behave == TARGET)	)	// whilst tracking a target!
	{
printf("\n\n\n\t\t\tEXPAND IN TARGET !!!\n\n\n");
			Cur_node = NMap->findnext(Cur_node);// Then look for new one
			int count =0;
			while((!planRoute(Cur_node)) && (count < NMap->NumNodes))
			{
//printf("\nFINDNEXT called from EXPLORE Distance loop");
				Cur_node = NMap->findnext(Cur_node);// Then look for new one
				count++;
			}
			if(count==NMap->NumNodes)
			{
//				printf("\n\n\tDroped out without finding route; dags");
//				getch();
			}
//printf("\nnow doing NODE");
			possible = 3;
			doing = NODE;
	}*/
}
//
Robot::Notpossible()						// totally failed to get there	
{
//printf("\nImpossible");
//
	int Last_Node = Cur_node;
//
	if((behave==EXPLORE) && (doing==EXPAND))
		NMap->Nodes[Cur_node]->DirFlag[Cur_dir] = -2;	//Indicate failure to form link because of failure getting to position //???
//
	if(ROUTE)
	{
		Last_Node = route_node;
		ROUTE =0;	// importanty to not be followiung route as this changes mode of findnext!!!
	}
//
	if(GOAL)
		GOAL =0;
//
	Cur_node = NMap->findnext(Cur_node);// Then look for new node
//printf("\nFINDNEXT called from NOTPOSSIBLE");
	int count =0;
	while((!planRoute(Cur_node)) && (count < NMap->NumNodes))
	{
//printf("\nFINDNEXT called from NOTPOSSIBLE loop");
		Cur_node = NMap->findnext(Cur_node);// Then look for new node
		if(Cur_node == Last_Node)
		{
			Cur_node = NMap->findnext(Cur_node);// Then skip this node and look for new/next one
			count++;
		}
		count++;
	}
				if(count==NMap->NumNodes)
				{
//					printf("\n\n\tDroped out without finding route e");
//					getch();
				}
	possible = 3;
	doing = NODE;
}

bool Robot::planRoute(int node)
{
	int x = NMap->Nodes[node]->x_x+NMap->off_x;	// convert to absolute
	int y = NMap->Nodes[node]->y_y+NMap->off_y;	// convert to absolute
//printf("\nPlan route to node number %d",node);
	return(planRoute(x,y));
}

bool Robot::planRoute()
{
	return(planRoute(goal.x,goal.y));
}

bool Robot::planRoute(float x,		// Absolute co-ord for goal/target
					  float y)		// Absolute co-ord for goal/target
{
//printf("\nRoutefinder");
	int ii;
	int endNode=-1, startNode=-1;
	float st_dist=9999, end_dist=9999;
	float dist;
	for(ii=0;ii<NMap->NumNodes;ii++)
	{
		if(NMapControl->isvisable(NMap->Nodes[ii]))
		{
			dist = NMap->distance(	NMap->Nodes[ii]->x_x,
									NMap->Nodes[ii]->y_y,
									pos_x - NMap->off_x,
									pos_y - NMap->off_y		);
			if(dist<st_dist)
			{
//printf("\nNode %d is closest to start at distance %f",ii,dist);
				startNode = ii;
				st_dist = dist;
			}
		}
//getch();
		if(NMapControl->isvisable(NMap->Nodes[ii], x, y))	// Freaky but correct, Nodes with relatiove co-ords and target given in abs co-ords. Ah well...
		{
			dist = NMap->distance(	NMap->Nodes[ii]->x_x,	// all co-ords
									NMap->Nodes[ii]->y_y,	// are relative
									x - NMap->off_x,		// x adjusted.
									y - NMap->off_y		);	// y adjusted.
			if(dist<end_dist)
			{
//printf("\nNode %d is closest to end at distance %f",ii,dist);
				endNode = ii;
				end_dist = dist;
			}
		}
	}
//getch();
	if(startNode==-1)
	{
//printf(" Had no startNode");
		return(0);						// return with FAIL
	}
//
//	Allow VERY short routs
	if(startNode == endNode)
	{
//printf(" starting node was same as ending node");
//		return(0);						// return with FAIL
	}
//
	if(endNode ==-1)
	{
//printf("\nBlindly going where no Robotic race has been before");
		end_dist=9999;
		for(ii=0;ii<NMap->NumNodes;ii++)
		{
			dist = NMap->distance(	NMap->Nodes[ii]->x_x,
									NMap->Nodes[ii]->y_y,
									x - NMap->off_x,
									y - NMap->off_y		);
			if(dist<end_dist)
			{
				endNode = ii;
				end_dist = dist;
			}
		}
//printf(" Chosen a blind end location");
	}
//
	int jj;
	for(jj=0;jj<8;jj++)
	{
		if(	(NMap->Nodes[startNode]->DirFlag[jj] == 1) &&
			(NMap->Nodes[startNode]->link[jj]->num == endNode) )
		{
//printf(" The route consists of only start and end nodes");
//			return(0);					// return with fail as route is only one node long!
		}	// Short routs are OK too!
	}
//
//printf("\nStart atnode %d and end at node %d", startNode, endNode);
//
// Otherwise we have a start and end point and can plan a route between
	for(ii=0;ii<NMap->NumNodes;ii++)
	{
		NMap->Nodes[ii]->checked=0;		// clear all checked bits
		NMap->Nodes[ii]->routeDir=-1;	// mark all direction bits
	}
	// clear exploration list
	NMapControl->routelist.clearlist();
	// 
	NMapControl->routelist.putlist(endNode);
//
	int exit = 0;
	int next = -2;		// Get-out clause,failure to find start node
	while((next != -1) && (!exit))	// As ALL nodes are connected this should never happen!
	{
		next = NMapControl->routelist.getlist();
		if(next == startNode)
		{
			exit = 1;
			break;
		}
		if(next == -1 )
			break;			// Tidy up here, while loop is not effective!!!
		else
			propogate(next);
	}
	if(next == -1)	// Underflow error
	{
//printf("\n Failed to find a connection");
		return(0);		// Failed to find full route + will not be of assistance
	}
//
	startAt = startNode;
	Cur_node = startNode;
	endAt = endNode;
	target.x= NMap->Nodes[startNode]->x_x + NMap->off_x;
	target.y= NMap->Nodes[startNode]->y_y + NMap->off_y;
	route_node = startAt;
//printf("Start node has direction set to %d",NMap->Nodes[startNode]->routeDir);
//getch();
	ROUTE=1;
	GOAL=0;
//printf(" Sucessful");
//printf("\nRoute starts at %d ends at %d cur_node is %d",startAt,endAt,Cur_node);
	return(1);							// return with success
}

void Robot::propogate(int from)
{
	int ii,backdir;
	for(ii=0;ii<8;ii++)
	{
		if(NMap->Nodes[from]->DirFlag[ii]==1)	// if a link exists
		{
			if(NMap->Nodes[from]->link[ii]->checked==0)	// and node has not already been checked
			{
				backdir = ii - 4;	// generate a reverse direction reference
				if(backdir<0)
					backdir += 8;
				// store the route direction in each linked to node
				NMap->Nodes[from]->link[ii]->routeDir = backdir;
				// set checked flag to prevent further exploration
				NMap->Nodes[from]->link[ii]->checked = 1;
				// put node on list to evaluated
				NMapControl->routelist.putlist(NMap->Nodes[from]->link[ii]->num);
			}
		}
	}
}

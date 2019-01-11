// NodeMap.cpp: implementation of the NodeMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NodeMap.h"
#include "Robot.h"
#include "Node.h"
#include "Math.h"

#include "conio.h"	//del

#include "MapController.h"

// Behaviour constants included for findnext node, explore finds next node
// and target finds closest node to target!
#define EXPLORE	0
#define TARGET	1
#define STOP	2

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NodeMap::NodeMap(MapController *ref)
{
	nMapControl = ref;	// For back ref to func`s
	NumNodes = 0;
	pi = 3.1415926535;
	alldone =0;			// flag for id when all nodes have been fully evaluated
	NewNode =0;

}


NodeMap::~NodeMap()
{

}

void NodeMap::MakeMasterNode(float pos_x, float pos_y)
{
	off_x= pos_x;
	off_y= pos_y;

	Nodes = new Node *[1];
	Nodes[0] = new Node;

	Nodes[0]->x_x=0;
	Nodes[0]->y_y=0;
	Nodes[0]->num=0;

	NumNodes=1;

	nMapControl->fred->Cur_node =0;
}

void NodeMap::addNode(float xx, float yy)//, int direction, Node *linkTo)
{
//	int x_,y_;	//Location of connecting to node
//	int opp;	//direction flag for connecting to node
//	float distance; //distance between nodes
//	float direct;	//direction to link to node
	int thisNode;
	thisNode = appendNode();
	// Set position of new node
	Nodes[thisNode]->x_x=xx-off_x;
	Nodes[thisNode]->y_y=yy-off_y;
	// Set linking direction and node to link to
//	Nodes[thisNode]->DirFlag[direction]=1;	//integer flag N=0,NE=1,E=2,...,NW=7
//	Nodes[thisNode]->link[direction]=linkTo;
	// linkto node links from opposite side
//	opp=4+direction;
//	if(opp>7)
//		opp-=8;
//	linkTo->DirFlag[opp]=1;
	// Calculate distance and direction to linked to node
//	x_= linkTo->x_x;
//	y_= linkTo->y_y;
//	distance = pow( (pow( (x_-xx),2 )+pow( (y_-yy),2 )),0.5);
//	direct = calcDir(xx,yy,x_,y_);
	// Set link angles for both nodes
//	Nodes[thisNode]->dir[direction]= direct;
//	direct+=0.5;	// Half a full turn
//	if(direct>0.5)	// Range restricted
//		direct-=1;
//	linkTo->dir[opp]= direct;
	// Set link distance for both nodes
//	Nodes[thisNode]->dist[direction]= distance;
//	linkTo->dist[opp]= distance;
	// compleate link
//	linkTo->link[opp]= Nodes[thisNode];
	//
	// Housekeeping?
	// Argh... when a new node is created, the findnext would benefit from knowing about it!
	alldone = 0;
//	nMapControl->fred->Cur_node = thisNode; // Diss results in new nodes formed whilst exploring and expanding preventing correct identification of impossible links, potentially removing newly formed correct links.
}

void NodeMap::linkNodes(Node *ref_a,float direction,int dir,float distance ,Node *ref_b)
{
// Checking is done, just put ends together.
	int opp;					//direction flag for connecting to node
// Set linking direction and node to link to
	ref_a->DirFlag[dir]=1;		//integer flag N=0,NE=1,E=2,...,NW=7
	ref_a->link[dir]=ref_b;
// linkto node links from opposite side
	opp=dir+4;
	if(opp>7)
		opp-=8;
	ref_b->DirFlag[opp]=1;
// Set link angles for both nodes
	ref_a->dir[dir]= direction;
	direction+=0.5;				// Half a full turn
	if(direction>0.5)			// Range restricted
		direction-=1;
	ref_b->dir[opp]= direction;
// Set link distance for both nodes
	ref_a->dist[dir]= distance;
	ref_b->dist[opp]= distance;
// compleate link
	ref_b->link[opp]= ref_a;	
}

int NodeMap::appendNode()
{
//	Node **Old;
	Node **Newlist;
	Newlist = new Node *[NumNodes+1];	//Create pointer to node list
	Newlist[NumNodes] = new Node;		//Create new node on end of list
	Newlist[NumNodes]->num=NumNodes;	//Nodes node number(Keeps track of things)
	Newlist[NumNodes]->checked=0;
	int i;
	for(i=0;i<NumNodes;i++)		//Populate new list from old pointers
		Newlist[i]= Nodes[i];
	Nodes= Newlist;	// Re-address To new Node list
	NumNodes++;
	return(NumNodes-1);	// returns index of new node not number of nodes
}

float NodeMap::calcDir(float Rx, float Ry, float Tx, float Ty)
{
// Its not that I realy like tan or anything!
// just lifted the code from Makeinference::Exe
	float err;
	float dX= Rx - Tx;
	float dY= Ry - Ty;
//
	if(Ty<Ry)					//East
	{			
		if(Tx<Rx)		
			err= atan(dY/dX)/(2*pi)+0.25;			//North //////////
		else
			err= -0.25-(-(atan(dY/dX)/(2*pi)));		//South	/////O.K.//////
	}
//
	else											//West
	{
		if(Tx<Rx)
			err= atan(dY/dX)/(2*pi)+0.25;			//North
		else
			err= -0.25-(-(atan(dY/dX)/(2*pi)));		//South//////O.K.//////
	}
//
	if(err>0.5)
		err -= 1;
	if(err<-0.5)
		err += 1;	//Maintain -0.5 -> +0.5 range
//
	return(err);
}

int NodeMap::OriToCompas(float ori)
{
//printf("\nDirection %f",ori);
	if((ori<1/16.0)&&(ori>=-1/16.0))
	return(0);//N
	if((ori<-1/16.0)&&(ori>=-3/16.0))
	return(1);//NE
	if((ori<-3/16.0)&&(ori>=-5/16.0))
	return(2);//E
	if((ori<-5/16.0)&&(ori>=-7/16.0))
	return(3);//SE
	if(((ori<-7/16.0)&&(ori>=-8/16.0)) || ((ori<8/16.0)&&(ori>=7/16.0)))
	return(4);//S
	if((ori<7/16.0)&&(ori>=5/16.0))
	return(5);//SW
	if((ori<5/16.0)&&(ori>=3/16.0))
	return(6);//W
	if((ori<3/16.0)&&(ori>=1/16.0))
	return(7);//NW
//return error code...
	return(-13);
}

int NodeMap::closest(float to_x,	// abs
					 float to_y)	// abs
{
	to_x -= off_x;					// to rel
	to_y -= off_y;					// to rel
//
	int ii,ireg;
	float temp;
	float close=999;
	for(ii=0;ii<NumNodes;ii++)
	{
		temp = distance(	Nodes[ii]->x_x,	// rel
							Nodes[ii]->y_y,	// rel
							to_x,			// rel
							to_y	);		// rel
//printf("\n\t\t\t\tNode %d is at %f",ii,temp);
		if((temp<close) && (nMapControl->isvisable(Nodes[ii])))
		{
			close=temp;
			ireg = ii;
		}
	}
	last_distance= close;
//printf("\nNode %d is the closest node at distance of %f",ireg,close);
//if ireg<0 or ireg>number of nodes then no node identified and failure
	return(ireg);
}


float NodeMap::distance(int nodenum,	float x,	// abs
										float y)	// abs
{
	float ax = Nodes[nodenum]->x_x + off_x;
	float ay = Nodes[nodenum]->y_y + off_y;
	return(distance(ax, ay, x, y));
}

float NodeMap::distance(float ax, float ay, float bx, float by)
{
//printf("\n ax = %f\tay= %f",ax,ay);
//printf("\n bx = %f\tby= %f",bx,by);
	int dx,dy;
	//
	if(ax<bx)
		dx= bx-ax;
	else
		dx= ax-bx;
	//
	if(ay<by)
		dy= by-ay;
	else
		dy= ay-by;
	//
	float dist = pow(pow(dx,2.0)+pow(dy,2.0),0.5);
//printf("\nDistance between = %f",dist);
	return(dist);
}


int NodeMap::findnext(int current)
{
//	parseNode(current);
	//
	static float RecheckDist=0;		// last RE-evaluated distance
	static float prev_x,prev_y;
	//
	if(nMapControl->fred->ROUTE)
	{
		parseNode(current);
		int direction = Nodes[current]->routeDir;
		if((direction<0) || (direction>7))		// if robot strays off route
		{
			nMapControl->fred->ROUTE = 0;							// initiate reset
			nMapControl->fred->possible = 0;
			return(current);
		}
		int nextnum = Nodes[current]->link[direction]->num;
		return(nextnum);
	}
	else
	{
//printf("\nFinding next node");
		int ii;
	//
		int dist=9999;				// Temp distance evaluation
		int min_dist = 9999;		// Temp min so far dist
		int nextnum=-1;				// Node number of min so far dist.
		int goto_x, goto_y;
//
		if(nMapControl->fred->behave == EXPLORE)
		{
			goto_x = nMapControl->fred->pos_x;//nMapControl->fred->pos_x - nMapControl->fred->NMap->off_x;	// relative co-ords
			goto_y = nMapControl->fred->pos_y;//prev_y;//nMapControl->fred->pos_y - nMapControl->fred->NMap->off_y;	// Nearest Node
			if(!alldone)
				RecheckDist = 0; // Only when first building map, then cycle thro nodes, else repetative patterns may form
		}
		else	// behave == TARGET
		{
			goto_x = nMapControl->fred->goal.x - nMapControl->fred->NMap->off_x;	// relative co-ords
			goto_y = nMapControl->fred->goal.y - nMapControl->fred->NMap->off_y;	// relative co-ords;	// Nearest to goal
			if((goto_x != prev_x) || (goto_y != prev_y))
			{
				RecheckDist =0;		// Identify new target point and reset ...
			}
			prev_x = goto_x;
			prev_y = goto_y;
		}
		//
		int max_free_links=0;
		int num_free_links,cc;
		if(!alldone)			//	pick up newly created nodes and nodes on fresh map
		{
//printf("\n\tMap NOT done");
			for(ii=0;ii<NumNodes;ii++)				// For each node
			{
//printf("\n\t\tExamining Node number %d",ii);
				if(!Nodes[ii]->explored)		// That is NOT fully explored
				{
					if(Nodes[ii]->num != current)	// And is not the current node
					{
						num_free_links = 0;
						for(cc=0;cc<7;cc++)				// Check each link direction
						{
							if(Nodes[ii]->DirFlag[cc] == 0)	// For potential links
								num_free_links++;			// And clock them
						}
//printf("\n\t\tHas %d potential links",num_free_links);
						//
						if(num_free_links >= max_free_links)	// Look for node with most potential links
						{
						//
							max_free_links = num_free_links;	// set precedence
						//
							dist = distance(Nodes[ii]->x_x, Nodes[ii]->y_y, goto_x, goto_y);
							if(dist<min_dist)			// Withing these find closest
							{
								min_dist=dist;			// Record closest so far
								nextnum=ii;				// And its ID number
//printf(", IS SUCESSFULL!!!");
							}
							else
							{
//printf(", Not closest found so far");
							}
						//
						}
						else
						{
//printf(", Not A-Nuff to count");
						}
					}
					else
					{
//printf(" ... Current Node!");
					}
				}
				else
				{
//printf(" ... EXPLORED!");
				}
			}
			if(nextnum==-1)	// ALL nodes have been explored, time to start re-checking
			{
				alldone =1;	// And do until a new node is created... Does not count brocken links, see assessnode.
//printf("\n\tAll Nodes Explored!");
			}
		}
		//
		if(alldone)			// will catch alldone from last if!
		{
//printf("\n\tMap is now compleate");
			nextnum = -1;
			min_dist =9999; // unnessessary but reasuring
			for(ii=0;ii<NumNodes;ii++)
			{
//printf("\nExamining node number %d",ii);
				if(Nodes[ii]->num != current)	// Any apart from current node will do this time
				{
					dist = distance(Nodes[ii]->x_x, Nodes[ii]->y_y, goto_x, goto_y);
					if(	(dist<min_dist)	&&
						(dist>RecheckDist)	)	// For TARGET finding, standard search patern spock, ie start close and work out, only grab further nodes
					{							// RecheckDist is reset whenever in EXPLORE mode as robot will be moving!!!
						min_dist=dist;			// We therefore want any node further than the previous node and closer than any other we find.
						nextnum=ii;				// Store the ID.
//printf(" ... SUCESSFULL");
					}
					else
					{
//printf(" ... Outside range");
					}
				}
				else
				{
//printf(" ... Is current node");
				}
			}
			RecheckDist= min_dist;				// Set precidence for further searches
		}
		if(nextnum==-1)		// Around again folks! OK. at some point we will run out of further nodes
		{					// This Guarentees to return a valid node by starting again with the closest
//printf("\n\tMap is begin re-examined");
							// However almost chaotic for EXPLORE mode as closet to robots CURRENT position should be returned
			min_dist =9999; // unnessessary but reasuring
			for(ii=0;ii<NumNodes;ii++)
			{
//printf("\nExamining node number %d",ii);
				if(Nodes[ii]->num != current)	// But still not the current node, what would be the point?
				{
					dist = distance(Nodes[ii]->x_x, Nodes[ii]->y_y, goto_x, goto_y);
					if(dist<min_dist)
					{
						min_dist=dist;
						nextnum=ii;
						RecheckDist = dist;		// store new recheck starting point
//printf(" ... SUCESSFULL");
					}
					else
					{
//printf(" ... Not the closest found so far");
					}
				}
				else
				{
//printf(" ... Is current node");
				}
			}
		}
		if(NumNodes==1)
		{
//printf("\nOnly one node exists!!!");
			return(0);
		}
		else
		{
//printf("\n\tReturning node number %d as the next node",nextnum);
			return(nextnum);
		}
	}
}


void NodeMap::setExploredBit(int NodeNumber)
{
	Nodes[NodeNumber]->explored = 1;
}

int NodeMap::assessNode(int number)
{
// Passively... Update node
//printf("\nAssessing node number %d",number);
	parseNode(number);
	// Perform laser scan
	nMapControl->fred->Laz->scan( Nodes[number]->x_x+off_x , Nodes[number]->y_y+off_y );
//
	if(nMapControl->fred->behave == TARGET)
	{
		float direction = calcDir(
					nMapControl->fred->pos_x,
					nMapControl->fred->pos_y,
					nMapControl->fred->goal.x,
					nMapControl->fred->goal.y	);
		Nodes[number]->lastDir = OriToCompas(direction);
	}
//
//	if(nMapControl->fred->behave == EXPLORE)
//	{
//
//	}
//
	int ii,jj;
	int lastdir = Nodes[number]->lastDir;
	for(ii=lastdir-1;ii<lastdir-1+8;ii++)
	{
		jj = ii;
		if(jj<0)
			jj += 8;
		if(jj>7)
			jj -= 8;
//
		if(	(Nodes[number]->DirFlag[jj]==0)	||		// if direction has never been evaluated
			(	(Nodes[number]->explored==1)	&&		// OR if node has been fully explored
				(Nodes[number]->DirFlag[jj] < 0) ) )	// and now reassess failed directions
		{
//printf("\n\tChecking direction %d",jj);
			if(assessDir(jj,number))	// Sets goal position
			{
				Nodes[number]->lastDir=jj;		// Store last attempt!
//printf("..PASSED");
				return(jj);		// and returns id for link creation direction
			}
			Nodes[number]->DirFlag[jj]=-1;	// Set flag to show impassable
//printf("..... FAILED");
		}
//
	}
//printf("\nNode %d has been fully explored",num);
	Nodes[number]->explored = 1;		// Set flag to show node has been fully explored
	return(10);	// Fail on all directions
}

int NodeMap::assessDir(int dir, int num)
{
	int sum=0;
	float average=0;
	int dist, furthest =0;
	int direction;
	//
	int n= nMapControl->fred->Laz->rot_inc;
//
	int ii,jj;	//ii direction index	jj data index pointer
	int datapntr;	// modified distance data pointer
	for(ii=(dir/8.0)*n;ii<((dir+1)/8.0)*n;ii++)
	{
		jj=ii-(1.0/16)*n;
		if(jj<0)
			jj+=n;
		datapntr = 16-jj;
		if(datapntr < 0)
			datapntr += 32;
		dist = nMapControl->fred->Laz->distances[datapntr];
		if(!dist)
			dist = nMapControl->fred->Laz->MaxRange;
		sum += dist;
//printf("\nDistance data[%d] = %d",datapntr,dist);
//printf("\nSum now = %d",sum);
		if(dist>furthest)		// Direction of target is to be toward furthest point
		{
			direction = jj;
			furthest = dist;
//printf("\nfurthest now = %d",dist);
		}
	}
	average = sum/((1.0/8.0)*n);		// Distance of target is to be average of distances
//
	if(average<12)	// 8 is minimum distance for a valid link, and 2 for robot width, and 2 to prevent target being set into a wall, this removed when target is set!
	{
//printf("\nDirection %d Determined to short at %f",dir,average);
//getch();
		return(0);
	}
	//
	int dy = (average-2) * cos( 2*pi * direction/n );	// average is pulled back some!
	int dx = (average-2) * sin( 2*pi * direction/n );	// average is pulled back some!

	float new_x = Nodes[num]->x_x + off_x + dx;
	float new_y = Nodes[num]->y_y + off_y + dy;

	int closestnode = closest(	new_x,				// abs co-ord
								new_y	);			// abs co-ord

//printf("\n\nThe closest node is node number %d\n\n",closestnode);

	if(distance(closestnode,
				new_x,					// abs
				new_y)				// abs
						< 8	)	// if node closer than 8 no point searching as node will not be created

	{
//printf("\n*************************************************");
//printf("\nNode number:%d\tis %f away",closestnode,distance(closestnode, new_x, new_y));			// abs
		return(0);
	}
	else
	{
//printf("\nNode number:%d\tis %f away",closestnode,distance(closestnode, new_x, new_y));			// abs
	}

	nMapControl->fred->target.y = new_y;
	nMapControl->fred->target.x = new_x;
//printf("\nHave set target to be at %d,%d",nMapControl->fred->target.x, nMapControl->fred->target.y);
	return(1);
}

void NodeMap::parseNode(int number)
{
	nMapControl->NodeJoin(Nodes[number]);	// Check for new connections
//
	int jj;									// Check for broken links
	for(jj=0;jj<8;jj++)
	{
//printf("\n\tChecking direction %d",jj);
	   if(Nodes[number]->DirFlag[jj]==1)
	   {
			if(!(nMapControl->isvisable(
				Nodes[number]->link[jj],
				Nodes[number]->x_x + off_x,		// convert to abs co-ords
				Nodes[number]->y_y + off_y)) )	// convert to abs co-ords
			{
				int temp = jj - 4;
				if(temp<0)
					temp += 8;
				(Nodes[number]->link[jj])->DirFlag[temp] = -1;
				Nodes[number]->DirFlag[jj] = -1;
//nah			alldone=0;						// atleast one node is not fully explored
//nah			Nodes[number]->explored=0;
//printf(" ... Break link");
				//
				if(	(nMapControl->fred->ROUTE)	&&		// IF rout in progress
					(Nodes[number]->routeDir == jj)	)	// AND going that way
				{										// THEN Route stops HERE!
//printf(" ... And Halt route");
					nMapControl->fred->endAt = number;
					nMapControl->fred->Cur_node = number;
					nMapControl->fred->ROUTE=0;
				}
			}
			else
			{
//printf(" ... Still Valid");
			}
		}
		else
		{
//printf(" ... Direction Flag not set");
		}
	}
}

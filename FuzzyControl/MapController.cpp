// MapController.cpp: implementation of the MapController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "MapController.h"
#include "Robot.h"
#include "conio.h"
#include "Node.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void MapController::NodeRules()			// PRIMARY FIVE
{
	int noderef;
//	int dir,opp;
//	float alt_x,alt_y;	// Repeated locals in isvisable().!
//	float trg_x,trg_y;
//	float direction;
	// Always linking to closest node
	noderef = fred->NMap->closest(fred->pos_x,fred->pos_y);  //Returns clostest VISABLE node
	// Restricting resolution and range
	if( (fred->NMap->last_distance > 8) && (fred->NMap->last_distance < 20) )
	{
		// Must be visable from here closest() returns only visable node
//		if(isvisable(fred->NMap->Nodes[noderef]))			// LEGACY! closest updated to return only visable nodes
//		{	// Functions acting on node positions are relative
//		alt_x = fred->pos_x-fred->NMap->off_x;
//		alt_y = fred->pos_y-fred->NMap->off_y;
//		trg_x = fred->NMap->Nodes[noderef]->x_x;
//		trg_y = fred->NMap->Nodes[noderef]->y_y;
//		direction = fred->NMap->calcDir(alt_x,alt_y,trg_x,trg_y);
//		dir = fred->NMap->OriToCompas(direction);
		//
//		opp = dir+4;
//		if(opp>7)
///			opp-=8;
//		if(fred->NMap->Nodes[noderef]->DirFlag[opp] != 1)
//		{//	Only Node function taking absolute values, CLEAN UP!
			fred->NMap->addNode(fred->pos_x,fred->pos_y);//,dir,fred->NMap->Nodes[noderef]);
//printf("\nNode has been created");
			NodeJoin(fred->NMap->Nodes[fred->NMap->NumNodes-1]);
//		}
//		else
//		{
//printf("\nDirectionFlag %d is already set",dir);
//		}
//		}
//		else
//		{
//printf("\nNode is not visable from here");
//		}
	}
//	else
//	{
//printf("\nNode is not within range limits");
//	}
//	getch();
}

void MapController::NodeJoin(Node *newNode)
{
	int nn;				// Node list search counter
	float ax,ay,bx,by;
	float direction;	//absolute direction between nodes
	int dir, opp;			//direction code for link and reverse link
	float distance;
	float alt_x,alt_y;	//relative co-ords
	float trg_x,trg_y;
	for(nn=0;nn<fred->NMap->NumNodes-1;nn++)	// For each node in network
	{	// check range of each node in network !!!
		ax= newNode->x_x;
		ay= newNode->y_y;
		bx= fred->NMap->Nodes[nn]->x_x;
		by= fred->NMap->Nodes[nn]->y_y;
		distance= fred->NMap->distance(ax,ay,bx,by);
		if( (distance > 8) && (distance < 20) )
		{
			// Must be visable from here
			if(isvisable(fred->NMap->Nodes[nn]) )
			{	// Functions acting on node positions are relative
				alt_x = fred->pos_x-fred->NMap->off_x;
				alt_y = fred->pos_y-fred->NMap->off_y;
				trg_x = fred->NMap->Nodes[nn]->x_x;
				trg_y = fred->NMap->Nodes[nn]->y_y;
				direction = fred->NMap->calcDir(alt_x,alt_y,trg_x,trg_y);
				dir = fred->NMap->OriToCompas(direction);
				//
				opp = dir+4;
				if(opp>7)
					opp-=8;
				if((fred->NMap->Nodes[nn]->DirFlag[opp] != 1) && (fred->NMap->Nodes[fred->NMap->NumNodes-1]->DirFlag[dir] != 1))
				{//	Only Node function to take absolute values, CLEAN UP!
					fred->NMap->linkNodes(newNode,direction,dir,distance,fred->NMap->Nodes[nn]);
//printf("\nLinked Node %d to node %d in direction %d",newNode->num,nn,dir);
				}
				else
				{
//printf("\nDirectionFlag %d is already set",dir);
				}
			}
			else
			{
//				printf("\nNode is not visable from here");
			}
		}
	}
}

bool MapController::isvisable(int x,	// Absolute co-ords
							  int y)	// Absolute co-ords
{
	Node *bluff;
	bluff = new Node;
	bluff->x_x = x - fred->NMap->off_x;	// Make real co-ords into relative
	bluff->y_y = y - fred->NMap->off_y; // so they can pass as a node.
	bool vis = isvisable(bluff);
	return(vis);
}

bool MapController::isvisable(Node *Nref)
{
	bool visable=0;
	float direction;
	float distance;
	int range;
	float alt_x,alt_y;
	alt_x = float(fred->pos_x-fred->NMap->off_x);	// Converts freds position to relative coords
	alt_y = float(fred->pos_y-fred->NMap->off_y);	// Converts freds position to relative coords
// Functions acting on Node positions are relative
	direction = fred->NMap->calcDir(alt_x, alt_y, Nref->x_x, Nref->y_y);
	distance = fred->NMap->distance(alt_x, alt_y, Nref->x_x, Nref->y_y);
// Functions acting FROM Fred are absolute
	range = fred->Laz->measure(fred->pos_x,fred->pos_y,direction);
//printf("\nNode is %f away at angle %f",distance,direction);
//printf("\nVisable range is %d",range);
	// Range returns 0 for no hit!
	if(!range)
		range = fred->Laz->MaxRange;
	if(range>=distance)
	{
//printf(", Hence is visable");
		visable = 1;
	}
	else
	{
//		printf(", Hence is NOT visable");
	}
	return(visable);
}

bool MapController::isvisable(Node *Nref,	float x,	// Absolute co-ord
											float y)	// Absolute co-ord
{
	bool visable=0;
	float direction;
	float distance;
	int range;
	float alt_x,alt_y;
	alt_x = float(x-fred->NMap->off_x);	// Converted to relative co-ord
	alt_y = float(y-fred->NMap->off_y);	// Converted to relative co-ord
// Functions acting on Node positions are relative
	direction = fred->NMap->calcDir(alt_x, alt_y, Nref->x_x, Nref->y_y);
	distance = fred->NMap->distance(alt_x, alt_y, Nref->x_x, Nref->y_y);
// Functions acting FROM Fred are absolute
	range = fred->Laz->measure(fred->pos_x,fred->pos_y,direction);
//printf("\nNode is %f away at angle %f",distance,direction);
//printf("\nVisable range is %d",range);
	// Range returns 0 for no hit!
	if(!range)
		range = fred->Laz->MaxRange;
	if(range>=distance)
	{
//printf(", Hence is visable");
		visable = 1;
	}
	else
	{
//		printf(", Hence is NOT visable");
	}
	return(visable);
}

MapController::MapController(Robot *fredrica)
{
	fred=fredrica;
}

MapController::MapController()
{

}

MapController::~MapController()
{

}



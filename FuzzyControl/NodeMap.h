// NodeMap.h: interface for the NodeMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODEMAP_H__4FDB7D00_39FA_11D6_909D_444553540001__INCLUDED_)
#define AFX_NODEMAP_H__4FDB7D00_39FA_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"
#include "MapController.h"

class NodeMap  
{
public:
	float distance(int nodenum, float x, float y);
	void parseNode(int number);
	bool NewNode;
	bool alldone;
	int assessDir(int dir, int num);
	int assessNode(int num);
	void setExploredBit(int NodeNumber);
	int findnext(int current);
	double pi;
	float off_x,off_y;//
	float last_distance;	
	Node **Nodes;
	int NumNodes;

	MapController *nMapControl;		// For Backward ref to functions
	
	float distance(float ax, float ay, float bx, float by);
	int closest(float to_x, float to_y);
	int OriToCompas(float ori);
	float calcDir(float Rx, float Ry, float Tx, float Ty);
	int appendNode();
	void MakeMasterNode(float x, float y);
	void addNode(float x, float y);//, int dir, Node *linkTo );
	void linkNodes(Node *ref_a,float direction,int dir,float distance ,Node *ref_b);
	
	NodeMap();
	NodeMap(MapController *ref);
	virtual ~NodeMap();

};

#endif // !defined(AFX_NODEMAP_H__4FDB7D00_39FA_11D6_909D_444553540001__INCLUDED_)

// Node.h: interface for the Node class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__4FDB7D01_39FA_11D6_909D_444553540001__INCLUDED_)
#define AFX_NODE_H__4FDB7D01_39FA_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Node  
{
private:
public:
	bool checked;
	int routeDir;
	int lastDir;
	bool explored;
	int num;
	int DirFlag[8];
	Node *link[8];
	float dir[8];
	float dist[8];
	float x_x;
	float y_y;
	Node();
	virtual ~Node();
};

#endif // !defined(AFX_NODE_H__4FDB7D01_39FA_11D6_909D_444553540001__INCLUDED_)

// MapController.h: interface for the MapController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPCONTROLLER_H__B2A5A700_3B88_11D6_909D_444553540001__INCLUDED_)
#define AFX_MAPCONTROLLER_H__B2A5A700_3B88_11D6_909D_444553540001__INCLUDED_

#include "list.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Robot;
class Node;

class MapController  
{
public:
	list routelist;
	bool isvisable(Node *Nref, float x, float y);
	bool isvisable(int x, int y);
	void NodeJoin(Node *newNode);
	Robot *fred;
	bool isvisable(Node *Nref);
	void NodeRules();

	MapController();
	MapController(Robot *fredrica);
	virtual ~MapController();
};

#endif // !defined(AFX_MAPCONTROLLER_H__B2A5A700_3B88_11D6_909D_444553540001__INCLUDED_)

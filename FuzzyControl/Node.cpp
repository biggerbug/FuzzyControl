// Node.cpp: implementation of the Node class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Node.h"
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Node::Node()
{
	int i;
	for(i=0;i<8;i++)
	{
		DirFlag[i]=0;
	}
	explored= 0;	// Node has unexplored connections
//	lastDir=0;			//North essentially, but avoids NULL assignment
	lastDir = rand() % 8;	// Int modulus should return 0->7
//printf("\n\n\t\t RANDOM NUMBER = %d",lastDir);
}

Node::~Node()
{

}

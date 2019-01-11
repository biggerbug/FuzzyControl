// list.cpp: implementation of the list class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "list.h"
#include "conio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

list::list()
{
	items = new int*[0];
	listpntr = 0;
}

list::~list()
{

}

void list::clearlist()
{
//	int i;
//	for(i=0;i<listpntr;i++)	// free memory allocation
//		delete &items[i];
	listpntr=0;				// reset pointer to 0
	// Major Memory leak
}

void list::putlist(int num)
{
	int i;
	int **Newlist;
	Newlist = new int *[listpntr+1];	//Create pointer to int list
	Newlist[listpntr] = new int;		//Create new int on end of list
//
	for(i=0;i<listpntr;i++)		//Populate new list from old int`s
	{
		Newlist[i]= items[i];
	}
//
	items = Newlist;			// Re-address To new int list
//
	*items[listpntr] = num;		// add new element to end of list
//
//printf("\nPutting number %d onto list",num);
//printf("\nList now looks like:");
//for(i=0;i<listpntr+1;i++)
//	printf("\nitems[%d]=%d", i, *items[i]);
//
	listpntr++;
//	getch();
}

int list::getlist()
{
	int i;
	int value=-1;
//
	if(listpntr==0)				// if list is empty
	{
//printf("\nEmptyList");
//getch();
		return(-1);				// return a fail code
	}
//
//printf("\n*items[0]=%d",*items[0]);
	value = *items[0];			// store value
//printf(" and value=%d",value);
//
	for(i=1;i<listpntr;i++)
	{
		items[i-1] = items[i];	// copy values back down chain
//printf("\nMoving item %d value %d to position %d",i,*items[i],i-1);
	}
//
//
	listpntr--;					// readdress the listpntr
//	delete &items[listpntr];		// free the end memory allocation
//	Memory leak
//printf("\nReturning number %d from list",value);
//printf("\nList now looks like:");
//for(i=0;i<listpntr;i++)
//	printf("\n*items[%d]=%d", i, *items[i]);
//
//	getch();
	return(value);				// return with the topmost value
}

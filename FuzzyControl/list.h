// list.h: interface for the list class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIST_H__14D80584_4575_11D6_909D_444553540001__INCLUDED_)
#define AFX_LIST_H__14D80584_4575_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class list  
{
public:
	int listpntr;
	int **items;
	int getlist();
	void putlist(int num);
	void clearlist();
	list();
	virtual ~list();

};

#endif // !defined(AFX_LIST_H__14D80584_4575_11D6_909D_444553540001__INCLUDED_)

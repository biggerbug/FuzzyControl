// GrayMap.h: interface for the GrayMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAYMAP_H__4408D737_2497_11D6_909D_444553540001__INCLUDED_)
#define AFX_GRAYMAP_H__4408D737_2497_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GrayMap  
{
private:

	int **data;	

public:
	int size_x();
	int x_size;
	int y_size;
	
	int GetPos(int X, int Y);
	void SetPos(int X, int Y, int Value);
	GrayMap();
	virtual ~GrayMap();
	void Build(int x, int y);

};

#endif // !defined(AFX_GRAYMAP_H__4408D737_2497_11D6_909D_444553540001__INCLUDED_)

// FuzzyMap.h: interface for the FuzzyMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUZZYMAP_H__FCD713E0_2C83_11D6_909D_444553540001__INCLUDED_)
#define AFX_FUZZYMAP_H__FCD713E0_2C83_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class FuzzyMap  
{
	int **BWall, **BClear;
	int x_pos, y_pos;

public:
	void clearMap();
	int x_size, y_size;

	int GetClear(int X, int Y);
	void SetClear(int X, int Y, int Value);

	int GetWall(int X, int Y);
	void SetWall(int X, int Y, int Value);
	
	void Build(int x, int y);

	FuzzyMap();
	virtual ~FuzzyMap();

};

#endif // !defined(AFX_FUZZYMAP_H__FCD713E0_2C83_11D6_909D_444553540001__INCLUDED_)

// BoolMap.h: interface for the BoolMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOLMAP_H__26B06AE0_2C75_11D6_909D_444553540001__INCLUDED_)
#define AFX_BOOLMAP_H__26B06AE0_2C75_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BoolMap  
{
private:

public:
	bool **data;
	void drawWall(int ax, int ay, int bx, int by, bool color);
	int x_size;
	int y_size;

	bool GetPos(int X, int Y);
	void SetPos(int X, int Y, bool Value);

	void Build(int x, int y);

	BoolMap();
	virtual ~BoolMap();

};

#endif // !defined(AFX_BOOLMAP_H__26B06AE0_2C75_11D6_909D_444553540001__INCLUDED_)

// MakeMapping.h: interface for the MakeMapping class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKEMAPPING_H__A5D7DB75_26ED_11D6_909D_444553540001__INCLUDED_)
#define AFX_MAKEMAPPING_H__A5D7DB75_26ED_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Matrix.h"

class MakeMappings  
{
public:
	Matrix **Mats;

	void build();
	MakeMappings();
	virtual ~MakeMappings();

};

#endif // !defined(AFX_MAKEMAPPING_H__A5D7DB75_26ED_11D6_909D_444553540001__INCLUDED_)

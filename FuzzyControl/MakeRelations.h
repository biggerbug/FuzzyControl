// MakeRelations.h: interface for the MakeRelations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKERELATIONS_H__A5D7DB74_26ED_11D6_909D_444553540001__INCLUDED_)
#define AFX_MAKERELATIONS_H__A5D7DB74_26ED_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FzyRelation.h"		// includes membfunc

class MakeRelations  
{
public:
	
	FzyRelation **Rels; 
	void build();
	MakeRelations();
	virtual ~MakeRelations();

};

#endif // !defined(AFX_MAKERELATIONS_H__A5D7DB74_26ED_11D6_909D_444553540001__INCLUDED_)

// MakeInferences.h: interface for the MakeInferences class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKEINFERENCES_H__790E5720_2A0E_11D6_909D_444553540001__INCLUDED_)
#define AFX_MAKEINFERENCES_H__790E5720_2A0E_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MakeRelations.h"		// includes membfunc
#include "MakeMapping.h"		// includes matrix
#include "Infer.h"				// includes membfunc
//#include "Robot.h"

class Robot;

class MakeInferences  
{
	double pi;

	MakeRelations Relations;
	MakeMappings Mappings;

public:
	InFer **rules;
	int Exe(Robot *ref);
	void Build();
	MakeInferences();
	virtual ~MakeInferences();

	float Lwheel,Rwheel;

};

#endif // !defined(AFX_MAKEINFERENCES_H__790E5720_2A0E_11D6_909D_444553540001__INCLUDED_)

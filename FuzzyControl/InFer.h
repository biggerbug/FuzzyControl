// InFer.h: interface for the InFer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFER_H__D93C19E0_2642_11D6_909D_444553540001__INCLUDED_)
#define AFX_INFER_H__D93C19E0_2642_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FzyRelation.h"	//includes membfunc
#include "Matrix.h"

class InFer  
{
	FzyRelation *Rels[2];
	FzyRelation *Output;
	Matrix *Mat;


public:
	void Build(FzyRelation *RelA,FzyRelation *RelB, FzyRelation *Out, Matrix *Mx);
	float MaX(float,float);
	float MaX(FzyRelation *,int,float,FzyRelation *,int,float);
	float MiN(float,float);
	float MiN(FzyRelation *,int,float,FzyRelation *,int,float);
	float Exe(float, float);
	InFer();
	virtual ~InFer();

};

#endif // !defined(AFX_INFER_H__D93C19E0_2642_11D6_909D_444553540001__INCLUDED_)

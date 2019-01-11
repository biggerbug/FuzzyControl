// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__90666562_27B2_11D6_909D_444553540001__INCLUDED_)
#define AFX_MATRIX_H__90666562_27B2_11D6_909D_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Matrix  
{

public:
	int **M;

	void Build(int, int, int values[]);
	Matrix();
	virtual ~Matrix();

};

#endif // !defined(AFX_MATRIX_H__90666562_27B2_11D6_909D_444553540001__INCLUDED_)

// Matrix.cpp: implementation of the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "versionone.h"
#include "Matrix.h"

//#include "conio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix::Matrix()
{

}

void Matrix::Build(int colums, int rows, int values[])
{
	int count, countb;

	M = new int *[rows];
//printf("\n");
	for(count=0;count<rows;count++)
	{
		M[count] = new int[colums];
		for(countb=0;countb<colums;countb++)
		{
			M[count][countb] = values[count*colums+countb];
//			printf("%d ",M[count][countb]);
		}
//		printf("\n");
	}
//	printf("Matrix Build");
//	getch();
}

Matrix::~Matrix()
{

}


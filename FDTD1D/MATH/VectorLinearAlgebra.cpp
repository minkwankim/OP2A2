/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * VectorLinearAlgebra.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: minkwan
 */

#include "./MATH/Vector.hpp"

namespace OP2A{
namespace MATH{




VECTOR VectorCrossProduct(VECTOR A, VECTOR B)
{
	unsigned int N = A.size();
	if (N != B.size() || N != 3)
	{
		throw Common::ExceptionGeneral (FromHere(), "Dimension of X and Y values do not match", "DimensionMismatch:");
	}
	VECTOR C(N, 0.0);

	C(1)	= A(2)*B(3)- A(3)*B(2);
	C(2)	= A(3)*B(1)- A(1)*B(3);
	C(3)	= A(1)*B(2)- A(2)*B(1);

	return (C);
}


double VectorDotProduct(VECTOR A, VECTOR B)
{
	unsigned int N = A.size();
	if (N != B.size())
	{
		throw Common::ExceptionGeneral (FromHere(), "Dimension of X and Y values do not match", "DimensionMismatch:");
	}

	double ans = 0.0;
	for (int i = 1; i <= N; i++)	ans	+= A(i)*B(i);
	return (ans);
}


VECTOR NormalFromThreePoint(VECTOR A, VECTOR B, VECTOR C)
{
	VECTOR AB = B - A;
	VECTOR AC = C - A;

	VECTOR ans;
	ans	= VectorCrossProduct(AB, AC);
	return (ans);
}







}
}

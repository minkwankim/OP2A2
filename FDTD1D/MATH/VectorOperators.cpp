/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * VectorOperators.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: minkwan
 */


#include "./MATH/Vector.hpp"



namespace OP2A{
namespace MATH{


// Operator Functions
VECTOR operator- (VECTOR A, VECTOR B)
{
	unsigned int N = A.size();
	if (N != B.size())
	{
		throw Common::ExceptionGeneral (FromHere(), "Dimension of X and Y values do not match", "DimensionMismatch:");
	}

	VECTOR C(N, 0.0);


	for (int i = 1; i <= N; i++)	C(i) = A(i) - B(i);
	return (C);
}


VECTOR operator+ (VECTOR A, VECTOR B)
{
	unsigned int N = A.size();
	if (N != B.size())
	{
		throw Common::ExceptionGeneral (FromHere(), "Dimension of X and Y values do not match", "DimensionMismatch:");
	}

	VECTOR C(N, 0.0);


	for (int i = 1; i <= N; i++)	C(i) = A(i) + B(i);
	return (C);
}


VECTOR operator* (const double a, VECTOR B)
{
	unsigned int N = B.size();

	VECTOR C(N, 0.0);
	for (int i = 1; i <= N; i++)	C(i) = a * B(i);
	return (C);
}



}
}


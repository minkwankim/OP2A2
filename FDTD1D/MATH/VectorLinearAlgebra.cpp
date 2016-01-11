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
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"


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


double VectorDotProduct(std::vector<double> A, std::vector<double>B)
{
	// Check the size of vector
	if (A.size() != B.size())
	{
		Common::ExceptionGeneral(FromHere(), "Error in dot product: Dimension of X and Y values do not match", OP2A::Common::ErrorCode::NotMatchDimention());
	}

	double ans = 0.0;
	for (int i = 0; i <= A.size()-1; i++)	ans	+= A[i]*B[i];
	return (ans);
}

double VectorDotProduct(double (&A)[3], double (&B)[3])
{
	double ans = 0.0;
	for (int i = 0; i <= 2; i++)	ans	+= A[i]*B[i];
	return (ans);
}




}
}

/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ShapeFunctions.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */

#include <omp.h>

#include "Gridv2.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

namespace GRID
{


int ShapeFunctionsCircle(const double x, const double y, const double z)
{
	double Xc, Yc, Zc;
	double R;


	Xc	= 0.0;
	Yc	= 0.0;
	Zc	= 0.0;
	R	= 1.0;

	double f	= pow(x - Xc, 2.0) + pow(y - Yc, 2.0) + pow(z - Zc, 2.0) - R*R;

	if (f > 0)		return (inside_domain);
	else if (f < 0)	return (outside_domain);
	else			return (edge_domain);
}












}



/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridShapeFunctions.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: minkwan
 */


#include "./COMMON/ExceptionGeneral.hpp"

namespace OP2A {
namespace GRID {



int GridShapeFunctions(const double x, const double y, const double z)
{
	double temp;

	temp = pow((x-1.0), 2.0) + pow(y, 2.0) - 1.0;

	if (temp > 0.0)			return (1);
	else if (temp < 0.0)	return (-1);
	else					return (0);
}



int GridShapeFunctions(const double x, const double y)
{
	return (GridShapeFunctions(x, y, 0.0));
}


}
}

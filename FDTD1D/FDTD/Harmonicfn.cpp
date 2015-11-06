/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * harmonicfn.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: minkwan
 */



#include "Harmonicfn.hpp"


namespace OP2A{
namespace FDTD1D{

double Harmonic::harminic_fn(double x)
{
	double result;

	result	= amp * cos(x + phase);
	return (result);
}






}
}

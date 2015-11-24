/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GaussianPulse.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: minkwan
 */

#include "COMMON/Assert.hpp"
#include "GaussianPulse.hpp"

namespace OP2A{
namespace FDTD{




double GaussianPulse::ezInc(double time, double location)
{
	assert(width > 0.0);

	double gaussian;
	gaussian = exp( - pow((time - delay - location/cdtds) / width, 2));

	return (gaussian);
}

}
}




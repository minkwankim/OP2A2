/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_BareBone.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: minkwan
 */

#include "./COMMON/Common.hpp"
#include "./COMMON/Array1D.hpp"


namespace OP2A{
namespace FDTD{


void	FDTD1D_BareBone(OP2A::Common::Array1D<double>& ez, OP2A::Common::Array1D<double>& hy, double imp0, unsigned int SIZE, unsigned int maxTime)
{
	int qTime;
	int mm;

	// Time stepping
	for (qTime = 0; qTime < maxTime; qTime++)
	{
		// Update Magnetic field
		for (mm = 1; mm <= SIZE-1; mm++)
			hy(mm)	= hy(mm)	+ (ez(mm+1)	- ez(mm))/imp0;

		// Update Electric field
		for (mm = 2; mm <= SIZE; mm++)
			ez(mm)	= ez(mm)	+ (hy(mm) - hy(mm-1)) * imp0;

		// Hardwire a source node
		ez(0)	= exp(-(qTime-30.0) * (qTime- 30.0) / 100.0);
	}
}




}
}

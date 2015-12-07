/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_CalculateTime.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: minkwan
 */



#include "./FDTD/FDTD1D.hpp"
#include "./PHYS/ConstantsEM.hpp"
#include <cmath>

namespace OP2A {
namespace FDTD {



void FDTD1Dv2::CalculateTime()
{
	double dx_min;
	double dx_temp;

	// Find Min dX;
	dx_min = fabs(grid.faces[1].conn.listNodes[0]->geo.x[0] - grid.faces[1].conn.listNodes[1]->geo.x[0]);

	for (int f = 2; f <= grid.config.NFM; f++)
	{
		dx_temp = fabs(grid.faces[f].conn.listNodes[0]->geo.x[0] - grid.faces[f].conn.listNodes[1]->geo.x[0]);
		dx_min = fmin(dx_min, dx_temp);
	}


	setup.dt = dx_min * setup.Sc / C;
	setup.t	 += setup.dt;
}


}
}


/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_applyBC.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */




#include <FDTD/FDTD1D.hpp>

namespace OP2A {
namespace FDTD {



void FDTD1D::applyBC()
{
	switch (grid.BC_type_0)
	{
	case 0:	// PCM BC
		data.H(0)	= 0.0;
		data.E(0)	= 0.0;
		break;

	case 1: // ABC BC
		data.H(0)	= data.H(1);
		data.E(0)	= data.H(1);
		break;
	}

	switch (grid.BC_type_L)
	{
	case 0:	// PCM BC
		data.H(grid.NNM)	= 0.0;
		data.E(grid.NCM)	= 0.0;
		break;

	case 1: // ABC BC
		data.H(grid.NNM)	= data.H(1);
		data.E(grid.NCM)	= data.H(1);
		break;
	}
}


}
}

/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_Setup.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */





#include "FDTD1D_Setup.hpp"


namespace OP2A{
namespace FDTD{



FDTD1D_SETUP::FDTD1D_SETUP():
		maxTimeStep(0), Sc(1.0), dt(0.0), n(0), t(0)
{

}


FDTD1D_SETUP::~FDTD1D_SETUP()
{

}



}
}

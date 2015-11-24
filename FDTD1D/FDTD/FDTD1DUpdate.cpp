/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1DUpdate.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: minkwan
 */



#include <FDTD/FDTD1D.hpp>
#include "./PHYS/ConstantsEM.hpp"

namespace OP2A {
namespace FDTD {


void FDTD1D::UpdateH()
{
	// Update Magnetic field
#pragma ivdep
	for (int c = 1; c <= grid.NCM; c++)
	{
		data.H(c)	= 	data.m_CoeffH1(c)*data.H(c) + 	data.m_CoeffH2(c)*(data.E(c) - data.E(c-1));
	}
}





void FDTD1D::UpdateE()
{
#pragma ivdep
	for (int n = 1; n <= grid.NNM; n++)
	{
		data.E(n)	= 	data.m_CoeffE1(n)*data.E(n) + data.m_CoeffE2(n)*(data.H(n+1) - data.H(n));
	}
}

}
}

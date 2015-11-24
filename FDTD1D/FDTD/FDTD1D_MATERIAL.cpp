/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1DMATERIAL.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */

#include <FDTD/FDTD1D_MATERIAL.hpp>

namespace OP2A {
namespace FDTD {

FDTD1D_MATERIAL::FDTD1D_MATERIAL() {
	// TODO Auto-generated constructor stub

}

FDTD1D_MATERIAL::~FDTD1D_MATERIAL() {
	// TODO Auto-generated destructor stub
}


void FDTD1D_MATERIAL::allocateSize(unsigned int nnm, unsigned int ncm)
{
	mu_n.resize(nnm + 1);
	mu_c.resize(ncm+1);

	eps_n.resize(nnm+1);
	eps_c.resize(ncm+1);

	sigma_n.resize(nnm+1);
	sigma_c.resize(ncm+1);

	sigma_m_n.resize(nnm+1);
	sigma_m_c.resize(ncm+1);
}








FDTD1D_MATERIALv2::FDTD1D_MATERIALv2():
		mu(1.0), eps(1.0), sigma(0.0), sigma_m(0.0)
{

}

FDTD1D_MATERIALv2::~FDTD1D_MATERIALv2()
{
	// TODO Auto-generated destructor stub
}



} /* namespace FDTD */
} /* namespace OP2A */

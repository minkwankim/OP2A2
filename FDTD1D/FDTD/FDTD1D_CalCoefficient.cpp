/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_CalCoefficient.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: minkwan
 */



#include <FDTD/FDTD1D.hpp>

namespace OP2A {
namespace FDTD {






void FDTD1D::CalculateUpdateCoefficient()
{
#pragma ivdep
	for (int n = 1; n <= grid.NNM; n++)
	{
		double dx	= grid.dXn(n);
		double aux1 = material.sigma_n[n] * setup.dt / (2.0*material.eps_n[n]);
		double aux2 = setup.dt / (material.eps_n[n]*dx);

		data.m_CoeffE1(n)	= (1-aux1) / (1+aux1);
		data.m_CoeffE2(n)	= aux2 / (1+aux1);
	}

#pragma ivdep
	for (int c = 1; c <= grid.NCM; c++)
	{
		double dx	= grid.dXc(c);
		double aux1 = material.sigma_m_c[c] * setup.dt / (2.0*material.mu_c[c]);
		double aux2 = setup.dt / (material.mu_c[c]*dx);

		data.m_CoeffH1(c)	= (1-aux1) / (1+aux1);
		data.m_CoeffH2(c)	= aux2 / (1+aux1);
	}





}

}
}


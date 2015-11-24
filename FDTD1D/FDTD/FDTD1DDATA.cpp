/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1DDATA.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: minkwan
 */

#include <FDTD/FDTD1DDATA.hpp>

namespace OP2A {
namespace FDTD {

FDTD1D_DATA::FDTD1D_DATA():
		m_NCM(0), m_NNM(0),
		bc_E0(0.0), bc_EL(0.0),
		bc_H0(0.0), bc_HL(0.0),
		m_isAllocatedDataSize(false)

{
	// TODO Auto-generated constructor stub

}

FDTD1D_DATA::~FDTD1D_DATA() {
	// TODO Auto-generated destructor stub
}



double& FDTD1D_DATA::E(unsigned int i)
{
	if(i == 0)			return bc_E0;
	if(i >= m_NNM)		return bc_EL;

	return data_E(i);
}

double& FDTD1D_DATA::H(unsigned int i)
{
	if(i <= 0)			return bc_H0;
	if(i > m_NCM)		return bc_HL;

	return data_H(i);
}


void FDTD1D_DATA::SetDataSize(unsigned int nnm, unsigned int ncm)
{
	if (m_isAllocatedDataSize == false)
	{
		m_NCM	= ncm;
		m_NNM	= nnm;

		data_E.resize(m_NNM);
		m_CoeffE1.reserve(m_NNM);
		m_CoeffE2.reserve(m_NNM);

		data_H.resize(m_NCM);
		m_CoeffH1.reserve(m_NCM);
		m_CoeffH2.reserve(m_NCM);

		m_isAllocatedDataSize = true;
	}
}


void FDTD1D_DATA::InitE(double Eini)
{
	for (int i = 1; i <= m_NNM; i++)
	{
		data_E(i)	= Eini;
	}
}
void FDTD1D_DATA::InitH(double Hini)
{
	for (int i = 1; i <= m_NCM; i++)
	{
		data_H(i)	= Hini;
	}

}




} /* namespace FDTD */
} /* namespace OP2A */

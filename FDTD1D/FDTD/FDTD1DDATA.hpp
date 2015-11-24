/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1DDATA.hpp
 *
 *  Created on: Nov 17, 2015
 *      Author: minkwan
 */

#ifndef FDTD1DDATA_HPP_
#define FDTD1DDATA_HPP_

#include "./COMMON/Array1D.hpp"

using namespace std;

namespace OP2A {
namespace FDTD {

class FDTD1D_DATA {
public:
	FDTD1D_DATA();
	~FDTD1D_DATA();

public:
	Common::Array1D<double>	data_E;
	Common::Array1D<double>	data_H;

	double bc_E0;
	double bc_EL;

	double bc_H0;
	double bc_HL;

	Common::Array1D<double>	m_CoeffE1;
	Common::Array1D<double>	m_CoeffE2;

	Common::Array1D<double>	m_CoeffH1;
	Common::Array1D<double>	m_CoeffH2;

protected:
	unsigned int 	m_NCM;
	unsigned int	m_NNM;
	bool 			m_isAllocatedDataSize;





public:
	double& E(unsigned int i);
	double& H(unsigned int i);

	void SetDataSize(unsigned int nnm, unsigned int ncm);
	void InitE(double Eini);
	void InitH(double Hini);
};




} /* namespace FDTD */
} /* namespace OP2A */

#endif /* FDTD1DDATA_HPP_ */
